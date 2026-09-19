from channel_description import context_html
"""Render recorded simulated channel recovery evidence. No synthetic results."""
from collections import Counter, defaultdict
from html import escape
import json


def build(root, start, end, *, allow_incomplete=False):
    directory=root/"results/recovery-improvements"
    read=lambda path:json.loads(path.read_text())
    manifest=read(directory/"VALIDATION.json")
    if manifest.get("campaign_status")!="complete" and not allow_incomplete:
        raise ValueError("The recovery campaign is incomplete; publish only completed evidence")
    base="https://github.com/adamdeprince/goblin-cannon/blob/main/"
    url=lambda path:base+str(path.relative_to(root))
    link=lambda path,label:f'<a href="{escape(url(path))}">{escape(label)}</a>'
    number=lambda value:"Unobserved" if value is None else f"{value:,.3f}"
    def spread(values,scale=1,suffix=""):
        finite=[v*scale for v in values if v is not None]
        if not finite:return "Unobserved"
        observed=f" ({len(finite)}/{len(values)} runs observed)" if len(finite)!=len(values) else ""
        return f"{min(finite):,.2f}–{max(finite):,.2f}{suffix}{observed}"
    modes={"qpsk":"QPSK / 4-QAM","16qam":"16-QAM","64qam":"64-QAM"}
    variants={"legacy":"Legacy startup","compact":"Protected compact header","recovery":"Recurring markers",
              "reselect":"Markers + tap reselection","fractional":"Markers + reselection + T/2"}
    groups=defaultdict(Counter);statuses=Counter();kept={};defects=[];count=0
    for path in sorted(directory.glob("*/[0-9]*.json")):
        if path.name.endswith(".host.json"):continue
        record=read(path);count+=1;statuses[record["status"]]+=1;groups[record["group"]][record["status"]]+=1
        if record["parameters"]["source_tree_sha256"]!=manifest["source_tree_sha256"]:
            raise ValueError(f"Mixed source snapshot: {path}")
        if record["parameters"].get("campaign") in ("polar_screen","polar_long") or record["group"]=="B5":
            kept[record["test_name"],record["seed"]]=(path,record)
        for assertion in record["assertions"]:
            if assertion["status"] in ("xfail","fail","xpass"):
                defects.append((path,record,assertion))
    if count!=manifest["main_cases"] or dict(statuses)!=manifest["main_statuses"]:
        raise ValueError("Recorded case counts differ from validation manifest")
    seed=manifest["seeds"][0]
    polar=[];messages=[];long_rows=[];screen_rows=[];comparison_rows=[];comparisons={}
    for bw in (10000,24000):
        for mode,label in modes.items():
            screen_cells=[]
            for preset in ("quiet","moderate","disturbed"):
                for variant in variants:
                    for group,target in (("A2",polar),("E2",messages)):
                        name=f"{group}_recovery_{bw}_{mode}_high_lat_{preset}_{variant}"
                        path,record=kept[name,seed]
                        observations={k:v for k,v in record["observations"].items() if not isinstance(v,(list,dict))}
                        target.append(dict(preset=preset,span=variant,parameters=record["parameters"],
                            observations=observations,metrics=record["metrics"],source=url(path)))
                        if group=="E2" and variant=="fractional":
                            screen_cells.append(f'<td>{link(path,number(record["metrics"]["goodput_bps"]))}</td>')
                before=[kept[f"E2_recovery_{bw}_{mode}_high_lat_{preset}_legacy",s] for s in manifest["seeds"]]
                after=[kept[f"E2_recovery_{bw}_{mode}_high_lat_{preset}_fractional",s] for s in manifest["seeds"]]
                matched_fields=("bandwidth_hz","modulation","fec","duration_s","seed","delay_spread_ms",
                    "doppler_spread_hz","path_gains_db","snr_db","equalizer_feedforward_taps",
                    "equalizer_feedback_taps","equalizer_delay_symbols","training_symbols",
                    "source_load_factor","message_interval_s","chunk_samples")
                for (_,old),(_,new) in zip(before,after):
                    if any(old["parameters"][k]!=new["parameters"][k] for k in matched_fields):
                        raise ValueError("Polar before/after channel or stream parameters differ")
                old_rates=[r["metrics"]["goodput_bps"] for _,r in before]
                new_rates=[r["metrics"]["goodput_bps"] for _,r in after]
                comparisons[bw,mode,preset]=(old_rates,new_rates)
                improved=sum(new>old for old,new in zip(old_rates,new_rates))
                sources="<br>".join(title+": "+" / ".join(link(p,str(r["seed"])) for p,r in records)
                                      for title,records in (("Before",before),("Updated",after)))
                comparison_rows.append(f'<tr><th scope="row">{bw//1000} kHz · {label}<br>{preset}</th>'
                    f'<td>{spread(old_rates)}</td><td>{spread(new_rates)}</td><td>{improved} / {len(after)}</td><td>{sources}</td></tr>')
                repetitions=[kept.get((f"E2_polar_long_{bw}_{mode}_high_lat_{preset}",s)) for s in manifest["seeds"]]
                if any(r is None for r in repetitions):
                    if not allow_incomplete:raise ValueError("Missing long-run replicate")
                    long_rows.append(f'<tr><th scope="row">{bw//1000} kHz · {label}<br>{preset}</th><td colspan="6">Pending: {sum(r is not None for r in repetitions)} of 3 replicates completed.</td></tr>')
                    continue
                values=[r["metrics"]["goodput_bps"] for _,r in repetitions]
                survival=[r["metrics"]["message_delivery_fraction_of_framed"] for _,r in repetitions]
                silences=[r["metrics"]["delivery_silence_ms"]["max"] for _,r in repetitions]
                freshness=[r["metrics"]["freshness_ms"]["p99_9"] for _,r in repetitions]
                durations={r["parameters"]["duration_s"] for _,r in repetitions}
                if len(durations)!=1:raise ValueError("Long-run durations differ across seeds")
                sources=" / ".join(link(p,str(r["seed"])) for p,r in repetitions)
                long_rows.append(f'<tr><th scope="row">{bw//1000} kHz · {label}<br>{preset}</th><td>{next(iter(durations)):,} s</td>'
                    f'<td>{spread(values)}</td><td>{spread(survival,100,"%")}</td><td>{spread(freshness,1," ms")}</td><td>{spread(silences,.001," s")}</td><td>{sources}</td></tr>')
            screen_rows.append(f'<tr><th scope="row">{bw//1000} kHz · {label}</th>{"".join(screen_cells)}</tr>')
    latency_records={key:value for key,value in kept.items() if value[1]["group"]=="B5"}
    latency_manifest=manifest
    latency_directory=directory
    if manifest.get("latency_results_directory"):
        latency_directory=directory/manifest["latency_results_directory"]
        latency_manifest=read(latency_directory/"VALIDATION.json")
        if latency_manifest["campaign_status"]!="complete":raise ValueError("Quiet-host latency validation is incomplete")
        if manifest["quiet_latency_status"]!="complete" or latency_manifest["host"]!=manifest["latency_host"]:
            raise ValueError("Quiet-host manifest and selected host differ")
        quiet_records={}
        for path in sorted(latency_directory.glob("*/[0-9]*.json")):
            if path.name.endswith(".host.json"):continue
            record=read(path)
            if record["group"]!="B5":raise ValueError("Unexpected quiet-host test group")
            p=record["parameters"]
            if p["source_tree_sha256"]!=manifest["source_tree_sha256"] or p["git_commit"]!=latency_manifest["git_commit"]:
                raise ValueError("Quiet-host source provenance differs")
            quiet_records[record["test_name"],record["seed"]]=(path,record)
        if quiet_records.keys()!=latency_records.keys():raise ValueError("Quiet-host latency selection differs from the baseline")
        if dict(Counter(r["status"] for _,r in quiet_records.values()))!=latency_manifest["statuses"]:
            raise ValueError("Quiet-host status counts differ from validation manifest")
        comparable=lambda p:{k:v for k,v in p.items() if k not in ("git_commit","require_avx512")}
        for key,(_,record) in quiet_records.items():
            baseline=latency_records[key][1]["parameters"]
            if comparable(record["parameters"])!=comparable(baseline):raise ValueError("Quiet-host test parameters differ from the baseline")
            if record["observations"]["demapper"]!=latency_manifest["runtime_isa"]:
                raise ValueError("Quiet-host ISA differs from validation manifest")
        latency_records=quiet_records
    latency=[];latency_rows=[]
    for (name,s),(path,record) in sorted(latency_records.items()):
        host_path=path.with_name(f"{s}.host.json")
        host=read(host_path)
        if host["parameters"]!=record["parameters"]:raise ValueError("Latency sidecar parameters differ")
        observation=host["observations"];p=record["parameters"]
        added=observation["host_added_software_latency_ms_percentiles"]
        total=observation["host_latency_ms_percentiles"]
        state=observation["added_software_latency_assertion"]["status"]
        display_name=str(p["bandwidth_hz"]//1000)+" kHz · "+modes[p["modulation"]]+(" · long span" if "polar_span" in name else " · short span")
        latency_rows.append(f'<tr><th scope="row">{link(host_path,display_name)}</th>'
            f'<td>{number(added["p50"])}</td><td>{number(added["p99"])}</td><td>{number(added["p99_9"])}</td>'
            f'<td>{number(added["max"])}</td><td>{number(total["p99_9"])}</td>'
            f'<td>{number(record["latency_reference"]["metrics"]["latency_ms"]["p99_9"])}</td><td>{escape(state)}</td></tr>')
        latency.append(dict(parameters=p,metrics=record["metrics"],host_metrics={k:v for k,v in observation.items()
            if k.endswith("percentiles") or k=="added_software_latency_assertion"},source=url(path),host_source=url(host_path)))
    status_columns=("pass","characterized","THRESHOLD_TBD","xfail","unavailable","fail","error")
    summary_rows="".join(f'<tr><th scope="row">{escape(group)}</th>'+"".join(f'<td>{counts[k]}</td>' for k in status_columns)+"</tr>"
                         for group,counts in groups.items())
    defect_rows="".join(f'<tr><th scope="row">{link(path,r["test_name"])} · seed {r["seed"]}</th>'
                       f'<td>{escape(a["assertion"])}</td><td>{escape(a["reason"] or a["status"])}</td></tr>' for path,r,a in defects)
    provenance=f'Base commit <code>{manifest["git_commit"][:12]}</code>; tested source SHA-256 <code class="source-hash">{manifest["source_tree_sha256"]}</code>. '+link(directory/"source-snapshot.tar.gz","Tested source snapshot")
    report=link(directory/"REPORT.md","Read the simulated channel findings →")
    host_name=manifest["latency_host"]
    quiet_note="Quiet-host validation is pending." if manifest.get("quiet_latency_status")!="complete" else "Quiet-host validation completed."
    if latency_directory!=directory:
        quiet_note+=f' {escape(latency_manifest["runtime_isa"])}; 12 configurations run serially from commit <code>{latency_manifest["git_commit"][:12]}</code>. '+link(latency_directory/"COMPARISON.md","Quiet-host results and AVX-512 comparison")+"."
    moderate_before,moderate_after=comparisons[24000,"qpsk","moderate"]
    long_moderate=[kept.get(("E2_polar_long_24000_qpsk_high_lat_moderate",s)) for s in manifest["seeds"]]
    long_disturbed=[kept.get(("E2_polar_long_24000_qpsk_high_lat_disturbed",s)) for s in manifest["seeds"]]
    moderate_rates=spread([r["metrics"]["goodput_bps"] for _,r in long_moderate]) if all(long_moderate) else "Pending"
    moderate_delivery=spread([r["metrics"]["message_delivery_fraction_of_framed"] for _,r in long_moderate],100,"%") if all(long_moderate) else "Pending"
    disturbed_rates=spread([r["metrics"]["goodput_bps"] for _,r in long_disturbed]) if all(long_disturbed) else "Pending"
    disturbed_silence=number(max(r["metrics"]["delivery_silence_ms"]["max"] for _,r in long_disturbed)/1000) if all(long_disturbed) else "Pending"
    section=f'''{start}
    <section class="evidence-section" id="benchmarks"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Recovery campaign · recorded evidence</p>
        <h2 class="section-title">Simulated channel.<br>Recover and keep measuring.</h2>
        <p class="section-intro">Recurring synchronization, a protected compact header, sparse tap reselection and half-symbol equalization are measured separately. Results count useful messages after FEC, alongside raw RF frames. Recovery consumes airtime; the comparisons include that cost.</p></header>
      <div class="evidence-stats"><div><strong>166 <small>symbols</small></strong><span>Protected header, down from 384. Training and acquisition are additional.</span></div>
        <div><strong>3 <small>seeds</small></strong><span>Independent polar runs, with full declared durations.</span></div>
        <div><strong>4 / 16 / 64</strong><span>Primary QAM orders tested at 10 and 24 kHz.</span></div></div>
      <h3>Simulated channel · added processing and buffering</h3>
      <p class="evidence-provenance">Current wall-clock host: <code>{escape(host_name)}</code>. {quiet_note} The 2.1 ms allowance applies to added processing/buffering. Each message is compared with its one-sample simulated reference before percentiles are computed; total time and modem/transmission/startup remain separate. No physical audio device is included.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel latency" tabindex="0"><table class="evidence-table">
      <caption>Simulated channel · wall-clock milliseconds · recurring markers enabled</caption><thead><tr><th>Configuration</th><th>Added p50</th><th>Added p99</th><th>Added p99.9</th><th>Added max</th><th>Total p99.9</th><th>Reference p99.9</th><th>Status</th></tr></thead>
      <tbody>{''.join(latency_rows)}</tbody></table></div><p class="evidence-provenance">{provenance}</p>
    </div></section>
    <section class="evidence-section polar-section" id="rf-simulation"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">A2 / E2 · characterize / full</p><h2 class="section-title">Simulated channel.<br>Progress on the polar plan.</h2>
        <p class="section-intro">The high-latitude campaign for the route peaking near 71°N is complete: {manifest['campaign_counts']['polar_screen']} comparison cases and {manifest['campaign_counts']['polar_long']} longer runs on <code>avx10</code>, across three independent seeds. Quiet/moderate/disturbed runs last 6000/300/100 simulated seconds per seed. The later <code>naamah</code> rerun measures software latency.</p></header>
      <div class="evidence-columns" id="polar-findings"><div class="evidence-method">
        <h3>Simulated channel · recovery improves delivery</h3>
        <p>At 24 kHz with QPSK under moderate fading, useful delivery rises from <strong>{spread(moderate_before)} to {spread(moderate_after)} bit/s</strong> in the matched ten-second screens. All three seeds improve. The longer updated runs deliver <strong>{moderate_rates} bit/s</strong>, with <strong>{moderate_delivery}</strong> of framed messages surviving.</p>
        <p>Recovery markers cost airtime. Some quiet-channel QPSK seeds deliver less useful data with the updated profile. The before/after table retains every configuration, including unchanged zero-delivery cases.</p>
      </div><div class="evidence-method evidence-findings">
        <h3>Simulated channel · disturbed conditions remain poor</h3>
        <p>The longer disturbed traces deliver only <strong>{disturbed_rates} bit/s</strong> with 24 kHz QPSK, and silence reaches <strong>{disturbed_silence} seconds</strong>. All tested 10 kHz constellations deliver zero useful messages in those disturbed traces.</p>
        <p>The route latitude selects high-latitude fading presets at a fixed nominal SNR. These runs do not predict which preset or SNR the actual route will experience, or establish route availability. The separate geometric propagation estimate remains unchanged.</p>
      </div></div>
      <h3>Simulated channel · before and after, every polar configuration</h3>
      <p class="evidence-provenance">Useful application bits/s after FEC and framing. Each range spans the same three seeds, ten seconds per run, at 30 dB nominal SNR. Both profiles use the same delay-spanning equalizer geometry. Updated includes the compact protected header, recurring markers, tap reselection and T/2 input. Improved seeds count paired increases in useful bits/s; these characterizations have no acceptance threshold.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel polar before and after" tabindex="0"><table class="evidence-table"><caption>Simulated channel · legacy startup versus complete recovery profile</caption><thead><tr><th>Configuration / preset</th><th>Before bit/s</th><th>Updated bit/s</th><th>Improved seeds</th><th>Seed records</th></tr></thead><tbody>{''.join(comparison_rows)}</tbody></table></div>
      {context_html(historical=True)}
      <div class="model-assumptions"><span>Two Rayleigh paths</span><span>Doppler spread: Gaussian spectrum per tap (2σ)</span><span>30 dB nominal SNR</span><span>Carrier correction off</span></div>
      <div id="rf-explorer" class="rf-explorer" hidden><div class="rf-controls">
        <label for="rf-bandwidth">Bandwidth<select id="rf-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
        <label for="rf-modulation">Constellation<select id="rf-modulation">{''.join(f'<option value="{m}">{label}</option>' for m,label in modes.items())}</select></label>
        <label for="rf-span">Receiver configuration<select id="rf-span">{''.join(f'<option value="{v}"'+(' selected' if v=='fractional' else '')+f'>{label}</option>' for v,label in variants.items())}</select></label>
        <label for="rf-preset">Delay spread / Doppler spread<select id="rf-preset"><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
        <label for="rf-layer">Measurement<select id="rf-layer"><option value="messages">Useful messages after FEC</option><option value="rf">Raw RF frames before FEC</option></select></label></div>
        <div id="rf-output" aria-live="polite" aria-atomic="true"><div class="rf-outcome"><p class="section-label">Recorded simulated channel result</p><h3 id="rf-outcome-title"></h3><p id="rf-outcome-note"></p></div>
          <div class="rf-metrics"><div><span id="rf-survival-label"></span><strong id="rf-survival"></strong><small id="rf-frames"></small></div>
            <div><span id="rf-ber-label"></span><strong id="rf-ber"></strong><small id="rf-observed"></small></div>
            <div><span id="rf-goodput-label"></span><strong id="rf-goodput"></strong><small id="rf-goodput-note"></small></div>
            <div><span>Headers / lock losses</span><strong id="rf-lock"></strong><small id="rf-acquisition"></small></div></div>
          <div class="rf-comparison" id="rf-comparison" aria-label="Simulated channel survival comparison"></div><p class="rf-parameters" id="rf-parameters"></p><a class="evidence-link" id="rf-record" href="#rf-static">Full parameters and observations →</a></div></div>
      <div class="table-scroll" id="rf-static" role="region" aria-label="Simulated channel useful goodput" tabindex="0"><table class="evidence-table"><caption>Simulated channel · complete recovery profile · useful message bits/s · ten-second screen, seed {seed}</caption><thead><tr><th>Configuration</th><th>Quiet</th><th>Moderate</th><th>Disturbed</th></tr></thead><tbody>{''.join(screen_rows)}</tbody></table></div>
      <h3>Simulated channel · longer runs, three independent seeds</h3><p class="evidence-provenance">Ranges show the minimum and maximum across seeds, not confidence bounds. Quiet/moderate/disturbed runs retain 6000/300/100 simulated seconds each, satisfying the F.1487 duration terms at the declared BER 1e-3 planning target. These are message-delivery measurements; BER 1e-5 certification is not claimed. Silence includes startup and the censored end of the observation.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel long polar measurements" tabindex="0"><table class="evidence-table"><caption>Simulated channel · all deliveries counted; no time or sample reduction</caption><thead><tr><th>Configuration / preset</th><th>Each run</th><th>Useful bits/s</th><th>Delivered / framed</th><th>Freshness p99.9</th><th>Longest silence</th><th>Seed records</th></tr></thead><tbody>{''.join(long_rows)}</tbody></table></div>
      <p class="evidence-provenance">The explorer selects saved results; it does not simulate RF in the browser. Its seed is {seed}. Nominal SNR uses a unit-mean constellation reference. Conditional BER excludes missing bits; the observation fraction is shown separately. The 24 kHz Watterson model extrapolates beyond F.1487's approximately 12 kHz scope. This custom single-carrier waveform is not certified MIL-STD-188-110C performance. No recorded-band noise beds are available.</p>
    </div></section>
    <section class="evidence-section" id="test-results"><div class="section-inner"><header class="evidence-head"><p class="section-label">Full recorded matrix</p><h2 class="section-title">Simulated channel.<br>The test ledger.</h2><p class="section-intro">{count:,} cases are recorded. Characterizations have no pass/fail threshold. Open margins remain THRESHOLD_TBD; known failing assertions remain visible as xfail.</p></header>
      <div class="table-scroll" role="region" aria-label="Simulated channel test ledger" tabindex="0"><table class="evidence-table"><caption>Simulated channel · cases, including independent seeds</caption><thead><tr><th>Group</th>{''.join(f'<th>{escape(s)}</th>' for s in status_columns)}</tr></thead><tbody>{summary_rows}</tbody></table></div>
      <details class="evidence-details"><summary>Simulated channel · defects found</summary><div class="table-scroll"><table class="evidence-table defect-table"><thead><tr><th>Case</th><th>Assertion</th><th>Finding</th></tr></thead><tbody>{defect_rows}</tbody></table></div></details>
      <p class="evidence-provenance">Runtime overruns, remaining receiver limits, unavailable recordings, open crypto/scheduler issues and manual soak coverage are recorded in the report. Host timings are separate from deterministic result JSON.</p>
      <div class="evidence-links">{report}{link(directory/'SUMMARY.md','All group tables →')}{link(root/'TESTING.md','Run the campaigns →')}{link(root/'results/fixes-2-5/FIXES.md','Previous validation →')}</div><p class="evidence-provenance">{provenance}</p>
    </div></section>
{end}'''
    data=dict(schema_version=2,report_header="Goblin Cannon simulated channel recovery HTML evidence",
              git_commit=manifest["git_commit"],source_tree_sha256=manifest["source_tree_sha256"],
              seeds=manifest["seeds"],polar=polar,messages=messages,latency=latency,
              latency_host=host_name,latency_validation_source=url(latency_directory/"VALIDATION.json"),
              validation_source=url(directory/"VALIDATION.json"))
    return section,"// Generated from recorded simulated channel results.\nglobalThis.GoblinChannelResults = "+json.dumps(data,separators=(",",":"),allow_nan=False)+";\n"
