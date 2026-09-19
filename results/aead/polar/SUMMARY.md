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
| characterized | 216 |
| pass | 72 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 108 | 0 | 0 | 0 |
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
| B5 | 0 | 0 | 0 | 0 |
| C1 | 0 | 0 | 0 | 0 |
| C2 | 0 | 0 | 0 | 0 |
| C3 | 0 | 0 | 0 | 0 |
| C4 | 36 | 0 | 0 | 0 |
| C5 | 0 | 0 | 0 | 0 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 0 | 0 | 0 | 0 |
| D4 | 36 | 0 | 0 | 0 |
| D5 | 0 | 0 | 0 | 0 |
| D6 | 0 | 0 | 0 | 0 |
| E1 | 0 | 0 | 0 | 0 |
| E2 | 108 | 0 | 0 | 0 |
| E3 | 0 | 0 | 0 | 0 |
| E4 | 0 | 0 | 0 | 0 |

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.401042 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.526042 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.371528 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.15625 | 0.0171278 | 248.574 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.149436 | 0.0210804 | 305.937 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.101992 | 0.057971 | 841.326 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000136565 | 0.915082 | 13800.4 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 13838.6 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000222778 | 0.91128 | 13738.3 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.490502 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.505208 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.361111 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.171528 | 0.0158103 | 229.438 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.156982 | 0.0158103 | 229.438 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0857205 | 0.0606061 | 879.513 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 13837.6 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 13837.6 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000215564 | 0.91128 | 13739.1 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.397321 | 0.00566572 | 25.3972 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.46131 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.289583 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.125306 | 0.163373 | 790.553 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.141767 | 0.177866 | 857.694 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0810596 | 0.263505 | 1275.09 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4616.82 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.5 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.477431 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.443182 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.117382 | 0.15415 | 745.776 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.117371 | 0.181818 | 878.04 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.125702 | 0.249012 | 1204.72 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.66 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.492188 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.453125 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.507812 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.105035 | 0.0750988 | 726.799 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.120984 | 0.0750988 | 726.799 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0790807 | 0.131752 | 1275.09 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.85 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.330529 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.417969 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.446181 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.105725 | 0.0790514 | 764.823 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.114462 | 0.088274 | 854.052 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.111193 | 0.115942 | 1121.74 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.76 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.473931 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.483903 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.485379 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0437705 | 0.212337 | 6856.69 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0381853 | 0.226572 | 7316.35 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0617118 | 0.146501 | 4730.73 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 2.55002e-05 | 0.998369 | 35243.9 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 35282.3 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 8.49885e-06 | 0.998369 | 35234 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.480368 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.483805 | 0.000788022 | 19.108 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.469685 | 0.00315209 | 76.4319 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0393617 | 0.22242 | 7181.69 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0365625 | 0.23013 | 7416.29 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0612976 | 0.142349 | 4596.28 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 5.66633e-06 | 0.998912 | 35261.8 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 35281 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 3.39934e-05 | 0.998369 | 35234.8 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.443948 | 0.0330969 | 267.536 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.445638 | 0.0307329 | 248.427 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.448111 | 0.0338849 | 273.906 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0849488 | 0.573294 | 6167.83 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0618291 | 0.532344 | 5727.27 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.102137 | 0.494362 | 5318.63 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000257184 | 0.990751 | 11654.5 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11756.9 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000629701 | 0.983134 | 11564.1 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.452957 | 0.0283688 | 229.296 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.427561 | 0.0291568 | 235.665 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.43441 | 0.0425532 | 343.943 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0657702 | 0.604982 | 6511.4 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0569773 | 0.522539 | 5624.06 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.109763 | 0.502966 | 5413.4 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000280498 | 0.998369 | 11747.9 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000634083 | 0.988037 | 11623.1 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.462919 | 0.0173365 | 280.276 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.465585 | 0.0110323 | 178.358 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.459415 | 0.0102443 | 165.618 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0365561 | 0.488731 | 10510.1 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0435661 | 0.441281 | 9499.23 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0745178 | 0.329181 | 7086.12 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 23522.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 23522.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23527 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.465025 | 0.0102443 | 165.602 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.466461 | 0.0110323 | 178.341 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.475 | 0.00551615 | 89.1705 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0601117 | 0.492289 | 10597 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0364554 | 0.417556 | 8988.28 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0748197 | 0.295967 | 6370.95 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_quiet](A2_refinement_screen_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_quiet](A2_refinement_screen_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_quiet](A2_refinement_screen_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23528.4 | — |

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
| Not run (144 declared cases) | — | not_run | — | — | — | — |

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
| [C4_refinement_10000_8psk_bch_null](C4_refinement_10000_8psk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 17368.1 | — |
| [C4_refinement_10000_8psk_bch_null](C4_refinement_10000_8psk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 17368.1 | — |
| [C4_refinement_10000_8psk_bch_null](C4_refinement_10000_8psk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 17368.1 | — |
| [C4_refinement_10000_8psk_soft_null](C4_refinement_10000_8psk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 17368.9 | — |
| [C4_refinement_10000_8psk_soft_null](C4_refinement_10000_8psk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 17368.9 | — |
| [C4_refinement_10000_8psk_soft_null](C4_refinement_10000_8psk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 17368.9 | — |
| [C4_refinement_10000_bpsk_bch_null](C4_refinement_10000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 5786.27 | — |
| [C4_refinement_10000_bpsk_bch_null](C4_refinement_10000_bpsk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 5786.27 | — |
| [C4_refinement_10000_bpsk_bch_null](C4_refinement_10000_bpsk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 5786.27 | — |
| [C4_refinement_10000_bpsk_soft_null](C4_refinement_10000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_refinement_10000_bpsk_soft_null](C4_refinement_10000_bpsk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_refinement_10000_bpsk_soft_null](C4_refinement_10000_bpsk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_refinement_10000_qpsk_bch_null](C4_refinement_10000_qpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 11576.9 | — |
| [C4_refinement_10000_qpsk_bch_null](C4_refinement_10000_qpsk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 11576.9 | — |
| [C4_refinement_10000_qpsk_bch_null](C4_refinement_10000_qpsk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 11576.9 | — |
| [C4_refinement_10000_qpsk_soft_null](C4_refinement_10000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_refinement_10000_qpsk_soft_null](C4_refinement_10000_qpsk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_refinement_10000_qpsk_soft_null](C4_refinement_10000_qpsk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_refinement_24000_8psk_bch_null](C4_refinement_24000_8psk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 41947.4 | — |
| [C4_refinement_24000_8psk_bch_null](C4_refinement_24000_8psk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 41947.4 | — |
| [C4_refinement_24000_8psk_bch_null](C4_refinement_24000_8psk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 41947.4 | — |
| [C4_refinement_24000_8psk_soft_null](C4_refinement_24000_8psk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 41950.2 | — |
| [C4_refinement_24000_8psk_soft_null](C4_refinement_24000_8psk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 41950.2 | — |
| [C4_refinement_24000_8psk_soft_null](C4_refinement_24000_8psk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 41950.2 | — |
| [C4_refinement_24000_bpsk_bch_null](C4_refinement_24000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981.1 | — |
| [C4_refinement_24000_bpsk_bch_null](C4_refinement_24000_bpsk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 13981.1 | — |
| [C4_refinement_24000_bpsk_bch_null](C4_refinement_24000_bpsk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 13981.1 | — |
| [C4_refinement_24000_bpsk_soft_null](C4_refinement_24000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_refinement_24000_bpsk_soft_null](C4_refinement_24000_bpsk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_refinement_24000_bpsk_soft_null](C4_refinement_24000_bpsk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_refinement_24000_qpsk_bch_null](C4_refinement_24000_qpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.5 | — |
| [C4_refinement_24000_qpsk_bch_null](C4_refinement_24000_qpsk_bch_null/7446530.json) | assert / quick | pass | 0 | 1 | 27966.5 | — |
| [C4_refinement_24000_qpsk_bch_null](C4_refinement_24000_qpsk_bch_null/7446531.json) | assert / quick | pass | 0 | 1 | 27966.5 | — |
| [C4_refinement_24000_qpsk_soft_null](C4_refinement_24000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |
| [C4_refinement_24000_qpsk_soft_null](C4_refinement_24000_qpsk_soft_null/7446530.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |
| [C4_refinement_24000_qpsk_soft_null](C4_refinement_24000_qpsk_soft_null/7446531.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |

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
| [D4_refinement_10000_8psk_bch_null](D4_refinement_10000_8psk_bch_null/7446529.json) | assert / quick | pass | — | — | 930.667 | 75 |
| [D4_refinement_10000_8psk_bch_null](D4_refinement_10000_8psk_bch_null/7446530.json) | assert / quick | pass | — | — | 930.667 | 75 |
| [D4_refinement_10000_8psk_bch_null](D4_refinement_10000_8psk_bch_null/7446531.json) | assert / quick | pass | — | — | 930.667 | 75 |
| [D4_refinement_10000_8psk_soft_null](D4_refinement_10000_8psk_soft_null/7446529.json) | assert / quick | pass | — | — | 674.667 | 85 |
| [D4_refinement_10000_8psk_soft_null](D4_refinement_10000_8psk_soft_null/7446530.json) | assert / quick | pass | — | — | 674.667 | 85 |
| [D4_refinement_10000_8psk_soft_null](D4_refinement_10000_8psk_soft_null/7446531.json) | assert / quick | pass | — | — | 674.667 | 85 |
| [D4_refinement_10000_bpsk_bch_null](D4_refinement_10000_bpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 301.333 | 134 |
| [D4_refinement_10000_bpsk_bch_null](D4_refinement_10000_bpsk_bch_null/7446530.json) | assert / quick | pass | — | — | 301.333 | 134 |
| [D4_refinement_10000_bpsk_bch_null](D4_refinement_10000_bpsk_bch_null/7446531.json) | assert / quick | pass | — | — | 301.333 | 134 |
| [D4_refinement_10000_bpsk_soft_null](D4_refinement_10000_bpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 216 | 159 |
| [D4_refinement_10000_bpsk_soft_null](D4_refinement_10000_bpsk_soft_null/7446530.json) | assert / quick | pass | — | — | 216 | 159 |
| [D4_refinement_10000_bpsk_soft_null](D4_refinement_10000_bpsk_soft_null/7446531.json) | assert / quick | pass | — | — | 216 | 159 |
| [D4_refinement_10000_qpsk_bch_null](D4_refinement_10000_qpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 616 | 92 |
| [D4_refinement_10000_qpsk_bch_null](D4_refinement_10000_qpsk_bch_null/7446530.json) | assert / quick | pass | — | — | 616 | 92 |
| [D4_refinement_10000_qpsk_bch_null](D4_refinement_10000_qpsk_bch_null/7446531.json) | assert / quick | pass | — | — | 616 | 92 |
| [D4_refinement_10000_qpsk_soft_null](D4_refinement_10000_qpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 445.333 | 104 |
| [D4_refinement_10000_qpsk_soft_null](D4_refinement_10000_qpsk_soft_null/7446530.json) | assert / quick | pass | — | — | 445.333 | 104 |
| [D4_refinement_10000_qpsk_soft_null](D4_refinement_10000_qpsk_soft_null/7446531.json) | assert / quick | pass | — | — | 445.333 | 104 |
| [D4_refinement_24000_8psk_bch_null](D4_refinement_24000_8psk_bch_null/7446529.json) | assert / quick | pass | — | — | 2248 | 36 |
| [D4_refinement_24000_8psk_bch_null](D4_refinement_24000_8psk_bch_null/7446530.json) | assert / quick | pass | — | — | 2248 | 36 |
| [D4_refinement_24000_8psk_bch_null](D4_refinement_24000_8psk_bch_null/7446531.json) | assert / quick | pass | — | — | 2248 | 36 |
| [D4_refinement_24000_8psk_soft_null](D4_refinement_24000_8psk_soft_null/7446529.json) | assert / quick | pass | — | — | 1637.33 | 42 |
| [D4_refinement_24000_8psk_soft_null](D4_refinement_24000_8psk_soft_null/7446530.json) | assert / quick | pass | — | — | 1637.33 | 42 |
| [D4_refinement_24000_8psk_soft_null](D4_refinement_24000_8psk_soft_null/7446531.json) | assert / quick | pass | — | — | 1637.33 | 42 |
| [D4_refinement_24000_bpsk_bch_null](D4_refinement_24000_bpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 749.333 | 62 |
| [D4_refinement_24000_bpsk_bch_null](D4_refinement_24000_bpsk_bch_null/7446530.json) | assert / quick | pass | — | — | 749.333 | 62 |
| [D4_refinement_24000_bpsk_bch_null](D4_refinement_24000_bpsk_bch_null/7446531.json) | assert / quick | pass | — | — | 749.333 | 62 |
| [D4_refinement_24000_bpsk_soft_null](D4_refinement_24000_bpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 538.667 | 89 |
| [D4_refinement_24000_bpsk_soft_null](D4_refinement_24000_bpsk_soft_null/7446530.json) | assert / quick | pass | — | — | 538.667 | 89 |
| [D4_refinement_24000_bpsk_soft_null](D4_refinement_24000_bpsk_soft_null/7446531.json) | assert / quick | pass | — | — | 538.667 | 89 |
| [D4_refinement_24000_qpsk_bch_null](D4_refinement_24000_qpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 1501.33 | 44 |
| [D4_refinement_24000_qpsk_bch_null](D4_refinement_24000_qpsk_bch_null/7446530.json) | assert / quick | pass | — | — | 1501.33 | 44 |
| [D4_refinement_24000_qpsk_bch_null](D4_refinement_24000_qpsk_bch_null/7446531.json) | assert / quick | pass | — | — | 1501.33 | 44 |
| [D4_refinement_24000_qpsk_soft_null](D4_refinement_24000_qpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 1093.33 | 50 |
| [D4_refinement_24000_qpsk_soft_null](D4_refinement_24000_qpsk_soft_null/7446530.json) | assert / quick | pass | — | — | 1093.33 | 50 |
| [D4_refinement_24000_qpsk_soft_null](D4_refinement_24000_qpsk_soft_null/7446531.json) | assert / quick | pass | — | — | 1093.33 | 50 |

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
| [E2_refinement_followup_10000_8psk_bch_high_lat_disturbed](E2_refinement_followup_10000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_bch_high_lat_disturbed](E2_refinement_followup_10000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_bch_high_lat_disturbed](E2_refinement_followup_10000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 10.88 | 43 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 11.3067 | 45 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 11.92 | 113 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 881.147 | 108 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 886.16 | 108 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 887.013 | 108 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 8.32 | 119 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 7.22667 | 54 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 7.22667 | 125 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 637.147 | 117 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 640.56 | 117 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 643.44 | 117 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 20.24 | 177 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 19.84 | 174 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 19.0933 | 174 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 292.987 | 165 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 293.627 | 165 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 297.68 | 165 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 11.1733 | 201 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 10.24 | 201 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 9.17333 | 201 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 210.933 | 189 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 211.893 | 189 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 215.093 | 189 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 25.6267 | 131 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 26.32 | 130 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 21.9467 | 130 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 589.2 | 122 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 591.333 | 122 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 597.84 | 122 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 17.8933 | 146 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 16.4 | 143 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 13.8667 | 142 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 425.84 | 135 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 427.76 | 135 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 432.88 | 135 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.32 | 23 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.32 | 27 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.08 | 34 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 330.48 | 61 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 330.347 | 63 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 309.653 | 63 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2083.63 | 45 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2090.99 | 45 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2087.04 | 45 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.64 | 31 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.96 | 30 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 1.2 | 37 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 249.387 | 69 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 247.733 | 70 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 232.133 | 70 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1528.16 | 58 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1529.33 | 58 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1527.63 | 58 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.88 | 56 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 4.8 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.16 | 59 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 276.88 | 89 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 271.44 | 89 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 262 | 90 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 700.027 | 78 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 699.173 | 78 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 701.093 | 78 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 1.84 | 124 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 2.16 | 132 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.56 | 126 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 192.48 | 100 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 190.32 | 100 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 181.307 | 101 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 507.36 | 89 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 506.933 | 89 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 508 | 89 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 3.76 | 42 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 7.68 | 94 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 4.16 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 462.88 | 71 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 455.28 | 72 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 438.747 | 71 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1409.47 | 60 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1409.57 | 60 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1409.15 | 60 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 2.48 | 40 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 5.44 | 103 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.56 | 103 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 332.267 | 78 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 333.813 | 78 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 314.48 | 78 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1022.03 | 66 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1022.03 | 66 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1022.03 | 66 |

### Simulated channel E2 local metric definitions

| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |
| --- | --- | --- | --- | --- |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.0073 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.0038 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.00972 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.09226000000000001 | 0.23333333333333334 | 10.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.09269 | 0.20666666666666667 | 11.306666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.08930666666666667 | 0.22666666666666666 | 11.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.6749700000000001 | 1.0 | 881.1466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.6776433333333334 | 1.0 | 886.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.6794633333333333 | 1.0 | 887.0133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.00726 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.0040100000000000005 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.009649999999999999 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.09456666666666667 | 0.19333333333333333 | 8.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.09406333333333333 | 0.17 | 7.226666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.08834666666666667 | 0.15 | 7.226666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.6745666666666666 | 1.0 | 637.1466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.67703 | 1.0 | 640.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.6800266666666667 | 1.0 | 643.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.02235 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.01697 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.01954 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.27636333333333335 | 0.4166666666666667 | 20.24 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.2826066666666667 | 0.44333333333333336 | 19.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.25986666666666663 | 0.41 | 19.093333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6770933333333333 | 1.0 | 292.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6776 | 1.0 | 293.62666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6836666666666666 | 1.0 | 297.68 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.02239 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.01702 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.0173 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.27447 | 0.2966666666666667 | 11.173333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.27091333333333334 | 0.24333333333333335 | 10.24 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.25533666666666666 | 0.22333333333333333 | 9.173333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6767533333333333 | 1.0 | 210.93333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6776 | 1.0 | 211.89333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6834 | 1.0 | 215.09333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.01146 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.01042 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.013540000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.16078333333333333 | 0.39666666666666667 | 25.626666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.16306 | 0.44333333333333336 | 26.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.1494 | 0.42 | 21.946666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6768933333333333 | 1.0 | 589.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6785333333333333 | 1.0 | 591.3333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6840766666666667 | 1.0 | 597.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.01344 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.01081 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.01319 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.16427 | 0.3333333333333333 | 17.893333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.16041999999999998 | 0.3433333333333333 | 16.4 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.15153666666666665 | 0.31 | 13.866666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.6767433333333334 | 1.0 | 425.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.6782366666666667 | 1.0 | 427.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.6840766666666667 | 1.0 | 432.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.21025 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.20363 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.225 | 0.05 | 2.08 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.2867 | 0.98 | 330.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.28679000000000004 | 0.9866666666666667 | 330.3466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.2792 | 0.9766666666666667 | 309.6533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6898366666666667 | 1.0 | 2083.6266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6913133333333333 | 1.0 | 2090.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6904766666666666 | 1.0 | 2087.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.21386 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.2073 | 0.02 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.22394999999999998 | 0.03 | 1.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.28913666666666665 | 0.9766666666666667 | 249.38666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.28733333333333333 | 0.9866666666666667 | 247.73333333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.28186 | 0.9733333333333334 | 232.13333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.6907366666666667 | 1.0 | 1528.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.69081 | 1.0 | 1529.3333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.6905266666666666 | 1.0 | 1527.6266666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.3136 | 0.03 | 0.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.31757 | 0.15 | 4.8 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.33773000000000003 | 0.07 | 2.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5678433333333334 | 1.0 | 276.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5624566666666666 | 1.0 | 271.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5545133333333334 | 1.0 | 262.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.69058 | 1.0 | 700.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.6897500000000001 | 1.0 | 699.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.69063 | 1.0 | 701.0933333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.31184999999999996 | 0.06 | 1.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.3173 | 0.07 | 2.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.3404 | 0.08 | 2.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.5706966666666666 | 0.9966666666666667 | 192.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.56134 | 0.9866666666666667 | 190.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.5543033333333334 | 0.9866666666666667 | 181.30666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.6903966666666667 | 1.0 | 507.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.6906833333333334 | 1.0 | 506.93333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.6904566666666667 | 1.0 | 508.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.26869 | 0.08 | 3.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.2597 | 0.14 | 7.68 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.27247 | 0.11 | 4.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.45461999999999997 | 1.0 | 462.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.44954 | 0.9966666666666667 | 455.28 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.44266 | 0.9966666666666667 | 438.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.6920133333333334 | 1.0 | 1409.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.69202 | 1.0 | 1409.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.69184 | 1.0 | 1409.1466666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.2618 | 0.07 | 2.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.25942 | 0.13 | 5.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.27588999999999997 | 0.06 | 2.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.45252333333333333 | 1.0 | 332.26666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.4485766666666667 | 1.0 | 333.81333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.4394566666666666 | 0.9966666666666667 | 314.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.6920266666666667 | 1.0 | 1022.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.69202 | 1.0 | 1022.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.69202 | 1.0 | 1022.0266666666666 | Unavailable: audit definitions/standby instrumentation |

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
| full / selected rerun | 108 / 108 | 43.122 | 1800 | yes |
| full / selected rerun | 108 / 108 | 871.234 | 1800 | yes |
| quick / selected rerun | 72 / 72 | 3.559 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
