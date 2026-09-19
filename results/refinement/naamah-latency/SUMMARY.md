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
| pass | 46 |

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
| B5 | 46 | 0 | 0 | 0 |
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
| Not run (582 declared cases) | — | not_run | — | — | — | — |

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
| [B5_refinement_10000_8psk_bch_latency](B5_refinement_10000_8psk_bch_latency/7446529.json) | assert / full | pass | — | — | 2076.67 | 90 |
| [B5_refinement_10000_8psk_soft_latency](B5_refinement_10000_8psk_soft_latency/7446529.json) | assert / full | pass | — | — | 2076.67 | 93 |
| [B5_refinement_10000_bpsk_bch_latency](B5_refinement_10000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 1006.67 | 120 |
| [B5_refinement_10000_bpsk_bch_p16_r16_latency](B5_refinement_10000_bpsk_bch_p16_r16_latency/7446529.json) | assert / full | pass | — | — | 968.667 | 122 |
| [B5_refinement_10000_bpsk_bch_p32_r4_latency](B5_refinement_10000_bpsk_bch_p32_r4_latency/7446529.json) | assert / full | pass | — | — | 486.667 | 121 |
| [B5_refinement_10000_bpsk_bch_p32_r64_latency](B5_refinement_10000_bpsk_bch_p32_r64_latency/7446529.json) | assert / full | pass | — | — | 1367.33 | 120 |
| [B5_refinement_10000_bpsk_bch_p64_r16_latency](B5_refinement_10000_bpsk_bch_p64_r16_latency/7446529.json) | assert / full | pass | — | — | 1028 | 119 |
| [B5_refinement_10000_bpsk_soft_latency](B5_refinement_10000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 730 | 128 |
| [B5_refinement_10000_diversity_commensurate_both_latency](B5_refinement_10000_diversity_commensurate_both_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_commensurate_lower_latency](B5_refinement_10000_diversity_commensurate_lower_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_commensurate_upper_latency](B5_refinement_10000_diversity_commensurate_upper_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_offset137_both_latency](B5_refinement_10000_diversity_offset137_both_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_offset137_lower_latency](B5_refinement_10000_diversity_offset137_lower_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_offset137_upper_latency](B5_refinement_10000_diversity_offset137_upper_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_wide137_both_latency](B5_refinement_10000_diversity_wide137_both_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_wide137_lower_latency](B5_refinement_10000_diversity_wide137_lower_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_diversity_wide137_upper_latency](B5_refinement_10000_diversity_wide137_upper_latency/7446529.json) | assert / full | pass | — | — | 412 | 262 |
| [B5_refinement_10000_qpsk_bch_latency](B5_refinement_10000_qpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 2007.33 | 102 |
| [B5_refinement_10000_qpsk_bch_p16_r16_latency](B5_refinement_10000_qpsk_bch_p16_r16_latency/7446529.json) | assert / full | pass | — | — | 1928 | 103 |
| [B5_refinement_10000_qpsk_bch_p32_r4_latency](B5_refinement_10000_qpsk_bch_p32_r4_latency/7446529.json) | assert / full | pass | — | — | 970 | 102 |
| [B5_refinement_10000_qpsk_bch_p32_r64_latency](B5_refinement_10000_qpsk_bch_p32_r64_latency/7446529.json) | assert / full | pass | — | — | 2718 | 102 |
| [B5_refinement_10000_qpsk_bch_p64_r16_latency](B5_refinement_10000_qpsk_bch_p64_r16_latency/7446529.json) | assert / full | pass | — | — | 2027.33 | 100 |
| [B5_refinement_10000_qpsk_soft_latency](B5_refinement_10000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 1460.67 | 108 |
| [B5_refinement_24000_8psk_bch_latency](B5_refinement_24000_8psk_bch_latency/7446529.json) | assert / full | pass | — | — | 2124 | 47 |
| [B5_refinement_24000_8psk_soft_latency](B5_refinement_24000_8psk_soft_latency/7446529.json) | assert / full | pass | — | — | 2124 | 48 |
| [B5_refinement_24000_bpsk_bch_latency](B5_refinement_24000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 2070 | 55 |
| [B5_refinement_24000_bpsk_bch_p16_r16_latency](B5_refinement_24000_bpsk_bch_p16_r16_latency/7446529.json) | assert / full | pass | — | — | 2109.33 | 58 |
| [B5_refinement_24000_bpsk_bch_p32_r4_latency](B5_refinement_24000_bpsk_bch_p32_r4_latency/7446529.json) | assert / full | pass | — | — | 999.333 | 92 |
| [B5_refinement_24000_bpsk_bch_p32_r64_latency](B5_refinement_24000_bpsk_bch_p32_r64_latency/7446529.json) | assert / full | pass | — | — | 2737.33 | 55 |
| [B5_refinement_24000_bpsk_bch_p64_r16_latency](B5_refinement_24000_bpsk_bch_p64_r16_latency/7446529.json) | assert / full | pass | — | — | 2108.67 | 55 |
| [B5_refinement_24000_bpsk_soft_latency](B5_refinement_24000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 1619.33 | 68 |
| [B5_refinement_24000_diversity_commensurate_both_latency](B5_refinement_24000_diversity_commensurate_both_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_commensurate_lower_latency](B5_refinement_24000_diversity_commensurate_lower_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_commensurate_upper_latency](B5_refinement_24000_diversity_commensurate_upper_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_offset137_both_latency](B5_refinement_24000_diversity_offset137_both_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_offset137_lower_latency](B5_refinement_24000_diversity_offset137_lower_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_offset137_upper_latency](B5_refinement_24000_diversity_offset137_upper_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_wide137_both_latency](B5_refinement_24000_diversity_wide137_both_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_wide137_lower_latency](B5_refinement_24000_diversity_wide137_lower_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_diversity_wide137_upper_latency](B5_refinement_24000_diversity_wide137_upper_latency/7446529.json) | assert / full | pass | — | — | 963.333 | 124 |
| [B5_refinement_24000_qpsk_bch_latency](B5_refinement_24000_qpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 2124 | 49 |
| [B5_refinement_24000_qpsk_bch_p16_r16_latency](B5_refinement_24000_qpsk_bch_p16_r16_latency/7446529.json) | assert / full | pass | — | — | 2160 | 49 |
| [B5_refinement_24000_qpsk_bch_p32_r4_latency](B5_refinement_24000_qpsk_bch_p32_r4_latency/7446529.json) | assert / full | pass | — | — | 1328.67 | 49 |
| [B5_refinement_24000_qpsk_bch_p32_r64_latency](B5_refinement_24000_qpsk_bch_p32_r64_latency/7446529.json) | assert / full | pass | — | — | 2757.33 | 49 |
| [B5_refinement_24000_qpsk_bch_p64_r16_latency](B5_refinement_24000_qpsk_bch_p64_r16_latency/7446529.json) | assert / full | pass | — | — | 2111.33 | 48 |
| [B5_refinement_24000_qpsk_soft_latency](B5_refinement_24000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 2124 | 51 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_refinement_10000_8psk_bch_latency](B5_refinement_10000_8psk_bch_latency/7446529.host.json) | 13.999615999999993 | 90.00336599999947 | 89.18749999999997 | 0.94108499999912 | 0.94108499999912 | pass |
| [B5_refinement_10000_8psk_soft_latency](B5_refinement_10000_8psk_soft_latency/7446529.host.json) | 18.007105000000134 | 93.05673000000003 | 92.68749999999937 | 0.987781999999271 | 0.987781999999271 | pass |
| [B5_refinement_10000_bpsk_bch_latency](B5_refinement_10000_bpsk_bch_latency/7446529.host.json) | 37.0028609999995 | 120.000306 | 119.43749999999997 | 0.9500340000001586 | 0.9500340000001586 | pass |
| [B5_refinement_10000_bpsk_bch_p16_r16_latency](B5_refinement_10000_bpsk_bch_p16_r16_latency/7446529.host.json) | 40.00274500000067 | 122.00229699999987 | 121.18749999999956 | 0.9808080000000032 | 0.9808080000000032 | pass |
| [B5_refinement_10000_bpsk_bch_p32_r4_latency](B5_refinement_10000_bpsk_bch_p32_r4_latency/7446529.host.json) | 111.00177199999983 | 121.04762099999999 | 120.81249999999999 | 0.950863000000794 | 0.950863000000794 | pass |
| [B5_refinement_10000_bpsk_bch_p32_r64_latency](B5_refinement_10000_bpsk_bch_p32_r64_latency/7446529.host.json) | 37.00129899999993 | 120.00106200000005 | 119.62500000000098 | 0.9602340000007814 | 0.9602340000007814 | pass |
| [B5_refinement_10000_bpsk_bch_p64_r16_latency](B5_refinement_10000_bpsk_bch_p64_r16_latency/7446529.host.json) | 37.002321000000116 | 119.00238200000058 | 118.50000000000006 | 0.9770389999999978 | 0.9770389999999978 | pass |
| [B5_refinement_10000_bpsk_soft_latency](B5_refinement_10000_bpsk_soft_latency/7446529.host.json) | 50.003436999999984 | 128.0030110000001 | 127.6875000000004 | 0.9903109999997994 | 0.9903109999997994 | pass |
| [B5_refinement_10000_diversity_commensurate_both_latency](B5_refinement_10000_diversity_commensurate_both_latency/7446529.host.json) | 86.00155699999989 | 262.00249300000024 | 261.12499999999983 | 0.9638409999999169 | 0.9638409999999169 | pass |
| [B5_refinement_10000_diversity_commensurate_lower_latency](B5_refinement_10000_diversity_commensurate_lower_latency/7446529.host.json) | 86.00100600000005 | 262.0083229999999 | 261.12499999999983 | 0.952649999998556 | 0.952649999998556 | pass |
| [B5_refinement_10000_diversity_commensurate_upper_latency](B5_refinement_10000_diversity_commensurate_upper_latency/7446529.host.json) | 86.00412300000015 | 262.0015610000004 | 261.12499999999983 | 0.9890560000003177 | 0.9890560000003177 | pass |
| [B5_refinement_10000_diversity_offset137_both_latency](B5_refinement_10000_diversity_offset137_both_latency/7446529.host.json) | 86.00142799999988 | 261.9890979999999 | 261.12499999999983 | 0.9528779999996573 | 0.9528779999996573 | pass |
| [B5_refinement_10000_diversity_offset137_lower_latency](B5_refinement_10000_diversity_offset137_lower_latency/7446529.host.json) | 86.0092520000002 | 262.0026530000001 | 261.12499999999983 | 0.9478010000001404 | 0.9478010000001404 | pass |
| [B5_refinement_10000_diversity_offset137_upper_latency](B5_refinement_10000_diversity_offset137_upper_latency/7446529.host.json) | 86.00345099999984 | 262.0013700000001 | 261.12499999999983 | 0.9477489999993765 | 0.9477489999993765 | pass |
| [B5_refinement_10000_diversity_wide137_both_latency](B5_refinement_10000_diversity_wide137_both_latency/7446529.host.json) | 86.0024290000001 | 261.998755 | 261.12499999999983 | 0.954159999999149 | 0.954159999999149 | pass |
| [B5_refinement_10000_diversity_wide137_lower_latency](B5_refinement_10000_diversity_wide137_lower_latency/7446529.host.json) | 86.0056950000001 | 262.0012909999998 | 261.12499999999983 | 0.9474169999990067 | 0.9474169999990067 | pass |
| [B5_refinement_10000_diversity_wide137_upper_latency](B5_refinement_10000_diversity_wide137_upper_latency/7446529.host.json) | 86.00143700000018 | 262.00174099999975 | 261.12499999999983 | 0.9469509999995012 | 0.9469509999995012 | pass |
| [B5_refinement_10000_qpsk_bch_latency](B5_refinement_10000_qpsk_bch_latency/7446529.host.json) | 23.146243999999427 | 102.01387999999945 | 101.4999999999997 | 1.0074909999999733 | 1.0074909999999733 | pass |
| [B5_refinement_10000_qpsk_bch_p16_r16_latency](B5_refinement_10000_qpsk_bch_p16_r16_latency/7446529.host.json) | 24.000360999998804 | 103.03117699999964 | 102.93750000000034 | 0.9767519999996921 | 0.9767519999996921 | pass |
| [B5_refinement_10000_qpsk_bch_p32_r4_latency](B5_refinement_10000_qpsk_bch_p32_r4_latency/7446529.host.json) | 25.030958999999964 | 102.02119800000008 | 101.375 | 0.9774960000001904 | 0.9774960000001904 | pass |
| [B5_refinement_10000_qpsk_bch_p32_r64_latency](B5_refinement_10000_qpsk_bch_p32_r64_latency/7446529.host.json) | 22.001780999999276 | 102.01487600000014 | 101.74999999999912 | 0.9691373333335918 | 0.9802693333336165 | pass |
| [B5_refinement_10000_qpsk_bch_p64_r16_latency](B5_refinement_10000_qpsk_bch_p64_r16_latency/7446529.host.json) | 23.000831000000055 | 100.00270899999997 | 99.37500000000021 | 0.9838703333335808 | 0.9838703333335808 | pass |
| [B5_refinement_10000_qpsk_soft_latency](B5_refinement_10000_qpsk_soft_latency/7446529.host.json) | 29.05824499999987 | 108.00414800000001 | 108.00000000000054 | 0.9626693333331104 | 0.9626693333331104 | pass |
| [B5_refinement_24000_8psk_bch_latency](B5_refinement_24000_8psk_bch_latency/7446529.host.json) | 7.999588999999752 | 47.04282999999965 | 46.0208333333334 | 1.1207136666664397 | 1.1207136666664397 | pass |
| [B5_refinement_24000_8psk_soft_latency](B5_refinement_24000_8psk_soft_latency/7446529.host.json) | 9.92142400000029 | 48.12554699999971 | 47.45833333333316 | 1.1584916666667056 | 1.1584916666667056 | pass |
| [B5_refinement_24000_bpsk_bch_latency](B5_refinement_24000_bpsk_bch_latency/7446529.host.json) | 18.97542699999999 | 55.04819999999988 | 54.5624999999994 | 1.1168366666662877 | 1.1168366666662877 | pass |
| [B5_refinement_24000_bpsk_bch_p16_r16_latency](B5_refinement_24000_bpsk_bch_p16_r16_latency/7446529.host.json) | 22.000147999999943 | 58.059635999999855 | 57.97916666666669 | 1.0306703333338163 | 1.0306703333338163 | pass |
| [B5_refinement_24000_bpsk_bch_p32_r4_latency](B5_refinement_24000_bpsk_bch_p32_r4_latency/7446529.host.json) | 57.00416900000005 | 91.90654799999987 | 91.29166666666654 | 1.066838333333319 | 1.066838333333319 | pass |
| [B5_refinement_24000_bpsk_bch_p32_r64_latency](B5_refinement_24000_bpsk_bch_p32_r64_latency/7446529.host.json) | 15.071974999999682 | 55.00714200000001 | 54.39583333333342 | 1.0550253333332922 | 1.0688703333334715 | pass |
| [B5_refinement_24000_bpsk_bch_p64_r16_latency](B5_refinement_24000_bpsk_bch_p64_r16_latency/7446529.host.json) | 18.013186999999988 | 55.03106699999982 | 54.04166666666654 | 1.08284166666661 | 1.08284166666661 | pass |
| [B5_refinement_24000_bpsk_soft_latency](B5_refinement_24000_bpsk_soft_latency/7446529.host.json) | 26.950971000001545 | 68.06054900000014 | 67.77083333333422 | 1.0823976666666226 | 1.0823976666666226 | pass |
| [B5_refinement_24000_diversity_commensurate_both_latency](B5_refinement_24000_diversity_commensurate_both_latency/7446529.host.json) | 39.04376200000037 | 124.01736799999964 | 123.91666666666623 | 1.0231799999997904 | 1.0231799999997904 | pass |
| [B5_refinement_24000_diversity_commensurate_lower_latency](B5_refinement_24000_diversity_commensurate_lower_latency/7446529.host.json) | 39.99482999999992 | 124.01107600000039 | 123.91666666666623 | 0.9942073333333212 | 0.9942073333333212 | pass |
| [B5_refinement_24000_diversity_commensurate_upper_latency](B5_refinement_24000_diversity_commensurate_upper_latency/7446529.host.json) | 39.985933999998835 | 124.00315100000014 | 123.91666666666623 | 1.0052536666664906 | 1.0052536666664906 | pass |
| [B5_refinement_24000_diversity_offset137_both_latency](B5_refinement_24000_diversity_offset137_both_latency/7446529.host.json) | 39.019785999999 | 124.01953200000015 | 123.91666666666623 | 1.024633000000108 | 1.024633000000108 | pass |
| [B5_refinement_24000_diversity_offset137_lower_latency](B5_refinement_24000_diversity_offset137_lower_latency/7446529.host.json) | 39.98793699999936 | 124.01941099999902 | 123.91666666666623 | 1.002888666666209 | 1.002888666666209 | pass |
| [B5_refinement_24000_diversity_offset137_upper_latency](B5_refinement_24000_diversity_offset137_upper_latency/7446529.host.json) | 39.97873999999957 | 124.02924000000048 | 123.91666666666623 | 0.9826629999993841 | 0.9826629999993841 | pass |
| [B5_refinement_24000_diversity_wide137_both_latency](B5_refinement_24000_diversity_wide137_both_latency/7446529.host.json) | 39.04911099999975 | 124.01802900000014 | 123.91666666666623 | 1.0238009999996578 | 1.0238009999996578 | pass |
| [B5_refinement_24000_diversity_wide137_lower_latency](B5_refinement_24000_diversity_wide137_lower_latency/7446529.host.json) | 39.97406100000056 | 124.01201700000009 | 123.91666666666623 | 1.012777666666409 | 1.012777666666409 | pass |
| [B5_refinement_24000_diversity_wide137_upper_latency](B5_refinement_24000_diversity_wide137_upper_latency/7446529.host.json) | 39.98504199999964 | 124.02811800000002 | 123.91666666666623 | 0.9931163333334325 | 0.9931163333334325 | pass |
| [B5_refinement_24000_qpsk_bch_latency](B5_refinement_24000_qpsk_bch_latency/7446529.host.json) | 9.99844900000002 | 49.034736999999495 | 48.104166666666615 | 1.0878336666668709 | 1.0878336666668709 | pass |
| [B5_refinement_24000_qpsk_bch_p16_r16_latency](B5_refinement_24000_qpsk_bch_p16_r16_latency/7446529.host.json) | 10.001074999999915 | 49.073800999998696 | 48.41666666666677 | 1.0707976666655128 | 1.0707976666655128 | pass |
| [B5_refinement_24000_qpsk_bch_p32_r4_latency](B5_refinement_24000_qpsk_bch_p32_r4_latency/7446529.host.json) | 12.008140000000722 | 49.04918399999936 | 48.104166666666615 | 1.0951396666669666 | 1.0951396666669666 | pass |
| [B5_refinement_24000_qpsk_bch_p32_r64_latency](B5_refinement_24000_qpsk_bch_p32_r64_latency/7446529.host.json) | 9.954116000001179 | 49.002014000000926 | 48.0624999999999 | 0.9916149999993351 | 1.0311276666663538 | pass |
| [B5_refinement_24000_qpsk_bch_p64_r16_latency](B5_refinement_24000_qpsk_bch_p64_r16_latency/7446529.host.json) | 9.977941000000017 | 48.062036999999336 | 47.89583333333347 | 1.0569343333335368 | 1.0569343333335368 | pass |
| [B5_refinement_24000_qpsk_soft_latency](B5_refinement_24000_qpsk_soft_latency/7446529.host.json) | 12.006867999998505 | 51.10193700000032 | 50.22916666666699 | 1.1360786666667622 | 1.1360786666667622 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_refinement_10000_8psk_bch_latency | host_source_to_framer_ms | 1.001694999999997 | 75.96904299999996 | 75.96904299999996 |
| B5_refinement_10000_8psk_bch_latency | host_intake_per_message_ms | 0.00033000000065896984 | 0.001421999999973167 | 0.0033870000000005285 |
| B5_refinement_10000_8psk_bch_latency | host_tx_per_block_ms | 0.0015929999999109157 | 0.10487800000000269 | 0.14996400000022447 |
| B5_refinement_10000_8psk_bch_latency | host_channel_per_block_ms | 0.0006909999999971106 | 0.0010520000000013852 | 0.0017729999992610601 |
| B5_refinement_10000_8psk_bch_latency | host_audio_wait_per_block_ms | 0.9541539999995408 | 1.00438000000036 | 1.0221829999998988 |
| B5_refinement_10000_8psk_bch_latency | host_rx_per_block_ms | 0.04259000000000901 | 2.9901250000001767 | 3.303628000000003 |
| B5_refinement_10000_8psk_soft_latency | host_source_to_framer_ms | 0.00204399999947924 | 74.93089000000009 | 74.93089000000009 |
| B5_refinement_10000_8psk_soft_latency | host_intake_per_message_ms | 0.0003010000000358559 | 0.0032260000000002703 | 0.00732400000003075 |
| B5_refinement_10000_8psk_soft_latency | host_tx_per_block_ms | 0.0019939999997831137 | 0.118925000000214 | 0.1651929999999524 |
| B5_refinement_10000_8psk_soft_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.017362999999992468 | 0.024245999999727985 |
| B5_refinement_10000_8psk_soft_latency | host_audio_wait_per_block_ms | 0.927463999999989 | 1.0036079999999892 | 1.0464089999997483 |
| B5_refinement_10000_8psk_soft_latency | host_rx_per_block_ms | 0.06941200000021297 | 3.0327459999996975 | 3.2066139999997745 |
| B5_refinement_10000_bpsk_bch_latency | host_source_to_framer_ms | 4.039590000000093 | 91.01039000000011 | 91.01039000000011 |
| B5_refinement_10000_bpsk_bch_latency | host_intake_per_message_ms | 0.00040100000031628724 | 0.001683000000030077 | 0.003236000000000211 |
| B5_refinement_10000_bpsk_bch_latency | host_tx_per_block_ms | 0.001512000000314373 | 0.10269400000018081 | 0.155322999999985 |
| B5_refinement_10000_bpsk_bch_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0009319999998425033 | 0.0013129999993921615 |
| B5_refinement_10000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.9555170000004054 | 1.0012639999992246 | 1.036260000000233 |
| B5_refinement_10000_bpsk_bch_latency | host_rx_per_block_ms | 0.04146799999993345 | 3.049126000000013 | 3.150397999999832 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_source_to_framer_ms | 4.003651999999969 | 9.028354999999877 | 9.028354999999877 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_intake_per_message_ms | 0.0005010000001526294 | 0.0028160000002941388 | 0.0034170000000003503 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_tx_per_block_ms | 0.0015030000000137989 | 0.10504900000007922 | 0.14401200000024872 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0011220000000000004 | 0.001612999999345277 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_audio_wait_per_block_ms | 0.9552960000007715 | 1.0214010000000329 | 1.0464989999992014 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | host_rx_per_block_ms | 0.04164899999992144 | 3.03720399999996 | 3.378318999999963 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_source_to_framer_ms | 4.961032999999837 | 18.05486700000003 | 18.05486700000003 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_intake_per_message_ms | 0.0005109999999808323 | 0.003626999999999103 | 0.017263000000156126 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_tx_per_block_ms | 9.09999999798572e-05 | 0.12209099999971329 | 0.1623070000000837 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.015959999998926833 | 0.0373210000006452 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_audio_wait_per_block_ms | 0.99415000000036 | 1.0217820000004707 | 1.0565280000012223 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | host_rx_per_block_ms | 0.0008919999998635575 | 3.078141999999673 | 3.1856550000000095 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_source_to_framer_ms | 4.010875000000524 | 69.04423999999997 | 69.04423999999997 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_intake_per_message_ms | 0.0004210000001947378 | 0.002795000000332948 | 0.0034570000000001128 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_tx_per_block_ms | 0.0015129999999530241 | 0.10400600000015636 | 0.1459459999999524 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0010319999992347562 | 0.0013719999998329513 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_audio_wait_per_block_ms | 0.9550469999997091 | 1.0004319999996625 | 1.046490000000233 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | host_rx_per_block_ms | 0.04171899999994011 | 2.8730929999998267 | 3.1484650000006553 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_source_to_framer_ms | 4.006036999999907 | 67.03939799999992 | 67.03939799999992 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_intake_per_message_ms | 0.0004510000000124137 | 0.0024849999999965178 | 0.0032260000000002703 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_tx_per_block_ms | 0.0015129999999530241 | 0.10474800000004336 | 0.1891679999999063 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0012929999999578001 | 0.0017930000000276891 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_audio_wait_per_block_ms | 0.9555270000000116 | 1.009819999999939 | 1.0466099999999479 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | host_rx_per_block_ms | 0.041498999999944886 | 3.0345900000003923 | 3.180525000000045 |
| B5_refinement_10000_bpsk_soft_latency | host_source_to_framer_ms | 4.998543000001021 | 74.95995499999997 | 74.95995499999997 |
| B5_refinement_10000_bpsk_soft_latency | host_intake_per_message_ms | 0.0004709999998908643 | 0.002794999999999881 | 0.0032260000000002703 |
| B5_refinement_10000_bpsk_soft_latency | host_tx_per_block_ms | 0.0016230000001726808 | 0.10308500000011378 | 0.12213100000035837 |
| B5_refinement_10000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0010419999991739815 | 0.0015729999999214428 |
| B5_refinement_10000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.945968999999991 | 1.011283000000418 | 1.024627000001388 |
| B5_refinement_10000_bpsk_soft_latency | host_rx_per_block_ms | 0.050786000000968556 | 2.9818100000005288 | 3.161258 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_source_to_framer_ms | 5.00059700000044 | 12.00285000000001 | 12.00285000000001 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_intake_per_message_ms | 0.0005009999997085401 | 0.0023449999999591853 | 0.004488000000000408 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_tx_per_block_ms | 0.002184999999599313 | 0.2384109999997719 | 0.38653099999996776 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_channel_per_block_ms | 0.0006909999994419991 | 0.0012119999999171682 | 0.0015430000000205002 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_audio_wait_per_block_ms | 0.9538739999985779 | 0.9987890000000554 | 1.028836 |
| B5_refinement_10000_diversity_commensurate_both_latency | host_rx_per_block_ms | 0.04238999999994775 | 4.573429999998879 | 5.575655000000013 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_source_to_framer_ms | 4.977523999999178 | 12.00336099999988 | 12.00336099999988 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_intake_per_message_ms | 0.0005109999996477654 | 0.0020139999996615643 | 0.004227999999998483 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_tx_per_block_ms | 0.0025250000010856866 | 0.2255069999996806 | 0.2887259999999614 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_channel_per_block_ms | 0.0006909999999971106 | 0.0011619999999989972 | 0.001683000000696211 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_audio_wait_per_block_ms | 0.9739820000000954 | 1.0072750000000852 | 1.1242359999998897 |
| B5_refinement_10000_diversity_commensurate_lower_latency | host_rx_per_block_ms | 0.022012000000071197 | 2.4018320000001037 | 3.087619999999985 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_source_to_framer_ms | 4.95632300000004 | 12.003680999999933 | 12.003680999999933 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_intake_per_message_ms | 0.0005709999997272064 | 0.0037470000000539017 | 0.004118000000000871 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_tx_per_block_ms | 0.0025240000000037455 | 0.22443499999980077 | 0.2888260000000198 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_channel_per_block_ms | 0.0006910000003301775 | 0.0013029999994529362 | 0.0015030000000137989 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_audio_wait_per_block_ms | 0.9737310000001997 | 1.0944400000001409 | 1.3013209999996889 |
| B5_refinement_10000_diversity_commensurate_upper_latency | host_rx_per_block_ms | 0.022081000000007123 | 2.4810120000005043 | 2.747165999999801 |
| B5_refinement_10000_diversity_offset137_both_latency | host_source_to_framer_ms | 4.97833599999975 | 12.00287000000011 | 12.00287000000011 |
| B5_refinement_10000_diversity_offset137_both_latency | host_intake_per_message_ms | 0.000551000000292845 | 0.003647000000000719 | 0.0036470000006616488 |
| B5_refinement_10000_diversity_offset137_both_latency | host_tx_per_block_ms | 0.0022550000000620685 | 0.24150600000005795 | 0.3217279999999656 |
| B5_refinement_10000_diversity_offset137_both_latency | host_channel_per_block_ms | 0.0006909999994419991 | 0.0013119999984212427 | 0.001642999999162953 |
| B5_refinement_10000_diversity_offset137_both_latency | host_audio_wait_per_block_ms | 0.9531130000000054 | 0.9993900000000444 | 1.022875 |
| B5_refinement_10000_diversity_offset137_both_latency | host_rx_per_block_ms | 0.04307200000042144 | 4.43109100000072 | 4.9215979999999995 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_source_to_framer_ms | 4.997130999999655 | 12.012637999999853 | 12.012637999999853 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_intake_per_message_ms | 0.0005920000001324865 | 0.003607000000016569 | 0.004508999999999763 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_tx_per_block_ms | 0.0025449999991877803 | 0.22297200000132023 | 0.2737869999999143 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0014229999987236397 | 0.0021640000000267 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_audio_wait_per_block_ms | 0.9740420000001748 | 1.0014639999997854 | 1.1789800000006068 |
| B5_refinement_10000_diversity_offset137_lower_latency | host_rx_per_block_ms | 0.021991999999748657 | 2.398887000000016 | 3.0069970000000112 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_source_to_framer_ms | 4.981430999999148 | 12.003420000000098 | 12.003420000000098 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_intake_per_message_ms | 0.0005309999999703052 | 0.003476999999918462 | 0.0046379999999995175 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_tx_per_block_ms | 0.0025450000000759587 | 0.22346200000011862 | 0.2687379999999351 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0012030000000606833 | 0.010348999999187924 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_audio_wait_per_block_ms | 0.9738809999983999 | 1.0101310000000252 | 1.0308089999995218 |
| B5_refinement_10000_diversity_offset137_upper_latency | host_rx_per_block_ms | 0.022111000000712977 | 2.494567999999475 | 2.774496999999876 |
| B5_refinement_10000_diversity_wide137_both_latency | host_source_to_framer_ms | 4.992901999999688 | 12.03723499999998 | 12.03723499999998 |
| B5_refinement_10000_diversity_wide137_both_latency | host_intake_per_message_ms | 0.0006510000000000044 | 0.0023339999999372196 | 0.003976999999998759 |
| B5_refinement_10000_diversity_wide137_both_latency | host_tx_per_block_ms | 0.0022340000001008775 | 0.24426200000071674 | 0.31661900000001797 |
| B5_refinement_10000_diversity_wide137_both_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0013620000007819044 | 0.009698000000391005 |
| B5_refinement_10000_diversity_wide137_both_latency | host_audio_wait_per_block_ms | 0.9536629999999935 | 1.0003119999999477 | 1.019849 |
| B5_refinement_10000_diversity_wide137_both_latency | host_rx_per_block_ms | 0.04259099999970317 | 4.330809999999907 | 4.863188000000019 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_source_to_framer_ms | 4.993904999999965 | 12.003311000000183 | 12.003311000000183 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_intake_per_message_ms | 0.0004710000001129089 | 0.0021040000000027703 | 0.004619000000000845 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_tx_per_block_ms | 0.002545000000964137 | 0.22257100000011576 | 0.2681470000001074 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0010919999997582863 | 0.0016729999998688072 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_audio_wait_per_block_ms | 0.9739119999999657 | 0.9999619999998544 | 1.026471 |
| B5_refinement_10000_diversity_wide137_lower_latency | host_rx_per_block_ms | 0.02209200000002909 | 2.431397999999696 | 2.787472000000013 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_source_to_framer_ms | 5.001288999999964 | 12.003692000000177 | 12.003692000000177 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_intake_per_message_ms | 0.000530999999526216 | 0.004028000001099485 | 0.004488999999999882 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_tx_per_block_ms | 0.0025149999998141936 | 0.22251099999870405 | 0.28445799999998744 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0010720000007680142 | 0.001312000000031066 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_audio_wait_per_block_ms | 0.9740220000002964 | 1.0024449999999074 | 1.0442550000000494 |
| B5_refinement_10000_diversity_wide137_upper_latency | host_rx_per_block_ms | 0.021971999999870206 | 2.5160480000003815 | 3.0071269999999983 |
| B5_refinement_10000_qpsk_bch_latency | host_source_to_framer_ms | 3.000875000000014 | 75.96945500000007 | 75.96945500000007 |
| B5_refinement_10000_qpsk_bch_latency | host_intake_per_message_ms | 0.00028100000015740534 | 0.0024950000000467654 | 0.003177000000000041 |
| B5_refinement_10000_qpsk_bch_latency | host_tx_per_block_ms | 0.0015929999999109157 | 0.10223399999986782 | 0.15909999999985658 |
| B5_refinement_10000_qpsk_bch_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0009320000000645479 | 0.0013819999997721766 |
| B5_refinement_10000_qpsk_bch_latency | host_audio_wait_per_block_ms | 0.9547059999999163 | 1.0020150000000783 | 1.0367910000006475 |
| B5_refinement_10000_qpsk_bch_latency | host_rx_per_block_ms | 0.04197000000027984 | 3.043284999999951 | 3.209148999999911 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_source_to_framer_ms | 4.001818000000323 | 9.032853000000785 | 9.032853000000785 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_intake_per_message_ms | 0.000360999999976519 | 0.0030160000000015175 | 0.0030359999998452736 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_tx_per_block_ms | 0.0016529999999903566 | 0.10488799999919252 | 0.15344999999999942 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0013519999999545007 | 0.0019839999998438884 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_audio_wait_per_block_ms | 0.9547059999999163 | 1.0214519999998117 | 1.2717759999993916 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | host_rx_per_block_ms | 0.042039000000215765 | 3.0197909999998274 | 3.4581909999999993 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_source_to_framer_ms | 3.035129999999775 | 11.041842999999885 | 11.041842999999885 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_intake_per_message_ms | 0.00040099999998322033 | 0.002344000000320534 | 0.0036669999999988656 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_tx_per_block_ms | 9.099999864758956e-05 | 0.10452800000004814 | 0.17039200000024124 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012420000001789333 | 0.0014129999996725928 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_audio_wait_per_block_ms | 0.9948410000002461 | 1.0219430000013574 | 1.0408480000001497 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | host_rx_per_block_ms | 0.0005210000004751691 | 3.086416999999564 | 3.399819999999998 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_source_to_framer_ms | 3.001787000000089 | 9.028766000000132 | 54.04346900000001 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_intake_per_message_ms | 0.0002700000010236181 | 0.0032360000004061362 | 0.003326000000001411 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_tx_per_block_ms | 0.0016029999999889188 | 0.10510800000052001 | 0.14823999999968862 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0011830000001822327 | 0.002114000000830174 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_audio_wait_per_block_ms | 0.954215000000147 | 1.0033270000002759 | 1.0413190000004846 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | host_rx_per_block_ms | 0.04219900000013155 | 2.854919999998984 | 3.251810000000008 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_source_to_framer_ms | 4.001727999999538 | 55.04727799999998 | 55.04727799999998 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_intake_per_message_ms | 0.00032000000005361073 | 0.001732999999504159 | 0.0032759999999999734 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_tx_per_block_ms | 0.0016030000002942302 | 0.10404699999977396 | 0.1465270000000629 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0011430000004253316 | 0.0015529999988217469 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_audio_wait_per_block_ms | 0.9547159999998556 | 1.0213319999996529 | 1.208856999999952 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | host_rx_per_block_ms | 0.04202900000027654 | 3.0361120000002018 | 3.61940500000002 |
| B5_refinement_10000_qpsk_soft_latency | host_source_to_framer_ms | 4.023860000000212 | 74.94321400000015 | 74.94321400000015 |
| B5_refinement_10000_qpsk_soft_latency | host_intake_per_message_ms | 0.00036100000011529687 | 0.0021240000001032655 | 0.0035260000000002234 |
| B5_refinement_10000_qpsk_soft_latency | host_tx_per_block_ms | 0.001963999999965438 | 0.11894500000053654 | 0.170733000000034 |
| B5_refinement_10000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006910000003301775 | 0.0010219999992955309 | 0.018425000000155123 |
| B5_refinement_10000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.9360599999999053 | 1.0094489999999956 | 1.0436330000000993 |
| B5_refinement_10000_qpsk_soft_latency | host_rx_per_block_ms | 0.05999299999981389 | 3.029480000000362 | 3.1277350000000204 |
| B5_refinement_24000_8psk_bch_latency | host_source_to_framer_ms | 0.009136999999270756 | 10.10284699999997 | 10.10284699999997 |
| B5_refinement_24000_8psk_bch_latency | host_intake_per_message_ms | 0.0003210000003583957 | 0.0035969999999992813 | 0.009547999999970358 |
| B5_refinement_24000_8psk_bch_latency | host_tx_per_block_ms | 0.014456999999801212 | 0.37476899999955293 | 0.4618140000012261 |
| B5_refinement_24000_8psk_bch_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0013330000001587905 | 0.009306999999125765 |
| B5_refinement_24000_8psk_bch_latency | host_audio_wait_per_block_ms | 0.8747339999999326 | 1.0124749999995686 | 1.069812999999975 |
| B5_refinement_24000_8psk_bch_latency | host_rx_per_block_ms | 0.1076040000000944 | 4.7546819999997325 | 4.993573999999779 |
| B5_refinement_24000_8psk_soft_latency | host_source_to_framer_ms | 0.0028160000002941388 | 11.136682000000064 | 11.136682000000064 |
| B5_refinement_24000_8psk_soft_latency | host_intake_per_message_ms | 0.0003209999999143065 | 0.0035869999999993407 | 0.009998999999982772 |
| B5_refinement_24000_8psk_soft_latency | host_tx_per_block_ms | 0.009217000000560915 | 0.37161299999999287 | 0.3785860000000696 |
| B5_refinement_24000_8psk_soft_latency | host_channel_per_block_ms | 0.0006710000000076377 | 0.0012119999999171682 | 0.0194469999996727 |
| B5_refinement_24000_8psk_soft_latency | host_audio_wait_per_block_ms | 0.8769389999998545 | 1.0015139999999256 | 1.03626 |
| B5_refinement_24000_8psk_soft_latency | host_rx_per_block_ms | 0.11223199999932376 | 4.779949999999644 | 4.967173999999998 |
| B5_refinement_24000_bpsk_bch_latency | host_source_to_framer_ms | 2.003348000000571 | 10.103317999999861 | 10.103317999999861 |
| B5_refinement_24000_bpsk_bch_latency | host_intake_per_message_ms | 0.0003210000003583957 | 0.0020540000000845993 | 0.004567999999999933 |
| B5_refinement_24000_bpsk_bch_latency | host_tx_per_block_ms | 0.014247000000189303 | 0.3743080000000454 | 0.3841159999999899 |
| B5_refinement_24000_bpsk_bch_latency | host_channel_per_block_ms | 0.0006810000001689076 | 0.0011329999995979279 | 0.001702999999686483 |
| B5_refinement_24000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.8771789999997281 | 1.0035579999989608 | 1.0760750000002872 |
| B5_refinement_24000_bpsk_bch_latency | host_rx_per_block_ms | 0.10673199999899907 | 4.78243400000089 | 5.304441999999996 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_source_to_framer_ms | 3.0659979999998477 | 9.116812000000252 | 9.116812000000252 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_intake_per_message_ms | 0.0003210000000253288 | 0.001843999999806556 | 0.003647000000000719 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_tx_per_block_ms | 0.014226999999977785 | 0.3671750000000529 | 0.3771030000001563 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_channel_per_block_ms | 0.000680999999946863 | 0.001172000000160267 | 0.009308000000096683 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_audio_wait_per_block_ms | 0.8771190000000928 | 1.007745999999976 | 1.1977750000000675 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | host_rx_per_block_ms | 0.10657199999997147 | 4.781412999999901 | 4.828241000000233 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_source_to_framer_ms | 3.0665600000006066 | 38.92476699999992 | 38.92476699999992 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_intake_per_message_ms | 0.0004709999998908643 | 0.0022340000001008775 | 0.004498999999999823 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_tx_per_block_ms | 0.008335999998720922 | 0.38459700000004204 | 0.39323300000049244 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_channel_per_block_ms | 0.000680999999946863 | 0.001222000000744572 | 0.009277000000196267 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_audio_wait_per_block_ms | 0.978069999999498 | 1.0210809999993131 | 1.0436639999991115 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | host_rx_per_block_ms | 0.011842999999345238 | 4.794197000000278 | 5.165197999999982 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_source_to_framer_ms | 1.0361800000000532 | 9.112633999999176 | 9.12606900000057 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_intake_per_message_ms | 0.0003310000000755764 | 0.0016639999991241439 | 0.0030049999999986338 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_tx_per_block_ms | 0.014286999999058025 | 0.37411799999986783 | 0.39016799999996854 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0013229999993313868 | 0.0016030000011824086 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_audio_wait_per_block_ms | 0.8763880000000057 | 1.0014839999996639 | 1.1392150000002488 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | host_rx_per_block_ms | 0.1070320000000069 | 4.6371399999998175 | 5.028601000000001 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_source_to_framer_ms | 2.007797000000977 | 9.107864999999993 | 9.107864999999993 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_intake_per_message_ms | 0.00037100000049861137 | 0.0034570000000400114 | 0.004257999999701667 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_tx_per_block_ms | 0.014237000000250077 | 0.38589000000044393 | 0.3892059999999198 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_channel_per_block_ms | 0.0007310000000870787 | 0.001353000000037241 | 0.001612999999345277 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_audio_wait_per_block_ms | 0.8773289999997047 | 1.0241470000000863 | 1.2530899999996237 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | host_rx_per_block_ms | 0.10609100000102956 | 4.788144999999577 | 5.064587999999999 |
| B5_refinement_24000_bpsk_soft_latency | host_source_to_framer_ms | 4.058875999998435 | 16.076173000000082 | 16.076173000000082 |
| B5_refinement_24000_bpsk_soft_latency | host_intake_per_message_ms | 0.00041100000025551253 | 0.0029350000003702803 | 0.004388000000001002 |
| B5_refinement_24000_bpsk_soft_latency | host_tx_per_block_ms | 0.008756999999803838 | 0.4177399999996112 | 0.49854299999996243 |
| B5_refinement_24000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006809999995027738 | 0.0012929999999578001 | 0.0015329999999980082 |
| B5_refinement_24000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.9111930000003099 | 1.0036979999998863 | 1.0356590000002441 |
| B5_refinement_24000_bpsk_soft_latency | host_rx_per_block_ms | 0.07797800000020061 | 4.800167999999994 | 5.250138999999265 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_source_to_framer_ms | 4.024341000000042 | 9.052170000000359 | 9.052170000000359 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_intake_per_message_ms | 0.0005110000005359439 | 0.0034669999999792367 | 0.0035570000003204427 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_tx_per_block_ms | 0.015128999999447501 | 0.931039999999328 | 0.9836800000000423 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_channel_per_block_ms | 0.0006909999985538207 | 0.0013120000001975995 | 0.0019240000000975144 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_audio_wait_per_block_ms | 0.9015950000001993 | 1.013517 | 1.0420909999999672 |
| B5_refinement_24000_diversity_commensurate_both_latency | host_rx_per_block_ms | 0.07960099999948511 | 6.387099999999535 | 7.188814999999238 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_source_to_framer_ms | 4.030563000000598 | 9.058522000000124 | 9.058522000000124 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_intake_per_message_ms | 0.0005909999998277016 | 0.002904999999664426 | 0.003377000000000588 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_tx_per_block_ms | 0.015450000000249986 | 0.9312010000002147 | 0.9421009999999175 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_channel_per_block_ms | 0.0007120000002913685 | 0.0013030000003411146 | 0.0017529999999932322 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_audio_wait_per_block_ms | 0.9413699999996084 | 1.0777490000002388 | 1.282785999999092 |
| B5_refinement_24000_diversity_commensurate_lower_latency | host_rx_per_block_ms | 0.041018000000003774 | 3.478869000000273 | 3.6197760000007406 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_source_to_framer_ms | 4.031575000000398 | 9.036551000000337 | 9.036551000000337 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_intake_per_message_ms | 0.0005719999998099468 | 0.003296000000041488 | 0.003757000000000066 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_tx_per_block_ms | 0.015378999998816312 | 0.9293479999996634 | 0.9907540000000381 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_channel_per_block_ms | 0.000680999999946863 | 0.0014020000005388056 | 0.006302000000957264 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_audio_wait_per_block_ms | 0.942912999999379 | 1.0207599999993988 | 1.3340729999997691 |
| B5_refinement_24000_diversity_commensurate_upper_latency | host_rx_per_block_ms | 0.040016000000253626 | 3.624535000000151 | 4.46919300000026 |
| B5_refinement_24000_diversity_offset137_both_latency | host_source_to_framer_ms | 4.034449999999801 | 9.038825000000195 | 9.038825000000195 |
| B5_refinement_24000_diversity_offset137_both_latency | host_intake_per_message_ms | 0.0005109999996477654 | 0.0036269999998950198 | 0.003827000000001385 |
| B5_refinement_24000_diversity_offset137_both_latency | host_tx_per_block_ms | 0.015179000000031806 | 0.9338469999988774 | 0.9699139999996831 |
| B5_refinement_24000_diversity_offset137_both_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0013320000000760501 | 0.0018239999999281054 |
| B5_refinement_24000_diversity_offset137_both_latency | host_audio_wait_per_block_ms | 0.9017450000001759 | 1.0105609999999998 | 1.2437329999990254 |
| B5_refinement_24000_diversity_offset137_both_latency | host_rx_per_block_ms | 0.07979999999996323 | 6.419169999999141 | 6.57835100000001 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_source_to_framer_ms | 4.043377000000348 | 9.056849000000256 | 9.056849000000256 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_intake_per_message_ms | 0.0005619999994266323 | 0.027352000000036014 | 0.03432499999966865 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_tx_per_block_ms | 0.01551900000151818 | 0.9382739999992395 | 0.981345999999661 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.005129999999908819 | 0.018404000000415977 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_audio_wait_per_block_ms | 0.9270230000000268 | 1.0078659999999962 | 1.0387349999998463 |
| B5_refinement_24000_diversity_offset137_lower_latency | host_rx_per_block_ms | 0.04098700000021438 | 3.4672370000001784 | 3.544873999999254 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_source_to_framer_ms | 4.038567999999909 | 9.036659999999586 | 9.036659999999586 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_intake_per_message_ms | 0.0006009999999889715 | 0.02135999999985927 | 0.027683000000000568 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_tx_per_block_ms | 0.030687999999834403 | 0.9276549999999162 | 0.9383840000003474 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_channel_per_block_ms | 0.0006909999994419991 | 0.0016230000001726808 | 0.021810999999871683 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_audio_wait_per_block_ms | 0.9259409999997636 | 1.0170739999999512 | 1.0420709999999778 |
| B5_refinement_24000_diversity_offset137_upper_latency | host_rx_per_block_ms | 0.04111699999942431 | 3.486464000000078 | 4.399631000000001 |
| B5_refinement_24000_diversity_wide137_both_latency | host_source_to_framer_ms | 4.038007000000121 | 9.081314999999535 | 9.081314999999535 |
| B5_refinement_24000_diversity_wide137_both_latency | host_intake_per_message_ms | 0.0005810000001105209 | 0.003356000000565018 | 0.003585999999999867 |
| B5_refinement_24000_diversity_wide137_both_latency | host_tx_per_block_ms | 0.015198999999910257 | 0.930900999999984 | 0.9508479999986719 |
| B5_refinement_24000_diversity_wide137_both_latency | host_channel_per_block_ms | 0.0006820000004736926 | 0.0013330000001587905 | 0.0030959999999247145 |
| B5_refinement_24000_diversity_wide137_both_latency | host_audio_wait_per_block_ms | 0.9015450000013914 | 1.0674890000004211 | 1.2247260000002314 |
| B5_refinement_24000_diversity_wide137_both_latency | host_rx_per_block_ms | 0.07969099999993734 | 6.414882000000066 | 7.17897699999992 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_source_to_framer_ms | 4.03553199999962 | 9.045807999999989 | 9.045807999999989 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_intake_per_message_ms | 0.0006009999999889715 | 0.0033459999999995577 | 0.003767000000154397 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_tx_per_block_ms | 0.015469000000045696 | 0.9872170000004843 | 1.0219120000000137 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012220000000784381 | 0.00181399999998888 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_audio_wait_per_block_ms | 0.9415209999996677 | 1.0175650000006087 | 1.0368610000011103 |
| B5_refinement_24000_diversity_wide137_lower_latency | host_rx_per_block_ms | 0.04092800000066177 | 3.482917000001251 | 3.61492699999999 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_source_to_framer_ms | 4.035442000000167 | 9.060715999998692 | 9.060715999998692 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_intake_per_message_ms | 0.0006009999999889715 | 0.004979999999932261 | 0.017302999999913027 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_tx_per_block_ms | 0.0239649999986824 | 0.9300589999998721 | 0.9657970000001015 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_channel_per_block_ms | 0.0006820000004736926 | 0.01659099999962166 | 0.038833999999710045 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_audio_wait_per_block_ms | 0.9272229999996995 | 1.013176000000001 | 1.0420510000006544 |
| B5_refinement_24000_diversity_wide137_upper_latency | host_rx_per_block_ms | 0.04137800000014735 | 3.484960999999842 | 3.7407039999999974 |
| B5_refinement_24000_qpsk_bch_latency | host_source_to_framer_ms | 0.01514900000021413 | 12.107749000000112 | 12.107749000000112 |
| B5_refinement_24000_qpsk_bch_latency | host_intake_per_message_ms | 0.0003109999999750812 | 0.0037370000001146764 | 0.003977999999999968 |
| B5_refinement_24000_qpsk_bch_latency | host_tx_per_block_ms | 0.014388000000309376 | 0.41958400000030593 | 0.44412999999998704 |
| B5_refinement_24000_qpsk_bch_latency | host_channel_per_block_ms | 0.0006810000000023742 | 0.0010620000008287889 | 0.00198399999895571 |
| B5_refinement_24000_qpsk_bch_latency | host_audio_wait_per_block_ms | 0.8763169999999043 | 1.0187859999994942 | 1.028786000000892 |
| B5_refinement_24000_qpsk_bch_latency | host_rx_per_block_ms | 0.10707300000056819 | 4.721970999999936 | 5.005757000000166 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_source_to_framer_ms | 0.925609999999466 | 9.133133000000015 | 9.133133000000015 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_intake_per_message_ms | 0.0003310000007417102 | 0.0024749999999948424 | 0.003757000000000066 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_tx_per_block_ms | 0.014387000000226635 | 0.3699499999996192 | 0.3772929999996677 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011920000000387176 | 0.0096479999998067 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_audio_wait_per_block_ms | 0.876226999999119 | 1.0071549999999263 | 1.0256189999999776 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | host_rx_per_block_ms | 0.10714300000014276 | 4.74999399999998 | 5.227847000000008 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_source_to_framer_ms | 1.010892000000041 | 32.81458999999987 | 32.81458999999987 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_intake_per_message_ms | 0.00041999999922381903 | 0.002384999999993642 | 0.004166999999999366 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_tx_per_block_ms | 0.00839600000013263 | 0.37432799999947974 | 0.40560700000025207 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_channel_per_block_ms | 0.0006909999998860883 | 0.0013119999993094211 | 0.010118999999697564 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_audio_wait_per_block_ms | 0.9780299999999631 | 1.0036780000000078 | 1.0258699999994292 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | host_rx_per_block_ms | 0.011570999999932496 | 4.725317000000007 | 5.017197999999997 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_source_to_framer_ms | 0.012864000000334386 | 9.032423000000733 | 9.062279000000117 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_intake_per_message_ms | 0.0003209999999143065 | 0.0037370000001146764 | 0.003757000000000066 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_tx_per_block_ms | 0.014557000000081644 | 0.4073599999996347 | 0.4653700000000205 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012520000001181586 | 0.0015030000000137989 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_audio_wait_per_block_ms | 0.8754650000000197 | 1.0005930000005492 | 1.0251789999999872 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | host_rx_per_block_ms | 0.10761299999995089 | 4.64444399999997 | 5.010626000000018 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_source_to_framer_ms | 0.014958000000009353 | 9.104559000000013 | 9.104559000000013 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_intake_per_message_ms | 0.0003199999999980996 | 0.002173999999799392 | 0.003977999999999968 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_tx_per_block_ms | 0.014397999999360422 | 0.3730250000000268 | 0.3883550000001179 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.001353000000037241 | 0.0015829999995276012 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_audio_wait_per_block_ms | 0.8765180000001038 | 1.00316700000036 | 1.1345059999996465 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | host_rx_per_block_ms | 0.10701300000004466 | 4.710548999998565 | 5.12329899999997 |
| B5_refinement_24000_qpsk_soft_latency | host_source_to_framer_ms | 0.003987999999566227 | 13.153937000000004 | 13.153937000000004 |
| B5_refinement_24000_qpsk_soft_latency | host_intake_per_message_ms | 0.000329999999992836 | 0.0021240000000199988 | 0.003597000000001016 |
| B5_refinement_24000_qpsk_soft_latency | host_tx_per_block_ms | 0.009017000000000053 | 0.37424799999996594 | 0.3842370000000095 |
| B5_refinement_24000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006720000000903781 | 0.0013030000003411146 | 0.00144199999851935 |
| B5_refinement_24000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.8989810000006315 | 1.002566000000371 | 1.0223329999998754 |
| B5_refinement_24000_qpsk_soft_latency | host_rx_per_block_ms | 0.09037100000064413 | 4.712924000000007 | 5.111667999999958 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_refinement_10000_8psk_bch_latency | 6.676041666666666 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_8psk_soft_latency | 9.208333333333334 | 0.5 | 0.5 | 3 | 3.0989583333333335 |
| B5_refinement_10000_bpsk_bch_latency | 20.028125 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_bpsk_bch_p16_r16_latency | 21.206250000000004 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_bpsk_bch_p32_r4_latency | 20.028125 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_bpsk_bch_p32_r64_latency | 20.028125 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_bpsk_bch_p64_r16_latency | 19.4390625 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_bpsk_soft_latency | 27.625 | 0.5 | 0.5 | 3 | 9.296875000000002 |
| B5_refinement_10000_diversity_commensurate_both_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_commensurate_lower_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_commensurate_upper_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_offset137_both_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_offset137_lower_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_offset137_upper_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_wide137_both_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_wide137_lower_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_diversity_wide137_upper_latency | 50.0703125 | 1.25 | 1.25 | 3.125 | 0 |
| B5_refinement_10000_qpsk_bch_latency | 10.0140625 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_qpsk_bch_p16_r16_latency | 10.603125000000002 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_qpsk_bch_p32_r4_latency | 10.0140625 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_qpsk_bch_p32_r64_latency | 10.0140625 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_qpsk_bch_p64_r16_latency | 9.71953125 | 0.5 | 0.5 | 3 | 0 |
| B5_refinement_10000_qpsk_soft_latency | 13.8125 | 0.5 | 0.5 | 3 | 4.648437500000001 |
| B5_refinement_24000_8psk_bch_latency | 2.7816840277777772 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_8psk_soft_latency | 3.836805555555556 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 1.291232638888889 |
| B5_refinement_24000_bpsk_bch_latency | 8.345052083333334 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_bpsk_bch_p16_r16_latency | 8.8359375 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_bpsk_bch_p32_r4_latency | 8.345052083333334 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_bpsk_bch_p32_r64_latency | 8.345052083333334 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_bpsk_bch_p64_r16_latency | 8.099609374999998 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_bpsk_soft_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 3.8736979166666665 |
| B5_refinement_24000_diversity_commensurate_both_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_commensurate_lower_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_commensurate_upper_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_offset137_both_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_offset137_lower_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_offset137_upper_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_wide137_both_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_wide137_lower_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_diversity_wide137_upper_latency | 20.862630208333332 | 0.5208333333333334 | 0.5208333333333334 | 3.125 | 0 |
| B5_refinement_24000_qpsk_bch_latency | 4.172526041666667 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_qpsk_bch_p16_r16_latency | 4.41796875 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_qpsk_bch_p32_r4_latency | 4.172526041666667 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_qpsk_bch_p32_r64_latency | 4.172526041666667 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_qpsk_bch_p64_r16_latency | 4.049804687499999 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 0 |
| B5_refinement_24000_qpsk_soft_latency | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 3.0208333333333335 | 1.9368489583333333 |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1218 declared cases) | — | not_run | — | — | — | — |

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
| Not run (142 declared cases) | — | not_run | — | — | — | — |

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
| Not run (92 declared cases) | — | not_run | — | — | — | — |

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
| Not run (639 declared cases) | — | not_run | — | — | — | — |

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
| full / selected rerun | 46 / 46 | 601.958 | 1800 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
