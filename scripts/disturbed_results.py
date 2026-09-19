#!/usr/bin/env python3
"""Validate and publish current simulated channel recovery measurements."""
import argparse
from collections import Counter
import hashlib
import json
import math
from pathlib import Path
import sys

import aead_results as common
from aead_results import read, save, records, span, url, LABELS, SEEDS

ROOT=Path(__file__).resolve().parents[1]
DIRECTORY=ROOT/"results/disturbed-recovery"
sys.path.insert(0,str(ROOT/"tests/simulated_channel"))
from catalog import OPEN_THRESHOLDS
from run import source_digest
from measurement_source import verify_snapshot
from channel_description import compact_markdown, RECORDED_OFFSETS, preset_markdown


def build():
    source=read(DIRECTORY/"MEASUREMENT_SOURCE.json")
    measured=verify_snapshot(DIRECTORY)
    if source["source_tree_sha256"]!=measured["source_tree_sha256"]:
        raise ValueError("Measurement source does not match the saved tested archive")
    selections={name:records(DIRECTORY/name) for name in ("security","polar","diversity","diversity-null","naamah-latency","repeat")}
    for name,count in (("security",35),("polar",576),("diversity",216),("diversity-null",54),("naamah-latency",24),("repeat",3)):
        if len(selections[name])!=count:raise ValueError(f"Incomplete {name}: {len(selections[name])}/{count}")
    all_records=[row for rows in selections.values() for row in rows]
    inventory=read(ROOT/"tests/simulated_channel/recorded_runs.json")
    actual={str(path.relative_to(ROOT)):hashlib.sha256(path.read_bytes()).hexdigest() for path,_ in all_records}
    if actual!=inventory:raise ValueError("The original 908 published records changed")
    for path,r in all_records:
        if r["parameters"]["source_tree_sha256"]!=source["source_tree_sha256"]:raise ValueError(f"Mixed source: {path}")
        if r["parameters"]["carrier_correction"]:raise ValueError(f"Carrier correction enabled: {path}")
        if r["status"]=="error":raise ValueError(f"Probe error: {path}")
    rows=[];comparisons=[];ablation=[]
    for band in (10000,24000):
        for variant,label in LABELS.items():
            for preset in ("quiet","moderate","disturbed"):
                name=f"disturbed_{band}_{variant}_high_lat_{preset}"
                chosen=[(DIRECTORY/"polar"/f"E2_{name}_combined"/f"{seed}.json") for seed in SEEDS]
                rf=[DIRECTORY/"polar"/f"A2_{name}_combined"/f"{seed}.json" for seed in SEEDS]
                rs=list(map(read,chosen));rr=list(map(read,rf));p=rs[0]["parameters"]
                rows.append(dict(bandwidth=band,variant=variant,label=label,preset=preset,
                    modulation=p["modulation"],bch=bool(p["bch_payload"]),duration=p["duration_s"],
                    parameters={k:p[k] for k in ("delay_spread_ms","doppler_spread_hz","doppler_spread_convention","doppler_shift_hz","residual_offset_hz","residual_drift_hz_per_second","snr_db","frame_symbols",
                        "training_symbols","equalizer_feedforward_taps","equalizer_feedback_taps","equalizer_delay_symbols",
                        "pilot_interval_symbols","recovery_interval_frames","sample_rate_hz","path_gains_db")},
                    goodput=[r["metrics"]["goodput_bps"] for r in rs],fresh_goodput=[r["metrics"]["fresh_goodput_bps"] for r in rs],
                    delivery=[r["metrics"]["message_delivery_fraction_of_framed"] for r in rs],
                    freshness=[r["metrics"]["freshness_ms"]["p99_9"] for r in rs],
                    silence=[r["metrics"]["delivery_silence_ms"]["max"] for r in rs],
                    auth_failures=[r["observations"]["authentication_failures"] for r in rs],
                    corrupt=[r["observations"]["corrupted_messages_delivered"] for r in rs],
                    ber=[r["metrics"]["ber"] for r in rr],survival=[r["metrics"]["frame_survival_fraction"] for r in rr],
                    observed=[r["metrics"]["bit_observation_fraction"] for r in rr],
                    measured_power=[r["observations"]["tx_mean_sample_power"] for r in rr],
                    sources=list(map(url,chosen)),rf_sources=list(map(url,rf))))
                baseline=[DIRECTORY/"polar"/f"E2_{name}_baseline"/f"{seed}.json" for seed in SEEDS]
                br=list(map(read,baseline))
                comparisons.append(dict(bandwidth=band,variant=variant,preset=preset,
                    baseline=[r["metrics"]["fresh_goodput_bps"] for r in br],combined=rows[-1]["fresh_goodput"],
                    baseline_silence=[r["metrics"]["delivery_silence_ms"]["max"] for r in br],combined_silence=rows[-1]["silence"],
                    baseline_sources=list(map(url,baseline)),sources=rows[-1]["sources"]))
                if preset=="disturbed" and variant in ("bpsk_bch","qpsk_bch"):
                    for change in ("baseline","warm","time","compact","combined"):
                        paths=[DIRECTORY/"polar"/f"E2_{name}_{change}"/f"{seed}.json" for seed in SEEDS]
                        data=list(map(read,paths))
                        ablation.append(dict(bandwidth=band,variant=variant,change=change,
                            fresh_goodput=[r["metrics"]["fresh_goodput_bps"] for r in data],
                            goodput=[r["metrics"]["goodput_bps"] for r in data],
                            silence=[r["metrics"]["delivery_silence_ms"]["max"] for r in data],sources=list(map(url,paths))))
    diversity=[]
    for band in (10000,24000):
        for spacing in ("commensurate","offset137","wide137"):
            for preset in ("moderate","disturbed","6.75ms","7.25ms"):
                group="A2" if preset.endswith("ms") else "E2"
                suffix=preset if group=="A2" else "high_lat_"+preset
                row=dict(bandwidth=band,spacing=spacing,preset=preset,branches={})
                for branch in ("lower","upper","both"):
                    paths=[DIRECTORY/"diversity"/f"{group}_disturbed_{band}_diversity_{spacing}_{branch}_{suffix}"/f"{seed}.json" for seed in SEEDS]
                    data=list(map(read,paths))
                    row["branches"][branch]=dict(fresh_goodput=[r["metrics"]["fresh_goodput_bps"] for r in data],
                        goodput=[r["metrics"]["goodput_bps"] for r in data],
                        silence=[r["metrics"]["delivery_silence_ms"]["max"] for r in data],
                        measured_power=[r["observations"]["tx_mean_sample_power"] for r in data],sources=list(map(url,paths)))
                diversity.append(row)
    latency=[]
    for path,r in selections["naamah-latency"]:
        hp=path.with_suffix(".host.json");host=read(hp)
        if host["parameters"]!=r["parameters"]:raise ValueError(f"Host parameter mismatch: {hp}")
        p=r["parameters"];h=host["observations"]
        old=ROOT/"results/aead/naamah-latency"/path.parent.name/hp.name
        latency.append(dict(case=r["test_name"],bandwidth=p["bandwidth_hz"],modulation=p["modulation"],
            span="disturbed" if "disturbed" in r["test_name"] else "polar" if "polar_span" in r["test_name"] else "short",
            profile="naamah-latency",added=h["host_added_software_latency_ms_percentiles"],
            total=h["host_latency_ms_percentiles"],reference=r["latency_reference"]["metrics"]["latency_ms"],
            status=h["added_software_latency_assertion"]["status"],
            tx=h["host_tx_per_block_ms_percentiles"],rx=h["host_rx_per_block_ms_percentiles"],
            stage_breakdown=r["metrics"]["latency_stage_breakdown_ms"],source=url(hp),record=url(path),
            old_added_p99_9_ms=read(old)["observations"]["host_added_software_latency_ms_percentiles"]["p99_9"] if old.exists() else None))
    defects=[dict(case=r["test_name"],assertion=a["assertion"],reason=a["reason"],source=url(path),status=a["status"])
             for path,r in all_records for a in r["assertions"] if a["status"] in ("xfail","fail","xpass")]
    repeats=[]
    for path,r in selections["repeat"]:
        original=DIRECTORY/"polar"/path.parent.name/path.name
        same=path.read_bytes()==original.read_bytes()
        repeats.append(dict(case=r["test_name"],seed=r["seed"],byte_identical=same,first=url(original),second=url(path)))
        if not same:raise ValueError(f"Nondeterministic result: {path}")
    power=[]
    for path,r in all_records:
        measured=r["observations"].get("tx_mean_sample_power")
        if measured is None:continue
        nominal=r["parameters"]["nominal_sample_power"]
        # The tolerance predates this experiment; never normalize a fade or
        # rescale the measurements after running the receiver.
        ratio=measured/nominal
        # The equal-power experiment uses constant-modulus PSK. Idle QAM
        # symbols need not have the ensemble mean constellation energy, so
        # their finite-stream power is characterized rather than required to
        # equal the nominal random-data reference (notably in null B5).
        constant_modulus=r["parameters"]["modulation"] in ("bpsk","qpsk","8psk") and not r['parameters']['pure_noise']
        power.append(dict(record=url(path),seed=r["seed"],parameters=r["parameters"],
            measured=measured,nominal=nominal,ratio=ratio,
            kind="assert" if constant_modulus else "characterize",
            measured_prefade_snr_db=None if r["parameters"]["snr_db"] is None or ratio<=0 else r["parameters"]["snr_db"]+10*math.log10(ratio),
            status=("pass" if abs(ratio-1)<=.02 else "fail") if constant_modulus else "characterized"))
    controls=[];fullband_controls=[]
    for d in diversity:
        for i,seed in enumerate(SEEDS):
            lower=d["branches"]["lower"]["measured_power"][i]
            ratios=[d["branches"][b]["measured_power"][i]/lower for b in ("upper","both")]
            controls.append(dict(bandwidth=d["bandwidth"],spacing=d["spacing"],preset=d["preset"],seed=seed,
                ratios=ratios,status="pass" if all(abs(r-1)<=.02 for r in ratios) else "fail",
                sources=[d["branches"][b]["sources"][i] for b in ("lower","upper","both")]))
            if d['preset'] in ('moderate','disturbed'):
                full=DIRECTORY/'polar'/f"E2_disturbed_{d['bandwidth']}_bpsk_bch_high_lat_{d['preset']}_combined"/f"{seed}.json"
                ratio=d['branches']['both']['measured_power'][i]/read(full)['observations']['tx_mean_sample_power']
                fullband_controls.append(dict(bandwidth=d['bandwidth'],spacing=d['spacing'],preset=d['preset'],seed=seed,
                    ratio=ratio,status='pass' if abs(ratio-1)<=.02 else 'fail',
                    sources=[url(full),d['branches']['both']['sources'][i]]))
    a8=[dict(case=r["test_name"],sir=r["parameters"]["data_sir_db"],delivered=r["observations"]["messages_delivered"],
             corrupt=r["observations"]["corrupted_messages_delivered"],authentication_failures=r["observations"]["authentication_failures"],
             fec_gaps=r["observations"]["fec_gap_events"],source=url(path),status=r["status"])
        for path,r in selections["security"] if r["group"]=="A8"]
    crypto=next(r["observations"] for _,r in selections["security"] if r["test_name"]=="D6_crypto_errors_replay_restart")
    executions=[]
    for directory in selections:
        for path in sorted((DIRECTORY/directory).glob("EXECUTION-*.json")):
            r=read(path);executions.append(dict(directory=directory,tier=r["tier"],seconds=r["elapsed_seconds"],
                budget=r["budget_seconds"],cases=r["executed_cases"],source=url(path)))
    groups={g:dict(Counter(r["status"] for _,r in all_records if r["group"]==g)) for g in sorted({r["group"] for _,r in all_records})}
    manifest=dict(report_header="simulated channel disturbed recovery validation",**{k:source[k] for k in ("git_commit","source_tree_sha256")},
        seeds=list(SEEDS),recorded_runs=len(all_records),unique_case_seed_profiles=len({(r["test_name"],r["seed"]) for _,r in all_records}),
        remaining_assertions=len(defects),remaining_cases=len({d["case"] for d in defects}),groups=groups,
        byte_identical_repeats=len(repeats),latency_configurations=len(latency),
        host_latency_statuses=dict(Counter(r["status"] for r in latency)),
        power_statuses=dict(Counter(r["status"] for r in power)),diversity_power_statuses=dict(Counter(r["status"] for r in controls)),
        fullband_power_statuses=dict(Counter(r['status'] for r in fullband_controls)),
        statuses=dict(Counter(r["status"] for _,r in all_records)))
    save(DIRECTORY/"POWER.json",dict(report_header="simulated channel measured power audit",kind="assert",tier="quick",
        tolerance=.02,tolerance_basis="Existing finite-waveform test tolerance",assertion_scope="Constant-modulus PSK and matched diversity controls. QAM idle-pattern power is characterization only.",measurements=power,controls=controls,fullband_controls=fullband_controls))
    return dict(schema_version=3,manifest=manifest,rows=rows,comparisons=comparisons,ablation=ablation,diversity=diversity,
                latency=latency,defects=defects,a8=a8,crypto=crypto,repeats=repeats,executions=executions)


def report(data):
    m=data["manifest"]
    qpsk=next(r for r in data['comparisons'] if r['bandwidth']==24000 and r['variant']=='qpsk_bch' and r['preset']=='disturbed')
    aging=next(r for r in data['ablation'] if r['bandwidth']==24000 and r['variant']=='qpsk_bch' and r['change']=='time')
    quiet=next(r for r in data['comparisons'] if r['bandwidth']==24000 and r['variant']=='8psk_bch' and r['preset']=='quiet')
    diversity_severe=[v for r in data['diversity'] if r['bandwidth']==24000 and r['preset']=='disturbed' for v in r['branches']['both']['fresh_goodput']]
    lines=["# Goblin Cannon simulated channel — disturbed recovery", "", compact_markdown(), "", preset_markdown(), "", RECORDED_OFFSETS, "",
        "All four experiments are implemented and measured: warm equalizer recovery with varied known startup symbols and shorter recurring training; uncertainty prediction through rejected decisions; a fiber-selected 13-byte authenticated header; and frequency diversity with matched measured power. Carrier correction remains off. The GCM tag remains 16 bytes.", "",
        "Fresh calibrated baselines use the same source, channel seeds and full durations as the changed receiver. The earlier noise reference underestimated RRC sample power and diversity width compensation increased transmit power. Those errors are corrected before these comparisons. No per-fade normalization is used.","",
        f"At 24 kHz on the disturbed preset, QPSK+BCH fresh goodput changes from {span(qpsk['baseline'])} to {span(qpsk['combined'])} bit/s. Longest delivery silences change from {span(qpsk['baseline_silence'],.001,3)} to {span(qpsk['combined_silence'],.001,3)} seconds. This is useful but still intermittent delivery. Uncertainty aging alone produces {span(aging['fresh_goodput'])} bit/s; it is not a standalone improvement on these traces.","",
        f"The recipe remains selectable: quiet 24 kHz 8-PSK+BCH falls from {span(quiet['baseline'])} to {span(quiet['combined'])} fresh bit/s. At 10 kHz, disturbed delivery remains essentially absent (one message in one seed for each QPSK coding choice). These controls do not provide a universal channel improvement.","",
        f"Two-copy frequency diversity at 24 kHz delivers only {span(diversity_severe)} fresh bit/s on the disturbed preset. It improves over its narrow single-copy controls on moderate fading, but remains far behind the full-band configurations. All 54 null-channel compact-diversity assertions pass; the poor fading result is retained.","",
        f"{m['recorded_runs']} recorded runs; {m['remaining_assertions']} failing assertions across {m['remaining_cases']} cases. Three seeds: {', '.join(map(str,SEEDS))}. Quiet/moderate/disturbed message durations are 300/300/100 seconds per seed; raw RF screens are ten seconds. Off-preset diversity traces are 100 seconds. Ranges are finite-seed ranges, not confidence intervals.","",
        "## Simulated channel A2 — current RF screening", "", "| Band | Coding | Preset | Conditional BER | Frame survival % | Observed bits % |", "| --- | --- | --- | --- | --- | --- |"]
    for r in data["rows"]:lines.append(f"| {r['bandwidth']//1000} kHz | {r['label']} | {r['preset']} | {span(r['ber'],digits=5)} | {span(r['survival'],100)} | {span(r['observed'],100)} |")
    lines += ["", "## Simulated channel E2 — fresh authenticated useful bit/s", "", "| Band | Coding | Preset | Calibrated baseline | Combined changes |", "| --- | --- | --- | --- | --- |"]
    for r in data["comparisons"]:lines.append(f"| {r['bandwidth']//1000} kHz | {LABELS[r['variant']]} | {r['preset']} | {span(r['baseline'])} | [{span(r['combined'])}]({r['sources'][0]}) |")
    lines += ["", "### Simulated channel E2 — disturbed ablation", "", "`warm` includes varied startup symbols, retained echo support, three warm training passes with cold fallback, a final-64-symbol training score, training length max(128, ceil(1.4 × feedforward span)) and recovery every eight frames. `time` changes uncertainty prediction alone; `compact` changes the message header alone. `combined` enables all three. Baseline retains the longer training and sixteen-frame cadence. The EVM rejection limit stays 0.45.", "",
        "| Band | Coding | Change | Useful bit/s | Fresh bit/s | Maximum silence, s |", "| --- | --- | --- | --- | --- | --- |"]
    for r in data["ablation"]:lines.append(f"| {r['bandwidth']//1000} kHz | {LABELS[r['variant']]} | {r['change']} | {span(r['goodput'])} | [{span(r['fresh_goodput'])}]({r['sources'][0]}) | {span(r['silence'],.001,3)} |")
    lines += ["", "### Simulated channel E2/A2 — frequency diversity", "", "Each branch occupies 0.4B. Separations are B/2, B/2 + 137 Hz, and 0.55B + 137 Hz. Both copies traverse one physical two-path realization; they are not independent fading channels. Each single-copy control has the full transmit power. All use BPSK+BCH and the compact authenticated path. Off-preset delays test sensitivity to the exact 7 ms echo.", "",
        "| Band | Spacing | Trace | Lower fresh bit/s | Upper fresh bit/s | Both fresh bit/s | Both maximum silence, s |", "| --- | --- | --- | --- | --- | --- | --- |"]
    for r in data["diversity"]:
        b=r['branches'];lines.append(f"| {r['bandwidth']//1000} kHz | {r['spacing']} | {r['preset']} | {span(b['lower']['fresh_goodput'])} | {span(b['upper']['fresh_goodput'])} | [{span(b['both']['fresh_goodput'])}]({b['both']['sources'][0]}) | {span(b['both']['silence'],.001,3)} |")
    lines += ["", "## Simulated channel B5 — serial naamah measurements", "", "2.1 ms applies to added processing and buffering. Total latency and the matched intrinsic transmission/modem reference remain separate. Previous values below are the preceding AEAD campaign for the same twelve named configurations; the additional twelve cases exercise the actual 7 ms equalizer span. Null channel, twelve seconds each; no concurrent validation on naamah.", "",
        "| Case | Previous added p99.9 ms | Added p99.9 ms | Total p99.9 ms | Intrinsic p99.9 ms | TX / RX per-block p99.9 ms | Result |", "| --- | --- | --- | --- | --- | --- | --- |"]
    for r in data["latency"]:
        old="—" if r['old_added_p99_9_ms'] is None else f"{r['old_added_p99_9_ms']:.6f}"
        lines.append(f"| [{r['case']}]({r['source']}) | {old} | {r['added']['p99_9']:.6f} | {r['total']['p99_9']:.3f} | {r['reference']['p99_9']:.3f} | {r['tx']['p99_9']:.6f} / {r['rx']['p99_9']:.6f} | {r['status']} |")
    lines += ["",f"Receiver-call timing is a separate finding: the largest per-block RX p99.9 is {max(r['rx']['p99_9'] for r in data['latency']):.3f} ms and the largest observed RX call is {max(r['rx']['max'] for r in data['latency']):.3f} ms. Training runs in bursts. Delivered-message latency passes do not prove a one-millisecond audio-callback deadline. This single-thread fixture creates source messages when its loop runs; scheduling delays before creation are outside its creation-to-delivery metric. Physical audio buffering still requires validation."]
    lines += ["", "## Simulated channel A8 / D6 — authenticated delivery", "", "| SIR dB | Delivered | Authentication failures | Foreign/corrupt delivered | Result |", "| --- | --- | --- | --- | --- |"]
    for r in data['a8']:lines.append(f"| {r['sir']:+g} | {r['delivered']} | {r['authentication_failures']} | {r['corrupt']} | {r['status']} |")
    c=data['crypto'];lines += ["",f"D6 rejects {c['tamper_attempts']} mutations, {c['replay_rejections']} same-session replays and {c['old_epoch_authentication_failures']} old-epoch records. Two sender processes produce {c['nonces_observed']} distinct nonces; no unverified plaintext reaches the sink. In compact format the epoch is implicit authenticated context, so old-epoch records count as authentication failures. Coordinated rotation remains unimplemented.","",
        "## Simulated channel E1 — determinism and power", "",f"Three repeated message runs have byte-identical canonical JSON. Seeded model/RF determinism also runs in the security selection. Host timings are excluded from byte equality and retained in separate files. Power audit: {m['power_statuses']}; lower/upper/both audit: {m['diversity_power_statuses']}; diversity/full-band audit: {m['fullband_power_statuses']}. See [POWER.json](POWER.json) for every measured ratio and its complete source parameters. The numerical tolerance is the existing 2%; it is not a new channel acceptance threshold.","",
        "## Simulated channel remaining test groups", "", "| Group | Status counts |", "| --- | --- |"]
    for g,statuses in m['groups'].items():lines.append(f"| {g} | {statuses} |")
    lines += ["", "## Simulated channel — Defects found", "", "| Case | Assertion | Reason |", "| --- | --- | --- |"]
    for r in data['defects']:lines.append(f"| [{r['case']}]({r['source']}) | {r['assertion']} ({r['status']}) | {r['reason']} |")
    lines += ["", "The prior nine-case security ledger is rerun with the new profile. This selection also includes C2 acquisition/noise tests, so its total is not obtained simply by subtracting fixed cases from nine. `validation-meta/CLASSIFICATION.json` records reviewed expected-failure changes; it changes no observations or thresholds. Receiver CPU bursts above are a separate characterization finding, not a newly invented acceptance assertion."]
    lines += ["", "## Simulated channel — Open thresholds", "", "| Threshold | Proposed approach | Reason |", "| --- | --- | --- |"]
    for name,(proposal,reason) in OPEN_THRESHOLDS.items():lines.append(f"| {name}: THRESHOLD_TBD | {proposal} | {reason} |")
    lines += ["", "## Simulated channel runtime and limitations", "", "| Selection | Tier | Cases | Seconds | Budget |", "| --- | --- | --- | --- | --- |"]
    for r in data['executions']:lines.append(f"| [{r['directory']}]({r['source']}) | {r['tier']} | {r['cases']} | {r['seconds']:.3f} | {'within' if r['seconds']<=r['budget'] else 'EXCEEDED'} {r['budget']} s |")
    totals=Counter()
    for r in data['executions']:totals[r['tier']]+=r['seconds']
    avx_full=sum(r['seconds'] for r in data['executions'] if r['tier']=='full' and r['directory']!='naamah-latency')
    if avx_full>1800:
        lines += ["",f"**Runtime finding:** the selected full channel workloads on avx10 total {avx_full/60:.2f} minutes, exceeding the 30-minute tier target. Every declared seed, duration and grid point was retained. Individual invocation budget labels above must not be read as a whole-tier pass."]
    if totals['quick']>120:
        lines += ["",f"**Runtime finding:** selected quick invocations total {totals['quick']:.3f} seconds across both hosts, exceeding the 120-second tier target. A complete quick-tier run under two minutes has not been established."]
    lines += ["",f"Sum of selected invocation wall times: {dict(totals)}. Selections are not the complete A1–E4 tiers; a per-invocation pass does not establish a whole-tier runtime. No counts or durations were reduced.","",
        "These are simulated channels, not measured route availability. The 24 kHz use extends beyond F.1487's validated bandwidth scope. Local usable-time proxies are not STAC audit definitions. No physical audio device/network socket, recorded-band noise, or four-hour soak is included. This change adds no frequency tracker, new code family, or new modulation; it refines existing conventional RLS/training/diversity and OpenSSL GCM. The existing US/international-family patent screen is not a legal clearance opinion.","",
        "### Simulated channel — questions for Adam", "", "- All unapproved thresholds above remain open.", "- Strict priority still permits lower-bid starvation; no age-based priority boost was added.", "- Coordinated overlapping-key rotation remains separate work.", "- Recorded-band noise and actual radio/audio-device validation still need inputs/hardware.", "",
        f"Tested source SHA-256: `{m['source_tree_sha256']}`. Base commit `{m['git_commit']}` plus the saved source snapshot identifies the measured worktree."]
    return "\n".join(lines)+"\n"


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("--snapshot",action="store_true");args=parser.parse_args()
    if args.snapshot:
        common.DIRECTORY=DIRECTORY;common.snapshot();return 0
    data=build();save(DIRECTORY/"DATA.json",data);save(DIRECTORY/"VALIDATION.json",data['manifest'])
    (DIRECTORY/"SUMMARY.md").write_text(report(data))
    m=data['manifest'];worst=max(r['added']['p99_9'] for r in data['latency'])
    lines=["# Goblin Cannon simulated channel current results", "", compact_markdown(), "", RECORDED_OFFSETS, "",
        "Warm recovery, elapsed-symbol RLS uncertainty, a 13-byte authenticated header and calibrated frequency diversity are implemented and tested. Carrier correction is off; the full 16-byte AES-GCM tag and persisted nonce epochs remain.","",
        "[Current report and open thresholds](disturbed-recovery/SUMMARY.md) · [Validation](disturbed-recovery/VALIDATION.json) · [Measured power](disturbed-recovery/POWER.json)","",
        "## Simulated channel — 24 kHz disturbed fresh useful bit/s", "",
        "Three seeds, 100 seconds each. Both columns are freshly measured at the corrected 30 dB reference; the baseline disables the new recovery/header controls.","",
        "| Configuration | Calibrated baseline | Combined changes |", "| --- | --- | --- |"]
    for r in data['comparisons']:
        if r['bandwidth']==24000 and r['preset']=='disturbed':lines.append(f"| {LABELS[r['variant']]} | {span(r['baseline'])} | {span(r['combined'])} |")
    lines += ["", "## Simulated channel — latency and security", "",
        f"{sum(r['status']=='pass' for r in data['latency'])} of {len(data['latency'])} measured latency configurations pass the unchanged 2.1 ms delivered-message added-processing/buffering limit; worst added p99.9 is {worst:.6f} ms. RX training calls still peak at {max(r['rx']['max'] for r in data['latency']):.3f} ms. Per-message passes do not establish a 1 ms audio-callback deadline; the report preserves stage timings and the fixture's source-scheduling limitation.","",
        f"A8 rejects injection at all three SIR settings. At −10 dB it counts {next(r['authentication_failures'] for r in data['a8'] if r['sir']==-10)} authentication failures and zero corrupt deliveries. D6 verifies tampering, replay, negotiated context and restart-safe nonces. {m['remaining_assertions']} expected-failing assertions across {m['remaining_cases']} cases remain in the expanded current selection; each is listed in the report.","",
        "The result set includes the three modulation families, two coding choices, both bandwidths, quiet/moderate/disturbed presets, component comparisons and matched-power diversity controls. These finite simulated channels do not establish route availability. No live recording or soak result is claimed."]
    (ROOT/"results/SUMMARY.md").write_text("\n".join(lines)+"\n")
    print(json.dumps(data['manifest']))


if __name__=="__main__":main()
