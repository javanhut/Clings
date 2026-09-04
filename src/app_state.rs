//! Application state: the exercise list, which one is current, which are
//! done, and persistence of that progress to `.clings-state.txt`.

use std::{fs, io, path::Path};

use anyhow::{bail, Context, Result};

use crate::{
    embedded,
    exercise::Exercise,
    info_file::InfoFile,
    runner::{RunReport, Toolchain},
    term,
};

pub const STATE_FILE: &str = ".clings-state.txt";
const STATE_HEADER: &str = "DON'T EDIT THIS FILE!\n\n";

pub struct AppState {
    pub exercises: Vec<Exercise>,
    current_idx: usize,
    n_done: usize,
    pub welcome_message: Option<String>,
    pub final_message: Option<String>,
    pub default_flags: Vec<String>,
    pub toolchain: Toolchain,
}

/// Parsed contents of the state file: current exercise name and done names.
fn parse_state(content: &str) -> (Option<&str>, Vec<&str>) {
    let mut lines = content
        .lines()
        .map(str::trim)
        .filter(|l| !l.is_empty() && !l.starts_with("DON'T EDIT"));
    let current = lines.next();
    (current, lines.collect())
}

impl AppState {
    pub fn load() -> Result<Self> {
        let info = InfoFile::parse()?;
        let toolchain = Toolchain::detect()?;

        let state = match fs::read_to_string(STATE_FILE) {
            Ok(s) => s,
            Err(e) if e.kind() == io::ErrorKind::NotFound => String::new(),
            Err(e) => return Err(e).context("Failed to read the state file"),
        };
        let (current_name, done_names) = parse_state(&state);

        let exercises: Vec<Exercise> = info
            .exercises
            .into_iter()
            .map(|ex| {
                let done = done_names.contains(&ex.name.as_str());
                Exercise::from_info(ex, done)
            })
            .collect();
        let n_done = exercises.iter().filter(|e| e.done).count();

        let current_idx = current_name
            .and_then(|name| exercises.iter().position(|e| e.name == name))
            .or_else(|| exercises.iter().position(|e| !e.done))
            .unwrap_or(0);

        Ok(Self {
            exercises,
            current_idx,
            n_done,
            welcome_message: info.welcome_message,
            final_message: info.final_message,
            default_flags: info.default_flags,
            toolchain,
        })
    }

    pub fn current_idx(&self) -> usize {
        self.current_idx
    }

    pub fn current(&self) -> &Exercise {
        &self.exercises[self.current_idx]
    }

    pub fn n_done(&self) -> usize {
        self.n_done
    }

    pub fn all_done(&self) -> bool {
        self.n_done == self.exercises.len()
    }

    pub fn find(&self, name: &str) -> Option<usize> {
        self.exercises
            .iter()
            .position(|e| e.name == name || e.display_name() == name)
    }

    /// Resolves an optional exercise name to an index, defaulting to the
    /// current exercise. Errors with suggestions if the name is unknown.
    pub fn resolve(&self, name: Option<&str>) -> Result<usize> {
        let Some(name) = name else {
            return Ok(self.current_idx);
        };
        if let Some(idx) = self.find(name) {
            return Ok(idx);
        }
        let mut msg = format!("No exercise named `{name}`.");
        let similar: Vec<&str> = self
            .exercises
            .iter()
            .filter(|e| e.name.contains(name) || name.contains(&e.name))
            .map(|e| e.name.as_str())
            .take(5)
            .collect();
        if !similar.is_empty() {
            msg.push_str(&format!(" Did you mean: {}?", similar.join(", ")));
        }
        msg.push_str("\nRun `clings list` to see all exercises.");
        bail!(msg)
    }

    pub fn find_by_abs_path(&self, path: &Path) -> Option<usize> {
        self.exercises.iter().position(|e| e.abs_path == path)
    }

    pub fn set_current_idx(&mut self, idx: usize) -> Result<()> {
        if idx != self.current_idx {
            self.current_idx = idx;
            self.write_state()?;
        }
        Ok(())
    }

    pub fn set_done(&mut self, idx: usize, done: bool) -> Result<()> {
        let ex = &mut self.exercises[idx];
        if ex.done != done {
            ex.done = done;
            if done {
                self.n_done += 1;
            } else {
                self.n_done -= 1;
            }
            self.write_state()?;
        }
        Ok(())
    }

    /// The next not-done exercise after the current one, wrapping around.
    /// Returns `None` when everything is done.
    pub fn next_pending(&self) -> Option<usize> {
        self.next_pending_after(self.current_idx)
    }

    /// The next not-done exercise after `idx`, wrapping around.
    pub fn next_pending_after(&self, idx: usize) -> Option<usize> {
        let n = self.exercises.len();
        (1..=n)
            .map(|offset| (idx + offset) % n)
            .find(|&i| !self.exercises[i].done)
    }

    pub fn run_exercise(&self, idx: usize) -> Result<RunReport> {
        self.exercises[idx].run(&self.toolchain, &self.default_flags)
    }

    /// Restores the exercise file to its pristine, embedded version and marks
    /// it as not done.
    pub fn reset(&mut self, idx: usize) -> Result<()> {
        self.restore_file(idx)?;
        self.set_done(idx, false)
    }

    /// Restores every exercise file, forgets all progress and makes the first
    /// exercise current again.
    pub fn reset_all(&mut self) -> Result<()> {
        for idx in 0..self.exercises.len() {
            self.restore_file(idx)?;
            self.exercises[idx].done = false;
        }
        self.n_done = 0;
        self.current_idx = 0;
        self.write_state()
    }

    /// Overwrites the exercise file with its pristine, embedded version
    /// without touching the recorded progress.
    fn restore_file(&self, idx: usize) -> Result<()> {
        let ex = &self.exercises[idx];
        let rel = ex.path.to_string_lossy().replace('\\', "/");
        let Some(content) = embedded::get(&rel) else {
            bail!(
                "No pristine copy of `{}` is embedded in this Clings binary, so it cannot be reset. \
                 (Custom exercises added to info.toml can only be reset by rebuilding Clings.)",
                ex.name
            );
        };
        if let Some(parent) = ex.path.parent() {
            fs::create_dir_all(parent)?;
        }
        fs::write(&ex.path, content)
            .with_context(|| format!("Failed to write {}", ex.path.display()))
    }

    pub fn write_state(&self) -> Result<()> {
        let mut content = String::from(STATE_HEADER);
        content.push_str(&self.current().name);
        content.push_str("\n\n");
        for ex in self.exercises.iter().filter(|e| e.done) {
            content.push_str(&ex.name);
            content.push('\n');
        }
        fs::write(STATE_FILE, content).context("Failed to write the state file")
    }

    pub fn progress_bar(&self) -> String {
        const WIDTH: usize = 40;
        let total = self.exercises.len();
        let filled = (self.n_done * WIDTH).checked_div(total).unwrap_or(0);
        let mut bar = String::new();
        bar.push_str(&term::green(&"#".repeat(filled)));
        if filled < WIDTH {
            bar.push_str(&term::green(">"));
            bar.push_str(&term::dim(&"-".repeat(WIDTH - filled - 1)));
        }
        let percent = if total == 0 {
            100.0
        } else {
            self.n_done as f64 * 100.0 / total as f64
        };
        format!(
            "Progress: [{bar}] {}/{} ({percent:.1} %)",
            self.n_done, total
        )
    }

    pub fn list(&self) -> String {
        let name_width = self
            .exercises
            .iter()
            .map(|e| e.display_name().len())
            .max()
            .unwrap_or(4)
            .max(4);
        let mut out = format!(
            "  {:<8} {:<name_width$}  {}\n",
            term::bold("Status"),
            term::bold("Name"),
            term::bold("Description"),
        );
        for (i, ex) in self.exercises.iter().enumerate() {
            let marker = if i == self.current_idx { ">" } else { " " };
            let status = if ex.done {
                term::green("done    ")
            } else {
                term::yellow("pending ")
            };
            out.push_str(&format!(
                "{marker} {status} {:<name_width$}  {}\n",
                ex.display_name(),
                term::dim(&ex.description),
            ));
        }
        out.push('\n');
        out.push_str(&self.progress_bar());
        out.push('\n');
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn state_file_round_trip() {
        let content = format!("{STATE_HEADER}intro2\n\nintro1\nvariables1\n");
        let (current, done) = parse_state(&content);
        assert_eq!(current, Some("intro2"));
        assert_eq!(done, vec!["intro1", "variables1"]);
    }

    #[test]
    fn empty_state() {
        let (current, done) = parse_state("");
        assert_eq!(current, None);
        assert!(done.is_empty());
    }
}
