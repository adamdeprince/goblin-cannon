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
| pass | 44 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 0 | 0 | 0 | 0 |
| A3 | 0 | 0 | 0 | 0 |
| A4 | 0 | 0 | 0 | 0 |
| A5 | 0 | 0 | 0 | 0 |
| A6 | 0 | 0 | 0 | 0 |
| A7 | 0 | 0 | 0 | 0 |
| A8 | 0 | 0 | 0 | 0 |
| A9 | 0 | 0 | 0 | 0 |
| B1 | 0 | 0 | 0 | 0 |
| B2 | 0 | 0 | 0 | 0 |
| B3 | 0 | 0 | 0 | 0 |
| B4 | 0 | 0 | 0 | 0 |
| B5 | 44 | 0 | 0 | 0 |
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

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (246 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (18 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (72 declared cases) | — | not_run | — | — | — | — |

### Simulated channel A4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |

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
| Not run (48 declared cases) | — | not_run | — | — | — | — |

### Simulated channel B1 affected-frame errors

Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.

| Case | Affected frames | Affected frame error rate |
| --- | --- | --- |

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
| [B5_psk_10000_16qam_reference_long_null](B5_psk_10000_16qam_reference_long_null/7446529.json) | assert / full | pass | — | — | 2187.33 | 80 |
| [B5_psk_10000_16qam_reference_short_null](B5_psk_10000_16qam_reference_short_null/7446529.json) | assert / quick | pass | — | — | 2576.67 | 51 |
| [B5_psk_10000_64qam_reference_long_null](B5_psk_10000_64qam_reference_long_null/7446529.json) | assert / full | pass | — | — | 2187.33 | 76 |
| [B5_psk_10000_64qam_reference_short_null](B5_psk_10000_64qam_reference_short_null/7446529.json) | assert / quick | pass | — | — | 2579.33 | 47 |
| [B5_psk_10000_8psk_bpsk_header_long_null](B5_psk_10000_8psk_bpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 1992.67 | 104 |
| [B5_psk_10000_8psk_bpsk_header_short_null](B5_psk_10000_8psk_bpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2294 | 75 |
| [B5_psk_10000_8psk_qpsk_header_long_null](B5_psk_10000_8psk_qpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 2187.33 | 83 |
| [B5_psk_10000_8psk_qpsk_header_short_null](B5_psk_10000_8psk_qpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2576.67 | 54 |
| [B5_psk_10000_bpsk_long_null](B5_psk_10000_bpsk_long_null/7446529.json) | assert / full | pass | — | — | 686.667 | 139 |
| [B5_psk_10000_bpsk_qpsk_header_long_null](B5_psk_10000_bpsk_qpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 756.667 | 118 |
| [B5_psk_10000_bpsk_qpsk_header_short_null](B5_psk_10000_bpsk_qpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 878 | 89 |
| [B5_psk_10000_bpsk_short_null](B5_psk_10000_bpsk_short_null/7446529.json) | assert / quick | pass | — | — | 782 | 110 |
| [B5_psk_10000_dbpsk_long_null](B5_psk_10000_dbpsk_long_null/7446529.json) | assert / full | pass | — | — | 686.667 | 139 |
| [B5_psk_10000_dbpsk_short_null](B5_psk_10000_dbpsk_short_null/7446529.json) | assert / quick | pass | — | — | 782 | 110 |
| [B5_psk_10000_dqpsk_long_null](B5_psk_10000_dqpsk_long_null/7446529.json) | assert / full | pass | — | — | 1374 | 119 |
| [B5_psk_10000_dqpsk_short_null](B5_psk_10000_dqpsk_short_null/7446529.json) | assert / quick | pass | — | — | 1568 | 91 |
| [B5_psk_10000_pi4_dqpsk_long_null](B5_psk_10000_pi4_dqpsk_long_null/7446529.json) | assert / full | pass | — | — | 1374 | 119 |
| [B5_psk_10000_pi4_dqpsk_short_null](B5_psk_10000_pi4_dqpsk_short_null/7446529.json) | assert / quick | pass | — | — | 1568 | 91 |
| [B5_psk_10000_qpsk_bpsk_header_long_null](B5_psk_10000_qpsk_bpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 1374 | 119 |
| [B5_psk_10000_qpsk_bpsk_header_short_null](B5_psk_10000_qpsk_bpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 1568 | 91 |
| [B5_psk_10000_qpsk_reference_long_null](B5_psk_10000_qpsk_reference_long_null/7446529.json) | assert / full | pass | — | — | 1516.67 | 99 |
| [B5_psk_10000_qpsk_reference_short_null](B5_psk_10000_qpsk_reference_short_null/7446529.json) | assert / quick | pass | — | — | 1760 | 70 |
| [B5_psk_24000_16qam_reference_long_null](B5_psk_24000_16qam_reference_long_null/7446529.json) | assert / full | pass | — | — | 2374 | 37 |
| [B5_psk_24000_16qam_reference_short_null](B5_psk_24000_16qam_reference_short_null/7446529.json) | assert / quick | pass | — | — | 2833.33 | 21 |
| [B5_psk_24000_64qam_reference_long_null](B5_psk_24000_64qam_reference_long_null/7446529.json) | assert / full | pass | — | — | 2376.67 | 35 |
| [B5_psk_24000_64qam_reference_short_null](B5_psk_24000_64qam_reference_short_null/7446529.json) | assert / quick | pass | — | — | 2838.67 | 20 |
| [B5_psk_24000_8psk_bpsk_header_long_null](B5_psk_24000_8psk_bpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 2131.33 | 47 |
| [B5_psk_24000_8psk_bpsk_header_short_null](B5_psk_24000_8psk_bpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2533.33 | 32 |
| [B5_psk_24000_8psk_qpsk_header_long_null](B5_psk_24000_8psk_qpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 2374 | 38 |
| [B5_psk_24000_8psk_qpsk_header_short_null](B5_psk_24000_8psk_qpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2693.33 | 23 |
| [B5_psk_24000_bpsk_long_null](B5_psk_24000_bpsk_long_null/7446529.json) | assert / full | pass | — | — | 1606 | 67 |
| [B5_psk_24000_bpsk_qpsk_header_long_null](B5_psk_24000_bpsk_qpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 1772.67 | 58 |
| [B5_psk_24000_bpsk_qpsk_header_short_null](B5_psk_24000_bpsk_qpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2114 | 43 |
| [B5_psk_24000_bpsk_short_null](B5_psk_24000_bpsk_short_null/7446529.json) | assert / quick | pass | — | — | 1888.67 | 51 |
| [B5_psk_24000_dbpsk_long_null](B5_psk_24000_dbpsk_long_null/7446529.json) | assert / full | pass | — | — | 1606 | 67 |
| [B5_psk_24000_dbpsk_short_null](B5_psk_24000_dbpsk_short_null/7446529.json) | assert / quick | pass | — | — | 1888.67 | 51 |
| [B5_psk_24000_dqpsk_long_null](B5_psk_24000_dqpsk_long_null/7446529.json) | assert / full | pass | — | — | 2131.33 | 49 |
| [B5_psk_24000_dqpsk_short_null](B5_psk_24000_dqpsk_short_null/7446529.json) | assert / quick | pass | — | — | 2347.33 | 34 |
| [B5_psk_24000_pi4_dqpsk_long_null](B5_psk_24000_pi4_dqpsk_long_null/7446529.json) | assert / full | pass | — | — | 2131.33 | 49 |
| [B5_psk_24000_pi4_dqpsk_short_null](B5_psk_24000_pi4_dqpsk_short_null/7446529.json) | assert / quick | pass | — | — | 2347.33 | 34 |
| [B5_psk_24000_qpsk_bpsk_header_long_null](B5_psk_24000_qpsk_bpsk_header_long_null/7446529.json) | assert / full | pass | — | — | 2131.33 | 49 |
| [B5_psk_24000_qpsk_bpsk_header_short_null](B5_psk_24000_qpsk_bpsk_header_short_null/7446529.json) | assert / quick | pass | — | — | 2347.33 | 34 |
| [B5_psk_24000_qpsk_reference_long_null](B5_psk_24000_qpsk_reference_long_null/7446529.json) | assert / full | pass | — | — | 2366 | 41 |
| [B5_psk_24000_qpsk_reference_short_null](B5_psk_24000_qpsk_reference_short_null/7446529.json) | assert / quick | pass | — | — | 2687.33 | 26 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_psk_10000_16qam_reference_long_null](B5_psk_10000_16qam_reference_long_null/7446529.host.json) | 12.029268000000926 | 80.04040999999961 | 79.18750000000063 | 0.9969659999999969 | 0.9969659999999969 | pass |
| [B5_psk_10000_16qam_reference_short_null](B5_psk_10000_16qam_reference_short_null/7446529.host.json) | 11.973873000000523 | 51.038080999999956 | 50.312500000000426 | 0.9964143333331918 | 0.9964143333331918 | pass |
| [B5_psk_10000_64qam_reference_long_null](B5_psk_10000_64qam_reference_long_null/7446529.host.json) | 9.001363999999956 | 76.09488199999959 | 75.81250000000006 | 1.0072450000002675 | 1.0072450000002675 | pass |
| [B5_psk_10000_64qam_reference_short_null](B5_psk_10000_64qam_reference_short_null/7446529.host.json) | 8.001023000000274 | 47.032038999999415 | 46.9375000000003 | 1.0038713333333504 | 1.0038713333333504 | pass |
| [B5_psk_10000_8psk_bpsk_header_long_null](B5_psk_10000_8psk_bpsk_header_long_null/7446529.host.json) | 18.001967000000008 | 104.03288099999929 | 103.43749999999984 | 0.9913150000002702 | 0.9913150000002702 | pass |
| [B5_psk_10000_8psk_bpsk_header_short_null](B5_psk_10000_8psk_bpsk_header_short_null/7446529.host.json) | 18.9935909999992 | 75.0381950000012 | 74.54166666666673 | 0.9891453333326083 | 0.9891453333326083 | pass |
| [B5_psk_10000_8psk_qpsk_header_long_null](B5_psk_10000_8psk_qpsk_header_long_null/7446529.host.json) | 17.005042999999944 | 83.03308700000001 | 82.68750000000047 | 1.2925339999991792 | 1.2925339999991792 | pass |
| [B5_psk_10000_8psk_qpsk_header_short_null](B5_psk_10000_8psk_qpsk_header_short_null/7446529.host.json) | 18.007498000000233 | 54.05111600000012 | 53.791666666667126 | 0.9879213333330306 | 0.9879213333330306 | pass |
| [B5_psk_10000_bpsk_long_null](B5_psk_10000_bpsk_long_null/7446529.host.json) | 48.00001899999984 | 139.0042030000007 | 138.43749999999932 | 0.9459439999996988 | 0.9459439999996988 | pass |
| [B5_psk_10000_bpsk_qpsk_header_long_null](B5_psk_10000_bpsk_qpsk_header_long_null/7446529.host.json) | 48.00185200000007 | 118.0016730000002 | 117.68749999999883 | 0.9615339999999861 | 0.9615339999999861 | pass |
| [B5_psk_10000_bpsk_qpsk_header_short_null](B5_psk_10000_bpsk_qpsk_header_short_null/7446529.host.json) | 47.00088000000058 | 89.00401299999983 | 88.6875000000007 | 0.9782603333330329 | 0.9782603333330329 | pass |
| [B5_psk_10000_bpsk_short_null](B5_psk_10000_bpsk_short_null/7446529.host.json) | 47.0021429999985 | 110.0014319999998 | 109.54166666666687 | 0.9595043333323616 | 0.9595043333323616 | pass |
| [B5_psk_10000_dbpsk_long_null](B5_psk_10000_dbpsk_long_null/7446529.host.json) | 48.000925000000194 | 139.00173000000038 | 138.43749999999932 | 0.9516659999997401 | 0.9516659999997401 | pass |
| [B5_psk_10000_dbpsk_short_null](B5_psk_10000_dbpsk_short_null/7446529.host.json) | 47.00658999999996 | 110.00176300000052 | 109.56249999999912 | 0.9619593333347609 | 0.9619593333347609 | pass |
| [B5_psk_10000_dqpsk_long_null](B5_psk_10000_dqpsk_long_null/7446529.host.json) | 27.553102999998913 | 119.0026959999999 | 118.81250000000021 | 0.9834340000001163 | 0.9834340000001163 | pass |
| [B5_psk_10000_dqpsk_short_null](B5_psk_10000_dqpsk_short_null/7446529.host.json) | 26.99856200000106 | 90.98620900000043 | 90.12500000000045 | 0.9839473333333295 | 0.9839473333333295 | pass |
| [B5_psk_10000_pi4_dqpsk_long_null](B5_psk_10000_pi4_dqpsk_long_null/7446529.host.json) | 27.645426999999945 | 119.00211499999891 | 118.81250000000021 | 0.9752933333331271 | 0.9752933333331271 | pass |
| [B5_psk_10000_pi4_dqpsk_short_null](B5_psk_10000_pi4_dqpsk_short_null/7446529.host.json) | 26.997681000000107 | 90.98789299999943 | 90.12500000000045 | 0.9672943333329798 | 0.9672943333329798 | pass |
| [B5_psk_10000_qpsk_bpsk_header_long_null](B5_psk_10000_qpsk_bpsk_header_long_null/7446529.host.json) | 27.572766999998777 | 119.00198500000015 | 118.81250000000021 | 0.9619453333336025 | 0.9619453333336025 | pass |
| [B5_psk_10000_qpsk_bpsk_header_short_null](B5_psk_10000_qpsk_bpsk_header_short_null/7446529.host.json) | 26.998352000000114 | 90.98814300000058 | 90.12500000000045 | 0.9841763333332558 | 0.9841763333332558 | pass |
| [B5_psk_10000_qpsk_reference_long_null](B5_psk_10000_qpsk_reference_long_null/7446529.host.json) | 27.993101000000074 | 99.00357400000104 | 98.31250000000047 | 0.9872820000000857 | 0.9872820000000857 | pass |
| [B5_psk_10000_qpsk_reference_short_null](B5_psk_10000_qpsk_reference_short_null/7446529.host.json) | 26.993552999999615 | 70.01223600000017 | 69.18749999999996 | 0.9695183333333617 | 0.9695183333333617 | pass |
| [B5_psk_24000_16qam_reference_long_null](B5_psk_24000_16qam_reference_long_null/7446529.host.json) | 6.004259999999206 | 37.06720700000066 | 36.1041666666666 | 1.1001653333329031 | 1.1001653333329031 | pass |
| [B5_psk_24000_16qam_reference_short_null](B5_psk_24000_16qam_reference_short_null/7446529.host.json) | 5.001894999999479 | 21.57219500000007 | 20.95833333333319 | 1.0457436666668762 | 1.0482186666669335 | pass |
| [B5_psk_24000_64qam_reference_long_null](B5_psk_24000_64qam_reference_long_null/7446529.host.json) | 5.008668000000327 | 35.085049999999725 | 34.70833333333445 | 1.1320396666683052 | 1.1320396666683052 | pass |
| [B5_psk_24000_64qam_reference_short_null](B5_psk_24000_64qam_reference_short_null/7446529.host.json) | 4.0016440000005815 | 20.015914000000024 | 19.520833333332988 | 1.0656516666660565 | 1.066222666667116 | pass |
| [B5_psk_24000_8psk_bpsk_header_long_null](B5_psk_24000_8psk_bpsk_header_long_null/7446529.host.json) | 7.966649000000103 | 47.05932500000021 | 46.208333333334295 | 1.0767713333332818 | 1.0767713333332818 | pass |
| [B5_psk_24000_8psk_bpsk_header_short_null](B5_psk_24000_8psk_bpsk_header_short_null/7446529.host.json) | 6.996544999999799 | 32.0099349999996 | 31.062499999999993 | 1.0457003333339543 | 1.0457003333339543 | pass |
| [B5_psk_24000_8psk_qpsk_header_long_null](B5_psk_24000_8psk_qpsk_header_long_null/7446529.host.json) | 7.986427000000518 | 38.065463000000136 | 37.58333333333308 | 1.1072126666675786 | 1.1072126666675786 | pass |
| [B5_psk_24000_8psk_qpsk_header_short_null](B5_psk_24000_8psk_qpsk_header_short_null/7446529.host.json) | 6.006151999999876 | 23.00923099999963 | 22.395833333332504 | 1.0378596666669182 | 1.0381996666666282 | pass |
| [B5_psk_24000_bpsk_long_null](B5_psk_24000_bpsk_long_null/7446529.host.json) | 25.00034799999984 | 67.01132899999962 | 66.583333333333 | 1.0824186666664737 | 1.0824186666664737 | pass |
| [B5_psk_24000_bpsk_qpsk_header_long_null](B5_psk_24000_bpsk_qpsk_header_long_null/7446529.host.json) | 24.997611999999947 | 58.04247499999882 | 57.99999999999983 | 1.0848926666664482 | 1.0848926666664482 | pass |
| [B5_psk_24000_bpsk_qpsk_header_short_null](B5_psk_24000_bpsk_qpsk_header_short_null/7446529.host.json) | 23.999774000000418 | 43.004265999998736 | 42.83333333333328 | 1.0136856666669303 | 1.0136856666669303 | pass |
| [B5_psk_24000_bpsk_short_null](B5_psk_24000_bpsk_short_null/7446529.host.json) | 24.011777000000123 | 51.00406600000085 | 50.499999999999545 | 1.0163016666666636 | 1.0163016666666636 | pass |
| [B5_psk_24000_dbpsk_long_null](B5_psk_24000_dbpsk_long_null/7446529.host.json) | 24.999785999998636 | 67.02553599999916 | 66.583333333333 | 1.083119666666299 | 1.083119666666299 | pass |
| [B5_psk_24000_dbpsk_short_null](B5_psk_24000_dbpsk_short_null/7446529.host.json) | 24.01525299999996 | 51.00974700000016 | 50.499999999999545 | 1.0189666666668984 | 1.0189666666668984 | pass |
| [B5_psk_24000_dqpsk_long_null](B5_psk_24000_dqpsk_long_null/7446529.host.json) | 10.015260999999498 | 49.052180999999976 | 48.97916666666724 | 1.0550969999991722 | 1.0550969999991722 | pass |
| [B5_psk_24000_dqpsk_short_null](B5_psk_24000_dqpsk_short_null/7446529.host.json) | 9.002336 | 34.856985999999424 | 33.83333333333294 | 1.0653193333327593 | 1.0653193333327593 | pass |
| [B5_psk_24000_pi4_dqpsk_long_null](B5_psk_24000_pi4_dqpsk_long_null/7446529.host.json) | 10.060185999999582 | 49.06810099999959 | 48.97916666666724 | 1.0874879999995812 | 1.0874879999995812 | pass |
| [B5_psk_24000_pi4_dqpsk_short_null](B5_psk_24000_pi4_dqpsk_short_null/7446529.host.json) | 9.001965999999584 | 34.78542999999945 | 33.83333333333294 | 1.0232816666659872 | 1.0232816666659872 | pass |
| [B5_psk_24000_qpsk_bpsk_header_long_null](B5_psk_24000_qpsk_bpsk_header_long_null/7446529.host.json) | 10.008879000000803 | 49.05157000000004 | 48.97916666666724 | 1.0546359999996646 | 1.0546359999996646 | pass |
| [B5_psk_24000_qpsk_bpsk_header_short_null](B5_psk_24000_qpsk_bpsk_header_short_null/7446529.host.json) | 9.001674999999487 | 34.839632999999814 | 33.83333333333294 | 1.0994113333335775 | 1.0994113333335775 | pass |
| [B5_psk_24000_qpsk_reference_long_null](B5_psk_24000_qpsk_reference_long_null/7446529.host.json) | 10.008980000000278 | 41.056215999999424 | 40.333333333333776 | 1.0945796666668173 | 1.0945796666668173 | pass |
| [B5_psk_24000_qpsk_reference_short_null](B5_psk_24000_qpsk_reference_short_null/7446529.host.json) | 9.002505999999855 | 26.022187000000585 | 25.187499999999474 | 1.0243246666665762 | 1.0252156666670231 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_psk_10000_16qam_reference_long_null | host_source_to_framer_ms | 0.0016030000011824086 | 23.01960100000011 | 23.01960100000011 |
| B5_psk_10000_16qam_reference_long_null | host_intake_per_message_ms | 0.00029100000009663063 | 0.0022239999999396076 | 0.0031259999999991295 |
| B5_psk_10000_16qam_reference_long_null | host_tx_per_block_ms | 0.002012999999578824 | 0.12133899999966502 | 0.14019500000017615 |
| B5_psk_10000_16qam_reference_long_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.018284000001145273 | 0.03475599999980261 |
| B5_psk_10000_16qam_reference_long_null | host_audio_wait_per_block_ms | 0.9399769999998142 | 1.0109809999994113 | 1.0439840000000533 |
| B5_psk_10000_16qam_reference_long_null | host_rx_per_block_ms | 0.05651699999997817 | 2.214946000000051 | 2.4530769999999977 |
| B5_psk_10000_16qam_reference_short_null | host_source_to_framer_ms | 0.0015230000007804279 | 9.520614999999566 | 9.520614999999566 |
| B5_psk_10000_16qam_reference_short_null | host_intake_per_message_ms | 0.0002299999999344493 | 0.002022999999989894 | 0.003186000000000508 |
| B5_psk_10000_16qam_reference_short_null | host_tx_per_block_ms | 0.002033999999984104 | 0.0684489999986937 | 0.077296000000171 |
| B5_psk_10000_16qam_reference_short_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.0013020000002583743 | 0.0017330000003923374 |
| B5_psk_10000_16qam_reference_short_null | host_audio_wait_per_block_ms | 0.9622190000000419 | 1.003156000000338 | 1.1528490000003444 |
| B5_psk_10000_16qam_reference_short_null | host_rx_per_block_ms | 0.033804000000969836 | 0.7271239999999679 | 0.881916999999996 |
| B5_psk_10000_64qam_reference_long_null | host_source_to_framer_ms | 0.0015219999999205314 | 22.113398000000117 | 22.113398000000117 |
| B5_psk_10000_64qam_reference_long_null | host_intake_per_message_ms | 0.0003510000006201608 | 0.0024039999999836414 | 0.003627000000000838 |
| B5_psk_10000_64qam_reference_long_null | host_tx_per_block_ms | 0.0022450000010110216 | 0.1041970000001946 | 0.11704100000020645 |
| B5_psk_10000_64qam_reference_long_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012420000001789333 | 0.001682999998919854 |
| B5_psk_10000_64qam_reference_long_null | host_audio_wait_per_block_ms | 0.932071999999895 | 1.0717150000001396 | 1.3226499999996477 |
| B5_psk_10000_64qam_reference_long_null | host_rx_per_block_ms | 0.06527299999881109 | 2.2084849999997047 | 2.442798000000579 |
| B5_psk_10000_64qam_reference_short_null | host_source_to_framer_ms | 0.0014630000002568977 | 9.518973000000486 | 9.518973000000486 |
| B5_psk_10000_64qam_reference_short_null | host_intake_per_message_ms | 0.00026999999924726126 | 0.002353999999371581 | 0.0035869999999993407 |
| B5_psk_10000_64qam_reference_short_null | host_tx_per_block_ms | 0.00231499999969742 | 0.06854000000000582 | 0.08612299999999351 |
| B5_psk_10000_64qam_reference_short_null | host_channel_per_block_ms | 0.0006910000003301775 | 0.0013420000000152754 | 0.0018840000000075463 |
| B5_psk_10000_64qam_reference_short_null | host_audio_wait_per_block_ms | 0.9532510000003214 | 1.0020239999999347 | 1.0313500000000002 |
| B5_psk_10000_64qam_reference_short_null | host_rx_per_block_ms | 0.04280099999931508 | 0.7263529999996798 | 0.8808650000000016 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_source_to_framer_ms | 1.001892999999754 | 9.571622000000168 | 9.571622000000168 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_intake_per_message_ms | 0.0003009999998138113 | 0.0032959999991533095 | 0.0037170000000003034 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_tx_per_block_ms | 0.0018339999989791522 | 0.1334030000004205 | 0.18049199999992105 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_channel_per_block_ms | 0.000682000001361871 | 0.0013120000001975995 | 0.0014630000002568977 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_audio_wait_per_block_ms | 0.9451259999995187 | 1.0059710000014377 | 1.1673170000001676 |
| B5_psk_10000_8psk_bpsk_header_long_null | host_rx_per_block_ms | 0.051066999999349605 | 2.5890830000001586 | 2.8260519999996347 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_source_to_framer_ms | 2.995882999999644 | 9.707058000000046 | 9.707058000000046 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_intake_per_message_ms | 0.00027100000110635847 | 0.001982999999761148 | 0.0035769999999994 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_tx_per_block_ms | 0.0018729999995414914 | 0.09874700000001013 | 0.13800100000027626 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.00131300000028034 | 0.001913000000186571 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_audio_wait_per_block_ms | 0.9667070000001221 | 1.011781999999073 | 1.032191 |
| B5_psk_10000_8psk_bpsk_header_short_null | host_rx_per_block_ms | 0.030115999999580367 | 0.7310719999997772 | 1.094318000000004 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_source_to_framer_ms | 0.0036469999997734703 | 26.087229999999906 | 26.087229999999906 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_intake_per_message_ms | 0.00026100000027895476 | 0.00231499999969742 | 0.0034760000000005203 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_tx_per_block_ms | 0.0018540000001898704 | 0.10407699999959164 | 0.10897599999992735 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.0013819999999942212 | 0.01129100000074601 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_audio_wait_per_block_ms | 0.9446149999999959 | 1.0478809999998617 | 1.3266479999999303 |
| B5_psk_10000_8psk_qpsk_header_long_null | host_rx_per_block_ms | 0.052689000000327724 | 2.177005000000065 | 2.859756000000005 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_source_to_framer_ms | 2.9880079999999865 | 9.499776000000182 | 9.499776000000182 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_intake_per_message_ms | 0.00020999999961190952 | 0.0021740000000214366 | 0.003495999999998667 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_tx_per_block_ms | 0.0018729999995414914 | 0.06768799999989916 | 0.07533200000020557 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.001172000000160267 | 0.0014530000000956278 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_audio_wait_per_block_ms | 0.9663469999994234 | 1.0022439999985977 | 1.0288050000002436 |
| B5_psk_10000_8psk_qpsk_header_short_null | host_rx_per_block_ms | 0.030387000000686726 | 0.7231070000006667 | 0.8861549999999996 |
| B5_psk_10000_bpsk_long_null | host_source_to_framer_ms | 4.578914999999961 | 9.762793000000158 | 9.762793000000158 |
| B5_psk_10000_bpsk_long_null | host_intake_per_message_ms | 0.0004400000000043258 | 0.0028750000007349286 | 0.003876999999999353 |
| B5_psk_10000_bpsk_long_null | host_tx_per_block_ms | 0.0015229999998922494 | 0.13750000000012363 | 0.15101500000014312 |
| B5_psk_10000_bpsk_long_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012320000006837972 | 0.0015230000016686063 |
| B5_psk_10000_bpsk_long_null | host_audio_wait_per_block_ms | 0.9540339999993819 | 1.0105200000003478 | 1.2245950000000505 |
| B5_psk_10000_bpsk_long_null | host_rx_per_block_ms | 0.043000999999875944 | 2.5967489999993987 | 2.9526810000000125 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_source_to_framer_ms | 4.977538999999531 | 22.165787000000048 | 22.165787000000048 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_intake_per_message_ms | 0.00043000000005122274 | 0.0033459999999995577 | 0.0034069999994557065 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_tx_per_block_ms | 0.0015329999989432963 | 0.10345499999964147 | 0.10777300000000545 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0011319999999592767 | 0.0017230000000090229 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_audio_wait_per_block_ms | 0.9537630000000519 | 1.0190269999998947 | 1.102604000000007 |
| B5_psk_10000_bpsk_qpsk_header_long_null | host_rx_per_block_ms | 0.04320200000001995 | 2.2161890000003126 | 2.3449120000000043 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_source_to_framer_ms | 5.000321000000696 | 19.021644000000173 | 19.021644000000173 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_intake_per_message_ms | 0.00039100000037706195 | 0.002053999999973577 | 0.002514999999999809 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_tx_per_block_ms | 0.0015330000007196531 | 0.06754800000052796 | 0.07429000000003239 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_channel_per_block_ms | 0.0006909999985538207 | 0.0010019999994170803 | 0.0015430000006588784 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_audio_wait_per_block_ms | 0.9767769999999842 | 1.0147380000000004 | 1.2268790000007357 |
| B5_psk_10000_bpsk_qpsk_header_short_null | host_rx_per_block_ms | 0.02025899999935632 | 0.704831999999378 | 0.8709760000000024 |
| B5_psk_10000_bpsk_short_null | host_source_to_framer_ms | 5.0000610000005 | 23.003520999999914 | 23.003520999999914 |
| B5_psk_10000_bpsk_short_null | host_intake_per_message_ms | 0.000460999999951639 | 0.0019030000000253011 | 0.003377000000000588 |
| B5_psk_10000_bpsk_short_null | host_tx_per_block_ms | 0.0015329999999980082 | 0.11741199999981689 | 0.15814800000013562 |
| B5_psk_10000_bpsk_short_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0013220000001368248 | 0.002163999999638122 |
| B5_psk_10000_bpsk_short_null | host_audio_wait_per_block_ms | 0.9769069999999713 | 1.0097179999997152 | 1.0382829999997512 |
| B5_psk_10000_bpsk_short_null | host_rx_per_block_ms | 0.020187999999699002 | 0.7219850000002026 | 1.020369 |
| B5_psk_10000_dbpsk_long_null | host_source_to_framer_ms | 4.345384000000507 | 9.549981999999346 | 9.549981999999346 |
| B5_psk_10000_dbpsk_long_null | host_intake_per_message_ms | 0.0004410000000731884 | 0.0030960000003688037 | 0.0034259999999990826 |
| B5_psk_10000_dbpsk_long_null | host_tx_per_block_ms | 0.0015329999998314747 | 0.13339199999951035 | 0.14331099999997932 |
| B5_psk_10000_dbpsk_long_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.001193000000121458 | 0.0014329999995510434 |
| B5_psk_10000_dbpsk_long_null | host_audio_wait_per_block_ms | 0.953672000000072 | 1.0064229999997565 | 1.1940370000003142 |
| B5_psk_10000_dbpsk_long_null | host_rx_per_block_ms | 0.043372000000374555 | 2.633156999999997 | 2.9560180000000047 |
| B5_psk_10000_dbpsk_short_null | host_source_to_framer_ms | 5.000703000000328 | 23.005574000000138 | 23.005574000000138 |
| B5_psk_10000_dbpsk_short_null | host_intake_per_message_ms | 0.0005609999997879811 | 0.0028849999997859754 | 0.0033259999999996764 |
| B5_psk_10000_dbpsk_short_null | host_tx_per_block_ms | 0.0015330000007196531 | 0.09887700000010824 | 0.14089600000000146 |
| B5_psk_10000_dbpsk_short_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.0013620000007819044 | 0.0035959999999946035 |
| B5_psk_10000_dbpsk_short_null | host_audio_wait_per_block_ms | 0.9765759999993406 | 1.0174529999997795 | 1.0458870000000786 |
| B5_psk_10000_dbpsk_short_null | host_rx_per_block_ms | 0.020509000000057398 | 0.7235770000000308 | 1.1080539999999972 |
| B5_psk_10000_dqpsk_long_null | host_source_to_framer_ms | 4.011301999999439 | 9.303607000001435 | 9.303607000001435 |
| B5_psk_10000_dqpsk_long_null | host_intake_per_message_ms | 0.0004009999994281088 | 0.0033370000000008254 | 0.0036569999997126956 |
| B5_psk_10000_dqpsk_long_null | host_tx_per_block_ms | 0.0017930000000276891 | 0.15011400000020103 | 0.16576300000004096 |
| B5_psk_10000_dqpsk_long_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.00127199999955252 | 0.0016030000002942302 |
| B5_psk_10000_dqpsk_long_null | host_audio_wait_per_block_ms | 0.9490239999996319 | 1.0145379999997317 | 1.0297669999994596 |
| B5_psk_10000_dqpsk_long_null | host_rx_per_block_ms | 0.047810999999953196 | 2.6175570000006587 | 3.041650000000007 |
| B5_psk_10000_dqpsk_short_null | host_source_to_framer_ms | 4.992998000000526 | 11.003248000000188 | 11.003248000000188 |
| B5_psk_10000_dqpsk_short_null | host_intake_per_message_ms | 0.0004109999984791557 | 0.0035870000001381186 | 0.0038069999996892534 |
| B5_psk_10000_dqpsk_short_null | host_tx_per_block_ms | 0.00181399999998888 | 0.09895699999962204 | 0.11346400000000756 |
| B5_psk_10000_dqpsk_short_null | host_channel_per_block_ms | 0.0006909999998860883 | 0.0013129999993921615 | 0.002123999999881221 |
| B5_psk_10000_dqpsk_short_null | host_audio_wait_per_block_ms | 0.9712259999999917 | 1.021099999999997 | 1.0397250000000469 |
| B5_psk_10000_dqpsk_short_null | host_rx_per_block_ms | 0.02566800000103342 | 0.7262029999992592 | 0.9876360000000001 |
| B5_psk_10000_pi4_dqpsk_long_null | host_source_to_framer_ms | 4.017633999999326 | 9.28952900000013 | 9.28952900000013 |
| B5_psk_10000_pi4_dqpsk_long_null | host_intake_per_message_ms | 0.0003209999999143065 | 0.003356000000120929 | 0.0035969999999992813 |
| B5_psk_10000_pi4_dqpsk_long_null | host_tx_per_block_ms | 0.0018029999999669144 | 0.13221999999935008 | 0.13853099999927565 |
| B5_psk_10000_pi4_dqpsk_long_null | host_channel_per_block_ms | 0.0007320000000587967 | 0.0010819999989308826 | 0.001963000000770876 |
| B5_psk_10000_pi4_dqpsk_long_null | host_audio_wait_per_block_ms | 0.9491540000006182 | 1.0011420000000104 | 1.034566 |
| B5_psk_10000_pi4_dqpsk_long_null | host_rx_per_block_ms | 0.047609999999309593 | 2.5999140000001475 | 2.8473419999999887 |
| B5_psk_10000_pi4_dqpsk_short_null | host_source_to_framer_ms | 4.997636000000583 | 11.004580000000042 | 11.004580000000042 |
| B5_psk_10000_pi4_dqpsk_short_null | host_intake_per_message_ms | 0.00039100000037706195 | 0.0024050000000386262 | 0.003486000000000461 |
| B5_psk_10000_pi4_dqpsk_short_null | host_tx_per_block_ms | 0.0018429999999458602 | 0.11597900000026584 | 0.13550599999945234 |
| B5_psk_10000_pi4_dqpsk_short_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.001382000000660355 | 0.015348999999886814 |
| B5_psk_10000_pi4_dqpsk_short_null | host_audio_wait_per_block_ms | 0.9712159999999415 | 1.0116019999999448 | 1.0463080000002734 |
| B5_psk_10000_pi4_dqpsk_short_null | host_rx_per_block_ms | 0.025658000000206016 | 0.7230859999998174 | 1.154202 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_source_to_framer_ms | 4.011531999999818 | 9.532538000000201 | 9.532538000000201 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_intake_per_message_ms | 0.0003109999999750812 | 0.003036000000067318 | 0.0036170000000008973 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_tx_per_block_ms | 0.00180299999999467 | 0.13042699999998852 | 0.1371289999999581 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0011420000003425912 | 0.0014129999996725928 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_audio_wait_per_block_ms | 0.9494549999997659 | 1.0013820000001061 | 1.0202690000000736 |
| B5_psk_10000_qpsk_bpsk_header_long_null | host_rx_per_block_ms | 0.047349000000806996 | 2.594063000000091 | 2.689823999999952 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_source_to_framer_ms | 4.999710000001656 | 11.003498 | 11.003498 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_intake_per_message_ms | 0.00028099999993536073 | 0.0014430000003784471 | 0.003305999999999795 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_tx_per_block_ms | 0.00181399999998888 | 0.09410799999987063 | 0.10917600000004413 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.0008420000003894756 | 0.0010320000001229346 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_audio_wait_per_block_ms | 0.9718169999999304 | 0.9989380000003933 | 1.0375510000004695 |
| B5_psk_10000_qpsk_bpsk_header_short_null | host_rx_per_block_ms | 0.025098000000056686 | 0.7100019999999319 | 1.078579000000003 |
| B5_psk_10000_qpsk_reference_long_null | host_source_to_framer_ms | 4.91143400000027 | 22.36040500000014 | 22.36040500000014 |
| B5_psk_10000_qpsk_reference_long_null | host_intake_per_message_ms | 0.00039999999978945766 | 0.002123999999881221 | 0.003335999999999617 |
| B5_psk_10000_qpsk_reference_long_null | host_tx_per_block_ms | 0.001822999999845365 | 0.1042870000009799 | 0.1128639999999903 |
| B5_psk_10000_qpsk_reference_long_null | host_channel_per_block_ms | 0.0006910000001081329 | 0.0012230000000000051 | 0.018094999999718198 |
| B5_psk_10000_qpsk_reference_long_null | host_audio_wait_per_block_ms | 0.948714000001516 | 1.0214499999996463 | 1.3514949999997583 |
| B5_psk_10000_qpsk_reference_long_null | host_rx_per_block_ms | 0.04823100000095337 | 2.231398000000162 | 2.454108999999871 |
| B5_psk_10000_qpsk_reference_short_null | host_source_to_framer_ms | 4.991764999999981 | 9.029327000000364 | 9.029327000000364 |
| B5_psk_10000_qpsk_reference_short_null | host_intake_per_message_ms | 0.00037100000005452216 | 0.0032759999999999734 | 0.003707000000074956 |
| B5_psk_10000_qpsk_reference_short_null | host_tx_per_block_ms | 0.0018339999998673306 | 0.06803799999843818 | 0.08050200000031538 |
| B5_psk_10000_qpsk_reference_short_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0012929999999578001 | 0.0019040000012182645 |
| B5_psk_10000_qpsk_reference_short_null | host_audio_wait_per_block_ms | 0.9714060000005631 | 1.0095080000001033 | 1.046248000000194 |
| B5_psk_10000_qpsk_reference_short_null | host_rx_per_block_ms | 0.0253980000000098 | 0.725700999999912 | 0.9862549999999983 |
| B5_psk_24000_16qam_reference_long_null | host_source_to_framer_ms | 0.0022939999997362293 | 10.962521999999808 | 10.962521999999808 |
| B5_psk_24000_16qam_reference_long_null | host_intake_per_message_ms | 0.00023099999957310047 | 0.003807000000577432 | 0.0038880000001739745 |
| B5_psk_24000_16qam_reference_long_null | host_tx_per_block_ms | 0.00914699999965407 | 0.3903980000004026 | 0.4065680000002736 |
| B5_psk_24000_16qam_reference_long_null | host_channel_per_block_ms | 0.000680999999946863 | 0.0012030000000606833 | 0.001452999999429494 |
| B5_psk_24000_16qam_reference_long_null | host_audio_wait_per_block_ms | 0.9123049999999466 | 1.004277999999914 | 1.0385429999999474 |
| B5_psk_24000_16qam_reference_long_null | host_rx_per_block_ms | 0.07806800000009773 | 2.9460090000004158 | 3.070965000000002 |
| B5_psk_24000_16qam_reference_short_null | host_source_to_framer_ms | 0.0030660000014393063 | 9.643287999999473 | 9.650600999999703 |
| B5_psk_24000_16qam_reference_short_null | host_intake_per_message_ms | 0.00024099999862414734 | 0.0018539999999955814 | 0.0036370000000007785 |
| B5_psk_24000_16qam_reference_short_null | host_tx_per_block_ms | 0.015389000000087805 | 0.24793800000111332 | 0.2691889999999475 |
| B5_psk_24000_16qam_reference_short_null | host_channel_per_block_ms | 0.0006909999985538207 | 0.0012119999990289898 | 0.0014730000010843014 |
| B5_psk_24000_16qam_reference_short_null | host_audio_wait_per_block_ms | 0.9175550000000143 | 1.0022850000001027 | 1.0321109999997802 |
| B5_psk_24000_16qam_reference_short_null | host_rx_per_block_ms | 0.06547400000034287 | 0.646321999999977 | 0.9807240000000023 |
| B5_psk_24000_64qam_reference_long_null | host_source_to_framer_ms | 0.001774000000231979 | 10.924440000000146 | 10.924440000000146 |
| B5_psk_24000_64qam_reference_long_null | host_intake_per_message_ms | 0.00021000000005599873 | 0.00233500000001996 | 0.0046580000000011335 |
| B5_psk_24000_64qam_reference_long_null | host_tx_per_block_ms | 0.009487999999890917 | 0.3704300000002547 | 0.3752990000003287 |
| B5_psk_24000_64qam_reference_long_null | host_channel_per_block_ms | 0.0006809999995027738 | 0.001201999999977943 | 0.009847999999923474 |
| B5_psk_24000_64qam_reference_long_null | host_audio_wait_per_block_ms | 0.9006520000000018 | 1.0006009999994347 | 1.027783 |
| B5_psk_24000_64qam_reference_long_null | host_rx_per_block_ms | 0.08922900000030154 | 2.9267220000002148 | 3.2703419999999817 |
| B5_psk_24000_64qam_reference_short_null | host_source_to_framer_ms | 0.0021139999999975068 | 9.589354999999244 | 9.590357999998744 |
| B5_psk_24000_64qam_reference_short_null | host_intake_per_message_ms | 0.0001909999998161993 | 0.0016030000002942302 | 0.0037670000000000065 |
| B5_psk_24000_64qam_reference_short_null | host_tx_per_block_ms | 0.01593999999993656 | 0.2303249999995316 | 0.2373279999998701 |
| B5_psk_24000_64qam_reference_short_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0008720000002071515 | 0.0015829999999716904 |
| B5_psk_24000_64qam_reference_short_null | host_audio_wait_per_block_ms | 0.8973869999999717 | 0.9988980000001924 | 1.1192260000001397 |
| B5_psk_24000_64qam_reference_short_null | host_rx_per_block_ms | 0.08500099999997346 | 0.6255120000000503 | 1.0069229999999998 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_source_to_framer_ms | 0.002925999999625617 | 22.285574999999945 | 22.285574999999945 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_intake_per_message_ms | 0.00023100000001718968 | 0.0017630000002100132 | 0.003897000000000969 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_tx_per_block_ms | 0.008987000000182377 | 0.4989830000000639 | 0.5066669999997941 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011620000002210418 | 0.0017730000001492385 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_audio_wait_per_block_ms | 0.919137999999986 | 1.0100089999998119 | 1.2646699999994127 |
| B5_psk_24000_8psk_bpsk_header_long_null | host_rx_per_block_ms | 0.07105399999929318 | 3.4061080000000743 | 3.6634140000000315 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_source_to_framer_ms | 0.0035770000001988933 | 9.888561000000017 | 9.888561000000017 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_intake_per_message_ms | 0.00020000000056086265 | 0.0023250000000807347 | 0.003476999999999994 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_tx_per_block_ms | 0.015118000000313714 | 0.35555200000025877 | 0.3638169999999885 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_channel_per_block_ms | 0.0006909999998860883 | 0.0010520000000013852 | 0.011472000000622984 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_audio_wait_per_block_ms | 0.92780399999981 | 1.0045990000000504 | 1.149041999999989 |
| B5_psk_24000_8psk_bpsk_header_short_null | host_rx_per_block_ms | 0.05553499999999545 | 0.8814160000003568 | 1.0792399999999986 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_source_to_framer_ms | 0.00314600000006493 | 10.971800000000087 | 10.971800000000087 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_intake_per_message_ms | 0.00023100000001718968 | 0.0030560000006119026 | 0.003626999999999103 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_tx_per_block_ms | 0.00937799999967126 | 0.38993700000133913 | 0.4216569999999642 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0011220000000200514 | 0.0015030000000137989 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_audio_wait_per_block_ms | 0.9139680000000427 | 1.0018040000012718 | 1.022993 |
| B5_psk_24000_8psk_qpsk_header_long_null | host_rx_per_block_ms | 0.07355900000005633 | 2.928155000001098 | 3.083467999999999 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_source_to_framer_ms | 0.0032360000004061362 | 9.601687999999942 | 9.639801000000004 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_intake_per_message_ms | 0.00017999999979423364 | 0.0016630000001516265 | 0.003677000000000541 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_tx_per_block_ms | 0.015139000000274905 | 0.2294930000008577 | 0.23595599999959305 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_channel_per_block_ms | 0.0007009999993812244 | 0.0009220000003473672 | 0.015569999999964779 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_audio_wait_per_block_ms | 0.9272119999996775 | 0.9989479999998885 | 1.03188 |
| B5_psk_24000_8psk_qpsk_header_short_null | host_rx_per_block_ms | 0.056046000000087304 | 0.6145819999989754 | 0.9783899999999991 |
| B5_psk_24000_bpsk_long_null | host_source_to_framer_ms | 4.041348999999528 | 28.102360999999966 | 28.102360999999966 |
| B5_psk_24000_bpsk_long_null | host_intake_per_message_ms | 0.0003209999999143065 | 0.002365000000281725 | 0.0037470000000001252 |
| B5_psk_24000_bpsk_long_null | host_tx_per_block_ms | 0.014487000000062977 | 0.49407399999878976 | 0.5121090000002049 |
| B5_psk_24000_bpsk_long_null | host_channel_per_block_ms | 0.0006910000003301775 | 0.0011030000006684304 | 0.0014329999999951326 |
| B5_psk_24000_bpsk_long_null | host_audio_wait_per_block_ms | 0.8873469999990391 | 1.0202689999996295 | 1.308212999999725 |
| B5_psk_24000_bpsk_long_null | host_rx_per_block_ms | 0.09604200000001839 | 3.411918999999486 | 3.587331000000006 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_source_to_framer_ms | 4.051106999999554 | 10.94206299999989 | 10.94206299999989 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_intake_per_message_ms | 0.0003400000001541059 | 0.003546000000298477 | 0.0035769999999994 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_tx_per_block_ms | 0.014507000000385517 | 0.37393699999999086 | 0.3891349999998184 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0012129999999999086 | 0.001662999999929582 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_audio_wait_per_block_ms | 0.8871069999999981 | 1.05574599999958 | 1.3614830000001632 |
| B5_psk_24000_bpsk_qpsk_header_long_null | host_rx_per_block_ms | 0.09691299999925462 | 2.93635100000067 | 3.4847370000000017 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_source_to_framer_ms | 4.452125000000251 | 9.60888300000029 | 9.60888300000029 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_intake_per_message_ms | 0.00028099999971331613 | 0.004088000000734837 | 0.004639000000000726 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_tx_per_block_ms | 0.014517999999963394 | 0.23246900000017945 | 0.24440200000030998 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_channel_per_block_ms | 0.000682000001361871 | 0.0012519999996740694 | 0.0020439999985910617 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_audio_wait_per_block_ms | 0.9484219999995602 | 1.051037000000754 | 1.4382780000001816 |
| B5_psk_24000_bpsk_qpsk_header_short_null | host_rx_per_block_ms | 0.0357369999992585 | 0.6138600000000771 | 0.8505879999999993 |
| B5_psk_24000_bpsk_short_null | host_source_to_framer_ms | 4.852972999999983 | 9.890495 | 9.890495 |
| B5_psk_24000_bpsk_short_null | host_intake_per_message_ms | 0.00031999999983156613 | 0.0031859999998218314 | 0.0036570000000006597 |
| B5_psk_24000_bpsk_short_null | host_tx_per_block_ms | 0.014537999999841844 | 0.3527769999998043 | 0.358407000000005 |
| B5_psk_24000_bpsk_short_null | host_channel_per_block_ms | 0.0006909999998860883 | 0.0011519999999487496 | 0.0014220000004172562 |
| B5_psk_24000_bpsk_short_null | host_audio_wait_per_block_ms | 0.9485330000007508 | 1.0073239999996986 | 1.1148969999998926 |
| B5_psk_24000_bpsk_short_null | host_rx_per_block_ms | 0.03545700000096019 | 0.8837509999999327 | 1.0916740000000007 |
| B5_psk_24000_dbpsk_long_null | host_source_to_framer_ms | 4.05821199999945 | 28.056032999999925 | 28.056032999999925 |
| B5_psk_24000_dbpsk_long_null | host_intake_per_message_ms | 0.00035099999973198237 | 0.002605000000599489 | 0.0035869999999993407 |
| B5_psk_24000_dbpsk_long_null | host_tx_per_block_ms | 0.014437999999117324 | 0.4918999999992124 | 0.5049339999998459 |
| B5_psk_24000_dbpsk_long_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012720000004406984 | 0.02902499999990482 |
| B5_psk_24000_dbpsk_long_null | host_audio_wait_per_block_ms | 0.8873870000005724 | 1.0572689999999163 | 1.34599500000121 |
| B5_psk_24000_dbpsk_long_null | host_rx_per_block_ms | 0.0966319999999854 | 3.3972420000001335 | 3.7633740000000415 |
| B5_psk_24000_dbpsk_short_null | host_source_to_framer_ms | 4.737685000000047 | 9.800784999999978 | 9.800784999999978 |
| B5_psk_24000_dbpsk_short_null | host_intake_per_message_ms | 0.000370999999999011 | 0.003175999999882606 | 0.003577000000001135 |
| B5_psk_24000_dbpsk_short_null | host_tx_per_block_ms | 0.014527000000041923 | 0.3533879999999545 | 0.3607720000005088 |
| B5_psk_24000_dbpsk_short_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012329999998783592 | 0.0016529999999903566 |
| B5_psk_24000_dbpsk_short_null | host_audio_wait_per_block_ms | 0.9478710000001556 | 1.0163520000001647 | 1.054443000000127 |
| B5_psk_24000_dbpsk_short_null | host_rx_per_block_ms | 0.03612899999999586 | 0.8901830000000999 | 1.2308660000000007 |
| B5_psk_24000_dqpsk_long_null | host_source_to_framer_ms | 0.005249999999956678 | 24.124472000000008 | 24.124472000000008 |
| B5_psk_24000_dqpsk_long_null | host_intake_per_message_ms | 0.00027099999933000163 | 0.0018639999996850065 | 0.004938999999998944 |
| B5_psk_24000_dqpsk_long_null | host_tx_per_block_ms | 0.010760000000331615 | 0.5076100000001027 | 0.5462429999996132 |
| B5_psk_24000_dqpsk_long_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0014530000000956278 | 0.02064899999965064 |
| B5_psk_24000_dqpsk_long_null | host_audio_wait_per_block_ms | 0.877709000000948 | 1.010679999999986 | 1.0378720000003838 |
| B5_psk_24000_dqpsk_long_null | host_rx_per_block_ms | 0.08136399999991717 | 3.431166000000374 | 3.759275999999978 |
| B5_psk_24000_dqpsk_short_null | host_source_to_framer_ms | 0.005120000000857772 | 5.03589900000001 | 5.03589900000001 |
| B5_psk_24000_dqpsk_short_null | host_intake_per_message_ms | 0.0003109999999750812 | 0.0029759999999878772 | 0.004488000000000408 |
| B5_psk_24000_dqpsk_short_null | host_tx_per_block_ms | 0.01487799999999595 | 0.3547510000014853 | 0.40083800000001446 |
| B5_psk_24000_dqpsk_short_null | host_channel_per_block_ms | 0.0006909999999971106 | 0.001353000000037241 | 0.0037669999999878634 |
| B5_psk_24000_dqpsk_short_null | host_audio_wait_per_block_ms | 0.9374220000000211 | 1.058501000000156 | 1.2920129999995922 |
| B5_psk_24000_dqpsk_short_null | host_rx_per_block_ms | 0.046456999999833215 | 0.8762760000000647 | 1.1200770000000007 |
| B5_psk_24000_pi4_dqpsk_long_null | host_source_to_framer_ms | 0.004818999999933737 | 24.145682000000114 | 24.145682000000114 |
| B5_psk_24000_pi4_dqpsk_long_null | host_intake_per_message_ms | 0.0002599999997521252 | 0.014988000000215607 | 0.015029000000055248 |
| B5_psk_24000_pi4_dqpsk_long_null | host_tx_per_block_ms | 0.008937000000042161 | 0.49828200000057166 | 0.5247519999986849 |
| B5_psk_24000_pi4_dqpsk_long_null | host_channel_per_block_ms | 0.0006910000003301775 | 0.0103389999992487 | 0.01656100000069216 |
| B5_psk_24000_pi4_dqpsk_long_null | host_audio_wait_per_block_ms | 0.9241270000002189 | 1.0006719999999802 | 1.035418 |
| B5_psk_24000_pi4_dqpsk_long_null | host_rx_per_block_ms | 0.0655639999997959 | 3.418131000000102 | 3.584596000000051 |
| B5_psk_24000_pi4_dqpsk_short_null | host_source_to_framer_ms | 0.004998999999727971 | 5.010701000000006 | 5.010701000000006 |
| B5_psk_24000_pi4_dqpsk_short_null | host_intake_per_message_ms | 0.0003309999998535318 | 0.003607000000016569 | 0.004107999999999196 |
| B5_psk_24000_pi4_dqpsk_short_null | host_tx_per_block_ms | 0.014929000000662995 | 0.37410700000073405 | 0.46745399999981174 |
| B5_psk_24000_pi4_dqpsk_short_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0013519999999545007 | 0.0019440000000869873 |
| B5_psk_24000_pi4_dqpsk_short_null | host_audio_wait_per_block_ms | 0.937151000000469 | 1.0028559999994968 | 1.032742 |
| B5_psk_24000_pi4_dqpsk_short_null | host_rx_per_block_ms | 0.046466999999994485 | 0.8966849999998416 | 1.0629390000000023 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_source_to_framer_ms | 0.005369999999782493 | 24.068745999999976 | 24.068745999999976 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_intake_per_message_ms | 0.0002500000002569891 | 0.0017439999999702138 | 0.0036170000000008973 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_tx_per_block_ms | 0.014407000000105086 | 0.5077190000002396 | 0.5715999999988952 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.001172000000160267 | 0.0015629999999822175 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_audio_wait_per_block_ms | 0.8777890000000177 | 1.0015530000000439 | 1.0427010000002568 |
| B5_psk_24000_qpsk_bpsk_header_long_null | host_rx_per_block_ms | 0.1046379999998237 | 3.422719999999657 | 3.591108000000176 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_source_to_framer_ms | 0.005260000000006926 | 5.004420000000009 | 5.004420000000009 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_intake_per_message_ms | 0.00028100000015740534 | 0.0025150000000362382 | 0.004558999999999466 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_tx_per_block_ms | 0.01613100000019685 | 0.35335800000169115 | 0.35843800000001647 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_channel_per_block_ms | 0.0006910000001081329 | 0.001292000000319149 | 0.0023640000001989847 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_audio_wait_per_block_ms | 0.9369310000000297 | 1.0031460000003989 | 1.033352999999959 |
| B5_psk_24000_qpsk_bpsk_header_short_null | host_rx_per_block_ms | 0.04540599999991457 | 0.8955929999991952 | 1.0761639999999975 |
| B5_psk_24000_qpsk_reference_long_null | host_source_to_framer_ms | 0.005240000000128475 | 10.9395990000003 | 10.9395990000003 |
| B5_psk_24000_qpsk_reference_long_null | host_intake_per_message_ms | 0.0002110000001387391 | 0.002214000000222427 | 0.0027749999999999997 |
| B5_psk_24000_qpsk_reference_long_null | host_tx_per_block_ms | 0.015249000000494561 | 0.37114100000046335 | 0.3765619999995806 |
| B5_psk_24000_qpsk_reference_long_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0010320000001229346 | 0.002063999999996069 |
| B5_psk_24000_qpsk_reference_long_null | host_audio_wait_per_block_ms | 0.8761560000003499 | 1.0028760000011516 | 1.0561060000000566 |
| B5_psk_24000_qpsk_reference_long_null | host_rx_per_block_ms | 0.10671199999912062 | 2.9449060000001914 | 3.127201000000024 |
| B5_psk_24000_qpsk_reference_short_null | host_source_to_framer_ms | 0.005099000000008402 | 6.619552000000084 | 6.623870999999948 |
| B5_psk_24000_qpsk_reference_short_null | host_intake_per_message_ms | 0.0003109999999750812 | 0.0022840000000190486 | 0.003656999999998925 |
| B5_psk_24000_qpsk_reference_short_null | host_tx_per_block_ms | 0.01487799999999595 | 0.23323100000016694 | 0.2572760000010277 |
| B5_psk_24000_qpsk_reference_short_null | host_channel_per_block_ms | 0.0006820000004736926 | 0.0013620000003378152 | 0.0014929999999913068 |
| B5_psk_24000_qpsk_reference_short_null | host_audio_wait_per_block_ms | 0.937712000000035 | 1.0024850000007746 | 1.0347349999992872 |
| B5_psk_24000_qpsk_reference_short_null | host_rx_per_block_ms | 0.04577600000033044 | 0.6626429999999628 | 0.9961529999999996 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_psk_10000_16qam_reference_long_null | 6.90625 | 0.5 | 0.5 | 1 | 2.3242187500000004 |
| B5_psk_10000_16qam_reference_short_null | 6.90625 | 0.5 | 0.5 | 0 | 2.3242187500000004 |
| B5_psk_10000_64qam_reference_long_null | 4.604166666666667 | 0.5 | 0.5 | 1 | 1.5494791666666667 |
| B5_psk_10000_64qam_reference_short_null | 4.604166666666667 | 0.5 | 0.5 | 0 | 1.5494791666666667 |
| B5_psk_10000_8psk_bpsk_header_long_null | 9.208333333333334 | 0.5 | 0.5 | 1 | 3.0989583333333335 |
| B5_psk_10000_8psk_bpsk_header_short_null | 9.208333333333334 | 0.5 | 0.5 | 0 | 3.0989583333333335 |
| B5_psk_10000_8psk_qpsk_header_long_null | 9.208333333333334 | 0.5 | 0.5 | 1 | 3.0989583333333335 |
| B5_psk_10000_8psk_qpsk_header_short_null | 9.208333333333334 | 0.5 | 0.5 | 0 | 3.0989583333333335 |
| B5_psk_10000_bpsk_long_null | 27.625 | 0.5 | 0.5 | 1 | 9.296875000000002 |
| B5_psk_10000_bpsk_qpsk_header_long_null | 27.625 | 0.5 | 0.5 | 1 | 9.296875000000002 |
| B5_psk_10000_bpsk_qpsk_header_short_null | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_psk_10000_bpsk_short_null | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_psk_10000_dbpsk_long_null | 27.625 | 0.5 | 0.5 | 1 | 9.296875000000002 |
| B5_psk_10000_dbpsk_short_null | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_psk_10000_dqpsk_long_null | 13.8125 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_psk_10000_dqpsk_short_null | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_psk_10000_pi4_dqpsk_long_null | 13.8125 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_psk_10000_pi4_dqpsk_short_null | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_psk_10000_qpsk_bpsk_header_long_null | 13.8125 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_psk_10000_qpsk_bpsk_header_short_null | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_psk_10000_qpsk_reference_long_null | 13.8125 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_psk_10000_qpsk_reference_short_null | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_psk_24000_16qam_reference_long_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.9684244791666666 |
| B5_psk_24000_16qam_reference_short_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_psk_24000_64qam_reference_long_null | 1.918402777777778 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.6456163194444445 |
| B5_psk_24000_64qam_reference_short_null | 1.918402777777778 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.6456163194444445 |
| B5_psk_24000_8psk_bpsk_header_long_null | 3.836805555555556 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.291232638888889 |
| B5_psk_24000_8psk_bpsk_header_short_null | 3.836805555555556 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.291232638888889 |
| B5_psk_24000_8psk_qpsk_header_long_null | 3.836805555555556 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.291232638888889 |
| B5_psk_24000_8psk_qpsk_header_short_null | 3.836805555555556 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.291232638888889 |
| B5_psk_24000_bpsk_long_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 3.8736979166666665 |
| B5_psk_24000_bpsk_qpsk_header_long_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 3.8736979166666665 |
| B5_psk_24000_bpsk_qpsk_header_short_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_psk_24000_bpsk_short_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_psk_24000_dbpsk_long_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 3.8736979166666665 |
| B5_psk_24000_dbpsk_short_null | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_psk_24000_dqpsk_long_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |
| B5_psk_24000_dqpsk_short_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_psk_24000_pi4_dqpsk_long_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |
| B5_psk_24000_pi4_dqpsk_short_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_psk_24000_qpsk_bpsk_header_long_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |
| B5_psk_24000_qpsk_bpsk_header_short_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_psk_24000_qpsk_reference_long_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |
| B5_psk_24000_qpsk_reference_short_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (354 declared cases) | — | not_run | — | — | — | — |

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
| Not run (54 declared cases) | — | not_run | — | — | — | — |

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
| Not run (249 declared cases) | — | not_run | — | — | — | — |

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
| full / selected rerun | 22 / 22 | 289.126 | 1800 | yes |
| quick / selected rerun | 22 / 22 | 281.828 | 120 | **NO** |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
