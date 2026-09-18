# Goblin Cannon simulated channel current results

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
