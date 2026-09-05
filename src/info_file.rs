//! Schema and parser for `info.toml`, the file that lists every exercise.

use std::{fmt, fs, io, path::PathBuf};

use anyhow::{bail, Context, Result};
use serde::Deserialize;

use crate::embedded;

/// The C standard an exercise is compiled with.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default, Deserialize)]
#[serde(rename_all = "lowercase")]
pub enum CStd {
    C89,
    C99,
    C11,
    #[default]
    C17,
    C23,
}

impl CStd {
    pub fn flag(self) -> &'static str {
        match self {
            CStd::C89 => "-std=c89",
            CStd::C99 => "-std=c99",
            CStd::C11 => "-std=c11",
            CStd::C17 => "-std=c17",
            CStd::C23 => "-std=c23",
        }
    }
}

impl fmt::Display for CStd {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.flag()[5..])
    }
}

#[derive(Debug, Clone, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct ExerciseInfo {
    /// Exercise name; also the file stem of the `.c` file.
    pub name: String,
    /// Optional topic directory below `exercises/` and `solutions/`.
    pub dir: Option<String>,
    /// One-line summary shown in the list.
    #[serde(default)]
    pub description: String,
    /// Shown by `clings hint`.
    pub hint: String,
    /// C standard to compile with. Defaults to c17.
    #[serde(default)]
    pub std: CStd,
    /// Exact stdout the compiled program must print.
    #[serde(default)]
    pub expected_stdout: String,
    /// Extra compiler flags for this exercise, in addition to `default_flags`.
    #[serde(default)]
    pub required_flags: Vec<String>,
    /// Exit code the program must return. Defaults to 0.
    #[serde(default)]
    pub expected_exit: i32,
    /// Command-line arguments passed to the program when it runs.
    #[serde(default)]
    pub args: Vec<String>,
    /// Text fed to the program on standard input when it runs.
    #[serde(default)]
    pub stdin: String,
    /// Support files, relative to the exercise's directory: `.c` files are
    /// compiled and linked together with the exercise (and the solution),
    /// `.h` files are only listed so that `clings reset` restores them.
    #[serde(default)]
    pub extra_sources: Vec<String>,
    /// `clings dev check` normally verifies that the unsolved exercise fails.
    /// Set this for exercises where that cannot be checked deterministically.
    #[serde(default)]
    pub skip_check_unsolved: bool,
}

impl ExerciseInfo {
    pub fn path(&self) -> PathBuf {
        rel_path("exercises", self.dir.as_deref(), &self.name)
    }

    pub fn solution_path(&self) -> PathBuf {
        rel_path("solutions", self.dir.as_deref(), &self.name)
    }

    /// Paths of the extra sources, resolved below `exercises/<dir>/`.
    pub fn extra_source_paths(&self) -> Vec<PathBuf> {
        self.extra_sources
            .iter()
            .map(|f| {
                let mut p = PathBuf::from("exercises");
                if let Some(dir) = &self.dir {
                    p.push(dir);
                }
                p.push(f);
                p
            })
            .collect()
    }
}

fn rel_path(root: &str, dir: Option<&str>, name: &str) -> PathBuf {
    let mut p = PathBuf::from(root);
    if let Some(dir) = dir {
        p.push(dir);
    }
    p.push(format!("{name}.c"));
    p
}

fn default_flags() -> Vec<String> {
    vec!["-Wall".into(), "-Wextra".into()]
}

#[derive(Debug, Deserialize)]
#[serde(deny_unknown_fields)]
pub struct InfoFile {
    pub format_version: u8,
    pub welcome_message: Option<String>,
    pub final_message: Option<String>,
    /// Compiler flags applied to every exercise. Defaults to `-Wall -Wextra`.
    #[serde(default = "default_flags")]
    pub default_flags: Vec<String>,
    pub exercises: Vec<ExerciseInfo>,
}

pub const CURRENT_FORMAT_VERSION: u8 = 1;

impl InfoFile {
    /// Reads `info.toml` from the current directory, falling back to the copy
    /// embedded in the binary.
    pub fn parse() -> Result<Self> {
        let content = match fs::read_to_string("info.toml") {
            Ok(c) => c,
            Err(e) if e.kind() == io::ErrorKind::NotFound => embedded::INFO_TOML.to_string(),
            Err(e) => return Err(e).context("Failed to read info.toml"),
        };
        Self::parse_str(&content)
    }

    pub fn parse_str(content: &str) -> Result<Self> {
        let info: InfoFile = toml::from_str(content).context("Failed to parse info.toml")?;
        info.validate()?;
        Ok(info)
    }

    fn validate(&self) -> Result<()> {
        if self.format_version > CURRENT_FORMAT_VERSION {
            bail!(
                "info.toml has format_version {}, but this version of Clings only supports up to {}. Please update Clings.",
                self.format_version,
                CURRENT_FORMAT_VERSION
            );
        }
        if self.exercises.is_empty() {
            bail!("info.toml does not list any exercises");
        }
        let mut seen = std::collections::HashSet::new();
        for ex in &self.exercises {
            if ex.name.is_empty() {
                bail!("info.toml contains an exercise with an empty name");
            }
            if !ex
                .name
                .chars()
                .all(|c| c.is_ascii_alphanumeric() || c == '_')
            {
                bail!(
                    "Exercise name `{}` is invalid: use only ASCII letters, digits and underscores",
                    ex.name
                );
            }
            if let Some(dir) = &ex.dir {
                if dir.is_empty() || dir.contains(['/', '\\', '.']) {
                    bail!("Exercise `{}` has an invalid dir `{dir}`", ex.name);
                }
            }
            for src in &ex.extra_sources {
                if src.is_empty()
                    || src.starts_with('/')
                    || src.contains("..")
                    || !(src.ends_with(".c") || src.ends_with(".h"))
                {
                    bail!(
                        "Exercise `{}` has an invalid extra source `{src}`: use a plain `.c` or `.h` file name in the exercise's directory",
                        ex.name
                    );
                }
            }
            if !seen.insert(&ex.name) {
                bail!("Duplicate exercise name `{}` in info.toml", ex.name);
            }
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn embedded_info_parses() {
        let info = InfoFile::parse_str(embedded::INFO_TOML).unwrap();
        assert!(info.exercises.len() > 10);
        for ex in &info.exercises {
            assert!(
                embedded::get(&ex.path().to_string_lossy()).is_some(),
                "exercise {} is not embedded",
                ex.name
            );
            assert!(
                embedded::get(&ex.solution_path().to_string_lossy()).is_some(),
                "solution for {} is not embedded",
                ex.name
            );
            for extra in ex.extra_source_paths() {
                assert!(
                    embedded::get(&extra.to_string_lossy()).is_some(),
                    "extra source {} for {} is not embedded",
                    extra.display(),
                    ex.name
                );
            }
        }
    }

    #[test]
    fn duplicate_names_are_rejected() {
        let toml = r#"
format_version = 1
[[exercises]]
name = "a"
hint = ""
[[exercises]]
name = "a"
hint = ""
"#;
        assert!(InfoFile::parse_str(toml).is_err());
    }

    #[test]
    fn bad_extra_sources_are_rejected() {
        let toml = r#"
format_version = 1
[[exercises]]
name = "a"
hint = ""
extra_sources = ["../evil.c"]
"#;
        assert!(InfoFile::parse_str(toml).is_err());
    }

    #[test]
    fn defaults_apply() {
        let toml = r#"
format_version = 1
[[exercises]]
name = "a"
dir = "d"
hint = "h"
extra_sources = ["lib.c"]
"#;
        let info = InfoFile::parse_str(toml).unwrap();
        assert_eq!(info.default_flags, vec!["-Wall", "-Wextra"]);
        let ex = &info.exercises[0];
        assert_eq!(ex.std, CStd::C17);
        assert_eq!(ex.expected_exit, 0);
        assert!(ex.args.is_empty());
        assert!(ex.stdin.is_empty());
        assert_eq!(ex.path(), PathBuf::from("exercises/d/a.c"));
        assert_eq!(ex.solution_path(), PathBuf::from("solutions/d/a.c"));
        assert_eq!(
            ex.extra_source_paths(),
            vec![PathBuf::from("exercises/d/lib.c")]
        );
    }
}
