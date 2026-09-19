# Goblin Cannon simulated channel current results

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

The original 908 recorded runs all disable carrier correction. All 722 Watterson runs use zero mean per-path Doppler shift and zero injected residual carrier frequency offset or drift. Across all 908 runs, 906 configure zero residual offset and drift; the two null-channel exceptions are a +5 Hz carrier frequency offset test and a +1 Hz/minute carrier-frequency drift test.

Warm recovery, elapsed-symbol RLS uncertainty, a 13-byte authenticated header and calibrated frequency diversity are implemented and tested. Carrier correction is off; the full 16-byte AES-GCM tag and persisted nonce epochs remain.

[Current report and open thresholds](disturbed-recovery/SUMMARY.md) · [Validation](disturbed-recovery/VALIDATION.json) · [Measured power](disturbed-recovery/POWER.json)

## Simulated channel — 24 kHz disturbed fresh useful bit/s

Three seeds, 100 seconds each. Both columns are freshly measured at the corrected 30 dB reference; the baseline disables the new recovery/header controls.

| Configuration | Calibrated baseline | Combined changes |
| --- | --- | --- |
| BPSK · convolutional | 2.16–3.20 | 7.92–15.60 |
| BPSK · BCH | 1.52–3.52 | 20.64–25.20 |
| QPSK · convolutional | 1.84–4.48 | 28.64–31.68 |
| QPSK · BCH | 2.24–7.36 | 38.00–46.48 |
| 8-PSK · convolutional | 0.32–1.60 | 14.56–16.64 |
| 8-PSK · BCH | 0.64–1.12 | 17.92–24.72 |

## Simulated channel — latency and security

24 of 24 measured latency configurations pass the unchanged 2.1 ms delivered-message added-processing/buffering limit; worst added p99.9 is 1.196315 ms. RX training calls still peak at 14.010 ms. Per-message passes do not establish a 1 ms audio-callback deadline; the report preserves stage timings and the fixture's source-scheduling limitation.

A8 rejects injection at all three SIR settings. At −10 dB it counts 373 authentication failures and zero corrupt deliveries. D6 verifies tampering, replay, negotiated context and restart-safe nonces. 5 expected-failing assertions across 5 cases remain in the expanded current selection; each is listed in the report.

The result set includes the three modulation families, two coding choices, both bandwidths, quiet/moderate/disturbed presets, component comparisons and matched-power diversity controls. These finite simulated channels do not establish route availability. No live recording or soak result is claimed.
