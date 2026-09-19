#!/usr/bin/env python3
"""Freeze sources and report the BCH/diversity/cadence simulated channel campaign."""
from __future__ import annotations
from channel_description import compact_markdown

import argparse
from collections import Counter
import gzip
import hashlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tarfile

from psk_results import read, records, spread, url

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/refinement"
SEEDS = (7446529, 7446530, 7446531)
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from catalog import OPEN_THRESHOLDS, refinement_campaign
from run import source_digest


def save(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2, sort_keys=True, allow_nan=False) + "\n")


def snapshot():
    files = [ROOT / "CMakeLists.txt"]
    for directory in ("src", "include", "proto", "tests", "cmake", "examples", "scripts", "config"):
        files += [p for p in sorted((ROOT / directory).rglob("*")) if p.is_file()
                  and "__pycache__" not in p.parts and p.suffix != ".pyc"]
    archive = DIRECTORY / "source-snapshot.tar.gz"
    archive.parent.mkdir(parents=True, exist_ok=True)
    with archive.open("wb") as output, gzip.GzipFile(filename="", mode="wb", fileobj=output, mtime=0) as compressed:
        with tarfile.open(fileobj=compressed, mode="w") as tar:
            for path in files:
                data = path.read_bytes()
                info = tarfile.TarInfo(str(path.relative_to(ROOT)))
                info.size = len(data)
                info.mode = 0o644
                tar.addfile(info, io.BytesIO(data))
    manifest = dict(report_header="simulated channel tested source snapshot",
        git_commit=subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=ROOT, text=True).strip(),
        source_tree_sha256=source_digest(), archive_sha256=hashlib.sha256(archive.read_bytes()).hexdigest(),
        files={str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in files})
    save(DIRECTORY / "validation-meta/SOURCE.json", manifest)
    print(json.dumps({k: v for k, v in manifest.items() if k != "files"}, indent=2))


def label(variant):
    if variant.startswith("diversity_"):
        _, spacing, branch = variant.split("_")
        return f"BPSK+BCH · {spacing} · {branch}"
    parts = variant.split("_")
    mode = {"bpsk": "BPSK", "qpsk": "QPSK", "8psk": "8-PSK"}[parts[0]]
    return mode + (" + BCH" if parts[1] == "bch" else " + soft K7") + (
        " · " + " / ".join(parts[2:]) if len(parts) > 2 else "")


def load():
    main = records(DIRECTORY)
    latency = records(DIRECTORY / "naamah-latency")
    counts = Counter(r["parameters"]["campaign"] for _, r in main)
    expected = dict(refinement_quick=92, refinement_screen=414, refinement_snr=192,
                    refinement_followup=414, refinement_delay=216)
    if counts != expected or len(latency) != 46:
        raise ValueError(f"Incomplete simulated channel campaign: {dict(counts)}; latency {len(latency)}/46")
    planned = {c.name: c for c in refinement_campaign()}
    expected_keys = {(c.name, s) for c in planned.values() for s in (
        SEEDS if c.parameters["campaign"] in ("refinement_followup", "refinement_screen", "refinement_delay") else SEEDS[:1])}
    if {(r["test_name"], r["seed"]) for _, r in main + latency} != expected_keys:
        raise ValueError("Unexpected or missing test/seed identities")
    provenance = read(DIRECTORY / "validation-meta/SOURCE.json")
    for path, r in main + latency:
        p = r["parameters"]
        if p["git_commit"] != provenance["git_commit"] or p["source_tree_sha256"] != provenance["source_tree_sha256"]:
            raise ValueError(f"Mixed tested sources: {path}")
        if p["carrier_correction"] or not p["adaptive_equalization"] or not p["sample_clock_recovery"]:
            raise ValueError(f"Receiver boundary changed: {path}")
        if r["status"] not in ("pass", "characterized", "xfail", "THRESHOLD_TBD"):
            raise ValueError(f"Unreviewed failure: {path}: {r['status']}")
        c = planned[r["test_name"]]
        for key, value in c.parameters.items():
            if key not in ("seed", "require_avx512") and p[key] != value:
                raise ValueError(f"Declared parameter changed: {path}: {key}")
        if p["seed"] != r["seed"] or p["execution"] != "simulated channel":
            raise ValueError(f"Incorrect seed/execution: {path}")
        if r["tier"] != c.tier or r["kind"] != c.kind:
            raise ValueError(f"Changed test classification: {path}")
    follow = [(p, r) for p, r in main if r["parameters"]["campaign"] == "refinement_followup"]
    rows = []
    keys = sorted({(r["parameters"]["bandwidth_hz"], r["parameters"]["delay_spread_ms"], r["parameters"]["refinement_variant"]) for _, r in follow})
    for band, delay, variant in keys:
        selected = sorted([(p, r) for p, r in follow if (r["parameters"]["bandwidth_hz"], r["parameters"]["delay_spread_ms"], r["parameters"]["refinement_variant"]) == (band, delay, variant)], key=lambda x: x[1]["seed"])
        params = selected[0][1]["parameters"]
        metrics = [r["metrics"] for _, r in selected]
        obs = [r["observations"] for _, r in selected]
        rows.append(dict(bandwidth=band, preset={1: "quiet", 3: "moderate", 7: "disturbed"}[delay],
            variant=variant, label=label(variant), experiment=params["experiment"], duration=params["duration_s"],
            goodput=[m["goodput_bps"] for m in metrics], fresh_goodput=[m["fresh_goodput_bps"] for m in metrics],
            delivery=[m["message_delivery_fraction_of_framed"] for m in metrics],
            freshness=[m["freshness_ms"]["p99_9"] for m in metrics], silence=[m["delivery_silence_ms"]["max"] for m in metrics],
            uptime=[m["uptime_fraction"] for m in metrics], usable=[m["usable_time_fraction"] for m in metrics],
            corrupt=[o["corrupted_messages_delivered"] for o in obs], duplicate=[o["duplicate_messages_delivered"] for o in obs],
            superseded=[o["superseded_messages_consumed"] for o in obs], sources=[url(p) for p, _ in selected],
            pilot_interval=params["pilot_interval_symbols"], recovery_interval=params["recovery_interval_frames"],
            training_symbols=params["training_symbols"], cadence=params["cadence_plan"], diversity=params["diversity"]))
    noise, screens, delays, timing, defects = [], [], [], [], []
    for path, r in main:
        p = r["parameters"]; m = r["metrics"]
        item = dict(bandwidth=p["bandwidth_hz"], variant=p["refinement_variant"], seed=r["seed"],
                    source=url(path), duration=p["duration_s"])
        if p["campaign"] == "refinement_snr":
            noise.append(item | dict(snr=p["snr_db"], ber=m["ber"], coded_ber=m["coded_ber"],
                observation_fraction=m["bit_observation_fraction"], survival=m["frame_survival_fraction"]))
        if p["campaign"] == "refinement_screen":
            screens.append(item | dict(delay_ms=p["delay_spread_ms"], ber=m["ber"], observation_fraction=m["bit_observation_fraction"],
                survival=m["frame_survival_fraction"], measured_power=r["observations"]["tx_mean_sample_power"],
                nominal_power=p["nominal_sample_power"], papr_db=r["observations"]["tx_papr_db"]))
        if p["campaign"] == "refinement_delay":
            delays.append(item | dict(delay_ms=p["delay_spread_ms"], doppler_spread_hz=p["doppler_spread_hz"],
                goodput=m["goodput_bps"], fresh_goodput=m["fresh_goodput_bps"], silence=m["delivery_silence_ms"]["max"],
                diversity=p["diversity"]))
    for path, r in main + latency:
        for a in r["assertions"]:
            if a["status"] == "xfail":
                defects.append(dict(case=r["test_name"], assertion=a["assertion"], reason=a["reason"], source=url(path)))
    for path, r in latency:
        sidecar = path.with_name(f"{r['seed']}.host.json")
        h = read(sidecar); o = h["observations"]; p = r["parameters"]
        if h["parameters"] != p: raise ValueError("Host sidecar parameters differ")
        a = o["added_software_latency_assertion"]
        if a["status"] not in ("pass", "xfail"): raise ValueError(f"Unreviewed host timing: {sidecar}")
        if a["status"] == "xfail":
            defects.append(dict(case=r["test_name"], assertion="host p99.9 <= 2.1 ms", reason=a["reason"], source=url(sidecar)))
        timing.append(dict(bandwidth=p["bandwidth_hz"], variant=p["refinement_variant"], label=label(p["refinement_variant"]),
            added=o["host_added_software_latency_ms_percentiles"], total=o["host_latency_ms_percentiles"],
            reference=r["latency_reference"]["metrics"]["latency_ms"], status=a["status"], reason=a["reason"],
            delivered=r["observations"]["messages_delivered"], source=url(sidecar), record=url(path),
            stages={k: v for k, v in o.items() if k.endswith("_ms_percentiles")},
            modem=r["observations"]["modem_delay_estimates"]))
    lookup = {(r["test_name"], r["seed"]): p for p, r in main}
    repeats = records(DIRECTORY / "determinism")
    if len(repeats) != 3: raise ValueError("Three repeated cases are required")
    for path, r in repeats:
        if path.read_bytes() != lookup[r["test_name"], r["seed"]].read_bytes():
            raise ValueError(f"Canonical determinism failure: {path}")
    power_audit = records(DIRECTORY / "power-audit")
    power_manifest = read(DIRECTORY / "power-audit/VALIDATION.json")
    if len(power_audit) != 60 or dict(Counter(r["status"] for _, r in power_audit)) != {"pass": 54, "xfail": 6}:
        raise ValueError("Power calibration findings require review")
    power_digest = hashlib.sha256()
    for path, r in power_audit:
        power_digest.update(str(path.relative_to(DIRECTORY)).encode() + b"\0" + path.read_bytes())
        for source in r["parameters"]["input_records"]:
            original = ROOT / source["record"]
            if hashlib.sha256(original.read_bytes()).hexdigest() != source["sha256"]:
                raise ValueError(f"Power audit input changed: {original}")
        if r["status"] == "xfail":
            defects.append(dict(case=r["test_name"], assertion=r["metrics"]["comparison"],
                reason=r["assertions"][0]["reason"], source=url(path)))
    unchanged = 0
    for _, r in follow:
        p = r["parameters"]; variant = p["refinement_variant"]
        if variant not in ("bpsk_bch", "bpsk_soft", "qpsk_soft"): continue
        preset_name = {1: "quiet", 3: "moderate", 7: "disturbed"}[p["delay_spread_ms"]]
        old = read(ROOT / "results/encoding-improvements" / f"E2_encoding_followup_{p['bandwidth_hz']}_{variant}_high_lat_{preset_name}" / f"{r['seed']}.json")
        for metric in ("goodput_bps", "fresh_goodput_bps", "freshness_ms", "delivery_silence_ms", "message_delivery_fraction_of_framed"):
            if r["metrics"][metric] != old["metrics"][metric]:
                raise ValueError(f"Matched old configuration changed: {r['test_name']} {metric}")
        unchanged += 1
    hosts = read(DIRECTORY / "HOSTS.json")
    if any(hosts[h]["ctest_passed"] != 20 for h in ("avx10", "naamah")):
        raise ValueError("Missing regression host evidence")
    cli = read(DIRECTORY / "validation-meta/PYTHON_GRPC.json")
    if len(cli["cases"]) != 19 or any(c["status"] != "pass" for c in cli["cases"]):
        raise ValueError("Incomplete CLI/protobuf configuration checks")
    archive_hash = hashlib.sha256((DIRECTORY / "source-snapshot.tar.gz").read_bytes()).hexdigest()
    if archive_hash != provenance["archive_sha256"]: raise ValueError("Source archive changed")
    executions = []
    for directory, host in ((DIRECTORY, "avx10"), (DIRECTORY / "naamah-latency", "naamah")):
        for path in sorted(directory.glob("EXECUTION-*.json")):
            e = read(path)
            if e["source_tree_sha256"] != provenance["source_tree_sha256"]:
                raise ValueError(f"Execution source differs: {path}")
            executions.append(dict(host=host, tier=e["tier"], campaign=e["selection"]["campaign"],
                seconds=e["elapsed_seconds"], cases=e["executed_cases"], source=url(path),
                status="resumed" if e["selection"].get("resume") else "complete"))
    interruptions = []
    for path in sorted((DIRECTORY / "validation-meta").glob("INTERRUPTED*.json")):
        e = read(path)
        interruptions.append(dict(source=url(path), sha256=hashlib.sha256(path.read_bytes()).hexdigest(), **e))
        executions.append(dict(host="avx10", tier="full", campaign=e["campaign"],
            seconds=e["elapsed_seconds"], cases=e["persisted_cases"], source=url(path), status="interrupted"))
    executed_counts = Counter()
    for e in executions:
        executed_counts[e["campaign"]] += e["cases"]
    if executed_counts != expected | dict(refinement_latency=46):
        raise ValueError(f"Execution accounting differs from saved cases: {dict(executed_counts)}")
    runtime = {host: dict(full_seconds=sum(e["seconds"] for e in executions if e["host"] == host and e["tier"] == "full"),
                         full_allowance_seconds=1800)
               for host in ("avx10", "naamah")}
    for r in runtime.values():
        r["within_full_allowance"] = r["full_seconds"] <= r["full_allowance_seconds"]
    digest = hashlib.sha256()
    for path, _ in main + latency:
        digest.update(str(path.relative_to(DIRECTORY)).encode() + b"\0" + path.read_bytes())
    host_digest = hashlib.sha256()
    for path, r in latency:
        sidecar = path.with_name(f"{r['seed']}.host.json")
        host_digest.update(str(sidecar.relative_to(DIRECTORY)).encode() + b"\0" + sidecar.read_bytes())
    manifest = dict(report_header="simulated channel refinement validation", status="complete",
        git_commit=provenance["git_commit"], source_tree_sha256=provenance["source_tree_sha256"],
        source_archive_sha256=archive_hash, measurements_sha256=digest.hexdigest(),
        host_measurements_sha256=host_digest.hexdigest(),
        host_build_evidence_sha256=hashlib.sha256((DIRECTORY/"HOSTS.json").read_bytes()).hexdigest(),
        cases=len(main), counts=dict(counts), statuses=dict(Counter(r["status"] for _, r in main)),
        latency_cases=len(latency), host_latency_statuses=dict(Counter(t["status"] for t in timing)),
        seeds=list(SEEDS), deterministic_repeats=len(repeats), unchanged_baseline_comparisons=unchanged,
        ctest={h: "20/20" for h in ("avx10", "naamah")}, python_harness_tests=14,
        python_cli_serialization_cases=len(cli["cases"]),
        runtime=runtime, interruptions=interruptions,
        power_audit=power_manifest,
        power_measurements_sha256=power_digest.hexdigest(),
        simulated_followup_hours=sum(r["parameters"]["duration_s"] for _, r in follow)/3600,
        scope="Legacy noise calibration; matched diversity power controls, no equal-power claim across waveform families, route forecast or worldwide patent clearance")
    return dict(manifest=manifest, rows=rows, screens=screens, noise=noise, delays=delays, latency=timing,
                defects=defects, executions=executions)


def report(data):
    m = data["manifest"]; rows = data["rows"]
    lines = ["# Goblin Cannon simulated channel — BCH, frequency diversity and training cadence", "", compact_markdown(), "",
        "QPSK and 8-PSK reuse the existing shortened BCH(58,40,7) payload code. Diversity now exposes branch width, center separation and full-power lower/upper controls through fiber/gRPC. Pilot spacing and periodic full retraining use the existing controls. Carrier correction is off; RLS and sample-clock recovery remain on.", "",
        f"{m['cases']} AVX-512 cases; {m['latency_cases']} serial quiet-host latency cases; 20/20 CTest tests on both hosts; 14 harness checks; three byte-identical repeats; {m['unchanged_baseline_comparisons']} unchanged prior-configuration comparisons. A separate audit of saved waveform power adds 60 quick assertions: 54 pass and six xfail.", "",
        "All primary comparisons use 10/24 kHz, the unchanged legacy 30 dB nominal noise reference, and three seeds. Quiet/moderate/disturbed traces last 300/300/100 seconds per seed. Ranges are seed observations, not confidence intervals. BCH changes the payload code rate from 1/2 to 40/58; goodput gain is not an equal-rate coding-gain claim.", "",
        "**Power calibration defect:** the measured waveform power disagrees with the harness's nominal noise reference. The RRC transmitter does not apply the sample-energy normalization assumed by that reference; diversity gain compensation also raises actual power by about 2.5× versus full-band BPSK. These results cannot establish equal-power cross-family performance or an actual 30 dB operating point. The 54 matched lower/upper/both power checks pass; six explicit assertions retain the two defects as xfails. [Power measurements and failing assertions](power-audit/SUMMARY.md).", ""]
    lines += ["The offered stream is 100 messages/s across 16 keys. Quiet results can be source-limited; they do not establish unrestricted channel capacity. Delivery silence includes startup and the right-censored trace tail.", "",
              "## Simulated channel — measured findings", ""]
    for preset_name in ("quiet", "moderate", "disturbed"):
        selected = [r for r in rows if r["bandwidth"] == 24000 and r["preset"] == preset_name]
        by_variant = {r["variant"]: r for r in selected}
        mean = lambda r: sum(r["fresh_goodput"])/len(r["fresh_goodput"])
        best = max(selected, key=mean)
        qpsk, reference = by_variant["qpsk_bch"], by_variant["qpsk_soft"]
        diversity = max((r for r in selected if r["experiment"] == "diversity" and r["variant"].endswith("_both")), key=mean)
        lower = by_variant[diversity["variant"].replace("_both", "_lower")]
        upper = by_variant[diversity["variant"].replace("_both", "_upper")]
        lines += [f"- **24 kHz {preset_name}**: highest observed mean fresh goodput is {best['label']}, **{spread(best['fresh_goodput'])} bit/s**, with longest gaps {spread(best['silence'],.001,3)} s.",
            f"  QPSK+BCH gives {spread(qpsk['fresh_goodput'])} fresh bit/s versus {spread(reference['fresh_goodput'])} for soft QPSK.",
            f"  Best observed two-copy spacing ({diversity['label']}) gives {spread(diversity['fresh_goodput'])} fresh bit/s; its matched lower/upper full-power controls give {spread(lower['fresh_goodput'])} / {spread(upper['fresh_goodput'])}."]
    lines += ["", "These rankings describe the measured grids. They do not introduce an acceptance threshold, adaptive on-air mode selection or a claim that a severe channel is dependable.", ""]
    for name, title in (("coding", "1. BCH combinations"), ("diversity", "2. Frequency spacing with matched power controls"), ("cadence", "3. Pilot and full-retraining cadence")):
        lines += [f"## Simulated channel — {title}", "",
            "| Band / preset | Configuration | Useful bit/s | Fresh bit/s | Delivered / framed | Freshness p99.9 ms | Longest silence s | Seed records |",
            "| --- | --- | ---: | ---: | ---: | ---: | ---: | --- |"]
        selected = [r for r in rows if r["experiment"] == name or (name == "cadence" and r["variant"] in ("bpsk_bch", "qpsk_bch"))]
        for r in selected:
            links = " / ".join(f"[{s}]({u})" for s,u in zip(SEEDS,r["sources"]))
            lines.append(f"| {r['bandwidth']//1000} kHz / {r['preset']} | {r['label']} | {spread(r['goodput'])} | {spread(r['fresh_goodput'])} | {spread(r['delivery'],100)}% | {spread(r['freshness'])} | {spread(r['silence'],.001,3)} | {links} |")
        lines.append("")
    lines += ["## Simulated channel — diversity controls and limitations", "",
        "Every new branch uses 40% of the allowed audio bandwidth with the tested 0.25 RRC rolloff. Other rolloffs are outside this spectral-spacing validation. Separations are B/2, B/2 + 137 Hz and 0.55B + 137 Hz. Both-copy runs split total power equally; lower/upper controls each use that full power at the same symbol rate, branch width, equalizer geometry and framing. Measured power matches among these diversity cases, but is about 2.5× full-band BPSK because of the retained calibration defect. Two-copy occupied span changes with separation but stays within the same 10/24 kHz allocation. The controls occupy one branch; they are not full-band capacity controls.", "",
        "All copies traverse one shared Watterson channel. Each JSON records analytical complex-gain correlation at the centers, using the actual rounded sample delay. Correlation is not assumed zero. Additional ten-second message screens use 2.75/3.25 ms at 10 Hz and 6.75/7.25 ms at 30 Hz; these are sensitivity checks, not ITU presets. No delay, spacing or seed was selected after observing the result.", "",
        "| Band | Separation | Width per copy | Preset delay | Center correlation magnitude |",
        "| --- | ---: | ---: | ---: | ---: |"]
    for r in rows:
        if r["experiment"] == "diversity" and r["variant"].endswith("_both"):
            d = r["diversity"]
            lines.append(f"| {r['bandwidth']//1000} kHz | {d['center_separation_hz']:.0f} Hz | {d['branch_bandwidth_hz']:.0f} Hz | {r['preset']} | {d['center_response_correlation_magnitude']:.6f} |")
    lines += ["", "## Simulated channel — airtime costs", "",
        "Five fixed schedules are compared: pilot pairs after 16/32/64 payload symbols with full retraining every 16 frames; then retraining every 4/16/64 frames with pilots every 32 symbols. Each frame is 64 payload symbols. Full retraining includes acquisition, the declared training sequence, protected header and startup pilots. It does not reset FEC or the cipher. Longer equalizer spans retain the same physical path-delay coverage.", "",
        "| Band / preset | Configuration | Training symbols | Complete segment ms | Payload airtime fraction |",
        "| --- | --- | ---: | ---: | ---: |"]
    for r in rows:
        if r["experiment"] == "cadence" or r["variant"] in ("bpsk_bch", "qpsk_bch"):
            c = r["cadence"]
            lines.append(f"| {r['bandwidth']//1000} kHz / {r['preset']} | {r['label']} | {r['training_symbols']} | {c['segment_ms']:.3f} | {c['payload_airtime_fraction']:.3%} |")
    lines += ["", "## Simulated channel — software latency", "",
        "Measured serially on naamah with the 3 ms moderate-channel equalizer spans and a null channel. Source-to-sink host time includes paced one-millisecond audio blocks, CPU and scheduler timing; no physical audio device is modeled. Per-message subtraction uses a one-sample reference with the same coding, framing and selected source messages. Diversity combining wait is disabled only in that reference and charged as added buffering. The 2.1 ms allowance applies to added p99.9. Transmission, training and modem residence remain visible separately. A 12-second run provides a limited tail sample; it is not a production latency guarantee.", "",
        "| Band | Configuration | Delivered | Added p99.9 ms | Total p99.9 ms | Intrinsic p50 / p99.9 ms | Result |",
        "| --- | --- | ---: | ---: | ---: | --- | --- |"]
    fmt = lambda v: "unobserved" if v is None else f"{v:.3f}"
    for r in data["latency"]:
        lines.append(f"| {r['bandwidth']//1000} kHz | [{r['label']}]({r['source']}) | {r['delivered']} | {fmt(r['added']['p99_9'])} | {fmt(r['total']['p99_9'])} | {fmt(r['reference']['p50'])} / {fmt(r['reference']['p99_9'])} | {r['status']} |")
    lines += ["", "## Simulated channel — Defects found", ""]
    lines += [f"- [{d['case']}]({d['source']}) — {d['assertion']}: {d['reason']}" for d in data["defects"]] or ["No new assertion failures in this campaign."]
    lines += ["", "The power defects affect interpretation of earlier SNR and cross-waveform reports too. No archived measurement has been rewritten. The modem and simulator remain unchanged by this audit; correcting calibration and rerunning absolute-SNR comparisons remains a separate fix.", "",
        "Existing AES-CTR/CRC authentication and restart findings, cross-key starvation, missing recordings and open thresholds remain in the earlier audit. Correct payloads in these tests do not establish AEAD security.", "",
        "## Simulated channel — Open thresholds", "",
        "No new channel acceptance threshold is invented: SNR, polar delivery and cadence results are characterization. Null-channel bit integrity and the approved 2.1 ms budget are assertions. Earlier unapproved thresholds remain open:", "",
        "| ID | Status | Proposed value / approach | Reason |", "| --- | --- | --- | --- |"]
    for key, (proposal, reason) in OPEN_THRESHOLDS.items():
        lines.append(f"| {key} | THRESHOLD_TBD | {proposal} | {reason} |")
    lines += ["", "## Simulated channel — questions for Adam", "",
        "- The power audit exposes an inherited SNR-reference defect and diversity gain compensation that defeats equal actual power across widths. These are retained as failing assertions under the test brief. Correct calibration and rerun absolute-SNR and cross-waveform comparisons before choosing an RF operating point.",
        "- The new width/separation controls are qualified at the existing 0.25 RRC rolloff. Other rolloffs need a separate spectral-spacing validation."]
    lines += ["", "## Simulated channel — runtime and provenance", "",
        "| Host / tier | Selection | Saved cases | Seconds | Execution |", "| --- | --- | ---: | ---: | --- |"]
    for e in data["executions"]:
        lines.append(f"| {e['host']} / {e['tier']} | [{e['campaign']}]({e['source']}) | {e['cases']} | {e['seconds']:.3f} | {e['status']} |")
    for host in ("avx10", "naamah"):
        full = sum(e["seconds"] for e in data["executions"] if e["host"] == host and e["tier"] == "full")
        lines.append(f"\n{host} full selections total {full:.3f} seconds: {'within' if full <= 1800 else 'EXCEEDS'} the 1800-second full-tier allowance. All declared cases and durations were retained.")
    if m["interruptions"]:
        lines += ["", "The initial sustained runner lost its SSH output connection and stopped collecting results while queued workers continued. The recorded interrupted interval is included above. Only records not already saved were rerun with identical parameters; remote log redirection allowed the resumed runner to survive disconnection. Lost work and restart overhead are not represented as simulated channel improvement."]
    lines += ["", f"The sustained comparison covers {m['simulated_followup_hours']:.3f} simulated hours. These are fixed-SNR traces, not a forecast for the route peaking near 71°N. The 24 kHz Watterson use exceeds the Recommendation's approximately 12 kHz validated scope; STAC usable time remains the documented local one-second delivery-window proxy.", "",
        "[Patent scope and implementation boundaries](../encoding-improvements/PATENT_SCREEN.md) remain US publications plus discovered international families. This work combines the existing conventional BCH/PSK pipeline, fixed spectral duplication and existing supervised pilot training. It adds no modern LDPC, learned demapper, CROW or specialized receiver method; the engineering screen is not worldwide legal clearance.", "",
        f"Base commit `{m['git_commit']}`; source digest `{m['source_tree_sha256']}`. [Source snapshot](source-snapshot.tar.gz), [source manifest](validation-meta/SOURCE.json), [all metrics](DATA.json), [validation](VALIDATION.json), [case tables](SUMMARY.md)."]
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--snapshot", action="store_true")
    args = parser.parse_args()
    if args.snapshot:
        snapshot()
        return
    data = load()
    save(DIRECTORY / "DATA.json", data)
    save(DIRECTORY / "VALIDATION.json", data["manifest"])
    (DIRECTORY / "REPORT.md").write_text(report(data))
    summary_path = DIRECTORY / "SUMMARY.md"
    summary = summary_path.read_text()
    start = summary.index("## Simulated channel — Defects found")
    end = summary.index("## Simulated channel — Open thresholds", start)
    defects = ["## Simulated channel — Defects found", "",
               "Modem cases and power-calibration assertions are reported separately. The latter audit the saved RF measurements; they do not add channel runs. [Power audit](power-audit/SUMMARY.md). [Combined runtime, including the interrupted runner](REPORT.md).", ""]
    defects += [f"- **xfail** [{d['case']}]({d['source']}) — {d['reason']}" for d in data["defects"]]
    summary_path.write_text(summary[:start] + "\n".join(defects) + "\n\n" + summary[end:])
    print(json.dumps(data["manifest"], indent=2))


if __name__ == "__main__":
    main()
