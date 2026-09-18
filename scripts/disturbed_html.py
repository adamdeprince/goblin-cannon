"""Render current calibrated simulated channel recovery measurements."""
import json
from html import escape
from disturbed_results import DIRECTORY, read, span, url


def number(value):
    return "Unobserved" if value is None else f"{value:.3f}"


def build(start, end):
    data=read(DIRECTORY / "DATA.json");m=data["manifest"]
    default=next(r for r in data["rows"] if r["bandwidth"]==24000 and r["variant"]=="qpsk_bch" and r["preset"]=="disturbed")
    table_rows="".join(f'<tr><th scope="row">{escape(r["label"])}</th><td>{span(r["goodput"])}</td><td>{span(r["fresh_goodput"])}</td><td>{span(r["delivery"],100)}</td><td>{span(r["freshness"])}</td><td>{span(r["silence"],.001,3)}</td><td>'+" · ".join(f'<a href="{escape(source)}">{seed}</a>' for seed,source in zip(m["seeds"],r["sources"]))+'</td></tr>'
                       for r in data["rows"] if r["bandwidth"]==24000 and r["preset"]=="disturbed")
    latencies=[r for r in data["latency"] if r["profile"]=="naamah-latency"]
    worst=max(r["added"]["p99_9"] for r in latencies)
    passing=sum(r["status"]=="pass" for r in latencies)
    rx_burst=max(r["rx"]["max"] for r in latencies)
    timing="".join(f'<tr><th scope="row"><a href="{r["source"]}">{escape(r["case"].removeprefix("B5_").replace("_"," "))}</a></th><td>{number(r["added"]["p99_9"])}</td><td>{number(r["total"]["p99_9"])}</td><td>{number(r["reference"]["p50"])} / {number(r["reference"]["p99_9"])}</td><td>{r["status"]}</td></tr>' for r in latencies)
    defects="".join(f'<tr><th scope="row"><a href="{d["source"]}">{escape(d["case"])}</a></th><td>{escape(d["assertion"])}</td><td>{escape(d["reason"])}</td></tr>' for d in data["defects"])
    a8="".join(f'<tr><th scope="row"><a href="{r["source"]}">{r["sir"]:+g} dB</a></th><td>{r["delivered"]}</td><td>{r["authentication_failures"]}</td><td>{r["fec_gaps"]}</td><td>{r["corrupt"]}</td><td>{r["status"]}</td></tr>' for r in sorted(data["a8"],key=lambda r:r["sir"]))
    negative=next(r for r in data["a8"] if r["sir"]==-10)
    severe=next(r for r in data['comparisons'] if r['bandwidth']==24000 and r['variant']=='qpsk_bch' and r['preset']=='disturbed')
    quiet_trade=next(r for r in data['comparisons'] if r['bandwidth']==24000 and r['variant']=='8psk_bch' and r['preset']=='quiet')
    ledger="".join(f'<tr><th scope="row">{escape(group)}</th><td>'+escape(", ".join(f"{key}: {value}" for key,value in sorted(counts.items())))+'</td></tr>' for group,counts in sorted(m["groups"].items()))
    diversity="".join(f'<tr><th scope="row">{r["bandwidth"]//1000} kHz · {r["spacing"]} · {r["preset"]}</th><td>{span(r["branches"]["lower"]["fresh_goodput"])}</td><td>{span(r["branches"]["upper"]["fresh_goodput"])}</td><td><a href="{r["branches"]["both"]["sources"][0]}">{span(r["branches"]["both"]["fresh_goodput"])}</a></td></tr>' for r in data["diversity"])
    sections=f'''{start}
    <section class="evidence-section polar-section" id="rf-simulation"><div class="section-inner">
      <span id="refinement-results"></span>
      <header class="evidence-head"><p class="section-label">Current waveform and authenticated delivery</p><h2 class="section-title">Simulated channel.<br>The 71°N problem.</h2>
        <p class="section-intro">BPSK, QPSK and 8-PSK with convolutional or BCH coding, measured with faster recovery, equalizer uncertainty prediction and a compact authenticated header. Three seeds cover each bandwidth and high-latitude preset; quiet and moderate traces last 300 seconds, disturbed traces 100 seconds.</p></header>
      <p class="evidence-provenance">The transmit-power and noise reference are now calibrated. Carrier correction is off; RLS equalization and audio-clock recovery are on. The header is 13 bytes and retains the full 16-byte GCM tag. Parameters and nonce epochs travel over fiber. These finite simulated channels do not establish availability for the route that reaches 71.534°N.</p>
      <div class="rf-explorer" id="rf-explorer">
        <div class="rf-controls" id="rf-controls" hidden>
          <label for="rf-bandwidth">Profile<select id="rf-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
          <label for="rf-modulation">Modulation<select id="rf-modulation"><option value="bpsk">BPSK</option><option value="qpsk" selected>QPSK / 4-QAM</option><option value="8psk">8-PSK</option></select></label>
          <label for="rf-coding">Payload FEC<select id="rf-coding"><option value="bch">BCH · 40/58</option><option value="soft">Convolutional · 1/2</option></select></label>
          <label for="rf-preset">Polar preset<select id="rf-preset"><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="disturbed" selected>Disturbed · 7 ms / 30 Hz</option></select></label>
          <label for="rf-layer">Measurement<select id="rf-layer"><option value="messages">Authenticated messages after FEC</option><option value="rf">Raw RF decisions · before message FEC</option></select></label>
        </div>
        <div class="rf-outcome" data-reception="limited"><p class="section-label">Simulated channel · current receiver</p><h3 id="rf-outcome-title">Useful messages delivered after FEC.</h3><p id="rf-outcome-note">24 kHz · QPSK · BCH · high-latitude disturbed. Only complete, authenticated records reach the message sink.</p></div>
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
      <p class="evidence-provenance">The RF view reports measured sample power; the <a href="{url(DIRECTORY/'POWER.json')}">power audit</a> checks the corrected noise reference and matched diversity controls using the existing 2% finite-waveform tolerance. The 24 kHz model extends beyond the Recommendation’s validated bandwidth scope. No live recordings or soak results are available.</p>
      <div class="table-scroll"><table class="evidence-table" id="current-delivery-table"><caption id="current-table-caption">Simulated channel · 24 kHz disturbed · current useful delivery</caption><thead><tr><th>Configuration</th><th>Useful bit/s</th><th>Fresh bit/s</th><th>Delivered / framed %</th><th>Freshness p99.9 ms</th><th>Longest silence s</th><th>Seed records</th></tr></thead><tbody>{table_rows}</tbody></table></div>
      <p class="evidence-provenance">Fresh goodput counts messages still current at their source key when delivered. Missing decisions do not count as zero BER. The RF view uses separate ten-second screens and reports the observed-bit fraction. The <a href="{url(DIRECTORY/'SUMMARY.md')}">paired experiment report</a> isolates recovery, uncertainty prediction and header size against a freshly calibrated baseline.</p>
      <p class="evidence-provenance">On the disturbed 24 kHz trace, QPSK+BCH improves from {span(severe['baseline'])} to {span(severe['combined'])} fresh bit/s. These settings remain selectable: quiet 24 kHz 8-PSK+BCH falls from {span(quiet_trade['baseline'])} to {span(quiet_trade['combined'])} fresh bit/s, and disturbed 10 kHz delivery remains essentially absent.</p>
      <details class="evidence-details"><summary>Simulated channel · frequency diversity at matched transmit power</summary><p>BPSK+BCH, compact authenticated records. Lower and upper controls each use full power; both copies share that same total power. Three spacings and off-preset delays test sensitivity to the exact echo. Values are fresh useful bit/s across three seeds.</p><div class="table-scroll"><table class="evidence-table" id="current-diversity-table"><caption>Simulated channel · one shared two-path realization</caption><thead><tr><th>Band · spacing · trace</th><th>Lower</th><th>Upper</th><th>Both</th></tr></thead><tbody>{diversity}</tbody></table></div></details>
    </div></section>
    <section class="evidence-section" id="benchmarks"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Measured on naamah · current recovery profile</p><h2 class="section-title">Simulated channel.<br>Software latency.</h2><p class="section-intro">{passing} of {len(latencies)} configurations pass the 2.1 ms added-processing and buffering allowance, including twelve with the long disturbed-channel equalizer. Transmission time, modem/FEC residence and acquisition remain separately visible.</p></header>
      <div class="evidence-stats"><div><strong>{worst:.3f}<small> ms</small></strong><span>Worst added p99.9</span></div><div><strong>{passing}/{len(latencies)}</strong><span>Current configurations pass</span></div><div><strong>2.1<small> ms</small></strong><span>Unchanged processing and buffering limit</span></div></div>
      <div class="table-scroll"><table class="evidence-table" id="current-latency-table"><caption>Simulated channel · current host measurements in milliseconds</caption><thead><tr><th>Configuration / equalizer span</th><th>Added p99.9</th><th>Total p99.9</th><th>Intrinsic p50 / p99.9</th><th>Result</th></tr></thead><tbody>{timing}</tbody></table></div>
      <p class="evidence-provenance">Serial twelve-second paced loopbacks include source creation, the auction, framing, authentication, FEC, modem processing and 1 ms audio blocks. Added latency is each delivered message’s host time above its matched one-sample intrinsic reference. No physical audio device or network socket is measured. Host timings vary and are stored separately from deterministic simulated-time JSON.</p>
      <p class="evidence-provenance">Receiver training is bursty: the longest measured RX call is {rx_burst:.3f} ms. Passing delivered-message percentiles does not establish a 1 ms audio-callback deadline. This fixture creates source messages on its processing loop; delays before creation are outside that latency metric.</p>
      <p class="evidence-provenance">The <a href="{url(DIRECTORY/'SUMMARY.md')}">report includes the twelve-case before/after table</a> and stage breakdowns. OpenSSL contexts and keys are initialized outside the per-frame path.</p>
    </div></section>
    <section class="evidence-section" id="test-results"><div class="section-inner">
      <header class="evidence-head"><p class="section-label">Authenticated records · explicit remaining defects</p><h2 class="section-title">Simulated channel.<br>Injection is rejected.</h2><p class="section-intro">The −10 dB co-channel trace now records {negative['authentication_failures']} authentication failures and zero foreign or corrupt sink deliveries. Authentication failures remain separate from RF lock loss.</p></header>
      <div class="table-scroll"><table class="evidence-table" id="current-auth-table"><caption>Simulated channel · same-waveform interferer with an independent key</caption><thead><tr><th>SIR</th><th>Useful deliveries</th><th>Authentication failures</th><th>FEC gaps</th><th>Foreign/corrupt delivered</th><th>Result</th></tr></thead><tbody>{a8}</tbody></table></div>
      <p class="evidence-provenance">A zero authentication count means no invalid complete record reached that check. D6 separately rejects {data['crypto']['tamper_attempts']} deliberately tampered records, {data['crypto']['replay_rejections']} same-session replays and {data['crypto']['old_epoch_authentication_failures']} old-epoch records. Two sender processes used {data['crypto']['nonces_observed']} distinct epoch/sequence nonces under one key. The compact format keeps the durable epoch in authenticated context supplied over fiber; no wall-clock nonce is used.</p>
      <p class="section-intro"><strong>{m['remaining_assertions']} failing assertions across {m['remaining_cases']} cases remain</strong> in the current selection. Coordinated key rotation remains open: key IDs are authenticated in both header formats, but overlapping keys and mid-stream old-key retirement are not implemented.</p>
      <details class="evidence-details"><summary>Simulated channel · remaining defects</summary><div class="table-scroll"><table class="evidence-table defect-table" id="current-defect-table"><thead><tr><th>Case</th><th>Assertion</th><th>Finding</th></tr></thead><tbody>{defects}</tbody></table></div></details>
      <details class="evidence-details"><summary>Simulated channel · validation coverage and source</summary><p>{m['recorded_runs']} recorded runs cover {m['unique_case_seed_profiles']} unique case/seed combinations. Both hosts pass 21/21 CTest tests; 15 harness checks and 19 CLI/protobuf checks pass. {m['byte_identical_repeats']} repeated authenticated-message runs have byte-identical canonical JSON. This is a selected campaign; no full-matrix or soak completion is claimed.</p><div class="table-scroll"><table class="evidence-table"><caption>Simulated channel · current validation selection</caption><thead><tr><th>Group</th><th>Current results</th></tr></thead><tbody>{ledger}</tbody></table></div><p>All unapproved acceptance margins remain THRESHOLD_TBD. Finite simulated traces do not establish route availability. Runtime overruns and every remaining defect are retained in the report.</p><p>Tested source SHA-256 <code class="source-hash">{m['source_tree_sha256']}</code>.</p></details>
      <div class="evidence-links"><a href="{url(DIRECTORY/'SUMMARY.md')}">Current simulated channel report →</a><a href="{url(DIRECTORY/'VALIDATION.json')}">Validation manifest →</a><a href="{url(DIRECTORY/'source-snapshot.tar.gz')}">Tested source snapshot →</a></div>
    </div></section>
{end}'''
    js="// Current simulated channel evidence; generated from results/disturbed-recovery only.\n"
    js+="globalThis.GoblinChannelResults = "+json.dumps(data,ensure_ascii=True,allow_nan=False,separators=(",",":"))+";\n"
    return sections,js
