# Goblin Cannon simulated channel report

All results use simulated channels. No transmission or RF equipment measurement is represented.

## Simulated channel execution summary

| Status | Cases |
| --- | ---: |
| THRESHOLD_TBD | 48 |
| characterized | 12 |
| pass | 60 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 0 | 0 | 0 | 0 |
| A3 | 0 | 0 | 0 | 0 |
| A4 | 72 | 0 | 48 | 0 |
| A5 | 0 | 0 | 0 | 0 |
| A6 | 0 | 0 | 0 | 0 |
| A7 | 0 | 0 | 0 | 0 |
| A8 | 0 | 0 | 0 | 0 |
| A9 | 0 | 0 | 0 | 0 |
| B1 | 48 | 0 | 0 | 0 |
| B2 | 0 | 0 | 0 | 0 |
| B3 | 0 | 0 | 0 | 0 |
| B4 | 0 | 0 | 0 | 0 |
| B5 | 0 | 0 | 0 | 0 |
| C1 | 0 | 0 | 0 | 0 |
| C2 | 0 | 0 | 0 | 0 |
| C3 | 0 | 0 | 0 | 0 |
| C4 | 0 | 0 | 0 | 0 |
| C5 | 0 | 0 | 0 | 0 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 0 | 0 | 0 | 0 |
| D4 | 0 | 0 | 0 | 0 |
| D5 | 0 | 0 | 0 | 0 |
| D6 | 0 | 0 | 0 | 0 |
| E1 | 0 | 0 | 0 | 0 |
| E2 | 0 | 0 | 0 | 0 |
| E3 | 0 | 0 | 0 | 0 |
| E4 | 0 | 0 | 0 | 0 |

## Simulated channel principal findings

- 24 kHz clean controls: 0/3 produced no valid header. Header validity and erased frames are retained alongside conditional BER.
- Remaining known failures are executable assertions marked `xfail`. Fixed assertions are removed from the expected-failure registry after reviewing their measurements.
- Runtime budget findings, measured host latency, unsupported capabilities and statistical-duration limits are reported explicitly below.

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (90 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (18 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A4_10000_16qam_-200ppm_10min](A4_10000_16qam_-200ppm_10min/7446530.json) | characterize / quick | characterized | 1.16211e-06 | 0.999986 | 30113.9 | — |
| [A4_10000_16qam_-50ppm_10min](A4_10000_16qam_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_200ppm_10min](A4_10000_16qam_200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_50ppm_10min](A4_10000_16qam_50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_drift_10min](A4_10000_16qam_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_offset_-1](A4_10000_16qam_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_-3](A4_10000_16qam_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_-5](A4_10000_16qam_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_0](A4_10000_16qam_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_1](A4_10000_16qam_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_3](A4_10000_16qam_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_5](A4_10000_16qam_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_64qam_-200ppm_10min](A4_10000_64qam_-200ppm_10min/7446530.json) | characterize / quick | characterized | 0.0447917 | 0 | 0 | — |
| [A4_10000_64qam_-50ppm_10min](A4_10000_64qam_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 45171.5 | — |
| [A4_10000_64qam_200ppm_10min](A4_10000_64qam_200ppm_10min/7446530.json) | characterize / quick | characterized | 0.0546875 | 0 | 0 | — |
| [A4_10000_64qam_50ppm_10min](A4_10000_64qam_50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 45171.5 | — |
| [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 1.06988e-06 | 0.999844 | 45164.5 | — |
| [A4_10000_64qam_offset_-1](A4_10000_64qam_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_-3](A4_10000_64qam_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_-5](A4_10000_64qam_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_0](A4_10000_64qam_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_1](A4_10000_64qam_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_3](A4_10000_64qam_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_qpsk_-200ppm_10min](A4_10000_qpsk_-200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_-50ppm_10min](A4_10000_qpsk_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_200ppm_10min](A4_10000_qpsk_200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_50ppm_10min](A4_10000_qpsk_50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_drift_10min](A4_10000_qpsk_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_offset_-1](A4_10000_qpsk_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_-3](A4_10000_qpsk_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_-5](A4_10000_qpsk_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_0](A4_10000_qpsk_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_1](A4_10000_qpsk_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_3](A4_10000_qpsk_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_5](A4_10000_qpsk_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_24000_16qam_-200ppm_10min](A4_24000_16qam_-200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 72279 | — |
| [A4_24000_16qam_-50ppm_10min](A4_24000_16qam_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 72279 | — |
| [A4_24000_16qam_200ppm_10min](A4_24000_16qam_200ppm_10min/7446530.json) | characterize / quick | characterized | 1.15289e-07 | 0.999994 | 72278.6 | — |
| [A4_24000_16qam_50ppm_10min](A4_24000_16qam_50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 72279 | — |
| [A4_24000_16qam_drift_10min](A4_24000_16qam_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72279 | — |
| [A4_24000_16qam_offset_-1](A4_24000_16qam_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_-3](A4_24000_16qam_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_-5](A4_24000_16qam_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_0](A4_24000_16qam_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_1](A4_24000_16qam_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_3](A4_24000_16qam_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_5](A4_24000_16qam_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_64qam_-200ppm_10min](A4_24000_64qam_-200ppm_10min/7446530.json) | characterize / quick | characterized | 0.0256944 | 2.36111e-05 | 2.55988 | — |
| [A4_24000_64qam_-50ppm_10min](A4_24000_64qam_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 108419 | — |
| [A4_24000_64qam_200ppm_10min](A4_24000_64qam_200ppm_10min/7446530.json) | characterize / quick | characterized | 0.0598958 | 0 | 0 | — |
| [A4_24000_64qam_50ppm_10min](A4_24000_64qam_50ppm_10min/7446530.json) | assert / quick | pass | 3.84295e-07 | 0.999982 | 108417 | — |
| [A4_24000_64qam_drift_10min](A4_24000_64qam_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108419 | — |
| [A4_24000_64qam_offset_-1](A4_24000_64qam_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-3](A4_24000_64qam_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-5](A4_24000_64qam_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_0](A4_24000_64qam_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_1](A4_24000_64qam_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_3](A4_24000_64qam_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_5](A4_24000_64qam_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_qpsk_-200ppm_10min](A4_24000_qpsk_-200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_-50ppm_10min](A4_24000_qpsk_-50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_200ppm_10min](A4_24000_qpsk_200ppm_10min/7446530.json) | characterize / quick | characterized | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_50ppm_10min](A4_24000_qpsk_50ppm_10min/7446530.json) | assert / quick | pass | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_drift_10min](A4_24000_qpsk_drift_10min/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_offset_-1](A4_24000_qpsk_offset_-1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_-3](A4_24000_qpsk_offset_-3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_-5](A4_24000_qpsk_offset_-5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_0](A4_24000_qpsk_offset_0/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_1](A4_24000_qpsk_offset_1/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_3](A4_24000_qpsk_offset_3/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_5](A4_24000_qpsk_offset_5/7446530.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |

### Simulated channel A4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |
| A4_10000_16qam_drift_10min | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_16qam_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_drift_10min | 0.0 | 1.0698784861529316e-06 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_0 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_5 | 0.0 | 0.0 | True | THRESHOLD_TBD |
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
| A4_24000_64qam_drift_10min | 0.0 | 0.0 | True | THRESHOLD_TBD |
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
| Not run (3 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A9

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group B1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B1_10000_16qam_-20dB_10_100](B1_10000_16qam_-20dB_10_100/7446530.json) | assert / quick | pass | 0.000813521 | 0.991525 | 28906.4 | — |
| [B1_10000_16qam_-20dB_10_1000](B1_10000_16qam_-20dB_10_1000/7446530.json) | assert / quick | pass | 0.000813521 | 0.991525 | 28906.4 | — |
| [B1_10000_16qam_-20dB_1_100](B1_10000_16qam_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000564484 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_-20dB_1_1000](B1_10000_16qam_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000564484 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_10_100](B1_10000_16qam_20dB_10_100/7446530.json) | assert / quick | pass | 8.30124e-05 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_10_1000](B1_10000_16qam_20dB_10_1000/7446530.json) | assert / quick | pass | 8.30124e-05 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_1_100](B1_10000_16qam_20dB_1_100/7446530.json) | assert / quick | pass | 0.00019923 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_1_1000](B1_10000_16qam_20dB_1_1000/7446530.json) | assert / quick | pass | 0.00019923 | 0.995763 | 29030.3 | — |
| [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446530.json) | assert / quick | pass | 0.00131713 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_-20dB_10_1000](B1_10000_64qam_-20dB_10_1000/7446530.json) | assert / quick | pass | 0.00131713 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000697304 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_-20dB_1_1000](B1_10000_64qam_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000697304 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_20dB_10_100](B1_10000_64qam_20dB_10_100/7446530.json) | assert / quick | pass | 0.000697304 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_20dB_10_1000](B1_10000_64qam_20dB_10_1000/7446530.json) | assert / quick | pass | 0.000697304 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_20dB_1_100](B1_10000_64qam_20dB_1_100/7446530.json) | assert / quick | pass | 0.000376323 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_20dB_1_1000](B1_10000_64qam_20dB_1_1000/7446530.json) | assert / quick | pass | 0.000376323 | 0.995763 | 43545.5 | — |
| [B1_10000_qpsk_-20dB_10_100](B1_10000_qpsk_-20dB_10_100/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_-20dB_10_1000](B1_10000_qpsk_-20dB_10_1000/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_-20dB_1_100](B1_10000_qpsk_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000996148 | 0.995763 | 14515.2 | — |
| [B1_10000_qpsk_-20dB_1_1000](B1_10000_qpsk_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000996148 | 0.995763 | 14515.2 | — |
| [B1_10000_qpsk_20dB_10_100](B1_10000_qpsk_20dB_10_100/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_10_1000](B1_10000_qpsk_20dB_10_1000/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_1_100](B1_10000_qpsk_20dB_1_100/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_1_1000](B1_10000_qpsk_20dB_1_1000/7446530.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_24000_16qam_-20dB_10_100](B1_24000_16qam_-20dB_10_100/7446530.json) | assert / quick | pass | 0.000207521 | 0.99469 | 70919.9 | — |
| [B1_24000_16qam_-20dB_10_1000](B1_24000_16qam_-20dB_10_1000/7446530.json) | assert / quick | pass | 0.000207521 | 0.99469 | 70919.9 | — |
| [B1_24000_16qam_-20dB_1_100](B1_24000_16qam_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000242107 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_-20dB_1_1000](B1_24000_16qam_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000242107 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_10_100](B1_24000_16qam_20dB_10_100/7446530.json) | assert / quick | pass | 1.38347e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_10_1000](B1_24000_16qam_20dB_10_1000/7446530.json) | assert / quick | pass | 1.38347e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_1_100](B1_24000_16qam_20dB_1_100/7446530.json) | assert / quick | pass | 4.15041e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_1_1000](B1_24000_16qam_20dB_1_1000/7446530.json) | assert / quick | pass | 4.15041e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_64qam_-20dB_10_100](B1_24000_64qam_-20dB_10_100/7446530.json) | assert / quick | pass | 0.000622562 | 0.99292 | 106190 | — |
| [B1_24000_64qam_-20dB_10_1000](B1_24000_64qam_-20dB_10_1000/7446530.json) | assert / quick | pass | 0.000622562 | 0.99292 | 106190 | — |
| [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000249025 | 0.99823 | 106759 | — |
| [B1_24000_64qam_-20dB_1_1000](B1_24000_64qam_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000249025 | 0.99823 | 106759 | — |
| [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446530.json) | assert / quick | pass | 0.000336644 | 0.99292 | 106190 | — |
| [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446530.json) | assert / quick | pass | 0.000336644 | 0.99292 | 106190 | — |
| [B1_24000_64qam_20dB_1_100](B1_24000_64qam_20dB_1_100/7446530.json) | assert / quick | pass | 0.000216744 | 0.99823 | 106759 | — |
| [B1_24000_64qam_20dB_1_1000](B1_24000_64qam_20dB_1_1000/7446530.json) | assert / quick | pass | 0.000216744 | 0.99823 | 106759 | — |
| [B1_24000_qpsk_-20dB_10_100](B1_24000_qpsk_-20dB_10_100/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_-20dB_10_1000](B1_24000_qpsk_-20dB_10_1000/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_-20dB_1_100](B1_24000_qpsk_-20dB_1_100/7446530.json) | assert / quick | pass | 0.000359702 | 0.99823 | 35586.2 | — |
| [B1_24000_qpsk_-20dB_1_1000](B1_24000_qpsk_-20dB_1_1000/7446530.json) | assert / quick | pass | 0.000359702 | 0.99823 | 35586.2 | — |
| [B1_24000_qpsk_20dB_10_100](B1_24000_qpsk_20dB_10_100/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_10_1000](B1_24000_qpsk_20dB_10_1000/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_1_100](B1_24000_qpsk_20dB_1_100/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_1_1000](B1_24000_qpsk_20dB_1_1000/7446530.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |

### Simulated channel B1 affected-frame errors

Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.

| Case | Affected frames | Affected frame error rate |
| --- | --- | --- |
| B1_10000_16qam_-20dB_10_100 | 21 | 0.09523809523809523 |
| B1_10000_16qam_-20dB_10_1000 | 127 | 0.015748031496062992 |
| B1_10000_16qam_-20dB_1_100 | 20 | 0.05 |
| B1_10000_16qam_-20dB_1_1000 | 125 | 0.008 |
| B1_10000_16qam_20dB_10_100 | 21 | 0.047619047619047616 |
| B1_10000_16qam_20dB_10_1000 | 127 | 0.007874015748031496 |
| B1_10000_16qam_20dB_1_100 | 20 | 0.05 |
| B1_10000_16qam_20dB_1_1000 | 125 | 0.008 |
| B1_10000_64qam_-20dB_10_100 | 21 | 0.09523809523809523 |
| B1_10000_64qam_-20dB_10_1000 | 127 | 0.015748031496062992 |
| B1_10000_64qam_-20dB_1_100 | 20 | 0.05 |
| B1_10000_64qam_-20dB_1_1000 | 125 | 0.008 |
| B1_10000_64qam_20dB_10_100 | 21 | 0.09523809523809523 |
| B1_10000_64qam_20dB_10_1000 | 127 | 0.015748031496062992 |
| B1_10000_64qam_20dB_1_100 | 20 | 0.05 |
| B1_10000_64qam_20dB_1_1000 | 125 | 0.008 |
| B1_10000_qpsk_-20dB_10_100 | 21 | 0.0 |
| B1_10000_qpsk_-20dB_10_1000 | 127 | 0.0 |
| B1_10000_qpsk_-20dB_1_100 | 20 | 0.05 |
| B1_10000_qpsk_-20dB_1_1000 | 125 | 0.008 |
| B1_10000_qpsk_20dB_10_100 | 21 | 0.0 |
| B1_10000_qpsk_20dB_10_1000 | 127 | 0.0 |
| B1_10000_qpsk_20dB_1_100 | 20 | 0.0 |
| B1_10000_qpsk_20dB_1_1000 | 125 | 0.0 |
| B1_24000_16qam_-20dB_10_100 | 48 | 0.0625 |
| B1_24000_16qam_-20dB_10_1000 | 302 | 0.009933774834437087 |
| B1_24000_16qam_-20dB_1_100 | 46 | 0.021739130434782608 |
| B1_24000_16qam_-20dB_1_1000 | 299 | 0.0033444816053511705 |
| B1_24000_16qam_20dB_10_100 | 48 | 0.020833333333333332 |
| B1_24000_16qam_20dB_10_1000 | 302 | 0.0033112582781456954 |
| B1_24000_16qam_20dB_1_100 | 46 | 0.021739130434782608 |
| B1_24000_16qam_20dB_1_1000 | 299 | 0.0033444816053511705 |
| B1_24000_64qam_-20dB_10_100 | 48 | 0.08333333333333333 |
| B1_24000_64qam_-20dB_10_1000 | 302 | 0.013245033112582781 |
| B1_24000_64qam_-20dB_1_100 | 46 | 0.021739130434782608 |
| B1_24000_64qam_-20dB_1_1000 | 299 | 0.0033444816053511705 |
| B1_24000_64qam_20dB_10_100 | 48 | 0.08333333333333333 |
| B1_24000_64qam_20dB_10_1000 | 302 | 0.013245033112582781 |
| B1_24000_64qam_20dB_1_100 | 46 | 0.021739130434782608 |
| B1_24000_64qam_20dB_1_1000 | 299 | 0.0033444816053511705 |
| B1_24000_qpsk_-20dB_10_100 | 48 | 0.0 |
| B1_24000_qpsk_-20dB_10_1000 | 302 | 0.0 |
| B1_24000_qpsk_-20dB_1_100 | 46 | 0.021739130434782608 |
| B1_24000_qpsk_-20dB_1_1000 | 299 | 0.0033444816053511705 |
| B1_24000_qpsk_20dB_10_100 | 48 | 0.0 |
| B1_24000_qpsk_20dB_10_1000 | 302 | 0.0 |
| B1_24000_qpsk_20dB_1_100 | 46 | 0.0 |
| B1_24000_qpsk_20dB_1_1000 | 299 | 0.0 |

## Simulated channel group B2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (36 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group B3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (18 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group B4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group B5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (12 declared cases) | — | not_run | — | — | — | — |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (2 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group C2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (11 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group C3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (6 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group C4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (32 declared cases) | — | not_run | — | — | — | — |

### Simulated channel C4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |

## Simulated channel group C5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group D1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

### Simulated channel D1 source-to-sink overload

Offered wire bits are 1.5×, 3×, or 10× nominal steady payload capacity, including sequence metadata, CRC, FEC and pilot overhead. Startup is included in measured delivery latency.

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
| Not run (2 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group D4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (4 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group D5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group D6

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (2 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group E1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

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

No observed assertion failures in the selected cases.

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

- These follow-up tests include Adam-authorized fixes to clock/gain/equalizer tracking, transmit buffering, auction freshness and receiver sequencing/gaps. Each record identifies its tested source snapshot; earlier audit records remain historical.
- Carrier correction is disabled. The adaptive equalizer includes a first-order common phase coefficient; it has no frequency estimate or frequency accumulator. Clock recovery adjusts sample instants only.
- 24 kHz use of the F.1487 model is an extrapolation beyond that recommendation's approximately 12 kHz scope.
- A1 uses declared 10-second screening traces. The requested grids and long 600-second quick cases are not reduced to meet a runtime budget.
- BER excludes erased/unobserved bits: inspect bit observation fraction and frame survival alongside it. No acquisition is never reported as zero BER.
- Symbol-probe goodput counts correct RF-frame bits; message-probe goodput counts application bytes. They are labeled separately in JSON.
- Total source-to-sink latency includes startup and audio buffering. B5 applies 2.1 ms to per-message added processing/buffering above a matched one-sample intrinsic reference. Its separate paced host observations include CPU/OS scheduling. Transmission and modem residence estimates are also reported. Physical audio devices and network sockets are outside this simulated loopback.
- Usable-time is an explicitly labeled local one-second delivery-window proxy. Exact STAC comparability is unavailable pending audit definitions/standby instrumentation.
- Conditional unsupported features, missing recordings, unrun soak cases, and open thresholds are never counted as passes.
- D6 cannot count AEAD authentication failures at A1 error rates because production exposes AES-CTR/CRC only. Its replay check exercises captured framed messages at the deframer; it does not claim an encrypted RF replay audit with wall-clock timestamp validation.
- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.

See [TESTING.md](../../../TESTING.md) and [source audit/questions](../../../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| quick / selected rerun | 120 / 120 | 50.841 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
