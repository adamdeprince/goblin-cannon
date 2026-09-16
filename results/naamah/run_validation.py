#!/usr/bin/env python3
"""Repeat the existing simulated channel B5 cases serially on a quiet host."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import subprocess
import sys
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--git-commit", required=True)
    parser.add_argument("--source-digest", required=True)
    args = parser.parse_args()
    repo = args.repo.resolve()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(repo / "tests/simulated_channel"))
    from run import source_digest
    actual_digest = source_digest()
    if actual_digest != args.source_digest:
        raise SystemExit(f"Source digest mismatch: {actual_digest}")

    def command_text(command):
        return subprocess.check_output(command, cwd=repo, text=True).strip()

    def snapshot():
        return dict(unix_time=time.time(), load_average=os.getloadavg(),
                    proc_stat=Path("/proc/stat").read_text())

    metadata = dict(
        report_header="simulated channel naamah validation environment",
        hostname=platform.node(), platform=platform.platform(),
        python=sys.version, lscpu=command_text(["lscpu"]),
        compiler=command_text(["/usr/local/bin/g++", "--version"]),
        libraries=command_text(["pkg-config", "--modversion", "grpc++", "protobuf", "openssl"]),
        git_commit=args.git_commit, source_tree_sha256=actual_digest,
        cpu_affinity=sorted(os.sched_getaffinity(0)),
        scheduling_policy=os.sched_getscheduler(0), nice=os.getpriority(os.PRIO_PROCESS, 0),
        cmake_cache=(repo / "build/CMakeCache.txt").read_text(),
        protocol="Existing B5 cases, three repeats, identical seeds, one worker, no other validation jobs in parallel; default OS scheduling; startup retained.",
        steps=[],
    )
    meta_path = output / "VALIDATION.host.json"

    def persist():
        meta_path.write_text(json.dumps(metadata, indent=2, sort_keys=True) + "\n")

    def run(name, command):
        print(f"simulated channel: starting {name}", flush=True)
        before = snapshot()
        start = time.monotonic()
        with (output / f"{name}.log").open("w") as log:
            result = subprocess.run(command, cwd=repo, stdout=log, stderr=subprocess.STDOUT)
        step = dict(name=name, command=command, returncode=result.returncode,
                    elapsed_seconds=time.monotonic()-start, before=before, after=snapshot())
        metadata["steps"].append(step)
        persist()
        print(f"simulated channel: finished {name}: exit={result.returncode}, seconds={step['elapsed_seconds']:.3f}", flush=True)
        return result.returncode

    persist()
    if run("ctest", ["ctest", "--test-dir", str(repo / "build"), "--output-on-failure", "-j", "4"]):
        return 1
    codes = []
    for repeat in range(1, 4):
        destination = output / f"repeat-{repeat}"
        codes.append(run(f"repeat-{repeat}", [
            sys.executable, str(repo / "tests/simulated_channel/run.py"),
            "--tier", "quick", "--group", "B5", "--jobs", "1", "--allow-non-avx512",
            "--probe", str(repo / "build/goblin_cannon_simulated_channel_probe"),
            "--results", str(destination), "--git-commit", args.git_commit,
            "--source-digest", actual_digest,
        ]))
        for path in sorted(destination.glob("B5*/*.host.json")):
            record = json.loads(path.read_text())
            print(json.dumps(dict(report_header="simulated channel latency observation",
                                  repeat=repeat, case=path.parent.name,
                                  percentiles_ms=record["observations"]["host_latency_ms_percentiles"])), flush=True)
    identical = {}
    for path in sorted((output / "repeat-1").glob("B5*/[0-9]*.json")):
        if path.name.endswith(".host.json"):
            continue
        relative = path.relative_to(output / "repeat-1")
        hashes = [hashlib.sha256((output / f"repeat-{i}" / relative).read_bytes()).hexdigest() for i in range(1, 4)]
        identical[str(relative)] = dict(sha256_by_repeat=hashes, identical=len(set(hashes)) == 1)
    metadata["canonical_repeat_check"] = identical
    metadata["complete"] = True
    metadata["returncode"] = int(any(codes) or len(identical) != 6 or not all(r["identical"] for r in identical.values()))
    persist()
    return metadata["returncode"]


if __name__ == "__main__":
    raise SystemExit(main())
