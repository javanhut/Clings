mod app_state;
mod cli;
mod dev;
mod embedded;
mod exercise;
mod info_file;
mod init;
mod runner;
mod term;
mod watch;

use std::{
    io::{self, Write},
    path::Path,
    process::ExitCode,
};

use anyhow::{bail, Result};
use clap::Parser;

use app_state::AppState;
use cli::{Args, Subcommands};

fn main() -> ExitCode {
    match run() {
        Ok(code) => code,
        Err(e) => {
            eprintln!("{} {e:#}", term::red("error:"));
            ExitCode::FAILURE
        }
    }
}

fn run() -> Result<ExitCode> {
    let args = Args::parse();

    // Commands that work before (or without) an initialized exercise directory.
    match args.command {
        Some(Subcommands::Init) => return init::init(),
        Some(Subcommands::Dev(cmd)) => return dev::run(cmd),
        _ => {}
    }

    if !Path::new("exercises").is_dir() {
        bail!(
            "No `exercises/` directory found in the current directory.\n\
             Run `clings init` to set up the exercises, then `cd clings` and run `clings` again."
        );
    }

    let mut app = AppState::load()?;

    match args.command {
        None => {
            let edit_cmd = if args.no_editor {
                None
            } else {
                args.edit_cmd
                    .or_else(|| std::env::var("CLINGS_EDIT_CMD").ok())
                    .map(|s| s.split_whitespace().map(str::to_string).collect::<Vec<_>>())
                    .filter(|v| !v.is_empty())
            };
            if let Some(msg) = app.welcome_message.as_deref().filter(|_| app.n_done() == 0) {
                println!("{}\n", msg.trim_end());
            }
            watch::watch(
                &mut app,
                watch::WatchOptions {
                    manual_run: args.manual_run,
                    edit_cmd,
                },
            )?;
            Ok(ExitCode::SUCCESS)
        }
        Some(Subcommands::Run { name }) => cmd_run(&mut app, name.as_deref()),
        Some(Subcommands::CheckAll) => cmd_check_all(&mut app),
        Some(Subcommands::Reset {
            all: true,
            keep_file,
            yes,
            ..
        }) => cmd_reset_all(&mut app, keep_file, yes),
        Some(Subcommands::Reset {
            name,
            keep_file,
            yes,
            ..
        }) => cmd_reset(&mut app, name.as_deref(), keep_file, yes),
        Some(Subcommands::Hint { name }) => {
            let idx = app.resolve(name.as_deref())?;
            let ex = &app.exercises[idx];
            println!(
                "{} {}\n\n{}",
                term::bold("Hint for"),
                term::bold(&ex.display_name()),
                ex.hint.trim_end()
            );
            Ok(ExitCode::SUCCESS)
        }
        Some(Subcommands::List) => {
            print!("{}", app.list());
            Ok(ExitCode::SUCCESS)
        }
        Some(Subcommands::Init) | Some(Subcommands::Dev(_)) => unreachable!("handled above"),
    }
}

fn cmd_run(app: &mut AppState, name: Option<&str>) -> Result<ExitCode> {
    let idx = app.resolve(name)?;
    println!("{}\n", app.exercises[idx].banner());
    let report = app.run_exercise(idx)?;
    print!("{}", report.text);
    app.set_done(idx, report.passed)?;
    println!();
    println!("{}", app.progress_bar());

    if !report.passed {
        // A failed run leaves the current exercise where it was, so trying an
        // old exercise never drags watch mode backwards.
        println!(
            "{}",
            term::dim(&format!(
                "Stuck? Try `clings hint {}`.",
                app.exercises[idx].name
            ))
        );
        return Ok(ExitCode::FAILURE);
    }
    if app.all_done() {
        println!(
            "\n{}",
            term::green("🎉 You have finished every exercise! 🎉")
        );
        if let Some(msg) = &app.final_message {
            println!("\n{}", msg.trim_end());
        }
    } else if idx == app.current_idx() {
        // Passing the current exercise moves on to the next pending one, as
        // `n` does in watch mode. Passing any other exercise (for example
        // re-running an old one) leaves the pointer alone.
        if let Some(next) = app.next_pending_after(idx) {
            app.set_current_idx(next)?;
            println!(
                "Next exercise: {} ({})",
                term::bold(&app.exercises[next].display_name()),
                app.exercises[next].path.display()
            );
        }
    } else {
        println!(
            "Current exercise is still {} ({}).",
            term::bold(&app.current().display_name()),
            app.current().path.display()
        );
    }
    Ok(ExitCode::SUCCESS)
}

/// Asks a yes/no question on the terminal. Returns `true` for yes.
fn confirm(question: &str) -> Result<bool> {
    print!("{} {question} [y/N] ", term::yellow("Warning:"));
    io::stdout().flush()?;
    let mut answer = String::new();
    io::stdin().read_line(&mut answer)?;
    Ok(matches!(answer.trim(), "y" | "Y" | "yes"))
}

fn cmd_reset_all(app: &mut AppState, keep_file: bool, yes: bool) -> Result<ExitCode> {
    let question = if keep_file {
        format!(
            "This forgets all your progress ({}/{} done) but keeps the files. Continue?",
            app.n_done(),
            app.exercises.len()
        )
    } else {
        format!(
            "This overwrites every exercise file and erases your progress ({}/{} done). Continue?",
            app.n_done(),
            app.exercises.len()
        )
    };
    if !yes && !confirm(&question)? {
        println!("Nothing was changed.");
        return Ok(ExitCode::FAILURE);
    }
    app.reset_all(keep_file)?;
    println!(
        "All {} exercises are pending again{}. Current exercise is {}. Run `clings` to start over.",
        app.exercises.len(),
        if keep_file {
            ""
        } else {
            " and restored to their original state"
        },
        term::bold(&app.current().display_name())
    );
    Ok(ExitCode::SUCCESS)
}

fn cmd_reset(
    app: &mut AppState,
    name: Option<&str>,
    keep_file: bool,
    yes: bool,
) -> Result<ExitCode> {
    let idxs = match name {
        None => vec![app.current_idx()],
        Some(name) => app.resolve_many(name)?,
    };
    if idxs.len() > 1 && !yes {
        let what = if keep_file {
            "forget the progress of"
        } else {
            "overwrite the files of and forget the progress of"
        };
        let question = format!(
            "This will {what} {} exercises in `{}`. Continue?",
            idxs.len(),
            name.unwrap_or_default()
        );
        if !confirm(&question)? {
            println!("Nothing was changed.");
            return Ok(ExitCode::FAILURE);
        }
    }
    for &idx in &idxs {
        app.reset(idx, keep_file)?;
        println!(
            "{} {}{}",
            term::green("reset"),
            app.exercises[idx].display_name(),
            if keep_file {
                " (progress forgotten, file kept)"
            } else {
                " (restored to its original state)"
            }
        );
    }
    // Make the first reset exercise current so `clings` picks it up next.
    let first = idxs[0];
    app.set_current_idx(first)?;
    println!(
        "\nCurrent exercise is now {} ({}). Run `clings` to redo it.",
        term::bold(&app.exercises[first].display_name()),
        app.exercises[first].path.display()
    );
    Ok(ExitCode::SUCCESS)
}

fn cmd_check_all(app: &mut AppState) -> Result<ExitCode> {
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
    match first_failed {
        None => {
            println!("\n{}", term::green("🎉 Every exercise passes! 🎉"));
            if let Some(msg) = &app.final_message {
                println!("\n{}", msg.trim_end());
            }
            Ok(ExitCode::SUCCESS)
        }
        Some(idx) => {
            app.set_current_idx(idx)?;
            println!(
                "Current exercise is now {}. Run `clings` to continue.",
                term::bold(&app.exercises[idx].display_name())
            );
            Ok(ExitCode::FAILURE)
        }
    }
}
