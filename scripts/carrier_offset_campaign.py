#!/usr/bin/env python3
"""Measure residual carrier frequency offset tolerance without receiver changes."""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import gzip
import hashlib
import io
import json
from pathlib import Path
import platform
import subprocess
import sys
import tarfile
import time
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from catalog import Case
from disturbed import campaign
from run import canonical, execute, revision, source_digest

SEEDS = (7446529, 7446530, 7446531)
BASE_CASE = "E2_disturbed_24000_qpsk_bch_high_lat_quiet_combined"
REQUIRED_MAGNITUDES = (0, 0.5, 1, 2, 5, 10, 20)


def snapshot(directory, commit, digest):
    files = [ROOT / "CMakeLists.txt"]
    for name in ("src", "include", "proto", "tests", "cmake", "examples", "scripts", "config"):
        files.extend(p for p in sorted((ROOT / name).rglob("*")) if p.is_file()
                     and "__pycache__" not in p.parts and p.suffix != ".pyc")
    output = io.BytesIO()
    with gzip.GzipFile(filename="", mode="wb", fileobj=output, mtime=0) as compressed:
        with tarfile.open(fileobj=compressed, mode="w") as archive:
            for path in files:
                value = path.read_bytes()
                info = tarfile.TarInfo(str(path.relative_to(ROOT)))
                info.size = len(value)
                info.mode = 0o644
                archive.addfile(info, io.BytesIO(value))
    archive = output.getvalue()
    (directory / "source-snapshot.tar.gz").write_bytes(archive)
    source = dict(git_commit=commit, source_tree_sha256=digest,
                  archive_sha256=hashlib.sha256(archive).hexdigest(),
                  files={str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in files})
    (directory / "SOURCE.json").write_text(json.dumps(source, indent=2, sort_keys=True) + "\n")


def make_case(template, offset_hz, seed):
    parameters = template.parameters | dict(seed=seed, residual_offset_hz=offset_hz,
        residual_drift_hz_per_second=0.0, carrier_correction=0, campaign="carrier_offset")
    return Case(f"E2_carrier_offset_24000_qpsk_bch_quiet_{offset_hz:g}Hz", "E2", "characterize", "full",
                parameters, checks=("no_corrupt_messages", "no_duplicates"), notes=[
                    "Constant carrier frequency offset at channel output; zero drift and zero mean per-path Doppler shift.",
                    "High-latitude quiet: 1 ms delay spread, 0.5 Hz Doppler spread (2-sigma Gaussian spectrum per tap).",
                    "24 kHz QPSK+BCH, corrected 30 dB reference, combined recovery profile, 300 seconds per seed.",
                    "Carrier correction disabled; no receiver frequency tracker added.",
                    "Paired-seed delivery criterion: absolute change <= 0.1 percentage points for every seed and both signs."])


def measure(c, args):
    path = args.results / c.name / f"{c.parameters['seed']}.json"
    if path.exists():
        record = json.loads(path.read_text())
        if record["parameters"]["source_tree_sha256"] != args.source_digest:
            raise ValueError(f"Existing run belongs to a different source snapshot: {path}")
    else:
        record = execute(c, args, {})
        if record["status"] in ("error", "fail", "xpass"):
            raise ValueError(f"{c.name}: {record.get('reason', record['assertions'])}")
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(canonical(record))
    if c.parameters["residual_offset_hz"] == 0:
        historical = ROOT / "results/disturbed-recovery/polar" / BASE_CASE / path.name
        before = json.loads(historical.read_text())
        if record["metrics"] != before["metrics"] or record["observations"] != before["observations"]:
            raise ValueError(f"Zero-offset control differs from published observations: {historical}")
    return record


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, default=ROOT / "build/goblin_cannon_simulated_channel_probe")
    parser.add_argument("--results", type=Path, default=ROOT / "results/carrier-offset")
    parser.add_argument("--git-commit")
    parser.add_argument("--jobs", type=int, default=4)
    args = parser.parse_args()
    args.git_commit = args.git_commit or revision()
    args.source_digest = source_digest()
    args.results.mkdir(parents=True, exist_ok=True)
    template = next(c for c in campaign() if c.name == BASE_CASE)
    assert template.parameters["duration_s"] == 300 and template.parameters["carrier_correction"] == 0
    snapshot(args.results, args.git_commit, args.source_digest)
    started = time.monotonic()
    baseline = None
    magnitudes = list(REQUIRED_MAGNITUDES)
    completed = []
    index = 0
    while index < len(magnitudes):
        magnitude = magnitudes[index]
        offsets = [0] if magnitude == 0 else [magnitude, -magnitude]
        cases = [make_case(template, offset, seed) for offset in offsets for seed in SEEDS]
        records = []
        with ThreadPoolExecutor(max_workers=args.jobs) as executor:
            for future in as_completed([executor.submit(measure, c, args) for c in cases]):
                records.append(future.result())
        means = []
        for offset in offsets:
            runs = [r for r in records if r["parameters"]["residual_offset_hz"] == offset]
            delivery = sum(r["metrics"]["message_delivery_fraction_of_framed"] for r in runs) / len(runs)
            goodput = sum(r["metrics"]["fresh_goodput_bps"] for r in runs) / len(runs)
            means.append(delivery)
            print(f"Carrier frequency offset {offset:+g} Hz: mean delivery {100*delivery:.6f}%; fresh goodput {goodput:.6f} bit/s", flush=True)
        completed.extend(offsets)
        if magnitude == 0:
            baseline = means[0]
            if not baseline:
                raise ValueError("Quiet-preset baseline has no delivery")
        if magnitude >= REQUIRED_MAGNITUDES[-1]:
            if max(means) <= baseline * .01:
                break
            magnitudes.append(magnitude * 2)
        index += 1
    metadata = dict(report_header="Simulated channel carrier frequency offset sweep", git_commit=args.git_commit,
        source_tree_sha256=args.source_digest, hostname=platform.node(), platform=platform.platform(),
        compiler=subprocess.check_output(["c++", "--version"], text=True),
        elapsed_seconds=time.monotonic()-started, offsets_hz=completed, seeds=list(SEEDS), duration_s=300,
        base_case=BASE_CASE, paired_delivery_tolerance_percentage_points=.1,
        collapse_criterion="Both signs' mean delivery <= 1% of zero-offset mean delivery; all required offsets measured first.",
        zero_offset_matches_published_observations=True)
    (args.results / "EXECUTION.json").write_text(json.dumps(metadata, indent=2, sort_keys=True) + "\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
