use clap::{Parser, Subcommand};

/// Clings is a collection of small exercises to get you used to reading and
/// writing C code. Run it without a subcommand to start the interactive
/// watch mode.
#[derive(Parser)]
#[command(version, about, long_about = None)]
pub struct Args {
    /// Never open an editor when switching exercises, even if CLINGS_EDIT_CMD is set.
    #[arg(long, global = true)]
    pub no_editor: bool,

    /// Command used to open an exercise in your editor when it becomes the
    /// current one in watch mode, e.g. `--edit-cmd "code -g"`. The exercise
    /// path is appended. Defaults to the CLINGS_EDIT_CMD environment variable.
    #[arg(long, global = true, value_name = "CMD")]
    pub edit_cmd: Option<String>,

    /// In watch mode, do not watch files. Re-run the current exercise with `r`.
    #[arg(long, global = true)]
    pub manual_run: bool,

    #[command(subcommand)]
    pub command: Option<Subcommands>,
}

#[derive(Subcommand)]
pub enum Subcommands {
    /// Initialize the exercises in a new `clings/` directory.
    Init,
    /// Compile and run a single exercise. Runs the current exercise by default.
    Run {
        /// Name of the exercise, e.g. `intro1` or `00_intro/intro1`.
        name: Option<String>,
    },
    /// Check every exercise, marking each as done or pending.
    CheckAll,
    /// Restore an exercise to its original state. Resets the current exercise by default.
    Reset {
        /// Name of the exercise.
        name: Option<String>,
    },
    /// Show a hint for an exercise. Shows the hint for the current exercise by default.
    Hint {
        /// Name of the exercise.
        name: Option<String>,
    },
    /// List every exercise with its status.
    List,
    /// Commands for developing new exercises.
    #[command(subcommand)]
    Dev(DevCommands),
}

#[derive(Subcommand)]
pub enum DevCommands {
    /// Create a new exercise skeleton and append it to info.toml.
    New {
        /// Exercise name (letters, digits and underscores).
        name: String,
        /// Topic directory below `exercises/`, e.g. `06_pointers`.
        #[arg(long, short)]
        dir: Option<String>,
    },
    /// Verify info.toml, that every solution passes and every unsolved exercise fails.
    Check,
}
