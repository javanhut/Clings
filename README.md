# Clings 🔗

Small exercises to get you used to reading and writing C code. It is
[rustlings](https://github.com/rust-lang/rustlings), but for C.

Every exercise is a short C program with something wrong or missing in it.
You fix it so that it **compiles without warnings** and **prints exactly the
expected output**. Clings watches the file and re-checks it every time you
save.

## Requirements

- A C compiler: `gcc` or `clang` (set `CC` to use a specific one).
- Rust and Cargo to build Clings itself.

## Installation

```
cargo install --path .
```
```
imlazy install
```


## Getting started

```
clings init     # creates a clings/ directory with all exercises
cd clings
clings          # start the interactive watch mode
```
```
imlazy init
imlazy run
```


Watch mode shows the current exercise and re-checks it whenever you save the
file. Inside watch mode:

| Key | Action                          |
| --- | ------------------------------- |
| `n` | Move on to the next exercise    |
| `h` | Show a hint                     |
| `l` | List all exercises              |
| `c` | Check every exercise            |
| `r` | Re-run the current exercise     |
| `q` | Quit (progress is saved)        |

Other commands:

```
clings run [name]      # compile and run one exercise
clings hint [name]     # show a hint
clings list            # list all exercises with their status
clings reset [name]    # restore an exercise to its original state
clings reset --all     # restore every exercise and erase all progress (asks first; -y skips)
clings check-all       # check every exercise
```

Global flags:

- `--manual-run`: don't watch files; press `r` to re-check.
- `--edit-cmd "<cmd>"`: open the exercise with `<cmd> <path>` whenever it
  becomes current, e.g. `--edit-cmd "code -g"`. Also read from the
  `CLINGS_EDIT_CMD` environment variable.
- `--no-editor`: never open an editor.

Watch mode clears the terminal before every check so the latest result is
always at the top. Set `CLINGS_NO_CLEAR=1` to keep the scrollback instead;
`NO_COLOR=1` disables colours.

Progress is saved in `.clings-state.txt` in the exercise directory.

> **Developing Clings?** Do not solve exercises inside this source tree.
> `cargo build` embeds whatever is in `exercises/` as the pristine templates
> used by `clings init` and `clings reset`, so solved files would leak into
> them. Run `clings init` somewhere else and work there. `clings dev check`
> fails if an exercise in the tree already passes.

## How an exercise is checked

1. The file is compiled with `<CC> -std=<std> -Wall -Wextra <required_flags>`.
   A compile error **or any warning** fails the exercise.
2. The binary is run (with a 10 second timeout, no stdin). Its stdout must
   match `expected_stdout` from `info.toml` (trailing whitespace is ignored)
   and its exit code must match `expected_exit` (default 0).

There is no unit-test harness: exercises are purely output-based, which keeps
them simple and works the same with every compiler.

## Topics

| Directory          | Exercises                                        |
| ------------------ | ------------------------------------------------ |
| `00_intro`         | first compile error, printf and newlines         |
| `01_variables`     | declarations, `const`, choosing a type           |
| `02_types`         | integer division, chars, ranges, `bool`          |
| `03_control_flow`  | `=` vs `==`, off-by-one, `break`/`continue`, `switch` |
| `04_functions`     | prototypes, return values, pass by value, recursion |
| `05_arrays`        | bounds, `sizeof`, 2D arrays                      |
| `06_pointers`      | `&` and `*`, swap, pointer arithmetic, `NULL`    |
| `07_strings`       | `strlen`, `strcmp`, reversing, comparisons       |
| `08_structs`       | members, `->`, arrays of structs                 |
| `09_enums`         | enums with `switch`, counting values             |
| `10_memory`        | `malloc`/`free`, `realloc`, dangling pointers    |
| `11_macros`        | parenthesizing macro arguments                   |

## Writing exercises

Exercises live in `exercises/<topic>/<name>.c` with a reference solution in
`solutions/<topic>/<name>.c`, and are listed in `info.toml`:

```toml
[[exercises]]
name = "intro1"
dir = "00_intro"
description = "Your first compile error."
hint = """
Every C statement ends with a semicolon."""
expected_stdout = """
Hello, Clings!
"""
# optional: std = "c99", required_flags = ["-lm"], expected_exit = 1,
#           skip_check_unsolved = true
```

From the repository root:

```
clings dev new <name> --dir <topic>   # scaffold files and an info.toml entry
clings dev check                      # every solution passes, every unsolved
                                      # exercise fails, no stray files
cargo build                           # re-embed the files into the binary
```

All exercise files and `info.toml` are embedded into the binary at build time
(see `build.rs`), so `clings init` works without cloning this repository.

## Development

```
cargo test
cargo clippy --all-targets -- -D warnings
CC=gcc   cargo run -- dev check
CC=clang cargo run -- dev check
```
