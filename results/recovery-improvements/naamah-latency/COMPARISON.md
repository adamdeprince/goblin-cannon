# Goblin Cannon simulated channel quiet-host latency comparison

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

**12/12 configurations pass** the 2.1 ms added-processing/buffering limit on `naamah` (AVX2). Added p99.9 spans **0.962–1.110 ms**. All 17/17 CTest entries passed before timing began (9.93 s).

## Simulated channel method and provenance

The tested commit is `86d72bb8ecb63343d8eb32286ed810a59163ac97`; source SHA-256 is `ed6bc5eaa2c79850c88b9cb33e76e741c0df7f227c7b5d469d48a878796a1072`, identical to the AVX-512 campaign. [Host/build metadata and exact commands](HOST.json) record the compiler, kernel, CPU, binary hash, affinity and load averages. The source transfer to naamah was explicitly approved.

All twelve configurations use seed 7446529: 10/24 kHz, QPSK (4-QAM)/16-QAM/64-QAM, short/long equalizer spans. Each runs for the original twelve seconds, with one worker, 48-sample audio blocks and no concurrent validation jobs. Carrier correction is off; adaptive equalization and the recovery profile are on. This is one observation per configuration, not a bound on future host scheduling delays.

Each delivered message is matched to a one-sample simulated-time production-stack reference. Intrinsic transmission, modem/FEC and startup are subtracted per message before computing added-latency percentiles. Total latency and the intrinsic reference remain separate. Host CPU/OS timing is non-canonical; physical audio devices and network sockets are outside this loopback. No RF transmission took place.

**12/12 canonical results match the AVX-512 baseline exactly** after excluding only `git_commit`, `require_avx512` and the observed `demapper`. All full parameters and observations remain in their original JSON; no measured values are normalized or overwritten. [Comparison checks](VALIDATION.json).

## Simulated channel B5 results

All times below are milliseconds. Configuration links open measured host sidecars. The original AVX-512 records remain in the parent directory and the parent report's baseline table.

| Configuration / span | Added p50 | Added p99 | Added p99.9 | Added max | Total p99.9 | Reference p99.9 | avx10 added p99.9 | Status |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| [10 kHz / 16qam / short](B5_10000_16qam_null/7446529.host.json) | 0.317 | 0.963 | 0.993 | 0.993 | 51.009 | 50.313 | 0.989 | pass |
| [10 kHz / 16qam / long](B5_10000_16qam_polar_span_null/7446529.host.json) | 0.319 | 0.965 | 0.997 | 0.997 | 80.034 | 79.188 | 0.976 | pass |
| [10 kHz / 64qam / short](B5_10000_64qam_null/7446529.host.json) | 0.376 | 0.955 | 1.004 | 1.004 | 47.020 | 46.938 | 0.989 | pass |
| [10 kHz / 64qam / long](B5_10000_64qam_polar_span_null/7446529.host.json) | 0.376 | 0.937 | 1.011 | 1.011 | 76.026 | 75.813 | 0.981 | pass |
| [10 kHz / qpsk / short](B5_10000_qpsk_null/7446529.host.json) | 0.461 | 0.959 | 0.962 | 0.962 | 70.003 | 69.187 | 0.961 | pass |
| [10 kHz / qpsk / long](B5_10000_qpsk_polar_span_null/7446529.host.json) | 0.443 | 0.944 | 0.991 | 0.991 | 99.003 | 98.313 | 0.968 | pass |
| [24 kHz / 16qam / short](B5_24000_16qam_null/7446529.host.json) | 0.439 | 0.983 | 1.049 | 1.050 | 21.556 | 20.958 | 1.025 | pass |
| [24 kHz / 16qam / long](B5_24000_16qam_polar_span_null/7446529.host.json) | 0.402 | 1.036 | 1.095 | 1.095 | 37.072 | 36.104 | 1.085 | pass |
| [24 kHz / 64qam / short](B5_24000_64qam_null/7446529.host.json) | 0.804 | 1.019 | 1.066 | 1.066 | 20.042 | 19.521 | 1.043 | pass |
| [24 kHz / 64qam / long](B5_24000_64qam_polar_span_null/7446529.host.json) | 0.774 | 1.044 | 1.110 | 1.110 | 35.112 | 34.708 | 1.074 | pass |
| [24 kHz / qpsk / short](B5_24000_qpsk_null/7446529.host.json) | 0.315 | 0.974 | 1.024 | 1.054 | 26.015 | 25.187 | 1.009 | pass |
| [24 kHz / qpsk / long](B5_24000_qpsk_polar_span_null/7446529.host.json) | 0.330 | 1.024 | 1.089 | 1.089 | 41.049 | 40.333 | 1.054 | pass |

[Complete group table, per-stage call durations, serialization and modem residence estimates](SUMMARY.md). Per-call CPU percentiles are not an additive breakdown of message latency.

## Simulated channel runtime and coverage

| Selection | Cases | Wall seconds |
| --- | ---: | ---: |
| B5 full | 6 | 79.224 |
| B5 quick | 6 | 77.304 |

These are B5 selections, not complete tiers. The original quick/full runtime overruns remain recorded. The original 9,920-case ledger is unchanged; these twelve follow-up runs are stored separately. No soak or fading campaign was rerun on naamah.

## Simulated channel defects found

No new B5 failures or xfails.

The [existing RF, crypto and scheduler findings](../REPORT.md) remain open; a quiet-host latency pass does not resolve them.

## Simulated channel open thresholds

B5 uses the agreed 2.1 ms added-processing/buffering limit. No threshold was changed; other acceptance margins remain `THRESHOLD_TBD` in the parent report.
