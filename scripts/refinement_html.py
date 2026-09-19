from channel_description import context_html
"""Render the completed BCH/diversity/cadence simulated channel evidence."""
import json
from html import escape

from refinement_results import DIRECTORY, SEEDS, load, read, spread, url


def row(r):
    sources = " / ".join(f'<a href="{escape(u)}">{s}</a>' for s,u in zip(SEEDS,r["sources"]))
    return (f'<tr><th scope="row">{escape(r["label"])}</th><td>{spread(r["goodput"])}</td>'
            f'<td>{spread(r["fresh_goodput"])}</td><td>{spread(r["freshness"])}</td>'
            f'<td>{spread(r["silence"],.001,3)}</td><td>{r["cadence"]["payload_airtime_fraction"]:.1%}</td>'
            f'<td>{sources}</td></tr>')


def build():
    data = load()
    m = data["manifest"]
    if read(DIRECTORY / "VALIDATION.json") != m:
        raise ValueError("Refinement validation is stale")
    selected = [r for r in data["rows"] if r["bandwidth"] == 24000 and r["preset"] == "moderate"]
    best = max(selected, key=lambda r: sum(r["fresh_goodput"]))
    baseline = next(r for r in selected if r["variant"] == "bpsk_bch")
    severe = max((r for r in data["rows"] if r["bandwidth"] == 24000 and r["preset"] == "disturbed"), key=lambda r: sum(r["fresh_goodput"]))
    runtime = m["runtime"]["avx10"]
    runtime_note = (f"The AVX-512 full selections took {runtime['full_seconds'] / 60:.1f} minutes, exceeding the 30-minute tier allowance. "
                    "All declared durations and cases were retained; the report includes interrupted execution time."
                    if not runtime["within_full_allowance"] else
                    f"The AVX-512 full selections took {runtime['full_seconds'] / 60:.1f} minutes, within the 30-minute tier allowance.")
    fmt = lambda v: "Unobserved" if v is None else f"{v:.3f}"
    timing = "".join(
        f'<tr><th scope="row"><a href="{escape(r["source"])}">{r["bandwidth"]//1000} kHz · {escape(r["label"])}</a></th>'
        f'<td>{r["delivered"]}</td><td>{fmt(r["added"]["p99_9"])}</td><td>{fmt(r["total"]["p99_9"])}</td>'
        f'<td>{fmt(r["reference"]["p50"])} / {fmt(r["reference"]["p99_9"])}</td><td>{r["status"]}</td></tr>'
        for r in data["latency"])
    defects = "".join(f'<li><a href="{escape(d["source"])}">{escape(d["case"])}</a>: {escape(d["reason"])}</li>'
                      for d in {d["case"]: d for d in data["defects"]}.values())
    section = f'''
    <section class="evidence-section polar-section" id="refinement-results"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">BCH combinations · frequency spacing · training intervals</p>
        <h2 class="section-title">Simulated channel.<br>Testing the next three changes.</h2>
        <p class="section-intro">QPSK and 8-PSK with BCH, three frequency separations with matched single-copy controls, and five pilot/retraining schedules. {m['cases']:,} AVX-512 cases cover 23 configurations per bandwidth; 46 serial latency measurements use the longer moderate-channel equalizer on naamah.</p></header>
      <p class="section-intro">At 24 kHz in moderate fading, the highest mean fresh goodput comes from <strong>{escape(best['label'])}</strong>: <strong>{spread(best['fresh_goodput'])} bit/s</strong>. The previous BPSK+BCH configuration delivers <strong>{spread(baseline['fresh_goodput'])} bit/s</strong> in the matched rerun. In disturbed fading, the strongest measured configuration is <strong>{escape(severe['label'])}</strong>, at <strong>{spread(severe['fresh_goodput'])} fresh bit/s</strong>, with maximum delivery gaps of <strong>{spread(severe['silence'],.001,3)} seconds</strong>.</p>
      {context_html(historical=True)}
      <p class="evidence-provenance">Carrier correction is off. All variants retain RLS and clock recovery. Settings travel over fiber/gRPC, and the three seeds are paired across configurations. These simulated channels use the unchanged legacy noise reference and do not predict route availability near 71°N.</p>
      <p class="section-intro"><strong>Calibration finding:</strong> measured waveform power exceeds the harness's nominal noise reference, so configured 30 dB is not actual 30 dB. Diversity also uses about 2.5× full-band BPSK's measured power. Its lower/upper/both controls match, but cross-family results are not equal-power comparisons. This affects the interpretation of earlier campaigns below. <a href="{url(DIRECTORY/'power-audit/SUMMARY.md')}">Power audit: 54 matched-control passes and six retained xfails →</a></p>
      <div class="rf-controls" id="refinement-controls" hidden>
        <label for="refinement-bandwidth">Profile<select id="refinement-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
        <label for="refinement-preset">Delay spread / Doppler spread<select id="refinement-preset"><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
        <label for="refinement-family">Experiment<select id="refinement-family"><option value="coding">BCH combinations</option><option value="diversity">Frequency diversity</option><option value="cadence">Pilot and retraining cadence</option></select></label>
      </div>
      <p class="evidence-provenance" id="refinement-context">24 kHz · moderate · 300 seconds per seed · BCH replaces rate-1/2 payload coding with rate 40/58. Gains include the changed code rate.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel refinement comparison" tabindex="0"><table class="evidence-table" id="refinement-delivery-table">
        <caption>Simulated channel · useful delivery, freshness and airtime</caption><thead><tr><th>Configuration</th><th>Useful bit/s</th><th>Fresh bit/s</th><th>Freshness p99.9 ms</th><th>Longest silence s</th><th>Payload airtime</th><th>Seed records</th></tr></thead><tbody>{''.join(row(r) for r in selected if r['experiment']=='coding')}</tbody></table></div>
      <p class="evidence-provenance">Quiet/moderate/disturbed runs last 300/300/100 seconds per seed: {m['simulated_followup_hours']:.1f} simulated hours. Ranges span seeds and are not confidence intervals. Fresh goodput excludes messages already superseded at their source. Payload airtime is the nominal fraction left after acquisition, training, protected headers, pilots and pulse tails.</p>
      <p class="evidence-provenance">Diversity uses a 0.4B branch width and center spacings B/2, B/2+137 Hz and 0.55B+137 Hz. Lower/upper controls each use full power at the same data rate. Both copies traverse one shared channel; center correlation is recorded, not assumed zero. The occupied span changes within the same allowed bandwidth. Another 216 cases vary path delay around the standard presets.</p>
      <p class="evidence-provenance">Cadence labels p16/p32/p64 specify payload symbols between pilot pairs; r4/r16/r64 specify frames between complete preamble/training/header blocks. Baselines use p32/r16. All equalizer spans cover the same physical path delay.</p>
      <details class="evidence-details"><summary>Simulated channel · software latency: {m['host_latency_statuses'].get('pass',0)}/46 within 2.1 ms</summary>
        <p class="evidence-provenance">Twelve-second null-channel measurements on naamah, with the 3 ms moderate-channel equalizer span. Added p99.9 is measured source-to-sink host time minus a paired one-sample intrinsic reference. Combining wait counts as buffering. Transmission, modem and retraining delays remain in the intrinsic reference. Physical audio devices are outside this test; host timings vary and are excluded from deterministic JSON equality.</p>
        <div class="table-scroll"><table class="evidence-table" id="refinement-latency-table"><caption>Simulated channel · measured milliseconds</caption><thead><tr><th>Configuration</th><th>Delivered</th><th>Added p99.9</th><th>Total p99.9</th><th>Intrinsic p50 / p99.9</th><th>Result</th></tr></thead><tbody>{timing}</tbody></table></div>
      </details>
      <details class="evidence-details"><summary>Simulated channel · calibration defects</summary><ul>{defects or '<li>No new expected failures in this campaign.</li>'}</ul></details>
      <p class="evidence-provenance">20/20 CTest regressions pass on each host; 14 harness checks, three identical seeded repeats, and {m['unchanged_baseline_comparisons']} unchanged baseline comparisons are verified. The full report preserves the 192-point AWGN sweep, delay sensitivity records, open thresholds, runtime limits and earlier crypto findings. The <a href="{url(DIRECTORY.parent/'encoding-improvements/PATENT_SCREEN.md')}">US and international-family engineering patent screen</a> applies to the conventional components; it does not provide worldwide legal clearance.</p>
      <p class="evidence-provenance">{runtime_note}</p>
      <div class="evidence-links"><a href="{url(DIRECTORY/'REPORT.md')}">All three experiments and results →</a><a href="{url(DIRECTORY/'SUMMARY.md')}">Parameter records →</a><a href="{url(DIRECTORY/'VALIDATION.json')}">Validation manifest →</a></div>
      <p class="evidence-provenance">Base revision <code>{m['git_commit'][:12]}</code>; tested source SHA-256 <code class="source-hash">{m['source_tree_sha256']}</code>. <a href="{url(DIRECTORY/'source-snapshot.tar.gz')}">Tested source snapshot</a>. Previous campaigns follow below.</p>
    </div></section>
'''
    return section, "\nglobalThis.GoblinRefinementResults = " + json.dumps(data, separators=(",", ":"), allow_nan=False) + ";\n"
