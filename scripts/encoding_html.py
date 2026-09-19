from channel_description import context_html
"""Render the completed conventional-encoding simulated channel measurements."""
import json
from html import escape
from encoding_results import DIRECTORY, LABELS, SEEDS, load, read, spread, url
from psk_html import links, noise_row


def comparison_row(r):
    return (f'<tr><th scope="row">{escape(r["label"])}</th>'
            f'<td>{spread(r["goodput"])}</td><td>{spread(r["fresh_goodput"])}</td>'
            f'<td>{spread(r["delivery"],100)}%</td><td>{spread(r["freshness"])}</td>'
            f'<td>{spread(r["silence"],.001,3)}</td><td>{links(r["sources"])}</td></tr>')


def build():
    data = load()
    m = data["manifest"]
    if read(DIRECTORY / "VALIDATION.json") != m:
        raise ValueError("Encoding validation manifest is stale; regenerate the report")
    rows = [r for r in data["rows"] if r["bandwidth"] == 24000 and r["preset"] == "moderate"]
    best = max(rows, key=lambda r: sum(r["goodput"]))
    baseline = next(r for r in rows if r["variant"] == "bpsk_reference")
    severe = max((r for r in data["rows"] if r["bandwidth"] == 24000 and r["preset"] == "disturbed"),
                 key=lambda r: sum(r["goodput"]))
    noise = [r for r in data["noise"] if r["bandwidth"] == 24000 and r["variant"] == "qpsk_reference"]
    papr = next(r for r in data["papr"] if r["bandwidth"] == 24000 and r["variant"] == "qpsk_reference")
    fmt = lambda v: "Unobserved" if v is None else f"{v:.3f}"
    timing = "".join(
        f'<tr><th scope="row"><a href="{escape(r["source"])}">{r["bandwidth"]//1000} kHz · {escape(r["label"])}</a></th>'
        f'<td>{r["delivered"]}</td><td>{fmt(r["added"]["p99_9"])}</td><td>{fmt(r["total"]["p99_9"])}</td>'
        f'<td>{fmt(r["reference"]["p50"])} / {fmt(r["reference"]["p99_9"])}</td><td>{escape(r["status"])}</td></tr>'
        for r in data["latency"])
    failures = "".join(
        f'<li><a href="{escape(d["source"])}">{escape(d["case"])}</a>: {escape(d["reason"])}</li>'
        for d in {d["case"]: d for d in data["defects"]}.values())
    host_passes = m["host_latency_statuses"].get("pass", 0)
    section = f'''
    <section class="evidence-section polar-section" id="encoding-results"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Conventional encoding · fixed total transmit power</p>
        <h2 class="section-title">Simulated channel.<br>More ways through fading.</h2>
        <p class="section-intro">Soft bit metrics, stronger convolutional codes, Walsh spreading, BCH, interleaving, noncoherent FSK and BPSK frequency diversity face the same polar traces. The comparison covers 21 configurations, {m['main_cases']:,} AVX-512 cases and 42 quiet-host latency measurements.</p></header>
      <p class="section-intro">At 24 kHz in moderate fading, <strong>{escape(best['label'])}</strong> delivers the highest mean correct goodput: <strong>{spread(best['goodput'])} bit/s</strong>, versus <strong>{spread(baseline['goodput'])} bit/s</strong> for the BPSK reference. In disturbed fading, <strong>{escape(severe['label'])}</strong> leads at <strong>{spread(severe['goodput'])} bit/s</strong>, with longest delivery gaps of <strong>{spread(severe['silence'],.001,3)} seconds</strong>. Freshness and buffering costs remain visible below.</p>
      {context_html(historical=True)}
      <p class="evidence-provenance">Carrier correction is off. Coherent modes retain RLS equalization and clock recovery; FSK uses tone-energy detection and per-frame acquisition. Diversity divides the existing total power between two subbands. Three-seed ranges are observations, not confidence intervals or route-availability forecasts.</p>
      <p class="evidence-provenance">The <a href="{url(DIRECTORY/'PATENT_SCREEN.md')}">public-record patent screen</a> documents the historical implementations and excludes modern CROW, specialized LDPC and unresolved adaptive designs. It is not worldwide patent clearance. Both endpoints receive settings over fiber/gRPC.</p>
      <div class="rf-controls" id="encoding-controls" hidden>
        <label for="encoding-bandwidth">Profile<select id="encoding-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
        <label for="encoding-preset">Delay spread / Doppler spread<select id="encoding-preset"><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
        <label for="encoding-mode">Noise-curve configuration<select id="encoding-mode">{''.join(f'<option value="{v}">{escape(label)}</option>' for v,label in LABELS.items())}</select></label>
      </div>
      <p class="evidence-provenance" id="encoding-context">24 kHz · moderate · 300 seconds per seed · 30 dB nominal sample SNR.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel encoding delivery comparison" tabindex="0"><table class="evidence-table" id="encoding-delivery-table">
        <caption>Simulated channel · correct and fresh useful message delivery</caption><thead><tr><th>Configuration</th><th>Correct bit/s</th><th>Fresh bit/s</th><th>Delivered / framed</th><th>Freshness p99.9 ms</th><th>Longest silence s</th><th>Seed records</th></tr></thead><tbody>{''.join(comparison_row(r) for r in rows)}</tbody></table></div>
      <p class="evidence-provenance">Fresh goodput excludes a delivered value when its key already has a newer source-created value. It is a simulator observation; the receiver receives no source oracle. All modes use 300/300/100 seconds per quiet/moderate/disturbed seed: {m['simulated_followup_hours']:.1f} simulated hours. The half-band BPSK control separates slower symbol timing from diversity. Longest silence includes startup and the trace tail.</p>
      <p class="evidence-provenance">Diversity limitation: the 5/12 kHz subband spacing and these fixed 1/3/7 ms delays give matching two-path responses at the subband centers. Both copies pass through the same simulated channel. This run does not establish the gain available with decorrelated frequency paths.</p>
      <details class="evidence-details"><summary>Simulated channel · 672 noise points and measured waveform peaks</summary>
        <p class="evidence-provenance">AWGN 0–30 dB in 2 dB steps; 10 seconds per coherent point and 30 per FSK point. Every mode uses the same nominal full-band sample power. This SNR is not Eb/N0 or the standard’s 3 kHz SNR. BER is conditional on observed bits, and short zero-error runs do not establish a BER 1e-5 operating limit.</p>
        <p class="evidence-provenance" id="encoding-papr">QPSK reference · 24 kHz measured PAPR: {spread(papr['db'])} dB.</p>
        <div class="table-scroll"><table class="evidence-table" id="encoding-noise-table"><caption>Simulated channel · AWGN · seed {SEEDS[0]}</caption><thead><tr><th>SNR dB</th><th>Raw BER</th><th>Post-FEC BER</th><th>Bits observed</th><th>RF frames survived</th><th>Record</th></tr></thead><tbody>{''.join(noise_row(r) for r in noise)}</tbody></table></div>
      </details>
      <details class="evidence-details"><summary>Simulated channel · added latency: {host_passes}/42 configurations within 2.1 ms</summary>
        <p class="evidence-provenance">Serial measurements on naamah. The paired intrinsic reference retains transmission, modem/FEC and startup but removes interleaver and diversity wait; those waits count against the added-buffering allowance. Total and intrinsic latency are separate. FSK runs last 30 seconds; others 12. No physical audio device is included. Host timing varies and is excluded from seeded byte-equality checks. Small sample counts limit p99.9 interpretation.</p>
        <div class="table-scroll"><table class="evidence-table" id="encoding-latency-table"><caption>Simulated channel · measured milliseconds</caption><thead><tr><th>Configuration</th><th>Delivered</th><th>Added p99.9</th><th>Total p99.9</th><th>Intrinsic p50 / p99.9</th><th>Result</th></tr></thead><tbody>{timing}</tbody></table></div>
        <p class="evidence-provenance">Expected failures preserve the measured delay and the original allowance; none is counted as a pass. Stage measurements are linked in each record.</p>
        <ul class="encoding-defects">{failures or '<li>No expected failures in this selection.</li>'}</ul>
      </details>
      <p class="evidence-provenance">20/20 CTest regressions pass on avx10 and naamah; 13 Python harness checks and three byte-identical seeded repeats pass. These custom waveforms are not MIL-STD-188-110C qualification. Existing AEAD/replay findings, open thresholds and unavailable recorded noise beds remain. FSK’s long serialization also needs an appropriate control-plane timestamp window.</p>
      <div class="evidence-links"><a href="{url(DIRECTORY/'REPORT.md')}">Encoding findings and full tables →</a><a href="{url(DIRECTORY/'SUMMARY.md')}">All parameter records →</a><a href="{url(DIRECTORY/'VALIDATION.json')}">Validation manifest →</a></div>
      <p class="evidence-provenance">Base revision <code>{m['git_commit'][:12]}</code>; tested source SHA-256 <code class="source-hash">{m['source_tree_sha256']}</code>. <a href="{url(DIRECTORY/'source-snapshot.tar.gz')}">Exact tested source snapshot</a>. Earlier campaigns remain separate below.</p>
    </div></section>
'''
    return section, "\nglobalThis.GoblinEncodingResults = " + json.dumps(data, separators=(",", ":"), allow_nan=False) + ";\n"
