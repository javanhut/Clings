//! The C toolchain runner: detects a compiler, compiles an exercise, runs the
//! resulting binary and checks its output.

use std::{
    cell::OnceCell,
    env,
    ffi::OsString,
    fs,
    io::{Read, Write},
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
/// How many lines of a sanitizer report are shown before it is cut off.
const MAX_SANITIZER_LINES: usize = 30;

#[derive(Debug, Clone)]
pub struct Toolchain {
    pub cc: OsString,
    pub version: String,
    /// Whether `-fsanitize=address,undefined` works with this compiler.
    /// Probed lazily the first time an exercise asks for sanitizers.
    sanitizers: OnceCell<bool>,
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
                    return Ok(Self {
                        cc,
                        version,
                        sanitizers: OnceCell::new(),
                    });
                }
            }
        }
        bail!(
            "No C compiler found. Install gcc or clang, or point the CC environment variable at your compiler."
        )
    }

    /// Compiles a trivial program with the sanitizers enabled to find out
    /// whether this compiler (and its runtime libraries) support them.
    pub fn sanitizers_supported(&self) -> bool {
        *self.sanitizers.get_or_init(|| {
            let dir = env::temp_dir().join(format!("clings-probe-{}", std::process::id()));
            if fs::create_dir_all(&dir).is_err() {
                return false;
            }
            let src = dir.join("probe.c");
            let bin = dir.join(format!("probe{}", env::consts::EXE_SUFFIX));
            if fs::write(&src, "int main(void) { return 0; }\n").is_err() {
                return false;
            }
            let ok = Command::new(&self.cc)
                .args(["-fsanitize=address,undefined", "-o"])
                .arg(&bin)
                .arg(&src)
                .stdin(Stdio::null())
                .stdout(Stdio::null())
                .stderr(Stdio::null())
                .status()
                .map(|s| s.success())
                .unwrap_or(false);
            let _ = fs::remove_dir_all(&dir);
            if !ok {
                eprintln!(
                    "{}",
                    term::yellow(
                        "Note: your compiler does not support -fsanitize=address,undefined, so Clings \
                         cannot detect memory errors and undefined behavior automatically. Exercises \
                         are checked by output only. Installing gcc or clang with sanitizer runtime \
                         libraries (e.g. libasan/libubsan) fixes this."
                    )
                );
            }
            ok
        })
    }
}

/// Everything needed to compile and check one C source file.
pub struct CheckSpec<'a> {
    /// Used to name the compiled binary.
    pub bin_name: &'a str,
    pub source: &'a Path,
    /// Support files; the `.c` ones are compiled and linked with `source`.
    pub extra_sources: &'a [PathBuf],
    pub std: CStd,
    pub flags: &'a [String],
    /// Command-line arguments the program is started with.
    pub args: &'a [String],
    /// Text fed to the program on standard input.
    pub stdin: &'a str,
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

fn is_sanitizer_flag(flag: &str) -> bool {
    flag.starts_with("-fsanitize") || flag.starts_with("-fno-sanitize")
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
        for extra in spec.extra_sources {
            if !extra.is_file() {
                bail!(
                    "Support file {} does not exist. Run `clings reset` to restore it.",
                    extra.display()
                );
            }
        }

        let extra_c: Vec<&PathBuf> = spec
            .extra_sources
            .iter()
            .filter(|p| p.extension().is_some_and(|e| e == "c"))
            .collect();

        // Drop the sanitizer flags if this compiler cannot handle them.
        let wants_sanitizers = spec.flags.iter().any(|f| is_sanitizer_flag(f));
        let flags: Vec<&String> = if wants_sanitizers && !self.sanitizers_supported() {
            spec.flags
                .iter()
                .filter(|f| !is_sanitizer_flag(f))
                .collect()
        } else {
            spec.flags.iter().collect()
        };

        // 1. Compile. Flags go after the sources so that link flags such
        //    as `-lm` in required_flags work with linkers that use
        //    --as-needed (libraries named before the objects that need them
        //    would be dropped).
        let out = Command::new(&self.cc)
            .arg(spec.std.flag())
            .arg("-o")
            .arg(&bin)
            .arg(spec.source)
            .args(&extra_c)
            .args(&flags)
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
        let prog = run_with_timeout(&bin, spec.args, spec.stdin)?;
        let mut text = String::new();
        if !diagnostics.is_empty() {
            // Notes etc. that are neither errors nor warnings.
            text.push_str(&indent(&diagnostics));
            text.push('\n');
        }

        if let Some(headline) = sanitizer_headline(&prog.stderr) {
            text.push_str(&format!("{}\n", term::red(headline)));
            text.push_str(&term::dim(
                "The first lines of the report say what went wrong and on which line of your file.\n",
            ));
            if !prog.stdout.trim().is_empty() {
                push_output(&mut text, "Output before the error:", &prog.stdout);
            }
            text.push_str(&format!("{}\n", term::dim("Sanitizer report:")));
            text.push_str(&indent(&truncate_lines(
                prog.stderr.trim_end(),
                MAX_SANITIZER_LINES,
            )));
            return Ok(RunReport {
                passed: false,
                text,
            });
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
            push_output(&mut text, "Output:", &prog.stdout);
            if !prog.stderr.trim().is_empty() {
                push_output(&mut text, "Program stderr:", &prog.stderr);
            }
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
        } else {
            push_output(&mut text, "Output:", &prog.stdout);
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

/// Recognizes the reports printed by AddressSanitizer, LeakSanitizer and
/// UndefinedBehaviorSanitizer and turns them into a one-line verdict.
fn sanitizer_headline(stderr: &str) -> Option<&'static str> {
    if stderr.contains("LeakSanitizer") {
        Some("✗ LeakSanitizer: memory was allocated but never freed.")
    } else if stderr.contains("AddressSanitizer") {
        Some("✗ AddressSanitizer: the program accessed memory it does not own.")
    } else if stderr.contains("runtime error:") {
        Some("✗ UndefinedBehaviorSanitizer: the program relied on undefined behavior.")
    } else {
        None
    }
}

fn truncate_lines(s: &str, max: usize) -> String {
    let total = s.lines().count();
    if total <= max {
        return s.to_string();
    }
    let mut out: String = s.lines().take(max).collect::<Vec<_>>().join("\n");
    out.push_str(&format!("\n... ({} more lines)", total - max));
    out
}

/// Appends a labelled, indented block of program output. An empty output is
/// shown as `(nothing)` so the user can see the program really printed nothing.
fn push_output(text: &mut String, label: &str, output: &str) {
    text.push_str(&format!("{}\n", term::dim(label)));
    if output.trim().is_empty() {
        text.push_str(&term::dim("    (nothing)\n"));
    } else {
        text.push_str(&indent(output.trim_end()));
    }
    text.push('\n');
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

fn run_with_timeout(bin: &PathBuf, args: &[String], stdin: &str) -> Result<ProgramOutput> {
    let mut child = Command::new(bin)
        .args(args)
        .stdin(if stdin.is_empty() {
            Stdio::null()
        } else {
            Stdio::piped()
        })
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .with_context(|| format!("Failed to run {}", bin.display()))?;

    // Feed stdin from a separate thread so a program that never reads it
    // cannot make us block on a full pipe.
    if let Some(mut child_stdin) = child.stdin.take() {
        let input = stdin.to_string();
        thread::spawn(move || {
            let _ = child_stdin.write_all(input.as_bytes());
            // Dropping child_stdin closes the pipe, so the program sees EOF.
        });
    }

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

    #[test]
    fn sanitizer_reports_are_recognized() {
        assert!(sanitizer_headline("==1==ERROR: AddressSanitizer: heap-use-after-free").is_some());
        assert!(sanitizer_headline("x.c:3:5: runtime error: signed integer overflow").is_some());
        assert!(sanitizer_headline("==1==ERROR: LeakSanitizer: detected memory leaks").is_some());
        assert!(sanitizer_headline("just some stderr text").is_none());
    }

    #[test]
    fn sanitizer_flags_are_recognized() {
        assert!(is_sanitizer_flag("-fsanitize=address,undefined"));
        assert!(is_sanitizer_flag("-fno-sanitize-recover=undefined"));
        assert!(!is_sanitizer_flag("-Wall"));
    }

    #[test]
    fn truncation_keeps_short_text() {
        assert_eq!(truncate_lines("a\nb", 5), "a\nb");
        assert_eq!(truncate_lines("a\nb\nc", 2), "a\nb\n... (1 more lines)");
    }
}
