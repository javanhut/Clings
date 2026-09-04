//! The C toolchain runner: detects a compiler, compiles an exercise, runs the
//! resulting binary and checks its output.

use std::{
    env,
    ffi::OsString,
    fs,
    io::Read,
    path::{Path, PathBuf},
    process::{Command, ExitStatus, Stdio},
    thread,
    time::{Duration, Instant},
};

use anyhow::{bail, Context, Result};

use crate::{info_file::CStd, term};

/// How long a compiled exercise may run before it is killed.
const RUN_TIMEOUT: Duration = Duration::from_secs(10);
/// Where compiled binaries go, relative to the working directory.
const BIN_DIR: &str = "target/clings";

#[derive(Debug, Clone)]
pub struct Toolchain {
    pub cc: OsString,
    pub version: String,
}

impl Toolchain {
    /// Uses `$CC` if set, otherwise the first of `cc`, `gcc`, `clang` found on
    /// the PATH.
    pub fn detect() -> Result<Self> {
        let mut candidates: Vec<OsString> = Vec::new();
        if let Some(cc) = env::var_os("CC") {
            if !cc.is_empty() {
                candidates.push(cc);
            }
        }
        candidates.extend(["cc", "gcc", "clang"].map(OsString::from));

        for cc in candidates {
            let out = Command::new(&cc)
                .arg("--version")
                .stdin(Stdio::null())
                .output();
            if let Ok(out) = out {
                if out.status.success() {
                    let version = String::from_utf8_lossy(&out.stdout)
                        .lines()
                        .next()
                        .unwrap_or_default()
                        .trim()
                        .to_string();
                    return Ok(Self { cc, version });
                }
            }
        }
        bail!(
            "No C compiler found. Install gcc or clang, or point the CC environment variable at your compiler."
        )
    }
}

/// Everything needed to compile and check one C source file.
pub struct CheckSpec<'a> {
    /// Used to name the compiled binary.
    pub bin_name: &'a str,
    pub source: &'a Path,
    pub std: CStd,
    pub flags: &'a [String],
    pub expected_stdout: &'a str,
    pub expected_exit: i32,
}

/// The result of checking one exercise: whether it passed and a
/// human-readable report explaining why (or why not).
pub struct RunReport {
    pub passed: bool,
    pub text: String,
}

struct ProgramOutput {
    /// `None` when the program was killed for exceeding the timeout.
    status: Option<ExitStatus>,
    stdout: String,
    stderr: String,
}

impl Toolchain {
    pub fn check(&self, spec: &CheckSpec) -> Result<RunReport> {
        let bin_dir = Path::new(BIN_DIR);
        fs::create_dir_all(bin_dir)
            .with_context(|| format!("Failed to create {}", bin_dir.display()))?;
        let bin = bin_dir.join(format!("{}{}", spec.bin_name, env::consts::EXE_SUFFIX));

        if !spec.source.is_file() {
            bail!(
                "Exercise file {} does not exist. Run `clings reset` to restore it.",
                spec.source.display()
            );
        }

        // 1. Compile.
        let out = Command::new(&self.cc)
            .arg(spec.std.flag())
            .args(spec.flags)
            .arg("-o")
            .arg(&bin)
            .arg(spec.source)
            .stdin(Stdio::null())
            .output()
            .with_context(|| {
                format!(
                    "Failed to run the C compiler `{}`",
                    self.cc.to_string_lossy()
                )
            })?;
        let diagnostics = String::from_utf8_lossy(&out.stderr).trim_end().to_string();

        if !out.status.success() {
            let mut text = format!("{}\n", term::red("✗ Compilation failed:"));
            text.push_str(&indent(&diagnostics));
            return Ok(RunReport {
                passed: false,
                text,
            });
        }

        if has_warnings(&diagnostics) {
            let mut text = format!(
                "{}\n",
                term::yellow("✗ Compiled, but the compiler reported warnings. Clings requires warning-free code:")
            );
            text.push_str(&indent(&diagnostics));
            return Ok(RunReport {
                passed: false,
                text,
            });
        }

        // 2. Run.
        let prog = run_with_timeout(&bin)?;
        let mut text = String::new();
        if !diagnostics.is_empty() {
            // Notes etc. that are neither errors nor warnings.
            text.push_str(&indent(&diagnostics));
            text.push('\n');
        }

        let Some(status) = prog.status else {
            text.push_str(&format!(
                "{}\n",
                term::red(&format!(
                    "✗ The program did not finish within {} seconds and was killed. Do you have an infinite loop?",
                    RUN_TIMEOUT.as_secs()
                ))
            ));
            push_captured(&mut text, &prog);
            return Ok(RunReport {
                passed: false,
                text,
            });
        };

        let Some(code) = status.code() else {
            text.push_str(&format!(
                "{}\n",
                term::red(&format!("✗ The program crashed ({status})."))
            ));
            push_captured(&mut text, &prog);
            return Ok(RunReport {
                passed: false,
                text,
            });
        };

        // 3. Compare.
        let expected = normalize(spec.expected_stdout);
        let actual = normalize(&prog.stdout);
        let output_ok = expected == actual;
        let exit_ok = code == spec.expected_exit;

        if output_ok && exit_ok {
            text.push_str(&term::green(
                "✓ Compiled without warnings and printed the expected output!",
            ));
            text.push('\n');
            return Ok(RunReport { passed: true, text });
        }

        if !exit_ok {
            text.push_str(&format!(
                "{}\n",
                term::red(&format!(
                    "✗ The program exited with code {code}, but {} was expected.",
                    spec.expected_exit
                ))
            ));
        }
        if !output_ok {
            text.push_str(&format!("{}\n", term::red("✗ The output does not match.")));
            text.push_str(&render_diff(&expected, &actual));
        }
        if !prog.stderr.trim().is_empty() {
            text.push_str(&format!("{}\n", term::dim("Program stderr:")));
            text.push_str(&indent(prog.stderr.trim_end()));
            text.push('\n');
        }
        Ok(RunReport {
            passed: false,
            text,
        })
    }
}

fn push_captured(text: &mut String, prog: &ProgramOutput) {
    if !prog.stdout.trim().is_empty() {
        text.push_str(&format!("{}\n", term::dim("Output so far:")));
        text.push_str(&indent(prog.stdout.trim_end()));
        text.push('\n');
    }
    if !prog.stderr.trim().is_empty() {
        text.push_str(&format!("{}\n", term::dim("Program stderr:")));
        text.push_str(&indent(prog.stderr.trim_end()));
        text.push('\n');
    }
}

fn has_warnings(diagnostics: &str) -> bool {
    diagnostics
        .lines()
        .any(|l| l.contains("warning:") || l.contains("Warning:"))
}

fn indent(s: &str) -> String {
    let mut out = String::new();
    for line in s.lines() {
        out.push_str("    ");
        out.push_str(line);
        out.push('\n');
    }
    out
}

/// Splits program output into lines, ignoring trailing whitespace on each
/// line and trailing blank lines, so that a missing final newline does not
/// count as a failure.
pub fn normalize(s: &str) -> Vec<String> {
    let mut lines: Vec<String> = s.lines().map(|l| l.trim_end().to_string()).collect();
    while lines.last().is_some_and(|l| l.is_empty()) {
        lines.pop();
    }
    lines
}

fn render_diff(expected: &[String], actual: &[String]) -> String {
    let mut out = String::new();
    out.push_str(&format!("{}\n", term::bold("Expected output:")));
    if expected.is_empty() {
        out.push_str(&term::dim("    (nothing)\n"));
    }
    for l in expected {
        out.push_str(&format!("    {l}\n"));
    }
    out.push_str(&format!("{}\n", term::bold("Your program printed:")));
    if actual.is_empty() {
        out.push_str(&term::dim("    (nothing)\n"));
    }
    let first_diff = expected
        .iter()
        .zip(actual.iter())
        .position(|(e, a)| e != a)
        .unwrap_or(expected.len().min(actual.len()));
    for (i, l) in actual.iter().enumerate() {
        if i == first_diff {
            out.push_str(&format!("  {} {}\n", term::red(">"), term::red(l)));
        } else {
            out.push_str(&format!("    {l}\n"));
        }
    }
    if expected.len() != actual.len() && first_diff >= expected.len().min(actual.len()) {
        if actual.len() < expected.len() {
            out.push_str(&term::red(&format!(
                "  > (line {} is missing)\n",
                first_diff + 1
            )));
        } else {
            out.push_str(&term::red(&format!(
                "  (line {} was not expected)\n",
                first_diff + 1
            )));
        }
    } else {
        out.push_str(&term::dim(&format!(
            "First difference at line {}.\n",
            first_diff + 1
        )));
    }
    out
}

fn run_with_timeout(bin: &PathBuf) -> Result<ProgramOutput> {
    let mut child = Command::new(bin)
        .stdin(Stdio::null())
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .with_context(|| format!("Failed to run {}", bin.display()))?;

    let mut stdout = child.stdout.take().expect("stdout is piped");
    let mut stderr = child.stderr.take().expect("stderr is piped");
    let stdout_reader = thread::spawn(move || {
        let mut buf = Vec::new();
        let _ = stdout.read_to_end(&mut buf);
        buf
    });
    let stderr_reader = thread::spawn(move || {
        let mut buf = Vec::new();
        let _ = stderr.read_to_end(&mut buf);
        buf
    });

    let start = Instant::now();
    let status = loop {
        if let Some(status) = child.try_wait()? {
            break Some(status);
        }
        if start.elapsed() > RUN_TIMEOUT {
            let _ = child.kill();
            let _ = child.wait();
            break None;
        }
        thread::sleep(Duration::from_millis(5));
    };

    let stdout = stdout_reader.join().unwrap_or_default();
    let stderr = stderr_reader.join().unwrap_or_default();
    Ok(ProgramOutput {
        status,
        stdout: String::from_utf8_lossy(&stdout).into_owned(),
        stderr: String::from_utf8_lossy(&stderr).into_owned(),
    })
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn normalize_ignores_trailing_whitespace() {
        assert_eq!(normalize("a  \nb\n\n\n"), vec!["a", "b"]);
        assert_eq!(normalize("a\nb"), vec!["a", "b"]);
        assert_eq!(normalize(""), Vec::<String>::new());
        assert_ne!(normalize("a\nb"), normalize("a\n\nb"));
    }

    #[test]
    fn warnings_are_detected() {
        assert!(has_warnings("x.c:3:5: warning: unused variable"));
        assert!(!has_warnings("x.c:3:5: note: something"));
    }
}
