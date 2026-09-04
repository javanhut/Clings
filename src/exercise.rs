//! A single exercise and how to check it.

use std::path::PathBuf;

use anyhow::Result;

use crate::{
    info_file::{CStd, ExerciseInfo},
    runner::{CheckSpec, RunReport, Toolchain},
    term,
};

#[derive(Debug, Clone)]
pub struct Exercise {
    pub name: String,
    pub dir: Option<String>,
    pub description: String,
    pub hint: String,
    pub std: CStd,
    pub expected_stdout: String,
    pub required_flags: Vec<String>,
    pub expected_exit: i32,
    pub skip_check_unsolved: bool,
    /// Path of the exercise source, relative to the working directory.
    pub path: PathBuf,
    /// Path of the reference solution, relative to the working directory.
    pub solution_path: PathBuf,
    /// Absolute path of the exercise source, used to match file-watcher events.
    pub abs_path: PathBuf,
    pub done: bool,
}

impl Exercise {
    pub fn from_info(info: ExerciseInfo, done: bool) -> Self {
        let path = info.path();
        let abs_path = std::fs::canonicalize(&path).unwrap_or_else(|_| {
            std::env::current_dir()
                .map(|cwd| cwd.join(&path))
                .unwrap_or_else(|_| path.clone())
        });
        Self {
            solution_path: info.solution_path(),
            path,
            abs_path,
            name: info.name,
            dir: info.dir,
            description: info.description,
            hint: info.hint,
            std: info.std,
            expected_stdout: info.expected_stdout,
            required_flags: info.required_flags,
            expected_exit: info.expected_exit,
            skip_check_unsolved: info.skip_check_unsolved,
            done,
        }
    }

    /// The exercise name with its topic directory, e.g. `00_intro/intro1`.
    pub fn display_name(&self) -> String {
        match &self.dir {
            Some(dir) => format!("{dir}/{}", self.name),
            None => self.name.clone(),
        }
    }

    fn flags(&self, default_flags: &[String]) -> Vec<String> {
        default_flags
            .iter()
            .chain(self.required_flags.iter())
            .cloned()
            .collect()
    }

    /// Compiles and runs the exercise as the learner wrote it.
    pub fn run(&self, toolchain: &Toolchain, default_flags: &[String]) -> Result<RunReport> {
        let flags = self.flags(default_flags);
        toolchain.check(&CheckSpec {
            bin_name: &self.name,
            source: &self.path,
            std: self.std,
            flags: &flags,
            expected_stdout: &self.expected_stdout,
            expected_exit: self.expected_exit,
        })
    }

    /// Compiles and runs the reference solution (used by `clings dev check`).
    pub fn run_solution(
        &self,
        toolchain: &Toolchain,
        default_flags: &[String],
    ) -> Result<RunReport> {
        let flags = self.flags(default_flags);
        let bin_name = format!("{}_solution", self.name);
        toolchain.check(&CheckSpec {
            bin_name: &bin_name,
            source: &self.solution_path,
            std: self.std,
            flags: &flags,
            expected_stdout: &self.expected_stdout,
            expected_exit: self.expected_exit,
        })
    }

    /// A one-line banner printed before a run.
    pub fn banner(&self) -> String {
        let mut s = format!(
            "{} {}  {}",
            term::cyan("Exercise"),
            term::bold(&self.display_name()),
            term::dim(&self.path.display().to_string())
        );
        if !self.description.is_empty() {
            s.push('\n');
            s.push_str(&self.description);
        }
        s
    }
}
