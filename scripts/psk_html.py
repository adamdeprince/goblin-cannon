"""Render the PSK simulated channel comparison from completed measurements."""
import json
from html import escape
from psk_results import DIRECTORY, LABELS, SEEDS, load, read, spread, url


def links(sources):
    return " / ".join(f'<a href="{escape(u)}">{s}</a>' for s,u in zip(SEEDS,sources))


def comparison_row(r):
    return (f'<tr><th scope="row">{escape(r["label"])}</th><td>{spread(r["goodput"])}</td>'
            f'<td>{spread(r["delivery"],100)}%</td><td>{spread(r["freshness"])}</td>'
            f'<td>{spread(r["silence"],.001,3)}</td><td>{links(r["sources"])}</td></tr>')


def noise_row(r):
    def value(v):return "Unobserved" if v is None else f"{v:.5g}"
    return (f'<tr><th scope="row">{r["snr"]}</th><td>{value(r["ber"])}</td>'
            f'<td>{value(r["coded_ber"])}</td><td>{value(None if r["observed"] is None else 100*r["observed"]) }%</td>'
            f'<td>{value(100*r["frame_survival"]) }%</td><td><a href="{escape(r["source"])}">JSON</a></td></tr>')


def build():
    data=load()
    m=data["manifest"]
    if read(DIRECTORY/"VALIDATION.json")!=m:
        raise ValueError("PSK validation manifest is stale; regenerate the report")
    rows=[r for r in data["rows"] if r["bandwidth"]==24000 and r["preset"]=="moderate"]
    bpsk=next(r for r in rows if r["variant"]=="bpsk_qpsk_header")
    qpsk=next(r for r in rows if r["variant"]=="qpsk_reference")
    noise=[r for r in data["noise"] if r["bandwidth"]==24000 and r["variant"]=="qpsk_reference"]
    headers="".join(f'<tr><th scope="row">{r["bandwidth"]//1000} kHz · {r["preset"]}</th>'
        f'<td>{spread(r["goodput"][:3])}</td><td>{spread(r["goodput"][3:])}</td>'
        f'<td>{spread(r["valid_headers"][:3],precision=0)} / {spread(r["valid_headers"][3:],precision=0)}</td>'
        f'<td>{links(r["sources"][:3])}<br>{links(r["sources"][3:])}</td></tr>' for r in data["headers"])
    timing="".join(f'<tr><th scope="row"><a href="{escape(r["source"])}">{r["bandwidth"]//1000} kHz · {escape(r["label"])} · {r["span"]}</a></th>'
        f'<td>{r["added"]["p99_9"]:.3f}</td><td>{r["total"]["p99_9"]:.3f}</td>'
        f'<td>{r["reference"]["p50"]:.3f} / {r["reference"]["p99_9"]:.3f}</td><td>{escape(r["status"])}</td></tr>' for r in data["latency"])
    section=f'''
    <section class="evidence-section polar-section" id="psk-results"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Earlier PSK comparison · three matched seeds</p>
        <h2 class="section-title">Simulated channel.<br>BPSK helps through moderate fading.</h2>
        <p class="section-intro">BPSK, 8-PSK, DBPSK, DQPSK and π/4-DQPSK face the same polar traces, with QPSK, 16-QAM and 64-QAM as controls. Header-only experiments separate the cost of a BPSK header from changing the payload. {m['main_cases']} AVX-512 cases and 44 quiet-host latency cases are complete.</p></header>
      <p class="evidence-provenance">Carrier correction stays off; adaptive RLS equalization and sample-clock recovery stay on. Both ends receive settings over fiber. Differential detection adds no frequency tracker or CMA. Ranges below span three seeds, not confidence intervals. The browser selects saved results.</p>
      <p class="section-intro">At 24 kHz under moderate fading, BPSK payload with the existing QPSK header delivers <strong>{spread(bpsk['goodput'])} bit/s</strong>, versus <strong>{spread(qpsk['goodput'])} bit/s</strong> for QPSK. All three seeds improve. BPSK header data and differential payload mappings reduce moderate-channel goodput in these tests.</p>
      <div class="rf-controls" id="psk-controls" hidden>
        <label for="psk-bandwidth">Profile<select id="psk-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
        <label for="psk-preset">Polar preset<select id="psk-preset"><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
        <label for="psk-mode">Noise-curve configuration<select id="psk-mode">{''.join(f'<option value="{v}">{escape(label)}</option>' for v,label in LABELS.items())}</select></label>
      </div>
      <p class="evidence-provenance" id="psk-context">24 kHz · moderate · 300 seconds per seed · 30 dB nominal SNR.</p>
      <div class="table-scroll" role="region" aria-label="Simulated channel PSK delivery comparison" tabindex="0"><table class="evidence-table" id="psk-delivery-table">
        <caption>Simulated channel · useful message delivery after FEC</caption><thead><tr><th>Payload / header</th><th>Useful bit/s</th><th>Delivered / framed</th><th>Freshness p99.9 ms</th><th>Longest silence s</th><th>Seed records</th></tr></thead><tbody>{''.join(comparison_row(r) for r in rows)}</tbody></table></div>
      <p class="evidence-provenance">Quiet/moderate/disturbed follow-ups last 300/300/100 seconds per seed. The earlier 6,000-second quiet runs remain separate below. No statistical operating limit is claimed. Message survival excludes updates rejected by the source auction; silence includes startup and the end of the trace. The 71.53°N geometry is unchanged; these fixed-SNR simulations do not forecast route availability.</p>
      <h3>Simulated channel · the header-only experiment</h3>
      <p class="evidence-provenance">BPSK header data uses 332 air symbols versus 166 for QPSK. Acquisition, equalizer training and embedded probes stay QPSK. The current receiver already validates headers on moderate fading. These ten-second paired screens include the extra airtime; header counts are not conditional success probabilities.</p>
      <div class="table-scroll"><table class="evidence-table" id="psk-header-table"><caption>Simulated channel · QPSK payload held fixed</caption><thead><tr><th>Profile / preset</th><th>QPSK-header bit/s</th><th>BPSK-header bit/s</th><th>Valid headers QPSK / BPSK</th><th>Seed records QPSK / BPSK</th></tr></thead><tbody>{headers}</tbody></table></div>
      <details class="evidence-details"><summary>Simulated channel · all 16 noise points and measured waveform peaks</summary>
        <p class="evidence-provenance">Ten seconds per AWGN point at equal nominal symbol energy. The selected noise curve has no multipath; its SNR is not Eb/N0. Conditional BER excludes lost bits, whose observation fraction is separate. PAPR covers the finite clean pulse-shaped stream, including controls and tails. No PA backoff or transmit-power gain is assumed.</p>
        <p class="evidence-provenance" id="psk-papr">QPSK · QPSK header · 24 kHz measured PAPR: {spread(next(r['db'] for r in data['papr'] if r['bandwidth']==24000 and r['variant']=='qpsk_reference'))} dB.</p>
        <div class="table-scroll"><table class="evidence-table" id="psk-noise-table"><caption>Simulated channel · AWGN · seed {SEEDS[0]}</caption><thead><tr><th>SNR dB</th><th>Raw BER</th><th>Post-Viterbi BER</th><th>Bits observed</th><th>RF frames survived</th><th>Record</th></tr></thead><tbody>{''.join(noise_row(r) for r in noise)}</tbody></table></div>
      </details>
      <details class="evidence-details"><summary>Simulated channel · 44 quiet-host latency measurements</summary>
        <p class="evidence-provenance">naamah, AVX2, one worker. The 2.1 ms allowance applies to added processing/buffering. Intrinsic reference, transmission/modem/startup and total latency remain separate. Host timing is excluded from deterministic JSON comparisons. Stage timings are in each linked host record. Serial short-span B5 took longer than its 120-second quick-tier allowance; all twelve-second durations were retained.</p>
        <div class="table-scroll"><table class="evidence-table" id="psk-latency-table"><caption>Simulated channel · measured milliseconds</caption><thead><tr><th>Configuration</th><th>Added p99.9</th><th>Total p99.9</th><th>Intrinsic reference p50 / p99.9</th><th>Result</th></tr></thead><tbody>{timing}</tbody></table></div>
      </details>
      <div class="evidence-links"><a href="{url(DIRECTORY/'REPORT.md')}">All PSK findings and seed tables →</a><a href="{url(DIRECTORY/'SUMMARY.md')}">Full parameter records →</a><a href="{url(DIRECTORY/'VALIDATION.json')}">Validation manifest →</a></div>
      <p class="evidence-provenance">Base revision <code>{m['git_commit'][:12]}</code>; tested source SHA-256 <code class="source-hash">{m['source_tree_sha256']}</code>. <a href="{url(DIRECTORY/'source-snapshot.tar.gz')}">Tested source snapshot</a>. Existing defects and open thresholds remain in the earlier test ledger.</p>
    </div></section>
'''
    return section,"\nglobalThis.GoblinPskResults = "+json.dumps(data,separators=(",",":"),allow_nan=False)+";\n"
