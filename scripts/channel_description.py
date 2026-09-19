"""Shared wording for the channel quantities, measured interface and presets."""
import json
from html import escape
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tests/simulated_channel"))
from channel_metadata import DOPPLER_SHIFT_DEFINITION, DOPPLER_SPREAD_DEFINITION, SPREAD_CONVENTION

ITU_URL = "https://www.itu.int/dms_pubrec/itu-r/rec/f/R-REC-F.1487-0-200005-I!!PDF-E.pdf"
PRESETS = (("Quiet", 1, .5, "4.1"), ("Moderate", 3, 10, "4.2"), ("Disturbed", 7, 30, "4.3"))
RECORDED_OFFSETS = (
    "The original 908 recorded runs all disable carrier correction. All 722 Watterson runs use "
    "zero mean per-path Doppler shift and zero injected residual carrier frequency offset or drift. "
    "Across all 908 runs, 906 configure zero residual offset and drift; the two null-channel "
    "exceptions are a +5 Hz carrier frequency offset test and a +1 Hz/minute carrier-frequency drift test."
)


def sweep_data():
    path = ROOT / "results/carrier-offset/DATA.json"
    return json.loads(path.read_text()) if path.exists() else None


def boundary_text(tolerance_hz=None):
    if tolerance_hz is None:
        data = sweep_data()
        tolerance_hz = data["tolerance_hz"] if data else None
    tolerance = f"{tolerance_hz:g}" if tolerance_hz is not None else "(tolerance being measured)"
    return ("The modem assumes the radio hands it audio with the carrier frequency offset "
            f"already removed to within {tolerance} Hz. It performs no Doppler-shift correction. "
            "Delay spread, Doppler spread, fading, phase rotation, multipath and noise are "
            "the modem's problem, and are what the recorded runs measure.")


def scope_text(data=None):
    return ("This boundary describes the recorded acceptance profile. The carrier-offset sweep uses "
            "24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, "
            "30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to "
            "that measured configuration and the tested offset grid. Other modes and historical "
            "receiver versions have no tolerance established by this sweep. The library retains "
            "an optional carrier-correction loop, enabled by default; the recorded acceptance "
            "profile explicitly disables it. Equalizer phase tracking does not estimate "
            "a mean carrier frequency offset or perform AFC.")


def definitions_markdown():
    return DOPPLER_SHIFT_DEFINITION + "\n\n" + DOPPLER_SPREAD_DEFINITION


def preset_markdown():
    lines = ["| High-latitude preset | Delay spread (ms) | Doppler spread (Hz) | F.1487 Annex 3 |",
             "| --- | ---: | ---: | --- |"]
    lines.extend(f"| {name} | {delay:g} | {width:g} | §{section} |" for name, delay, width, section in PRESETS)
    lines += ["", SPREAD_CONVENTION + " Thus 30 Hz means σ = 15 Hz. The two taps fade independently; "
              "delay spread is their differential delay. Mean per-path Doppler shift is a separate "
              f"parameter; these presets use zero. [Recommendation, Annex 1 §2 and Annex 3 §§1, 4.1–4.3]({ITU_URL})."]
    return "\n".join(lines)


def compact_markdown():
    return "\n\n".join(["<!-- BEGIN CHANNEL CONTRACT -->", "For the recorded acceptance profile:",
                         boundary_text(), scope_text(), "<!-- END CHANNEL CONTRACT -->"])


def context_html(*, historical=False):
    definitions = "".join(f"<p>{escape(value)}</p>" for value in (DOPPLER_SHIFT_DEFINITION, DOPPLER_SPREAD_DEFINITION))
    rows = "".join(f"<tr><th scope=\"row\">{name}</th><td>{delay:g}</td><td>{width:g}</td><td>§{section}</td></tr>"
                   for name,delay,width,section in PRESETS)
    history = "<p class=\"evidence-provenance\">This is a historical campaign; the current interface tolerance below was measured separately.</p>" if historical else ""
    return history + f'''<div class="channel-boundary">
      <p class="evidence-provenance"><strong>Radio/software boundary for the recorded acceptance profile.</strong> {escape(boundary_text())}</p>
      <p class="evidence-provenance">{escape(scope_text())}</p>
      <details class="evidence-details"><summary>Doppler shift and Doppler spread</summary>{definitions}</details>
      <div class="table-scroll"><table class="evidence-table channel-presets"><caption>ITU-R F.1487 high-latitude channel presets</caption><thead><tr><th>Preset</th><th>Delay spread (ms)</th><th>Doppler spread (Hz)</th><th>Annex 3</th></tr></thead><tbody>{rows}</tbody></table></div>
      <p class="evidence-provenance">{escape(SPREAD_CONVENTION)} Thus 30 Hz means σ = 15 Hz. The taps fade independently. Mean per-path Doppler shift is a separate parameter; these presets use zero. <a href="{ITU_URL}">F.1487 Annex 1 §2 and Annex 3 §§1, 4.1–4.3</a>.</p>
      {'' if historical else '<p class="evidence-provenance">'+escape(RECORDED_OFFSETS)+'</p>'}
    </div>'''


def sweep_html():
    data = sweep_data()
    if not data:
        return '<p class="evidence-provenance">Carrier frequency offset tolerance: (tolerance being measured).</p>'
    rows = []
    for row in data["rows"]:
        d, g = row["delivery_percent"], row["fresh_goodput_bps"]
        sources = " · ".join(f'<a href="{url}">{seed}</a>' for seed,url in zip(data["seeds"],row["sources"]))
        rows.append(f'<tr><th scope="row">{row["carrier_frequency_offset_hz"]:+g}</th>'
                    f'<td>{row["mean_delivery_percent"]:.4f}<br>{min(d):.4f}–{max(d):.4f}</td>'
                    f'<td>{row["mean_fresh_goodput_bps"]:.2f}<br>{min(g):.2f}–{max(g):.2f}</td>'
                    f'<td>{row["max_absolute_paired_delta_percentage_points"]:.4f}</td><td>{sources}</td></tr>')
    return f'''<details class="evidence-details" id="carrier-offset-sweep"><summary>Measured carrier frequency offset tolerance: {data['tolerance_hz']:g} Hz</summary>
      <p>{escape(data['criterion'])} The largest passing tested magnitude before the first failure is {data['tolerance_hz']:g} Hz. This is a sampled bound for the stated quiet-preset configuration. Both signs reach delivery collapse by {data['collapse_magnitude_hz']:g} Hz. No carrier-offset correction was added.</p>
      <p>Zero-offset delivery varies by {data['baseline_seed_range_percentage_points']:.4f} percentage points across the three seeds. All zero-offset observations and metrics match the previously published quiet controls. Delivery is delivered / framed messages; fresh goodput uses the existing source-key freshness metric.</p>
      <div class="table-scroll"><table class="evidence-table"><caption>Quiet high-latitude preset · 24 kHz QPSK+BCH · 30 dB nominal SNR · 300 seconds per seed · mean and seed range</caption><thead><tr><th>Carrier frequency offset (Hz)</th><th>Delivery (%)</th><th>Fresh goodput (bit/s)</th><th>Largest paired change (percentage points)</th><th>Seed records</th></tr></thead><tbody>{''.join(rows)}</tbody></table></div>
      <p><a href="https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/SUMMARY.md">Sweep method, records and source snapshot</a>.</p></details>'''
