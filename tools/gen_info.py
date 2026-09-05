#!/usr/bin/env python3
"""Builds info.toml from tools/meta.py and the reference solutions.

Run from the repository root:

    python3 tools/gen_info.py            # uses gcc, or $CC

For every exercise in META it compiles solutions/<dir>/<name>.c (plus the
.c support files), runs it with the exercise's args/stdin, checks the exit
code, checks that the EXPECTED OUTPUT block in the exercise header matches
the real output, and writes the [[exercises]] entry with expected_stdout
taken from the run. Nothing is written if any check fails.

To add an exercise: write exercises/<dir>/<name>.c and
solutions/<dir>/<name>.c, add an ex(...) line to tools/meta.py in the right
place, run this script, then `cargo run -- dev check`.
"""
import os, re, subprocess, sys, tempfile
sys.path.insert(0, os.path.dirname(__file__))
from meta import META, HEADER, WELCOME, FINAL

CC = os.environ.get("CC", "gcc")
FLAGS = ["-std=c17", "-Wall", "-Wextra", "-g", "-fsanitize=address,undefined", "-fno-sanitize-recover=undefined"]

def toml_str(s):
    if "\n" in s:
        s = s.replace("\\", "\\\\").replace('"""', '\\"""')
        return '"""\n' + s + ('' if s.endswith("\n") else "\n") + '"""'
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'

def header_expected(path):
    lines = open(path).read().splitlines()
    out = []
    i = 0
    while i < len(lines) and not lines[i].startswith("// EXPECTED OUTPUT"):
        i += 1
    if i == len(lines):
        return None
    i += 1
    while i < len(lines) and lines[i].startswith("//"):
        body = lines[i][2:]
        if body.startswith("     "):
            out.append(body[5:].rstrip())
        elif body.strip() == "":
            out.append("")
        else:
            break
        i += 1
    while out and out[-1] == "":
        out.pop()
    return out

problems = 0
entries = []
for m in META:
    name, d = m["name"], m["dir"]
    ex = f"exercises/{d}/{name}.c"
    sol = f"solutions/{d}/{name}.c"
    extras = [f"exercises/{d}/{e}" for e in m.get("extra_sources", []) if e.endswith(".c")]
    for f in [ex, sol] + extras:
        if not os.path.isfile(f):
            print(f"MISSING {f}"); problems += 1
    if problems:
        continue
    with tempfile.TemporaryDirectory() as td:
        binp = os.path.join(td, name)
        std = m.get("std")
        flags = list(FLAGS)
        if std:
            flags[0] = "-std=" + std
        flags += m.get("required_flags", [])
        r = subprocess.run([CC, "-o", binp, sol] + extras + flags, capture_output=True, text=True)
        if r.returncode != 0 or "warning:" in r.stderr:
            print(f"COMPILE {sol}:\n{r.stderr}"); problems += 1; continue
        try:
            p = subprocess.run([binp] + m.get("args", []), input=m.get("stdin", ""), capture_output=True, text=True, timeout=10)
        except subprocess.TimeoutExpired:
            print(f"TIMEOUT {sol}"); problems += 1; continue
        if p.returncode != m.get("expected_exit", 0):
            print(f"EXIT {sol}: got {p.returncode}\n{p.stderr[:800]}"); problems += 1; continue
        if "Sanitizer" in p.stderr or "runtime error:" in p.stderr:
            print(f"SANITIZER {sol}:\n{p.stderr[:800]}"); problems += 1; continue
        actual = [l.rstrip() for l in p.stdout.splitlines()]
        while actual and actual[-1] == "":
            actual.pop()
        exp = header_expected(ex)
        if exp is None:
            print(f"NO EXPECTED OUTPUT BLOCK in {ex}"); problems += 1
        elif exp != actual:
            print(f"HEADER MISMATCH {ex}\n  header: {exp}\n  actual: {actual}"); problems += 1
        if not m.get("hint", "").strip():
            print(f"NO HINT {name}"); problems += 1
    e = ["[[exercises]]", f'name = "{name}"', f'dir = "{d}"', f'description = {toml_str(m["description"])}']
    e.append("hint = " + toml_str(m["hint"].strip()))
    if m.get("std"): e.append(f'std = "{m["std"]}"')
    if m.get("args"): e.append("args = [" + ", ".join(toml_str(a) for a in m["args"]) + "]")
    if m.get("stdin"): e.append("stdin = " + toml_str(m["stdin"]))
    if m.get("extra_sources"): e.append("extra_sources = [" + ", ".join(toml_str(a) for a in m["extra_sources"]) + "]")
    if m.get("required_flags"): e.append("required_flags = [" + ", ".join(toml_str(a) for a in m["required_flags"]) + "]")
    if m.get("expected_exit"): e.append(f'expected_exit = {m["expected_exit"]}')
    if m.get("skip_check_unsolved"): e.append("skip_check_unsolved = true")
    e.append("expected_stdout = " + toml_str(p.stdout if p.stdout.strip() else ""))
    entries.append("\n".join(e))

if problems:
    print(f"\n{problems} problem(s); info.toml NOT written")
    sys.exit(1)

out = [HEADER, "welcome_message = " + toml_str(WELCOME), "", "final_message = " + toml_str(FINAL), ""]
cur = None
for m, e in zip(META, entries):
    if m["dir"] != cur:
        cur = m["dir"]
        out.append("# " + "-" * 75 + f"\n# {cur}\n# " + "-" * 75 + "\n")
    out.append(e + "\n")
open("info.toml", "w").write("\n".join(out))
print(f"wrote info.toml with {len(entries)} exercises")
