#!/usr/bin/env python3

"""
./a.cpp -> "a"
./a/b.cpp -> "a_b"
./a/b/c.cpp -> "a_b_c"
"""

import json
from pathlib import Path
import sys

def rel_path_to_name(p: Path, cwd: Path) -> str:
    rel = p.relative_to(cwd)
    rel_no_ext = rel.with_suffix("")  # drop extension
    return "_".join(rel_no_ext.parts)

def read_file_text(path: Path) -> str:
    try:
        return path.read_text(encoding="utf-8")
    except Exception:
        try:
            return path.read_text(encoding="latin-1")
        except Exception as e:
            print(f"Warning: failed to read {path}: {e}", file=sys.stderr)
            return ""

def main():
    cwd = Path.cwd()
    cpp_files = sorted(cwd.rglob("*.cpp"))

    # avoid picking the output file if named snippets.code-snippets in cwd
    out_file = cwd / "snippets.code-snippets"
    cpp_files = [p for p in cpp_files if p.resolve() != out_file.resolve()]

    if not cpp_files:
        print("No .cpp files found in current directory or subdirectories.")
        return

    snippets = {}
    used_names = set()

    for p in cpp_files:
        text = read_file_text(p)
        if text is None:
            print(f"Skipping {p} (could not read).")
            continue

        base_name = rel_path_to_name(p, cwd)
        name = base_name
        # avoid collisions
        i = 1
        while name in used_names:
            name = f"{base_name}_{i}"
            i += 1
        used_names.add(name)

        # VS Code snippet body should be list-of-lines
        body_lines = text.splitlines()

        snippets[name] = {
            "prefix": name,
            "body": body_lines,
            "description": f"Generated from {str(p.relative_to(cwd))}",
            "scope": "cpp"
        }

    # write single snippets file
    try:
        with out_file.open("w", encoding="utf-8") as fh:
            json.dump(snippets, fh, ensure_ascii=False, indent=2)
        print(f"Wrote {out_file}")
        print(f"Snippets generated: {len(snippets)} (place in VS Code User Snippets or project .vscode/)")
    except Exception as e:
        print(f"Failed to write {out_file}: {e}", file=sys.stderr)

if __name__ == "__main__":
    main()

