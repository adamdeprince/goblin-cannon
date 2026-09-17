#!/usr/bin/env python3
"""Run and report the simulated channel matrix against the real C++ library."""
from __future__ import annotations

import argparse
import concurrent.futures
import copy
import csv
import hashlib
import json
import os
import platform
import subprocess
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

from catalog import (Case, DEFAULTS, OPEN_THRESHOLDS, PRESETS, RECOVERY_PROFILE, full_parameters, matrix)
from metrics import METRIC_DEFINITIONS, check, percentiles, summarize, latency_above_reference

REPO=Path(__file__).resolve().parents[2]


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(",", ":"), allow_nan=False)+"\n"


def source_digest():
    digest=hashlib.sha256()
    for directory in ("src", "include", "proto", "tests", "cmake"):
        for path in sorted((REPO/directory).rglob("*")):
            if (not path.is_file() or "__pycache__" in path.parts or path.suffix in (".pyc",".md")
                    or path.name=="expected_failures.json"):
                continue
            digest.update(str(path.relative_to(REPO)).encode()+b"\0"+path.read_bytes())
    digest.update((REPO/"CMakeLists.txt").read_bytes())
    return digest.hexdigest()


def revision():
    try:
        return subprocess.check_output(["git", "rev-parse", "HEAD"], cwd=REPO, text=True, stderr=subprocess.DEVNULL).strip()
    except subprocess.CalledProcessError:
        raise SystemExit("Source copy lacks .git: supply --git-commit and --source-digest from the originating workspace")


def probe(binary, parameters):
    args=[str(binary)]
    for key,value in sorted(parameters.items()):
        if key not in DEFAULTS:
            continue
        args.append(f"{key}={'inf' if value is None else value}")
    result=subprocess.run(args, capture_output=True, text=True)
    if result.returncode:
        raise RuntimeError(result.stderr.strip() or f"probe exited {result.returncode}")
    return json.loads(result.stdout)


def load_known():
    path=Path(__file__).with_name("expected_failures.json")
    return json.loads(path.read_text()) if path.exists() else {}


def evaluate(c, raw, metrics, known):
    checks=[]
    for name in c.checks:
        failure=check(name, raw, metrics)
        reason=expected_reason(c,name,known)
        status=("xpass" if reason else "pass") if failure is None else "xfail" if reason else "fail"
        checks.append(dict(assertion=name, status=status, reason=reason if status=="xfail" else failure))
    if any(x["status"] in ("fail","xpass") for x in checks):
        status="fail"
    elif any(x["status"]=="xfail" for x in checks):
        status="xfail"
    elif c.thresholds:
        status="THRESHOLD_TBD"
    else:
        status="characterized" if c.kind=="characterize" else "pass"
    return status, checks


def expected_reason(c, name, known):
    key=c.name+"."+name
    return known.get(c.parameters.get("rf_profile","legacy")+"::"+key,known.get(key))


def execute(c, args, known):
    params=copy.deepcopy(c.parameters)
    record=dict(schema_version=1, report_header="Goblin Cannon simulated channel result",
                test_name=c.name, group=c.group, kind=c.kind, tier=c.tier,
                seed=params["seed"], parameters=full_parameters(c, args.git_commit, args.source_digest),
                metric_definitions=METRIC_DEFINITIONS, notes=c.notes.copy(),
                open_thresholds=[dict(id=t, status="THRESHOLD_TBD", proposed=OPEN_THRESHOLDS[t][0],
                                      reason=OPEN_THRESHOLDS[t][1]) for t in c.thresholds])
    record["expected_failure_registry_sha256"]=hashlib.sha256(canonical(known).encode()).hexdigest()
    if c.unavailable:
        record |= dict(status="unavailable", reason=c.unavailable, observations={}, metrics=summarize({}), assertions=[])
        return record
    mode=params["mode"]
    if mode=="analysis":
        record |= dict(status="pending_analysis", observations={}, metrics=summarize({}), assertions=[])
        return record
    if mode=="soak":
        params["mode"]="messages"
        params["soak"]=1
    raw={}
    try:
        if mode=="determinism":
            trial=params|{"mode":"model"}
            first=probe(args.probe,trial)
            second=probe(args.probe,trial)
            rf_params=params|{"mode":"rf"}
            rf_first=probe(args.probe,rf_params)
            rf_second=probe(args.probe,rf_params)
            # Compare complete canonical result content, not only a numeric
            # tolerance; no wall-clock runtime is present in this record.
            one={"parameters":record["parameters"],"model":first,"rf":rf_first,"metrics":summarize(rf_first)}
            two={"parameters":record["parameters"],"model":second,"rf":rf_second,"metrics":summarize(rf_second)}
            raw=first|dict(identical_json=int(canonical(one)==canonical(two)),
                           repeated_result_sha256=hashlib.sha256(canonical(one).encode()).hexdigest())
        elif mode=="paired_survival":
            raw=paired_survival(params,args)
        else:
            if c.group=="A4" and params["residual_drift_hz_per_second"]!=0:
                control=params|dict(residual_drift_hz_per_second=0,residual_offset_hz=0)
                baseline=probe(args.probe,control)
                record["baseline"]=dict(parameters=record["parameters"]|dict(residual_drift_hz_per_second=0,residual_offset_hz=0),
                                        observations=baseline,metrics=summarize(baseline))
            if "clipping_percent" in params:
                calibration=probe(args.probe,params|{"calibrate_clip":1,"soft_clip":0})
                params["clip_amplitude"]=calibration[f"clip_top_{params['clipping_percent']}"]
                record["parameters"]["clip_amplitude"]=params["clip_amplitude"]
                baseline=probe(args.probe,params|{"clip_amplitude":None,"soft_clip":0})
                record["baseline"]=dict(parameters=record["parameters"]|{"clip_amplitude":None,"soft_clip":0},
                                        observations=baseline,metrics=summarize(baseline))
            raw=probe(args.probe,params)
            if c.group=="B5":
                # Replay exactly the messages selected by the measured auction,
                # available at their original creation times. The reference
                # retains modem/serialization work without making a second,
                # block-size-dependent auction choose a different source stream.
                reference_params=params|dict(chunk_samples=1,host_timing=0,auction_intake=0,
                    selected_messages=",".join(str(int(i)) for i in raw["consumed_ids"]))
                if params.get("campaign")=="encoding_latency":
                    reference_params.update(interleaver_rows=0,interleaver_columns=0,diversity_wait_ms=0)
                reference=probe(args.probe,reference_params)
                if params.get("campaign")=="encoding_latency":
                    raw["added_buffering_scope"]="Interleaving and diversity combining wait are disabled only in the intrinsic reference, so their waiting time is included in the 2.1 ms assertion. Coding and RF serialization remain enabled."
                reference_case=Case(c.name,c.group,c.kind,c.tier,reference_params)
                record["latency_reference"]=dict(
                    parameters=full_parameters(reference_case,args.git_commit,args.source_digest),
                    observations=reference,metrics=summarize(reference))
                raw["added_software_latency_ms"]=latency_above_reference(raw,reference)
                if "host_latency_ms" in raw:
                    raw["host_added_software_latency_ms"]=latency_above_reference(raw,reference,"host_latency_ms")
                    raw["host_added_latency_scope"]="Per-message measured total minus one-sample simulated-clock replay of the selected message stream, available at original source times; includes added batching, queueing, CPU and OS scheduling. Intrinsic serialization, modem/FEC and startup remain in the separately reported reference. No physical audio device."
                    if params.get("campaign")=="encoding_latency":
                        raw["host_added_latency_scope"] += " Interleaver and diversity combining waits are disabled in the intrinsic reference and are charged as added buffering."
            if c.group=="D1":
                pipeline=params|dict(mode="messages",bandwidth_hz=10000,modulation="qpsk",fec="1/2",chunk_samples=48,
                                     auction_intake=1,source_load_factor=params["overload"])
                nested=Case(c.name,c.group,c.kind,c.tier,pipeline)
                raw["pipeline"]={"parameters":full_parameters(nested,args.git_commit,args.source_digest),
                                 "observations":probe(args.probe,pipeline)}
                raw["pipeline"]["metrics"]=summarize(raw["pipeline"]["observations"])
            if c.group=="C3" and params["sample_slip_index"]>=0:
                boundary_parameters=params|{"mode":"rf"}
                raw["boundary_probe"]={"parameters":record["parameters"]|{"mode":"rf","measurement_layer":"RF frame recovery"},
                                       "observations":probe(args.probe,boundary_parameters)}
        metrics=summarize(raw)
        if c.group=="B5":
            metrics["latency_stage_breakdown_ms"]={
                "audio_block_duration":raw.get("audio_block_ms"),
                "initial_acquisition_until_preamble_found":None if raw.get("acquisition_time_s") is None else raw["acquisition_time_s"]*1000,
                "intrinsic_transmission_modem_startup":record["latency_reference"]["metrics"]["latency_ms"],
                "added_buffering":metrics["added_software_latency_ms"],
                "source_to_framer":percentiles(raw.get("source_to_framer_ms",[])),
                "nominal_message_serialization":percentiles(raw.get("nominal_message_serialization_ms",[])),
                "modem_residence_estimates":raw.get("modem_delay_estimates",{}),
                "method":"Matched message identities, one-sample reference. Host per-call CPU and queue observations are in the sidecar; call-duration percentiles are not added together.",
            }
        host={key:raw.pop(key) for key in list(raw) if key.startswith("host_")}
        if host:
            record["host_observations"]=host
            for key,value in list(host.items()):
                if key.endswith("_ms") and isinstance(value,list):host[key+"_percentiles"]=percentiles(value)
            if "host_added_software_latency_ms" in host:
                p999=host["host_added_software_latency_ms_percentiles"]["p99_9"]
                failure=p999 is None or p999>2.1
                reason=expected_reason(c,"latency_2_1ms",known)
                host["added_software_latency_assertion"]={"threshold_ms":2.1,"percentile":"p99.9",
                    "status":("xfail" if reason else "fail") if failure else "pass",
                    "reason":reason if failure else None,"observed_ms":p999,"scope":host["host_added_latency_scope"]}
        if "baseline" in record:
            b=record["baseline"]["metrics"]["ber"]
            metrics["ber_penalty"]=metrics["ber"]-b if metrics["ber"] is not None and b is not None else None
        status,checks=evaluate(c,raw,metrics,known)
        record |= dict(status=status, observations=raw, metrics=metrics, assertions=checks)
    except (RuntimeError,ValueError,KeyError) as e:
        # Harness failures are failures, never automatically reclassified xfail.
        host={key:raw.pop(key) for key in list(raw) if key.startswith("host_")}
        if host:record["host_observations"]=host
        record |= dict(status="error", reason=str(e), observations=raw, metrics=summarize(raw), assertions=[])
    return record


def paired_survival(params,args):
    candidates=[]
    target=params["target_survival"]
    def measure(preset_name,snr):
        delay,spread=PRESETS[preset_name]
        trial=params|dict(mode="rf",channel_model="watterson",delay_spread_ms=delay,doppler_spread_hz=spread,
                          bandwidth_hz=10000,fec="1/2",snr_db=snr,calibration_preset=preset_name)
        raw=probe(args.probe,trial)
        manifest=full_parameters(Case("D2_calibration","D2","characterize","full",trial),args.git_commit,args.source_digest)
        candidates.append(dict(parameters=manifest,observations=raw,metrics=summarize(raw)))
    for preset_name in params["survival_calibration_presets"]:
        for snr in params["survival_snr_grid_db"]:measure(preset_name,snr)
    for _ in range(params["survival_refinement_rounds"]):
        brackets=[]
        for preset_name in params["survival_calibration_presets"]:
            rows=sorted((r for r in candidates if r["parameters"]["calibration_preset"]==preset_name and r["metrics"]["frame_survival_fraction"] is not None),key=lambda r:r["parameters"]["snr_db"])
            for low,high in zip(rows,rows[1:]):
                a=low["metrics"]["frame_survival_fraction"]-target;b=high["metrics"]["frame_survival_fraction"]-target
                if a*b<=0 and low["parameters"]["snr_db"]!=high["parameters"]["snr_db"]:
                    brackets.append((abs(a)+abs(b),preset_name,low["parameters"]["snr_db"],high["parameters"]["snr_db"]))
        if not brackets:break
        _,preset_name,low,high=min(brackets)
        measure(preset_name,(low+high)/2)
    usable=[r for r in candidates if r["metrics"]["frame_survival_fraction"] is not None]
    selected=min(usable,key=lambda r:abs(r["metrics"]["frame_survival_fraction"]-target))
    noisy=selected["parameters"]|dict(mode="messages",fec="1/2",chunk_samples=48)
    noisy=full_parameters(Case("D2_channel_delivery","D2","characterize","full",noisy),args.git_commit,args.source_digest)
    channel_messages=probe(args.probe,noisy)
    direct_parameters=params|dict(mode="erasure",bandwidth_hz=10000,fec="1/2",direct_survival=target)
    direct_parameters=full_parameters(Case("D2_direct_erasure","D2","characterize","full",direct_parameters),args.git_commit,args.source_digest)
    direct=probe(args.probe,direct_parameters)
    return dict(simulated_seconds=params["duration_s"], target_survival=target,
                achieved_channel_frame_survival=selected["metrics"]["frame_survival_fraction"],
                calibration=candidates, channel_parameters=noisy,channel_messages=channel_messages,
                direct_erasure_parameters=direct_parameters,direct_erasure=direct,
                channel_metrics=summarize(channel_messages),direct_erasure_metrics=summarize(direct),
                target_attained=selected["metrics"]["frame_survival_fraction"]==target,
                notes="No acceptance tolerance supplied for matching channel survival to target; closest observed SNR recorded without relabeling it.")


def persist(record,output):
    directory=output/record["test_name"]
    directory.mkdir(parents=True,exist_ok=True)
    target=directory/f"{record['seed']}.json"
    temporary=target.with_suffix(".json.tmp")
    host=record.pop("host_observations",None)
    if host is not None:
        observation=dict(report_header="simulated channel non-canonical host observations",parameters=record["parameters"],observations=host)
        target.with_suffix(".host.json").write_text(canonical(observation))
    temporary.write_text(canonical(record))
    temporary.replace(target)


def analysis(output, cases, args):
    records=[]
    for path in sorted(output.glob("*/[0-9]*.json")):
        if path.name.endswith(".host.json"):continue
        records.append(json.loads(path.read_text()))
    a1=[r for r in records if r["group"]=="A1" and r["status"]=="characterized"]
    table=[]
    indexed=defaultdict(list)
    for r in a1:
        p=r["parameters"]
        # Keep CCIR aliases separate in the table despite identical parameters.
        preset_name=next((n for n in PRESETS if f"_{n}_" in r["test_name"]),"unknown")
        indexed[(p["bandwidth_hz"],p["modulation"],p["fec"],preset_name)].append(r)
    for (bw,mod,fec,preset_name),rows in sorted(indexed.items()):
        row=dict(bandwidth_hz=bw,modulation=mod,fec=fec,preset=preset_name,standard_waveform_id=None,
                 standard_assertion="not comparable: framing/rate/interleaver differ")
        for target in (1e-3,1e-5):
            passing=[r for r in rows if r["metrics"]["coded_ber"] is not None and r["metrics"]["coded_ber"]<=target]
            row[f"empirical_snr_at_{target}"]=min((r["parameters"]["snr_db"] for r in passing),default=None)
            # F.1487 Annex 3 recommends 100/(BER*rate) seconds. A short zero-error
            # trace cannot establish the requested BER operating point.
            established=[r for r in passing if r["observations"].get("coded_bits_compared",0)>=100/target and
                         r["observations"].get("simulated_seconds",0)>=3000/r["parameters"]["doppler_spread_hz"]]
            row[f"established_snr_at_{target}"]=min((r["parameters"]["snr_db"] for r in established),default=None)
        table.append(row)
    for c in cases:
        if c.name=="C1_ber_tables":
            r=execute(c,args,{})
            r["status"]="characterized" if table else "unavailable"
            r["reason"]="Short screening records do not establish F.1487 BER operating limits." if table else "Run A1 to populate this table."
            r["observations"]={"table":table,"input_results":[f"{r['test_name']}/{r['seed']}.json" for r in a1]}
            persist(r,output)
        elif c.group=="D2" and c.parameters["mode"]=="analysis":
            r=execute(c,args,{})
            r["status"]="THRESHOLD_TBD"
            r["reason"]="Freshness comparison margin and target-survival matching tolerance are unapproved."
            persist(r,output)


def report(output,all_cases):
    records=[json.loads(p.read_text()) for p in sorted(output.glob("*/[0-9]*.json")) if not p.name.endswith(".host.json")]
    indexed={(r["test_name"],r["seed"]):r for r in records}
    for r in records:
        p=r["parameters"]
        if r["group"]=="A4" and p["clock_ppm"]==0:
            baseline=(r["baseline"]|dict(test_name=r["test_name"],seed=r["seed"])) if "baseline" in r else indexed.get((f"A4_{p['bandwidth_hz']}_{p['modulation']}_offset_0",r["seed"]))
            threshold="A4.ber_delta"
        elif r["group"]=="C4" and p["mode"]=="rf":
            baseline=indexed.get((f"C4_{p['bandwidth_hz']}_{p['modulation']}_random",r["seed"]))
            threshold="C4.pattern_ber_margin"
        else:continue
        if baseline:
            observed=r["metrics"]["ber"]; reference=baseline["metrics"]["ber"]
            r["comparisons"]={
                "baseline_result":f"{baseline['test_name']}/{baseline['seed']}.json",
                "baseline_location":"inline baseline" if "baseline" in r else "separate result",
                "baseline_parameters":baseline["parameters"],
                "baseline_ber":reference,
                "absolute_ber_delta":observed-reference if observed is not None and reference is not None else None,
                "matched_duration":p["duration_s"]==baseline["parameters"]["duration_s"],
                "threshold":threshold,"status":"THRESHOLD_TBD",
                "interpretation":"Descriptive comparison only; missing bits remain excluded. A short reference does not establish a long-run BER margin.",
            }
            persist(r,output)
    grouped=defaultdict(list)
    for r in records:grouped[r["group"]].append(r)
    lines=["# Goblin Cannon simulated channel report", "",
           "All results use simulated channels. No transmission or RF equipment measurement is represented.", "",
           "## Simulated channel execution summary", "",
           "| Status | Cases |", "| --- | ---: |"]
    for status,count in sorted(Counter(r["status"] for r in records).items()):lines.append(f"| {status} | {count} |")
    lines += ["", "## Simulated channel coverage at a glance", "",
              "| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |", "| --- | ---: | ---: | ---: | ---: |"]
    for group in dict.fromkeys(c.group for c in all_cases):
        counts=Counter(r["status"] for r in grouped[group])
        lines.append(f"| {group} | {len(grouped[group])} | {counts['xfail']} | {counts['THRESHOLD_TBD']} | {counts['unavailable']} |")
    controls=[r for r in records if r['group']=='A4' and r['test_name'].endswith('_offset_0') and r['parameters']['bandwidth_hz']==24000]
    if controls:
        lines += ["", "## Simulated channel principal findings", "",
                  f"- 24 kHz clean controls: {sum(r['observations'].get('valid_headers',0)==0 for r in controls)}/{len(controls)} produced no valid header. Header validity and erased frames are retained alongside conditional BER.",
                  "- Remaining known failures are executable assertions marked `xfail`. Fixed assertions are removed from the expected-failure registry after reviewing their measurements.",
                  "- Runtime budget findings, measured host latency, unsupported capabilities and statistical-duration limits are reported explicitly below."]
    primary=[r for r in records if r['group']=='A1' and r['parameters']['modulation'] in ('qpsk','16qam','64qam') and
             r['parameters']['bandwidth_hz']==10000 and r['parameters']['fec']=='1/2' and r['parameters']['snr_db']==30 and
             any('_'+n+'_' in r['test_name'] for n in ('high_lat_quiet','high_lat_moderate','high_lat_disturbed'))]
    if primary:
        lines += ["", "### Simulated channel primary high-latitude screening points", "",
                  "10 kHz, rate-1/2 FEC, 30 dB SNR, ten-second traces. Missing BER means no comparable bits, not zero errors.","",
                  "| Case | BER | Frame survival | Raw RF goodput bit/s |", "| --- | --- | --- | --- |"]
        for r in primary:
            m=r['metrics'];lines.append(f"| [{r['test_name']}]({r['test_name']}/{r['seed']}.json) | {m['ber']} | {m['frame_survival_fraction']} | {m['goodput_bps']} |")
    for group in dict.fromkeys(c.group for c in all_cases):
        rows=grouped[group]
        lines += ["",f"## Simulated channel group {group}","",
                  "| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |", "| --- | --- | --- | ---: | ---: | ---: | ---: |"]
        if not rows:
            planned=[c for c in all_cases if c.group==group]
            lines.append(f"| Not run ({len(planned)} declared cases) | — | not_run | — | — | — | — |")
        # Each complete grid is also exported for plotting without scraping Markdown.
        csv_rows=[]
        for r in rows:
            m=r["metrics"]
            def fmt(x):return "—" if x is None else f"{x:.6g}"
            p999=m["latency_ms"]["p99_9"]
            path=f"{r['test_name']}/{r['seed']}.json"
            lines.append(f"| [{r['test_name']}]({path}) | {r['kind']} / {r['tier']} | {r['status']} | {fmt(m['ber'])} | {fmt(m['frame_survival_fraction'])} | {fmt(m['goodput_bps'])} | {fmt(p999)} |")
            csv_rows.append(dict(simulated_channel_case=r["test_name"],seed=r["seed"],status=r["status"],
                                 parameters_json=canonical(r["parameters"]).strip(),metrics_json=canonical(m).strip()))
        if csv_rows:
            with (output/f"{group}.csv").open("w",newline="") as f:
                writer=csv.DictWriter(f,fieldnames=list(csv_rows[0]));writer.writeheader();writer.writerows(csv_rows)
        if group=="D2":
            lines += ["", "### Simulated channel D2 freshness comparison", "",
                      "| Target frame survival | Measured channel survival | Channel freshness p99.9 ms | Erasure freshness p99.9 ms |",
                      "| --- | --- | --- | --- |"]
            for r in rows:
                o=r["observations"]
                if "channel_metrics" in o:
                    lines.append(f"| {o['target_survival']} | {o['achieved_channel_frame_survival']} | {o['channel_metrics']['freshness_ms']['p99_9']} | {o['direct_erasure_metrics']['freshness_ms']['p99_9']} |")
        if group=="D1":
            lines += ["", "### Simulated channel D1 source-to-sink overload", "",
                      "Offered wire bits are 1.5×, 3×, or 10× nominal steady payload capacity, including sequence metadata, CRC, FEC and pilot overhead. Startup is included in measured delivery latency.","",
                      "| Case | Created / delivered | Queue maximum | Superseded at framer | Delivered stale | p99.9 ms | First / last window p99.9 ms |",
                      "| --- | --- | --- | --- | --- | --- | --- |"]
            for r in rows:
                p=r['observations'].get('pipeline')
                if not p:continue
                o=p['observations'];m=p['metrics'];windows=m.get('latency_ms_by_window',{})
                first=windows.get('0',{}).get('p99_9');last=windows.get('9',{}).get('p99_9')
                lines.append(f"| {r['test_name']} | {o['messages_created']} / {o['messages_delivered']} | {o['queue_depth_max']} | {o['superseded_messages_consumed']} | {o['stale_messages_delivered']} | {m['latency_ms']['p99_9']} | {first} / {last} |")
        if group in ("A4","C4"):
            lines += ["",f"### Simulated channel {group} paired BER observations", "",
                      "| Case | Reference BER | BER minus reference | Matched duration | Acceptance |",
                      "| --- | --- | --- | --- | --- |"]
            for r in rows:
                if "comparisons" in r:
                    c=r["comparisons"]
                    lines.append(f"| {r['test_name']} | {c['baseline_ber']} | {c['absolute_ber_delta']} | {c['matched_duration']} | THRESHOLD_TBD |")
        if group=="B5":
            lines += ["", "### Simulated channel B5 measured host loopback", "",
                      "Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.","",
                      "2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.","",
                      "| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |",
                      "| --- | --- | --- | --- | --- | --- | --- |"]
            stages=[]
            for r in rows:
                path=output/r["test_name"]/f"{r['seed']}.host.json"
                if not path.exists():continue
                h=json.loads(path.read_text())["observations"]
                if "host_latency_ms_percentiles" not in h:continue
                m=h["host_latency_ms_percentiles"]
                added=h.get("host_added_software_latency_ms_percentiles",{})
                intrinsic=r.get("latency_reference",{}).get("metrics",{}).get("latency_ms",{})
                assertion=h.get('added_software_latency_assertion',h.get('whole_loopback_latency_assertion',{}))
                lines.append(f"| [{r['test_name']}]({path.relative_to(output)}) | {m['p50']} | {m['p99_9']} | {intrinsic.get('p99_9')} | {added.get('p99_9')} | {added.get('max')} | {assertion.get('status')} |")
                for key in ("host_source_to_framer_ms","host_intake_per_message_ms","host_tx_per_block_ms","host_channel_per_block_ms","host_audio_wait_per_block_ms","host_rx_per_block_ms"):
                    if key+"_percentiles" in h:stages.append((r['test_name'],key,h[key+"_percentiles"]))
            lines += ["", "#### Simulated channel B5 stage call durations", "",
                      "TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.","",
                      "| Case | Stage | p50 ms | p99.9 ms | Max ms |", "| --- | --- | --- | --- | --- |"]
            for name,stage,m in stages:lines.append(f"| {name} | {stage} | {m['p50']} | {m['p99_9']} | {m['max']} |")
            lines += ["", "#### Simulated channel B5 transmission and modem residence", "",
                      "Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.", "",
                      "| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |", "| --- | --- | --- | --- | --- | --- |"]
            for r in rows:
                raw=r['observations']; d=raw.get('modem_delay_estimates',{})
                serialization=percentiles(raw.get('nominal_message_serialization_ms',[]))
                lines.append(f"| {r['test_name']} | {serialization['p50']} | {d.get('tx_rrc_group_delay_ms')} | {d.get('rx_rrc_group_delay_ms')} | {d.get('equalizer_decision_delay_ms')} | {d.get('viterbi_lookahead_nominal_ms')} |")
        if group=="B1":
            lines += ["", "### Simulated channel B1 affected-frame errors", "",
                      "Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.","",
                      "| Case | Affected frames | Affected frame error rate |", "| --- | --- | --- |"]
            for r in rows:
                if 'agc_affected_frames' in r['observations']:
                    lines.append(f"| {r['test_name']} | {r['observations']['agc_affected_frames']} | {r['metrics']['agc_affected_frame_error_rate']} |")
        if group=="E2":
            lines += ["", "### Simulated channel E2 local metric definitions", "",
                      "| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |",
                      "| --- | --- | --- | --- | --- |"]
            for r in rows:
                m=r["metrics"]
                lines.append(f"| {r['test_name']} | {m['uptime_fraction']} | {m['usable_time_fraction']} | {m['goodput_bps']} | Unavailable: audit definitions/standby instrumentation |")
        for r in rows:
            if r["group"]=="C1" and "table" in r["observations"]:
                lines += ["", "### Simulated channel C1 performance-table layout", "",
                          "| BW | Modulation / FEC | Channel | Empirical SNR BER 1e-3 | Empirical SNR BER 1e-5 | Established operating limit |",
                          "| --- | --- | --- | --- | --- | --- |"]
                for entry in r["observations"]["table"]:
                    lines.append(f"| {entry['bandwidth_hz']} | {entry['modulation']} / {entry['fec']} | {entry['preset']} | {entry['empirical_snr_at_0.001']} | {entry['empirical_snr_at_1e-05']} | Not established by screening duration |")
    lines += ["", "## Simulated channel — Defects found", ""]
    failures=defaultdict(list)
    for r in records:
        for assertion in r["assertions"]:
            if assertion["status"] in ("xfail","fail","xpass"):
                failures[(assertion["status"],assertion["reason"])].append(r)
        if r["status"]=="error":failures[("harness error",r.get("reason",""))].append(r)
    if not failures:lines.append("No observed assertion failures in the selected cases.")
    for (status,reason),rows in failures.items():
        lines.append(f"- **{status}** — {reason}")
        # Every xfail remains individually linked, rather than disappearing in a count.
        lines.append("  Cases: "+", ".join(f"[{r['test_name']}]({r['test_name']}/{r['seed']}.json)" for r in rows)+".")
    lines += ["", "## Simulated channel — Open thresholds", "", "| ID | Status | Proposed value / approach | Reason |", "| --- | --- | --- | --- |"]
    for name,(proposal,reason) in OPEN_THRESHOLDS.items():lines.append(f"| {name} | THRESHOLD_TBD | {proposal} | {reason} |")
    lines += ["", "## Simulated channel coverage and limitations", "",
              "- These follow-up tests include Adam-authorized fixes to clock/gain/equalizer tracking, transmit buffering, auction freshness and receiver sequencing/gaps. Each record identifies its tested source snapshot; earlier audit records remain historical.",
              "- Carrier correction is disabled. The adaptive equalizer includes a first-order common phase coefficient; it has no frequency estimate or frequency accumulator. Clock recovery adjusts sample instants only.",
              "- 24 kHz use of the F.1487 model is an extrapolation beyond that recommendation's approximately 12 kHz scope.",
              "- A1 uses declared 10-second screening traces. The requested grids and long 600-second quick cases are not reduced to meet a runtime budget.",
              "- BER excludes erased/unobserved bits: inspect bit observation fraction and frame survival alongside it. No acquisition is never reported as zero BER.",
              "- Symbol-probe goodput counts correct RF-frame bits; message-probe goodput counts application bytes. They are labeled separately in JSON.",
              "- Total source-to-sink latency includes startup and audio buffering. B5 applies 2.1 ms to per-message added processing/buffering above a matched one-sample intrinsic reference. Its separate paced host observations include CPU/OS scheduling. Transmission and modem residence estimates are also reported. Physical audio devices and network sockets are outside this simulated loopback.",
              "- Usable-time is an explicitly labeled local one-second delivery-window proxy. Exact STAC comparability is unavailable pending audit definitions/standby instrumentation.",
              "- Conditional unsupported features, missing recordings, unrun soak cases, and open thresholds are never counted as passes.",
              "- D6 cannot count AEAD authentication failures at A1 error rates because production exposes AES-CTR/CRC only. Its replay check exercises captured framed messages at the deframer; it does not claim an encrypted RF replay audit with wall-clock timestamp validation.",
              "- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.",
              "", f"See [TESTING.md]({os.path.relpath(REPO/'TESTING.md',output.resolve())}) and [source audit/questions]({os.path.relpath(REPO/'tests/simulated_channel/QUESTIONS.md',output.resolve())})."]
    executions=sorted(output.glob("EXECUTION-*.json"))
    if not executions and (output/"EXECUTION.json").exists():executions=[output/"EXECUTION.json"]
    if executions:
        lines += ["", "## Simulated channel runtime observations", "",
                  "| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |",
                  "| --- | --- | ---: | ---: | --- |"]
        for path in executions:
            data=json.loads(path.read_text())
            complete=data.get("complete_tier",data['selected_cases'] in (243,9023,1))
            selection="complete tier" if complete else "selected rerun"
            budget=data["budget_seconds"]
            within="yes" if data["elapsed_seconds"]<=budget else "**NO**"
            lines.append(f"| {data['tier']} / {selection} | {data['executed_cases']} / {data['selected_cases']} | {data['elapsed_seconds']:.3f} | {budget} | {within} |")
        lines.append("Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.")
    (output/"SUMMARY.md").write_text("\n".join(lines)+"\n")


def reclassify(output,all_cases):
    known=load_known()
    indexed={c.name:c for c in all_cases}
    for path in sorted(output.glob("*/[0-9]*.json")):
        if path.name.endswith(".host.json"):continue
        r=json.loads(path.read_text())
        c=indexed.get(r["test_name"])
        if c is None or r["status"] in ("error","unavailable","pending_analysis") or c.parameters["mode"]=="analysis":continue
        previous={a["assertion"] for a in r["assertions"]}
        if previous!=set(c.checks) or r["parameters"]["mode"]!=c.parameters["mode"]:continue
        r["status"],r["assertions"]=evaluate(c,r["observations"],r["metrics"],known)
        r["expected_failure_registry_sha256"]=hashlib.sha256(canonical(known).encode()).hexdigest()
        persist(r,output)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--tier",choices=("quick","full","soak"),default="quick")
    parser.add_argument("--group",action="append",default=[])
    parser.add_argument("--exclude-group",action="append",default=[],help="record a partial-tier selection, e.g. B5 measured separately on a quiet host")
    parser.add_argument("--case",action="append",default=[])
    parser.add_argument("--list",action="store_true")
    parser.add_argument("--probe",type=Path,default=REPO/"build/goblin_cannon_simulated_channel_probe")
    parser.add_argument("--results",type=Path,default=REPO/"results")
    parser.add_argument("--jobs",type=int,default=4)
    parser.add_argument("--seed",type=int,default=None)
    parser.add_argument("--seeds",type=int,nargs="+",help="independent seeds; full declared duration for each")
    parser.add_argument("--profile",choices=("legacy","recovery"),default="legacy")
    parser.add_argument("--campaign",choices=("matrix","polar_screen","polar_long","psk_quick","psk_screen","psk_followup","psk_snr","psk_latency","encoding_quick","encoding_screen","encoding_followup","encoding_snr","encoding_latency"))
    parser.add_argument("--git-commit")
    parser.add_argument("--source-digest")
    parser.add_argument("--resume",action="store_true",help="reuse only parameter-identical records")
    parser.add_argument("--report-only",action="store_true")
    parser.add_argument("--reclassify",action="store_true",help="apply the reviewed exact-case expected-failure registry to existing observations; no measurements change")
    parser.add_argument("--allow-non-avx512",action="store_true")
    parser.add_argument("--recordings",type=Path,help="receive-only fc32 IQ provenance manifest for E4")
    args=parser.parse_args()
    if args.jobs<1:parser.error("--jobs must be positive")
    if args.seed is not None and not 0<=args.seed<2**32:parser.error("--seed must be an unsigned 32-bit integer")
    if args.seed is not None and args.seeds:parser.error("choose --seed or --seeds")
    if args.seeds and (len(args.seeds)!=len(set(args.seeds)) or any(not 0<=s<2**32 for s in args.seeds)):
        parser.error("--seeds must be distinct unsigned 32-bit integers")
    all_cases=matrix()
    if args.profile=="recovery":
        for c in all_cases:
            if c.parameters.get("campaign","matrix")=="matrix":
                c.parameters.update(RECOVERY_PROFILE)
                c.parameters["rf_profile"]="recovery"
    if args.recordings:
        manifest=json.loads(args.recordings.read_text())
        all_cases=[c for c in all_cases if c.group!="E4"]
        from catalog import case
        required={"path","sha256","sample_rate_hz","format","frequency_hz","utc","receiver_location","source_url","permission"}
        for index,entry in enumerate(manifest):
            if required-entry.keys():parser.error(f"Recording {index} lacks {sorted(required-entry.keys())}")
            path=Path(entry["path"]).resolve()
            if entry["format"]!="fc32_iq_le" or entry["sample_rate_hz"]!=48000:
                parser.error("E4 currently requires 48 ksample/s little-endian float32 IQ; convert explicitly and document provenance")
            if hashlib.sha256(path.read_bytes()).hexdigest()!=entry["sha256"]:parser.error("recording checksum mismatch")
            if path.stat().st_size%8:parser.error("recording ends inside an IQ sample")
            duration=path.stat().st_size/8/48000-0.25
            if duration<=0:parser.error("recording is too short for a startup trace")
            all_cases.append(case("E4",f"recording_{index}","characterize","full",noise_file=str(path),
                                  bandwidth_hz=10000,snr_db=20,duration_s=duration,recording_provenance=entry,
                                  notes=["Receive-only recorded noise bed; no looping; simulated channel only."]))
    cases=[c for c in all_cases if c.tier==args.tier and c.group not in args.exclude_group and (not args.group or c.group in args.group) and (not args.case or c.name in args.case)
           and (not args.campaign or c.parameters.get("campaign","matrix")==args.campaign)]
    if args.seeds:
        cases=[copy.deepcopy(c) for c in cases for _ in args.seeds]
        for i,c in enumerate(cases):c.parameters["seed"]=args.seeds[i%len(args.seeds)]
    if args.list:
        print(canonical({"report_header":"simulated channel manifest","tier":args.tier,"count":len(cases),
                         "cases":[dict(name=c.name,kind=c.kind,tier=c.tier,parameters=c.parameters,unavailable=c.unavailable) for c in cases]}),end="")
        return 0
    args.results.mkdir(parents=True,exist_ok=True)
    if args.report_only:
        if args.reclassify:reclassify(args.results,all_cases)
        report(args.results,all_cases);return 0
    args.git_commit=args.git_commit or revision()
    args.source_digest=args.source_digest or source_digest()
    args.probe=args.probe.resolve()
    if not args.probe.is_file():parser.error(f"probe not built: {args.probe}")
    known=load_known()
    planned=[]
    for c in cases:
        if args.seed is not None:c.parameters["seed"]=args.seed
        if args.allow_non_avx512:c.parameters["require_avx512"]=0
        path=args.results/c.name/f"{c.parameters['seed']}.json"
        if args.resume and path.exists():
            existing=json.loads(path.read_text())
            if existing["parameters"]==full_parameters(c,args.git_commit,args.source_digest) and existing["status"] not in ("error","pending_analysis"):
                continue
        planned.append(c)
    print(f"simulated channel: {len(planned)} cases, tier={args.tier}, jobs={args.jobs}",flush=True)
    # Longest traces first avoids a 600-second pure-noise trace becoming a
    # serial tail after the short cases. This changes no inputs or durations.
    planned.sort(key=lambda c:c.parameters["duration_s"]*(3 if c.parameters["pure_noise"] else 1),reverse=True)
    start=time.monotonic()
    statuses=Counter()
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures={pool.submit(execute,c,args,known):c for c in planned}
        completed=0
        for future in concurrent.futures.as_completed(futures):
            result=future.result()
            host_assertion=result.get("host_observations",{}).get("added_software_latency_assertion",{})
            if host_assertion.get("status") in ("fail","xpass"):statuses["host_latency_fail"]+=1
            persist(result,args.results)
            statuses[result["status"]]+=1;completed+=1
            if result["status"] in ("error","fail") or completed%50==0 or completed==len(planned):
                print(f"simulated channel: {completed}/{len(planned)} {result['test_name']} {result['status']}",flush=True)
    analysis(args.results,cases,args)
    elapsed=time.monotonic()-start
    execution=dict(report_header="simulated channel non-canonical execution observations",tier=args.tier,
                   elapsed_seconds=elapsed,budget_seconds={"quick":120,"full":1800,"soak":43200}[args.tier],
                   jobs=args.jobs,host=platform.platform(),python=sys.version,selected_cases=len(cases),executed_cases=len(planned),statuses=dict(statuses),
                   complete_tier=not args.group and not args.exclude_group and not args.case and not args.resume and not args.campaign,
                   selection=dict(groups=args.group,excluded_groups=args.exclude_group,cases=args.case,seed=args.seed,seeds=args.seeds,profile=args.profile,campaign=args.campaign,resume=args.resume),
                   git_commit=args.git_commit,source_tree_sha256=args.source_digest,
                   parameter_records=[f"{c.name}/{c.parameters['seed']}.json" for c in cases])
    serialized=json.dumps(execution,indent=2,sort_keys=True)+"\n"
    (args.results/"EXECUTION.json").write_text(serialized)
    # Selected follow-up runs must not erase a complete tier's budget finding.
    tag=args.tier if execution["complete_tier"] else args.tier+"-selection-"+hashlib.sha256(canonical(execution["selection"]).encode()).hexdigest()[:12]
    (args.results/f"EXECUTION-{tag}.json").write_text(serialized)
    report(args.results,all_cases)
    print(f"simulated channel: {elapsed:.3f}s {dict(statuses)}; {args.results/'SUMMARY.md'}",flush=True)
    return 1 if statuses["error"] or statuses["fail"] or statuses["host_latency_fail"] else 0


if __name__=="__main__":
    sys.exit(main())
