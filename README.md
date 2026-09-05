# Clings 🔗

Exercises that take you from your first compile error to writing real C. It
is [rustlings](https://github.com/rust-lang/rustlings), but for C.

There are 114 exercises in 18 topics, and three kinds of them:

- **Fix:** a short program with a bug or a gap. Repair it.
- **Write:** a specification and a test harness. You write the code.
- **Project:** a larger program that combines several topics (a word
  counter, a string builder, an RPN calculator, a tiny database).

Every exercise must **compile without warnings** and **print exactly the
expected output**. The compiler runs with AddressSanitizer and
UndefinedBehaviorSanitizer, so out-of-bounds accesses, use-after-free,
leaks, signed overflow and bad shifts fail loudly instead of hiding.

Each exercise file starts with a long comment: what the concept is, when
real programs use it, the pitfalls, and the task. The topics:

| Topic                    | Covers                                                        |
| ------------------------ | ------------------------------------------------------------- |
| `00_intro`               | compile errors, printf and format specifiers                  |
| `01_variables`           | declarations, const, types, scope and shadowing               |
| `02_types`               | integer division, chars, ranges, bool, signed/unsigned, stdint, floating point |
| `03_control_flow`        | if, loops, switch and fallthrough, do-while, ternary, goto cleanup |
| `04_functions`           | prototypes, by-value, recursion, static locals, return types  |
| `05_arrays`              | bounds, sizeof, 2D arrays, decay, in-place algorithms, binary search |
| `06_pointers`            | address/deref, swap, arithmetic, NULL, out-params, ranges, const, `**`, dangling |
| `07_strings`             | terminators, strcmp, literals vs arrays, implementing string.h, overflow, strtol, ctype |
| `08_structs`             | members, `->`, arrays of structs, by-value vs pointer, typedef, nesting, unions, padding |
| `09_enums`               | enums, count sentinels, state machines                        |
| `10_bits`                | bitwise ops, flags, packing, undefined shifts, bit tricks     |
| `11_memory`              | malloc/free, realloc, lifetimes, use-after-free, leaks, calloc, ownership, sizing |
| `12_function_pointers`   | syntax, qsort comparators, map/reduce, dispatch tables, callbacks with context |
| `13_data_structures`     | linked lists, stack, ring buffer, binary search tree, hash map |
| `14_preprocessor`        | macros, stringify, include guards, headers, static/extern linkage, `-D` flags |
| `15_io`                  | argv, stderr and exit codes, fgets, scanf pitfalls, files, errno |
| `16_undefined_behavior`  | uninitialized reads, overflow, sequence points, alignment, a bug tour |
| `17_projects`            | four capstone programs                                        |

## Requirements

- A C compiler: `gcc` or `clang` (set `CC` to use a specific one). The
  sanitizers need the compiler's runtime libraries (`libasan`, `libubsan`);
  if they are missing, Clings says so once and checks by output only.
- Rust and Cargo to build Clings itself.

## Installation

```
cargo install --path .
```

## Getting started

```
clings init     # creates a clings/ directory with all exercises
cd clings
clings          # start the interactive watch mode
```

Watch mode shows the current exercise and re-checks it whenever you save the
file (or a header next to it). Inside watch mode:

| Key | Action                                       |
| --- | -------------------------------------------- |
| `n` | Move on to the next exercise                 |
| `h` | Show a hint                                  |
| `l` | List all exercises                           |
| `c` | Check every exercise                         |
| `r` | Re-run the current exercise                  |
| `x` | Reset the current exercise (asks first)      |
| `q` | Quit (progress is saved)                     |

Other commands:

```
clings run [name]          # compile and run one exercise
clings hint [name]         # show a hint
clings list                # list all exercises with their status
clings check-all           # check every exercise
```

### Redoing exercises

If a concept did not stick, reset it and do it again:

```
clings reset                    # the current exercise: original file, marked pending
clings reset pointers2          # one exercise by name
clings reset 06_pointers        # every exercise of a topic (asks first)
clings reset --all              # everything (asks first; -y skips the question)
clings reset 06_pointers --keep-file   # forget progress but keep your files
```

After a reset the first reset exercise becomes the current one, so `clings`
picks it up right away. `--keep-file` (alias `--progress-only`) is useful
when you want to redo a topic while keeping your old answers around to
compare against.

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

## Developing Clings

Do not solve exercises inside this source tree. `cargo build` embeds
whatever is in `exercises/` as the pristine templates used by `clings init`
and `clings reset`, so solved files would leak into them. Run `clings init`
somewhere else and work there. `clings dev check` fails if an exercise in
the tree already passes.

`info.toml` is generated. To add or change an exercise:

1. Write `exercises/<dir>/<name>.c` (with a `CONCEPT` / `WHEN YOU USE THIS`
   / `TASK` / `EXPECTED OUTPUT` header) and `solutions/<dir>/<name>.c`.
2. Add an `ex(...)` entry to `tools/meta.py`: description (starting with
   `Fix:`, `Write:` or `Project:`), hint, and optionally `args`, `stdin`,
   `extra_sources`, `required_flags`, `expected_exit`.
3. Run `python3 tools/gen_info.py`. It compiles every solution, runs it,
   checks the header's expected output against the real output, and writes
   `info.toml`.
4. Run `cargo run -- dev check` to verify every solution passes and every
   unsolved exercise fails, with both `CC=gcc` and `CC=clang` if you can.

Multi-file exercises list their support files in `extra_sources`; `.c`
files are compiled and linked with the exercise, `.h` files are restored by
`clings reset`. A solution can ship its own copy of a header next to it
when the fix lives in the header.
