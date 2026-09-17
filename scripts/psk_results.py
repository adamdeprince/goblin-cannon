#!/usr/bin/env python3
"""Summarize the completed PSK simulated channel campaign from saved records."""
from __future__ import annotations

from collections import Counter
import hashlib
from html import escape
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/psk-improvements"
SEEDS = (7446529, 7446530, 7446531)
LABELS = {
    "qpsk_reference": "QPSK · QPSK header",
    "qpsk_bpsk_header": "QPSK · BPSK header",
    "bpsk_qpsk_header": "BPSK · QPSK header",
    "bpsk": "BPSK · BPSK header",
    "8psk_qpsk_header": "8-PSK · QPSK header",
    "8psk_bpsk_header": "8-PSK · BPSK header",
    "16qam_reference": "16-QAM · QPSK header",
    "64qam_reference": "64-QAM · QPSK header",
    "dbpsk": "DBPSK · BPSK header",
    "dqpsk": "DQPSK · BPSK header",
    "pi4_dqpsk": "π/4-DQPSK · BPSK header",
}


def read(path):
    return json.loads(path.read_text())


def records(directory):
    return [(p, read(p)) for p in sorted(directory.glob("*/[0-9]*.json"))
            if not p.name.endswith(".host.json")]


def url(path):
    return "https://github.com/adamdeprince/goblin-cannon/blob/main/" + str(path.relative_to(ROOT))


def spread(values, scale=1, precision=2):
    observed = [v * scale for v in values if v is not None]
    if not observed:
        return "Unobserved"
    low, high = min(observed), max(observed)
    value = f"{low:.{precision}f}" if low == high else f"{low:.{precision}f}–{high:.{precision}f}"
    return value + (" (some unobserved)" if len(observed) != len(values) else "")


def load():
    main, latency = records(DIRECTORY), records(DIRECTORY / "naamah-latency")
    counts = dict(Counter(r["parameters"]["campaign"] for _, r in main))
    if counts != {"psk_quick": 22, "psk_screen": 396, "psk_snr": 352, "psk_followup": 198}:
        raise ValueError(f"Incomplete PSK campaign: {counts}")
    if len(latency) != 44:
        raise ValueError(f"Incomplete quiet-host latency campaign: {len(latency)}/44")
    hashes = {r["parameters"]["source_tree_sha256"] for _, r in main + latency}
    commits = {r["parameters"]["git_commit"] for _, r in main + latency}
    if len(hashes) != 1 or len(commits) != 1:
        raise ValueError("Mixed source provenance in PSK campaign")
    if any(r["status"] not in ("pass", "characterized", "xfail") for _, r in main + latency):
        raise ValueError("Unreviewed PSK assertion failure")
    for path, r in main + latency:
        p = r["parameters"]
        if p["carrier_correction"] or not p["adaptive_equalization"] or not p["sample_clock_recovery"]:
            raise ValueError(f"PSK design boundary changed: {path}")
    lookup = {(r["test_name"], r["seed"]): (p, r) for p, r in main}
    rows, headers, papr, timing, noise = [], [], [], [], []
    for bw in (10000, 24000):
        for preset in ("quiet", "moderate", "disturbed"):
            for variant, label in LABELS.items():
                selected = [lookup[f"E2_psk_followup_{bw}_{variant}_high_lat_{preset}", s] for s in SEEDS]
                duration = 100 if preset == "disturbed" else 300
                if any(r["parameters"]["duration_s"] != duration for _, r in selected):
                    raise ValueError("Follow-up duration changed")
                rows.append(dict(bandwidth=bw, preset=preset, variant=variant, label=label, duration=duration,
                    goodput=[r["metrics"]["goodput_bps"] for _, r in selected],
                    delivery=[r["metrics"]["message_delivery_fraction_of_framed"] for _, r in selected],
                    freshness=[r["metrics"]["freshness_ms"]["p99_9"] for _, r in selected],
                    silence=[r["metrics"]["delivery_silence_ms"]["max"] for _, r in selected],
                    sources=[url(p) for p, _ in selected]))
            selected = [lookup[f"E2_psk_screen_{bw}_{v}_high_lat_{preset}", s]
                        for v in ("qpsk_reference", "qpsk_bpsk_header") for s in SEEDS]
            headers.append(dict(bandwidth=bw, preset=preset,
                goodput=[r["metrics"]["goodput_bps"] for _, r in selected],
                valid_headers=[r["observations"]["valid_headers"] for _, r in selected],
                sources=[url(p) for p, _ in selected]))
        for variant, label in LABELS.items():
            selected = [lookup[f"A2_psk_screen_{bw}_{variant}_high_lat_quiet", s] for s in SEEDS]
            papr.append(dict(bandwidth=bw, variant=variant, label=label,
                db=[r["observations"]["tx_papr_db"] for _, r in selected],
                sources=[url(p) for p, _ in selected]))
            for snr in range(0, 31, 2):
                p, r = lookup[f"C1_psk_snr_{bw}_{variant}_{snr}dB", SEEDS[0]]
                noise.append(dict(bandwidth=bw, variant=variant, snr=snr, ber=r["metrics"]["ber"],
                    coded_ber=r["metrics"]["coded_ber"], observed=r["metrics"]["bit_observation_fraction"],
                    frame_survival=r["metrics"]["frame_survival_fraction"], source=url(p)))
    for path, r in latency:
        sidecar = path.with_name(f"{r['seed']}.host.json")
        h = read(sidecar)
        if h["parameters"] != r["parameters"]:
            raise ValueError("Quiet-host latency sidecar parameters differ")
        o, p = h["observations"], r["parameters"]
        timing.append(dict(bandwidth=p["bandwidth_hz"], variant=p["psk_variant"],
            span="long" if "_long_" in r["test_name"] else "short", label=LABELS[p["psk_variant"]],
            added=o["host_added_software_latency_ms_percentiles"], total=o["host_latency_ms_percentiles"],
            reference=r["latency_reference"]["metrics"]["latency_ms"],
            status=o["added_software_latency_assertion"]["status"], source=url(sidecar)))
    repeated = records(DIRECTORY / "determinism")
    if len(repeated) != 3:
        raise ValueError("Three determinism repetitions are required")
    for p, r in repeated:
        original = lookup[r["test_name"], r["seed"]][0]
        if p.read_bytes() != original.read_bytes():
            raise ValueError(f"Canonical result differs on repetition: {p}")
    executions = [(p, read(p)) for directory in (DIRECTORY, DIRECTORY / "naamah-latency")
                  for p in sorted(directory.glob("EXECUTION-*.json"))]
    runtime = [dict(source=url(p), host="naamah" if "naamah-latency" in p.parts else "avx10",
                    tier=e["tier"], campaign=e["selection"]["campaign"], cases=e["executed_cases"],
                    seconds=e["elapsed_seconds"], allowance=e["budget_seconds"])
               for p, e in executions]
    digest = hashlib.sha256()
    for path, _ in main + latency:
        digest.update(str(path.relative_to(DIRECTORY)).encode()+b"\0"+path.read_bytes())
    manifest = dict(report_header="simulated channel PSK validation", campaign_status="complete",
        git_commit=commits.pop(), source_tree_sha256=hashes.pop(), seeds=list(SEEDS),
        source_revision_note="Base revision; source digest and archive identify the tested working tree.",
        source_archive_sha256=hashlib.sha256((DIRECTORY/"source-snapshot.tar.gz").read_bytes()).hexdigest(),
        campaign_counts=counts, main_cases=len(main), main_statuses=dict(Counter(r["status"] for _, r in main)),
        latency_cases=len(latency), latency_statuses=dict(Counter(r["status"] for _, r in latency)),
        host_latency_statuses=dict(Counter(r["status"] for r in timing)),
        main_host="avx10", latency_host="naamah", measurements_sha256=digest.hexdigest(),
        deterministic_repeats=3, simulated_followup_hours=sum(r["parameters"]["duration_s"] for _, r in main
            if r["parameters"]["campaign"]=="psk_followup")/3600,
        ctest={"avx10":"18/18", "naamah":"18/18"}, python_harness_tests=12,
        scope="Custom waveform, simulated channel; no CMA, PA headroom gain or route availability forecast.")
    hosts=read(DIRECTORY/"HOSTS.json")
    for host in ("avx10","naamah"):
        if hosts[host]["ctest_passed"]!=18 or hosts[host]["ctest_total"]!=18:
            raise ValueError(f"Incomplete regression evidence on {host}")
    if any(r["status"]!="pass" for r in timing):
        raise ValueError("Quiet-host latency failures need explicit review before publication")
    return dict(manifest=manifest, rows=rows, headers=headers, papr=papr, latency=timing, noise=noise, runtime=runtime)


def seed_links(sources):
    return " / ".join(f"[{s}]({u})" for s, u in zip(SEEDS, sources))


def write_report(data):
    d, rows = DIRECTORY, data["rows"]
    m = data["manifest"]
    indexed={(r["bandwidth"],r["preset"],r["variant"]):r for r in rows}
    qpsk=indexed[24000,"moderate","qpsk_reference"]
    bpsk=indexed[24000,"moderate","bpsk_qpsk_header"]
    psk8=indexed[10000,"quiet","8psk_qpsk_header"]
    qam16=indexed[10000,"quiet","16qam_reference"]
    quiet8=indexed[24000,"quiet","8psk_qpsk_header"]
    quiet16=indexed[24000,"quiet","16qam_reference"]
    disturbed=indexed[24000,"disturbed","bpsk"]
    disturbed_qpsk=indexed[24000,"disturbed","qpsk_reference"]
    added=[r["added"]["p99_9"] for r in data["latency"]]
    reference={r["variant"]:r["reference"]["p50"] for r in data["latency"] if r["bandwidth"]==24000 and r["span"]=="short"}
    lines = ["# Goblin Cannon simulated channel PSK comparison", "",
        "BPSK, BPSK-only header data, DBPSK, DQPSK and π/4-DQPSK are implemented. Existing 8-PSK is included in the matched comparison. Both endpoints configure the modes over fiber/gRPC. Carrier correction remains off; adaptive RLS equalization and sample-clock recovery remain on.", "",
        f"{m['main_cases']} AVX-512 cases; {m['latency_cases']} serial quiet-host latency cases; 18/18 CTest regressions on each host; 12 Python harness tests. Three representative canonical results repeat byte-for-byte. Full observations and parameters remain in [SUMMARY.md](SUMMARY.md) and [quiet-host SUMMARY.md](naamah-latency/SUMMARY.md).", "",
        "## Simulated channel: findings", "",
        f"- On 24 kHz moderate fading, BPSK payload with a QPSK header delivers **{spread(bpsk['goodput'])} bit/s**, versus **{spread(qpsk['goodput'])} bit/s** for QPSK. It delivers **{spread(bpsk['delivery'],100)}%** of framed messages, versus **{spread(qpsk['delivery'],100)}%**. BPSK improves goodput in all three matched seeds.",
        f"- BPSK reduces each moderate run's longest delivery silence to **{spread(bpsk['silence'],.001,3)} s**, versus **{spread(qpsk['silence'],.001,3)} s** for QPSK. Its source-to-delivery freshness p99.9 increases to **{spread(bpsk['freshness'])} ms** from **{spread(qpsk['freshness'])} ms**: more reliable delivery costs airtime.",
        "- BPSK header data reduces QPSK goodput in all three 24 kHz moderate seeds. The current recovery implementation already validates headers there; doubling header airtime does not remove the remaining payload losses.",
        "- DBPSK, DQPSK and π/4-DQPSK do not improve moderate-channel goodput over their matching coherent BPSK-header controls at either bandwidth. They still depend on coherent acquisition, headers and pilot lock checks in this implementation.",
        f"- 8-PSK is the best measured 10 kHz quiet configuration: **{spread(psk8['goodput'])} bit/s**, versus **{spread(qam16['goodput'])} bit/s** for 16-QAM. At 24 kHz quiet, 8-PSK delivers **{spread(quiet8['delivery'],100)}%** of framed messages, versus **{spread(quiet16['delivery'],100)}%** for 16-QAM; QPSK retains slightly higher useful goodput than 8-PSK.",
        "- Four-bit 16-QAM survives the quiet simulated channel at both bandwidths. The tables retain its remaining losses rather than treating survival as an acceptance threshold.",
        f"- On 24 kHz disturbed fading, BPSK payload and header deliver **{spread(disturbed['goodput'])} bit/s**, versus **{spread(disturbed_qpsk['goodput'])} bit/s** for QPSK. Delivery remains sparse: **{spread(disturbed['delivery'],100)}%** of framed messages, with longest silences of **{spread(disturbed['silence'],.001,3)} s**. At 10 kHz disturbed, even the new modes deliver at most isolated messages.",
        f"- All 44 quiet-host configurations pass the added-processing allowance: p99.9 **{spread(added,precision=3)} ms**. At 24 kHz with short equalizer spans, the intrinsic reference median is **{reference['bpsk_qpsk_header']:.3f} ms** for BPSK with a QPSK header versus **{reference['qpsk_reference']:.3f} ms** for QPSK. The airtime cost is separate from the 2.1 ms software allowance.", "",
        "## Simulated channel: sustained delivery", "",
        "All eleven configurations use the same three seeds at 30 dB nominal SNR. Quiet/moderate/disturbed use 1/3/7 ms two-path delay spread and 0.5/10/30 Hz Gaussian Doppler spread, respectively. The follow-up uses 300/300/100 seconds per seed (12.833 simulated hours altogether). Ranges are seed minima/maxima, not confidence intervals. These runs do not replace the previous 6,000-second quiet campaign or establish an F.1487 BER operating limit.", "",
        "Useful goodput counts delivered application bits, not coded RF throughput. Delivery fraction divides by messages claimed by the framer, excluding source auction rejections. Freshness is source creation to delivery; silence includes startup and the censored end of each run.", "",
        "| Band | Preset | Payload / header | Useful bit/s | Delivered / framed | Freshness p99.9 ms | Longest silence s | Seeds |",
        "| --- | --- | --- | ---: | ---: | ---: | ---: | --- |"]
    for r in rows:
        lines.append(f"| {r['bandwidth']//1000} kHz | {r['preset']} | {r['label']} | {spread(r['goodput'])} | {spread(r['delivery'],100)}% | {spread(r['freshness'])} | {spread(r['silence'],.001,3)} | {seed_links(r['sources'])} |")
    lines += ["", "## Simulated channel: header-only experiment", "",
        "QPSK payload and equalizer geometry stay fixed. BPSK header data doubles the protected header from 166 to 332 air symbols; acquisition, training and embedded probes remain QPSK. Header counts are per ten-second trace, not conditional success probabilities: longer headers also reduce the number of available segments. The updated receiver already validates headers on moderate fading.", "",
        "| Band | Preset | QPSK-header bit/s | BPSK-header bit/s | Valid headers, QPSK / BPSK | Records, QPSK then BPSK |",
        "| --- | --- | ---: | ---: | --- | --- |"]
    for r in data["headers"]:
        lines.append(f"| {r['bandwidth']//1000} kHz | {r['preset']} | {spread(r['goodput'][:3])} | {spread(r['goodput'][3:])} | {spread(r['valid_headers'][:3],precision=0)} / {spread(r['valid_headers'][3:],precision=0)} | {seed_links(r['sources'][:3])}; {seed_links(r['sources'][3:])} |")
    lines += ["", "## Simulated channel: noise and waveform peaks", "",
        "[C1.csv](C1.csv) retains every ten-second 0–30 dB AWGN point in 2 dB steps, at both bandwidths, with raw and post-Viterbi BER and observation fractions. These are empirical curves at equal nominal symbol energy, not certified Eb/N0 limits. Missing observations are not zero BER.", "",
        "PAPR below is measured over each finite clean pulse-shaped waveform, including acquisition, training, headers, pilots and tails. A constant-modulus symbol alphabet does not make the filtered audio envelope constant. No PA model, backoff improvement or extra transmit power is assumed.", "",
        "| Band | Configuration | Measured PAPR dB | Seed records |", "| --- | --- | ---: | --- |"]
    for r in data["papr"]:
        lines.append(f"| {r['bandwidth']//1000} kHz | {r['label']} | {spread(r['db'])} | {seed_links(r['sources'])} |")
    lines += ["", "## Simulated channel: quiet-host latency", "",
        "Measured serially on naamah (AVX2). The 2.1 ms assertion applies to added processing/buffering, paired per message against a one-sample production-stack reference. Total source-to-sink and intrinsic reference latency retain modem/FEC, serialization and startup. Stage-call distributions and serialization estimates are in the linked records. A physical audio device is not modeled. All measured host observations remain outside canonical seed-equality checks.", "",
        "| Band | Configuration | Span | Added p99.9 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Result |",
        "| --- | --- | --- | ---: | ---: | ---: | --- |"]
    for r in data["latency"]:
        lines.append(f"| {r['bandwidth']//1000} kHz | [{r['label']}]({r['source']}) | {r['span']} | {r['added']['p99_9']:.3f} | {r['total']['p99_9']:.3f} | {r['reference']['p99_9']:.3f} | {r['status']} |")
    lines += ["", "## Simulated channel: Defects found", "",
        "No new functional acceptance failures were found in this campaign. Characterization losses remain visible above; they are not relabeled passes. Existing crypto, scheduler and impairment xfails remain in the [prior recovery report](../recovery-improvements/SUMMARY.md); this selection does not retest or resolve them.", "",
        "## Simulated channel: Open thresholds", "",
        "No new BER, goodput, outage or freshness acceptance threshold is imposed. All previously open THRESHOLD_TBD margins remain open in [the threshold register](../../tests/simulated_channel/QUESTIONS.md). The null-channel assertions require exact symbols, complete frame boundaries and sync; host latency uses the user-specified 2.1 ms budget.", "",
        "## Simulated channel: runtime and limits", "",
        "| Host | Selection | Cases executed | Wall seconds | Tier allowance seconds |", "| --- | --- | ---: | ---: | ---: |"]
    for r in data["runtime"]:
        lines.append(f"| {r['host']} | [{r['campaign']}]({r['source']}) | {r['cases']} | {r['seconds']:.2f} | {r['allowance']} ({r['tier']}) |")
    lines += ["", "Serial B5 includes 22 twelve-second short-span runs and necessarily exceeds the 120-second quick-tier budget. No duration or grid was reduced. Campaign selections are not a rerun of the entire original full tier; the manual soak and unavailable recorded-noise tests remain separate.", "",
        "Differential detection uses adjacent equalized complex observations, with absolute pilots resetting the reference. It adds no carrier-frequency estimator or CMA. Acquisition and header decoding still require the existing coherent equalizer; differential payloads alone cannot remove those limits or compensate for delay spread. π/4-DQPSK follows [Keysight's phase increments](https://helpfiles.keysight.com/csg/89600B/Webhelp/Subsystems/digdemod/content/dlg_digdemod_fmt_pi4dqpsk.htm).", "",
        "The 71.533836°N great-circle geometry is unchanged: its idealized sky path is 39.502838 ms and its idealized fiber floor is 55.610261 ms. Those geometric calculations do not predict route availability or actual cable delay. The 24 kHz Watterson model remains an extrapolation beyond F.1487's approximately 12 kHz validation scope. Fixed-SNR traces omit a time-dependent ionospheric link budget.", "",
        f"Base commit `{m['git_commit']}`; tested source SHA-256 `{m['source_tree_sha256']}`. [Source snapshot](source-snapshot.tar.gz), [validation manifest](VALIDATION.json), [host/build evidence](HOSTS.json).", ""]
    (d/"REPORT.md").write_text("\n".join(lines))
    (d/"VALIDATION.json").write_text(json.dumps(m,indent=2,sort_keys=True)+"\n")


if __name__ == "__main__":
    write_report(load())
