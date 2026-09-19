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
| pass | 24 |

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
| B5 | 24 | 0 | 0 | 0 |
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
| Not run (702 declared cases) | — | not_run | — | — | — | — |

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
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json) | assert / quick | pass | — | — | 1016 | 79 |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 988 | 84 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json) | assert / quick | pass | — | — | 1527.33 | 72 |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 1484 | 77 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 507.333 | 116 |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 492 | 127 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | pass | — | — | 2400 | 34 |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 1913.33 | 35 |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json) | assert / quick | pass | — | — | 2461.33 | 26 |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 2274 | 32 |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 1224 | 48 |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 1125.33 | 53 |
| [B5_disturbed_10000_8psk_bch_latency](B5_disturbed_10000_8psk_bch_latency/7446529.json) | assert / full | pass | — | — | 822 | 118 |
| [B5_disturbed_10000_8psk_soft_latency](B5_disturbed_10000_8psk_soft_latency/7446529.json) | assert / full | pass | — | — | 596.667 | 125 |
| [B5_disturbed_10000_bpsk_bch_latency](B5_disturbed_10000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 271.333 | 192 |
| [B5_disturbed_10000_bpsk_soft_latency](B5_disturbed_10000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 196.667 | 260 |
| [B5_disturbed_10000_qpsk_bch_latency](B5_disturbed_10000_qpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 547.333 | 128 |
| [B5_disturbed_10000_qpsk_soft_latency](B5_disturbed_10000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 396.667 | 139 |
| [B5_disturbed_24000_8psk_bch_latency](B5_disturbed_24000_8psk_bch_latency/7446529.json) | assert / full | pass | — | — | 1276.67 | 82 |
| [B5_disturbed_24000_8psk_soft_latency](B5_disturbed_24000_8psk_soft_latency/7446529.json) | assert / full | pass | — | — | 982.667 | 90 |
| [B5_disturbed_24000_bpsk_bch_latency](B5_disturbed_24000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 450.667 | 142 |
| [B5_disturbed_24000_bpsk_soft_latency](B5_disturbed_24000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 326 | 174 |
| [B5_disturbed_24000_qpsk_bch_latency](B5_disturbed_24000_qpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 902 | 92 |
| [B5_disturbed_24000_qpsk_soft_latency](B5_disturbed_24000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 652.667 | 141 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 29.005424 | 79.01410999999992 | 78.79166666666748 | 1.0013450000005975 | 1.0013450000005975 | pass |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.host.json) | 30.070289000000194 | 84.05717199999962 | 83.68749999999991 | 1.002393000000005 | 1.002393000000005 | pass |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 21.99350599999983 | 72.04506300000003 | 71.91666666666663 | 1.0056670000002654 | 1.0056670000002654 | pass |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.host.json) | 22.98324900000015 | 77.03554599999984 | 76.56249999999964 | 1.0458663333334783 | 1.0458663333334783 | pass |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 92.00109399999957 | 116.00328100000002 | 115.35416666666664 | 0.9700073333327452 | 0.9700073333327452 | pass |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.host.json) | 96.99573500000014 | 127.00339500000001 | 126.60416666666663 | 0.9903920000011723 | 0.9903920000011723 | pass |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 17.07227400000022 | 34.00805000000018 | 33.08333333333336 | 1.1858426666666588 | 1.1858426666666588 | pass |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.host.json) | 11.94950100000014 | 35.085759000001104 | 34.04166666666697 | 1.143467666667064 | 1.143467666667064 | pass |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | 7.982103999999879 | 26.885803000000763 | 25.9999999999998 | 1.1262196666645963 | 1.1262196666645963 | pass |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.host.json) | 10.184119999999908 | 32.202052999999786 | 31.166666666667453 | 1.196314666667142 | 1.196314666667142 | pass |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | 39.003813 | 48.007048999999746 | 47.250000000000014 | 1.0400376666668265 | 1.0400376666668265 | pass |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.host.json) | 44.04692600000004 | 53.070209000001256 | 52.52083333333246 | 1.0838643333333486 | 1.0838643333333486 | pass |
| [B5_disturbed_10000_8psk_bch_latency](B5_disturbed_10000_8psk_bch_latency/7446529.host.json) | 35.996922999999015 | 117.99079199999873 | 117.1875 | 0.9984683333339461 | 0.9984683333339461 | pass |
| [B5_disturbed_10000_8psk_soft_latency](B5_disturbed_10000_8psk_soft_latency/7446529.host.json) | 45.00691199999984 | 125.02959100000055 | 124.91666666666657 | 1.035731333333331 | 1.035731333333331 | pass |
| [B5_disturbed_10000_bpsk_bch_latency](B5_disturbed_10000_bpsk_bch_latency/7446529.host.json) | 152.00465299999965 | 192.00318700000008 | 191.62499999999994 | 0.964090333333445 | 0.964090333333445 | pass |
| [B5_disturbed_10000_bpsk_soft_latency](B5_disturbed_10000_bpsk_soft_latency/7446529.host.json) | 177.0159290000004 | 260.0063429999997 | 259.4374999999998 | 0.9879230000003076 | 0.9879230000003076 | pass |
| [B5_disturbed_10000_qpsk_bch_latency](B5_disturbed_10000_qpsk_bch_latency/7446529.host.json) | 48.00818100000015 | 128.00474999999966 | 127.47916666666659 | 0.9792419999996582 | 0.9792419999996582 | pass |
| [B5_disturbed_10000_qpsk_soft_latency](B5_disturbed_10000_qpsk_soft_latency/7446529.host.json) | 130.99886600000053 | 139.01033500000005 | 138.68749999999963 | 0.9780180000005245 | 0.9780180000005245 | pass |
| [B5_disturbed_24000_8psk_bch_latency](B5_disturbed_24000_8psk_bch_latency/7446529.host.json) | 23.00758500000022 | 82.07691600000011 | 81.35416666666728 | 1.1528946666667927 | 1.1528946666667927 | pass |
| [B5_disturbed_24000_8psk_soft_latency](B5_disturbed_24000_8psk_soft_latency/7446529.host.json) | 27.97858100000017 | 90.10491599999959 | 89.89583333333329 | 1.175142666667739 | 1.175142666667739 | pass |
| [B5_disturbed_24000_bpsk_bch_latency](B5_disturbed_24000_bpsk_bch_latency/7446529.host.json) | 98.04998999999981 | 142.11424799999995 | 141.87499999999997 | 1.1137846666664615 | 1.1137846666664615 | pass |
| [B5_disturbed_24000_bpsk_soft_latency](B5_disturbed_24000_bpsk_soft_latency/7446529.host.json) | 110.01576100000054 | 174.03738199999987 | 173.9583333333332 | 1.1729816666668 | 1.1729816666668 | pass |
| [B5_disturbed_24000_qpsk_bch_latency](B5_disturbed_24000_qpsk_bch_latency/7446529.host.json) | 29.098920999999972 | 92.00115500000017 | 91.14583333333215 | 1.147626666666568 | 1.147626666666568 | pass |
| [B5_disturbed_24000_qpsk_soft_latency](B5_disturbed_24000_qpsk_soft_latency/7446529.host.json) | 88.0153220000004 | 141.12181999999996 | 140.97916666666666 | 1.1601816666670928 | 1.1601816666670928 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_10000_16qam_null | host_source_to_framer_ms | 4.015727999999719 | 55.99702799999995 | 55.99702799999995 |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.0006109999999281968 | 0.0034669999999792367 | 0.0034759999998357216 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.002024000000488968 | 0.08239499999973532 | 0.10499900000127127 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0016130000002334555 | 0.0018529999996630409 |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.9457690000000962 | 1.013879 | 1.0782609999999693 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.05055599999970184 | 0.8000839999997567 | 1.1489839999999987 |
| B5_10000_16qam_polar_span_null | host_source_to_framer_ms | 4.018434000000015 | 15.002438000000007 | 15.002438000000007 |
| B5_10000_16qam_polar_span_null | host_intake_per_message_ms | 0.0006310000006948258 | 0.0036869999995303715 | 0.004678999999998754 |
| B5_10000_16qam_polar_span_null | host_tx_per_block_ms | 0.0019729999998219228 | 0.08173500000019374 | 0.087135000000238 |
| B5_10000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0014830000001353483 | 0.0017240000000917632 |
| B5_10000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.9325850000001523 | 1.0243680000003863 | 1.0567699999999292 |
| B5_10000_16qam_polar_span_null | host_rx_per_block_ms | 0.06357100000009552 | 2.0246710000009216 | 2.1774610000004913 |
| B5_10000_64qam_null | host_source_to_framer_ms | 4.9784100000001 | 50.72362899999994 | 50.72362899999994 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.00046099999906346056 | 0.002473999999530463 | 0.0032660000000000328 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.0022349999999615733 | 0.0823159999985279 | 0.1301559999991042 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0015929999999109157 | 0.002744999999748643 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.9438050000003528 | 1.0234269999997991 | 1.03920699999982 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.05230899999997263 | 0.8045519999999584 | 1.1206399999999992 |
| B5_10000_64qam_polar_span_null | host_source_to_framer_ms | 4.071504000000115 | 9.092494000000118 | 9.092494000000118 |
| B5_10000_64qam_polar_span_null | host_intake_per_message_ms | 0.0004709999998908643 | 0.0033459999997376144 | 0.003347000000000766 |
| B5_10000_64qam_polar_span_null | host_tx_per_block_ms | 0.002214000000222427 | 0.0822859999995984 | 0.143130999999741 |
| B5_10000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0014630000002568977 | 0.002905999998858988 |
| B5_10000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.9203509999999859 | 1.024939999998864 | 1.0454779999999886 |
| B5_10000_64qam_polar_span_null | host_rx_per_block_ms | 0.07554299999945613 | 1.997218999999717 | 2.1030390000005283 |
| B5_10000_qpsk_null | host_source_to_framer_ms | 4.283214999999174 | 73.00102199999992 | 73.00102199999992 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.0004210000000004488 | 0.002535000000025711 | 0.004367999999999386 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.0019030000000253011 | 0.08060200000059581 | 0.08704399999992507 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.0006819999999740922 | 0.0013619999990055476 | 0.0015530000001540145 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.9667499999999052 | 1.0059729999998268 | 1.1510779999994725 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.029807000000658945 | 0.7589360000004319 | 1.060076 |
| B5_10000_qpsk_polar_span_null | host_source_to_framer_ms | 4.986536000000541 | 33.001704999999994 | 33.001704999999994 |
| B5_10000_qpsk_polar_span_null | host_intake_per_message_ms | 0.0004909999997693149 | 0.004007999999444678 | 0.005531000000225106 |
| B5_10000_qpsk_polar_span_null | host_tx_per_block_ms | 0.0017830000000884638 | 0.08053200000013305 | 0.08805700000014127 |
| B5_10000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006810000012791306 | 0.0014020000005388056 | 0.14776000000082945 |
| B5_10000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.9452479999998431 | 1.01443 | 1.0442560000001322 |
| B5_10000_qpsk_polar_span_null | host_rx_per_block_ms | 0.05126699999991047 | 2.002599000000771 | 2.301283999999626 |
| B5_24000_16qam_null | host_source_to_framer_ms | 3.990511000000474 | 10.279531 | 10.279531 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.0004209999993065594 | 0.00382699999999965 | 0.020348999999697526 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.011131000000164093 | 0.3256359999994629 | 0.3766920000000118 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.0006810000012791306 | 0.018125000000424052 | 0.0417290000012116 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.9180779999997668 | 1.0213129999998571 | 1.1425420000001907 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.06773799999981733 | 0.9529239999999106 | 1.2756740000000009 |
| B5_24000_16qam_polar_span_null | host_source_to_framer_ms | 0.003015000000772261 | 11.151380000000044 | 11.151380000000044 |
| B5_24000_16qam_polar_span_null | host_intake_per_message_ms | 0.00036099999967120766 | 0.0034859999988867685 | 0.004559000000001201 |
| B5_24000_16qam_polar_span_null | host_tx_per_block_ms | 0.009197000000682465 | 0.28087199999982104 | 0.41643800000001896 |
| B5_24000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006809999995027738 | 0.0014729999997520338 | 0.011200999999516625 |
| B5_24000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.8958850000000407 | 1.0229050000001294 | 1.1171440000001809 |
| B5_24000_16qam_polar_span_null | host_rx_per_block_ms | 0.09311599999994868 | 2.2263330000000003 | 2.343153999999986 |
| B5_24000_64qam_null | host_source_to_framer_ms | 0.0030960000003688037 | 10.195622000000002 | 10.195622000000002 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.00030999999989234084 | 0.0022639999999185534 | 0.0038780000000005616 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.009617999999989024 | 0.2938160000010015 | 0.30363499999985777 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.000680999999946863 | 0.0014630000002568977 | 0.0017430000003315627 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.9120559999997724 | 1.0117940000000658 | 1.0757650000000618 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.07785699999995899 | 0.9608380000010186 | 1.1858340000000003 |
| B5_24000_64qam_polar_span_null | host_source_to_framer_ms | 0.003064999999580209 | 10.853426000000166 | 10.853426000000166 |
| B5_24000_64qam_polar_span_null | host_intake_per_message_ms | 0.00028999999912571184 | 0.004037000000067792 | 0.004349000000000713 |
| B5_24000_64qam_polar_span_null | host_tx_per_block_ms | 0.009579000000314863 | 0.27958899999980247 | 0.4181409999999275 |
| B5_24000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006710000000076377 | 0.0014230000004999965 | 0.0018239999999281054 |
| B5_24000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.8776299999997406 | 1.0526610000010095 | 1.2283740000000876 |
| B5_24000_64qam_polar_span_null | host_rx_per_block_ms | 0.11268300000111253 | 2.186567999999056 | 2.6643210000000006 |
| B5_24000_qpsk_null | host_source_to_framer_ms | 4.984231000000006 | 12.072612999999954 | 12.072612999999954 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.0006309999989184689 | 0.0031959999997610566 | 0.004557999999999993 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.014828000001188002 | 0.2843780000008067 | 0.42935200000004947 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0017129999996257084 | 0.009837999999984248 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.925320999999979 | 1.0217330000008573 | 1.1912240000002683 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.05865100000068679 | 0.9573920000001124 | 1.2739000000000014 |
| B5_24000_qpsk_polar_span_null | host_source_to_framer_ms | 4.183927000000143 | 17.084137000000112 | 17.084137000000112 |
| B5_24000_qpsk_polar_span_null | host_intake_per_message_ms | 0.0006109999999281968 | 0.003356999999998972 | 0.004849999999834154 |
| B5_24000_qpsk_polar_span_null | host_tx_per_block_ms | 0.00889699999984117 | 0.32146800000010245 | 0.4167390000000548 |
| B5_24000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006809999995027738 | 0.0014930000000745736 | 0.0037680000000150926 |
| B5_24000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.9167249999997296 | 1.018537000000208 | 1.0447869999996584 |
| B5_24000_qpsk_polar_span_null | host_rx_per_block_ms | 0.07370999999967154 | 2.2045219999995425 | 2.470415 |
| B5_disturbed_10000_8psk_bch_latency | host_source_to_framer_ms | 4.973200999998539 | 17.016648000000025 | 17.016648000000025 |
| B5_disturbed_10000_8psk_bch_latency | host_intake_per_message_ms | 0.0006210000003115113 | 0.004247999999762442 | 0.004408000000566403 |
| B5_disturbed_10000_8psk_bch_latency | host_tx_per_block_ms | 0.0016029999994060518 | 0.08867799999912052 | 0.10573999999952122 |
| B5_disturbed_10000_8psk_bch_latency | host_channel_per_block_ms | 0.0006909999994419991 | 0.0015430000002147892 | 0.03542700000025434 |
| B5_disturbed_10000_8psk_bch_latency | host_audio_wait_per_block_ms | 0.9500979999996773 | 1.0265419999999637 | 1.1954020000004562 |
| B5_disturbed_10000_8psk_bch_latency | host_rx_per_block_ms | 0.04792100000017285 | 2.6693610000001478 | 3.979218999999999 |
| B5_disturbed_10000_8psk_soft_latency | host_source_to_framer_ms | 4.099726999999831 | 9.067747999999654 | 9.067747999999654 |
| B5_disturbed_10000_8psk_soft_latency | host_intake_per_message_ms | 0.0005609999997879811 | 0.0033460000000012924 | 0.0036869999995303715 |
| B5_disturbed_10000_8psk_soft_latency | host_tx_per_block_ms | 0.0016430000000511313 | 0.08728500000110273 | 0.09012099999994305 |
| B5_disturbed_10000_8psk_soft_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0014729999993079446 | 0.0017030000005746615 |
| B5_disturbed_10000_8psk_soft_latency | host_audio_wait_per_block_ms | 0.9452689999989161 | 1.0189780000002813 | 1.0901119999999764 |
| B5_disturbed_10000_8psk_soft_latency | host_rx_per_block_ms | 0.05098600000019715 | 2.6000800000005597 | 3.794198999999998 |
| B5_disturbed_10000_bpsk_bch_latency | host_source_to_framer_ms | 5.001153000000258 | 50.99942000000013 | 50.99942000000013 |
| B5_disturbed_10000_bpsk_bch_latency | host_intake_per_message_ms | 0.0005610000000100257 | 0.0033660000000011736 | 0.0035369999995538137 |
| B5_disturbed_10000_bpsk_bch_latency | host_tx_per_block_ms | 0.0015129999990648457 | 0.10276499999939404 | 0.11817399999980438 |
| B5_disturbed_10000_bpsk_bch_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0013229999993313868 | 0.0019140000002693114 |
| B5_disturbed_10000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.9501780000000792 | 1.0229160000001514 | 1.0599760000000735 |
| B5_disturbed_10000_bpsk_bch_latency | host_rx_per_block_ms | 0.04781999999980968 | 2.5879170000000506 | 3.635949999999999 |
| B5_disturbed_10000_bpsk_soft_latency | host_source_to_framer_ms | 5.001434000000415 | 9.090942000000268 | 9.090942000000268 |
| B5_disturbed_10000_bpsk_soft_latency | host_intake_per_message_ms | 0.0007010000002694028 | 0.002715000000000356 | 0.003677000000000541 |
| B5_disturbed_10000_bpsk_soft_latency | host_tx_per_block_ms | 0.0015229999998922494 | 0.10493899999985956 | 0.14663700000028257 |
| B5_disturbed_10000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.001602999999850141 | 0.02427599999954566 |
| B5_disturbed_10000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.949526999999506 | 1.0213829999994317 | 1.2038280000000734 |
| B5_disturbed_10000_bpsk_soft_latency | host_rx_per_block_ms | 0.04792100000017285 | 2.5981660000002904 | 4.082084999999999 |
| B5_disturbed_10000_qpsk_bch_latency | host_source_to_framer_ms | 4.004537999999336 | 9.040215999999823 | 9.040215999999823 |
| B5_disturbed_10000_qpsk_bch_latency | host_intake_per_message_ms | 0.0005910000009379246 | 0.0038069999996892534 | 0.004076999999824693 |
| B5_disturbed_10000_qpsk_bch_latency | host_tx_per_block_ms | 0.0016030000002942302 | 0.08777599999909569 | 0.10997800000023261 |
| B5_disturbed_10000_qpsk_bch_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0014930000000745736 | 0.002675000000174066 |
| B5_disturbed_10000_qpsk_bch_latency | host_audio_wait_per_block_ms | 0.9488959999996993 | 1.0226650000006998 | 1.0970550000006796 |
| B5_disturbed_10000_qpsk_bch_latency | host_rx_per_block_ms | 0.048019999999482366 | 2.5942589999994325 | 3.9539310000000008 |
| B5_disturbed_10000_qpsk_soft_latency | host_source_to_framer_ms | 4.002101999999397 | 9.039955000000433 | 9.039955000000433 |
| B5_disturbed_10000_qpsk_soft_latency | host_intake_per_message_ms | 0.0005709999992831172 | 0.0037469999991657232 | 0.0037470000000539017 |
| B5_disturbed_10000_qpsk_soft_latency | host_tx_per_block_ms | 0.0016130000002334555 | 0.08731500000003223 | 0.1002089999997402 |
| B5_disturbed_10000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0015229999998922494 | 0.002223999999273474 |
| B5_disturbed_10000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.9457399999996952 | 1.015119999999925 | 1.0328349999984 |
| B5_disturbed_10000_qpsk_soft_latency | host_rx_per_block_ms | 0.050937000000139676 | 2.5963230000005666 | 3.577598999999994 |
| B5_disturbed_24000_8psk_bch_latency | host_source_to_framer_ms | 3.06782499999958 | 47.17071599999989 | 47.17071599999989 |
| B5_disturbed_24000_8psk_bch_latency | host_intake_per_message_ms | 0.00039099999993297274 | 0.012874999999468173 | 0.015728999999353732 |
| B5_disturbed_24000_8psk_bch_latency | host_tx_per_block_ms | 0.00889700000072935 | 0.4642379999999502 | 0.638978999999873 |
| B5_disturbed_24000_8psk_bch_latency | host_channel_per_block_ms | 0.000680999999946863 | 0.014968000000337156 | 0.03367299999990081 |
| B5_disturbed_24000_8psk_bch_latency | host_audio_wait_per_block_ms | 0.9338270000003313 | 1.0177160000000018 | 1.087478000000086 |
| B5_disturbed_24000_8psk_bch_latency | host_rx_per_block_ms | 0.033764000000324756 | 6.067870999999947 | 12.485565000000005 |
| B5_disturbed_24000_8psk_soft_latency | host_source_to_framer_ms | 4.08909799999968 | 45.172204999999856 | 45.172204999999856 |
| B5_disturbed_24000_8psk_soft_latency | host_intake_per_message_ms | 0.00046099999906346056 | 0.0029560000003314713 | 0.00382699999999965 |
| B5_disturbed_24000_8psk_soft_latency | host_tx_per_block_ms | 0.0089170000006078 | 0.48275300000000243 | 0.5194429999999528 |
| B5_disturbed_24000_8psk_soft_latency | host_channel_per_block_ms | 0.0006710000000076377 | 0.0015130000008412026 | 0.0021740000004655258 |
| B5_disturbed_24000_8psk_soft_latency | host_audio_wait_per_block_ms | 0.946630999999698 | 1.022854999999545 | 1.3845400000001007 |
| B5_disturbed_24000_8psk_soft_latency | host_rx_per_block_ms | 0.023244000000310905 | 6.2172340000001824 | 12.636810999999998 |
| B5_disturbed_24000_bpsk_bch_latency | host_source_to_framer_ms | 4.090880999999769 | 47.115741999999905 | 47.115741999999905 |
| B5_disturbed_24000_bpsk_bch_latency | host_intake_per_message_ms | 0.0006420000016049698 | 0.0027350000000314623 | 0.0035869999999993407 |
| B5_disturbed_24000_bpsk_bch_latency | host_tx_per_block_ms | 0.008446000000716936 | 0.4821820000000532 | 0.5918500000010596 |
| B5_disturbed_24000_bpsk_bch_latency | host_channel_per_block_ms | 0.0007120000002913685 | 0.0015229999998922494 | 0.006922999999936508 |
| B5_disturbed_24000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.9484749999995046 | 1.0152210000002881 | 1.0931489999999044 |
| B5_disturbed_24000_bpsk_bch_latency | host_rx_per_block_ms | 0.022973000000092725 | 6.149485999999982 | 12.45102 |
| B5_disturbed_24000_bpsk_soft_latency | host_source_to_framer_ms | 4.930468999999604 | 55.13677899999991 | 55.13677899999991 |
| B5_disturbed_24000_bpsk_soft_latency | host_intake_per_message_ms | 0.0005109999996477654 | 0.0035959999999998077 | 0.003877000000152009 |
| B5_disturbed_24000_bpsk_soft_latency | host_tx_per_block_ms | 0.008586000000754268 | 0.4806689999998781 | 0.5230800000006752 |
| B5_disturbed_24000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006809999995027738 | 0.0015229999998922494 | 0.002835000000089849 |
| B5_disturbed_24000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.9485339999999454 | 1.0127260000007965 | 1.1040690000001518 |
| B5_disturbed_24000_bpsk_soft_latency | host_rx_per_block_ms | 0.022893000000578922 | 6.23926599999991 | 12.907333 |
| B5_disturbed_24000_qpsk_bch_latency | host_source_to_framer_ms | 4.014956999999875 | 47.112545999999924 | 47.112545999999924 |
| B5_disturbed_24000_qpsk_bch_latency | host_intake_per_message_ms | 0.0005309999999703052 | 0.0034859999999987262 | 0.003546999999493039 |
| B5_disturbed_24000_qpsk_bch_latency | host_tx_per_block_ms | 0.00858599999986609 | 0.4677250000000299 | 0.6027709999996134 |
| B5_disturbed_24000_qpsk_bch_latency | host_channel_per_block_ms | 0.0006809999995027738 | 0.0016030000002942302 | 0.0023850000001601757 |
| B5_disturbed_24000_qpsk_bch_latency | host_audio_wait_per_block_ms | 0.9478939999998381 | 1.0179859999999152 | 1.1688510000000818 |
| B5_disturbed_24000_qpsk_bch_latency | host_rx_per_block_ms | 0.023013999999932366 | 6.217124000000851 | 13.456141000000004 |
| B5_disturbed_24000_qpsk_soft_latency | host_source_to_framer_ms | 4.922172999999752 | 55.123213999999976 | 55.123213999999976 |
| B5_disturbed_24000_qpsk_soft_latency | host_intake_per_message_ms | 0.0004710000003349535 | 0.0031959999997610566 | 0.0034460000000006985 |
| B5_disturbed_24000_qpsk_soft_latency | host_tx_per_block_ms | 0.009468000000012466 | 0.4814309999998656 | 0.5431380000011643 |
| B5_disturbed_24000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006809999995027738 | 0.0015419999996879596 | 0.003166000000831559 |
| B5_disturbed_24000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.945900000000055 | 1.0130070000000657 | 1.0341970000009582 |
| B5_disturbed_24000_qpsk_soft_latency | host_rx_per_block_ms | 0.022953999999408836 | 6.218126000000268 | 14.010220000000004 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_10000_16qam_null | 18.062500000000004 | 0.5 | 0.5 | 0 | 2.3242187500000004 |
| B5_10000_16qam_polar_span_null | 18.062500000000004 | 0.5 | 0.5 | 1 | 2.3242187500000004 |
| B5_10000_64qam_null | 12.041666666666668 | 0.5 | 0.5 | 0 | 1.5494791666666667 |
| B5_10000_64qam_polar_span_null | 12.041666666666668 | 0.5 | 0.5 | 1 | 1.5494791666666667 |
| B5_10000_qpsk_null | 36.12500000000001 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_10000_qpsk_polar_span_null | 36.12500000000001 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_24000_16qam_null | 7.526041666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_24000_16qam_polar_span_null | 7.526041666666666 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.9684244791666666 |
| B5_24000_64qam_null | 5.017361111111112 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.6456163194444445 |
| B5_24000_64qam_polar_span_null | 5.017361111111112 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.6456163194444445 |
| B5_24000_qpsk_null | 15.052083333333332 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_24000_qpsk_polar_span_null | 15.052083333333332 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |
| B5_disturbed_10000_8psk_bch_latency | 17.460416666666667 | 0.5 | 0.5 | 7 | 0 |
| B5_disturbed_10000_8psk_soft_latency | 24.083333333333336 | 0.5 | 0.5 | 7 | 3.0989583333333335 |
| B5_disturbed_10000_bpsk_bch_latency | 52.381249999999994 | 0.5 | 0.5 | 7 | 0 |
| B5_disturbed_10000_bpsk_soft_latency | 72.25000000000001 | 0.5 | 0.5 | 7 | 9.296875000000002 |
| B5_disturbed_10000_qpsk_bch_latency | 26.190624999999997 | 0.5 | 0.5 | 7 | 0 |
| B5_disturbed_10000_qpsk_soft_latency | 36.12500000000001 | 0.5 | 0.5 | 7 | 4.648437500000001 |
| B5_disturbed_24000_8psk_bch_latency | 7.27517361111111 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 0 |
| B5_disturbed_24000_8psk_soft_latency | 10.034722222222223 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 1.291232638888889 |
| B5_disturbed_24000_bpsk_bch_latency | 21.825520833333336 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 0 |
| B5_disturbed_24000_bpsk_soft_latency | 30.104166666666664 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 3.8736979166666665 |
| B5_disturbed_24000_qpsk_bch_latency | 10.912760416666668 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 0 |
| B5_disturbed_24000_qpsk_soft_latency | 15.052083333333332 | 0.20833333333333334 | 0.20833333333333334 | 7.03125 | 1.9368489583333333 |

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
| Not run (154 declared cases) | — | not_run | — | — | — | — |

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
| Not run (104 declared cases) | — | not_run | — | — | — | — |

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
| Not run (759 declared cases) | — | not_run | — | — | — | — |

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
- D6 audits production AES-256-GCM tampering, replay and persisted restart epochs. A8 measures authentication rejection through the simulated RF path. Full A1-rate coverage and coordinated key rotation remain open.
- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.

See [TESTING.md](../../../TESTING.md) and [source audit/questions](../../../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 18 / 18 | 236.381 | 1800 | yes |
| quick / selected rerun | 6 / 6 | 76.518 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
