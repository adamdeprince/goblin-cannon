#!/usr/bin/env python3
"""Generate the simulated channel comparison from preserved B5 observations."""
import json
from pathlib import Path
import sys

HERE = Path(__file__).resolve().parent
REPO = HERE.parents[1]
sys.path.insert(0, str(REPO / "tests/simulated_channel"))
from metrics import percentiles


def read(path):
    return json.loads(path.read_text())


def fmt(value):
    return "no deliveries" if value is None else f"{value:.3f}"


def main():
    environment = read(HERE / "VALIDATION.host.json")
    assert environment["complete"] and environment["returncode"] == 0
    assert len(environment["canonical_repeat_check"]) == 6
    assert all(row["identical"] for row in environment["canonical_repeat_check"].values())
    comparisons = []
    for first in sorted((HERE / "repeat-1").glob("B5*/[0-9]*.json")):
        if first.name.endswith(".host.json"):
            continue
        relative = first.relative_to(HERE / "repeat-1")
        baseline_path = REPO / "results" / relative
        baseline = read(baseline_path)
        baseline_host = read(baseline_path.with_suffix(".host.json"))
        repeats = []
        for repeat in range(1, 4):
            path = HERE / f"repeat-{repeat}" / relative
            record = read(path)
            host = read(path.with_suffix(".host.json"))
            p = record["parameters"]
            assert p["carrier_correction"] == 0 and p["equalizer"]["enabled"]
            assert p["duration_s"] == 12 and p["seed"] == baseline["seed"]
            assert p["require_avx512"] == 0 and record["observations"]["demapper"] == "AVX2"
            assert p == host["parameters"]
            changes = {k: {"avx10": baseline["parameters"].get(k), "naamah": v}
                       for k, v in p.items() if baseline["parameters"].get(k) != v}
            assert set(changes) <= {"require_avx512", "source_tree_sha256"}
            raw, observed = record["observations"], host["observations"]
            assert len(raw["latency_ms"]) == len(observed["host_latency_ms"])
            # Diagnostic only: retain the unchanged whole-run assertion above.
            after_startup = [wall for wall, arrival, simulated in zip(
                observed["host_latency_ms"], raw["delivery_times_s"], raw["latency_ms"])
                if arrival - simulated / 1000 >= 1.0 - 1e-9]
            repeats.append(dict(
                repeat=repeat, result=str(path.relative_to(HERE)),
                parameters=p, parameter_differences_from_avx10=changes,
                messages_created=raw["messages_created"], messages_delivered=raw["messages_delivered"],
                host_percentiles_ms=observed["host_latency_ms_percentiles"],
                sample_clock_percentiles_ms=record["metrics"]["latency_ms"],
                sample_clock_metrics_equal_avx10=record["metrics"] == baseline["metrics"],
                delivered_message_ids_equal_avx10=raw["delivered_ids"] == baseline["observations"]["delivered_ids"],
                diagnostic_source_created_at_or_after_1s=dict(
                    kind="characterize", source_creation_time_min_s=1.0, messages=len(after_startup),
                    host_percentiles_ms=percentiles(after_startup), used_for_assertion=False),
                stages={key: value for key, value in observed.items()
                        if key.endswith("_percentiles") and key != "host_latency_ms_percentiles"},
                assertion=observed["whole_loopback_latency_assertion"],
            ))
        comparisons.append(dict(test_name=baseline["test_name"], seed=baseline["seed"],
                                baseline_result=str(relative), baseline_parameters=baseline["parameters"],
                                baseline_host_percentiles_ms=baseline_host["observations"]["host_latency_ms_percentiles"],
                                repeats=repeats))
    assert len(comparisons) == 6
    assert all(r["sample_clock_metrics_equal_avx10"] and r["delivered_message_ids_equal_avx10"]
               for row in comparisons for r in row["repeats"])
    result = dict(report_header="Goblin Cannon simulated channel quiet-host latency comparison",
                  environment="VALIDATION.host.json", comparisons=comparisons,
                  scope="Source-to-sink paced simulated audio loopback, startup included; physical audio devices and network sockets absent.",
                  caveat="avx10 used AVX-512 and four concurrent matrix workers; naamah uses AVX2 and one worker. This compares observed runs, not a controlled estimate of host-noise cost.")
    (HERE / "COMPARISON.json").write_text(json.dumps(result, indent=2, sort_keys=True, allow_nan=False) + "\n")
    lines = ["# Goblin Cannon simulated channel — naamah latency retest", "",
             "Built and tested the existing B5 cases on `naamah` (AMD Ryzen Threadripper PRO 5995WX, AVX2, GCC 16.1, Release). Installed the missing gRPC dependencies. The 11 CTest entries passed in 6.40 seconds.", "",
             "All six B5 cases ran three times, one worker at a time, with their original 12-second duration and seed `7446529`. Carrier correction remained off and adaptive equalization remained on. Canonical result JSON was byte-identical across the three repetitions for every case. Host wall-clock observations remain separate.", "",
             "The measured path is source creation through auction, framing, FEC, crypto, modem and paced 1 ms simulated audio buffers to sink delivery. Startup is included. Physical audio drivers and network sockets are not represented.", "",
             "The quieter host did not materially change these latency measurements. Sample-clock metrics and delivered message IDs match the original `avx10` runs exactly. The deterministic path already takes 77 / 67 / 63 ms at p99.9 for QPSK / 16-QAM / 64-QAM on the 10 kHz profile, before CPU/OS time is measured. All six B5 cases retain their reviewed expected failures; the 24 kHz cases still deliver no messages.", "",
             "## Simulated channel — comparison with avx10", "",
             "The prior `avx10` run used AVX-512 and four matrix workers. `naamah` uses AVX2 and one worker. CPU, ISA and concurrency differ; this is a comparison of recorded observations, not an isolated measurement of scheduler noise.", "",
             "| Profile | Modulation | avx10 p99.9 ms | naamah p99.9 ms, repeats 1 / 2 / 3 | Sample-clock p99.9 ms | 2.1 ms assertion |",
             "| --- | --- | ---: | --- | ---: | --- |"]
    for row in comparisons:
        p = row["baseline_parameters"]
        reps = row["repeats"]
        lines.append(f"| {p['bandwidth_hz']/1000:g} kHz | {p['modulation']} | {fmt(row['baseline_host_percentiles_ms']['p99_9'])} | {' / '.join(fmt(r['host_percentiles_ms']['p99_9']) for r in reps)} | {fmt(reps[0]['sample_clock_percentiles_ms']['p99_9'])} | {' / '.join(r['assertion']['status'] for r in reps)} |")
    lines += ["", "## Simulated channel — individual observations", "",
              "| Case | Repeat | Delivered / created | p50 ms | p99 ms | p99.9 ms | Max ms |",
              "| --- | ---: | ---: | ---: | ---: | ---: | ---: |"]
    for row in comparisons:
        for r in row["repeats"]:
            m = r["host_percentiles_ms"]
            lines.append(f"| [{row['test_name']}]({r['result'].replace('.json', '.host.json')}) | {r['repeat']} | {r['messages_delivered']} / {r['messages_created']} | {fmt(m['p50'])} | {fmt(m['p99'])} | {fmt(m['p99_9'])} | {fmt(m['max'])} |")
    lines += ["", "## Simulated channel — startup diagnostic", "",
              "The following characterization selects messages created at least one second after stream start, using recorded sample-clock creation times. It does not replace the complete-run results or alter the 2.1 ms assertion.", "",
              "| Case | Selected delivered messages, repeats 1 / 2 / 3 | p99.9 ms, repeats 1 / 2 / 3 |",
              "| --- | --- | --- |"]
    for row in comparisons:
        subsets = [r["diagnostic_source_created_at_or_after_1s"] for r in row["repeats"]]
        lines.append(f"| {row['test_name']} | {' / '.join(str(s['messages']) for s in subsets)} | {' / '.join(fmt(s['host_percentiles_ms']['p99_9']) for s in subsets)} |")
    lines += ["", "## Simulated channel — stage call durations", "",
              "Stage times are measured per call and do not add up to per-message latency. TX and RX include their internal framing/FEC/crypto work; queue residence remains in the source-to-sink measurement.", "",
              "| Case | Stage | p99.9 ms, repeats 1 / 2 / 3 |",
              "| --- | --- | --- |"]
    for row in comparisons:
        for stage in row["repeats"][0]["stages"]:
            lines.append(f"| {row['test_name']} | {stage.removesuffix('_percentiles')} | {' / '.join(fmt(r['stages'][stage]['p99_9']) for r in row['repeats'])} |")
    lines += ["", "## Simulated channel — retained evidence", "",
              "[Comparison JSON](COMPARISON.json) includes full parameters and explicit differences from `avx10`. [Host environment and commands](VALIDATION.host.json) include CPU flags, compiler/library versions, CMake configuration, source digest, load and CPU counters before/after each repetition. The original `avx10` result files are retained in the parent results directory.", "",
              "[Repetition 1](repeat-1/SUMMARY.md), [repetition 2](repeat-2/SUMMARY.md), [repetition 3](repeat-3/SUMMARY.md), and [CTest log](ctest.log). Reproduce the comparison with `python3 results/naamah/compare.py`.", ""]
    (HERE / "COMPARISON.md").write_text("\n".join(lines))
    print(json.dumps(dict(cases=len(comparisons), repeated_runs=sum(len(r["repeats"]) for r in comparisons),
                         canonical_repeats_identical=True,
                         sample_clock_metrics_equal_avx10=all(r["sample_clock_metrics_equal_avx10"] for row in comparisons for r in row["repeats"]))))


if __name__ == "__main__":
    main()
