//! Interactive watch mode: re-checks the current exercise whenever its file
//! is saved, and accepts single-letter commands on stdin.

use std::{
    io::{self, BufRead, Write},
    path::{Path, PathBuf},
    process::{Command, Stdio},
    sync::mpsc,
    thread,
    time::{Duration, Instant},
};

use anyhow::{Context, Result};
use notify::{EventKind, RecursiveMode, Watcher};

use crate::{app_state::AppState, term};

enum Event {
    FileChanged(PathBuf),
    Input(String),
    Eof,
}

pub struct WatchOptions {
    pub manual_run: bool,
    /// Command (program + args) used to open the current exercise in an editor.
    pub edit_cmd: Option<Vec<String>>,
}

pub fn watch(app: &mut AppState, opts: WatchOptions) -> Result<()> {
    if app.all_done() {
        print_final(app);
        return Ok(());
    }

    let (tx, rx) = mpsc::channel::<Event>();

    // Stdin reader thread.
    {
        let tx = tx.clone();
        thread::spawn(move || {
            let stdin = io::stdin();
            for line in stdin.lock().lines() {
                match line {
                    Ok(l) => {
                        if tx.send(Event::Input(l)).is_err() {
                            break;
                        }
                    }
                    Err(_) => break,
                }
            }
            let _ = tx.send(Event::Eof);
        });
    }

    // File watcher.
    let _watcher = if opts.manual_run {
        None
    } else {
        let tx = tx.clone();
        let mut watcher = notify::recommended_watcher(move |res: notify::Result<notify::Event>| {
            if let Ok(ev) = res {
                if matches!(ev.kind, EventKind::Modify(_) | EventKind::Create(_)) {
                    for path in ev.paths {
                        let _ = tx.send(Event::FileChanged(path));
                    }
                }
            }
        })
        .context("Failed to create the file watcher")?;
        watcher
            .watch(Path::new("exercises"), RecursiveMode::Recursive)
            .context("Failed to watch the exercises directory")?;
        Some(watcher)
    };

    open_in_editor(&opts, app.current().path.as_path());
    let mut last_run = Instant::now() - Duration::from_secs(1);
    // Set while we wait for a yes/no answer to "reset this exercise?".
    let mut awaiting_reset_confirm = false;
    run_current(app, &opts, &mut last_run)?;

    while let Ok(event) = rx.recv() {
        match event {
            Event::FileChanged(path) => {
                // Editors fire several events per save; ignore the burst.
                if last_run.elapsed() < Duration::from_millis(200) {
                    continue;
                }
                let canonical = std::fs::canonicalize(&path).unwrap_or(path);
                match app.find_by_abs_path(&canonical) {
                    Some(idx) => {
                        if idx != app.current_idx() {
                            app.set_current_idx(idx)?;
                        }
                    }
                    None => {
                        // A header or support file next to the current
                        // exercise (multi-file exercises) re-runs it.
                        if !is_support_file_for(app, &canonical) {
                            continue;
                        }
                    }
                }
                run_current(app, &opts, &mut last_run)?;
                if drain_file_events(&rx) {
                    break;
                }
            }
            Event::Input(line) if awaiting_reset_confirm => {
                awaiting_reset_confirm = false;
                if matches!(line.trim(), "y" | "Y" | "yes") {
                    let idx = app.current_idx();
                    app.reset(idx, false)?;
                    println!(
                        "{}",
                        term::green(&format!(
                            "{} has been restored to its original state.",
                            app.current().display_name()
                        ))
                    );
                    open_in_editor(&opts, app.current().path.as_path());
                    run_current(app, &opts, &mut last_run)?;
                    if drain_file_events(&rx) {
                        break;
                    }
                } else {
                    println!("Nothing was changed.");
                    prompt(app);
                }
            }
            Event::Input(line) => match line.trim() {
                "" => {}
                "n" | "next" => {
                    let Some(next) = app.next_pending() else {
                        print_final(app);
                        break;
                    };
                    if !app.current().done {
                        println!(
                            "{}",
                            term::yellow(
                                "The current exercise is not done yet. Skipping it for now."
                            )
                        );
                    }
                    app.set_current_idx(next)?;
                    open_in_editor(&opts, app.current().path.as_path());
                    run_current(app, &opts, &mut last_run)?;
                    if drain_file_events(&rx) {
                        break;
                    }
                }
                "h" | "hint" => {
                    println!(
                        "{}\n{}\n",
                        term::bold("Hint:"),
                        app.current().hint.trim_end()
                    );
                    prompt(app);
                }
                "l" | "list" => {
                    print!("{}", app.list());
                    println!();
                    prompt(app);
                }
                "c" | "check-all" => {
                    check_all(app)?;
                    prompt(app);
                }
                "r" | "run" => {
                    run_current(app, &opts, &mut last_run)?;
                    if drain_file_events(&rx) {
                        break;
                    }
                }
                "x" | "reset" => {
                    print!(
                        "{} Reset {} to its original state? Your changes to the file will be lost. [y/N] ",
                        term::yellow("Warning:"),
                        term::bold(&app.current().display_name())
                    );
                    let _ = io::stdout().flush();
                    awaiting_reset_confirm = true;
                }
                "q" | "quit" | "exit" => break,
                other => {
                    println!("{}", term::yellow(&format!("Unknown command `{other}`.")));
                    prompt(app);
                }
            },
            Event::Eof => break,
        }
        if app.all_done() {
            print_final(app);
            break;
        }
    }

    println!("{}", term::dim("Bye! Your progress is saved."));
    Ok(())
}

/// True when `path` is a `.c` or `.h` file in the current exercise's
/// directory that is not itself an exercise.
fn is_support_file_for(app: &AppState, path: &Path) -> bool {
    let is_source = path.extension().is_some_and(|e| e == "c" || e == "h");
    is_source && path.parent() == app.current().abs_path.parent()
}

/// Discards the burst of file events an editor fires per save. Returns
/// `true` if stdin reached end-of-file meanwhile, so the caller can stop.
fn drain_file_events(rx: &mpsc::Receiver<Event>) -> bool {
    // Give the editor's burst of events a moment to arrive, then discard it.
    thread::sleep(Duration::from_millis(100));
    let mut eof = false;
    while let Ok(ev) = rx.try_recv() {
        match ev {
            Event::FileChanged(_) => {}
            // Input events cannot be put back on the receiver; they are
            // rare enough during a run that dropping them is acceptable.
            Event::Input(line) => eprintln!(
                "{}",
                term::dim(&format!(
                    "(ignored input `{}` typed during a run)",
                    line.trim()
                ))
            ),
            Event::Eof => eof = true,
        }
    }
    eof
}

/// Prints the one-line watch-mode header shown at the top of every run.
fn print_header(app: &AppState, opts: &WatchOptions) {
    let how = if opts.manual_run {
        "Press `r` to check the current exercise."
    } else {
        "Save the exercise file to re-check it."
    };
    println!(
        "{}",
        term::dim(&format!(
            "Clings watch mode · {} · {how}",
            app.toolchain.version
        ))
    );
    println!();
}

fn run_current(app: &mut AppState, opts: &WatchOptions, last_run: &mut Instant) -> Result<()> {
    let idx = app.current_idx();
    term::clear_screen();
    print_header(app, opts);
    println!("{}", app.exercises[idx].banner());
    println!();
    let report = app.run_exercise(idx)?;
    print!("{}", report.text);
    *last_run = Instant::now();

    if report.passed {
        app.set_done(idx, true)?;
        println!();
        println!("{}", app.progress_bar());
        if app.all_done() {
            return Ok(());
        }
        if let Some(next) = app.next_pending() {
            println!(
                "Next exercise: {}. Press {} to continue.",
                term::bold(&app.exercises[next].display_name()),
                term::bold("n")
            );
        }
    } else {
        app.set_done(idx, false)?;
        println!();
        println!("{}", app.progress_bar());
    }
    prompt(app);
    Ok(())
}

fn check_all(app: &mut AppState) -> Result<()> {
    term::clear_screen();
    let mut first_failed = None;
    for idx in 0..app.exercises.len() {
        let report = app.run_exercise(idx)?;
        let name = app.exercises[idx].display_name();
        if report.passed {
            println!("{} {name}", term::green("✓"));
        } else {
            println!("{} {name}", term::red("✗"));
            first_failed.get_or_insert(idx);
        }
        app.set_done(idx, report.passed)?;
    }
    println!();
    println!("{}", app.progress_bar());
    if let Some(idx) = first_failed {
        app.set_current_idx(idx)?;
        println!(
            "Current exercise is now {}.",
            term::bold(&app.exercises[idx].display_name())
        );
    }
    Ok(())
}

fn prompt(app: &AppState) {
    let _ = app;
    println!(
        "{}",
        term::dim("n:next  h:hint  l:list  c:check-all  r:run again  x:reset  q:quit")
    );
    print!("> ");
    let _ = io::stdout().flush();
}

fn print_final(app: &AppState) {
    println!();
    println!("{}", app.progress_bar());
    println!();
    println!("{}", term::green("🎉 You have finished every exercise! 🎉"));
    if let Some(msg) = &app.final_message {
        println!();
        println!("{}", msg.trim_end());
    }
}

fn open_in_editor(opts: &WatchOptions, path: &Path) {
    let Some(cmd) = &opts.edit_cmd else {
        return;
    };
    let Some((program, args)) = cmd.split_first() else {
        return;
    };
    let result = Command::new(program)
        .args(args)
        .arg(path)
        .stdin(Stdio::null())
        .stdout(Stdio::null())
        .stderr(Stdio::null())
        .spawn();
    match result {
        Ok(mut child) => {
            // Detach: GUI editors return immediately, terminal ones would
            // fight with us over stdin, so we never wait for them.
            thread::spawn(move || {
                let _ = child.wait();
            });
        }
        Err(e) => eprintln!(
            "{}",
            term::yellow(&format!(
                "Could not run the editor command `{}`: {e}",
                cmd.join(" ")
            ))
        ),
    }
}
