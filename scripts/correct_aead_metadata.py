#!/usr/bin/env python3
"""Correct stale descriptive labels without relabeling measurements as a new run."""
import csv
import hashlib
import json
from pathlib import Path
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/aead"
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from run import canonical, source_digest

REPLACEMENTS = {
    'coding_stage_order=["FEC","AES-CTR",': 'coding_stage_order=["AES-256-GCM (production messages only)","FEC",',
    'Viterbi hard decisions checked by existing message CRC': 'Viterbi hard decisions; production message integrity checked by AES-256-GCM',
    'row=3 MSB-first cipher bits;': 'row=3 MSB-first FEC-coded bits;',
}


def read(path):
    return json.loads(path.read_text())


def verify_measured_source():
    """Accept exactly the three descriptive edits, with every other tested file identical."""
    manifest = read(DIRECTORY / "SOURCE.json")
    archive = DIRECTORY / "source-snapshot.tar.gz"
    assert hashlib.sha256(archive.read_bytes()).hexdigest() == manifest["archive_sha256"]
    measured_digest = hashlib.sha256()
    checked = 0
    with tarfile.open(archive) as snapshot:
        for directory in ("src", "include", "proto", "tests", "cmake"):
            for path in sorted((ROOT / directory).rglob("*")):
                if (not path.is_file() or "__pycache__" in path.parts or path.suffix in (".pyc", ".md")
                        or path.name == "expected_failures.json"):
                    continue
                name = str(path.relative_to(ROOT))
                original = snapshot.extractfile(name).read()
                assert hashlib.sha256(original).hexdigest() == manifest["files"][name]
                expected = original
                if name == "tests/simulated_channel/catalog.py":
                    for old, new in REPLACEMENTS.items():
                        assert expected.count(old.encode()) == 1
                        expected = expected.replace(old.encode(), new.encode())
                assert path.read_bytes() == expected, f"Non-metadata source change: {name}"
                measured_digest.update(name.encode() + b"\0" + original)
                checked += 1
        cmake = snapshot.extractfile("CMakeLists.txt").read()
        assert cmake == (ROOT / "CMakeLists.txt").read_bytes()
        measured_digest.update(cmake)
    assert measured_digest.hexdigest() == manifest["source_tree_sha256"]
    return manifest["source_tree_sha256"], checked


def correct_parameters(value):
    if not isinstance(value, dict):
        return
    params = value.get("parameters")
    if params and "coding_stage_order" in params:
        order = params["coding_stage_order"]
        if order[:2] == ["FEC", "AES-CTR"]:
            params["coding_stage_order"] = ["AES-256-GCM (production messages only)", "FEC"] + order[2:]
        soft = params.get("soft_metric_parameters", {})
        if soft.get("decoder_output") in REPLACEMENTS:
            soft["decoder_output"] = REPLACEMENTS[soft["decoder_output"]]
        params["walsh_mapping"] = params["walsh_mapping"].replace("MSB-first cipher bits", "MSB-first FEC-coded bits")
    if "latency_reference" in value:
        correct_parameters(value["latency_reference"])


def main():
    if (DIRECTORY / "METADATA_CORRECTION.json").exists():
        raise SystemExit("Correction audit already exists; preserve its original record hashes.")
    measured, checked = verify_measured_source()
    corrected_source = source_digest()
    corrections = []
    for directory in (DIRECTORY, DIRECTORY / "polar", DIRECTORY / "brief-latency", DIRECTORY / "naamah-latency"):
        for path in sorted(directory.glob("*/[0-9]*.json")):
            original = read(path)
            assert original["parameters"]["source_tree_sha256"] == measured
            corrected = json.loads(canonical(original))
            correct_parameters(corrected)
            # This correction cannot change evidence, statuses, thresholds or seeds.
            for key in original.keys() - {"parameters", "latency_reference", "metadata_correction"}:
                assert original[key] == corrected[key]
            corrected["metadata_correction"] = dict(
                fields=["coding_stage_order", "soft_metric_parameters.decoder_output", "walsh_mapping"],
                measured_source_tree_sha256=measured, metadata_source_tree_sha256=corrected_source,
                reason="Correct stale CTR/CRC and Walsh descriptions; tested C++ and all observations/metrics are unchanged.")
            before = hashlib.sha256(path.read_bytes()).hexdigest()
            path.write_text(canonical(corrected))
            corrections.append(dict(path=str(path.relative_to(DIRECTORY)), original_sha256=before,
                                    corrected_sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
        # Rebuild CSV views from the corrected canonical JSON, preserving CSV formatting.
        for path in directory.glob("*.csv"):
            with path.open(newline="") as stream:
                reader = csv.DictReader(stream); fields = reader.fieldnames; rows = list(reader)
            for row in rows:
                record = read(directory / row["simulated_channel_case"] / (row["seed"] + ".json"))
                row["parameters_json"] = json.dumps(record["parameters"], sort_keys=True)
            with path.open("w", newline="") as stream:
                writer = csv.DictWriter(stream, fieldnames=fields); writer.writeheader(); writer.writerows(rows)
    audit = dict(report_header="simulated channel parameter-description correction", measured_source_tree_sha256=measured,
        metadata_source_tree_sha256=corrected_source, checked_source_files=checked + 1,
        allowed_catalog_replacements=REPLACEMENTS, unchanged="All compiled source, simulation controls, observations, metrics, assertions, thresholds and measured source identities.",
        records=corrections)
    (DIRECTORY / "METADATA_CORRECTION.json").write_text(json.dumps(audit, indent=2, sort_keys=True) + "\n")
    print(f"Corrected descriptions in {len(corrections)} result records; measurements retain source {measured}.")


if __name__ == "__main__":
    main()
