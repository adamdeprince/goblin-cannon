"""Verify saved measurement source independently of later documentation edits."""
import hashlib
import json
from pathlib import Path
import tarfile


def verify_snapshot(directory):
    directory = Path(directory)
    source = json.loads((directory / "SOURCE.json").read_text())
    archive_path = directory / "source-snapshot.tar.gz"
    if hashlib.sha256(archive_path.read_bytes()).hexdigest() != source["archive_sha256"]:
        raise ValueError(f"Measurement archive changed: {archive_path}")
    with tarfile.open(archive_path) as archive:
        contents = {member.name: archive.extractfile(member).read()
                    for member in archive.getmembers() if member.isfile()}
    actual = {name: hashlib.sha256(value).hexdigest() for name, value in contents.items()}
    if actual != source["files"]:
        raise ValueError(f"Measurement source manifest mismatch: {directory}")
    digest = hashlib.sha256()
    for directory_name in ("src", "include", "proto", "tests", "cmake"):
        for name in sorted(contents, key=Path):
            path = Path(name)
            if path.parts[0] != directory_name or "__pycache__" in path.parts:
                continue
            if path.suffix in (".pyc", ".md") or path.name == "expected_failures.json":
                continue
            digest.update(name.encode() + b"\0" + contents[name])
    digest.update(contents["CMakeLists.txt"])
    if digest.hexdigest() != source["source_tree_sha256"]:
        raise ValueError(f"Measurement source digest mismatch: {directory}")
    return source
