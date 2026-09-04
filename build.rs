//! Embeds every file under `exercises/` and `solutions/` into the binary so
//! that `clings init` can populate a fresh directory without a git clone.

use std::{
    env, fs,
    path::{Path, PathBuf},
};

fn collect(dir: &Path, root: &Path, out: &mut Vec<(String, PathBuf)>) {
    let mut entries: Vec<PathBuf> = fs::read_dir(dir)
        .unwrap_or_else(|e| panic!("failed to read {}: {e}", dir.display()))
        .map(|e| e.unwrap().path())
        .collect();
    entries.sort();
    for path in entries {
        if path.is_dir() {
            collect(&path, root, out);
        } else {
            let rel = path
                .strip_prefix(root)
                .unwrap()
                .to_string_lossy()
                .replace('\\', "/");
            out.push((rel, path));
        }
    }
}

fn main() {
    let manifest = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let mut files = Vec::new();
    for dir in ["exercises", "solutions"] {
        let d = manifest.join(dir);
        println!("cargo:rerun-if-changed={}", d.display());
        collect(&d, &manifest, &mut files);
    }
    println!(
        "cargo:rerun-if-changed={}",
        manifest.join("info.toml").display()
    );

    let mut code = String::from("pub static EMBEDDED_FILES: &[EmbeddedFile] = &[\n");
    for (rel, abs) in &files {
        println!("cargo:rerun-if-changed={}", abs.display());
        code.push_str(&format!(
            "    EmbeddedFile {{ path: {rel:?}, content: include_str!({:?}) }},\n",
            abs.display().to_string()
        ));
    }
    code.push_str("];\n");

    let out = PathBuf::from(env::var("OUT_DIR").unwrap()).join("embedded_files.rs");
    fs::write(out, code).unwrap();
}
