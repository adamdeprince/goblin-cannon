#!/usr/bin/env python3
"""Audit measured transmitter power in the saved simulated channel RF traces.

This adds assertions over existing measurements; it does not rerun or rescale
the channel. The numerical tolerance is the existing finite-waveform tolerance
in test_audio_waveform.cpp, not a channel acceptance threshold.
"""
import hashlib
import json
import math
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DIRECTORY = ROOT / "results/refinement"
OUTPUT = DIRECTORY / "power-audit"
SEEDS = (7446529, 7446530, 7446531)
TOLERANCE = .02
KNOWN_SOURCE = "1279f74e940aad991bf328e3b7cd796ea496b24bd9e05c78e3a6c6a8cec322e8"
EXPECTED = {
    **{f"E_power_nominal_{band}_{variant}":
       "The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes."
       for band in (10000, 24000) for variant in ("bpsk_bch", "diversity_commensurate_both")},
    **{f"E_power_fullband_{band}":
       "The diversity branch gain increases measured power by about B/branch_width relative to full-band BPSK."
       for band in (10000, 24000)}
}


def source(band, variant, preset, seed):
    path = DIRECTORY / f"A2_refinement_screen_{band}_{variant}_high_lat_{preset}" / f"{seed}.json"
    raw = path.read_bytes()
    record = json.loads(raw)
    return dict(record=str(path.relative_to(ROOT)), sha256=hashlib.sha256(raw).hexdigest(),
                parameters=record["parameters"], measured_power=record["observations"]["tx_mean_sample_power"])


def audit(name, seed, inputs, ratios, description):
    passed = all(abs(r - 1) <= TOLERANCE for r in ratios)
    known = name in EXPECTED and seed == SEEDS[0] and all(
        r["parameters"]["source_tree_sha256"] == KNOWN_SOURCE for r in inputs)
    status = ("xpass" if passed else "xfail") if known else ("pass" if passed else "fail")
    reason = EXPECTED[name] if known else description
    record = dict(report_header="simulated channel power calibration assertion", test_name=name,
        kind="assert", tier="quick", group="E", seed=seed, status=status,
        parameters=dict(seed=seed, git_commit=inputs[0]["parameters"]["git_commit"],
            source_tree_sha256=inputs[0]["parameters"]["source_tree_sha256"],
            ratio_tolerance=TOLERANCE, tolerance_basis="Existing 2% finite-RRC waveform power tolerance",
            scope="Assertion over saved pre-channel waveform measurements; no new channel run or normalization",
            input_records=inputs),
        metrics=dict(power_ratios=ratios, comparison=description),
        assertions=[dict(assertion="power_ratio_within_numerical_tolerance", status=status, reason=reason)])
    path = OUTPUT / name / f"{seed}.json"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(record, indent=2, sort_keys=True, allow_nan=False) + "\n")
    return path, record


def main():
    rows = []
    for band in (10000, 24000):
        for variant in ("bpsk_bch", "diversity_commensurate_both"):
            r = source(band, variant, "moderate", SEEDS[0])
            ratio = r["measured_power"] / r["parameters"]["nominal_sample_power"]
            rows.append(audit(f"E_power_nominal_{band}_{variant}", SEEDS[0], [r], [ratio],
                              "Measured pre-channel sample power / declared noise-reference power"))
        reference = source(band, "bpsk_bch", "moderate", SEEDS[0])
        diversity = source(band, "diversity_commensurate_both", "moderate", SEEDS[0])
        rows.append(audit(f"E_power_fullband_{band}", SEEDS[0], [reference, diversity],
                          [diversity["measured_power"] / reference["measured_power"]],
                          "Two-copy measured power / full-band BPSK measured power"))
        for spacing in ("commensurate", "offset137", "wide137"):
            for preset in ("quiet", "moderate", "disturbed"):
                for seed in SEEDS:
                    inputs = [source(band, f"diversity_{spacing}_{branch}", preset, seed)
                              for branch in ("lower", "upper", "both")]
                    ratios = [r["measured_power"] / inputs[0]["measured_power"] for r in inputs[1:]]
                    rows.append(audit(f"E_power_controls_{band}_{spacing}_{preset}", seed, inputs, ratios,
                                      "Upper-copy and two-copy measured power / lower-copy measured power"))
    from collections import Counter
    manifest = dict(report_header="simulated channel power audit", cases=len(rows),
                    statuses=dict(Counter(r["status"] for _, r in rows)),
                    seed_policy="Same explicit seeds and parameter records as the input RF screens",
                    defects=[dict(test_name=r["test_name"], seed=r["seed"], reason=r["assertions"][0]["reason"],
                                  record=str(p.relative_to(ROOT))) for p, r in rows if r["status"] == "xfail"])
    (OUTPUT / "VALIDATION.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n")
    lines = ["# Simulated channel — power calibration audit", "",
        "The transmitter-power observations reveal two defects: the nominal SNR reference is not the actual pre-channel signal power, and diversity width compensation changes actual power relative to full-band BPSK. Production behavior and the original measurements are retained. Matched lower/upper/both diversity controls do have equal measured power within the existing 2% finite-waveform tolerance.", "",
        "| Assertion | Seed | Power ratio(s) | Status |", "| --- | --- | --- | --- |"]
    for path, r in rows:
        ratios = " / ".join(f"{v:.6f}" for v in r["metrics"]["power_ratios"])
        lines.append(f"| [{r['test_name']}]({path.relative_to(OUTPUT)}) | {r['seed']} | {ratios} | {r['status']} |")
    lines += ["", "## Simulated channel — Defects found", ""]
    for d in manifest["defects"]:
        lines.append(f"- `{d['test_name']}` ({d['seed']}) — {d['reason']}")
    lines += ["", "## Simulated channel — pre-fade SNR interpretation", "",
              "Measured pre-fade SNR is the configured nominal SNR plus 10 log10(measured power / nominal reference power). It is not the instantaneous SNR through a fade.", "",
              "| Band | Waveform | Configured nominal SNR | Measured pre-fade SNR |", "| --- | --- | ---: | ---: |"]
    for band in (10000, 24000):
        for variant in ("bpsk_bch", "diversity_commensurate_both"):
            r = source(band, variant, "moderate", SEEDS[0]); p = r["parameters"]
            actual = p["snr_db"] + 10 * math.log10(r["measured_power"] / p["nominal_sample_power"])
            lines.append(f"| {band//1000} kHz | {variant} | {p['snr_db']} dB | {actual:.3f} dB |")
    (OUTPUT / "SUMMARY.md").write_text("\n".join(lines) + "\n")
    print(json.dumps(manifest, indent=2))
    if any(r["status"] in ("fail", "xpass") for _, r in rows):
        raise SystemExit("Power audit requires review")


if __name__ == "__main__":
    main()
