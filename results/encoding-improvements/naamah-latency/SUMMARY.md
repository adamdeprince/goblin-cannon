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
| pass | 36 |
| xfail | 6 |

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
| B5 | 42 | 6 | 0 | 0 |
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
| Not run (372 declared cases) | — | not_run | — | — | — | — |

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
| [B5_encoding_10000_16qam_reference_latency](B5_encoding_10000_16qam_reference_latency/7446529.json) | assert / full | pass | — | — | 2576.67 | 51 |
| [B5_encoding_10000_16qam_soft_latency](B5_encoding_10000_16qam_soft_latency/7446529.json) | assert / full | pass | — | — | 2576.67 | 51 |
| [B5_encoding_10000_bpsk_bch_latency](B5_encoding_10000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 1215.33 | 81 |
| [B5_encoding_10000_bpsk_bpsk_header_reference_latency](B5_encoding_10000_bpsk_bpsk_header_reference_latency/7446529.json) | assert / full | pass | — | — | 782 | 110 |
| [B5_encoding_10000_bpsk_diversity_latency](B5_encoding_10000_bpsk_diversity_latency/7446529.json) | assert / full | pass | — | — | 437.333 | 168 |
| [B5_encoding_10000_bpsk_halfband_control_latency](B5_encoding_10000_bpsk_halfband_control_latency/7446529.json) | assert / full | pass | — | — | 437.333 | 168 |
| [B5_encoding_10000_bpsk_interleave2048_latency](B5_encoding_10000_bpsk_interleave2048_latency/7446529.json) | assert / full | xfail | — | — | 88 | 320 |
| [B5_encoding_10000_bpsk_interleave256_latency](B5_encoding_10000_bpsk_interleave256_latency/7446529.json) | assert / full | xfail | — | — | 706 | 118 |
| [B5_encoding_10000_bpsk_interleave32_latency](B5_encoding_10000_bpsk_interleave32_latency/7446529.json) | assert / full | xfail | — | — | 878 | 93 |
| [B5_encoding_10000_bpsk_k9_half_latency](B5_encoding_10000_bpsk_k9_half_latency/7446529.json) | assert / full | pass | — | — | 878 | 92 |
| [B5_encoding_10000_bpsk_k9_third_latency](B5_encoding_10000_bpsk_k9_third_latency/7446529.json) | assert / full | pass | — | — | 585.333 | 112 |
| [B5_encoding_10000_bpsk_reference_latency](B5_encoding_10000_bpsk_reference_latency/7446529.json) | assert / full | pass | — | — | 878 | 89 |
| [B5_encoding_10000_bpsk_soft_bpsk_header_latency](B5_encoding_10000_bpsk_soft_bpsk_header_latency/7446529.json) | assert / full | pass | — | — | 782 | 110 |
| [B5_encoding_10000_bpsk_soft_latency](B5_encoding_10000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 878 | 89 |
| [B5_encoding_10000_bpsk_walsh8_latency](B5_encoding_10000_bpsk_walsh8_latency/7446529.json) | assert / full | pass | — | — | 328.667 | 155 |
| [B5_encoding_10000_fsk4_guard4_latency](B5_encoding_10000_fsk4_guard4_latency/7446529.json) | assert / full | pass | — | — | 10.4 | 4777 |
| [B5_encoding_10000_fsk4_guard8_latency](B5_encoding_10000_fsk4_guard8_latency/7446529.json) | assert / full | pass | — | — | 6.4 | 7167 |
| [B5_encoding_10000_fsk8_guard4_latency](B5_encoding_10000_fsk8_guard4_latency/7446529.json) | assert / full | pass | — | — | 20 | 2491 |
| [B5_encoding_10000_fsk8_guard8_latency](B5_encoding_10000_fsk8_guard8_latency/7446529.json) | assert / full | pass | — | — | 12.5333 | 3739 |
| [B5_encoding_10000_qpsk_reference_latency](B5_encoding_10000_qpsk_reference_latency/7446529.json) | assert / full | pass | — | — | 1760 | 70 |
| [B5_encoding_10000_qpsk_soft_latency](B5_encoding_10000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 1760 | 70 |
| [B5_encoding_24000_16qam_reference_latency](B5_encoding_24000_16qam_reference_latency/7446529.json) | assert / full | pass | — | — | 2833.33 | 21 |
| [B5_encoding_24000_16qam_soft_latency](B5_encoding_24000_16qam_soft_latency/7446529.json) | assert / full | pass | — | — | 2833.33 | 21 |
| [B5_encoding_24000_bpsk_bch_latency](B5_encoding_24000_bpsk_bch_latency/7446529.json) | assert / full | pass | — | — | 2684.67 | 30 |
| [B5_encoding_24000_bpsk_bpsk_header_reference_latency](B5_encoding_24000_bpsk_bpsk_header_reference_latency/7446529.json) | assert / full | pass | — | — | 1888.67 | 51 |
| [B5_encoding_24000_bpsk_diversity_latency](B5_encoding_24000_bpsk_diversity_latency/7446529.json) | assert / full | pass | — | — | 1054 | 76 |
| [B5_encoding_24000_bpsk_halfband_control_latency](B5_encoding_24000_bpsk_halfband_control_latency/7446529.json) | assert / full | pass | — | — | 1054 | 76 |
| [B5_encoding_24000_bpsk_interleave2048_latency](B5_encoding_24000_bpsk_interleave2048_latency/7446529.json) | assert / full | xfail | — | — | 212 | 198 |
| [B5_encoding_24000_bpsk_interleave256_latency](B5_encoding_24000_bpsk_interleave256_latency/7446529.json) | assert / full | xfail | — | — | 1705.33 | 55 |
| [B5_encoding_24000_bpsk_interleave32_latency](B5_encoding_24000_bpsk_interleave32_latency/7446529.json) | assert / full | xfail | — | — | 2114 | 45 |
| [B5_encoding_24000_bpsk_k9_half_latency](B5_encoding_24000_bpsk_k9_half_latency/7446529.json) | assert / full | pass | — | — | 2114 | 44 |
| [B5_encoding_24000_bpsk_k9_third_latency](B5_encoding_24000_bpsk_k9_third_latency/7446529.json) | assert / full | pass | — | — | 1409.33 | 53 |
| [B5_encoding_24000_bpsk_reference_latency](B5_encoding_24000_bpsk_reference_latency/7446529.json) | assert / full | pass | — | — | 2114 | 43 |
| [B5_encoding_24000_bpsk_soft_bpsk_header_latency](B5_encoding_24000_bpsk_soft_bpsk_header_latency/7446529.json) | assert / full | pass | — | — | 1888.67 | 51 |
| [B5_encoding_24000_bpsk_soft_latency](B5_encoding_24000_bpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 2114 | 43 |
| [B5_encoding_24000_bpsk_walsh8_latency](B5_encoding_24000_bpsk_walsh8_latency/7446529.json) | assert / full | pass | — | — | 792 | 82 |
| [B5_encoding_24000_fsk4_guard4_latency](B5_encoding_24000_fsk4_guard4_latency/7446529.json) | assert / full | pass | — | — | 10.4 | 4777 |
| [B5_encoding_24000_fsk4_guard8_latency](B5_encoding_24000_fsk4_guard8_latency/7446529.json) | assert / full | pass | — | — | 6.4 | 7167 |
| [B5_encoding_24000_fsk8_guard4_latency](B5_encoding_24000_fsk8_guard4_latency/7446529.json) | assert / full | pass | — | — | 20 | 2491 |
| [B5_encoding_24000_fsk8_guard8_latency](B5_encoding_24000_fsk8_guard8_latency/7446529.json) | assert / full | pass | — | — | 12.5333 | 3739 |
| [B5_encoding_24000_qpsk_reference_latency](B5_encoding_24000_qpsk_reference_latency/7446529.json) | assert / full | pass | — | — | 2687.33 | 26 |
| [B5_encoding_24000_qpsk_soft_latency](B5_encoding_24000_qpsk_soft_latency/7446529.json) | assert / full | pass | — | — | 2687.33 | 26 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_encoding_10000_16qam_reference_latency](B5_encoding_10000_16qam_reference_latency/7446529.host.json) | 11.981022999998814 | 51.00844200000054 | 50.312500000000426 | 1.0055003333331314 | 1.0055003333331314 | pass |
| [B5_encoding_10000_16qam_soft_latency](B5_encoding_10000_16qam_soft_latency/7446529.host.json) | 11.973659000000136 | 51.01302100000016 | 50.312500000000426 | 1.0129643333331977 | 1.0129643333331977 | pass |
| [B5_encoding_10000_bpsk_bch_latency](B5_encoding_10000_bpsk_bch_latency/7446529.host.json) | 35.010708000000164 | 81.00201899999959 | 80.50000000000068 | 0.9600083333332066 | 0.9600083333332066 | pass |
| [B5_encoding_10000_bpsk_bpsk_header_reference_latency](B5_encoding_10000_bpsk_bpsk_header_reference_latency/7446529.host.json) | 47.004104999999626 | 110.00178499999969 | 109.54166666666687 | 0.9677433333332743 | 0.9677433333332743 | pass |
| [B5_encoding_10000_bpsk_diversity_latency](B5_encoding_10000_bpsk_diversity_latency/7446529.host.json) | 87.00114599999998 | 168.00134100000008 | 167.16666666666669 | 0.9683029999996222 | 0.9683029999996222 | pass |
| [B5_encoding_10000_bpsk_halfband_control_latency](B5_encoding_10000_bpsk_halfband_control_latency/7446529.host.json) | 87.00113599999959 | 168.00334599999988 | 167.16666666666669 | 0.9616793333333362 | 0.9616793333333362 | pass |
| [B5_encoding_10000_bpsk_interleave2048_latency](B5_encoding_10000_bpsk_interleave2048_latency/7446529.host.json) | 319.78477600000053 | 322.08179600000005 | 47.43750000000002 | 276.76199200000013 | 276.76199200000013 | xfail |
| [B5_encoding_10000_bpsk_interleave256_latency](B5_encoding_10000_bpsk_interleave256_latency/7446529.host.json) | 76.33070099999983 | 118.336836 | 81.04166666666757 | 79.52009799999992 | 79.52009799999992 | xfail |
| [B5_encoding_10000_bpsk_interleave32_latency](B5_encoding_10000_bpsk_interleave32_latency/7446529.host.json) | 50.0405869999998 | 93.04053899999998 | 90.7916666666666 | 4.2479333333331795 | 4.2479333333331795 | xfail |
| [B5_encoding_10000_bpsk_k9_half_latency](B5_encoding_10000_bpsk_k9_half_latency/7446529.host.json) | 50.000216000000044 | 92.03407800000019 | 91.49999999999991 | 0.9917090000000002 | 0.9917090000000002 | pass |
| [B5_encoding_10000_bpsk_k9_third_latency](B5_encoding_10000_bpsk_k9_third_latency/7446529.host.json) | 73.00002500000002 | 112.01173400000019 | 111.68750000000038 | 0.9797050000000098 | 0.9797050000000098 | pass |
| [B5_encoding_10000_bpsk_reference_latency](B5_encoding_10000_bpsk_reference_latency/7446529.host.json) | 47.00070800000012 | 89.00358999999992 | 88.6875000000007 | 0.9820343333335515 | 0.9820343333335515 | pass |
| [B5_encoding_10000_bpsk_soft_bpsk_header_latency](B5_encoding_10000_bpsk_soft_bpsk_header_latency/7446529.host.json) | 47.00207 | 110.00128399999997 | 109.54166666666687 | 0.9629933333323919 | 0.9629933333323919 | pass |
| [B5_encoding_10000_bpsk_soft_latency](B5_encoding_10000_bpsk_soft_latency/7446529.host.json) | 47.00100800000051 | 89.00630499999984 | 88.6875000000007 | 0.9835163333331565 | 0.9835163333331565 | pass |
| [B5_encoding_10000_bpsk_walsh8_latency](B5_encoding_10000_bpsk_walsh8_latency/7446529.host.json) | 147.00556900000007 | 155.00507799999986 | 154.87500000000054 | 0.9634113333332266 | 0.9634113333332266 | pass |
| [B5_encoding_10000_fsk4_guard4_latency](B5_encoding_10000_fsk4_guard4_latency/7446529.host.json) | 3579.0061960000016 | 4777.00798 | 4777.000000000001 | 0.01568399999950998 | 0.01568399999950998 | pass |
| [B5_encoding_10000_fsk4_guard8_latency](B5_encoding_10000_fsk4_guard8_latency/7446529.host.json) | 5365.006132000001 | 7167.006649999999 | 7167 | 0.013245999999526248 | 0.013245999999526248 | pass |
| [B5_encoding_10000_fsk8_guard4_latency](B5_encoding_10000_fsk8_guard4_latency/7446529.host.json) | 1647.004847 | 2491.007429 | 2490.9999999999995 | 0.013232999996944272 | 0.013232999996944272 | pass |
| [B5_encoding_10000_fsk8_guard8_latency](B5_encoding_10000_fsk8_guard8_latency/7446529.host.json) | 2463.0040640000016 | 3739.008858000002 | 3739.000000000001 | 0.011684999997214618 | 0.011684999997214618 | pass |
| [B5_encoding_10000_qpsk_reference_latency](B5_encoding_10000_qpsk_reference_latency/7446529.host.json) | 26.99482799999986 | 70.00496400000067 | 69.18749999999996 | 0.9700633333333784 | 0.9700633333333784 | pass |
| [B5_encoding_10000_qpsk_soft_latency](B5_encoding_10000_qpsk_soft_latency/7446529.host.json) | 26.99152199999999 | 70.00556500000066 | 69.18749999999996 | 0.9742013333333688 | 0.9742013333333688 | pass |
| [B5_encoding_24000_16qam_reference_latency](B5_encoding_24000_16qam_reference_latency/7446529.host.json) | 5.001763000000103 | 21.66000300000004 | 20.95833333333319 | 1.0776506666658747 | 1.0787426666665212 | pass |
| [B5_encoding_24000_16qam_soft_latency](B5_encoding_24000_16qam_soft_latency/7446529.host.json) | 5.015337999999758 | 21.730386000000657 | 20.95833333333319 | 1.1150016666672258 | 1.1158936666664232 | pass |
| [B5_encoding_24000_bpsk_bch_latency](B5_encoding_24000_bpsk_bch_latency/7446529.host.json) | 15.00014800000038 | 30.009092000000237 | 29.39583333333351 | 1.0046516666664118 | 1.0055836666666984 | pass |
| [B5_encoding_24000_bpsk_bpsk_header_reference_latency](B5_encoding_24000_bpsk_bpsk_header_reference_latency/7446529.host.json) | 24.00627799999988 | 51.00384800000057 | 50.499999999999545 | 1.0242476666668665 | 1.0242476666668665 | pass |
| [B5_encoding_24000_bpsk_diversity_latency](B5_encoding_24000_bpsk_diversity_latency/7446529.host.json) | 40.048023000000214 | 75.998534 | 75.10416666666764 | 0.9848763333337729 | 0.9848763333337729 | pass |
| [B5_encoding_24000_bpsk_halfband_control_latency](B5_encoding_24000_bpsk_halfband_control_latency/7446529.host.json) | 40.02973899999995 | 75.99961599999894 | 75.10416666666764 | 0.9835266666673448 | 0.9835266666673448 | pass |
| [B5_encoding_24000_bpsk_interleave2048_latency](B5_encoding_24000_bpsk_interleave2048_latency/7446529.host.json) | 136.5475500000004 | 199.3928060000001 | 26.312499999999517 | 183.30947266666686 | 183.30947266666686 | xfail |
| [B5_encoding_24000_bpsk_interleave256_latency](B5_encoding_24000_bpsk_interleave256_latency/7446529.host.json) | 36.21027100000029 | 55.378054000000176 | 33.77083333333353 | 37.62687066666665 | 37.62687066666665 | xfail |
| [B5_encoding_24000_bpsk_interleave32_latency](B5_encoding_24000_bpsk_interleave32_latency/7446529.host.json) | 24.99823199999973 | 45.02951799999977 | 43.583333333334195 | 2.3758663333328656 | 2.3758663333328656 | xfail |
| [B5_encoding_24000_bpsk_k9_half_latency](B5_encoding_24000_bpsk_k9_half_latency/7446529.host.json) | 25.0000749999999 | 44.05427500000059 | 43.97916666666646 | 1.1031366666669484 | 1.1031366666669484 | pass |
| [B5_encoding_24000_bpsk_k9_third_latency](B5_encoding_24000_bpsk_k9_third_latency/7446529.host.json) | 36.00030399999987 | 53.02788300000039 | 52.604166666666785 | 1.0477906666661596 | 1.0477906666661596 | pass |
| [B5_encoding_24000_bpsk_reference_latency](B5_encoding_24000_bpsk_reference_latency/7446529.host.json) | 24.00034700000031 | 43.00587300000025 | 42.83333333333328 | 1.020820666665756 | 1.020820666665756 | pass |
| [B5_encoding_24000_bpsk_soft_bpsk_header_latency](B5_encoding_24000_bpsk_soft_bpsk_header_latency/7446529.host.json) | 24.007830999998703 | 51.00392800000009 | 50.499999999999545 | 1.0289566666674688 | 1.0289566666674688 | pass |
| [B5_encoding_24000_bpsk_soft_latency](B5_encoding_24000_bpsk_soft_latency/7446529.host.json) | 23.999415000000468 | 43.004360000001185 | 42.83333333333328 | 1.0290066666662767 | 1.0290066666662767 | pass |
| [B5_encoding_24000_bpsk_walsh8_latency](B5_encoding_24000_bpsk_walsh8_latency/7446529.host.json) | 63.99166200000028 | 82.00451399999986 | 81.16666666666661 | 1.0164576666671366 | 1.0164576666671366 | pass |
| [B5_encoding_24000_fsk4_guard4_latency](B5_encoding_24000_fsk4_guard4_latency/7446529.host.json) | 3579.0063960000007 | 4777.006888000003 | 4777.000000000001 | 0.014711000000261265 | 0.014711000000261265 | pass |
| [B5_encoding_24000_fsk4_guard8_latency](B5_encoding_24000_fsk4_guard8_latency/7446529.host.json) | 5365.006303000001 | 7167.005909 | 7167 | 0.012794999999641732 | 0.012794999999641732 | pass |
| [B5_encoding_24000_fsk8_guard4_latency](B5_encoding_24000_fsk8_guard4_latency/7446529.host.json) | 1647.0044160000016 | 2491.007489000001 | 2490.9999999999995 | 0.020926999994117068 | 0.020926999994117068 | pass |
| [B5_encoding_24000_fsk8_guard8_latency](B5_encoding_24000_fsk8_guard8_latency/7446529.host.json) | 2463.0047959999997 | 3739.008408 | 3739.000000000001 | 0.011073999997734063 | 0.011073999997734063 | pass |
| [B5_encoding_24000_qpsk_reference_latency](B5_encoding_24000_qpsk_reference_latency/7446529.host.json) | 9.001592000000613 | 26.01251900000001 | 25.187499999999474 | 1.0386066666665528 | 1.038957666667173 | pass |
| [B5_encoding_24000_qpsk_soft_latency](B5_encoding_24000_qpsk_soft_latency/7446529.host.json) | 9.001722000000045 | 26.0289199999999 | 25.187499999999474 | 1.0454696666664098 | 1.0496776666659713 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_encoding_10000_16qam_reference_latency | host_source_to_framer_ms | 0.0015629999996491506 | 9.595865000001425 | 9.595865000001425 |
| B5_encoding_10000_16qam_reference_latency | host_intake_per_message_ms | 0.0002299999999344493 | 0.002513999999953498 | 0.0034160000000008767 |
| B5_encoding_10000_16qam_reference_latency | host_tx_per_block_ms | 0.002253999999979328 | 0.06784800000048108 | 0.07197600000097282 |
| B5_encoding_10000_16qam_reference_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0012520000005622478 | 0.0021839999995165726 |
| B5_encoding_10000_16qam_reference_latency | host_audio_wait_per_block_ms | 0.9508770000001832 | 1.0029950000003396 | 1.0362380000001892 |
| B5_encoding_10000_16qam_reference_latency | host_rx_per_block_ms | 0.04478500000004715 | 0.7238379999998656 | 1.0028050000000024 |
| B5_encoding_10000_16qam_soft_latency | host_source_to_framer_ms | 0.0014129999996725928 | 9.65378499999936 | 9.65378499999936 |
| B5_encoding_10000_16qam_soft_latency | host_intake_per_message_ms | 0.00019100000070437773 | 0.002143999999981716 | 0.0032759999999999734 |
| B5_encoding_10000_16qam_soft_latency | host_tx_per_block_ms | 0.0022240000001616522 | 0.06499300000006869 | 0.07452000000007786 |
| B5_encoding_10000_16qam_soft_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0009119999999640527 | 0.0013429999999869935 |
| B5_encoding_10000_16qam_soft_latency | host_audio_wait_per_block_ms | 0.9428919999994179 | 1.0507159999999516 | 1.3448509999998137 |
| B5_encoding_10000_16qam_soft_latency | host_rx_per_block_ms | 0.05312100000010034 | 0.703971000000081 | 1.0367000000000015 |
| B5_encoding_10000_bpsk_bch_latency | host_source_to_framer_ms | 4.994989000000061 | 9.038342000000002 | 9.038342000000002 |
| B5_encoding_10000_bpsk_bch_latency | host_intake_per_message_ms | 0.0004499999999296733 | 0.0030759999996021747 | 0.003597000000001016 |
| B5_encoding_10000_bpsk_bch_latency | host_tx_per_block_ms | 0.0015829999995276012 | 0.06840900000071315 | 0.07437000000004579 |
| B5_encoding_10000_bpsk_bch_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0013020000002583743 | 0.0020940000009517235 |
| B5_encoding_10000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.9822760000002262 | 1.0028149999996572 | 1.026190000001037 |
| B5_encoding_10000_bpsk_bch_latency | host_rx_per_block_ms | 0.014687999999374313 | 0.7223559999989249 | 1.0360989999999988 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_source_to_framer_ms | 4.999808999999966 | 23.003884999999833 | 23.003884999999833 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_intake_per_message_ms | 0.0004909999997693149 | 0.0022239999999396076 | 0.0036670000000006003 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_tx_per_block_ms | 0.0015929999999109157 | 0.09835600000052125 | 0.14229900000017892 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012119999999171682 | 0.0013519999999545007 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_audio_wait_per_block_ms | 0.9741209999987177 | 1.0025240000004487 | 1.0386229999994612 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | host_rx_per_block_ms | 0.022823000000116167 | 0.7766169999996464 | 1.118543999999999 |
| B5_encoding_10000_bpsk_diversity_latency | host_source_to_framer_ms | 4.99445800000009 | 18.00325299999983 | 18.00325299999983 |
| B5_encoding_10000_bpsk_diversity_latency | host_intake_per_message_ms | 0.0005810000001105209 | 0.0037269999999534065 | 0.004790000000001043 |
| B5_encoding_10000_bpsk_diversity_latency | host_tx_per_block_ms | 0.0021040000000027703 | 0.11976600000007664 | 0.15348999999997837 |
| B5_encoding_10000_bpsk_diversity_latency | host_channel_per_block_ms | 0.0006909999985538207 | 0.0012720000004406984 | 0.0014530000012058508 |
| B5_encoding_10000_bpsk_diversity_latency | host_audio_wait_per_block_ms | 0.9641620000002682 | 0.9988579999999914 | 1.0343050000010123 |
| B5_encoding_10000_bpsk_diversity_latency | host_rx_per_block_ms | 0.03226099999986687 | 3.3277790000001417 | 3.6019679999999 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_source_to_framer_ms | 4.749094999999759 | 18.002050999999852 | 18.002050999999852 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_intake_per_message_ms | 0.0004909999999913595 | 0.002123999999992243 | 0.0050290000000001445 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_tx_per_block_ms | 0.0014129999996725928 | 0.11812300000002551 | 0.13588599999997397 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0012119999990289898 | 0.0014530000003176724 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_audio_wait_per_block_ms | 0.9806530000000535 | 1.0041680000001385 | 1.1229420000002932 |
| B5_encoding_10000_bpsk_halfband_control_latency | host_rx_per_block_ms | 0.01652100000004708 | 1.5955659999997707 | 1.9405479999999864 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_source_to_framer_ms | 5.665486999999914 | 8.962157000000001 | 8.962157000000001 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_intake_per_message_ms | 0.0004709999998908643 | 0.0029549999999989307 | 0.00338599999999932 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_tx_per_block_ms | 0.0015630000000030342 | 0.06616499999978487 | 0.07262699999999178 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.001292000000319149 | 0.001893000000002809 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_audio_wait_per_block_ms | 0.9825169999999606 | 1.0019439999995328 | 1.032782000000232 |
| B5_encoding_10000_bpsk_interleave2048_latency | host_rx_per_block_ms | 0.014567999999992587 | 1.9348869999999962 | 2.122149999999934 |
| B5_encoding_10000_bpsk_interleave256_latency | host_source_to_framer_ms | 4.67356199999891 | 9.668731999999736 | 9.668731999999736 |
| B5_encoding_10000_bpsk_interleave256_latency | host_intake_per_message_ms | 0.0004310000001339631 | 0.0019430000000042469 | 0.0033370000000008254 |
| B5_encoding_10000_bpsk_interleave256_latency | host_tx_per_block_ms | 0.0015530000005981037 | 0.06798800000007432 | 0.07030199999924491 |
| B5_encoding_10000_bpsk_interleave256_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.00127199999955252 | 0.001563000000009973 |
| B5_encoding_10000_bpsk_interleave256_latency | host_audio_wait_per_block_ms | 0.9825570000003836 | 1.0017929999985853 | 1.028894000000058 |
| B5_encoding_10000_bpsk_interleave256_latency | host_rx_per_block_ms | 0.014536999999981148 | 0.6724610000001796 | 1.0359580000000035 |
| B5_encoding_10000_bpsk_interleave32_latency | host_source_to_framer_ms | 4.999118000000635 | 19.015605999999963 | 19.015605999999963 |
| B5_encoding_10000_bpsk_interleave32_latency | host_intake_per_message_ms | 0.000480999999996623 | 0.00285600000005104 | 0.0036469999999989844 |
| B5_encoding_10000_bpsk_interleave32_latency | host_tx_per_block_ms | 0.0015819999994448608 | 0.06540300000068555 | 0.07193599999943956 |
| B5_encoding_10000_bpsk_interleave32_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012429999998175845 | 0.010108999999758339 |
| B5_encoding_10000_bpsk_interleave32_latency | host_audio_wait_per_block_ms | 0.9820659999999481 | 1.000420000000446 | 1.0315500000004363 |
| B5_encoding_10000_bpsk_interleave32_latency | host_rx_per_block_ms | 0.014598000000032307 | 0.7173150000001627 | 1.0422289999999987 |
| B5_encoding_10000_bpsk_k9_half_latency | host_source_to_framer_ms | 4.990701999999736 | 19.055815000000198 | 19.055815000000198 |
| B5_encoding_10000_bpsk_k9_half_latency | host_intake_per_message_ms | 0.0005000000005139782 | 0.0026050000000010093 | 0.002836000000006056 |
| B5_encoding_10000_bpsk_k9_half_latency | host_tx_per_block_ms | 0.0016029999994060518 | 0.06711699999950582 | 0.07076400000000094 |
| B5_encoding_10000_bpsk_k9_half_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.001321999999998047 | 0.0017529999993826095 |
| B5_encoding_10000_bpsk_k9_half_latency | host_audio_wait_per_block_ms | 0.9432729999989675 | 1.0010220000000736 | 1.0165520000000003 |
| B5_encoding_10000_bpsk_k9_half_latency | host_rx_per_block_ms | 0.05351200000003331 | 0.7216440000004098 | 1.0466280000000008 |
| B5_encoding_10000_bpsk_k9_third_latency | host_source_to_framer_ms | 4.986986000000471 | 9.033883000000003 | 9.033883000000003 |
| B5_encoding_10000_bpsk_k9_third_latency | host_intake_per_message_ms | 0.00048099999894191114 | 0.0018629999996022661 | 0.003436000000000758 |
| B5_encoding_10000_bpsk_k9_third_latency | host_tx_per_block_ms | 0.001573000000032465 | 0.06519300000018546 | 0.06947099999976558 |
| B5_encoding_10000_bpsk_k9_third_latency | host_channel_per_block_ms | 0.0006710000004517269 | 0.0008610000001851859 | 0.0010219999992955309 |
| B5_encoding_10000_bpsk_k9_third_latency | host_audio_wait_per_block_ms | 0.9544439999995546 | 0.9996189999998961 | 1.028043 |
| B5_encoding_10000_bpsk_k9_third_latency | host_rx_per_block_ms | 0.042270000000232955 | 0.7184779999995783 | 1.0323709999999973 |
| B5_encoding_10000_bpsk_reference_latency | host_source_to_framer_ms | 4.999258999999867 | 19.025006000000122 | 19.025006000000122 |
| B5_encoding_10000_bpsk_reference_latency | host_intake_per_message_ms | 0.0004709999998908643 | 0.0025640000000382024 | 0.0033259999999996764 |
| B5_encoding_10000_bpsk_reference_latency | host_tx_per_block_ms | 0.001582999999999446 | 0.06647499999967721 | 0.07487100000003188 |
| B5_encoding_10000_bpsk_reference_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0012220000000784381 | 0.0016829999998080325 |
| B5_encoding_10000_bpsk_reference_latency | host_audio_wait_per_block_ms | 0.9743210000010549 | 1.0005810000013327 | 1.0409969999998214 |
| B5_encoding_10000_bpsk_reference_latency | host_rx_per_block_ms | 0.022633000000382708 | 0.7212930000000117 | 0.8559269999999994 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_source_to_framer_ms | 4.999349000000208 | 23.004737000000162 | 23.004737000000162 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_intake_per_message_ms | 0.00043999999999044803 | 0.0020539999998625547 | 0.003476999999999994 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_tx_per_block_ms | 0.0015730000004765543 | 0.09624200000146743 | 0.13344200000009465 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_channel_per_block_ms | 0.0006819999999185811 | 0.0009819999995386297 | 0.0014930000000745736 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_audio_wait_per_block_ms | 0.972709000000016 | 1.0005010000000425 | 1.1566860000002954 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | host_rx_per_block_ms | 0.024315999999302562 | 0.8340960000001729 | 1.2334509999999965 |
| B5_encoding_10000_bpsk_soft_latency | host_source_to_framer_ms | 4.998778000000037 | 19.024845999999982 | 19.024845999999982 |
| B5_encoding_10000_bpsk_soft_latency | host_intake_per_message_ms | 0.0004909999997693149 | 0.0029359999995648423 | 0.0034869999999999346 |
| B5_encoding_10000_bpsk_soft_latency | host_tx_per_block_ms | 0.001592999998578648 | 0.08344799999981944 | 0.12575700000000412 |
| B5_encoding_10000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.001292999999513711 | 0.020308000000746063 |
| B5_encoding_10000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.9724580000005645 | 1.0017629999999889 | 1.0344350000000002 |
| B5_encoding_10000_bpsk_soft_latency | host_rx_per_block_ms | 0.024516999999946165 | 0.7198499999999664 | 0.950867000000001 |
| B5_encoding_10000_bpsk_walsh8_latency | host_source_to_framer_ms | 4.9988380000005606 | 9.039334 | 9.039334 |
| B5_encoding_10000_bpsk_walsh8_latency | host_intake_per_message_ms | 0.000460999999951639 | 0.002494000000000454 | 0.002615000000538714 |
| B5_encoding_10000_bpsk_walsh8_latency | host_tx_per_block_ms | 0.0016340000001946464 | 0.0685090000001054 | 0.07665499999998104 |
| B5_encoding_10000_bpsk_walsh8_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0009319999989543248 | 0.03559700000010935 |
| B5_encoding_10000_bpsk_walsh8_latency | host_audio_wait_per_block_ms | 0.9789600000003063 | 1.0039769999998782 | 1.1748310000000428 |
| B5_encoding_10000_bpsk_walsh8_latency | host_rx_per_block_ms | 0.017623999999827333 | 0.709350000000164 | 1.0365589999999993 |
| B5_encoding_10000_fsk4_guard4_latency | host_source_to_framer_ms | 4.001912999999746 | 8.0018829999986 | 8.0018829999986 |
| B5_encoding_10000_fsk4_guard4_latency | host_intake_per_message_ms | 0.0004409999996290992 | 0.0019429999973397116 | 0.0035769999999994 |
| B5_encoding_10000_fsk4_guard4_latency | host_tx_per_block_ms | 0.00037999999946691787 | 0.0029149999996036513 | 0.010269999999978907 |
| B5_encoding_10000_fsk4_guard4_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0012230000017154907 | 0.0016430000009393098 |
| B5_encoding_10000_fsk4_guard4_latency | host_audio_wait_per_block_ms | 0.996975000000011 | 1.0022139999996682 | 1.1625570000000016 |
| B5_encoding_10000_fsk4_guard4_latency | host_rx_per_block_ms | 0.0012520000005622478 | 0.006923000000824686 | 0.39014700000006286 |
| B5_encoding_10000_fsk4_guard8_latency | host_source_to_framer_ms | 4.00165299999955 | 8.00207300000011 | 8.00207300000011 |
| B5_encoding_10000_fsk4_guard8_latency | host_intake_per_message_ms | 0.0003409999997927571 | 0.0016630000001516265 | 0.004749000000000073 |
| B5_encoding_10000_fsk4_guard8_latency | host_tx_per_block_ms | 0.00037099999961043295 | 0.001452999999429494 | 0.014506999999941428 |
| B5_encoding_10000_fsk4_guard8_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0008719999993189731 | 0.001353000000037241 |
| B5_encoding_10000_fsk4_guard8_latency | host_audio_wait_per_block_ms | 0.9970139999992966 | 0.9998790000018687 | 1.0226830000004128 |
| B5_encoding_10000_fsk4_guard8_latency | host_rx_per_block_ms | 0.0012320000006837972 | 0.00621199999972788 | 0.40182899999985366 |
| B5_encoding_10000_fsk8_guard4_latency | host_source_to_framer_ms | 6.00113099999966 | 8.005069000000088 | 8.005069000000088 |
| B5_encoding_10000_fsk8_guard4_latency | host_intake_per_message_ms | 0.00037099999872225453 | 0.0015429999999927446 | 0.0036870000000004816 |
| B5_encoding_10000_fsk8_guard4_latency | host_tx_per_block_ms | 0.0003710000022749682 | 0.003225999998690554 | 0.012663999999995568 |
| B5_encoding_10000_fsk8_guard4_latency | host_channel_per_block_ms | 0.0006909999998860883 | 0.000851999999995634 | 0.0011820000000994924 |
| B5_encoding_10000_fsk8_guard4_latency | host_audio_wait_per_block_ms | 0.9960620000000198 | 0.9989179999969622 | 1.048541000000014 |
| B5_encoding_10000_fsk8_guard4_latency | host_rx_per_block_ms | 0.002144999999842412 | 0.009888000001012642 | 0.4107469999999891 |
| B5_encoding_10000_fsk8_guard8_latency | host_source_to_framer_ms | 4.002143999999319 | 12.004107000000097 | 12.004107000000097 |
| B5_encoding_10000_fsk8_guard8_latency | host_intake_per_message_ms | 0.00036100000011529687 | 0.0019639999990772594 | 0.004368000000001121 |
| B5_encoding_10000_fsk8_guard8_latency | host_tx_per_block_ms | 0.00037099999961043295 | 0.0025849999971683246 | 0.012703999999974513 |
| B5_encoding_10000_fsk8_guard8_latency | host_channel_per_block_ms | 0.0006810000030554875 | 0.0009220000016796348 | 0.0015419999996879596 |
| B5_encoding_10000_fsk8_guard8_latency | host_audio_wait_per_block_ms | 0.9961029999985271 | 1.0014229999981694 | 1.0288849999966487 |
| B5_encoding_10000_fsk8_guard8_latency | host_rx_per_block_ms | 0.00214400000064785 | 0.010500000000135401 | 0.40086699999997144 |
| B5_encoding_10000_qpsk_reference_latency | host_source_to_framer_ms | 4.988196999999417 | 9.036859000000064 | 9.036859000000064 |
| B5_encoding_10000_qpsk_reference_latency | host_intake_per_message_ms | 0.0004009999994281088 | 0.0030060000000275977 | 0.0031560000000041555 |
| B5_encoding_10000_qpsk_reference_latency | host_tx_per_block_ms | 0.001984000000065933 | 0.06659600000036292 | 0.0712940000013873 |
| B5_encoding_10000_qpsk_reference_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012829999995744856 | 0.0015030000000137989 |
| B5_encoding_10000_qpsk_reference_latency | host_audio_wait_per_block_ms | 0.9658759999999766 | 1.0032259999999127 | 1.0435920000000376 |
| B5_encoding_10000_qpsk_reference_latency | host_rx_per_block_ms | 0.03077900000025835 | 0.721262999999972 | 0.7572009999998741 |
| B5_encoding_10000_qpsk_soft_latency | host_source_to_framer_ms | 4.985151999999937 | 9.075633 | 9.075633 |
| B5_encoding_10000_qpsk_soft_latency | host_intake_per_message_ms | 0.00031999999983156613 | 0.0033360000002424783 | 0.003516000000036712 |
| B5_encoding_10000_qpsk_soft_latency | host_tx_per_block_ms | 0.0019729999998219228 | 0.0665650000009066 | 0.07789699999971589 |
| B5_encoding_10000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0013219999999147802 | 0.001463000000034853 |
| B5_encoding_10000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.9619269999999736 | 1.0012829999999084 | 1.0439430000008798 |
| B5_encoding_10000_qpsk_soft_latency | host_rx_per_block_ms | 0.03469499999964043 | 0.7209429999996964 | 1.0736289999999995 |
| B5_encoding_24000_16qam_reference_latency | host_source_to_framer_ms | 0.0028849999997859754 | 9.718746999999972 | 9.74140900000009 |
| B5_encoding_24000_16qam_reference_latency | host_intake_per_message_ms | 0.00020000000056086265 | 0.0015030000000137989 | 0.003956999999998878 |
| B5_encoding_24000_16qam_reference_latency | host_tx_per_block_ms | 0.015719999999996848 | 0.23112700000016417 | 0.2401739999999819 |
| B5_encoding_24000_16qam_reference_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.001111999999636737 | 0.0015929999999976518 |
| B5_encoding_24000_16qam_reference_latency | host_audio_wait_per_block_ms | 0.8924569999999576 | 1.0002700000004694 | 1.029806 |
| B5_encoding_24000_16qam_reference_latency | host_rx_per_block_ms | 0.09016099999925586 | 0.7247289999998685 | 1.1387019999999983 |
| B5_encoding_24000_16qam_soft_latency | host_source_to_framer_ms | 0.002555000000015184 | 9.813635999999626 | 9.818935999999834 |
| B5_encoding_24000_16qam_soft_latency | host_intake_per_message_ms | 0.0002109999996946499 | 0.014657000000362075 | 0.015528999999903093 |
| B5_encoding_24000_16qam_soft_latency | host_tx_per_block_ms | 0.01012899999963679 | 0.23078600000014937 | 0.28610099999992755 |
| B5_encoding_24000_16qam_soft_latency | host_channel_per_block_ms | 0.0006809999995027738 | 0.0012820000000468568 | 0.01514800000013139 |
| B5_encoding_24000_16qam_soft_latency | host_audio_wait_per_block_ms | 0.8937989999999729 | 1.0001799999983518 | 1.0261300000000002 |
| B5_encoding_24000_16qam_soft_latency | host_rx_per_block_ms | 0.08938899999999528 | 0.802306000000641 | 0.9254989999999997 |
| B5_encoding_24000_bpsk_bch_latency | host_source_to_framer_ms | 2.0060010000015893 | 9.756277999999341 | 9.75850200000039 |
| B5_encoding_24000_bpsk_bch_latency | host_intake_per_message_ms | 0.00022099999963387518 | 0.003496999999999875 | 0.0036269999998950198 |
| B5_encoding_24000_bpsk_bch_latency | host_tx_per_block_ms | 0.014367000000015118 | 0.2341329999993036 | 0.2427389999999363 |
| B5_encoding_24000_bpsk_bch_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0011620000002210418 | 0.01066999999999041 |
| B5_encoding_24000_bpsk_bch_latency | host_audio_wait_per_block_ms | 0.9599040000000114 | 1.0027350000001434 | 1.1327910000000774 |
| B5_encoding_24000_bpsk_bch_latency | host_rx_per_block_ms | 0.023894999999996003 | 0.7636430000008687 | 0.9596629999999995 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_source_to_framer_ms | 4.833644999999942 | 9.973608000000024 | 9.973608000000024 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_intake_per_message_ms | 0.0002500000000349445 | 0.0020439999999233294 | 0.0037869999999998877 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_tx_per_block_ms | 0.014657999999556637 | 0.35086299999953496 | 0.3562740000000453 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011719999997161779 | 0.0017130000000697976 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_audio_wait_per_block_ms | 0.9425109999998682 | 1.0077250000000149 | 1.0457360000000193 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | host_rx_per_block_ms | 0.04140799999996503 | 0.9555059999999393 | 1.0800410000000003 |
| B5_encoding_24000_bpsk_diversity_latency | host_source_to_framer_ms | 4.02217099999902 | 10.108602999999993 | 10.108602999999993 |
| B5_encoding_24000_bpsk_diversity_latency | host_intake_per_message_ms | 0.0005610000002320703 | 0.004198000000066315 | 0.005420000000810887 |
| B5_encoding_24000_bpsk_diversity_latency | host_tx_per_block_ms | 0.002443999999712787 | 0.06196800000068947 | 0.06469200000047692 |
| B5_encoding_24000_bpsk_diversity_latency | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012520000005622478 | 0.00395800000063673 |
| B5_encoding_24000_bpsk_diversity_latency | host_audio_wait_per_block_ms | 0.9477709999998751 | 0.9996600000015121 | 1.0734280000000984 |
| B5_encoding_24000_bpsk_diversity_latency | host_rx_per_block_ms | 0.04788100000041595 | 1.369568000001209 | 1.5667109999999984 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_source_to_framer_ms | 4.011821000000637 | 9.642822999999968 | 9.642822999999968 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_intake_per_message_ms | 0.00042100000108291624 | 0.0018440000002506451 | 0.003656999999998925 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_tx_per_block_ms | 0.0016829999998080325 | 0.05663700000013705 | 0.06099500000011915 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0008019999988562176 | 0.0013629999999764664 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_audio_wait_per_block_ms | 0.9694119999998918 | 0.9995089999996765 | 1.0147979999999999 |
| B5_encoding_24000_bpsk_halfband_control_latency | host_rx_per_block_ms | 0.02711199999971825 | 0.6473040000001262 | 0.9700729999999949 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_source_to_framer_ms | 4.004407000000043 | 66.98147300000001 | 66.98147300000001 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_intake_per_message_ms | 0.0005509999994046666 | 0.0036459999999995107 | 0.003928000000041898 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_tx_per_block_ms | 0.014307000000712833 | 0.25077399999950956 | 0.28306499999997126 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0012330000001004038 | 0.0015030000000137989 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_audio_wait_per_block_ms | 0.9608060000001473 | 1.0029149999999931 | 1.0372109999998713 |
| B5_encoding_24000_bpsk_interleave2048_latency | host_rx_per_block_ms | 0.023394000000287463 | 1.6445679999996798 | 2.0134350000002854 |
| B5_encoding_24000_bpsk_interleave256_latency | host_source_to_framer_ms | 4.78437099999951 | 9.766697999999963 | 9.766697999999963 |
| B5_encoding_24000_bpsk_interleave256_latency | host_intake_per_message_ms | 0.00036099999967120766 | 0.0036170000000008973 | 0.003706999999408822 |
| B5_encoding_24000_bpsk_interleave256_latency | host_tx_per_block_ms | 0.01431699999976388 | 0.23361099999999468 | 0.2445630000003085 |
| B5_encoding_24000_bpsk_interleave256_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.001251999998785891 | 0.0018330000000066349 |
| B5_encoding_24000_bpsk_interleave256_latency | host_audio_wait_per_block_ms | 0.9608060000001473 | 1.0029049999999984 | 1.0343949999995772 |
| B5_encoding_24000_bpsk_interleave256_latency | host_rx_per_block_ms | 0.023394000000287463 | 0.785443999999913 | 1.131939000000002 |
| B5_encoding_24000_bpsk_interleave32_latency | host_source_to_framer_ms | 4.0290140000001085 | 9.079027999999933 | 9.079027999999933 |
| B5_encoding_24000_bpsk_interleave32_latency | host_intake_per_message_ms | 0.00025999999930803597 | 0.003876999999999353 | 0.00706299999997384 |
| B5_encoding_24000_bpsk_interleave32_latency | host_tx_per_block_ms | 0.014436999999922762 | 0.23440199999980038 | 0.24357999999979896 |
| B5_encoding_24000_bpsk_interleave32_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012530000006449882 | 0.0018329999997845903 |
| B5_encoding_24000_bpsk_interleave32_latency | host_audio_wait_per_block_ms | 0.9575599999998019 | 1.0027049999998816 | 1.0742900000000333 |
| B5_encoding_24000_bpsk_interleave32_latency | host_rx_per_block_ms | 0.02504800000036056 | 0.7774790000003584 | 1.2133330000000004 |
| B5_encoding_24000_bpsk_k9_half_latency | host_source_to_framer_ms | 4.316627999999767 | 9.76301000000035 | 9.76301000000035 |
| B5_encoding_24000_bpsk_k9_half_latency | host_intake_per_message_ms | 0.00023000000037853852 | 0.0019640000008536163 | 0.0035669999999994595 |
| B5_encoding_24000_bpsk_k9_half_latency | host_tx_per_block_ms | 0.014658000001332994 | 0.23059499999966704 | 0.23772900000018637 |
| B5_encoding_24000_bpsk_k9_half_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011220000004641406 | 0.0015030000000137989 |
| B5_encoding_24000_bpsk_k9_half_latency | host_audio_wait_per_block_ms | 0.8746229999996302 | 1.0019640000002994 | 1.1664439999998777 |
| B5_encoding_24000_bpsk_k9_half_latency | host_rx_per_block_ms | 0.1092859999998197 | 0.7950020000002667 | 1.1906410000000027 |
| B5_encoding_24000_bpsk_k9_third_latency | host_source_to_framer_ms | 4.980332000000143 | 9.704680000000465 | 9.704680000000465 |
| B5_encoding_24000_bpsk_k9_third_latency | host_intake_per_message_ms | 0.0004209999993065594 | 0.003555999999349524 | 0.0038370000000013255 |
| B5_encoding_24000_bpsk_k9_third_latency | host_tx_per_block_ms | 0.014698000001089895 | 0.24728799999884643 | 0.2865519999999955 |
| B5_encoding_24000_bpsk_k9_third_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0011020000001416008 | 0.0017439999999979694 |
| B5_encoding_24000_bpsk_k9_third_latency | host_audio_wait_per_block_ms | 0.881846000000186 | 1.000570999999617 | 1.0299269999999998 |
| B5_encoding_24000_bpsk_k9_third_latency | host_rx_per_block_ms | 0.10193299999983196 | 0.80429999999998 | 1.1189040000000003 |
| B5_encoding_24000_bpsk_reference_latency | host_source_to_framer_ms | 4.36665199999986 | 9.659385000000853 | 9.659385000000853 |
| B5_encoding_24000_bpsk_reference_latency | host_intake_per_message_ms | 0.0003010000000358559 | 0.003706999999408822 | 0.004597999999999755 |
| B5_encoding_24000_bpsk_reference_latency | host_tx_per_block_ms | 0.014686999999291572 | 0.24914099999939765 | 0.2621860000004972 |
| B5_encoding_24000_bpsk_reference_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.0013529999999262188 | 0.00341600000020037 |
| B5_encoding_24000_bpsk_reference_latency | host_audio_wait_per_block_ms | 0.9419900000002812 | 1.0033360000001323 | 1.0370589999997293 |
| B5_encoding_24000_bpsk_reference_latency | host_rx_per_block_ms | 0.041798999999898 | 0.7128370000000217 | 1.058029000000002 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_source_to_framer_ms | 4.913544999999964 | 10.04685700000002 | 10.04685700000002 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_intake_per_message_ms | 0.00027099999933000163 | 0.0021340000000008574 | 0.0021649999997208624 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_tx_per_block_ms | 0.014676999999796436 | 0.35152400000004747 | 0.3571149999999079 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012729999996352603 | 0.0014029999997333675 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_audio_wait_per_block_ms | 0.9382430000002273 | 1.0037770000002055 | 1.104877000000004 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | host_rx_per_block_ms | 0.04557599999976958 | 1.0338839999999294 | 1.1705229999999998 |
| B5_encoding_24000_bpsk_soft_latency | host_source_to_framer_ms | 4.2606920000007875 | 9.768640999999079 | 9.768640999999079 |
| B5_encoding_24000_bpsk_soft_latency | host_intake_per_message_ms | 0.00021000000005599873 | 0.0035469999999995783 | 0.0040779999999074334 |
| B5_encoding_24000_bpsk_soft_latency | host_tx_per_block_ms | 0.014667999999939951 | 0.2293130000001753 | 0.234212999999997 |
| B5_encoding_24000_bpsk_soft_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.000912000000075075 | 0.0014930000000745736 |
| B5_encoding_24000_bpsk_soft_latency | host_audio_wait_per_block_ms | 0.9377719999985601 | 0.9994789999998588 | 1.0483309999997914 |
| B5_encoding_24000_bpsk_soft_latency | host_rx_per_block_ms | 0.04599699999907614 | 0.7792730000000248 | 1.1251959999999985 |
| B5_encoding_24000_bpsk_walsh8_latency | host_source_to_framer_ms | 4.999728000000481 | 23.008421999999975 | 23.008421999999975 |
| B5_encoding_24000_bpsk_walsh8_latency | host_intake_per_message_ms | 0.0005410000003536197 | 0.0024149999999778515 | 0.0035059999999986075 |
| B5_encoding_24000_bpsk_walsh8_latency | host_tx_per_block_ms | 0.014347000000469734 | 0.2331710000005316 | 0.2553929999997706 |
| B5_encoding_24000_bpsk_walsh8_latency | host_channel_per_block_ms | 0.0006810000012791306 | 0.0012730000005234388 | 0.001793999999222251 |
| B5_encoding_24000_bpsk_walsh8_latency | host_audio_wait_per_block_ms | 0.9521689999996141 | 1.001994000000117 | 1.0233239999997146 |
| B5_encoding_24000_bpsk_walsh8_latency | host_rx_per_block_ms | 0.03175999999971424 | 0.7857149999996871 | 1.1482800000000015 |
| B5_encoding_24000_fsk4_guard4_latency | host_source_to_framer_ms | 4.0015430000011065 | 8.001843000002395 | 8.001843000002395 |
| B5_encoding_24000_fsk4_guard4_latency | host_intake_per_message_ms | 0.0004410000009613668 | 0.0022839999989088255 | 0.0033870000000005285 |
| B5_encoding_24000_fsk4_guard4_latency | host_tx_per_block_ms | 0.00037100000049861137 | 0.0032760000001630374 | 0.01808400000014032 |
| B5_encoding_24000_fsk4_guard4_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.001241999999734844 | 0.0014829999983589914 |
| B5_encoding_24000_fsk4_guard4_latency | host_audio_wait_per_block_ms | 0.9970040000002456 | 1.0254779999989694 | 1.0438119999998108 |
| B5_encoding_24000_fsk4_guard4_latency | host_rx_per_block_ms | 0.001241999999734844 | 0.007434000000472452 | 0.4721420000000087 |
| B5_encoding_24000_fsk4_guard8_latency | host_source_to_framer_ms | 4.001854000000193 | 8.002483999999477 | 8.002483999999477 |
| B5_encoding_24000_fsk4_guard8_latency | host_intake_per_message_ms | 0.0003399999997100167 | 0.0015929999968022912 | 0.005129000000001285 |
| B5_encoding_24000_fsk4_guard8_latency | host_tx_per_block_ms | 0.0003699999999717818 | 0.0011820000000994924 | 0.015239000000111247 |
| B5_encoding_24000_fsk4_guard8_latency | host_channel_per_block_ms | 0.0006819999995855142 | 0.000851000000023916 | 0.0014429999999999996 |
| B5_encoding_24000_fsk4_guard8_latency | host_audio_wait_per_block_ms | 0.9970149999993794 | 0.9994989999999593 | 1.031248999998624 |
| B5_encoding_24000_fsk4_guard8_latency | host_rx_per_block_ms | 0.001232000002460154 | 0.005941000001286056 | 0.3842259999999875 |
| B5_encoding_24000_fsk8_guard4_latency | host_source_to_framer_ms | 6.001773000000377 | 8.004658000000052 | 8.004658000000052 |
| B5_encoding_24000_fsk8_guard4_latency | host_intake_per_message_ms | 0.00036099999967120766 | 0.0016129999984570986 | 0.004568999999999407 |
| B5_encoding_24000_fsk8_guard4_latency | host_tx_per_block_ms | 0.000370999999999011 | 0.003125999999298301 | 0.01185199999997888 |
| B5_encoding_24000_fsk8_guard4_latency | host_channel_per_block_ms | 0.0006810000030554875 | 0.0008020000024089313 | 0.0014129999996725928 |
| B5_encoding_24000_fsk8_guard4_latency | host_audio_wait_per_block_ms | 0.9960819999994541 | 0.998878000000758 | 1.0225920000017652 |
| B5_encoding_24000_fsk8_guard4_latency | host_rx_per_block_ms | 0.002154000000587075 | 0.009928999999964105 | 0.3965989999999975 |
| B5_encoding_24000_fsk8_guard8_latency | host_source_to_framer_ms | 4.001603000000742 | 12.00384600000004 | 12.00384600000004 |
| B5_encoding_24000_fsk8_guard8_latency | host_intake_per_message_ms | 0.0003409999997927571 | 0.0017139999997084487 | 0.004639000000000726 |
| B5_encoding_24000_fsk8_guard8_latency | host_tx_per_block_ms | 0.00037099999961043295 | 0.0026849999983369344 | 0.012845000000094586 |
| B5_encoding_24000_fsk8_guard8_latency | host_channel_per_block_ms | 0.0006810000030554875 | 0.0008520000012168794 | 0.001292999999999996 |
| B5_encoding_24000_fsk8_guard8_latency | host_audio_wait_per_block_ms | 0.9960930000012524 | 0.9987480000006599 | 1.0214809999986585 |
| B5_encoding_24000_fsk8_guard8_latency | host_rx_per_block_ms | 0.002143999999981716 | 0.009477999999063513 | 0.3859600000000185 |
| B5_encoding_24000_qpsk_reference_latency | host_source_to_framer_ms | 0.005018999999606422 | 6.697436999999917 | 6.702506999999969 |
| B5_encoding_24000_qpsk_reference_latency | host_intake_per_message_ms | 0.0002299999994903601 | 0.0019240000000003699 | 0.003727000000000244 |
| B5_encoding_24000_qpsk_reference_latency | host_tx_per_block_ms | 0.01510899999956905 | 0.2317879999997885 | 0.2386709999999681 |
| B5_encoding_24000_qpsk_reference_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0012630000005842135 | 0.0015019999999310585 |
| B5_encoding_24000_qpsk_reference_latency | host_audio_wait_per_block_ms | 0.9249579999996982 | 1.0025749999993394 | 1.1073119999999992 |
| B5_encoding_24000_qpsk_reference_latency | host_rx_per_block_ms | 0.05834000000071171 | 0.7162739999997392 | 1.053690999999999 |
| B5_encoding_24000_qpsk_soft_latency | host_source_to_framer_ms | 0.004819999999128299 | 6.760525999999878 | 6.7622899999992825 |
| B5_encoding_24000_qpsk_soft_latency | host_intake_per_message_ms | 0.00021100000147100673 | 0.0019229999999037517 | 0.0036170000000008973 |
| B5_encoding_24000_qpsk_soft_latency | host_tx_per_block_ms | 0.01508799999960786 | 0.23533500000016971 | 0.24420099999988842 |
| B5_encoding_24000_qpsk_soft_latency | host_channel_per_block_ms | 0.0006810000003909522 | 0.0011220000000200514 | 0.0015019999999310585 |
| B5_encoding_24000_qpsk_soft_latency | host_audio_wait_per_block_ms | 0.9161220000004633 | 1.000420000000446 | 1.0432009999998826 |
| B5_encoding_24000_qpsk_soft_latency | host_rx_per_block_ms | 0.06718700000085676 | 0.7881489999999047 | 0.9732099999999987 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_encoding_10000_16qam_reference_latency | 6.90625 | 0.5 | 0.5 | 0 | 2.3242187500000004 |
| B5_encoding_10000_16qam_soft_latency | 6.90625 | 0.5 | 0.5 | 0 | 2.3242187500000004 |
| B5_encoding_10000_bpsk_bch_latency | 20.028125 | 0.5 | 0.5 | 0 | 6.740234375 |
| B5_encoding_10000_bpsk_bpsk_header_reference_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_diversity_latency | 55.25 | 1 | 1 | 0 | 18.593750000000004 |
| B5_encoding_10000_bpsk_halfband_control_latency | 55.25 | 1 | 1 | 0 | 18.593750000000004 |
| B5_encoding_10000_bpsk_interleave2048_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_interleave256_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_interleave32_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_k9_half_latency | 27.625 | 0.5 | 0.5 | 0 | 11.953125 |
| B5_encoding_10000_bpsk_k9_third_latency | 41.4375 | 0.5 | 0.5 | 0 | 17.929687500000004 |
| B5_encoding_10000_bpsk_reference_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_soft_bpsk_header_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_soft_latency | 27.625 | 0.5 | 0.5 | 0 | 9.296875000000002 |
| B5_encoding_10000_bpsk_walsh8_latency | 73.66666666666667 | 0.5 | 0.5 | 0 | 24.791666666666668 |
| B5_encoding_10000_fsk4_guard4_latency | 2782 | 0 | 0 | 0 | 936.25 |
| B5_encoding_10000_fsk4_guard8_latency | 4173.000000000001 | 0 | 0 | 0 | 1404.3750000000002 |
| B5_encoding_10000_fsk8_guard4_latency | 1473.3333333333333 | 0 | 0 | 0 | 495.8333333333333 |
| B5_encoding_10000_fsk8_guard8_latency | 2210 | 0 | 0 | 0 | 743.75 |
| B5_encoding_10000_qpsk_reference_latency | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_encoding_10000_qpsk_soft_latency | 13.8125 | 0.5 | 0.5 | 0 | 4.648437500000001 |
| B5_encoding_24000_16qam_reference_latency | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_encoding_24000_16qam_soft_latency | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_encoding_24000_bpsk_bch_latency | 8.345052083333334 | 0.20833333333333334 | 0.20833333333333334 | 0 | 2.808430989583333 |
| B5_encoding_24000_bpsk_bpsk_header_reference_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_diversity_latency | 23.020833333333332 | 0.4166666666666667 | 0.4166666666666667 | 0 | 7.747395833333333 |
| B5_encoding_24000_bpsk_halfband_control_latency | 23.020833333333332 | 0.4166666666666667 | 0.4166666666666667 | 0 | 7.747395833333333 |
| B5_encoding_24000_bpsk_interleave2048_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_interleave256_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_interleave32_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_k9_half_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 4.98046875 |
| B5_encoding_24000_bpsk_k9_third_latency | 17.265625 | 0.20833333333333334 | 0.20833333333333334 | 0 | 7.470703125 |
| B5_encoding_24000_bpsk_reference_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_soft_bpsk_header_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_soft_latency | 11.510416666666666 | 0.20833333333333334 | 0.20833333333333334 | 0 | 3.8736979166666665 |
| B5_encoding_24000_bpsk_walsh8_latency | 30.694444444444446 | 0.20833333333333334 | 0.20833333333333334 | 0 | 10.329861111111112 |
| B5_encoding_24000_fsk4_guard4_latency | 2782 | 0 | 0 | 0 | 936.25 |
| B5_encoding_24000_fsk4_guard8_latency | 4173.000000000001 | 0 | 0 | 0 | 1404.3750000000002 |
| B5_encoding_24000_fsk8_guard4_latency | 1473.3333333333333 | 0 | 0 | 0 | 495.8333333333333 |
| B5_encoding_24000_fsk8_guard8_latency | 2210 | 0 | 0 | 0 | 743.75 |
| B5_encoding_24000_qpsk_reference_latency | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |
| B5_encoding_24000_qpsk_soft_latency | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 0 | 1.9368489583333333 |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1026 declared cases) | — | not_run | — | — | — | — |

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
| Not run (96 declared cases) | — | not_run | — | — | — | — |

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
| Not run (46 declared cases) | — | not_run | — | — | — | — |

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
| Not run (501 declared cases) | — | not_run | — | — | — | — |

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

- **xfail** — The 2048-bit block interleaver at 10 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 276.762 ms.
  Cases: [B5_encoding_10000_bpsk_interleave2048_latency](B5_encoding_10000_bpsk_interleave2048_latency/7446529.json).
- **xfail** — The 256-bit block interleaver at 10 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 79.520 ms.
  Cases: [B5_encoding_10000_bpsk_interleave256_latency](B5_encoding_10000_bpsk_interleave256_latency/7446529.json).
- **xfail** — The 32-bit block interleaver at 10 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 4.248 ms.
  Cases: [B5_encoding_10000_bpsk_interleave32_latency](B5_encoding_10000_bpsk_interleave32_latency/7446529.json).
- **xfail** — The 2048-bit block interleaver at 24 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 183.309 ms.
  Cases: [B5_encoding_24000_bpsk_interleave2048_latency](B5_encoding_24000_bpsk_interleave2048_latency/7446529.json).
- **xfail** — The 256-bit block interleaver at 24 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 37.627 ms.
  Cases: [B5_encoding_24000_bpsk_interleave256_latency](B5_encoding_24000_bpsk_interleave256_latency/7446529.json).
- **xfail** — The 32-bit block interleaver at 24 kHz exceeds the 2.1 ms added-buffering allowance; measured host p99.9 is 2.376 ms.
  Cases: [B5_encoding_24000_bpsk_interleave32_latency](B5_encoding_24000_bpsk_interleave32_latency/7446529.json).

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
| full / selected rerun | 42 / 42 | 673.629 | 1800 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
