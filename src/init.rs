//! `clings init`: writes the embedded exercises into a fresh `clings/` directory.

use std::{fs, path::Path, process::ExitCode};

use anyhow::{bail, Context, Result};

use crate::{embedded, term};

const GITIGNORE: &str = "/target\n.clings-state.txt\n";

const README: &str = r#"# Clings

Small exercises to get you used to reading and writing C code.

## How it works

Every file under `exercises/` is a short C program with something wrong or
missing in it. Your job is to fix it so that it

1. compiles with **no warnings**, and
2. prints exactly the expected output.

Start the interactive mode from this directory:

```
clings
```

Clings shows the current exercise, waits for you to edit and save the file,
then re-compiles and re-runs it automatically. When it passes, press `n` to
move on to the next one.

Useful commands:

| Command              | What it does                                       |
| -------------------- | -------------------------------------------------- |
| `clings`             | Watch mode: re-check the current exercise on save. |
| `clings run [name]`  | Compile and run one exercise.                      |
| `clings hint [name]` | Show a hint.                                       |
| `clings list`        | List all exercises and their status.               |
| `clings reset [name]`| Restore an exercise to its original state.         |
| `clings check-all`   | Check every exercise.                              |

Reference solutions live in `solutions/`. Try the hint first!

Your progress is stored in `.clings-state.txt`.
"#;

pub fn init() -> Result<ExitCode> {
    if Path::new("exercises").is_dir() {
        bail!(
            "An `exercises/` directory already exists here, so it looks like Clings is already \
             initialized in this directory.\nRun `clings` to start with the exercises."
        );
    }
    let root = Path::new("clings");
    if root.exists() {
        bail!(
            "A `clings` directory already exists here. Run `cd clings` and then `clings` to \
             continue, or remove that directory to start over."
        );
    }

    fs::create_dir(root).context("Failed to create the `clings` directory")?;
    for file in embedded::EMBEDDED_FILES {
        let path = root.join(file.path);
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent)
                .with_context(|| format!("Failed to create {}", parent.display()))?;
        }
        fs::write(&path, file.content)
            .with_context(|| format!("Failed to write {}", path.display()))?;
    }
    fs::write(root.join("info.toml"), embedded::INFO_TOML)?;
    fs::write(root.join(".gitignore"), GITIGNORE)?;
    fs::write(root.join("README.md"), README)?;

    println!(
        "{}\n\nRun `cd clings` to go into the new directory, then `clings` to get started.",
        term::green("Initialization done ✓")
    );
    Ok(ExitCode::SUCCESS)
}
