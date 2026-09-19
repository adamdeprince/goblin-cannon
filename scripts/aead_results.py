#!/usr/bin/env python3
"""Validate and publish current AEAD simulated channel evidence, without rerunning it."""
from __future__ import annotations
from channel_description import compact_markdown
import argparse
from collections import Counter, defaultdict
import gzip
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tarfile

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/aead"
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from run import source_digest
from catalog import OPEN_THRESHOLDS
from channel_metadata import normalize_record

SEEDS = (7446529, 7446530, 7446531)
LABELS = {"bpsk_soft": "BPSK · convolutional", "bpsk_bch": "BPSK · BCH",
          "qpsk_soft": "QPSK · convolutional", "qpsk_bch": "QPSK · BCH",
          "8psk_soft": "8-PSK · convolutional", "8psk_bch": "8-PSK · BCH"}


def read(path):
    value = json.loads(path.read_text())
    return normalize_record(value, warn=False) if isinstance(value, dict) and "parameters" in value else value


def save(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2, sort_keys=True, allow_nan=False) + "\n")


def records(directory):
    return [(p, read(p)) for p in sorted(directory.glob("*/[0-9]*.json")) if not p.name.endswith(".host.json")]


def url(path):
    return "https://github.com/adamdeprince/goblin-cannon/blob/main/" + str(path.relative_to(ROOT))


def span(values, scale=1, digits=2):
    observed = [v * scale for v in values if v is not None]
    if not observed:
        return "Unobserved"
    low, high = min(observed), max(observed)
    return (f"{low:.{digits}f}" if low == high else f"{low:.{digits}f}–{high:.{digits}f}") + (" (some unobserved)" if len(observed) != len(values) else "")


def snapshot():
    files = [ROOT / "CMakeLists.txt"]
    for directory in ("src", "include", "proto", "tests", "cmake", "examples", "scripts", "config"):
        files += [p for p in sorted((ROOT / directory).rglob("*")) if p.is_file()
                  and "__pycache__" not in p.parts and p.suffix != ".pyc"]
    output = io.BytesIO()
    with gzip.GzipFile(filename="", mode="wb", fileobj=output, mtime=0) as compressed:
        with tarfile.open(fileobj=compressed, mode="w") as archive:
            for path in files:
                content = path.read_bytes()
                info = tarfile.TarInfo(str(path.relative_to(ROOT)))
                info.size = len(content); info.mode = 0o644
                archive.addfile(info, io.BytesIO(content))
    # Preserve the actual measurement snapshot when only report descriptions changed.
    report_only = (DIRECTORY / "SOURCE.json").exists() and read(DIRECTORY / "SOURCE.json")["source_tree_sha256"] != source_digest()
    archive_name = "report-source-snapshot.tar.gz" if report_only else "source-snapshot.tar.gz"
    manifest_name = "REPORT_SOURCE.json" if report_only else "SOURCE.json"
    (DIRECTORY / archive_name).write_bytes(output.getvalue())
    save(DIRECTORY / manifest_name, dict(report_header="simulated channel report source snapshot" if report_only else "simulated channel tested source snapshot",
         git_commit=subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip(),
         source_tree_sha256=source_digest(), archive_sha256=hashlib.sha256(output.getvalue()).hexdigest(),
         files={str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in files}))


def build():
    source = source_digest()
    main, polar = records(DIRECTORY), records(DIRECTORY / "polar")
    brief, current = records(DIRECTORY / "brief-latency"), records(DIRECTORY / "naamah-latency")
    if tuple(map(len, (main, polar, brief, current))) != (112, 288, 12, 12):
        raise ValueError(f"Incomplete selection: {tuple(map(len, (main, polar, brief, current)))}")
    all_records = main + polar + brief + current
    metadata_source = source
    if all_records[0][1]["parameters"]["source_tree_sha256"] != source:
        from correct_aead_metadata import verify_measured_source
        source, _ = verify_measured_source()
        correction = read(DIRECTORY / "METADATA_CORRECTION.json")
        if correction["metadata_source_tree_sha256"] != metadata_source:
            raise ValueError("Metadata correction does not match the current formatter")
        for record in correction["records"]:
            if hashlib.sha256((DIRECTORY / record["path"]).read_bytes()).hexdigest() != record["corrected_sha256"]:
                raise ValueError(f"Corrected record changed after audit: {record['path']}")
    for path, record in all_records:
        if record["parameters"]["source_tree_sha256"] != source:
            raise ValueError(f"Untested or mixed source: {path}")
        if record["parameters"]["carrier_correction"] != 0:
            raise ValueError(f"Carrier correction enabled: {path}")
    invalid = [(str(p), r.get("reason", r["status"])) for p, r in all_records if r["status"] in ("fail", "xpass", "error")]
    defects = [dict(case=r["test_name"], assertion=a["assertion"], reason=a["reason"], source=url(p))
               for p, r in main for a in r["assertions"] if a["status"] in ("xfail", "fail", "xpass")]
    grouped = defaultdict(Counter)
    for _, r in main:
        grouped[r["group"]][r["status"]] += 1
    rows = []
    for bw in (10000, 24000):
        for variant, label in LABELS.items():
            for preset in ("quiet", "moderate", "disturbed"):
                chosen = []
                for seed in SEEDS:
                    p = DIRECTORY / "polar" / f"E2_refinement_followup_{bw}_{variant}_high_lat_{preset}" / f"{seed}.json"
                    chosen.append((p, read(p)))
                settings = chosen[0][1]["parameters"]
                rf = [(DIRECTORY / "polar" / f"A2_refinement_screen_{bw}_{variant}_high_lat_{preset}" / f"{seed}.json") for seed in SEEDS]
                rf_records = [read(p) for p in rf]
                if [r["seed"] for _, r in chosen] != list(SEEDS):
                    raise ValueError("Wrong seed set")
                rows.append(dict(bandwidth=bw, variant=variant, label=label, preset=preset,
                    modulation=settings["modulation"], bch=bool(settings["bch_payload"]), duration=settings["duration_s"],
                    parameters={k: settings[k] for k in ("delay_spread_ms", "doppler_spread_hz", "snr_db", "frame_symbols",
                        "training_symbols", "equalizer_feedforward_taps", "equalizer_feedback_taps", "equalizer_delay_symbols",
                        "pilot_interval_symbols", "recovery_interval_frames", "sample_rate_hz", "path_gains_db")},
                    goodput=[r["metrics"]["goodput_bps"] for _, r in chosen],
                    fresh_goodput=[r["metrics"]["fresh_goodput_bps"] for _, r in chosen],
                    delivery=[r["metrics"]["message_delivery_fraction_of_framed"] for _, r in chosen],
                    freshness=[r["metrics"]["freshness_ms"]["p99_9"] for _, r in chosen],
                    silence=[r["metrics"]["delivery_silence_ms"]["max"] for _, r in chosen],
                    auth_failures=[r["observations"]["authentication_failures"] for _, r in chosen],
                    corrupt=[r["observations"]["corrupted_messages_delivered"] for _, r in chosen],
                    ber=[r["metrics"]["ber"] for r in rf_records],
                    survival=[r["metrics"]["frame_survival_fraction"] for r in rf_records],
                    observed=[r["metrics"]["bit_observation_fraction"] for r in rf_records],
                    measured_power=[r["observations"]["tx_mean_sample_power"] for r in rf_records],
                    sources=[url(p) for p, _ in chosen], rf_sources=[url(p) for p in rf]))
    latency = []
    comparisons = []
    for directory, selection, baseline in (("brief-latency", brief, ROOT / "results/fixes-2-5"),
                                           ("naamah-latency", current, ROOT / "results/recovery-improvements/naamah-latency")):
        for path, record in selection:
            host_path = path.with_suffix(".host.json")
            host = read(host_path)
            if host["parameters"] != record["parameters"]:
                raise ValueError("Host/canonical parameter mismatch")
            o, p = host["observations"], record["parameters"]
            old_path = baseline / path.parent.name / host_path.name
            old = read(old_path)["observations"]
            row = dict(case=record["test_name"], bandwidth=p["bandwidth_hz"], modulation=p["modulation"],
                       span="polar" if "polar_span" in record["test_name"] else "short", profile=directory,
                       added=o["host_added_software_latency_ms_percentiles"], total=o["host_latency_ms_percentiles"],
                       reference=record["latency_reference"]["metrics"]["latency_ms"],
                       status=o["added_software_latency_assertion"]["status"],
                       delivered=record["observations"]["messages_delivered"],
                       tx=o["host_tx_per_block_ms_percentiles"], rx=o["host_rx_per_block_ms_percentiles"],
                       source=url(host_path), record=url(path),
                       stage_breakdown=record["metrics"]["latency_stage_breakdown_ms"])
            if row["status"] != "pass":
                invalid.append((str(host_path), row["status"]))
            latency.append(row)
            comparisons.append(dict(case=row["case"], profile=directory,
                old_added_p99_9_ms=old["host_added_software_latency_ms_percentiles"]["p99_9"],
                new_added_p99_9_ms=row["added"]["p99_9"], baseline=url(old_path), source=row["source"], status=row["status"]))
    repeats = []
    for variant in LABELS:
        for bw in (10000, 24000):
            name=f"D4_refinement_{bw}_{variant}_null"
            a, b = DIRECTORY / name / "7446529.json", DIRECTORY / "polar" / name / "7446529.json"
            identical = a.read_bytes() == b.read_bytes()
            repeats.append(dict(case=name, seed=7446529, byte_identical=identical, first=url(a), second=url(b)))
            if not identical:
                invalid.append((name, "Repeated canonical JSON differs"))
    a8 = [dict(case=r["test_name"], sir=r["parameters"]["data_sir_db"],
               delivered=r["observations"]["messages_delivered"], corrupt=r["observations"]["corrupted_messages_delivered"],
               authentication_failures=r["observations"]["authentication_failures"], fec_gaps=r["observations"]["fec_gap_events"],
               source=url(p), status=r["status"]) for p, r in main if r["group"] == "A8"]
    unique = {(r["test_name"], r["seed"], r["parameters"].get("rf_profile", "legacy")) for _, r in all_records}
    executions = []
    for directory, label in ((DIRECTORY, "Security"), (DIRECTORY / "polar", "Polar"),
                             (DIRECTORY / "brief-latency", "Brief B5"),
                             (DIRECTORY / "naamah-latency", "Current B5")):
        for path in sorted(directory.glob("EXECUTION-*.json")):
            execution = read(path)
            if execution["source_tree_sha256"] != source:
                raise ValueError(f"Mixed-source execution: {path}")
            executions.append(dict(selection=label, tier=execution["tier"],
                cases=execution["executed_cases"], seconds=execution["elapsed_seconds"],
                budget=execution["budget_seconds"], source=url(path)))
    manifest = dict(report_header="simulated channel AEAD validation", source_tree_sha256=source,
        metadata_source_tree_sha256=metadata_source,
        git_commit=main[0][1]["parameters"]["git_commit"], seeds=list(SEEDS), recorded_runs=len(all_records),
        unique_case_seed_profiles=len(unique), security_records=len(main), polar_records=len(polar),
        security_statuses=dict(Counter(r["status"] for _, r in main)), polar_statuses=dict(Counter(r["status"] for _, r in polar)),
        remaining_assertions=len(defects), remaining_cases=len({d["case"] for d in defects}),
        closed_authentication_assertions=6, byte_identical_repeats=len(repeats),
        latency_configurations=len(latency), host_latency_statuses=dict(Counter(r["status"] for r in latency)),
        failures=invalid, groups={g: dict(c) for g, c in grouped.items()},
        latency_baseline_note="The brief's 1.019 ms / 13 assertions in 11 cases are from fixes-2-5. The newer recovery-profile ledger had 15 assertions in 13 cases; six crypto assertions now pass, leaving nine assertions in nine cases. Different profiles are never silently combined.",
        limitations=["Only the six ordinary BPSK/QPSK/8-PSK coding configurations were rerun for current polar delivery.",
            "Configured 30 dB retains the uncalibrated nominal noise reference; measured sample power is reported. These are not actual-30-dB availability estimates.",
            "High-latitude presets are simulated channels, not observations of the 71-degree route. No recorded-band noise or soak was run.",
            "The 24 kHz two-path model extends beyond ITU-R F.1487's validated bandwidth scope.",
            "Physical radio/audio devices and network sockets are outside the paced software loopback.",
            "The combined quick selections, including both B5 profiles, exceed two minutes. Each selected invocation fits its tier, but this does not establish the whole quick tier's CI runtime."])
    return dict(schema_version=3, manifest=manifest, rows=rows, latency=latency, comparisons=comparisons,
                defects=defects, a8=a8, repeats=repeats, executions=executions,
                crypto=read(DIRECTORY / "D6_crypto_errors_replay_restart/7446529.json")["observations"])


def report(data):
    m=data["manifest"]
    lines=["# Goblin Cannon simulated channel AEAD results", "", compact_markdown(), "",
        "OpenSSL AES-256-GCM authenticates production messages before sink delivery. The tag replaces message CRC integrity; RF-header CRCs screen framing only.", "",
        f"{m['recorded_runs']} recorded runs / {m['unique_case_seed_profiles']} unique case/seed/profile combinations. {m['remaining_assertions']} expected-failing assertions across {m['remaining_cases']} cases remain in the current recovery-profile security selection. Six crypto assertions are fixed.", "",
        "## Simulated channel scope and defect count", "", m["latency_baseline_note"], "",
        "## Simulated channel A8: co-channel rejection", "",
        "| SIR dB | Delivered | Authentication failures | FEC gaps | Foreign/corrupt delivered | Result |",
        "| ---: | ---: | ---: | ---: | ---: | --- |"]
    for r in data["a8"]:
        lines.append(f"| [{r['sir']}]({r['source']}) | {r['delivered']} | {r['authentication_failures']} | {r['fec_gaps']} | {r['corrupt']} | {r['status']} |")
    lines += ["", "A zero authentication count means no invalid complete record reached authentication in that trace. It is not a fabricated rejection count. The wrong-key RF/gRPC regression and D6 separately exercise actual verification failures.", "",
        "## Simulated channel D6: errors, replay and process restart", "",
        "| Observation | Count |", "| --- | ---: |"]
    for key in ("tamper_attempts", "authentication_failures", "replay_rejections", "replay_deliveries", "nonces_observed", "reused_nonces_after_process_restart", "valid_authenticated_deliveries"):
        lines.append(f"| {key} | {data['crypto'][key]} |")
    lines += ["", "Two distinct sender processes reserve epochs from one persisted journal with the same key. Every observed wire nonce is distinct. Key IDs are authenticated, but two-key overlap and coordinated mid-stream retirement remain `xfail`.", "",
        "## Simulated channel B5: requested 12-case comparison", "",
        "Added processing/buffering p99.9 in milliseconds. Old values are the brief's saved fixes-2-5 baseline; new values are serial naamah measurements with the same declared RF configuration. Total latency and the intrinsic transmission/modem reference are separate columns.", "",
        "| Case | Old added | New added | Change µs | Total p99.9 | Intrinsic p99.9 | Result |",
        "| --- | ---: | ---: | ---: | ---: | ---: | --- |"]
    for r in data["comparisons"]:
        if r["profile"] != "brief-latency": continue
        timing=next(t for t in data["latency"] if t["case"]==r["case"] and t["profile"]==r["profile"])
        lines.append(f"| [{r['case']}]({r['source']}) | {r['old_added_p99_9_ms']:.6f} | {r['new_added_p99_9_ms']:.6f} | {(r['new_added_p99_9_ms']-r['old_added_p99_9_ms'])*1000:.1f} | {timing['total']['p99_9']:.3f} | {timing['reference']['p99_9']:.3f} | {r['status']} |")
    lines += ["", "## Simulated channel B5: current recovery profile", "",
              "| Case | Added p99.9 ms | Total p99.9 ms | Intrinsic p99.9 ms | Result |", "| --- | ---: | ---: | ---: | --- |"]
    for r in data["latency"]:
        if r["profile"]=="naamah-latency": lines.append(f"| [{r['case']}]({r['source']}) | {r['added']['p99_9']:.6f} | {r['total']['p99_9']:.3f} | {r['reference']['p99_9']:.3f} | {r['status']} |")
    lines += ["", "Both tables use the unchanged 2.1 ms allowance. `.host.json` files retain measured stage call durations and source-to-framer timings. Canonical JSON retains deterministic added buffering, serialization estimates and modem/FEC residence; per-stage percentiles are not summed.", "",
              "## Simulated channel B5: crypto profile", ""]
    profile=read(DIRECTORY / "profile/gcm.host.json")
    lines += ["20,000 measured calls per size after 1,000 warmup calls, on naamah. EVP contexts are initialized once and reused. Times are microseconds; this profile excludes FEC/framing and journal startup.", "",
              "| Body bytes | Seal p99.9 µs | Verify/open p99.9 µs |", "| ---: | ---: | ---: |"]
    for r in profile["cases"]: lines.append(f"| {r['body_bytes']} | {r['seal_us']['p99_9']:.3f} | {r['open_us']['p99_9']:.3f} |")
    lines += ["", "The first cold EVP context setup took %.3f µs before any message was created. There is no per-frame context creation or re-keying. Longer authenticated records change phase relative to 1 ms audio blocks; inspect `PROFILE.md` for the largest per-configuration regressions, deterministic buffering and matched pre-AEAD CPU measurements." % profile["cases"][0]["context_initialization_us"], "",
              "## Simulated channel A2/E2: current polar delivery", "",
              "Ranges cover three independent seeds, not confidence intervals. Quiet/moderate/disturbed durations are 300/300/100 seconds per seed; raw RF screens remain ten seconds. The source uses the real airtime auction and every delivered message has passed GCM.", "",
              "| Band kHz | Configuration | Preset | Useful bit/s | Fresh bit/s | Delivered / framed % | Freshness p99.9 ms | Longest silence s |",
              "| ---: | --- | --- | ---: | ---: | ---: | ---: | ---: |"]
    for r in data["rows"]:
        lines.append(f"| {r['bandwidth']//1000} | [{r['label']}]({r['sources'][0]}) | {r['preset']} | {span(r['goodput'])} | {span(r['fresh_goodput'])} | {span(r['delivery'],100)} | {span(r['freshness'])} | {span(r['silence'],.001,3)} |")
    lines += ["", "## Simulated channel remaining test groups", "", "| Group | Status counts |", "| --- | --- |"]
    for group, counts in sorted(m["groups"].items()): lines.append(f"| {group} | {', '.join(f'{k}: {v}' for k,v in sorted(counts.items()))} |")
    lines += ["", "## Simulated channel validation and runtime", "",
              "Both avx10 and naamah pass 21/21 CTest tests, including the production wrong-key RF/gRPC counter regression. The Python harness passes 14 checks; CLI/protobuf serialization passes 19. Logs and browser evidence are in `validation-meta/`.", "",
              "| Selection | Tier | Runs | Wall seconds | Invocation budget seconds |",
              "| --- | --- | ---: | ---: | ---: |"]
    for execution in data["executions"]:
        lines.append(f"| [{execution['selection']}]({execution['source']}) | {execution['tier']} | {execution['cases']} | {execution['seconds']:.3f} | {execution['budget']} |")
    lines += ["", "These are selected invocations, not complete tiers. Their combined quick runtime exceeds 120 seconds, including the two separately measured B5 profiles; no counts or durations were reduced. The slow-FSK unit recovery trace was extended from 30 to 120 simulated seconds to fit complete authenticated records around its dropout, with its delivery assertions retained.", ""]
    lines += ["", "## Simulated channel defects found", "", "| Case | Assertion | Finding |", "| --- | --- | --- |"]
    for d in data["defects"]: lines.append(f"| [{d['case']}]({d['source']}) | {d['assertion']} | {d['reason']} |")
    lines += ["", "## Simulated channel open thresholds", "", "All unapproved thresholds remain `THRESHOLD_TBD`; no acceptance threshold changed.", "", "| Threshold | Proposed value | Reason |", "| --- | --- | --- |"]
    for name,(proposed,why) in OPEN_THRESHOLDS.items(): lines.append(f"| {name}: THRESHOLD_TBD | {proposed} | {why} |")
    lines += ["", "## Simulated channel limits and reproducibility", "", *["- "+v for v in m["limitations"]],
              f"- {len(data['repeats'])} independently repeated authenticated message runs have byte-identical canonical JSON. Host measurements are excluded.",
              f"- Base commit `{m['git_commit']}`; tested source SHA-256 `{m['source_tree_sha256']}`. `SOURCE.json` and `source-snapshot.tar.gz` preserve the tested files.",
              f"- Report-description source SHA-256 `{m['metadata_source_tree_sha256']}`. `METADATA_CORRECTION.json` records corrections to three stale CTR/CRC/Walsh labels. A byte comparison verifies that all compiled source and simulation controls match the measurement snapshot; metrics, assertions and measured-source IDs are unchanged. `REPORT_SOURCE.json` preserves the corrected formatter.",
              "- `EXECUTION_*.json` preserves durations, host details and each exact selection. This is a selected campaign, not the complete A1–E4 matrix.", ""]
    return "\n".join(lines)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("--snapshot",action="store_true");args=parser.parse_args()
    data=build()
    save(DIRECTORY / "DATA.json",data);save(DIRECTORY / "VALIDATION.json",data["manifest"])
    (DIRECTORY / "SUMMARY.md").write_text(report(data))
    if args.snapshot: snapshot()
    print(json.dumps(data["manifest"]))
    return bool(data["manifest"]["failures"])


if __name__=="__main__":
    raise SystemExit(main())
