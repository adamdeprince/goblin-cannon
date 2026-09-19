#!/usr/bin/env python3
"""Publish paired-seed delivery and fresh goodput from the carrier-offset sweep."""
import argparse
import hashlib
import json
from pathlib import Path

from measurement_source import verify_snapshot

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/carrier-offset"
SEEDS = (7446529, 7446530, 7446531)


def build():
    source = verify_snapshot(DIRECTORY)
    execution = json.loads((DIRECTORY / "EXECUTION.json").read_text())
    if execution["source_tree_sha256"] != source["source_tree_sha256"]:
        raise ValueError("Sweep execution and source snapshot differ")
    records = {}
    paths = {}
    for path in sorted(DIRECTORY.glob("*/[0-9]*.json")):
        record = json.loads(path.read_text())
        p = record["parameters"]
        if record["status"] != "characterized" or p["source_tree_sha256"] != source["source_tree_sha256"]:
            raise ValueError(f"Invalid sweep record: {path}")
        expected = dict(carrier_correction=0, residual_drift_hz_per_second=0, channel_model="watterson",
                        delay_spread_ms=1, doppler_spread_hz=.5, doppler_shift_hz=[0, 0],
                        bandwidth_hz=24000, modulation="qpsk", bch_payload=1, snr_db=30, duration_s=300)
        if any(p[k] != v for k, v in expected.items()):
            raise ValueError(f"Wrong quiet-preset profile: {path}")
        key = (p["residual_offset_hz"], record["seed"])
        if key in records:
            raise ValueError(f"Duplicate sweep record: {path}")
        records[key], paths[key] = record, path
    offsets = sorted({offset for offset, seed in records})
    if set(offsets) != set(execution["offsets_hz"]):
        raise ValueError("Sweep records and execution offsets differ")
    if not {0, .5, 1, 2, 5, 10, 20}.issubset(offsets):
        raise ValueError("Required positive offsets are missing")
    if set(records) != {(offset, seed) for offset in offsets for seed in SEEDS}:
        raise ValueError("Sweep is missing a seed")
    baseline = {seed: records[0, seed]["metrics"]["message_delivery_fraction_of_framed"] for seed in SEEDS}
    rows = []
    for offset in offsets:
        selected = [records[offset, seed] for seed in SEEDS]
        delivery = [100 * r["metrics"]["message_delivery_fraction_of_framed"] for r in selected]
        fresh = [r["metrics"]["fresh_goodput_bps"] for r in selected]
        deltas = [100 * (r["metrics"]["message_delivery_fraction_of_framed"] - baseline[r["seed"]]) for r in selected]
        rows.append(dict(carrier_frequency_offset_hz=offset, delivery_percent=delivery,
            mean_delivery_percent=sum(delivery)/len(delivery), fresh_goodput_bps=fresh,
            mean_fresh_goodput_bps=sum(fresh)/len(fresh), paired_delivery_delta_percentage_points=deltas,
            max_absolute_paired_delta_percentage_points=max(map(abs, deltas)),
            within_tolerance=all(abs(d) <= .1 + 1e-12 for d in deltas),
            sources=["https://github.com/adamdeprince/goblin-cannon/blob/main/" + str(paths[offset, seed].relative_to(ROOT)) for seed in SEEDS]))
    indexed = {r["carrier_frequency_offset_hz"]: r for r in rows}
    magnitudes = sorted(offset for offset in offsets if offset > 0)
    tolerance = 0
    for magnitude in magnitudes:
        if -magnitude not in indexed:
            raise ValueError("Both signs must be measured for a magnitude tolerance")
        if not (indexed[magnitude]["within_tolerance"] and indexed[-magnitude]["within_tolerance"]):
            break
        tolerance = magnitude
    largest = magnitudes[-1]
    if max(indexed[largest]["mean_delivery_percent"], indexed[-largest]["mean_delivery_percent"]) > indexed[0]["mean_delivery_percent"] * .01:
        raise ValueError("The sweep has not reached delivery collapse in both directions")
    return dict(schema_version=1, report_header="Simulated channel carrier frequency offset tolerance",
        profile="24 kHz QPSK+BCH, combined recovery, high-latitude quiet, 30 dB nominal SNR",
        duration_s=300, seeds=list(SEEDS), tolerance_hz=tolerance, collapse_magnitude_hz=largest,
        tolerance_percentage_points=.1, criterion="Every seed and both offset signs stay within 0.1 percentage points of the paired 0 Hz delivery value, at every tested magnitude up to the reported bound.",
        baseline_seed_range_percentage_points=max(indexed[0]["delivery_percent"])-min(indexed[0]["delivery_percent"]),
        source_tree_sha256=source["source_tree_sha256"], git_commit=source["git_commit"],
        zero_offset_matches_published_observations=execution["zero_offset_matches_published_observations"],
        records_sha256={str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths.values()},
        rows=rows)


def table_markdown(data):
    lines = ["| Carrier frequency offset (Hz) | Delivery %: mean [seed range] | Fresh goodput bit/s: mean [seed range] | Largest paired delivery change (percentage points) | Within 0.1 points for every seed |",
             "| ---: | ---: | ---: | ---: | :---: |"]
    for r in data["rows"]:
        d, g = r["delivery_percent"], r["fresh_goodput_bps"]
        offset = r["carrier_frequency_offset_hz"]
        lines.append(f"| [{offset:+g}]({r['sources'][0]}) | {r['mean_delivery_percent']:.4f} [{min(d):.4f}–{max(d):.4f}] | {r['mean_fresh_goodput_bps']:.2f} [{min(g):.2f}–{max(g):.2f}] | {r['max_absolute_paired_delta_percentage_points']:.4f} | {'yes' if r['within_tolerance'] else 'no'} |")
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = build()
    from channel_description import boundary_text, definitions_markdown, preset_markdown, scope_text
    report = "\n\n".join(["# Carrier frequency offset tolerance in the simulated quiet channel",
        boundary_text(data["tolerance_hz"]), scope_text(data), definitions_markdown(), preset_markdown(),
        "A constant carrier frequency offset is applied at channel output, after filtering and sample-clock resampling. Per-path Doppler shift is zero; Doppler spread stays at 0.5 Hz. Carrier correction remains disabled. The zero-offset observations and metrics exactly match the three published quiet controls.",
        f"The measured bound is **{data['tolerance_hz']:g} Hz** in either direction. {data['criterion']} This is a sampled bound, not a continuous-frequency guarantee. The zero-offset delivery range across seeds is {data['baseline_seed_range_percentage_points']:.4f} percentage points. Delivery collapses by ±{data['collapse_magnitude_hz']:g} Hz under the declared 1%-of-baseline criterion.",
        table_markdown(data),
        "Delivery is authenticated messages delivered / messages framed. Fresh goodput uses the existing source-key freshness metric. Each offset has three full 300-second traces, seeds 7446529–7446531. All individual records and their source snapshot are retained here; the original 908-record campaign is unchanged.",
        "Reproduce with `python3 scripts/carrier_offset_campaign.py`, then `python3 scripts/carrier_offset_results.py`. The runner measures 0, ±0.5, ±1, ±2, ±5, ±10 and ±20 Hz, doubling the magnitude afterward until mean delivery in both directions is at most 1% of the 0 Hz value. It uses the original canonical run schema and metric calculation."])+"\n"
    outputs = {DIRECTORY/"DATA.json": json.dumps(data, indent=2, sort_keys=True)+"\n", DIRECTORY/"SUMMARY.md": report}
    if args.check:
        if any(not p.exists() or p.read_text()!=text for p,text in outputs.items()):
            parser.exit(1, "Carrier-offset publication is stale\n")
        print("Carrier-offset publication matches all recorded measurements.")
    else:
        for path,text in outputs.items():
            path.write_text(text)
        print(f"Measured carrier frequency offset tolerance: {data['tolerance_hz']:g} Hz")


if __name__ == "__main__":
    main()
