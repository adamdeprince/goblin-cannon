#!/usr/bin/env python3
"""Publish recorded simulated channel evidence; never run or synthesize a channel."""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from html import escape
import hashlib
import json
from pathlib import Path
import re


ROOT = Path(__file__).resolve().parents[1]
RESULTS = ROOT / "results/fixes-2-5"
WEB = ROOT / "html"
GITHUB = "https://github.com/adamdeprince/goblin-cannon/blob/main/"
START = "    <!-- BEGIN GENERATED SIMULATED CHANNEL RESULTS -->"
END = "    <!-- END GENERATED SIMULATED CHANNEL RESULTS -->"
MODES = {"qpsk": "QPSK / 4-QAM", "16qam": "16-QAM", "64qam": "64-QAM"}
PRESETS = {"quiet": (1, .5), "moderate": (3, 10), "disturbed": (7, 30)}


def read(path):
    return json.loads(path.read_text())


def url(path):
    return GITHUB + str(path.relative_to(ROOT))


def link(path, label):
    return f'<a href="{escape(url(path))}">{escape(label)}</a>'


def records(directory):
    return [(p, read(p)) for p in sorted(directory.glob("*/[0-9]*.json"))
            if not p.name.endswith(".host.json")]


def number(value):
    return "Unobserved" if value is None else f"{value:.3f}"


def build():
    if (ROOT / "results/recovery-improvements/VALIDATION.json").exists():
        from recovery_html import build as build_recovery
        sections, js = build_recovery(ROOT, START, END)
        if (ROOT / "results/psk-improvements/VALIDATION.json").exists():
            from psk_html import build as build_psk
            psk_section, psk_js = build_psk()
            sections = sections.replace(START, START + psk_section, 1)
            js += psk_js
        return sections, js
    manifest = read(RESULTS / "VALIDATION.json")
    main = records(RESULTS)
    extra = records(RESULTS / "additional-seed")
    for rows, name in ((main, "main"), (extra, "additional_seed")):
        if len(rows) != manifest[f"{name}_cases"]:
            raise ValueError(f"{name}: case count does not match validation manifest")
        if dict(Counter(d["status"] for _, d in rows)) != manifest[f"{name}_statuses"]:
            raise ValueError(f"{name}: status counts do not match validation manifest")
        for path, d in rows:
            if d["parameters"]["source_tree_sha256"] != manifest["source_tree_sha256"]:
                raise ValueError(f"Mixed source snapshots: {path}")
    by_name = {d["test_name"]: (p, d) for p, d in main}
    seed = manifest["seeds"][0]
    report = link(RESULTS / "FIXES.md", "Read the validation report →")
    tables = link(RESULTS / "SUMMARY.md", "All recorded group tables →")
    hosts = link(RESULTS / "HOSTS.json", "Host and build configurations")
    provenance = (
        f'Base revision <code>{manifest["git_commit"][:12]}</code>; tested source '
        f'SHA-256 <code class="source-hash">{manifest["source_tree_sha256"]}</code>. '
        f'The source snapshot includes the fixes made after that base commit. '
        f'{link(RESULTS / "source-snapshot.tar.gz", "Download the tested source")}.'
    )

    latency = []
    for bandwidth in (10000, 24000):
        for mode in MODES:
            for span in ("short", "long"):
                suffix = "_polar_span" if span == "long" else ""
                path, d = by_name[f"B5_{bandwidth}_{mode}{suffix}_null"]
                sidecar = path.with_name(f"{seed}.host.json")
                h = read(sidecar)
                if h["parameters"] != d["parameters"]:
                    raise ValueError(f"Host/canonical parameter mismatch: {path}")
                latency.append(dict(
                    bandwidth=bandwidth, modulation=mode, span=span,
                    kind=d["kind"], tier=d["tier"], status=d["status"],
                    parameters=d["parameters"], metrics=d["metrics"],
                    host_metrics={k: v for k, v in h["observations"].items()
                                  if k.endswith("percentiles") or k == "added_software_latency_assertion"},
                    reference_metrics=d["latency_reference"]["metrics"],
                    source=url(path), host_source=url(sidecar),
                ))
    added = [x["host_metrics"]["host_added_software_latency_ms_percentiles"]["p99_9"] for x in latency]
    passes = sum(x["host_metrics"]["added_software_latency_assertion"]["status"] == "pass" for x in latency)
    compact_rows = []
    for short, long in zip(latency[::2], latency[1::2]):
        cells = [x["host_metrics"]["host_added_software_latency_ms_percentiles"]["p99_9"] for x in (short, long)]
        compact_rows.append(
            f'<tr><th scope="row">{short["bandwidth"] // 1000} kHz · {MODES[short["modulation"]]}</th>'
            f'<td>{number(cells[0])} ms</td><td>{number(cells[1])} ms</td></tr>'
        )
    detailed_rows = []
    for x in latency:
        h = x["host_metrics"]
        p = h["host_added_software_latency_ms_percentiles"]
        detailed_rows.append(
            f'<tr><th scope="row"><a href="{x["host_source"]}">{x["bandwidth"] // 1000} kHz · '
            f'{MODES[x["modulation"]]} · {x["span"]}</a></th>'
            + "".join(f'<td>{number(p[k])}</td>' for k in ("p50", "p99", "p99_9", "max"))
            + f'<td>{number(h["host_latency_ms_percentiles"]["p99_9"])}</td>'
            + f'<td><a href="{x["source"]}">{number(x["reference_metrics"]["latency_ms"]["p99_9"])}</a></td></tr>'
        )

    polar = []
    polar_rows = []
    for bandwidth in (10000, 24000):
        for mode in MODES:
            cells = []
            for preset, expected in PRESETS.items():
                for span in ("short", "causal", "delayed"):
                    name = f"A2_polar_{bandwidth}_{mode}_high_lat_{preset}_{span}"
                    path, d = by_name[name]
                    p = d["parameters"]
                    if (p["delay_spread_ms"], p["doppler_spread_hz"]) != expected or p["carrier_correction"] != 0:
                        raise ValueError(f"Unexpected polar parameters: {path}")
                    polar.append(dict(test_name=name, preset=preset, span=span, parameters=p,
                                      kind=d["kind"], tier=d["tier"], status=d["status"],
                                      metrics=d["metrics"], observations=d["observations"], source=url(path)))
                    if span == "delayed":
                        o = d["observations"]
                        label = f'{o["frames_survived"]:,} / {o["frames_sent"]:,}'
                        cells.append(f'<td>{link(path, label)}</td>')
            polar_rows.append(f'<tr><th scope="row">{bandwidth // 1000} kHz · {MODES[mode]}</th>' + "".join(cells) + '</tr>')

    statuses = ("pass", "characterized", "THRESHOLD_TBD", "xfail", "unavailable")
    group_names = dict(A="Channel", B="Radio / audio", C="Modem", D="Data path / scheduler", E="Harness")
    groups = defaultdict(Counter)
    failures = []
    for path, d in main:
        groups[d["group"][0]][d["status"]] += 1
        for assertion in d["assertions"]:
            if assertion["status"] == "xfail":
                failures.append(f'<tr><th scope="row">{link(path, d["test_name"])}</th>'
                                f'<td>{escape(assertion["assertion"])}</td><td>{escape(assertion["reason"])}</td></tr>')
    if len(failures) != read(RESULTS / "EXPECTED_FAILURE_REVIEW.json")["after_count"]:
        raise ValueError("Expected-failure review does not match result assertions")
    group_rows = []
    for group, title in group_names.items():
        group_rows.append(f'<tr><th scope="row">{group} · {title}</th>'
                          + "".join(f'<td>{groups[group][s]}</td>' for s in statuses) + '</tr>')
    summary_rows = "".join(group_rows)
    summary_rows += f'<tr class="table-total"><th scope="row">Main run · {len(main)} cases</th>' + "".join(
        f'<td>{manifest["main_statuses"].get(s, 0)}</td>' for s in statuses) + '</tr>'
    summary_rows += f'<tr><th scope="row">Independent seed · {len(extra)} cases</th>' + "".join(
        f'<td>{manifest["additional_seed_statuses"].get(s, 0)}</td>' for s in statuses) + '</tr>'
    ctests = " and ".join(f'{v["passed"]}/{v["passed"] + v["failed"]} on <code>{escape(k)}</code>'
                          for k, v in manifest["ctest"].items())

    sections = f'''{START}
    <section class="evidence-section" id="benchmarks">
      <div class="section-inner">
        <header class="evidence-head">
          <p class="section-label">B5 · Quiet host: naamah · 12 configurations</p>
          <h2 class="section-title">Simulated channel.<br>Measured software.</h2>
          <p class="section-intro">The 2.1 ms allowance applies to added processing and buffering. Transmission, modem/FEC residence and startup are recorded separately. The quiet-host runs meet that allowance in both bandwidths and all three constellations.</p>
        </header>
        <div class="evidence-stats">
          <div><strong>{max(added):.3f} <small>ms</small></strong><span>Highest added p99.9 across 12 runs</span></div>
          <div><strong>2.1 <small>ms</small></strong><span>Added processing / buffering limit</span></div>
          <div><strong>{passes} / {len(latency)}</strong><span>Null-channel configurations pass</span></div>
        </div>
        <div class="evidence-columns">
          <div class="table-scroll" role="region" aria-label="Simulated channel latency benchmarks" tabindex="0">
            <table class="evidence-table">
              <caption>Simulated channel · added wall-clock p99.9</caption>
              <thead><tr><th scope="col">Profile</th><th scope="col">Short span</th><th scope="col">Long span</th></tr></thead>
              <tbody>{''.join(compact_rows)}</tbody>
            </table>
          </div>
          <div class="evidence-method">
            <h3>What the clock includes</h3>
            <p>Source creation → auction → framing → FEC/crypto → modem → sink, with paced 48-sample (1 ms) audio blocks and OS scheduling. Each trace lasts 12 seconds at 100 source messages per second.</p>
            <p>Subtract the one-sample simulated reference from each matching delivered message <em>before</em> computing percentiles. Canonical sample-clock metrics and variable host timings stay separate.</p>
            <p>The long equalizer uses the high-latitude quiet span through a null channel. No physical audio device, network socket or radio is included. These are local software measurements.</p>
            <p><code>naamah</code>: Threadripper PRO 5995WX · AVX2 · GCC 16.1 · Release. {hosts}.</p>
          </div>
        </div>
        <details class="evidence-details">
          <summary>Simulated channel · all latency percentiles and separate modem reference</summary>
          <p>All values in milliseconds. “Total” is measured creation-to-sink time; “reference” is transmission, modem/FEC and startup on the simulated sample clock. Quantiles are not additive. Each profile links to its host record; each reference links to full parameters and the stage breakdown.</p>
          <div class="table-scroll" role="region" aria-label="Simulated channel latency details" tabindex="0">
            <table class="evidence-table">
              <caption>Simulated channel · added versus total latency</caption>
              <thead><tr><th scope="col">Profile / equalizer span</th><th scope="col">Added p50</th><th scope="col">Added p99</th><th scope="col">Added p99.9</th><th scope="col">Added max</th><th scope="col">Total p99.9</th><th scope="col">Reference p99.9</th></tr></thead>
              <tbody>{''.join(detailed_rows)}</tbody>
            </table>
          </div>
          <p>RRC group delay, equalizer decision delay, serialization and Viterbi lookahead are reported as residence estimates. CPU stage timings in the host files are per-call observations, not an additive per-message breakdown.</p>
        </details>
        <p class="evidence-provenance">{provenance}</p>
      </div>
    </section>

    <section class="evidence-section polar-section" id="rf-simulation">
      <div class="section-inner">
        <header class="evidence-head">
          <p class="section-label">A2 · Polar screening · Characterize / full</p>
          <h2 class="section-title">Simulated channel.<br>The polar limit.</h2>
          <p class="section-intro">QPSK survives the quiet, delayed-equalizer trace in both bandwidths. Moderate and disturbed traces deliver no bit-exact RF frames. Even the quiet trace loses most 16-QAM and 64-QAM frames. These are ten-second observations, not an operating envelope for the route near 71°N.</p>
        </header>
        <div class="model-assumptions">
          <span>Two independent Rayleigh paths</span><span>Gaussian Doppler spectrum</span><span>Nominal 30 dB SNR</span><span>Seed 0x71A001</span><span>Carrier correction off</span>
        </div>
        <p class="evidence-provenance">The explorer selects among {len(polar)} saved runs. It does not generate a new channel in the browser. All use adaptive equalization and sample-clock recovery. Doppler spread is the fading rate (2σ), distinct from carrier offset. The radio handles carrier frequency correction.</p>
        <div id="rf-explorer" class="rf-explorer" hidden>
          <div class="rf-controls">
            <label for="rf-bandwidth">Occupied bandwidth<select id="rf-bandwidth"><option value="24000">24 kHz</option><option value="10000">10 kHz</option></select></label>
            <label for="rf-modulation">Constellation<select id="rf-modulation"><option value="qpsk">QPSK / 4-QAM</option><option value="16qam">16-QAM</option><option value="64qam">64-QAM</option></select></label>
            <label for="rf-span">Equalizer span<select id="rf-span"><option value="delayed">Long, with decision delay</option><option value="causal">Long feedback, no delay</option><option value="short">Short baseline</option></select></label>
            <label for="rf-preset">High-latitude preset<select id="rf-preset"><option value="quiet">Quiet · 1 ms / 0.5 Hz</option><option value="moderate">Moderate · 3 ms / 10 Hz</option><option value="disturbed">Disturbed · 7 ms / 30 Hz</option></select></label>
          </div>
          <div id="rf-output" aria-live="polite" aria-atomic="true">
            <div class="rf-outcome"><p class="section-label">Recorded simulated channel result</p><h3 id="rf-outcome-title"></h3><p id="rf-outcome-note"></p></div>
            <div class="rf-metrics">
              <div><span>Bit-exact RF frame survival</span><strong id="rf-survival"></strong><small id="rf-frames"></small></div>
              <div><span>Observed BER</span><strong id="rf-ber"></strong><small id="rf-observed"></small></div>
              <div><span>Raw RF-frame goodput</span><strong id="rf-goodput"></strong><small>Not application payload goodput</small></div>
              <div><span>Validated headers / lock losses</span><strong id="rf-lock"></strong><small id="rf-acquisition"></small></div>
            </div>
            <div class="rf-comparison" id="rf-comparison" aria-label="Simulated channel frame survival across polar presets"></div>
            <p class="rf-parameters" id="rf-parameters"></p>
            <a class="evidence-link" id="rf-record" href="#rf-static">Inspect full parameters and result →</a>
          </div>
        </div>
        <div class="table-scroll" id="rf-static" role="region" aria-label="Simulated channel polar results" tabindex="0">
          <table class="evidence-table">
            <caption>Simulated channel · delayed equalizer · bit-exact frames / sent frames</caption>
            <thead><tr><th scope="col">Profile</th><th scope="col">Quiet<br><small>1 ms / 0.5 Hz</small></th><th scope="col">Moderate<br><small>3 ms / 10 Hz</small></th><th scope="col">Disturbed<br><small>7 ms / 30 Hz</small></th></tr></thead>
            <tbody>{''.join(polar_rows)}</tbody>
          </table>
        </div>
        <p class="evidence-provenance">Equal mean path powers; 10 seconds requested per point, with startup/tail included in actual simulated duration. Nominal SNR uses a unit-mean constellation reference, not 3 kHz SNR or Eb/N₀. Raw RF frame bits are measured before the production message path; BER covers compared bits only. Unobserved BER is not zero. Each table cell links to the complete parameter record.</p>
        <p class="evidence-provenance">The 24 kHz model extrapolates F.1487 beyond its approximately 12 kHz scope. This is the project’s single-carrier RRC waveform with WBHF constellation mappings; it is not certified MIL-STD-188-110C performance. No recorded-band noise beds are available.</p>
      </div>
    </section>

    <section class="evidence-section" id="test-results">
      <div class="section-inner">
        <header class="evidence-head">
          <p class="section-label">Selected regression coverage · Seeds 0x71A001 / 0x71A002</p>
          <h2 class="section-title">Simulated channel.<br>The test ledger.</h2>
          <p class="section-intro">{manifest['main_cases']} main cases and {manifest['additional_seed_cases']} independent-seed cases are recorded. A characterization is a measurement, not a pass. Open acceptance thresholds stay <code>THRESHOLD_TBD</code>; known defects stay <code>xfail</code>.</p>
        </header>
        <div class="table-scroll" role="region" aria-label="Simulated channel test status by group" tabindex="0">
          <table class="evidence-table">
            <caption>Simulated channel · case statuses, not assertion counts</caption>
            <thead><tr><th scope="col">Group</th><th scope="col">Pass</th><th scope="col">Characterize</th><th scope="col">Threshold open</th><th scope="col">Expected failure</th><th scope="col">Unavailable</th></tr></thead>
            <tbody>{summary_rows}</tbody>
          </table>
        </div>
        <div class="evidence-columns">
          <div class="evidence-method">
            <h3>What was verified</h3>
            <ul>
              <li>C++ / gRPC CTest: {ctests}. Nine Python harness checks pass.</li>
              <li>A4: all 60 synchronization / boundary assertions pass for each seed, retaining ten-minute drift and clock traces. BER margins remain open; ±200 ppm stays characterization.</li>
              <li>B1: all 48 gain-step cases pass for each seed; affected-frame error rates are reported.</li>
              <li>B4 / D4: explicit audio gaps, duplicate and stale suppression, serial wrap and FEC gaps pass.</li>
              <li>D1: maximum waiting auction depth is one at 1.5×, 3× and 10× load; no superseded candidate reaches the framer.</li>
              <li>E1: three repeated seeded scenarios produce identical canonical results.</li>
            </ul>
          </div>
          <div class="evidence-method evidence-findings">
            <h3>What remains unresolved</h3>
            <ul>
              <li>Polar moderate / disturbed reception and dropout recovery; 24 kHz header acquisition at 0 and 3 dB.</li>
              <li>AES-CTR + CRC provides no AEAD authentication. Restart can reuse the default keystream; coordinated key retirement is absent. The −10 dB co-channel trace delivers non-source payloads.</li>
              <li>Strict cross-key priority can starve a lower bid. Older data receives no age boost. Four 10× overload messages became stale while already in flight.</li>
              <li>The A4/B1 quick subset alone took 132.085 s on four-worker <code>avx10</code>, over the whole-tier 120 s budget. Samples and durations were retained.</li>
              <li>The complete A1/A5/A6/A7/C1 grids and soak were not rerun. E4 awaits recordings. C5 mode changes and D5 parallel fiber delivery remain unavailable.</li>
            </ul>
          </div>
        </div>
        <details class="evidence-details">
          <summary>Simulated channel · defects found: {len(failures)} expected failing assertions across {manifest['main_statuses']['xfail']} cases</summary>
          <div class="table-scroll" role="region" aria-label="Simulated channel expected failures" tabindex="0">
            <table class="evidence-table defect-table"><caption>Simulated channel · retained expected failures</caption>
              <thead><tr><th scope="col">Case</th><th scope="col">Assertion</th><th scope="col">Reason</th></tr></thead>
              <tbody>{''.join(failures)}</tbody>
            </table>
          </div>
        </details>
        <div class="evidence-links">{report}{tables}{link(ROOT / 'TESTING.md', 'Run each tier →')}{link(ROOT / 'tests/simulated_channel/QUESTIONS.md', 'Open thresholds and design questions →')}</div>
        <p class="evidence-provenance">{provenance}</p>
      </div>
    </section>
{END}'''
    data = dict(report_header="Goblin Cannon simulated channel HTML evidence",
                git_commit=manifest["git_commit"], source_tree_sha256=manifest["source_tree_sha256"],
                seeds=manifest["seeds"], polar=polar, latency=latency,
                validation_source=url(RESULTS / "VALIDATION.json"))
    # A plain script works on static hosting and when index.html is opened locally.
    js = "// Generated by scripts/update_html_results.py from recorded simulated channel results.\n"
    js += "globalThis.GoblinChannelResults = " + json.dumps(data, ensure_ascii=True, allow_nan=False, separators=(",", ":")) + ";\n"
    return sections, js


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="Fail if published evidence is out of date")
    args = parser.parse_args()
    sections, js = build()
    index = WEB / "index.html"
    old = index.read_text()
    before, tail = old.split(START, 1)
    _, after = tail.split(END, 1)
    document = before + sections + after
    for name, content in (("simulated-channel.js", js.encode()),
                          ("rf-explorer.js", (WEB/"rf-explorer.js").read_bytes()),
                          ("psk-explorer.js", (WEB/"psk-explorer.js").read_bytes()),
                          ("evidence.css", (WEB/"evidence.css").read_bytes())):
        version = hashlib.sha256(content).hexdigest()[:16]
        document = re.sub(r'((?:src|href)=")'+re.escape(name)+r'(?:\?[^" ]*)?"',
                          lambda m: m.group(1)+name+"?v="+version+'"', document)
    outputs = {index: document, WEB / "simulated-channel.js": js}
    stale = [path for path, value in outputs.items() if not path.exists() or path.read_text() != value]
    if args.check:
        if stale:
            parser.exit(1, "Stale simulated channel HTML: " + ", ".join(str(p.relative_to(ROOT)) for p in stale) + "\n")
        print("Simulated channel HTML matches the recorded results.")
    else:
        for path, value in outputs.items():
            path.write_text(value)
        print("Updated simulated channel HTML from recorded parameter-complete results.")


if __name__ == "__main__":
    main()
