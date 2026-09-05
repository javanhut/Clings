//! `clings dev`: helpers for people writing exercises.

use std::{fs, path::Path, process::ExitCode};

use anyhow::{bail, Context, Result};

use crate::{app_state::AppState, cli::DevCommands, info_file::InfoFile, term};

pub fn run(cmd: DevCommands) -> Result<ExitCode> {
    match cmd {
        DevCommands::New { name, dir } => new(&name, dir.as_deref()),
        DevCommands::Check => check(),
    }
}

const EXERCISE_TEMPLATE: &str = r#"// {name}.c
//
// CONCEPT
// TODO: explain the idea in a few sentences: what it is and how it works.
//
// WHEN YOU USE THIS
// TODO: say where this shows up in real programs and why it matters.
//
// TASK
// TODO: say exactly what to fix or write.
//
// EXPECTED OUTPUT
//     Hello

#include <stdio.h>

int main(void)
{
    // TODO
    printf("Hello\n");
    return 0;
}
"#;

fn new(name: &str, dir: Option<&str>) -> Result<ExitCode> {
    if !Path::new("info.toml").is_file() {
        bail!("No info.toml in the current directory. Run `clings dev new` from the root of the Clings repository.");
    }
    if name.is_empty() || !name.chars().all(|c| c.is_ascii_alphanumeric() || c == '_') {
        bail!("Exercise names may only contain ASCII letters, digits and underscores");
    }
    let info = InfoFile::parse()?;
    if info.exercises.iter().any(|e| e.name == name) {
        bail!("An exercise named `{name}` already exists");
    }

    let mut ex_path = Path::new("exercises").to_path_buf();
    let mut sol_path = Path::new("solutions").to_path_buf();
    if let Some(dir) = dir {
        ex_path.push(dir);
        sol_path.push(dir);
    }
    fs::create_dir_all(&ex_path)?;
    fs::create_dir_all(&sol_path)?;
    ex_path.push(format!("{name}.c"));
    sol_path.push(format!("{name}.c"));
    if ex_path.exists() || sol_path.exists() {
        bail!(
            "{} or {} already exists",
            ex_path.display(),
            sol_path.display()
        );
    }
    let content = EXERCISE_TEMPLATE.replace("{name}", name);
    fs::write(&ex_path, &content)?;
    fs::write(&sol_path, &content)?;

    let mut entry = String::from("\n[[exercises]]\n");
    entry.push_str(&format!("name = \"{name}\"\n"));
    if let Some(dir) = dir {
        entry.push_str(&format!("dir = \"{dir}\"\n"));
    }
    entry.push_str("description = \"TODO\"\n");
    entry.push_str("hint = \"\"\"\nTODO\"\"\"\n");
    entry.push_str("expected_stdout = \"\"\"\nHello\n\"\"\"\n");
    let mut info_toml = fs::read_to_string("info.toml")?;
    if !info_toml.ends_with('\n') {
        info_toml.push('\n');
    }
    info_toml.push_str(&entry);
    fs::write("info.toml", info_toml).context("Failed to update info.toml")?;

    println!(
        "Created {} and {} and added `{name}` to info.toml.\n\
         Write the exercise, the solution, the hint and the expected output, then run \
         `clings dev check`. Rebuild Clings to embed the new files.",
        ex_path.display(),
        sol_path.display()
    );
    Ok(ExitCode::SUCCESS)
}

fn check() -> Result<ExitCode> {
    if !Path::new("info.toml").is_file() {
        bail!("No info.toml in the current directory. Run `clings dev check` from the root of the Clings repository.");
    }
    let app = AppState::load()?;
    println!(
        "Using compiler `{}` ({})",
        app.toolchain.cc.to_string_lossy(),
        app.toolchain.version
    );

    let mut problems = 0usize;
    let mut report = |ok: bool, what: String| {
        if ok {
            println!("{} {what}", term::green("ok  "));
        } else {
            problems += 1;
            println!("{} {what}", term::red("FAIL"));
        }
    };

    for ex in &app.exercises {
        let name = ex.display_name();
        if !ex.path.is_file() {
            report(
                false,
                format!("{name}: missing exercise file {}", ex.path.display()),
            );
            continue;
        }
        if !ex.solution_path.is_file() {
            report(
                false,
                format!(
                    "{name}: missing solution file {}",
                    ex.solution_path.display()
                ),
            );
            continue;
        }
        if ex.expected_stdout.trim().is_empty() && ex.expected_exit == 0 {
            report(false, format!("{name}: expected_stdout is empty"));
        }
        if ex.hint.trim().is_empty() {
            report(false, format!("{name}: hint is empty"));
        }

        let sol = ex.run_solution(&app.toolchain, &app.default_flags)?;
        if sol.passed {
            report(true, format!("{name}: solution passes"));
        } else {
            report(
                false,
                format!("{name}: solution does not pass:\n{}", sol.text),
            );
        }

        if ex.skip_check_unsolved {
            continue;
        }
        let unsolved = ex.run(&app.toolchain, &app.default_flags)?;
        if unsolved.passed {
            report(
                false,
                format!("{name}: the unsolved exercise already passes"),
            );
        } else {
            report(true, format!("{name}: unsolved exercise fails as expected"));
        }
    }

    // Warn if exercises on disk are not listed in info.toml.
    let mut listed: std::collections::HashSet<_> =
        app.exercises.iter().map(|e| e.path.clone()).collect();
    for ex in &app.exercises {
        for extra in &ex.extra_sources {
            if !extra.is_file() {
                report(
                    false,
                    format!(
                        "{}: missing support file {}",
                        ex.display_name(),
                        extra.display()
                    ),
                );
            }
            listed.insert(extra.clone());
        }
    }
    for file in walk_c_files(Path::new("exercises"))? {
        if !listed.contains(&file) {
            report(
                false,
                format!("{} is not listed in info.toml", file.display()),
            );
        }
    }

    println!();
    if problems == 0 {
        println!("{}", term::green("Everything checks out ✓"));
        Ok(ExitCode::SUCCESS)
    } else {
        println!("{}", term::red(&format!("{problems} problem(s) found")));
        Ok(ExitCode::FAILURE)
    }
}

fn walk_c_files(dir: &Path) -> Result<Vec<std::path::PathBuf>> {
    let mut out = Vec::new();
    if !dir.is_dir() {
        return Ok(out);
    }
    for entry in fs::read_dir(dir)? {
        let path = entry?.path();
        if path.is_dir() {
            out.extend(walk_c_files(&path)?);
        } else if path.extension().is_some_and(|e| e == "c") {
            out.push(path);
        }
    }
    out.sort();
    Ok(out)
}
