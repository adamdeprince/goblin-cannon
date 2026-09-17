#!/usr/bin/env python3
"""Compare saved simulated channel B5 runs without altering measurements."""
from collections import Counter
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "results/recovery-improvements"
QUIET = BASELINE / "naamah-latency"


def read(path):
    return json.loads(path.read_text())


def normalized(value):
    # These are the only intentional cross-host provenance/dispatch differences.
    if isinstance(value, dict):
        return {k: normalized(v) for k, v in value.items()
                if k not in ("git_commit", "require_avx512", "demapper")}
    if isinstance(value, list):
        return [normalized(v) for v in value]
    return value


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(",", ":"), allow_nan=False)


def main():
    host = read(QUIET / "HOST.json")
    baseline_manifest = read(BASELINE / "VALIDATION.json")
    paths = sorted(QUIET.glob("B5_*/[0-9]*.json"))
    paths = [p for p in paths if not p.name.endswith(".host.json")]
    baseline_paths = {p.relative_to(BASELINE) for p in BASELINE.glob("B5_*/[0-9]*.json")
                      if not p.name.endswith(".host.json")}
    if {p.relative_to(QUIET) for p in paths} != baseline_paths or len(paths) != 12:
        raise ValueError("Expected the same twelve B5 case/seed pairs on both hosts")
    digest = hashlib.sha256()
    statuses, host_statuses = Counter(), Counter()
    comparisons, rows = [], []
    for path in paths:
        relative = path.relative_to(QUIET)
        record, baseline = read(path), read(BASELINE / relative)
        sidecar = path.with_name(f"{record['seed']}.host.json")
        timing = read(sidecar)
        old_timing = read((BASELINE / relative).with_name(sidecar.name))
        p = record["parameters"]
        if timing["parameters"] != p or normalized(p) != normalized(baseline["parameters"]):
            raise ValueError(f"Mismatched parameters: {relative}")
        if (p["git_commit"] != host["git_commit"] or p["source_tree_sha256"] != host["source_tree_sha256"]
                or p["source_tree_sha256"] != baseline_manifest["source_tree_sha256"]
                or p["require_avx512"] != 0 or record["observations"]["demapper"] != host["runtime_isa"]):
            raise ValueError(f"Mismatched source or ISA metadata: {relative}")
        for evidence in (path, sidecar):
            digest.update(str(evidence.relative_to(QUIET)).encode() + b"\0" + evidence.read_bytes())
        obs, old_obs = timing["observations"], old_timing["observations"]
        added = obs["host_added_software_latency_ms_percentiles"]
        old_added = old_obs["host_added_software_latency_ms_percentiles"]["p99_9"]
        state = obs["added_software_latency_assertion"]["status"]
        statuses[record["status"]] += 1
        host_statuses[state] += 1
        comparisons.append(dict(test_name=record["test_name"], seed=record["seed"],
            parameters_source=str(relative), host_source=str(sidecar.relative_to(QUIET)),
            baseline_source=str(Path("..") / relative),
            canonical_equal_excluding_revision_and_isa=canonical(normalized(record)) == canonical(normalized(baseline)),
            metrics_identical=canonical(record["metrics"]) == canonical(baseline["metrics"]),
            added_p99_9_ms=added["p99_9"], baseline_added_p99_9_ms=old_added,
            difference_ms=added["p99_9"] - old_added, host_status=state))
        label = f"{p['bandwidth_hz']//1000} kHz / {p['modulation']} / " + ("long" if "polar_span" in record["test_name"] else "short")
        values = [added[k] for k in ("p50", "p99", "p99_9", "max")]
        values += [obs["host_latency_ms_percentiles"]["p99_9"],
                   record["latency_reference"]["metrics"]["latency_ms"]["p99_9"], old_added]
        rows.append(f"| [{label}]({sidecar.relative_to(QUIET)}) | " + " | ".join(f"{v:.3f}" for v in values) + f" | {state} |")
    runtime = {e["tier"]: e["elapsed_seconds"] for e in
               (read(p) for p in QUIET.glob("EXECUTION-*-selection-*.json"))}
    manifest = dict(report_header="simulated channel recovery quiet-host validation", campaign_status="complete",
        host=host["hostname"], runtime_isa=host["runtime_isa"], git_commit=host["git_commit"],
        source_tree_sha256=host["source_tree_sha256"], cases=len(paths), statuses=dict(statuses),
        host_statuses=dict(host_statuses), jobs=host["worker_count"], seeds=sorted({c["seed"] for c in comparisons}),
        ctest_passed=host["ctest_passed"], ctest_total=host["ctest_total"], ctest_wall_seconds=host["ctest_wall_seconds"],
        selected_tier_runtime_seconds=runtime, evidence_sha256=digest.hexdigest(),
        evidence_hash_definition="Sorted canonical result paths, followed by their host sidecars: relative UTF-8 path, NUL, exact file bytes.",
        canonical_comparison_exclusions=["git_commit", "require_avx512", "demapper"], comparisons=comparisons)
    (QUIET / "VALIDATION.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n")
    values = [c["added_p99_9_ms"] for c in comparisons]
    equal = sum(c["canonical_equal_excluding_revision_and_isa"] for c in comparisons)
    lines = ["# Goblin Cannon simulated channel quiet-host latency comparison", "",
        f"**{host_statuses['pass']}/{len(paths)} configurations pass** the 2.1 ms added-processing/buffering limit on `{host['hostname']}` ({host['runtime_isa']}). Added p99.9 spans **{min(values):.3f}–{max(values):.3f} ms**. All {host['ctest_passed']}/{host['ctest_total']} CTest entries passed before timing began ({host['ctest_wall_seconds']:.2f} s).", "",
        "## Simulated channel method and provenance", "",
        f"The tested commit is `{host['git_commit']}`; source SHA-256 is `{host['source_tree_sha256']}`, identical to the AVX-512 campaign. [Host/build metadata and exact commands](HOST.json) record the compiler, kernel, CPU, binary hash, affinity and load averages. The source transfer to naamah was explicitly approved.", "",
        "All twelve configurations use seed 7446529: 10/24 kHz, QPSK (4-QAM)/16-QAM/64-QAM, short/long equalizer spans. Each runs for the original twelve seconds, with one worker, 48-sample audio blocks and no concurrent validation jobs. Carrier correction is off; adaptive equalization and the recovery profile are on. This is one observation per configuration, not a bound on future host scheduling delays.", "",
        "Each delivered message is matched to a one-sample simulated-time production-stack reference. Intrinsic transmission, modem/FEC and startup are subtracted per message before computing added-latency percentiles. Total latency and the intrinsic reference remain separate. Host CPU/OS timing is non-canonical; physical audio devices and network sockets are outside this loopback. No RF transmission took place.", "",
        f"**{equal}/{len(paths)} canonical results match the AVX-512 baseline exactly** after excluding only `git_commit`, `require_avx512` and the observed `demapper`. All full parameters and observations remain in their original JSON; no measured values are normalized or overwritten. [Comparison checks](VALIDATION.json).", "",
        "## Simulated channel B5 results", "",
        "All times below are milliseconds. Configuration links open measured host sidecars. The original AVX-512 records remain in the parent directory and the parent report's baseline table.", "",
        "| Configuration / span | Added p50 | Added p99 | Added p99.9 | Added max | Total p99.9 | Reference p99.9 | avx10 added p99.9 | Status |",
        "| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |", *rows, "",
        "[Complete group table, per-stage call durations, serialization and modem residence estimates](SUMMARY.md). Per-call CPU percentiles are not an additive breakdown of message latency.", "",
        "## Simulated channel runtime and coverage", "",
        "| Selection | Cases | Wall seconds |", "| --- | ---: | ---: |",
        *[f"| B5 {tier} | 6 | {seconds:.3f} |" for tier, seconds in sorted(runtime.items())], "",
        "These are B5 selections, not complete tiers. The original quick/full runtime overruns remain recorded. The original 9,920-case ledger is unchanged; these twelve follow-up runs are stored separately. No soak or fading campaign was rerun on naamah.", "",
        "## Simulated channel defects found", "",
        "No new B5 failures or xfails." if host_statuses == {"pass": 12} and statuses == {"pass": 12} else f"Canonical statuses: {dict(statuses)}; host statuses: {dict(host_statuses)}. See the per-case assertions above.", "",
        "The [existing RF, crypto and scheduler findings](../REPORT.md) remain open; a quiet-host latency pass does not resolve them.", "",
        "## Simulated channel open thresholds", "",
        "B5 uses the agreed 2.1 ms added-processing/buffering limit. No threshold was changed; other acceptance margins remain `THRESHOLD_TBD` in the parent report.", ""]
    (QUIET / "COMPARISON.md").write_text("\n".join(lines))
    print(json.dumps({"cases": len(paths), "host_statuses": dict(host_statuses), "canonical_matches": equal,
                      "added_p99_9_ms_range": [min(values), max(values)]}))


if __name__ == "__main__":
    main()
