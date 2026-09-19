from channel_description import context_html
"""Render only the current simulated channel dataset, including AEAD failures."""
import json
from html import escape
from aead_results import DIRECTORY, read, span, url


def number(value):
    return "Unobserved" if value is None else f"{value:.3f}"


def build(start, end):
    data=read(DIRECTORY / "DATA.json");m=data["manifest"]
    default=next(r for r in data["rows"] if r["bandwidth"]==24000 and r["variant"]=="bpsk_bch" and r["preset"]=="moderate")
    table_rows="".join(f'<tr><th scope="row">{escape(r["label"])}</th><td>{span(r["goodput"])}</td><td>{span(r["fresh_goodput"])}</td><td>{span(r["delivery"],100)}</td><td>{span(r["freshness"])}</td><td>{span(r["silence"],.001,3)}</td><td>'+" · ".join(f'<a href="{escape(source)}">{seed}</a>' for seed,source in zip(m["seeds"],r["sources"]))+'</td></tr>'
                       for r in data["rows"] if r["bandwidth"]==24000 and r["preset"]=="moderate")
    latencies=[r for r in data["latency"] if r["profile"]=="naamah-latency"]
    worst=max(r["added"]["p99_9"] for r in latencies)
    timing="".join(f'<tr><th scope="row"><a href="{r["source"]}">{r["bandwidth"]//1000} kHz · {r["modulation"].upper()} · {r["span"]}</a></th><td>{number(r["added"]["p99_9"])}</td><td>{number(r["total"]["p99_9"])}</td><td>{number(r["reference"]["p50"])} / {number(r["reference"]["p99_9"])}</td><td>{r["status"]}</td></tr>' for r in latencies)
    defects="".join(f'<tr><th scope="row"><a href="{d["source"]}">{escape(d["case"])}</a></th><td>{escape(d["assertion"])}</td><td>{escape(d["reason"])}</td></tr>' for d in data["defects"])
    a8="".join(f'<tr><th scope="row"><a href="{r["source"]}">{r["sir"]:+g} dB</a></th><td>{r["delivered"]}</td><td>{r["authentication_failures"]}</td><td>{r["fec_gaps"]}</td><td>{r["corrupt"]}</td><td>{r["status"]}</td></tr>' for r in sorted(data["a8"],key=lambda r:r["sir"]))
    negative=next(r for r in data["a8"] if r["sir"]==-10)
    ledger="".join(f'<tr><th scope="row">{escape(group)}</th><td>'+escape(", ".join(f"{key}: {value}" for key,value in sorted(counts.items())))+'</td></tr>' for group,counts in sorted(m["groups"].items()))
    sections=f'''{start}
    <section class="evidence-section polar-section" id="rf-simulation"><div class="section-inner">
      <span id="refinement-results"></span>
      <header class="evidence-head"><p class="section-label">Current waveform and authenticated delivery</p><h2 class="section-title">Simulated channel.<br>The 71°N problem.</h2>
        <p class="section-intro">BPSK, QPSK and 8-PSK, each with convolutional or BCH payload coding. All message measurements use the current AES-256-GCM path. Three seeds cover each bandwidth and high-latitude preset; quiet and moderate traces last 300 seconds, disturbed traces 100 seconds.</p></header>
      {context_html(historical=True)}
      <p class="evidence-provenance">Carrier correction is off; RLS equalization and audio-clock recovery are on. Parameters travel over fiber. These finite simulated channels do not establish availability for the route that reaches 71.534°N.</p>
      <div class="rf-explorer" id="rf-explorer">
        <div class="rf-controls" id="rf-controls" hidden>
          <label for="rf-bandwidth">Profile<select id="rf-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
          <label for="rf-modulation">Modulation<select id="rf-modulation"><option value="bpsk">BPSK</option><option value="qpsk">QPSK / 4-QAM</option><option value="8psk">8-PSK</option></select></label>
          <label for="rf-coding">Payload FEC<select id="rf-coding"><option value="bch">BCH · 40/58</option><option value="soft">Convolutional · 1/2</option></select></label>
          <label for="rf-preset">Delay spread / Doppler spread<select id="rf-preset"><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
          <label for="rf-layer">Measurement<select id="rf-layer"><option value="messages">Authenticated messages after FEC</option><option value="rf">Raw RF decisions · before message FEC</option></select></label>
        </div>
        <div class="rf-outcome" data-reception="limited"><p class="section-label">Simulated channel · current receiver</p><h3 id="rf-outcome-title">Useful messages delivered after FEC.</h3><p id="rf-outcome-note">24 kHz · BPSK · BCH · high-latitude moderate. Only complete, authenticated records reach the message sink.</p></div>
        <div class="rf-metrics" aria-live="polite">
          <div><span id="rf-metric-label-0">Delivered / framed messages</span><strong id="rf-metric-0">{span(default['delivery'],100)}%</strong><small>Range across three seeds</small></div>
          <div><span id="rf-metric-label-1">Useful goodput</span><strong id="rf-metric-1">{span(default['goodput'])}</strong><small id="rf-unit-1">Useful bits per second</small></div>
          <div><span id="rf-metric-label-2">Delivered freshness p99.9</span><strong id="rf-metric-2">{span(default['freshness'])}</strong><small id="rf-unit-2">Milliseconds from source creation</small></div>
          <div><span id="rf-metric-label-3">Longest delivery silence</span><strong id="rf-metric-3">{span(default['silence'],.001,3)}</strong><small id="rf-unit-3">Seconds, including terminal silence</small></div>
        </div>
        <div class="rf-comparison" id="rf-comparison" hidden></div>
        <p class="rf-parameters" id="rf-parameters">Configured SNR 30 dB; equal-gain two-path Watterson channel. Ranges are seed ranges, not confidence intervals.</p>
        <div class="evidence-links rf-source-links" id="rf-sources">{' · '.join(f'<a href="{s}">Seed {seed} parameters + metrics</a>' for seed,s in zip(m['seeds'],default['sources']))}</div>
      </div>
      <p class="evidence-provenance"><strong>Calibration remains open:</strong> measured waveform power exceeds the nominal noise reference. Configured 30 dB is not calibrated actual 30 dB; the RF view reports measured sample power. The 24 kHz model also extends beyond the Recommendation’s validated bandwidth scope. No live recordings or soak results are available.</p>
      <div class="table-scroll"><table class="evidence-table" id="current-delivery-table"><caption id="current-table-caption">Simulated channel · 24 kHz moderate · current useful delivery</caption><thead><tr><th>Configuration</th><th>Useful bit/s</th><th>Fresh bit/s</th><th>Delivered / framed %</th><th>Freshness p99.9 ms</th><th>Longest silence s</th><th>Seed records</th></tr></thead><tbody>{table_rows}</tbody></table></div>
      <p class="evidence-provenance">Fresh goodput counts messages still current at their source key when delivered. Missing decisions do not count as zero BER. The RF view uses separate ten-second screens and reports the observed-bit fraction. Frequency-diversity and alternate training cadences are implemented; this current-format polar selection covers the six configurations shown above.</p>
    </div></section>
    <section class="evidence-section" id="benchmarks"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Measured on naamah · current recovery profile</p><h2 class="section-title">Simulated channel.<br>Software within budget.</h2><p class="section-intro">All 12 configurations pass the 2.1 ms added-processing and buffering allowance. Transmission time, modem/FEC residence and acquisition remain separately visible.</p></header>
      <div class="evidence-stats"><div><strong>{worst:.3f}<small> ms</small></strong><span>Worst added p99.9</span></div><div><strong>12/12</strong><span>Current recovery-profile configurations pass</span></div><div><strong>2.1<small> ms</small></strong><span>Unchanged processing and buffering limit</span></div></div>
      <div class="table-scroll"><table class="evidence-table" id="current-latency-table"><caption>Simulated channel · current host measurements in milliseconds</caption><thead><tr><th>Configuration / equalizer span</th><th>Added p99.9</th><th>Total p99.9</th><th>Intrinsic p50 / p99.9</th><th>Result</th></tr></thead><tbody>{timing}</tbody></table></div>
      <p class="evidence-provenance">Serial twelve-second paced loopbacks include source creation, the auction, framing, authentication, FEC, modem processing and 1 ms audio blocks. Added latency is each delivered message’s host time above its matched one-sample intrinsic reference. No physical audio device or network socket is measured. Host timings vary and are stored separately from deterministic simulated-time JSON.</p>
      <p class="evidence-provenance">The requested twelve-case profile also passes. The <a href="{url(DIRECTORY/'SUMMARY.md')}">report contains the requested before/after table</a>, stage breakdowns, and the crypto profile. OpenSSL contexts and keys are initialized outside the per-frame path.</p>
    </div></section>
    <section class="evidence-section" id="test-results"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Authenticated records · explicit remaining defects</p><h2 class="section-title">Simulated channel.<br>Injection is rejected.</h2><p class="section-intro">The −10 dB co-channel trace now records {negative['authentication_failures']} authentication failures and zero foreign or corrupt sink deliveries. Authentication failures remain separate from RF lock loss.</p></header>
      <div class="table-scroll"><table class="evidence-table" id="current-auth-table"><caption>Simulated channel · same-waveform interferer with an independent key</caption><thead><tr><th>SIR</th><th>Useful deliveries</th><th>Authentication failures</th><th>FEC gaps</th><th>Foreign/corrupt delivered</th><th>Result</th></tr></thead><tbody>{a8}</tbody></table></div>
      <p class="evidence-provenance">A zero authentication count means no invalid complete record reached that check. D6 separately rejects {data['crypto']['tamper_attempts']} deliberately tampered records and {data['crypto']['replay_rejections']} replays. Two sender processes produced {data['crypto']['nonces_observed']} distinct wire nonces under one key. Durable epoch reservation completes before transmission; no wall-clock nonce is used.</p>
      <p class="section-intro"><strong>{m['remaining_assertions']} failing assertions across {m['remaining_cases']} cases remain</strong> in the current recovery-profile audit. Six authentication assertions are fixed. Coordinated key rotation remains open: key IDs are authenticated, but overlapping keys and mid-stream old-key retirement are not implemented.</p>
      <details class="evidence-details"><summary>Simulated channel · remaining defects</summary><div class="table-scroll"><table class="evidence-table defect-table" id="current-defect-table"><thead><tr><th>Case</th><th>Assertion</th><th>Finding</th></tr></thead><tbody>{defects}</tbody></table></div></details>
      <details class="evidence-details"><summary>Simulated channel · validation coverage and source</summary><p>{m['recorded_runs']} recorded runs cover {m['unique_case_seed_profiles']} unique case/seed/profile combinations. Both hosts pass 21/21 CTest tests; 14 harness checks and 19 CLI/protobuf checks pass. {m['byte_identical_repeats']} repeated authenticated-message runs have byte-identical canonical JSON. This is a selected campaign; no full-matrix or soak completion is claimed.</p><div class="table-scroll"><table class="evidence-table"><caption>Simulated channel · security and regression selection</caption><thead><tr><th>Group</th><th>Current results</th></tr></thead><tbody>{ledger}</tbody></table></div><p>All unapproved acceptance margins remain THRESHOLD_TBD. Calibration and route availability remain open. The report explains the older brief’s 13/11 count and the current recovery-profile scope.</p><p>Tested source SHA-256 <code class="source-hash">{m['source_tree_sha256']}</code>.</p></details>
      <div class="evidence-links"><a href="{url(DIRECTORY/'SUMMARY.md')}">Current simulated channel report →</a><a href="{url(DIRECTORY/'VALIDATION.json')}">Validation manifest →</a><a href="{url(DIRECTORY/'source-snapshot.tar.gz')}">Tested source snapshot →</a></div>
    </div></section>
{end}'''
    js="// Current simulated channel evidence; generated from results/aead only.\n"
    js+="globalThis.GoblinChannelResults = "+json.dumps(data,ensure_ascii=True,allow_nan=False,separators=(",",":"))+";\n"
    return sections,js
