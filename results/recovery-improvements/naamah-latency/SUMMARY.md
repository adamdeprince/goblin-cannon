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
| pass | 12 |

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
| B5 | 12 | 0 | 0 | 0 |
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
| Not run (180 declared cases) | — | not_run | — | — | — | — |

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
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json) | assert / quick | pass | — | — | 2576.67 | 51 |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 2187.33 | 80 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json) | assert / quick | pass | — | — | 2579.33 | 47 |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 2187.33 | 76 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 1760 | 70 |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 1516.67 | 99 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | pass | — | — | 2833.33 | 21 |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 2374 | 37 |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json) | assert / quick | pass | — | — | 2838.67 | 20 |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 2376.67 | 35 |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 2687.33 | 26 |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 2366 | 41 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 11.978591000000094 | 51.00871099999971 | 50.312500000000426 | 0.9927903333331045 | 0.9927903333331045 | pass |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.host.json) | 12.025669999999877 | 80.03382199999898 | 79.18750000000063 | 0.9969440000006102 | 0.9969440000006102 | pass |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 8.000883000000236 | 47.019951999999975 | 46.9375000000003 | 1.0043513333333323 | 1.0043513333333323 | pass |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.host.json) | 9.00098199999988 | 76.0259759999995 | 75.81250000000006 | 1.0114419999984747 | 1.0114419999984747 | pass |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 26.997869000000563 | 70.00311300000028 | 69.18749999999996 | 0.9624700000010478 | 0.9624700000010478 | pass |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.host.json) | 27.996305999999915 | 99.00283499999985 | 98.31250000000047 | 0.9909249999999759 | 0.9909249999999759 | pass |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 5.001593000000248 | 21.556033000001307 | 20.95833333333319 | 1.0490896666661698 | 1.0498506666660745 | pass |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.host.json) | 6.003867999999635 | 37.071519000000386 | 36.1041666666666 | 1.0953690000001792 | 1.0953690000001792 | pass |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | 4.001964000000024 | 20.04164100000061 | 19.520833333332988 | 1.0656406666664786 | 1.0661526666666532 | pass |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.host.json) | 5.031650000001164 | 35.11211499999867 | 34.70833333333445 | 1.1097213333339795 | 1.1097213333339795 | pass |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | 9.001404000001045 | 26.015300999999713 | 25.187499999999474 | 1.0242326666665136 | 1.0544706666664183 | pass |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.host.json) | 10.007325000000122 | 41.049006999999804 | 40.333333333333776 | 1.0885956666666647 | 1.0885956666666647 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_10000_16qam_null | host_source_to_framer_ms | 0.0014029999988451891 | 9.526665999999295 | 9.526665999999295 |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.00016999999996603066 | 0.001692999999997058 | 0.0032059999999986544 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.002004000000166428 | 0.0671469999993235 | 0.07309799999999367 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.0006810000001689076 | 0.0011529999994763784 | 0.0018140000000027579 |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.9623090000001611 | 1.0026449999998022 | 1.0920040000002018 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.03381400000002088 | 0.7228559999994388 | 0.9669780000000003 |
| B5_10000_16qam_polar_span_null | host_source_to_framer_ms | 0.0019439999998649427 | 23.019168999999895 | 23.019168999999895 |
| B5_10000_16qam_polar_span_null | host_intake_per_message_ms | 0.00041100000025551253 | 0.0018440000015829128 | 0.003317000000000944 |
| B5_10000_16qam_polar_span_null | host_tx_per_block_ms | 0.0020140000001056535 | 0.10326499999990801 | 0.12911500000001297 |
| B5_10000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006810000003909522 | 0.0013330000001587905 | 0.0018339999989791522 |
| B5_10000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.9397259999985863 | 1.0059919999996225 | 1.1623370000002353 |
| B5_10000_16qam_polar_span_null | host_rx_per_block_ms | 0.05681700000081946 | 2.245033999999979 | 2.5797659999999834 |
| B5_10000_64qam_null | host_source_to_framer_ms | 0.001192000000926896 | 9.506087999998414 | 9.506087999998414 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.00016099999999852344 | 0.0015029999999860433 | 0.0029849999999987525 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.0022739999998577787 | 0.06791800000005566 | 0.07578399999985663 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.000680999999946863 | 0.0011629999999707152 | 0.0014630000000070975 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.9536620000001328 | 1.0012530000000002 | 1.0606449999999157 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.04242100000073634 | 0.7238980000003892 | 0.8921169999999978 |
| B5_10000_64qam_polar_span_null | host_source_to_framer_ms | 0.0014129999996725928 | 22.06626700000003 | 22.06626700000003 |
| B5_10000_64qam_polar_span_null | host_intake_per_message_ms | 0.0003299999997707914 | 0.001372000000054996 | 0.0034570000000001128 |
| B5_10000_64qam_polar_span_null | host_tx_per_block_ms | 0.002263999999030375 | 0.102654000000868 | 0.10839499999998337 |
| B5_10000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011120000005249153 | 0.0015930000003550049 |
| B5_10000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.9312509999999108 | 1.002655000000019 | 1.038433000000616 |
| B5_10000_64qam_polar_span_null | host_rx_per_block_ms | 0.06507299999999883 | 2.187313999999496 | 2.582090000000009 |
| B5_10000_qpsk_null | host_source_to_framer_ms | 4.997415999999921 | 9.027282999999997 | 9.027282999999997 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.00020100000064360302 | 0.003096000000035737 | 0.003356000000001233 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.00181399999998888 | 0.06639499999927523 | 0.07694499999999493 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012229999999391339 | 0.0018040000000496548 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.9716659999998711 | 1.002033999999874 | 1.0371500000001532 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.025187000000315152 | 0.7220150000000203 | 0.8766670000000045 |
| B5_10000_qpsk_polar_span_null | host_source_to_framer_ms | 4.939185000000457 | 22.130157999999955 | 22.130157999999955 |
| B5_10000_qpsk_polar_span_null | host_intake_per_message_ms | 0.00030999999989234084 | 0.0026249999987015826 | 0.003547000000001313 |
| B5_10000_qpsk_polar_span_null | host_tx_per_block_ms | 0.0018129999999061397 | 0.1045269999999654 | 0.14224799999951188 |
| B5_10000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011630000003037821 | 0.014977999999998826 |
| B5_10000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.942802000000853 | 1.0009220000011254 | 1.0300470000004225 |
| B5_10000_qpsk_polar_span_null | host_rx_per_block_ms | 0.05368199999988832 | 2.1884070000002254 | 2.3299839999992855 |
| B5_24000_16qam_null | host_source_to_framer_ms | 0.0027949999998888586 | 9.63269599999994 | 9.634880999999318 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.00018000000023832285 | 0.0016529999999903566 | 0.004337999999999564 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.01535899999982604 | 0.22992500000018623 | 0.23748800000067405 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.0006809999995027738 | 0.001141999999898502 | 0.0018639999996850065 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.9177349999999196 | 0.9992189999996626 | 1.030207 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.06540399999988011 | 0.630581000000241 | 0.9738409999999996 |
| B5_24000_16qam_polar_span_null | host_source_to_framer_ms | 0.002624000000395199 | 11.01094100000033 | 11.01094100000033 |
| B5_24000_16qam_polar_span_null | host_intake_per_message_ms | 0.00025999999930803597 | 0.0019540000000262125 | 0.004397999999999208 |
| B5_24000_16qam_polar_span_null | host_tx_per_block_ms | 0.009126999999997665 | 0.38926500000080466 | 0.4060479999994371 |
| B5_24000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006719999998683335 | 0.0012830000000185748 | 0.0017240000005358525 |
| B5_24000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.9128460000000782 | 1.0020139999999955 | 1.0321210000001635 |
| B5_24000_16qam_polar_span_null | host_rx_per_block_ms | 0.0774159999998858 | 2.9205800000013937 | 2.9849820000000804 |
| B5_24000_64qam_null | host_source_to_framer_ms | 0.0022140000000003823 | 9.59516500000035 | 9.596547999999316 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.0002010000001995138 | 0.0019540000000262125 | 0.003948000000000146 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.015949999999875786 | 0.23201900000024978 | 0.2424979999999799 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.0006809999995027738 | 0.001172999999354829 | 0.0018040000000496548 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.8977569999997215 | 1.0355269999999805 | 1.8213920000000001 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.08480099999985669 | 0.6313029999995834 | 1.0028860000000015 |
| B5_24000_64qam_polar_span_null | host_source_to_framer_ms | 0.00214400000064785 | 10.953103000000297 | 10.953103000000297 |
| B5_24000_64qam_polar_span_null | host_intake_per_message_ms | 0.00032000000027565534 | 0.0034570000000001128 | 0.01840499999961054 |
| B5_24000_64qam_polar_span_null | host_tx_per_block_ms | 0.009497999998941964 | 0.3873819999999917 | 0.4203949999999068 |
| B5_24000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006710000004517269 | 0.016832000000022163 | 0.021781000000054007 |
| B5_24000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.9002220000002836 | 1.003537000000776 | 1.027783 |
| B5_24000_64qam_polar_span_null | host_rx_per_block_ms | 0.08923799999926985 | 2.9229949999995952 | 3.3255659999999985 |
| B5_24000_qpsk_null | host_source_to_framer_ms | 0.0046989999997748555 | 6.599142999999974 | 6.602138999999951 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.00016999999985500835 | 0.0017429999999984958 | 0.0034660000000005797 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.014807999999977284 | 0.23027499999983547 | 0.242628000000078 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.0006810000000023742 | 0.0010320000001229346 | 0.07236599999949078 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.9380029999999095 | 0.9998099999997123 | 1.194236999999987 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.045606000000031344 | 0.618028000001658 | 0.8988990000000017 |
| B5_24000_qpsk_polar_span_null | host_source_to_framer_ms | 0.005180000000049034 | 10.93249399999996 | 10.93249399999996 |
| B5_24000_qpsk_polar_span_null | host_intake_per_message_ms | 0.00020999999961190952 | 0.0023140000013910367 | 0.004057999999999493 |
| B5_24000_qpsk_polar_span_null | host_tx_per_block_ms | 0.01477799999882734 | 0.37157199999970913 | 0.38486799999937205 |
| B5_24000_qpsk_polar_span_null | host_channel_per_block_ms | 0.000680999999946863 | 0.0011520000002818165 | 0.009998999999982772 |
| B5_24000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.8770180000001737 | 1.0023040000000094 | 1.2032340000001085 |
| B5_24000_qpsk_polar_span_null | host_rx_per_block_ms | 0.10637100000021604 | 2.944296000000346 | 3.1506649999997194 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_10000_16qam_null | 6.90625 | 0.5 | 0.5 | 0 | 2.3242187500000004 |
| B5_10000_16qam_polar_span_null | 6.90625 | 0.5 | 0.5 | 1 | 2.3242187500000004 |
| B5_10000_64qam_null | 4.604166666666667 | 0.5 | 0.5 | 0 | 1.5494791666666667 |
| B5_10000_64qam_polar_span_null | 4.604166666666667 | 0.5 | 0.5 | 1 | 1.5494791666666667 |
| B5_10000_qpsk_null | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_10000_qpsk_polar_span_null | 13.8125 | 0.5 | 0.5 | 1 | 4.648437500000001 |
| B5_24000_16qam_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_24000_16qam_polar_span_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.9684244791666666 |
| B5_24000_64qam_null | 1.918402777777778 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.6456163194444445 |
| B5_24000_64qam_polar_span_null | 1.918402777777778 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.6456163194444445 |
| B5_24000_qpsk_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_24000_qpsk_polar_span_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |

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
| Not run (117 declared cases) | — | not_run | — | — | — | — |

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

See [TESTING.md](../TESTING.md) and [source audit/questions](../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 6 / 6 | 79.224 | 1800 | yes |
| quick / selected rerun | 6 / 6 | 77.304 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
