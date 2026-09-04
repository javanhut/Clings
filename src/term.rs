//! Tiny ANSI color helpers. Colors are disabled when stdout is not a terminal
//! or when `NO_COLOR` is set.

use std::io::IsTerminal;
use std::sync::OnceLock;

fn enabled() -> bool {
    static ENABLED: OnceLock<bool> = OnceLock::new();
    *ENABLED
        .get_or_init(|| std::env::var_os("NO_COLOR").is_none() && std::io::stdout().is_terminal())
}

fn paint(code: &str, s: &str) -> String {
    if enabled() {
        format!("\x1b[{code}m{s}\x1b[0m")
    } else {
        s.to_string()
    }
}

pub fn bold(s: &str) -> String {
    paint("1", s)
}

pub fn dim(s: &str) -> String {
    paint("2", s)
}

pub fn red(s: &str) -> String {
    paint("1;31", s)
}

pub fn green(s: &str) -> String {
    paint("1;32", s)
}

pub fn yellow(s: &str) -> String {
    paint("1;33", s)
}

pub fn cyan(s: &str) -> String {
    paint("1;36", s)
}
