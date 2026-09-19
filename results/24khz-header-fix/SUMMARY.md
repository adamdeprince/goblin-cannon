# Goblin Cannon simulated channel report

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

All results use simulated channels. No transmission or RF equipment measurement is represented.

## Simulated channel execution summary

| Status | Cases |
| --- | ---: |
| THRESHOLD_TBD | 88 |
| characterized | 66 |
| pass | 17 |
| unavailable | 3 |
| xfail | 77 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 0 | 0 | 0 | 0 |
| A3 | 0 | 0 | 0 | 0 |
| A4 | 72 | 16 | 44 | 0 |
| A5 | 0 | 0 | 0 | 0 |
| A6 | 0 | 0 | 0 | 0 |
| A7 | 0 | 0 | 0 | 0 |
| A8 | 3 | 3 | 0 | 0 |
| A9 | 3 | 3 | 0 | 0 |
| B1 | 48 | 36 | 0 | 0 |
| B2 | 36 | 0 | 0 | 0 |
| B3 | 18 | 0 | 0 | 0 |
| B4 | 3 | 3 | 0 | 0 |
| B5 | 6 | 6 | 0 | 0 |
| C1 | 0 | 0 | 0 | 0 |
| C2 | 11 | 2 | 8 | 0 |
| C3 | 6 | 0 | 6 | 0 |
| C4 | 32 | 0 | 30 | 1 |
| C5 | 1 | 0 | 0 | 1 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 2 | 2 | 0 | 0 |
| D4 | 4 | 4 | 0 | 0 |
| D5 | 1 | 0 | 0 | 1 |
| D6 | 2 | 2 | 0 | 0 |
| E1 | 3 | 0 | 0 | 0 |
| E2 | 0 | 0 | 0 | 0 |
| E3 | 0 | 0 | 0 | 0 |
| E4 | 0 | 0 | 0 | 0 |

## Simulated channel principal findings

- 24 kHz clean controls: 0/3 produced no valid header. This prevents meaningful impairment comparisons on that profile.
- Known failures remain executable assertions marked `xfail`; production behavior was not changed to satisfy them.
- Runtime budget findings, measured host latency, unsupported capabilities and statistical-duration limits are reported explicitly below.

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (36 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (18 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A4_10000_16qam_-200ppm_10min](A4_10000_16qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0121875 | 7.08326e-05 | 2.1331 | — |
| [A4_10000_16qam_-50ppm_10min](A4_10000_16qam_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.00188802 | 0.000679993 | 20.4777 | — |
| [A4_10000_16qam_200ppm_10min](A4_10000_16qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.016226 | 4.24995e-05 | 1.27986 | — |
| [A4_10000_16qam_50ppm_10min](A4_10000_16qam_50ppm_10min/7446529.json) | assert / quick | xfail | 7.74104e-05 | 0.00920823 | 277.303 | — |
| [A4_10000_16qam_drift_10min](A4_10000_16qam_drift_10min/7446529.json) | assert / quick | xfail | 3.2317e-07 | 0.856097 | 25781.1 | — |
| [A4_10000_16qam_offset_-1](A4_10000_16qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_-3](A4_10000_16qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_-5](A4_10000_16qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_0](A4_10000_16qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_1](A4_10000_16qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_3](A4_10000_16qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_16qam_offset_5](A4_10000_16qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.3 | — |
| [A4_10000_64qam_-200ppm_10min](A4_10000_64qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0277778 | 0 | 0 | — |
| [A4_10000_64qam_-50ppm_10min](A4_10000_64qam_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.00160256 | 0.00028333 | 12.7986 | — |
| [A4_10000_64qam_200ppm_10min](A4_10000_64qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0729167 | 0 | 0 | — |
| [A4_10000_64qam_50ppm_10min](A4_10000_64qam_50ppm_10min/7446529.json) | assert / quick | xfail | 0.00327381 | 0.000141665 | 6.3993 | — |
| [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json) | assert / quick | xfail | 6.65378e-07 | 0.443525 | 20034.9 | — |
| [A4_10000_64qam_offset_-1](A4_10000_64qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.5 | — |
| [A4_10000_64qam_offset_-3](A4_10000_64qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.5 | — |
| [A4_10000_64qam_offset_-5](A4_10000_64qam_offset_-5/7446529.json) | assert / quick | xfail | 0.151042 | 0 | 0 | — |
| [A4_10000_64qam_offset_0](A4_10000_64qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.5 | — |
| [A4_10000_64qam_offset_1](A4_10000_64qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.5 | — |
| [A4_10000_64qam_offset_3](A4_10000_64qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.5 | — |
| [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446529.json) | assert / quick | xfail | 0.140625 | 0 | 0 | — |
| [A4_10000_qpsk_-200ppm_10min](A4_10000_qpsk_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.00427632 | 0.000552494 | 8.31908 | — |
| [A4_10000_qpsk_-50ppm_10min](A4_10000_qpsk_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.00171913 | 0.00286164 | 43.0886 | — |
| [A4_10000_qpsk_200ppm_10min](A4_10000_qpsk_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.000593933 | 0.00235164 | 35.4094 | — |
| [A4_10000_qpsk_50ppm_10min](A4_10000_qpsk_50ppm_10min/7446529.json) | assert / quick | xfail | 0.000190823 | 0.00977489 | 147.184 | — |
| [A4_10000_qpsk_drift_10min](A4_10000_qpsk_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_offset_-1](A4_10000_qpsk_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_-3](A4_10000_qpsk_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_-5](A4_10000_qpsk_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_0](A4_10000_qpsk_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_1](A4_10000_qpsk_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_3](A4_10000_qpsk_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_10000_qpsk_offset_5](A4_10000_qpsk_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.2 | — |
| [A4_24000_16qam_-200ppm_10min](A4_24000_16qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.001875 | 5.90277e-05 | 4.26647 | — |
| [A4_24000_16qam_-50ppm_10min](A4_24000_16qam_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.00142492 | 0.000413194 | 29.8653 | — |
| [A4_24000_16qam_200ppm_10min](A4_24000_16qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.00868056 | 1.18055e-05 | 0.853294 | — |
| [A4_24000_16qam_50ppm_10min](A4_24000_16qam_50ppm_10min/7446529.json) | assert / quick | xfail | 0.000196204 | 0.00380729 | 275.187 | — |
| [A4_24000_16qam_drift_10min](A4_24000_16qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72279 | — |
| [A4_24000_16qam_offset_-1](A4_24000_16qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_-3](A4_24000_16qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_-5](A4_24000_16qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_0](A4_24000_16qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_1](A4_24000_16qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_3](A4_24000_16qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_16qam_offset_5](A4_24000_16qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.5 | — |
| [A4_24000_64qam_-200ppm_10min](A4_24000_64qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.00347222 | 1.18055e-05 | 1.27994 | — |
| [A4_24000_64qam_-50ppm_10min](A4_24000_64qam_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.000173611 | 0.000165278 | 17.9192 | — |
| [A4_24000_64qam_200ppm_10min](A4_24000_64qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.09375 | 0 | 0 | — |
| [A4_24000_64qam_50ppm_10min](A4_24000_64qam_50ppm_10min/7446529.json) | assert / quick | xfail | 0.00308642 | 4.72222e-05 | 5.11977 | — |
| [A4_24000_64qam_drift_10min](A4_24000_64qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 9.22309e-08 | 0.999965 | 108415 | — |
| [A4_24000_64qam_offset_-1](A4_24000_64qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-3](A4_24000_64qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-5](A4_24000_64qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_0](A4_24000_64qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_1](A4_24000_64qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_3](A4_24000_64qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_5](A4_24000_64qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_qpsk_-200ppm_10min](A4_24000_qpsk_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.00148026 | 0.000259722 | 9.38624 | — |
| [A4_24000_qpsk_-50ppm_10min](A4_24000_qpsk_-50ppm_10min/7446529.json) | assert / quick | xfail | 0.000328563 | 0.00124548 | 45.0113 | — |
| [A4_24000_qpsk_200ppm_10min](A4_24000_qpsk_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0068523 | 0.00097986 | 35.4117 | — |
| [A4_24000_qpsk_50ppm_10min](A4_24000_qpsk_50ppm_10min/7446529.json) | assert / quick | xfail | 0.000202047 | 0.00407291 | 147.193 | — |
| [A4_24000_qpsk_drift_10min](A4_24000_qpsk_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_offset_-1](A4_24000_qpsk_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_-3](A4_24000_qpsk_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_-5](A4_24000_qpsk_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_0](A4_24000_qpsk_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_1](A4_24000_qpsk_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_3](A4_24000_qpsk_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |
| [A4_24000_qpsk_offset_5](A4_24000_qpsk_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.7 | — |

### Simulated channel A4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |
| A4_10000_16qam_drift_10min | 0.0 | 3.231697732330628e-07 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_drift_10min | 0.0 | 6.653784939024715e-07 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-5 | 0.0 | 0.15104166666666666 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_5 | 0.0 | 0.140625 | True | THRESHOLD_TBD |
| A4_10000_qpsk_drift_10min | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_qpsk_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_drift_10min | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_16qam_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_drift_10min | 0.0 | 9.223091078393323e-08 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_64qam_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_drift_10min | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_24000_qpsk_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |

## Simulated channel group A5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (108 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A6

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (36 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A7

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (156 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A8

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json) | assert / full | xfail | — | — | 122.4 | 34 |
| [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json) | assert / full | xfail | — | — | 122.4 | 34 |
| [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json) | assert / full | xfail | — | — | 3086.4 | 34 |

## Simulated channel group A9

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A9_dropout_2s](A9_dropout_2s/7446529.json) | assert / full | xfail | — | — | 0 | — |
| [A9_dropout_300s](A9_dropout_300s/7446529.json) | assert / full | xfail | — | — | 0 | — |
| [A9_dropout_30s](A9_dropout_30s/7446529.json) | assert / full | xfail | — | — | 0 | — |

## Simulated channel group B1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B1_10000_16qam_-20dB_10_100](B1_10000_16qam_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.00954861 | 0.0169492 | 495.659 | — |
| [B1_10000_16qam_-20dB_10_1000](B1_10000_16qam_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00954861 | 0.0169492 | 495.659 | — |
| [B1_10000_16qam_-20dB_1_100](B1_10000_16qam_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.0416667 | 0.0169492 | 495.659 | — |
| [B1_10000_16qam_-20dB_1_1000](B1_10000_16qam_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0416667 | 0.0169492 | 495.659 | — |
| [B1_10000_16qam_20dB_10_100](B1_10000_16qam_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 29154.8 | — |
| [B1_10000_16qam_20dB_10_1000](B1_10000_16qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 29154.8 | — |
| [B1_10000_16qam_20dB_1_100](B1_10000_16qam_20dB_1_100/7446529.json) | assert / quick | xfail | 0.0078125 | 0.0169492 | 495.659 | — |
| [B1_10000_16qam_20dB_1_1000](B1_10000_16qam_20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0078125 | 0.0169492 | 495.659 | — |
| [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.0225694 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_-20dB_10_1000](B1_10000_64qam_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.0225694 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.0434028 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_-20dB_1_1000](B1_10000_64qam_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0434028 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_20dB_10_100](B1_10000_64qam_20dB_10_100/7446529.json) | assert / quick | xfail | 0.00983796 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_20dB_10_1000](B1_10000_64qam_20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00983796 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_20dB_1_100](B1_10000_64qam_20dB_1_100/7446529.json) | assert / quick | xfail | 0.0190972 | 0.0169492 | 743.488 | — |
| [B1_10000_64qam_20dB_1_1000](B1_10000_64qam_20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0190972 | 0.0169492 | 743.488 | — |
| [B1_10000_qpsk_-20dB_10_100](B1_10000_qpsk_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.0667614 | 0.0169492 | 247.829 | — |
| [B1_10000_qpsk_-20dB_10_1000](B1_10000_qpsk_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.0667614 | 0.0169492 | 247.829 | — |
| [B1_10000_qpsk_-20dB_1_100](B1_10000_qpsk_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.0329861 | 0.0169492 | 247.829 | — |
| [B1_10000_qpsk_-20dB_1_1000](B1_10000_qpsk_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0329861 | 0.0169492 | 247.829 | — |
| [B1_10000_qpsk_20dB_10_100](B1_10000_qpsk_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 14577.4 | — |
| [B1_10000_qpsk_20dB_10_1000](B1_10000_qpsk_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 14577.4 | — |
| [B1_10000_qpsk_20dB_1_100](B1_10000_qpsk_20dB_1_100/7446529.json) | assert / quick | pass | 0 | 1 | 14577.4 | — |
| [B1_10000_qpsk_20dB_1_1000](B1_10000_qpsk_20dB_1_1000/7446529.json) | assert / quick | pass | 0 | 1 | 14577.4 | — |
| [B1_24000_16qam_-20dB_10_100](B1_24000_16qam_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.00218023 | 0.0353982 | 2525.23 | — |
| [B1_24000_16qam_-20dB_10_1000](B1_24000_16qam_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00218023 | 0.0353982 | 2525.23 | — |
| [B1_24000_16qam_-20dB_1_100](B1_24000_16qam_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.00799851 | 0.0353982 | 2525.23 | — |
| [B1_24000_16qam_-20dB_1_1000](B1_24000_16qam_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.00799851 | 0.0353982 | 2525.23 | — |
| [B1_24000_16qam_20dB_10_100](B1_24000_16qam_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 71300.1 | — |
| [B1_24000_16qam_20dB_10_1000](B1_24000_16qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 71300.1 | — |
| [B1_24000_16qam_20dB_1_100](B1_24000_16qam_20dB_1_100/7446529.json) | assert / quick | xfail | 0.00130208 | 0.0353982 | 2525.23 | — |
| [B1_24000_16qam_20dB_1_1000](B1_24000_16qam_20dB_1_1000/7446529.json) | assert / quick | xfail | 0.00130208 | 0.0353982 | 2525.23 | — |
| [B1_24000_64qam_-20dB_10_100](B1_24000_64qam_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.00111607 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_-20dB_10_1000](B1_24000_64qam_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00111607 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.00706845 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_-20dB_1_1000](B1_24000_64qam_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.00706845 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446529.json) | assert / quick | xfail | 0.00062004 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00062004 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_20dB_1_100](B1_24000_64qam_20dB_1_100/7446529.json) | assert / quick | xfail | 0.00533234 | 0.0353982 | 3787.84 | — |
| [B1_24000_64qam_20dB_1_1000](B1_24000_64qam_20dB_1_1000/7446529.json) | assert / quick | xfail | 0.00533234 | 0.0353982 | 3787.84 | — |
| [B1_24000_qpsk_-20dB_10_100](B1_24000_qpsk_-20dB_10_100/7446529.json) | assert / quick | xfail | 0.00985054 | 0.0389381 | 1388.87 | — |
| [B1_24000_qpsk_-20dB_10_1000](B1_24000_qpsk_-20dB_10_1000/7446529.json) | assert / quick | xfail | 0.00985054 | 0.0389381 | 1388.87 | — |
| [B1_24000_qpsk_-20dB_1_100](B1_24000_qpsk_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.0078125 | 0.0353982 | 1262.61 | — |
| [B1_24000_qpsk_-20dB_1_1000](B1_24000_qpsk_-20dB_1_1000/7446529.json) | assert / quick | xfail | 0.0078125 | 0.0353982 | 1262.61 | — |
| [B1_24000_qpsk_20dB_10_100](B1_24000_qpsk_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 35650.1 | — |
| [B1_24000_qpsk_20dB_10_1000](B1_24000_qpsk_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 35650.1 | — |
| [B1_24000_qpsk_20dB_1_100](B1_24000_qpsk_20dB_1_100/7446529.json) | assert / quick | pass | 0 | 1 | 35650.1 | — |
| [B1_24000_qpsk_20dB_1_1000](B1_24000_qpsk_20dB_1_1000/7446529.json) | assert / quick | pass | 1.38347e-05 | 0.99823 | 35586.9 | — |

### Simulated channel B1 affected-frame errors

Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.

| Case | Affected frames | Affected frame error rate |
| --- | --- | --- |
| B1_10000_16qam_-20dB_10_100 | 21 | 0.9523809523809523 |
| B1_10000_16qam_-20dB_10_1000 | 127 | 0.9921259842519685 |
| B1_10000_16qam_-20dB_1_100 | 20 | 0.95 |
| B1_10000_16qam_-20dB_1_1000 | 125 | 0.992 |
| B1_10000_16qam_20dB_10_100 | 21 | 0.0 |
| B1_10000_16qam_20dB_10_1000 | 127 | 0.0 |
| B1_10000_16qam_20dB_1_100 | 20 | 0.95 |
| B1_10000_16qam_20dB_1_1000 | 125 | 0.992 |
| B1_10000_64qam_-20dB_10_100 | 21 | 0.9523809523809523 |
| B1_10000_64qam_-20dB_10_1000 | 127 | 0.9921259842519685 |
| B1_10000_64qam_-20dB_1_100 | 20 | 0.95 |
| B1_10000_64qam_-20dB_1_1000 | 125 | 0.992 |
| B1_10000_64qam_20dB_10_100 | 21 | 0.9523809523809523 |
| B1_10000_64qam_20dB_10_1000 | 127 | 0.9921259842519685 |
| B1_10000_64qam_20dB_1_100 | 20 | 0.95 |
| B1_10000_64qam_20dB_1_1000 | 125 | 0.992 |
| B1_10000_qpsk_-20dB_10_100 | 21 | 0.9523809523809523 |
| B1_10000_qpsk_-20dB_10_1000 | 127 | 0.9921259842519685 |
| B1_10000_qpsk_-20dB_1_100 | 20 | 0.95 |
| B1_10000_qpsk_-20dB_1_1000 | 125 | 0.992 |
| B1_10000_qpsk_20dB_10_100 | 21 | 0.0 |
| B1_10000_qpsk_20dB_10_1000 | 127 | 0.0 |
| B1_10000_qpsk_20dB_1_100 | 20 | 0.0 |
| B1_10000_qpsk_20dB_1_1000 | 125 | 0.0 |
| B1_24000_16qam_-20dB_10_100 | 48 | 0.9791666666666666 |
| B1_24000_16qam_-20dB_10_1000 | 302 | 0.9966887417218543 |
| B1_24000_16qam_-20dB_1_100 | 46 | 0.9782608695652174 |
| B1_24000_16qam_-20dB_1_1000 | 299 | 0.9966555183946488 |
| B1_24000_16qam_20dB_10_100 | 48 | 0.0 |
| B1_24000_16qam_20dB_10_1000 | 302 | 0.0 |
| B1_24000_16qam_20dB_1_100 | 46 | 0.9782608695652174 |
| B1_24000_16qam_20dB_1_1000 | 299 | 0.9966555183946488 |
| B1_24000_64qam_-20dB_10_100 | 48 | 0.9791666666666666 |
| B1_24000_64qam_-20dB_10_1000 | 302 | 0.9966887417218543 |
| B1_24000_64qam_-20dB_1_100 | 46 | 0.9782608695652174 |
| B1_24000_64qam_-20dB_1_1000 | 299 | 0.9966555183946488 |
| B1_24000_64qam_20dB_10_100 | 48 | 0.9791666666666666 |
| B1_24000_64qam_20dB_10_1000 | 302 | 0.9966887417218543 |
| B1_24000_64qam_20dB_1_100 | 46 | 0.9782608695652174 |
| B1_24000_64qam_20dB_1_1000 | 299 | 0.9966555183946488 |
| B1_24000_qpsk_-20dB_10_100 | 48 | 0.9375 |
| B1_24000_qpsk_-20dB_10_1000 | 302 | 0.9900662251655629 |
| B1_24000_qpsk_-20dB_1_100 | 46 | 0.9782608695652174 |
| B1_24000_qpsk_-20dB_1_1000 | 299 | 0.9966555183946488 |
| B1_24000_qpsk_20dB_10_100 | 48 | 0.0 |
| B1_24000_qpsk_20dB_10_1000 | 302 | 0.0 |
| B1_24000_qpsk_20dB_1_100 | 46 | 0.0 |
| B1_24000_qpsk_20dB_1_1000 | 299 | 0.0033444816053511705 |

## Simulated channel group B2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B2_10000_16qam_hard_10pct](B2_10000_16qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_16qam_hard_1pct](B2_10000_16qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_16qam_hard_5pct](B2_10000_16qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_16qam_soft_10pct](B2_10000_16qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_16qam_soft_1pct](B2_10000_16qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_16qam_soft_5pct](B2_10000_16qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.8 | — |
| [B2_10000_64qam_hard_10pct](B2_10000_64qam_hard_10pct/7446529.json) | characterize / quick | characterized | 8.13802e-05 | 0.131356 | 5762.03 | — |
| [B2_10000_64qam_hard_1pct](B2_10000_64qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 43732.2 | — |
| [B2_10000_64qam_hard_5pct](B2_10000_64qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 0.135593 | 5947.91 | — |
| [B2_10000_64qam_soft_10pct](B2_10000_64qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0.00016276 | 0.127119 | 5576.16 | — |
| [B2_10000_64qam_soft_1pct](B2_10000_64qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 0.135593 | 5947.91 | — |
| [B2_10000_64qam_soft_5pct](B2_10000_64qam_soft_5pct/7446529.json) | characterize / quick | characterized | 8.13802e-05 | 0.131356 | 5762.03 | — |
| [B2_10000_qpsk_hard_10pct](B2_10000_qpsk_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_10000_qpsk_hard_1pct](B2_10000_qpsk_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_10000_qpsk_hard_5pct](B2_10000_qpsk_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_10000_qpsk_soft_10pct](B2_10000_qpsk_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_10000_qpsk_soft_1pct](B2_10000_qpsk_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_10000_qpsk_soft_5pct](B2_10000_qpsk_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.4 | — |
| [B2_24000_16qam_hard_10pct](B2_24000_16qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_16qam_hard_1pct](B2_24000_16qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_16qam_hard_5pct](B2_24000_16qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_16qam_soft_10pct](B2_24000_16qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_16qam_soft_1pct](B2_24000_16qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_16qam_soft_5pct](B2_24000_16qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71300.1 | — |
| [B2_24000_64qam_hard_10pct](B2_24000_64qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0.00016276 | 0.0530973 | 5681.76 | — |
| [B2_24000_64qam_hard_1pct](B2_24000_64qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 106950 | — |
| [B2_24000_64qam_hard_5pct](B2_24000_64qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 0.0566372 | 6060.54 | — |
| [B2_24000_64qam_soft_10pct](B2_24000_64qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0.00016276 | 0.0530973 | 5681.76 | — |
| [B2_24000_64qam_soft_1pct](B2_24000_64qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 0.0566372 | 6060.54 | — |
| [B2_24000_64qam_soft_5pct](B2_24000_64qam_soft_5pct/7446529.json) | characterize / quick | characterized | 8.13802e-05 | 0.0548673 | 5871.15 | — |
| [B2_24000_qpsk_hard_10pct](B2_24000_qpsk_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |
| [B2_24000_qpsk_hard_1pct](B2_24000_qpsk_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |
| [B2_24000_qpsk_hard_5pct](B2_24000_qpsk_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |
| [B2_24000_qpsk_soft_10pct](B2_24000_qpsk_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |
| [B2_24000_qpsk_soft_1pct](B2_24000_qpsk_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |
| [B2_24000_qpsk_soft_5pct](B2_24000_qpsk_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35650.1 | — |

## Simulated channel group B3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B3_10000_16qam_0.5ms](B3_10000_16qam_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 29120 | — |
| [B3_10000_16qam_1ms](B3_10000_16qam_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 29120 | — |
| [B3_10000_16qam_2ms](B3_10000_16qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 29120 | — |
| [B3_10000_64qam_0.5ms](B3_10000_64qam_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 43679.9 | — |
| [B3_10000_64qam_1ms](B3_10000_64qam_1ms/7446529.json) | characterize / quick | characterized | 0.00260417 | 0.0550847 | 2416.34 | — |
| [B3_10000_64qam_2ms](B3_10000_64qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 43679.9 | — |
| [B3_10000_qpsk_0.5ms](B3_10000_qpsk_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14560 | — |
| [B3_10000_qpsk_1ms](B3_10000_qpsk_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14560 | — |
| [B3_10000_qpsk_2ms](B3_10000_qpsk_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14560 | — |
| [B3_24000_16qam_0.5ms](B3_24000_16qam_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71211.4 | — |
| [B3_24000_16qam_1ms](B3_24000_16qam_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71211.4 | — |
| [B3_24000_16qam_2ms](B3_24000_16qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71211.4 | — |
| [B3_24000_64qam_0.5ms](B3_24000_64qam_0.5ms/7446529.json) | characterize / quick | characterized | 2.52832e-05 | 0.180531 | 19318 | — |
| [B3_24000_64qam_1ms](B3_24000_64qam_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 106817 | — |
| [B3_24000_64qam_2ms](B3_24000_64qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 106817 | — |
| [B3_24000_qpsk_0.5ms](B3_24000_qpsk_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35605.7 | — |
| [B3_24000_qpsk_1ms](B3_24000_qpsk_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35605.7 | — |
| [B3_24000_qpsk_2ms](B3_24000_qpsk_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35605.7 | — |

## Simulated channel group B4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B4_jitter](B4_jitter/7446529.json) | assert / quick | xfail | — | — | 2676 | 80.6692 |
| [B4_overrun](B4_overrun/7446529.json) | assert / quick | xfail | — | — | 600 | 80 |
| [B4_underrun](B4_underrun/7446529.json) | assert / quick | xfail | — | — | 2664 | 80 |

## Simulated channel group B5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json) | assert / quick | xfail | — | — | 3107.33 | 67 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json) | assert / quick | xfail | — | — | 3107.33 | 63 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json) | assert / quick | xfail | — | — | 3102.67 | 77 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | xfail | — | — | 3115.33 | 22 |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json) | assert / quick | xfail | — | — | 3115.33 | 21 |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json) | assert / quick | xfail | — | — | 3113.33 | 27 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

| Case | p50 ms | p99 ms | p99.9 ms | Max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 8.999300000001043 | 9.005923000000138 | 67.01544200000001 | 73.042787 | xfail |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 6.000282000000023 | 7.009423999999598 | 63.03296300000001 | 71.046885 | xfail |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 16.00005400000004 | 17.003220999999513 | 77.014084 | 79.983553 | xfail |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 4.000276000000191 | 4.019655000000455 | 22.037617 | 31.067269 | xfail |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | 3.0026610000000176 | 3.0324519999993527 | 21.058278 | 30.082904 | xfail |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | 7.000263000000118 | 7.014050999998744 | 27.023367 | 34.051046 | xfail |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.00028400000040562645 | 0.0022470000000000007 | 0.0024359999999390425 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.0013790000004121339 | 0.0030600000000546856 | 0.006079999999908381 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.00046000000075707703 | 0.0009629999997429195 | 0.005660000000240473 |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.9816519999999995 | 0.9986339999999982 | 1.021569 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.01580800000056115 | 0.031250000000149214 | 0.14175799999999183 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.0003080000006150385 | 0.002798999999999998 | 0.0028159999994059604 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.0014379999999647453 | 0.004142999999956487 | 0.010140999999741496 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.0004460000013750687 | 0.0009890000001178123 | 0.0023549999994543214 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.97653099999917 | 0.998220999999997 | 1.0121639999999998 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.02086899999986791 | 0.04040600000010386 | 0.14618300000000806 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.00024399999976054687 | 0.0017339999995868993 | 0.002476000000000001 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.0013340000002415309 | 0.002918999999934613 | 0.0060279999996026845 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.00047500000022182576 | 0.0010690000000757038 | 0.005785000000813056 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.9873580000006044 | 1.0566350000011937 | 1.093997999999985 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.009389999999775966 | 0.017566999999996114 | 0.18199700000000318 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.0003370000001279294 | 0.0019180000006002729 | 0.0021860000000000026 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.007809999999608408 | 0.016476000000764657 | 0.021601000000259774 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.00045600000042611555 | 0.0010709999997970954 | 0.0056160000010407884 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.953661999999994 | 0.9979459999999996 | 1.1179830000003221 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.03734499999996643 | 0.07823299999998312 | 0.31566599999999917 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.0004090000000900318 | 0.0020509999991702443 | 0.0020609999999999995 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.012895999999429364 | 0.018032999999917365 | 0.07298600000105182 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.0007520000000482696 | 0.0011130000014958341 | 0.0055500000009089945 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.9039799999994713 | 1.0243990000002867 | 2.7493550000006195 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.08139300000031824 | 0.11066200000087179 | 0.26462299999999855 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.0002939999994566733 | 0.0016840000007789513 | 0.001970000000000003 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.007354000000070471 | 0.014655000000196594 | 0.02049399999926038 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.00044700000056963063 | 0.0010629999991351724 | 0.005154000000118231 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.9681939999994782 | 0.9984220000000023 | 1.021315 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.023268000000076228 | 0.04599399999882792 | 0.2554999999999988 |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (2 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group C2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C2_10000_acquire_0dB](C2_10000_acquire_0dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.4 | — |
| [C2_10000_acquire_10dB](C2_10000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.4 | — |
| [C2_10000_acquire_3dB](C2_10000_acquire_3dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.4 | — |
| [C2_10000_acquire_6dB](C2_10000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.4 | — |
| [C2_10000_cw_preamble](C2_10000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.4 | — |
| [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json) | assert / quick | xfail | — | 0 | 0 | — |
| [C2_24000_acquire_10dB](C2_24000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35650.1 | — |
| [C2_24000_acquire_3dB](C2_24000_acquire_3dB/7446529.json) | assert / quick | xfail | — | 0 | 0 | — |
| [C2_24000_acquire_6dB](C2_24000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 2.76694e-05 | 0.99823 | 35586.9 | — |
| [C2_24000_cw_preamble](C2_24000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35650.1 | — |
| [C2_noise_10min](C2_noise_10min/7446529.json) | assert / quick | pass | — | — | 0 | — |

## Simulated channel group C3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C3_10000_sample_-1](C3_10000_sample_-1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 2676 | 80 |
| [C3_10000_sample_1](C3_10000_sample_1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 2676 | 80 |
| [C3_24000_sample_-1](C3_24000_sample_-1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 2680 | 34 |
| [C3_24000_sample_1](C3_24000_sample_1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 2680 | 34 |
| [C3_bit_delete](C3_bit_delete/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | — | — |
| [C3_bit_insert](C3_bit_insert/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | — | — |

## Simulated channel group C4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C4_10000_16qam_alternating](C4_10000_16qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29154.5 | — |
| [C4_10000_16qam_ones](C4_10000_16qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29154.5 | — |
| [C4_10000_16qam_random](C4_10000_16qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29154.5 | — |
| [C4_10000_16qam_repeating](C4_10000_16qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29154.5 | — |
| [C4_10000_16qam_zeros](C4_10000_16qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29154.5 | — |
| [C4_10000_64qam_alternating](C4_10000_64qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43731.7 | — |
| [C4_10000_64qam_ones](C4_10000_64qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43731.7 | — |
| [C4_10000_64qam_random](C4_10000_64qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43731.7 | — |
| [C4_10000_64qam_repeating](C4_10000_64qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43731.7 | — |
| [C4_10000_64qam_zeros](C4_10000_64qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43731.7 | — |
| [C4_10000_qpsk_alternating](C4_10000_qpsk_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.2 | — |
| [C4_10000_qpsk_ones](C4_10000_qpsk_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.2 | — |
| [C4_10000_qpsk_random](C4_10000_qpsk_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.2 | — |
| [C4_10000_qpsk_repeating](C4_10000_qpsk_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.2 | — |
| [C4_10000_qpsk_zeros](C4_10000_qpsk_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.2 | — |
| [C4_24000_16qam_alternating](C4_24000_16qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71300.4 | — |
| [C4_24000_16qam_ones](C4_24000_16qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71300.4 | — |
| [C4_24000_16qam_random](C4_24000_16qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71300.4 | — |
| [C4_24000_16qam_repeating](C4_24000_16qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71300.4 | — |
| [C4_24000_16qam_zeros](C4_24000_16qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71300.4 | — |
| [C4_24000_64qam_alternating](C4_24000_64qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106950 | — |
| [C4_24000_64qam_ones](C4_24000_64qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106950 | — |
| [C4_24000_64qam_random](C4_24000_64qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106950 | — |
| [C4_24000_64qam_repeating](C4_24000_64qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106950 | — |
| [C4_24000_64qam_zeros](C4_24000_64qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106950 | — |
| [C4_24000_qpsk_alternating](C4_24000_qpsk_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.9 | — |
| [C4_24000_qpsk_ones](C4_24000_qpsk_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.9 | — |
| [C4_24000_qpsk_random](C4_24000_qpsk_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.9 | — |
| [C4_24000_qpsk_repeating](C4_24000_qpsk_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.9 | — |
| [C4_24000_qpsk_zeros](C4_24000_qpsk_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.9 | — |
| [C4_empty_maximum_frames](C4_empty_maximum_frames/7446529.json) | assert / quick | unavailable | — | — | — | — |
| [C4_generated_messages](C4_generated_messages/7446529.json) | assert / quick | pass | — | — | — | — |

### Simulated channel C4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |
| C4_10000_16qam_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_16qam_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_16qam_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_16qam_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_16qam_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_64qam_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_64qam_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_64qam_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_64qam_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_64qam_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_qpsk_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_qpsk_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_qpsk_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_qpsk_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_10000_qpsk_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_16qam_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_16qam_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_16qam_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_16qam_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_16qam_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_64qam_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_64qam_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_64qam_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_64qam_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_64qam_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_qpsk_alternating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_qpsk_ones | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_qpsk_random | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_qpsk_repeating | 0.0 | 0.0 | True | THRESHOLD_TBD |
| C4_24000_qpsk_zeros | 0.0 | 0.0 | True | THRESHOLD_TBD |

## Simulated channel group C5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C5_mode_change](C5_mode_change/7446529.json) | assert / quick | unavailable | — | — | — | — |

## Simulated channel group D1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

### Simulated channel D1 source-to-sink overload

Offered wire bits are 1.5×, 3×, or 10× nominal steady payload capacity, including CRC, FEC and pilot overhead. Startup is included in measured delivery latency.

| Case | Created / delivered | Queue maximum | Superseded at framer | Delivered stale | p99.9 ms | First / last window p99.9 ms |
| --- | --- | --- | --- | --- | --- | --- |

## Simulated channel group D2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (6 declared cases) | — | not_run | — | — | — | — |

### Simulated channel D2 freshness comparison

| Target frame survival | Measured channel survival | Channel freshness p99.9 ms | Erasure freshness p99.9 ms |
| --- | --- | --- | --- |

## Simulated channel group D3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D3_auction_contention](D3_auction_contention/7446529.json) | assert / quick | xfail | — | — | — | 20 |
| [D3_auction_flood](D3_auction_flood/7446529.json) | assert / quick | xfail | — | — | — | 20 |

## Simulated channel group D4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D4_duplicate](D4_duplicate/7446529.json) | assert / quick | xfail | — | — | — | — |
| [D4_fec_failure](D4_fec_failure/7446529.json) | assert / quick | xfail | — | — | — | — |
| [D4_out_of_order](D4_out_of_order/7446529.json) | assert / quick | xfail | — | — | — | — |
| [D4_wrap](D4_wrap/7446529.json) | assert / quick | xfail | — | — | — | — |

## Simulated channel group D5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D5_dual_path](D5_dual_path/7446529.json) | assert / quick | unavailable | — | — | — | — |

## Simulated channel group D6

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json) | assert / full | xfail | — | — | — | — |
| [D6_key_rotation](D6_key_rotation/7446529.json) | assert / full | xfail | — | — | — | — |

## Simulated channel group E1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [E1_composed](E1_composed/7446529.json) | assert / quick | pass | — | — | — | — |
| [E1_null](E1_null/7446529.json) | assert / quick | pass | — | — | — | — |
| [E1_watterson](E1_watterson/7446529.json) | assert / quick | pass | — | — | — | — |

## Simulated channel group E2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (9 declared cases) | — | not_run | — | — | — | — |

### Simulated channel E2 local metric definitions

| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |
| --- | --- | --- | --- | --- |

## Simulated channel group E3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group E4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel — Defects found

- **xfail** — No sample-clock recovery is implemented; the requested clock mismatch loses frame boundaries.
  Cases: [A4_10000_16qam_-50ppm_10min](A4_10000_16qam_-50ppm_10min/7446529.json), [A4_10000_16qam_50ppm_10min](A4_10000_16qam_50ppm_10min/7446529.json), [A4_10000_64qam_-50ppm_10min](A4_10000_64qam_-50ppm_10min/7446529.json), [A4_10000_64qam_50ppm_10min](A4_10000_64qam_50ppm_10min/7446529.json), [A4_10000_qpsk_-50ppm_10min](A4_10000_qpsk_-50ppm_10min/7446529.json), [A4_10000_qpsk_50ppm_10min](A4_10000_qpsk_50ppm_10min/7446529.json), [A4_24000_16qam_-50ppm_10min](A4_24000_16qam_-50ppm_10min/7446529.json), [A4_24000_16qam_50ppm_10min](A4_24000_16qam_50ppm_10min/7446529.json), [A4_24000_64qam_-50ppm_10min](A4_24000_64qam_-50ppm_10min/7446529.json), [A4_24000_64qam_50ppm_10min](A4_24000_64qam_50ppm_10min/7446529.json), [A4_24000_qpsk_-50ppm_10min](A4_24000_qpsk_-50ppm_10min/7446529.json), [A4_24000_qpsk_50ppm_10min](A4_24000_qpsk_50ppm_10min/7446529.json).
- **xfail** — With carrier correction disabled, this residual-offset/drift trace loses synchronization.
  Cases: [A4_10000_16qam_drift_10min](A4_10000_16qam_drift_10min/7446529.json), [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json), [A4_10000_64qam_offset_-5](A4_10000_64qam_offset_-5/7446529.json), [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446529.json).
- **xfail** — Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
  Cases: [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json), [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json), [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json), [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json).
- **xfail** — With a co-channel interferer at -10 dB SIR, the message sink receives payloads outside the expected source stream; authenticated delivery is not implemented.
  Cases: [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json).
- **xfail** — The high_lat_moderate trace does not validate a header; dropout recovery and stale-message rejection cannot be established.
  Cases: [A9_dropout_2s](A9_dropout_2s/7446529.json), [A9_dropout_300s](A9_dropout_300s/7446529.json), [A9_dropout_30s](A9_dropout_30s/7446529.json).
- **xfail** — The receiver loses synchronization through this specified 20 dB AGC excursion.
  Cases: [B1_10000_16qam_-20dB_10_100](B1_10000_16qam_-20dB_10_100/7446529.json), [B1_10000_16qam_-20dB_10_1000](B1_10000_16qam_-20dB_10_1000/7446529.json), [B1_10000_16qam_-20dB_1_100](B1_10000_16qam_-20dB_1_100/7446529.json), [B1_10000_16qam_-20dB_1_1000](B1_10000_16qam_-20dB_1_1000/7446529.json), [B1_10000_16qam_20dB_1_100](B1_10000_16qam_20dB_1_100/7446529.json), [B1_10000_16qam_20dB_1_1000](B1_10000_16qam_20dB_1_1000/7446529.json), [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446529.json), [B1_10000_64qam_-20dB_10_1000](B1_10000_64qam_-20dB_10_1000/7446529.json), [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446529.json), [B1_10000_64qam_-20dB_1_1000](B1_10000_64qam_-20dB_1_1000/7446529.json), [B1_10000_64qam_20dB_10_100](B1_10000_64qam_20dB_10_100/7446529.json), [B1_10000_64qam_20dB_10_1000](B1_10000_64qam_20dB_10_1000/7446529.json), [B1_10000_64qam_20dB_1_100](B1_10000_64qam_20dB_1_100/7446529.json), [B1_10000_64qam_20dB_1_1000](B1_10000_64qam_20dB_1_1000/7446529.json), [B1_10000_qpsk_-20dB_10_100](B1_10000_qpsk_-20dB_10_100/7446529.json), [B1_10000_qpsk_-20dB_10_1000](B1_10000_qpsk_-20dB_10_1000/7446529.json), [B1_10000_qpsk_-20dB_1_100](B1_10000_qpsk_-20dB_1_100/7446529.json), [B1_10000_qpsk_-20dB_1_1000](B1_10000_qpsk_-20dB_1_1000/7446529.json), [B1_24000_16qam_-20dB_10_100](B1_24000_16qam_-20dB_10_100/7446529.json), [B1_24000_16qam_-20dB_10_1000](B1_24000_16qam_-20dB_10_1000/7446529.json), [B1_24000_16qam_-20dB_1_100](B1_24000_16qam_-20dB_1_100/7446529.json), [B1_24000_16qam_-20dB_1_1000](B1_24000_16qam_-20dB_1_1000/7446529.json), [B1_24000_16qam_20dB_1_100](B1_24000_16qam_20dB_1_100/7446529.json), [B1_24000_16qam_20dB_1_1000](B1_24000_16qam_20dB_1_1000/7446529.json), [B1_24000_64qam_-20dB_10_100](B1_24000_64qam_-20dB_10_100/7446529.json), [B1_24000_64qam_-20dB_10_1000](B1_24000_64qam_-20dB_10_1000/7446529.json), [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json), [B1_24000_64qam_-20dB_1_1000](B1_24000_64qam_-20dB_1_1000/7446529.json), [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446529.json), [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446529.json), [B1_24000_64qam_20dB_1_100](B1_24000_64qam_20dB_1_100/7446529.json), [B1_24000_64qam_20dB_1_1000](B1_24000_64qam_20dB_1_1000/7446529.json), [B1_24000_qpsk_-20dB_10_100](B1_24000_qpsk_-20dB_10_100/7446529.json), [B1_24000_qpsk_-20dB_10_1000](B1_24000_qpsk_-20dB_10_1000/7446529.json), [B1_24000_qpsk_-20dB_1_100](B1_24000_qpsk_-20dB_1_100/7446529.json), [B1_24000_qpsk_-20dB_1_1000](B1_24000_qpsk_-20dB_1_1000/7446529.json).
- **xfail** — The sample-array interface has no block deadline or explicit gap event for injected audio delivery jitter.
  Cases: [B4_jitter](B4_jitter/7446529.json).
- **xfail** — Raw IQ/audio interface has no explicit underrun/overrun gap report.
  Cases: [B4_overrun](B4_overrun/7446529.json), [B4_underrun](B4_underrun/7446529.json).
- **xfail** — Source-to-sink latency including startup and audio buffering exceeds the 2.1 ms allowance.
  Cases: [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json), [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json), [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json), [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json), [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json), [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json).
- **xfail** — At the requested low SNR, the receiver detects the preamble but loses lock without validating a header.
  Cases: [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json), [C2_24000_acquire_3dB](C2_24000_acquire_3dB/7446529.json).
- **xfail** — The auction does not preempt an already queued winner when a higher-priority bid becomes ready.
  Cases: [D3_auction_contention](D3_auction_contention/7446529.json), [D3_auction_flood](D3_auction_flood/7446529.json).
- **xfail** — A sustained high-bid flood starves offered lower-bid instruments; the auction has no starvation prevention.
  Cases: [D3_auction_flood](D3_auction_flood/7446529.json).
- **xfail** — Receiver delivered a repeated valid message again.
  Cases: [D4_duplicate](D4_duplicate/7446529.json).
- **xfail** — Uncertain/FEC-failed data is discarded without a downstream gap event.
  Cases: [D4_fec_failure](D4_fec_failure/7446529.json).
- **xfail** — Stale messages were delivered, or no delivery established this property.
  Cases: [D4_out_of_order](D4_out_of_order/7446529.json).
- **xfail** — The message envelope has no sequence number or wraparound semantics.
  Cases: [D4_wrap](D4_wrap/7446529.json).
- **xfail** — Restarting the production AES-CTR generator with the unchanged key and default counter repeats its keystream.
  Cases: [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json).
- **xfail** — The production deframer delivers captured valid framed messages again; it has no message-level replay suppression.
  Cases: [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json).
- **xfail** — No coordinated mid-stream key-rotation and old-key retirement contract is exposed.
  Cases: [D6_key_rotation](D6_key_rotation/7446529.json).

## Simulated channel — Open thresholds

| ID | Status | Proposed value / approach | Reason |
| --- | --- | --- | --- |
| A4.ber_delta | THRESHOLD_TBD | 0 absolute excess BER in the noise-free regression; select a confidence interval for noisy runs | No radio residual-offset budget or BER margin is specified. |
| C2.acquisition_seconds | THRESHOLD_TBD | one complete preamble/training/header plus one audio block | The configured startup lengths give a measurable lower bound; approval needed. |
| C3.recovery_frames | THRESHOLD_TBD | 2 frames after a new valid epoch preamble | The current stream needs an epoch preamble to reacquire; a deadline without one is undefined. |
| C4.pattern_ber_margin | THRESHOLD_TBD | a paired confidence interval, with its significance level selected by Adam | Equal finite-sample BER is not a statistical scrambler test. |
| D1.newest_latency_ms | THRESHOLD_TBD | one frame duration + 2.1 ms, as proposed in the brief | Needs agreement on whether serialization, FEC lookahead and startup are included. |
| D2.freshness_agreement_ms | THRESHOLD_TBD | compare paired freshness distributions; select a quantile margin | Equal survival fractions do not imply equal burst structure. |
| D2.target_survival_margin | THRESHOLD_TBD | select a confidence interval for channel calibration; direct erasures round to the nearest whole frame | A finite SNR grid cannot guarantee exactly 30%, 50%, or 80% channel survival. |
| D3.instrument_delay_ms | THRESHOLD_TBD | one frame duration + 2.1 ms | Strict bid priority and starvation freedom can conflict under sustained overload. |
| D6.rotation_loss_frames | THRESHOLD_TBD | one epoch startup plus the in-flight frame | There is no coordinated rotation protocol to measure yet. |
| E3.memory_growth_bytes | THRESHOLD_TBD | zero steady growth after warmup; choose an allocator/RSS allowance | Host RSS varies and includes harness allocations. |
| E3.queue_depth | THRESHOLD_TBD | configured ring capacity plus one pending auction bid | Must distinguish queue capacity from newest-message freshness. |
| E3.latency_change | THRESHOLD_TBD | a paired percentile tolerance chosen from baseline variability | Exact equality across different fading realizations is not a usable acceptance rule. |

## Simulated channel coverage and limitations

- Production modem, framing, scheduler and crypto behavior was not changed for this test brief.
- Carrier correction is disabled through the existing switch; this also disables its coupled phase PLL. The adaptive equalizer remains enabled.
- 24 kHz use of the F.1487 model is an extrapolation beyond that recommendation's approximately 12 kHz scope.
- A1 uses declared 10-second screening traces. The requested grids and long 600-second quick cases are not reduced to meet a runtime budget.
- BER excludes erased/unobserved bits: inspect bit observation fraction and frame survival alongside it. No acquisition is never reported as zero BER.
- Symbol-probe goodput counts correct RF-frame bits; message-probe goodput counts application bytes. They are labeled separately in JSON.
- Canonical sample-clock latency includes startup and audio buffering. B5's separate paced host observations include real CPU/OS scheduling through auction, framing, FEC, crypto and modem. Physical audio devices and network sockets are outside this simulated loopback.
- Usable-time is an explicitly labeled local one-second delivery-window proxy. Exact STAC comparability is unavailable pending audit definitions/standby instrumentation.
- Conditional unsupported features, missing recordings, unrun soak cases, and open thresholds are never counted as passes.
- D6 cannot count AEAD authentication failures at A1 error rates because production exposes AES-CTR/CRC only. Its replay check exercises captured framed messages at the deframer; it does not claim an encrypted RF replay audit with wall-clock timestamp validation.
- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.

See [TESTING.md](../TESTING.md) and [source audit/questions](../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 8 / 8 | 7.697 | 1800 | yes |
| quick / complete tier | 243 / 243 | 206.333 | 120 | **NO** |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
