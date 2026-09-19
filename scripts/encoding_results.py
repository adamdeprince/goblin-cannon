#!/usr/bin/env python3
"""Generate the conventional-encoding simulated channel report from saved results."""
from __future__ import annotations
from channel_description import compact_markdown

from collections import Counter
import hashlib
import json
from pathlib import Path
from psk_results import read, records, url, spread, seed_links

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/encoding-improvements"
SEEDS = (7446529, 7446530, 7446531)
LABELS = {
    "qpsk_reference": "QPSK reference",
    "bpsk_reference": "BPSK reference",
    "bpsk_bpsk_header_reference": "BPSK + BPSK header reference",
    "bpsk_soft_bpsk_header": "Soft BPSK + BPSK header",
    "16qam_reference": "16-QAM reference",
    "qpsk_soft": "Soft QPSK",
    "bpsk_soft": "Soft BPSK",
    "16qam_soft": "Soft 16-QAM",
    "bpsk_k9_half": "Soft BPSK · K9 rate 1/2",
    "bpsk_k9_third": "Soft BPSK · K9 rate 1/3",
    "bpsk_walsh8": "Soft BPSK · Walsh 8",
    "bpsk_bch": "BPSK · BCH (58,40), hard decoder",
    "bpsk_interleave32": "Soft BPSK · 32-bit interleaver",
    "bpsk_interleave256": "Soft BPSK · 256-bit interleaver",
    "bpsk_interleave2048": "Soft BPSK · 2048-bit interleaver",
    "bpsk_diversity": "BPSK · two-subband diversity",
    "bpsk_halfband_control": "BPSK · half-band control",
    "fsk4_guard8": "4-FSK · 8 ms guard",
    "fsk8_guard8": "8-FSK · 8 ms guard",
    "fsk4_guard4": "4-FSK · 4 ms guard",
    "fsk8_guard4": "8-FSK · 4 ms guard",
}


def load():
    main = records(DIRECTORY)
    latency = records(DIRECTORY / "naamah-latency")
    counts = dict(Counter(r["parameters"]["campaign"] for _, r in main))
    expected = dict(encoding_quick=84, encoding_screen=756, encoding_snr=672, encoding_followup=378)
    if counts != expected or len(latency) != 42:
        raise ValueError(f"Incomplete simulated channel campaign: {counts}, latency={len(latency)}")
    provenance = read(DIRECTORY / "validation-meta/SOURCE.json")
    for path, r in main + latency:
        p = r["parameters"]
        required = {"channel_model", "delay_spread_ms", "doppler_spread_hz", "path_gains_db",
                    "snr_db", "cw_hz", "cw_sir_db", "data_sir_db", "interferer_start_s",
                    "frame_symbols", "fec", "interleaver", "stage_order", "seed",
                    "git_commit", "source_tree_sha256"}
        if required - p.keys():
            raise ValueError(f"Incomplete result parameters: {path}: {sorted(required - p.keys())}")
        if p["seed"] != r["seed"]:
            raise ValueError(f"Result and parameter seeds differ: {path}")
        if p["carrier_correction"] or p["execution"] != "simulated channel":
            raise ValueError(f"Design boundary changed: {path}")
        if p["source_tree_sha256"] != provenance["source_tree_sha256"] or p["git_commit"] != provenance["git_commit"]:
            raise ValueError(f"Mixed source provenance: {path}")
        if r["status"] not in ("characterized", "pass", "xfail", "THRESHOLD_TBD"):
            raise ValueError(f"Unreviewed failed result: {path}: {r['status']}")
        if p["encoding_variant"] not in LABELS or p["seed"] not in SEEDS:
            raise ValueError(f"Unknown configuration or seed: {path}")
        if p["audio_waveform"].startswith("fsk"):
            if p["adaptive_equalization"] or p["sample_clock_recovery"]:
                raise ValueError("FSK incorrectly claims RLS/Gardner tracking")
        elif not (p["adaptive_equalization"] and p["sample_clock_recovery"]):
            raise ValueError("Coherent receiver tracking unexpectedly disabled")
        if p["campaign"] == "encoding_followup":
            if p["duration_s"] != (100 if p["doppler_spread_hz"] == 30 else 300):
                raise ValueError("Follow-up duration changed")
        if p["interleaver_rows"] and p["interleaver"] == "none":
            raise ValueError("Unrecorded interleaver")
    lookup = {(r["test_name"], r["seed"]): (p, r) for p, r in main}
    if len(lookup) != len(main):
        raise ValueError("Duplicate measurement identity")
    baseline_comparisons = 0
    old_variants = dict(qpsk_reference="qpsk_reference", bpsk_reference="bpsk_qpsk_header",
                        bpsk_bpsk_header_reference="bpsk", **{"16qam_reference": "16qam_reference"})
    for band in (10000, 24000):
        for preset in ("quiet", "moderate", "disturbed"):
            for variant, old_variant in old_variants.items():
                for seed in SEEDS:
                    current = lookup[f"E2_encoding_followup_{band}_{variant}_high_lat_{preset}", seed][1]
                    previous = read(ROOT / "results/psk-improvements" /
                                    f"E2_psk_followup_{band}_{old_variant}_high_lat_{preset}" / f"{seed}.json")
                    for metric in ("goodput_bps", "message_delivery_fraction_of_framed", "freshness_ms", "delivery_silence_ms"):
                        if current["metrics"][metric] != previous["metrics"][metric]:
                            raise ValueError(f"Legacy comparison changed: {band} {preset} {variant} {seed} {metric}")
                    baseline_comparisons += 1
    rows, rf, papr, noise, timing = [], [], [], [], []
    for band in (10000, 24000):
        for preset in ("quiet", "moderate", "disturbed"):
            for variant, label in LABELS.items():
                selected = [lookup[f"E2_encoding_followup_{band}_{variant}_high_lat_{preset}", s] for s in SEEDS]
                rows.append(dict(bandwidth=band, preset=preset, variant=variant, label=label,
                    duration=100 if preset == "disturbed" else 300,
                    goodput=[r["metrics"]["goodput_bps"] for _, r in selected],
                    fresh_goodput=[r["metrics"]["fresh_goodput_bps"] for _, r in selected],
                    delivery=[r["metrics"]["message_delivery_fraction_of_framed"] for _, r in selected],
                    freshness=[r["metrics"]["freshness_ms"]["p99_9"] for _, r in selected],
                    silence=[r["metrics"]["delivery_silence_ms"]["max"] for _, r in selected],
                    corrupt=[r["observations"]["corrupted_messages_delivered"] for _, r in selected],
                    duplicate=[r["observations"]["duplicate_messages_delivered"] for _, r in selected],
                    superseded=[r["observations"]["superseded_messages_consumed"] for _, r in selected],
                    queue=[r["observations"]["queue_depth_max"] for _, r in selected],
                    sources=[url(path) for path, _ in selected]))
                selected_rf = [lookup[f"A2_encoding_screen_{band}_{variant}_high_lat_{preset}", s] for s in SEEDS]
                rf.append(dict(bandwidth=band,preset=preset,variant=variant,label=label,
                    ber=[r["metrics"]["ber"] for _, r in selected_rf],
                    observed=[r["metrics"]["bit_observation_fraction"] for _, r in selected_rf],
                    survival=[r["metrics"]["frame_survival_fraction"] for _, r in selected_rf],
                    duration=selected_rf[0][1]["parameters"]["duration_s"],
                    sources=[url(path) for path, _ in selected_rf]))
                if preset == "quiet":
                    papr.append(dict(bandwidth=band,variant=variant,label=label,
                        db=[r["observations"]["tx_papr_db"] for _, r in selected_rf],
                        power=[r["observations"]["tx_mean_sample_power"] for _, r in selected_rf],
                        sources=[url(path) for path, _ in selected_rf]))
        for variant, label in LABELS.items():
            for snr in range(0,31,2):
                path,r=lookup[f"C1_encoding_snr_{band}_{variant}_{snr}dB",SEEDS[0]]
                noise.append(dict(bandwidth=band,variant=variant,snr=snr,ber=r["metrics"]["ber"],
                    coded_ber=r["metrics"]["coded_ber"],compared=r["observations"].get("coded_bits_compared",0),
                    observed=r["metrics"]["bit_observation_fraction"],frame_survival=r["metrics"]["frame_survival_fraction"],
                    duration=r["parameters"]["duration_s"],source=url(path)))
    defects=[]
    for path,r in main+latency:
        for a in r["assertions"]:
            if a["status"]=="xfail":
                defects.append(dict(case=r["test_name"],assertion=a["assertion"],reason=a["reason"],source=url(path)))
    for path,r in latency:
        sidecar=path.with_name(f"{r['seed']}.host.json")
        h=read(sidecar);o=h["observations"];p=r["parameters"]
        if h["parameters"]!=p:
            raise ValueError("Host sidecar parameters differ")
        a=o["added_software_latency_assertion"]
        if a["status"] not in ("pass","xfail"):
            raise ValueError(f"Unreviewed host latency failure: {sidecar}")
        if a["status"]=="xfail":
            defects.append(dict(case=r["test_name"],assertion="host p99.9 <= 2.1 ms",reason=a["reason"],source=url(sidecar)))
        timing.append(dict(bandwidth=p["bandwidth_hz"],variant=p["encoding_variant"],label=LABELS[p["encoding_variant"]],
            added=o["host_added_software_latency_ms_percentiles"],total=o["host_latency_ms_percentiles"],
            reference=r["latency_reference"]["metrics"]["latency_ms"],
            delivered=r["observations"]["messages_delivered"],status=a["status"],reason=a["reason"],
            tx=o.get("host_tx_per_block_ms_percentiles"),rx=o.get("host_rx_per_block_ms_percentiles"),
            source=url(sidecar),record=url(path)))
    repeated=records(DIRECTORY/"determinism")
    if len(repeated)!=3:
        raise ValueError("Three byte-identical repeated results are required")
    for path,r in repeated:
        original=lookup[r["test_name"],r["seed"]][0]
        if path.read_bytes()!=original.read_bytes():
            raise ValueError(f"Determinism failure: {path}")
    hosts=read(DIRECTORY/"HOSTS.json")
    for host in ("avx10","naamah"):
        if hosts[host]["ctest_passed"]!=20 or hosts[host]["ctest_total"]!=20:
            raise ValueError(f"Incomplete CTest evidence on {host}")
    cli = read(DIRECTORY/"validation-meta/PYTHON_GRPC.json")
    if len(cli["cases"]) != 12 or any(c["status"] != "pass" for c in cli["cases"]):
        raise ValueError("Incomplete CLI/gRPC serialization evidence")
    if cli["source_tree_sha256"] != provenance["source_tree_sha256"]:
        raise ValueError("CLI/gRPC serialization used a different source snapshot")
    archive_hash=hashlib.sha256((DIRECTORY/"source-snapshot.tar.gz").read_bytes()).hexdigest()
    if archive_hash!=provenance["archive_sha256"]:
        raise ValueError("Source archive checksum differs")
    digest=hashlib.sha256()
    for path,_ in main+latency:
        digest.update(str(path.relative_to(DIRECTORY)).encode()+b"\0"+path.read_bytes())
    host_digest = hashlib.sha256()
    for path, r in latency:
        sidecar = path.with_name(f"{r['seed']}.host.json")
        host_digest.update(str(sidecar.relative_to(DIRECTORY)).encode()+b"\0"+sidecar.read_bytes())
    executions=[]
    for folder,host in ((DIRECTORY,"avx10"),(DIRECTORY/"naamah-latency","naamah")):
        for path in sorted(folder.glob("EXECUTION-*.json")):
            e=read(path)
            executions.append(dict(host=host,campaign=e["selection"]["campaign"],tier=e["tier"],
                cases=e["executed_cases"],seconds=e["elapsed_seconds"],budget=e["budget_seconds"],source=url(path)))
    runtime_totals = []
    for host in ("avx10", "naamah"):
        for tier, budget in (("quick", 120), ("full", 1800)):
            selected = [e for e in executions if e["host"] == host and e["tier"] == tier]
            if selected:
                seconds = sum(e["seconds"] for e in selected)
                runtime_totals.append(dict(host=host, tier=tier, cases=sum(e["cases"] for e in selected),
                    seconds=seconds, budget=budget, within_budget=seconds <= budget))
    manifest=dict(report_header="simulated channel conventional encoding validation",campaign_status="complete",
        git_commit=provenance["git_commit"],source_tree_sha256=provenance["source_tree_sha256"],
        source_archive_sha256=archive_hash,measurements_sha256=digest.hexdigest(),
        host_measurements_sha256=host_digest.hexdigest(),
        host_build_evidence_sha256=hashlib.sha256((DIRECTORY/"HOSTS.json").read_bytes()).hexdigest(),
        expected_failures_sha256=hashlib.sha256((ROOT/"tests/simulated_channel/expected_failures.json").read_bytes()).hexdigest(),
        campaign_counts=counts,main_cases=len(main),main_statuses=dict(Counter(r["status"] for _,r in main)),
        latency_cases=len(latency),latency_statuses=dict(Counter(r["status"] for _,r in latency)),
        host_latency_statuses=dict(Counter(r["status"] for r in timing)),seeds=list(SEEDS),
        deterministic_repeats=3,ctest={"avx10":"20/20","naamah":"20/20"},python_harness_tests=13,
        unchanged_prior_campaign_comparisons=baseline_comparisons,
        python_cli_serialization_cases=len(cli["cases"]),
        simulated_followup_hours=sum(r["parameters"]["duration_s"] for _,r in main if r["parameters"]["campaign"]=="encoding_followup")/3600,
        scope="Fixed-power simulated channels, conventional algorithms; public-record patent screen, no worldwide patent clearance or route-availability forecast.")
    return dict(manifest=manifest,rows=rows,rf=rf,papr=papr,noise=noise,latency=timing,defects=defects,
                runtime=executions,runtime_totals=runtime_totals)


def report(data):
    m=data["manifest"];rows=data["rows"]
    lines=["# Goblin Cannon simulated channel — conventional encoding comparison","", compact_markdown(), "",
        "Implemented and measured: fixed-constellation soft bit metrics, K9 convolutional rates 1/2 and 1/3, plain Walsh-8 spreading, shortened BCH(58,40,7), rectangular interleaving, noncoherent 4/8-FSK and fixed-power two-subband BPSK diversity. All are opt-in; existing defaults remain compatible. Both endpoints receive coding and waveform settings over fiber/gRPC.","",
        "The [patent screen](PATENT_SCREEN.md) excludes modern CROW, specialized LDPC constructions/decoders, adaptive constellation learning and unresolved Walsh-specific equalizers. It documents the conventional implementations and their historical basis; it is not worldwide legal clearance.","",
        f"{m['main_cases']} AVX-512 cases, {m['latency_cases']} serial quiet-host latency cases, 20/20 CTest regressions on both hosts, 13 harness checks and three byte-identical repeats. Carrier correction is off. Coherent modes retain RLS and clock recovery; FSK uses tone-energy acquisition and per-frame timing reacquisition, with no RLS, Gardner or carrier-frequency loop.","",
        "## Simulated channel — main comparisons","",
        "All comparisons below use the same seeds, durations, workload and nominal full-band sample power. Ranges span seeds; they are not confidence intervals. BCH uses a hard decoder and the soft protected header; its 40/58 payload rate is higher than the reference's 1/2, with less decoder lookahead. Goodput gains are not a claim of coding gain at an equal code rate.",""]
    for preset in ("moderate","disturbed"):
        selected=[r for r in rows if r["bandwidth"]==24000 and r["preset"]==preset]
        rank=sorted(selected,key=lambda r:sum(r["goodput"])/3,reverse=True)
        baseline=next(r for r in selected if r["variant"]=="bpsk_reference")
        best=rank[0]
        lines.append(f"- **24 kHz {preset}: {best['label']}** has the highest mean useful goodput, **{spread(best['goodput'])} bit/s**, versus **{spread(baseline['goodput'])} bit/s** for the BPSK/QPSK-header reference. Its longest delivery silence is **{spread(best['silence'],.001,3)} s**, and delivered-message freshness p99.9 is **{spread(best['freshness'])} ms**. These are measured rankings, not acceptance thresholds.")
    previous_best = next(r for r in rows if r["bandwidth"] == 24000 and r["preset"] == "disturbed"
                         and r["variant"] == "bpsk_bpsk_header_reference")
    lines += ["", f"The earlier best disturbed configuration, BPSK with a BPSK header, delivers **{spread(previous_best['goodput'])} bit/s** in the matched control. BCH also exceeds that control, while severe fading still leaves multi-second delivery gaps."]
    moderate = {r["variant"]: r for r in rows if r["bandwidth"] == 24000 and r["preset"] == "moderate"}
    mean = lambda variant: sum(moderate[variant]["goodput"]) / 3
    lines += ["", "| Experiment | 24 kHz moderate finding (three-seed means) |", "| --- | --- |",
        f"| Soft bit metrics | QPSK {mean('qpsk_reference'):.2f} → {mean('qpsk_soft'):.2f} bit/s; BPSK {mean('bpsk_reference'):.2f} → {mean('bpsk_soft'):.2f}; 16-QAM {mean('16qam_reference'):.2f} → {mean('16qam_soft'):.2f}. |",
        f"| K9 convolutional codes | Half rate {mean('bpsk_k9_half'):.2f} bit/s, third rate {mean('bpsk_k9_third'):.2f}; neither exceeds soft K7 BPSK at {mean('bpsk_soft'):.2f}. |",
        f"| BCH | {mean('bpsk_bch'):.2f} bit/s; highest useful goodput in this comparison, at a higher payload code rate. |",
        f"| Plain Walsh-8 | {mean('bpsk_walsh8'):.2f} bit/s; spreading overhead outweighs the observed benefit. |",
        f"| Rectangular interleaving | 32/256/2048 bits deliver {mean('bpsk_interleave32'):.2f}/{mean('bpsk_interleave256'):.2f}/{mean('bpsk_interleave2048'):.2f} bit/s. All six bandwidth/size combinations fail the added-buffering allowance. |",
        "| Noncoherent 4/8-FSK | Every delivered moderate-channel message is already superseded at its source; fresh goodput is zero. No messages survive the disturbed trials. Headers and guard intervals make serialization very long. |",
        f"| Two-subband BPSK | {mean('bpsk_diversity'):.2f} bit/s versus {mean('bpsk_halfband_control'):.2f} for the half-band control, both below full-band soft BPSK. The channel/spacing correlation limitation is explained in group D. |"]
    lines += ["", f"All **{m['unchanged_prior_campaign_comparisons']}** matched legacy comparisons reproduce the prior PSK campaign's goodput, delivery fraction, freshness and silence exactly. New options remain opt-in."]
    lines += ["", "## Simulated channel — A: RF channel screen", "",
        "Raw BER is conditional on observed bits. Missing frames are included in survival. FSK screens are 30 seconds; other screens are 10 seconds, as declared before execution. Use the matched-duration sustained message tables for cross-waveform goodput rankings.","",
        "| Band | Preset | Configuration | Raw BER | Bits observed | RF survival | Seed records |",
        "| --- | --- | --- | --- | --- | --- | --- |"]
    for r in data["rf"]:
        lines.append(f"| {r['bandwidth']//1000} kHz | {r['preset']} | {r['label']} | {spread(r['ber'],precision=6)} | {spread(r['observed'],100)}% | {spread(r['survival'],100)}% | {seed_links(r['sources'])} |")
    lines += ["","## Simulated channel — B: added processing and buffering","",
        "The 2.1 ms limit applies to per-message host latency minus a paired one-sample intrinsic reference. The reference retains FEC, waveform serialization and startup. It disables the interleaver and diversity combining wait so those waits are charged to the allowance. Host CPU/OS timings stay in sidecars and are excluded from deterministic JSON checks. No physical audio device is included.","",
        "The FSK runs last 30 seconds and other configurations 12 seconds. Small delivered-message counts limit interpretation of the empirical p99.9; its sample count is shown. Detailed per-call TX/RX and audio-wait observations remain in each sidecar; their percentiles are not added together. FSK's intrinsic median message latency is 1.647–5.365 seconds in this framing configuration: its small processing overhead does not make it a low-latency market-data mode.","",
        "| Band | Configuration | Delivered | Added p99.9 ms | Total p99.9 ms | Intrinsic p50 / p99.9 ms | Result |",
        "| --- | --- | --- | --- | --- | --- | --- |"]
    for r in data["latency"]:
        fmt=lambda x: "Unobserved" if x is None else f"{x:.3f}"
        lines.append(f"| {r['bandwidth']//1000} kHz | [{r['label']}]({r['source']}) | {r['delivered']} | {fmt(r['added']['p99_9'])} | {fmt(r['total']['p99_9'])} | {fmt(r['reference']['p50'])} / {fmt(r['reference']['p99_9'])} | {r['status']} |")
    lines += ["","## Simulated channel — C: SNR curves and code verification","",
        "The [saved dataset](DATA.json) contains all 672 declared AWGN points (0–30 dB, step 2). FSK uses 30 seconds per point; other modes use 10. This is nominal complex-sample SNR, not Eb/N0 or the standard's 3 kHz SNR. No claim of a BER 1e-5 operating limit follows from a short zero-error trace. These custom configurations are not directly comparable to MIL-STD-188-110C performance requirements.","",
        "| Verification | Scope | Result |","| --- | --- | --- |",
        "| BCH | Every three-error pattern on the zero codeword; randomized nonzero words with 0–3 errors; uncorrectable-word reporting | Pass |",
        "| Soft metrics | Analytical BPSK LLR, all constellation labels, weak errors marked uncertain, CTR sign inversion | Pass |",
        "| Coding streams | Five convolutional settings × BCH/Walsh/interleaver combinations; chunking, absolute offset recovery and legacy bytes | Pass |",
        "| New waveforms | Both bands; exact payload/frame positions; FSK common phase and +3 Hz residual through the existing simulator | Pass |",
        "| gRPC | Coding/waveform configuration round trip and invalid interleaver rejection | Pass |","",
        "## Simulated channel — D: message delivery and scheduler observations","",
        "All message measurements use the production framer, AES-CTR/CRC, FEC, receiver and airtime auction. Integrity is checked against source messages. CRC is not AEAD: the earlier crypto defects remain unresolved. Block coding and spreading do not remove acquisition requirements; plain Walsh uses the coherent preamble and RLS equalizer.","",
        "The frequency-diversity experiment uses one shared two-path channel. Its center spacing is 5 kHz or 12 kHz. With the presets' 1/3/7 ms delay, spacing × delay is an integer, so the two-path response repeats at the subband centers: `H(f + Δf) = H(f)` when `Δf × delay` is an integer. This is a model/spacing limitation, not evidence against frequency diversity with decorrelated paths. The half-band control is retained; no independently fading branches were fabricated.","",
        "| Observation across sustained cases | Count / maximum |","| --- | --- |",
        f"| Incorrect delivered payloads | {sum(sum(r['corrupt']) for r in rows)} |",
        f"| Duplicate deliveries | {sum(sum(r['duplicate']) for r in rows)} |",
        f"| Superseded messages claimed by framer | {sum(sum(r['superseded']) for r in rows)} |",
        f"| Maximum observed source queue depth | {max(max(r['queue']) for r in rows)} |","",
        "Fresh goodput counts only useful bits whose key has no newer source-created value at delivery. It is stricter than correct goodput. This is a simulator observation, not a receiver-side oracle or a change to application delivery semantics.","",
        "## Simulated channel — E: sustained polar delivery and determinism","",
        f"Each configuration runs quiet/moderate/disturbed for 300/300/100 seconds per seed: **{m['simulated_followup_hours']:.3f} simulated hours** in total. Delay spread and Doppler spread are 1 ms/0.5 Hz, 3 ms/10 Hz and 7 ms/30 Hz. The equalizer spans and training follow the prior PSK campaign; half-band branches scale spans to the same physical delay. All path gains are 0/0 dB, normalized in mean power. All runs use 30 dB nominal SNR.","",
        "The 71.53°N great-circle geometry is unchanged. These fixed-SNR traces do not predict route availability. The earlier 6,000-second quiet campaign stays separate. The 24 kHz Watterson use remains a bandwidth extrapolation beyond the recommendation's validation scope.","",
        "| Band | Preset | Configuration | Correct bit/s | Fresh bit/s | Delivered / framed | Freshness p99.9 ms | Longest silence s | Seeds |",
        "| --- | --- | --- | --- | --- | --- | --- | --- | --- |"]
    for r in rows:
        lines.append(f"| {r['bandwidth']//1000} kHz | {r['preset']} | {r['label']} | {spread(r['goodput'])} | {spread(r['fresh_goodput'])} | {spread(r['delivery'],100)}% | {spread(r['freshness'])} | {spread(r['silence'],.001,3)} | {seed_links(r['sources'])} |")
    lines += ["","## Simulated channel — Defects found","",
        "These expected failures preserve observed results and the existing 2.1 ms requirement. No production behavior was adjusted after a failed budget measurement to force acceptance.","",
        "| Case | Assertion | Reason |","| --- | --- | --- |"]
    for d in data["defects"]:
        lines.append(f"| [{d['case']}]({d['source']}) | {d['assertion']} | {d['reason']} |")
    if not data["defects"]:lines.append("| None in this selection | — | Earlier ledger remains separate. |")
    lines += ["","## Simulated channel — Open thresholds and questions for Adam","",
        "- Existing `THRESHOLD_TBD` decisions remain open in [the threshold register](../../tests/simulated_channel/QUESTIONS.md). No new BER, goodput, silence or acquisition threshold is invented here.",
        "- FSK headers and guard intervals add substantial modem airtime. Its fixed within-frame timing is reacquired on every preamble; no general sample-clock loop is implemented. The existing 0.1-second wall-clock replay window is unsuitable for long FSK serialization unless the control-plane session selects an appropriate window. Simulations keep the timestamp test disabled exactly as earlier campaigns did.",
        "- The patent screen covers the US and discovered international families, not a country-by-country legal clearance. Modern constructions with unresolved coverage are excluded.",
        "- The fixed frequency-diversity spacing coincides with the idealized channel's frequency periodicity. A later comparison should vary subband spacing with a matched bandwidth/rate control, or use a justified distribution of path delays; the current run does not establish an independent-diversity gain.",
        "- Soak, recorded-band noise (no recordings supplied), full nine-preset A1 qualification, AEAD and physical audio-device latency are not newly established by this campaign.","",
        "## Simulated channel — runtime and provenance","",
        "| Host | Selection | Tier | Cases | Wall seconds | Selection allowance seconds |","| --- | --- | --- | --- | --- | --- |"]
    for r in data["runtime"]:
        lines.append(f"| {r['host']} | [{r['campaign']}]({r['source']}) | {r['tier']} | {r['cases']} | {r['seconds']:.3f} | {r['budget']} |")
    lines += ["", "| Host | All new selections in tier | Cases | Summed wall seconds | Tier allowance | Within allowance |",
              "| --- | --- | --- | --- | --- | --- |"]
    for r in data["runtime_totals"]:
        lines.append(f"| {r['host']} | {r['tier']} | {r['cases']} | {r['seconds']:.3f} | {r['budget']} | {'Yes' if r['within_budget'] else '**NO**'} |")
    quick = next(r for r in data["runtime_totals"] if r["host"] == "avx10" and r["tier"] == "quick")
    lines += ["", f"The new quick selection plus the 19.08-second avx10 CTest run takes {quick['seconds'] + 19.08:.3f} seconds. This does not replace the original complete quick matrix's recorded overrun.",
        "", "Budgets apply to a complete selected tier, not independently to every subsection. Selections run sequentially on each host; the two hosts worked concurrently. Summed host durations are not a measured cross-host elapsed time. Runtime evidence records actual jobs and commands. No SNR points, seeds or durations were removed for runtime.","",
        f"Base commit `{m['git_commit']}`. Tested source SHA-256 `{m['source_tree_sha256']}`. [Exact source snapshot](source-snapshot.tar.gz), [manifest](VALIDATION.json), [host/build evidence](HOSTS.json), [canonical record index](SUMMARY.md), [quiet-host record index](naamah-latency/SUMMARY.md).","",
        "The exploratory first screen used a shorter equalizer/training geometry by mistake; it was excluded. All published runs use the declared matched geometry and the source digest above.",""]
    return "\n".join(lines)


def main():
    data=load()
    (DIRECTORY/"DATA.json").write_text(json.dumps(data,sort_keys=True,separators=(",",":"),allow_nan=False)+"\n")
    (DIRECTORY/"VALIDATION.json").write_text(json.dumps(data["manifest"],indent=2,sort_keys=True)+"\n")
    (DIRECTORY/"REPORT.md").write_text(report(data))
    print(json.dumps(data["manifest"],indent=2))

if __name__=="__main__":
    main()
