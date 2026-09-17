#!/usr/bin/env python3
"""Run the declared AEAD simulated channel selections without changing durations."""
import argparse
import json
import platform
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from catalog import matrix, REFINEMENT_CODING


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("stage", choices=("security", "latency", "polar"))
    parser.add_argument("--git-commit", required=True)
    parser.add_argument("--source-digest", required=True)
    args = parser.parse_args()
    root = ROOT / "results/aead"
    root.mkdir(parents=True, exist_ok=True)
    base = [sys.executable, str(ROOT / "tests/simulated_channel/run.py"),
            "--git-commit", args.git_commit, "--source-digest", args.source_digest]
    cases = matrix()
    selections = []
    if args.stage == "security":
        names = {"A4_10000_64qam_offset_5", "A4_10000_64qam_drift_10min", "D3_auction_flood",
                 "B1_10000_64qam_-20dB_1_100", "B1_10000_64qam_-20dB_10_100",
                 "B1_24000_64qam_-20dB_1_100", "B1_24000_64qam_20dB_10_100",
                 "B1_24000_64qam_20dB_10_1000", "C4_generated_messages"}
        for tier in ("quick", "full"):
            selected = [c.name for c in cases if c.tier == tier and
                        (c.name in names or c.group in ("A8", "D6", "D4", "B4", "E1"))]
            selections.append((tier, "recovery", root, selected, ["--jobs", "2"]))
    elif args.stage == "latency":
        for profile, directory in (("legacy", "brief-latency"), ("recovery", "naamah-latency")):
            target = root / directory
            target.mkdir(parents=True, exist_ok=True)
            host = dict(report_header="simulated channel quiet-host provenance", hostname=platform.node(),
                        platform=platform.platform(), git_commit=args.git_commit, source_tree_sha256=args.source_digest,
                        openssl=subprocess.check_output(["openssl", "version", "-a"], text=True),
                        compiler=subprocess.check_output(["c++", "--version"], text=True),
                        cpu_flags=next((line for line in Path("/proc/cpuinfo").read_text().splitlines() if line.startswith("flags")), ""))
            (target / "HOST.json").write_text(json.dumps(host, indent=2) + "\n")
            for tier in ("quick", "full"):
                selected = [c.name for c in cases if c.group == "B5" and c.tier == tier and
                            c.parameters.get("campaign", "matrix") == "matrix"]
                selections.append((tier, profile, target, selected, ["--jobs", "1", "--allow-non-avx512"]))
    else:
        # All six ordinary BPSK/QPSK/8-PSK coding configurations; identical
        # declared three-seed 300/300/100 s traces and 10 s RF screens.
        for campaign in ("refinement_quick", "refinement_screen", "refinement_followup"):
            selected = [c.name for c in cases if c.parameters.get("campaign") == campaign and
                        c.parameters.get("refinement_variant") in REFINEMENT_CODING]
            selections.append(("quick" if campaign.endswith("quick") else "full", "recovery", root / "polar",
                               selected, ["--jobs", "2", "--seeds", "7446529", "7446530", "7446531"]))
    failures = []
    for tier, profile, target, selected, extra in selections:
        if not selected:
            raise RuntimeError("empty validation selection")
        command = base + ["--tier", tier, "--profile", profile, "--results", str(target)] + extra
        for name in selected:
            command += ["--case", name]
        result = subprocess.run(command, cwd=ROOT)
        if result.returncode:
            failures.append(dict(tier=tier, profile=profile, results=str(target.relative_to(ROOT)), code=result.returncode))
    if failures:
        print(json.dumps({"report_header": "simulated channel failed selections", "failures": failures}), flush=True)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
