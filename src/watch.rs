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

    println!(
        "{} Using compiler `{}` ({}).",
        term::dim("Clings watch mode."),
        app.toolchain.cc.to_string_lossy(),
        term::dim(&app.toolchain.version)
    );
    if opts.manual_run {
        println!(
            "{}",
            term::dim("Manual mode: press `r` to check the current exercise.")
        );
    } else {
        println!(
            "{}",
            term::dim("Edit and save the exercise file; Clings re-checks it automatically.")
        );
    }
    println!();

    open_in_editor(&opts, app.current().path.as_path());
    let mut last_run = Instant::now() - Duration::from_secs(1);
    run_current(app, &mut last_run)?;

    while let Ok(event) = rx.recv() {
        match event {
            Event::FileChanged(path) => {
                // Editors fire several events per save; ignore the burst.
                if last_run.elapsed() < Duration::from_millis(200) {
                    continue;
                }
                let canonical = std::fs::canonicalize(&path).unwrap_or(path);
                let Some(idx) = app.find_by_abs_path(&canonical) else {
                    continue;
                };
                if idx != app.current_idx() {
                    app.set_current_idx(idx)?;
                }
                run_current(app, &mut last_run)?;
                drain_file_events(&rx);
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
                    run_current(app, &mut last_run)?;
                    drain_file_events(&rx);
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
                    run_current(app, &mut last_run)?;
                    drain_file_events(&rx);
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

fn drain_file_events(rx: &mpsc::Receiver<Event>) {
    // Give the editor's burst of events a moment to arrive, then discard it.
    thread::sleep(Duration::from_millis(100));
    let mut kept = Vec::new();
    while let Ok(ev) = rx.try_recv() {
        if !matches!(ev, Event::FileChanged(_)) {
            kept.push(ev);
        }
    }
    // Input events cannot be put back on the receiver; they are rare enough
    // during a run that handling them here is acceptable.
    for ev in kept {
        if let Event::Input(line) = ev {
            eprintln!(
                "{}",
                term::dim(&format!(
                    "(ignored input `{}` typed during a run)",
                    line.trim()
                ))
            );
        }
    }
}

fn run_current(app: &mut AppState, last_run: &mut Instant) -> Result<()> {
    let idx = app.current_idx();
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
        term::dim("n:next  h:hint  l:list  c:check-all  r:run again  q:quit")
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
