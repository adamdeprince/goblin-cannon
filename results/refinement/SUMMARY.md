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
| characterized | 1236 |
| pass | 92 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 630 | 0 | 0 | 0 |
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
| C1 | 192 | 0 | 0 | 0 |
| C2 | 0 | 0 | 0 | 0 |
| C3 | 0 | 0 | 0 | 0 |
| C4 | 46 | 0 | 0 | 0 |
| C5 | 0 | 0 | 0 | 0 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 0 | 0 | 0 | 0 |
| D4 | 46 | 0 | 0 | 0 |
| D5 | 0 | 0 | 0 | 0 |
| D6 | 0 | 0 | 0 | 0 |
| E1 | 0 | 0 | 0 | 0 |
| E2 | 414 | 0 | 0 | 0 |
| E3 | 0 | 0 | 0 | 0 |
| E4 | 0 | 0 | 0 | 0 |

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A2_refinement_delay_10000_diversity_commensurate_both_2.75ms](A2_refinement_delay_10000_diversity_commensurate_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_2.75ms](A2_refinement_delay_10000_diversity_commensurate_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_2.75ms](A2_refinement_delay_10000_diversity_commensurate_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 12.8 | 91 |
| [A2_refinement_delay_10000_diversity_commensurate_both_3.25ms](A2_refinement_delay_10000_diversity_commensurate_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 2.4 | 69 |
| [A2_refinement_delay_10000_diversity_commensurate_both_3.25ms](A2_refinement_delay_10000_diversity_commensurate_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_3.25ms](A2_refinement_delay_10000_diversity_commensurate_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 92 |
| [A2_refinement_delay_10000_diversity_commensurate_both_6.75ms](A2_refinement_delay_10000_diversity_commensurate_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_6.75ms](A2_refinement_delay_10000_diversity_commensurate_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_6.75ms](A2_refinement_delay_10000_diversity_commensurate_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_7.25ms](A2_refinement_delay_10000_diversity_commensurate_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_7.25ms](A2_refinement_delay_10000_diversity_commensurate_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_both_7.25ms](A2_refinement_delay_10000_diversity_commensurate_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 85 |
| [A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 2.4 | 69 |
| [A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_10000_diversity_commensurate_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_10000_diversity_commensurate_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 91 |
| [A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 2.4 | 69 |
| [A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 92 |
| [A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_10000_diversity_commensurate_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_10000_diversity_commensurate_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_2.75ms](A2_refinement_delay_10000_diversity_offset137_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 4.8 | 72 |
| [A2_refinement_delay_10000_diversity_offset137_both_2.75ms](A2_refinement_delay_10000_diversity_offset137_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_2.75ms](A2_refinement_delay_10000_diversity_offset137_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 12.8 | 91 |
| [A2_refinement_delay_10000_diversity_offset137_both_3.25ms](A2_refinement_delay_10000_diversity_offset137_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 9.6 | 86 |
| [A2_refinement_delay_10000_diversity_offset137_both_3.25ms](A2_refinement_delay_10000_diversity_offset137_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_3.25ms](A2_refinement_delay_10000_diversity_offset137_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_offset137_both_6.75ms](A2_refinement_delay_10000_diversity_offset137_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_6.75ms](A2_refinement_delay_10000_diversity_offset137_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_6.75ms](A2_refinement_delay_10000_diversity_offset137_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_7.25ms](A2_refinement_delay_10000_diversity_offset137_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_7.25ms](A2_refinement_delay_10000_diversity_offset137_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_both_7.25ms](A2_refinement_delay_10000_diversity_offset137_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_2.75ms](A2_refinement_delay_10000_diversity_offset137_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_2.75ms](A2_refinement_delay_10000_diversity_offset137_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_2.75ms](A2_refinement_delay_10000_diversity_offset137_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 85 |
| [A2_refinement_delay_10000_diversity_offset137_lower_3.25ms](A2_refinement_delay_10000_diversity_offset137_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 9.6 | 85 |
| [A2_refinement_delay_10000_diversity_offset137_lower_3.25ms](A2_refinement_delay_10000_diversity_offset137_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_3.25ms](A2_refinement_delay_10000_diversity_offset137_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_offset137_lower_6.75ms](A2_refinement_delay_10000_diversity_offset137_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_6.75ms](A2_refinement_delay_10000_diversity_offset137_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_6.75ms](A2_refinement_delay_10000_diversity_offset137_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_7.25ms](A2_refinement_delay_10000_diversity_offset137_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_7.25ms](A2_refinement_delay_10000_diversity_offset137_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_lower_7.25ms](A2_refinement_delay_10000_diversity_offset137_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_2.75ms](A2_refinement_delay_10000_diversity_offset137_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 4.8 | 71 |
| [A2_refinement_delay_10000_diversity_offset137_upper_2.75ms](A2_refinement_delay_10000_diversity_offset137_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_2.75ms](A2_refinement_delay_10000_diversity_offset137_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 12.8 | 91 |
| [A2_refinement_delay_10000_diversity_offset137_upper_3.25ms](A2_refinement_delay_10000_diversity_offset137_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_3.25ms](A2_refinement_delay_10000_diversity_offset137_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_3.25ms](A2_refinement_delay_10000_diversity_offset137_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_offset137_upper_6.75ms](A2_refinement_delay_10000_diversity_offset137_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_6.75ms](A2_refinement_delay_10000_diversity_offset137_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_6.75ms](A2_refinement_delay_10000_diversity_offset137_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_7.25ms](A2_refinement_delay_10000_diversity_offset137_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_7.25ms](A2_refinement_delay_10000_diversity_offset137_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_offset137_upper_7.25ms](A2_refinement_delay_10000_diversity_offset137_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_2.75ms](A2_refinement_delay_10000_diversity_wide137_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_2.75ms](A2_refinement_delay_10000_diversity_wide137_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_2.75ms](A2_refinement_delay_10000_diversity_wide137_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 12.8 | 91 |
| [A2_refinement_delay_10000_diversity_wide137_both_3.25ms](A2_refinement_delay_10000_diversity_wide137_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 12 | 91 |
| [A2_refinement_delay_10000_diversity_wide137_both_3.25ms](A2_refinement_delay_10000_diversity_wide137_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_3.25ms](A2_refinement_delay_10000_diversity_wide137_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_wide137_both_6.75ms](A2_refinement_delay_10000_diversity_wide137_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_6.75ms](A2_refinement_delay_10000_diversity_wide137_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_6.75ms](A2_refinement_delay_10000_diversity_wide137_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_7.25ms](A2_refinement_delay_10000_diversity_wide137_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_7.25ms](A2_refinement_delay_10000_diversity_wide137_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_both_7.25ms](A2_refinement_delay_10000_diversity_wide137_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_2.75ms](A2_refinement_delay_10000_diversity_wide137_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_2.75ms](A2_refinement_delay_10000_diversity_wide137_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_2.75ms](A2_refinement_delay_10000_diversity_wide137_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 85 |
| [A2_refinement_delay_10000_diversity_wide137_lower_3.25ms](A2_refinement_delay_10000_diversity_wide137_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 9.6 | 85 |
| [A2_refinement_delay_10000_diversity_wide137_lower_3.25ms](A2_refinement_delay_10000_diversity_wide137_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_3.25ms](A2_refinement_delay_10000_diversity_wide137_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_wide137_lower_6.75ms](A2_refinement_delay_10000_diversity_wide137_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_6.75ms](A2_refinement_delay_10000_diversity_wide137_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_6.75ms](A2_refinement_delay_10000_diversity_wide137_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_7.25ms](A2_refinement_delay_10000_diversity_wide137_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_7.25ms](A2_refinement_delay_10000_diversity_wide137_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_lower_7.25ms](A2_refinement_delay_10000_diversity_wide137_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_2.75ms](A2_refinement_delay_10000_diversity_wide137_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 2.4 | 66 |
| [A2_refinement_delay_10000_diversity_wide137_upper_2.75ms](A2_refinement_delay_10000_diversity_wide137_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_2.75ms](A2_refinement_delay_10000_diversity_wide137_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 85 |
| [A2_refinement_delay_10000_diversity_wide137_upper_3.25ms](A2_refinement_delay_10000_diversity_wide137_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_3.25ms](A2_refinement_delay_10000_diversity_wide137_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_3.25ms](A2_refinement_delay_10000_diversity_wide137_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 6.4 | 92 |
| [A2_refinement_delay_10000_diversity_wide137_upper_6.75ms](A2_refinement_delay_10000_diversity_wide137_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_6.75ms](A2_refinement_delay_10000_diversity_wide137_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_6.75ms](A2_refinement_delay_10000_diversity_wide137_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_7.25ms](A2_refinement_delay_10000_diversity_wide137_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_7.25ms](A2_refinement_delay_10000_diversity_wide137_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_10000_diversity_wide137_upper_7.25ms](A2_refinement_delay_10000_diversity_wide137_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_2.75ms](A2_refinement_delay_24000_diversity_commensurate_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 164 | 124 |
| [A2_refinement_delay_24000_diversity_commensurate_both_2.75ms](A2_refinement_delay_24000_diversity_commensurate_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 130.4 | 121 |
| [A2_refinement_delay_24000_diversity_commensurate_both_2.75ms](A2_refinement_delay_24000_diversity_commensurate_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 166.4 | 129 |
| [A2_refinement_delay_24000_diversity_commensurate_both_3.25ms](A2_refinement_delay_24000_diversity_commensurate_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 248.8 | 126 |
| [A2_refinement_delay_24000_diversity_commensurate_both_3.25ms](A2_refinement_delay_24000_diversity_commensurate_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 190.4 | 119 |
| [A2_refinement_delay_24000_diversity_commensurate_both_3.25ms](A2_refinement_delay_24000_diversity_commensurate_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 215.2 | 123 |
| [A2_refinement_delay_24000_diversity_commensurate_both_6.75ms](A2_refinement_delay_24000_diversity_commensurate_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_6.75ms](A2_refinement_delay_24000_diversity_commensurate_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_6.75ms](A2_refinement_delay_24000_diversity_commensurate_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_7.25ms](A2_refinement_delay_24000_diversity_commensurate_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_7.25ms](A2_refinement_delay_24000_diversity_commensurate_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_both_7.25ms](A2_refinement_delay_24000_diversity_commensurate_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 128.8 | 115 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 124 | 121 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 145.6 | 120 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 186.4 | 121 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 146.4 | 118 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 166.4 | 124 |
| [A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms](A2_refinement_delay_24000_diversity_commensurate_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms](A2_refinement_delay_24000_diversity_commensurate_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 138.4 | 124 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 114.4 | 121 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 157.6 | 120 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 187.2 | 123 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 156 | 118 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 169.6 | 123 |
| [A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms](A2_refinement_delay_24000_diversity_commensurate_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms](A2_refinement_delay_24000_diversity_commensurate_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_offset137_both_2.75ms](A2_refinement_delay_24000_diversity_offset137_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 172.8 | 124 |
| [A2_refinement_delay_24000_diversity_offset137_both_2.75ms](A2_refinement_delay_24000_diversity_offset137_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 123.2 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_both_2.75ms](A2_refinement_delay_24000_diversity_offset137_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 162.4 | 129 |
| [A2_refinement_delay_24000_diversity_offset137_both_3.25ms](A2_refinement_delay_24000_diversity_offset137_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 133.6 | 49 |
| [A2_refinement_delay_24000_diversity_offset137_both_3.25ms](A2_refinement_delay_24000_diversity_offset137_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 108 | 119 |
| [A2_refinement_delay_24000_diversity_offset137_both_3.25ms](A2_refinement_delay_24000_diversity_offset137_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 179.2 | 124 |
| [A2_refinement_delay_24000_diversity_offset137_both_6.75ms](A2_refinement_delay_24000_diversity_offset137_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_both_6.75ms](A2_refinement_delay_24000_diversity_offset137_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_both_6.75ms](A2_refinement_delay_24000_diversity_offset137_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_both_7.25ms](A2_refinement_delay_24000_diversity_offset137_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_both_7.25ms](A2_refinement_delay_24000_diversity_offset137_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_both_7.25ms](A2_refinement_delay_24000_diversity_offset137_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_offset137_lower_2.75ms](A2_refinement_delay_24000_diversity_offset137_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 111.2 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_lower_2.75ms](A2_refinement_delay_24000_diversity_offset137_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 130.4 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_lower_2.75ms](A2_refinement_delay_24000_diversity_offset137_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 127.2 | 129 |
| [A2_refinement_delay_24000_diversity_offset137_lower_3.25ms](A2_refinement_delay_24000_diversity_offset137_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 128.8 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_lower_3.25ms](A2_refinement_delay_24000_diversity_offset137_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 95.2 | 49 |
| [A2_refinement_delay_24000_diversity_offset137_lower_3.25ms](A2_refinement_delay_24000_diversity_offset137_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 105.6 | 123 |
| [A2_refinement_delay_24000_diversity_offset137_lower_6.75ms](A2_refinement_delay_24000_diversity_offset137_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_lower_6.75ms](A2_refinement_delay_24000_diversity_offset137_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_lower_6.75ms](A2_refinement_delay_24000_diversity_offset137_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_lower_7.25ms](A2_refinement_delay_24000_diversity_offset137_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_lower_7.25ms](A2_refinement_delay_24000_diversity_offset137_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_lower_7.25ms](A2_refinement_delay_24000_diversity_offset137_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_offset137_upper_2.75ms](A2_refinement_delay_24000_diversity_offset137_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 163.2 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_upper_2.75ms](A2_refinement_delay_24000_diversity_offset137_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 104 | 46 |
| [A2_refinement_delay_24000_diversity_offset137_upper_2.75ms](A2_refinement_delay_24000_diversity_offset137_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 103.2 | 120 |
| [A2_refinement_delay_24000_diversity_offset137_upper_3.25ms](A2_refinement_delay_24000_diversity_offset137_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 136.8 | 121 |
| [A2_refinement_delay_24000_diversity_offset137_upper_3.25ms](A2_refinement_delay_24000_diversity_offset137_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 130.4 | 118 |
| [A2_refinement_delay_24000_diversity_offset137_upper_3.25ms](A2_refinement_delay_24000_diversity_offset137_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 124.8 | 123 |
| [A2_refinement_delay_24000_diversity_offset137_upper_6.75ms](A2_refinement_delay_24000_diversity_offset137_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_upper_6.75ms](A2_refinement_delay_24000_diversity_offset137_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_upper_6.75ms](A2_refinement_delay_24000_diversity_offset137_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_upper_7.25ms](A2_refinement_delay_24000_diversity_offset137_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_upper_7.25ms](A2_refinement_delay_24000_diversity_offset137_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_offset137_upper_7.25ms](A2_refinement_delay_24000_diversity_offset137_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_wide137_both_2.75ms](A2_refinement_delay_24000_diversity_wide137_both_2.75ms/7446529.json) | characterize / full | characterized | — | — | 198.4 | 124 |
| [A2_refinement_delay_24000_diversity_wide137_both_2.75ms](A2_refinement_delay_24000_diversity_wide137_both_2.75ms/7446530.json) | characterize / full | characterized | — | — | 145.6 | 121 |
| [A2_refinement_delay_24000_diversity_wide137_both_2.75ms](A2_refinement_delay_24000_diversity_wide137_both_2.75ms/7446531.json) | characterize / full | characterized | — | — | 189.6 | 129 |
| [A2_refinement_delay_24000_diversity_wide137_both_3.25ms](A2_refinement_delay_24000_diversity_wide137_both_3.25ms/7446529.json) | characterize / full | characterized | — | — | 164 | 118 |
| [A2_refinement_delay_24000_diversity_wide137_both_3.25ms](A2_refinement_delay_24000_diversity_wide137_both_3.25ms/7446530.json) | characterize / full | characterized | — | — | 130.4 | 119 |
| [A2_refinement_delay_24000_diversity_wide137_both_3.25ms](A2_refinement_delay_24000_diversity_wide137_both_3.25ms/7446531.json) | characterize / full | characterized | — | — | 155.2 | 124 |
| [A2_refinement_delay_24000_diversity_wide137_both_6.75ms](A2_refinement_delay_24000_diversity_wide137_both_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_both_6.75ms](A2_refinement_delay_24000_diversity_wide137_both_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_both_6.75ms](A2_refinement_delay_24000_diversity_wide137_both_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_both_7.25ms](A2_refinement_delay_24000_diversity_wide137_both_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_both_7.25ms](A2_refinement_delay_24000_diversity_wide137_both_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_both_7.25ms](A2_refinement_delay_24000_diversity_wide137_both_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_delay_24000_diversity_wide137_lower_2.75ms](A2_refinement_delay_24000_diversity_wide137_lower_2.75ms/7446529.json) | characterize / full | characterized | — | — | 215.2 | 122 |
| [A2_refinement_delay_24000_diversity_wide137_lower_2.75ms](A2_refinement_delay_24000_diversity_wide137_lower_2.75ms/7446530.json) | characterize / full | characterized | — | — | 107.2 | 121 |
| [A2_refinement_delay_24000_diversity_wide137_lower_2.75ms](A2_refinement_delay_24000_diversity_wide137_lower_2.75ms/7446531.json) | characterize / full | characterized | — | — | 125.6 | 120 |
| [A2_refinement_delay_24000_diversity_wide137_lower_3.25ms](A2_refinement_delay_24000_diversity_wide137_lower_3.25ms/7446529.json) | characterize / full | characterized | — | — | 141.6 | 123 |
| [A2_refinement_delay_24000_diversity_wide137_lower_3.25ms](A2_refinement_delay_24000_diversity_wide137_lower_3.25ms/7446530.json) | characterize / full | characterized | — | — | 117.6 | 116 |
| [A2_refinement_delay_24000_diversity_wide137_lower_3.25ms](A2_refinement_delay_24000_diversity_wide137_lower_3.25ms/7446531.json) | characterize / full | characterized | — | — | 116.8 | 123 |
| [A2_refinement_delay_24000_diversity_wide137_lower_6.75ms](A2_refinement_delay_24000_diversity_wide137_lower_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_lower_6.75ms](A2_refinement_delay_24000_diversity_wide137_lower_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_lower_6.75ms](A2_refinement_delay_24000_diversity_wide137_lower_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_lower_7.25ms](A2_refinement_delay_24000_diversity_wide137_lower_7.25ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_lower_7.25ms](A2_refinement_delay_24000_diversity_wide137_lower_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_lower_7.25ms](A2_refinement_delay_24000_diversity_wide137_lower_7.25ms/7446531.json) | characterize / full | characterized | — | — | 3.2 | 51 |
| [A2_refinement_delay_24000_diversity_wide137_upper_2.75ms](A2_refinement_delay_24000_diversity_wide137_upper_2.75ms/7446529.json) | characterize / full | characterized | — | — | 104.8 | 121 |
| [A2_refinement_delay_24000_diversity_wide137_upper_2.75ms](A2_refinement_delay_24000_diversity_wide137_upper_2.75ms/7446530.json) | characterize / full | characterized | — | — | 120.8 | 121 |
| [A2_refinement_delay_24000_diversity_wide137_upper_2.75ms](A2_refinement_delay_24000_diversity_wide137_upper_2.75ms/7446531.json) | characterize / full | characterized | — | — | 139.2 | 120 |
| [A2_refinement_delay_24000_diversity_wide137_upper_3.25ms](A2_refinement_delay_24000_diversity_wide137_upper_3.25ms/7446529.json) | characterize / full | characterized | — | — | 165.6 | 120 |
| [A2_refinement_delay_24000_diversity_wide137_upper_3.25ms](A2_refinement_delay_24000_diversity_wide137_upper_3.25ms/7446530.json) | characterize / full | characterized | — | — | 111.2 | 124 |
| [A2_refinement_delay_24000_diversity_wide137_upper_3.25ms](A2_refinement_delay_24000_diversity_wide137_upper_3.25ms/7446531.json) | characterize / full | characterized | — | — | 160 | 124 |
| [A2_refinement_delay_24000_diversity_wide137_upper_6.75ms](A2_refinement_delay_24000_diversity_wide137_upper_6.75ms/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_upper_6.75ms](A2_refinement_delay_24000_diversity_wide137_upper_6.75ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_upper_6.75ms](A2_refinement_delay_24000_diversity_wide137_upper_6.75ms/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_upper_7.25ms](A2_refinement_delay_24000_diversity_wide137_upper_7.25ms/7446529.json) | characterize / full | characterized | — | — | 9.6 | 45 |
| [A2_refinement_delay_24000_diversity_wide137_upper_7.25ms](A2_refinement_delay_24000_diversity_wide137_upper_7.25ms/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [A2_refinement_delay_24000_diversity_wide137_upper_7.25ms](A2_refinement_delay_24000_diversity_wide137_upper_7.25ms/7446531.json) | characterize / full | characterized | — | — | 9.6 | 55 |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.453125 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.510417 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_disturbed](A2_refinement_screen_10000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.423611 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.18625 | 0.0105402 | 152.968 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.163889 | 0.0197628 | 286.816 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_moderate](A2_refinement_screen_10000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0990428 | 0.0527009 | 764.842 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 13838.6 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 13838.6 | — |
| [A2_refinement_screen_10000_8psk_bch_high_lat_quiet](A2_refinement_screen_10000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000201219 | 0.912548 | 13757.4 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.372396 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.505208 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_disturbed](A2_refinement_screen_10000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.403646 | 0 | 0 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.165496 | 0.0144928 | 210.318 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.173412 | 0.0184453 | 267.678 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_moderate](A2_refinement_screen_10000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0958995 | 0.057971 | 841.274 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 13837.6 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 13837.6 | — |
| [A2_refinement_screen_10000_8psk_soft_high_lat_quiet](A2_refinement_screen_10000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000136524 | 0.91128 | 13739.1 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.498047 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.493924 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.425625 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.102069 | 0.183136 | 886.184 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0978442 | 0.198946 | 959.701 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.131211 | 0.246377 | 1192.21 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_refinement_screen_10000_bpsk_bch_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4616.82 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.53125 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.468112 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.108303 | 0.21067 | 984.058 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.115466 | 0.166895 | 775.984 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.118944 | 0.239398 | 1118.25 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.85112 | 4120.48 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.935441 | 4528.7 | — |
| [A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.894598 | 4327.98 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.263889 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.546875 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.381836 | 0.003125 | 6.40991 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.100943 | 0.328804 | 774.203 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0935106 | 0.391304 | 915.167 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0945789 | 0.350543 | 825.39 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.876574 | 2216.66 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.926952 | 2344.06 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.929471 | 2344.26 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.0520833 | 0.00198413 | 12.7754 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.090121 | 0.0492754 | 324.418 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.373077 | 0.0521739 | 343.501 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.271617 | 0.0454106 | 298.973 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.937977 | 6265.76 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999046 | 6673.7 | — |
| [A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.938931 | 6269.74 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.4375 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.229167 | 0.00139276 | 6.39482 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.523438 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.18249 | 0.22093 | 1089.68 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.170376 | 0.189922 | 930.566 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.186834 | 0.167959 | 828.409 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.879503 | 4510.24 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.919255 | 4714.09 | — |
| [A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_bpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.880745 | 4515.01 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.505515 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.470486 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.3125 | 0 | 0 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.146747 | 0.183136 | 886.008 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.137665 | 0.177866 | 858.918 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_moderate](A2_refinement_screen_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.106661 | 0.247694 | 1198.34 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_refinement_screen_10000_bpsk_soft_high_lat_quiet](A2_refinement_screen_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.66 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0929487 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.113095 | 0.0382166 | 76.4033 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.84953 | 1728.92 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.949843 | 1933.75 | — |
| [A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.115552 | 0.0318471 | 63.6694 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.949843 | 1933.75 | — |
| [A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.34375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.15625 | 0.0318471 | 63.6694 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.949843 | 1933.75 | — |
| [A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_commensurate_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.15407 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.188447 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.84953 | 1728.92 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.00103154 | 0.99373 | 2023.37 | — |
| [A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0828125 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000491207 | 0.996865 | 2029.77 | — |
| [A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0979167 | 0.0286624 | 57.3025 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.107143 | 0.022293 | 44.5686 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.949843 | 1933.75 | — |
| [A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_offset137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.103906 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.109776 | 0.0382166 | 76.4033 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.84953 | 1728.92 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000736811 | 0.99373 | 2023.37 | — |
| [A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0851293 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.3125 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.140086 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.00068769 | 0.99373 | 2023.37 | — |
| [A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 2036.17 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.151654 | 0.022293 | 44.5686 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.359375 | 0 | 0 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.102865 | 0.0254777 | 50.9356 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.899687 | 1831.34 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.949843 | 1933.75 | — |
| [A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_10000_diversity_wide137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000147362 | 0.99373 | 2023.37 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.440878 | 0.00141643 | 12.6986 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.40625 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.470703 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0936275 | 0.0922266 | 892.56 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.103576 | 0.088274 | 854.307 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0975481 | 0.11726 | 1134.83 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.85 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.5 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.515625 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.345703 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.113555 | 0.0711354 | 664.285 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0543221 | 0.112175 | 1046.13 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0755149 | 0.0943912 | 881.455 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.8722 | 8445.06 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.935441 | 9057.39 | — |
| [A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.894598 | 8655.95 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.453125 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.3125 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.359375 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.112869 | 0.247283 | 1164.05 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.126515 | 0.211957 | 997.76 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.108567 | 0.222826 | 1048.93 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.876574 | 4431.61 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.926952 | 4686.3 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.929471 | 4692.47 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.429688 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.15 | 0.0202899 | 267.167 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.108902 | 0.0299517 | 394.39 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.1312 | 0.0125604 | 165.389 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.937977 | 12531.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999046 | 13347.4 | — |
| [A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.938931 | 12539.5 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.498047 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.439453 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.508247 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.185716 | 0.0839793 | 828.11 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.227725 | 0.0736434 | 726.188 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.230437 | 0.0542636 | 535.086 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.879503 | 9020.47 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.919255 | 9428.18 | — |
| [A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_10000_qpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.880745 | 9030.03 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.388393 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.421875 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.515625 | 0 | 0 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.108406 | 0.0988142 | 956.028 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.122863 | 0.0711462 | 688.341 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_moderate](A2_refinement_screen_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.13879 | 0.106719 | 1032.51 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_refinement_screen_10000_qpsk_soft_high_lat_quiet](A2_refinement_screen_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.76 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.483843 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.466092 | 0.00236407 | 57.3292 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_disturbed](A2_refinement_screen_24000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.475919 | 0.00157604 | 38.2195 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0404264 | 0.217082 | 7009.91 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0331889 | 0.242586 | 7814.92 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_moderate](A2_refinement_screen_24000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.061646 | 0.154211 | 4979.72 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000298815 | 0.982055 | 34668 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 35282.3 | — |
| [A2_refinement_screen_24000_8psk_bch_high_lat_quiet](A2_refinement_screen_24000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 5.09931e-05 | 0.997825 | 35214.8 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.473689 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.482059 | 0 | 0 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_disturbed](A2_refinement_screen_24000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.471332 | 0.00157604 | 38.2159 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0389347 | 0.234875 | 7583.86 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0410645 | 0.223606 | 7219.99 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_moderate](A2_refinement_screen_24000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0538984 | 0.160142 | 5170.81 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 5.66633e-06 | 0.998912 | 35261.8 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 35281 | — |
| [A2_refinement_screen_24000_8psk_soft_high_lat_quiet](A2_refinement_screen_24000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 1.41639e-05 | 0.997281 | 35196.4 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.449421 | 0.0299448 | 242.057 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.466079 | 0.0141844 | 114.658 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.45692 | 0.0260047 | 210.207 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0794452 | 0.580415 | 6244.45 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.05 | 0.532344 | 5727.27 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.102669 | 0.484866 | 5216.48 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11756.9 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11756.9 | — |
| [A2_refinement_screen_24000_bpsk_bch_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000475351 | 0.98259 | 11557.7 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.41015 | 0.0646726 | 509.413 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.438377 | 0.0315279 | 248.339 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.417748 | 0.0549717 | 433.001 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0928008 | 0.522727 | 5442.25 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0587646 | 0.54914 | 5714.84 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0902608 | 0.534398 | 5563.76 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999435 | 11314.2 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000132439 | 0.998305 | 11301.4 | — |
| [A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000282501 | 0.99774 | 11294.4 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.451519 | 0.0334029 | 102.143 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.40714 | 0.0709812 | 217.054 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.407143 | 0.0626305 | 191.518 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0836104 | 0.559633 | 2730.27 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0587941 | 0.623853 | 3043.58 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0785156 | 0.583224 | 2845.37 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.00318471 | 0.983315 | 5651.69 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000261042 | 0.995551 | 5722.02 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.00232949 | 0.986652 | 5665.08 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.481897 | 0.0148011 | 204.48 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.48221 | 0.00601295 | 83.0702 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.501169 | 0.000462535 | 6.39002 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.121222 | 0.346854 | 5358.81 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0563411 | 0.386589 | 5967.31 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.122211 | 0.300911 | 4648.99 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000141681 | 0.973896 | 15518.9 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999598 | 15928.4 | — |
| [A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000163187 | 0.999197 | 15918.6 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.444189 | 0.0287714 | 235.774 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.425811 | 0.0482115 | 395.081 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.423717 | 0.0458787 | 375.964 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0616617 | 0.530612 | 5805.72 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0571832 | 0.545773 | 5971.67 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0761895 | 0.507872 | 5559.19 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000252033 | 0.9904 | 11856.2 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.998933 | 11958.4 | — |
| [A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_bpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000999597 | 0.987733 | 11818.7 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.441954 | 0.0378251 | 305.727 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.460471 | 0.0228526 | 184.71 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.445084 | 0.0283688 | 229.296 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0623003 | 0.598458 | 6441.18 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0730265 | 0.519573 | 5592.14 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_moderate](A2_refinement_screen_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0996747 | 0.494662 | 5324.02 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_refinement_screen_24000_bpsk_soft_high_lat_quiet](A2_refinement_screen_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.0054664 | 0.978793 | 11514.4 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.452148 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.431066 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.487564 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.141109 | 0.253772 | 1179.89 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.128596 | 0.245542 | 1139.23 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.138419 | 0.192044 | 892.892 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.957728 | 4620.16 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.5625 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.4375 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.489298 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.146566 | 0.201646 | 937.536 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.132191 | 0.223594 | 1037.19 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.163493 | 0.15775 | 733.447 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.5625 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.398438 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.480574 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.120366 | 0.224966 | 1045.96 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0874545 | 0.216735 | 1005.3 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.175197 | 0.168724 | 784.469 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_commensurate_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.438988 | 0.00147059 | 6.37454 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.349609 | 0.00147059 | 6.37454 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.117009 | 0.271605 | 1262.8 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.103247 | 0.314129 | 1458.12 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.14448 | 0.229081 | 1065.09 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.957728 | 4620.16 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.486213 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.585938 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.428977 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.130958 | 0.21262 | 988.559 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.135814 | 0.198903 | 922.389 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.17515 | 0.183813 | 854.625 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.486213 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.39277 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.300595 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0973323 | 0.178326 | 829.114 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0994224 | 0.23594 | 1094.59 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.15088 | 0.131687 | 612.269 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_offset137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.542969 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.342672 | 0.00147059 | 6.37454 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.494196 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.13753 | 0.252401 | 1173.51 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.158093 | 0.218107 | 1011.68 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.138365 | 0.186557 | 867.38 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.516113 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.475962 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.457849 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0972155 | 0.216735 | 1007.69 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.139896 | 0.216735 | 1005.3 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.176965 | 0.155007 | 720.691 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | 8.26071e-05 | 0.997358 | 4813.21 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.977543 | 4717.58 | — |
| [A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.484375 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.288194 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.436979 | 0 | 0 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.154827 | 0.186557 | 867.38 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.116226 | 0.223594 | 1037.19 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.135774 | 0.1893 | 880.136 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.998679 | 4819.58 | — |
| [A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet](A2_refinement_screen_24000_diversity_wide137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 4824.17 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.467427 | 0.0102443 | 165.618 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.470142 | 0.00945626 | 152.878 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.465498 | 0.0118203 | 191.097 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0417671 | 0.495848 | 10673.9 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0364779 | 0.441281 | 9499.23 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0673585 | 0.327402 | 7047.82 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 23522.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 23522.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23527 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.469582 | 0.0129345 | 203.765 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.442189 | 0.00727567 | 114.618 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.441835 | 0.0234438 | 369.324 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0430363 | 0.430939 | 8977.31 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0427535 | 0.457336 | 9515.42 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0493687 | 0.392265 | 8171.66 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999435 | 22637.3 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999435 | 22637.3 | — |
| [A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 22641.9 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.452493 | 0.0229645 | 140.447 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.448042 | 0.0208768 | 127.679 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.434055 | 0.0229645 | 140.447 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0721529 | 0.471822 | 4603 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0680016 | 0.48886 | 4769.22 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.080656 | 0.462647 | 4513.5 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.997775 | 11469.6 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.997775 | 11469.6 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 11483.6 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.484032 | 0.00647549 | 178.92 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.482884 | 0.00370028 | 102.24 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.498692 | 0 | 0 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0796674 | 0.180877 | 5588.13 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0303547 | 0.238825 | 7378.38 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0426683 | 0.159354 | 4923.18 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999598 | 31851.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999598 | 31851.8 | — |
| [A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 31863.6 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.459975 | 0.00777605 | 127.445 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.465022 | 0.0155521 | 254.891 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.454055 | 0.0147745 | 242.146 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.057097 | 0.438811 | 9610.67 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0834914 | 0.399184 | 8731.01 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0813661 | 0.361888 | 7925.93 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.998933 | 23916.7 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.998933 | 23916.7 | — |
| [A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet](A2_refinement_screen_24000_qpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23931.1 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.475394 | 0.00394011 | 63.6932 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.470695 | 0.00945626 | 152.864 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed](A2_refinement_screen_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.480494 | 0.00394011 | 63.6932 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0520663 | 0.470937 | 10137.3 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.038326 | 0.412811 | 8886.14 | — |
| [A2_refinement_screen_24000_qpsk_soft_high_lat_moderate](A2_refinement_screen_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0678726 | 0.310202 | 6677.37 | — |
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
| [C1_refinement_snr_10000_8psk_bch_0dB](C1_refinement_snr_10000_8psk_bch_0dB/7446529.json) | characterize / full | characterized | 0.00132144 | 0.782514 | 13693.8 | — |
| [C1_refinement_snr_10000_8psk_bch_10dB](C1_refinement_snr_10000_8psk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_12dB](C1_refinement_snr_10000_8psk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_14dB](C1_refinement_snr_10000_8psk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_16dB](C1_refinement_snr_10000_8psk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_18dB](C1_refinement_snr_10000_8psk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_20dB](C1_refinement_snr_10000_8psk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_22dB](C1_refinement_snr_10000_8psk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_24dB](C1_refinement_snr_10000_8psk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_26dB](C1_refinement_snr_10000_8psk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_28dB](C1_refinement_snr_10000_8psk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_2dB](C1_refinement_snr_10000_8psk_bch_2dB/7446529.json) | characterize / full | characterized | 9.11338e-05 | 0.982514 | 17196.7 | — |
| [C1_refinement_snr_10000_8psk_bch_30dB](C1_refinement_snr_10000_8psk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_4dB](C1_refinement_snr_10000_8psk_bch_4dB/7446529.json) | characterize / full | characterized | 5.69586e-06 | 0.998907 | 17483.8 | — |
| [C1_refinement_snr_10000_8psk_bch_6dB](C1_refinement_snr_10000_8psk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_bch_8dB](C1_refinement_snr_10000_8psk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17502.9 | — |
| [C1_refinement_snr_10000_8psk_soft_0dB](C1_refinement_snr_10000_8psk_soft_0dB/7446529.json) | characterize / full | characterized | 0.001287 | 0.785792 | 13752.4 | — |
| [C1_refinement_snr_10000_8psk_soft_10dB](C1_refinement_snr_10000_8psk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_12dB](C1_refinement_snr_10000_8psk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_14dB](C1_refinement_snr_10000_8psk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_16dB](C1_refinement_snr_10000_8psk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_18dB](C1_refinement_snr_10000_8psk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_20dB](C1_refinement_snr_10000_8psk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_22dB](C1_refinement_snr_10000_8psk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_24dB](C1_refinement_snr_10000_8psk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_26dB](C1_refinement_snr_10000_8psk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_28dB](C1_refinement_snr_10000_8psk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_2dB](C1_refinement_snr_10000_8psk_soft_2dB/7446529.json) | characterize / full | characterized | 0.000102505 | 0.980328 | 17159 | — |
| [C1_refinement_snr_10000_8psk_soft_30dB](C1_refinement_snr_10000_8psk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_4dB](C1_refinement_snr_10000_8psk_soft_4dB/7446529.json) | characterize / full | characterized | 1.13894e-05 | 0.997814 | 17465.2 | — |
| [C1_refinement_snr_10000_8psk_soft_6dB](C1_refinement_snr_10000_8psk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_8psk_soft_8dB](C1_refinement_snr_10000_8psk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 17503.5 | — |
| [C1_refinement_snr_10000_bpsk_bch_0dB](C1_refinement_snr_10000_bpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_10dB](C1_refinement_snr_10000_bpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_12dB](C1_refinement_snr_10000_bpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_14dB](C1_refinement_snr_10000_bpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_16dB](C1_refinement_snr_10000_bpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_18dB](C1_refinement_snr_10000_bpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_20dB](C1_refinement_snr_10000_bpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_22dB](C1_refinement_snr_10000_bpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_24dB](C1_refinement_snr_10000_bpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_26dB](C1_refinement_snr_10000_bpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_28dB](C1_refinement_snr_10000_bpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_2dB](C1_refinement_snr_10000_bpsk_bch_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_30dB](C1_refinement_snr_10000_bpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_4dB](C1_refinement_snr_10000_bpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_6dB](C1_refinement_snr_10000_bpsk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_bch_8dB](C1_refinement_snr_10000_bpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_refinement_snr_10000_bpsk_soft_0dB](C1_refinement_snr_10000_bpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_10dB](C1_refinement_snr_10000_bpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_12dB](C1_refinement_snr_10000_bpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_14dB](C1_refinement_snr_10000_bpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_16dB](C1_refinement_snr_10000_bpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_18dB](C1_refinement_snr_10000_bpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_20dB](C1_refinement_snr_10000_bpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_22dB](C1_refinement_snr_10000_bpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_24dB](C1_refinement_snr_10000_bpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_26dB](C1_refinement_snr_10000_bpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_28dB](C1_refinement_snr_10000_bpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_2dB](C1_refinement_snr_10000_bpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_30dB](C1_refinement_snr_10000_bpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_4dB](C1_refinement_snr_10000_bpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_6dB](C1_refinement_snr_10000_bpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_bpsk_soft_8dB](C1_refinement_snr_10000_bpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_refinement_snr_10000_qpsk_bch_0dB](C1_refinement_snr_10000_qpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_10dB](C1_refinement_snr_10000_qpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_12dB](C1_refinement_snr_10000_qpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_14dB](C1_refinement_snr_10000_qpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_16dB](C1_refinement_snr_10000_qpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_18dB](C1_refinement_snr_10000_qpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_20dB](C1_refinement_snr_10000_qpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_22dB](C1_refinement_snr_10000_qpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_24dB](C1_refinement_snr_10000_qpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_26dB](C1_refinement_snr_10000_qpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_28dB](C1_refinement_snr_10000_qpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_2dB](C1_refinement_snr_10000_qpsk_bch_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_30dB](C1_refinement_snr_10000_qpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_4dB](C1_refinement_snr_10000_qpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_6dB](C1_refinement_snr_10000_qpsk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_bch_8dB](C1_refinement_snr_10000_qpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_0dB](C1_refinement_snr_10000_qpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_10dB](C1_refinement_snr_10000_qpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_12dB](C1_refinement_snr_10000_qpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_14dB](C1_refinement_snr_10000_qpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_16dB](C1_refinement_snr_10000_qpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_18dB](C1_refinement_snr_10000_qpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_20dB](C1_refinement_snr_10000_qpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_22dB](C1_refinement_snr_10000_qpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_24dB](C1_refinement_snr_10000_qpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_26dB](C1_refinement_snr_10000_qpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_28dB](C1_refinement_snr_10000_qpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_2dB](C1_refinement_snr_10000_qpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_30dB](C1_refinement_snr_10000_qpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_4dB](C1_refinement_snr_10000_qpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_6dB](C1_refinement_snr_10000_qpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_10000_qpsk_soft_8dB](C1_refinement_snr_10000_qpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_refinement_snr_24000_8psk_bch_0dB](C1_refinement_snr_24000_8psk_bch_0dB/7446529.json) | characterize / full | characterized | 0.1235 | 0 | 0 | — |
| [C1_refinement_snr_24000_8psk_bch_10dB](C1_refinement_snr_24000_8psk_bch_10dB/7446529.json) | characterize / full | characterized | 6.40766e-05 | 0.98861 | 41605.8 | — |
| [C1_refinement_snr_24000_8psk_bch_12dB](C1_refinement_snr_24000_8psk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_14dB](C1_refinement_snr_24000_8psk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_16dB](C1_refinement_snr_24000_8psk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_18dB](C1_refinement_snr_24000_8psk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_20dB](C1_refinement_snr_24000_8psk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_22dB](C1_refinement_snr_24000_8psk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_24dB](C1_refinement_snr_24000_8psk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_26dB](C1_refinement_snr_24000_8psk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_28dB](C1_refinement_snr_24000_8psk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_2dB](C1_refinement_snr_24000_8psk_bch_2dB/7446529.json) | characterize / full | characterized | 0.080075 | 0 | 0 | — |
| [C1_refinement_snr_24000_8psk_bch_30dB](C1_refinement_snr_24000_8psk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42085.2 | — |
| [C1_refinement_snr_24000_8psk_bch_4dB](C1_refinement_snr_24000_8psk_bch_4dB/7446529.json) | characterize / full | characterized | 0.0291329 | 0.0173121 | 728.701 | — |
| [C1_refinement_snr_24000_8psk_bch_6dB](C1_refinement_snr_24000_8psk_bch_6dB/7446529.json) | characterize / full | characterized | 0.00749798 | 0.323918 | 13627.5 | — |
| [C1_refinement_snr_24000_8psk_bch_8dB](C1_refinement_snr_24000_8psk_bch_8dB/7446529.json) | characterize / full | characterized | 0.000894698 | 0.84738 | 35661.1 | — |
| [C1_refinement_snr_24000_8psk_soft_0dB](C1_refinement_snr_24000_8psk_soft_0dB/7446529.json) | characterize / full | characterized | 0.118883 | 0 | 0 | — |
| [C1_refinement_snr_24000_8psk_soft_10dB](C1_refinement_snr_24000_8psk_soft_10dB/7446529.json) | characterize / full | characterized | 5.45787e-05 | 0.989977 | 41664.4 | — |
| [C1_refinement_snr_24000_8psk_soft_12dB](C1_refinement_snr_24000_8psk_soft_12dB/7446529.json) | characterize / full | characterized | 2.37299e-06 | 0.999544 | 42067.1 | — |
| [C1_refinement_snr_24000_8psk_soft_14dB](C1_refinement_snr_24000_8psk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_16dB](C1_refinement_snr_24000_8psk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_18dB](C1_refinement_snr_24000_8psk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_20dB](C1_refinement_snr_24000_8psk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_22dB](C1_refinement_snr_24000_8psk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_24dB](C1_refinement_snr_24000_8psk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_26dB](C1_refinement_snr_24000_8psk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_28dB](C1_refinement_snr_24000_8psk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_2dB](C1_refinement_snr_24000_8psk_soft_2dB/7446529.json) | characterize / full | characterized | 0.0725263 | 0 | 0 | — |
| [C1_refinement_snr_24000_8psk_soft_30dB](C1_refinement_snr_24000_8psk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 42086.3 | — |
| [C1_refinement_snr_24000_8psk_soft_4dB](C1_refinement_snr_24000_8psk_soft_4dB/7446529.json) | characterize / full | characterized | 0.0285708 | 0.0159453 | 671.128 | — |
| [C1_refinement_snr_24000_8psk_soft_6dB](C1_refinement_snr_24000_8psk_soft_6dB/7446529.json) | characterize / full | characterized | 0.00650444 | 0.339408 | 14282.4 | — |
| [C1_refinement_snr_24000_8psk_soft_8dB](C1_refinement_snr_24000_8psk_soft_8dB/7446529.json) | characterize / full | characterized | 0.000930634 | 0.838269 | 35279.1 | — |
| [C1_refinement_snr_24000_bpsk_bch_0dB](C1_refinement_snr_24000_bpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0.000397749 | 0.925285 | 12979 | — |
| [C1_refinement_snr_24000_bpsk_bch_10dB](C1_refinement_snr_24000_bpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_12dB](C1_refinement_snr_24000_bpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_14dB](C1_refinement_snr_24000_bpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_16dB](C1_refinement_snr_24000_bpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_18dB](C1_refinement_snr_24000_bpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_20dB](C1_refinement_snr_24000_bpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_22dB](C1_refinement_snr_24000_bpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_24dB](C1_refinement_snr_24000_bpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_26dB](C1_refinement_snr_24000_bpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_28dB](C1_refinement_snr_24000_bpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_2dB](C1_refinement_snr_24000_bpsk_bch_2dB/7446529.json) | characterize / full | characterized | 2.13648e-05 | 0.998633 | 14008.3 | — |
| [C1_refinement_snr_24000_bpsk_bch_30dB](C1_refinement_snr_24000_bpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_4dB](C1_refinement_snr_24000_bpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_6dB](C1_refinement_snr_24000_bpsk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_bch_8dB](C1_refinement_snr_24000_bpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_refinement_snr_24000_bpsk_soft_0dB](C1_refinement_snr_24000_bpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0.000367603 | 0.926651 | 12999.5 | — |
| [C1_refinement_snr_24000_bpsk_soft_10dB](C1_refinement_snr_24000_bpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_12dB](C1_refinement_snr_24000_bpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_14dB](C1_refinement_snr_24000_bpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_16dB](C1_refinement_snr_24000_bpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_18dB](C1_refinement_snr_24000_bpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_20dB](C1_refinement_snr_24000_bpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_22dB](C1_refinement_snr_24000_bpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_24dB](C1_refinement_snr_24000_bpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_26dB](C1_refinement_snr_24000_bpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_28dB](C1_refinement_snr_24000_bpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_2dB](C1_refinement_snr_24000_bpsk_soft_2dB/7446529.json) | characterize / full | characterized | 7.11926e-06 | 0.999544 | 14022.2 | — |
| [C1_refinement_snr_24000_bpsk_soft_30dB](C1_refinement_snr_24000_bpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_4dB](C1_refinement_snr_24000_bpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_6dB](C1_refinement_snr_24000_bpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_bpsk_soft_8dB](C1_refinement_snr_24000_bpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_0dB](C1_refinement_snr_24000_qpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0.0186833 | 0.215945 | 6053.51 | — |
| [C1_refinement_snr_24000_qpsk_bch_10dB](C1_refinement_snr_24000_qpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_12dB](C1_refinement_snr_24000_qpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_14dB](C1_refinement_snr_24000_qpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_16dB](C1_refinement_snr_24000_qpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_18dB](C1_refinement_snr_24000_qpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_20dB](C1_refinement_snr_24000_qpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_22dB](C1_refinement_snr_24000_qpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_24dB](C1_refinement_snr_24000_qpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_26dB](C1_refinement_snr_24000_qpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_28dB](C1_refinement_snr_24000_qpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_2dB](C1_refinement_snr_24000_qpsk_bch_2dB/7446529.json) | characterize / full | characterized | 0.00309369 | 0.767198 | 21523.4 | — |
| [C1_refinement_snr_24000_qpsk_bch_30dB](C1_refinement_snr_24000_qpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_bch_4dB](C1_refinement_snr_24000_qpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0.000252764 | 0.976765 | 27404.5 | — |
| [C1_refinement_snr_24000_qpsk_bch_6dB](C1_refinement_snr_24000_qpsk_bch_6dB/7446529.json) | characterize / full | characterized | 1.06802e-05 | 0.999089 | 28031 | — |
| [C1_refinement_snr_24000_qpsk_bch_8dB](C1_refinement_snr_24000_qpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28056.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_0dB](C1_refinement_snr_24000_qpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0.0196265 | 0.197267 | 5533.55 | — |
| [C1_refinement_snr_24000_qpsk_soft_10dB](C1_refinement_snr_24000_qpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_12dB](C1_refinement_snr_24000_qpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_14dB](C1_refinement_snr_24000_qpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_16dB](C1_refinement_snr_24000_qpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_18dB](C1_refinement_snr_24000_qpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_20dB](C1_refinement_snr_24000_qpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_22dB](C1_refinement_snr_24000_qpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_24dB](C1_refinement_snr_24000_qpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_26dB](C1_refinement_snr_24000_qpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_28dB](C1_refinement_snr_24000_qpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_2dB](C1_refinement_snr_24000_qpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0.00302551 | 0.77221 | 21666 | — |
| [C1_refinement_snr_24000_qpsk_soft_30dB](C1_refinement_snr_24000_qpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_refinement_snr_24000_qpsk_soft_4dB](C1_refinement_snr_24000_qpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0.00018865 | 0.983144 | 27584.7 | — |
| [C1_refinement_snr_24000_qpsk_soft_6dB](C1_refinement_snr_24000_qpsk_soft_6dB/7446529.json) | characterize / full | characterized | 3.55943e-06 | 0.999544 | 28044.8 | — |
| [C1_refinement_snr_24000_qpsk_soft_8dB](C1_refinement_snr_24000_qpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |

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
| [C4_refinement_10000_8psk_soft_null](C4_refinement_10000_8psk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 17368.9 | — |
| [C4_refinement_10000_bpsk_bch_null](C4_refinement_10000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 5786.27 | — |
| [C4_refinement_10000_bpsk_bch_p16_r16_null](C4_refinement_10000_bpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 5552.21 | — |
| [C4_refinement_10000_bpsk_bch_p32_r4_null](C4_refinement_10000_bpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | 0 | 1 | 3465.07 | — |
| [C4_refinement_10000_bpsk_bch_p32_r64_null](C4_refinement_10000_bpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | 0 | 1 | 6949.28 | — |
| [C4_refinement_10000_bpsk_bch_p64_r16_null](C4_refinement_10000_bpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 5951.85 | — |
| [C4_refinement_10000_bpsk_soft_null](C4_refinement_10000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_refinement_10000_diversity_commensurate_both_null](C4_refinement_10000_diversity_commensurate_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_commensurate_lower_null](C4_refinement_10000_diversity_commensurate_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_commensurate_upper_null](C4_refinement_10000_diversity_commensurate_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_offset137_both_null](C4_refinement_10000_diversity_offset137_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_offset137_lower_null](C4_refinement_10000_diversity_offset137_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_offset137_upper_null](C4_refinement_10000_diversity_offset137_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_wide137_both_null](C4_refinement_10000_diversity_wide137_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_wide137_lower_null](C4_refinement_10000_diversity_wide137_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_diversity_wide137_upper_null](C4_refinement_10000_diversity_wide137_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 2330.95 | — |
| [C4_refinement_10000_qpsk_bch_null](C4_refinement_10000_qpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 11576.9 | — |
| [C4_refinement_10000_qpsk_bch_p16_r16_null](C4_refinement_10000_qpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 11108.4 | — |
| [C4_refinement_10000_qpsk_bch_p32_r4_null](C4_refinement_10000_qpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | 0 | 1 | 6940.97 | — |
| [C4_refinement_10000_qpsk_bch_p32_r64_null](C4_refinement_10000_qpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | 0 | 1 | 13898.6 | — |
| [C4_refinement_10000_qpsk_bch_p64_r16_null](C4_refinement_10000_qpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 11908.6 | — |
| [C4_refinement_10000_qpsk_soft_null](C4_refinement_10000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_refinement_24000_8psk_bch_null](C4_refinement_24000_8psk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 41947.4 | — |
| [C4_refinement_24000_8psk_soft_null](C4_refinement_24000_8psk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 41950.2 | — |
| [C4_refinement_24000_bpsk_bch_null](C4_refinement_24000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981.1 | — |
| [C4_refinement_24000_bpsk_bch_p16_r16_null](C4_refinement_24000_bpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 13383.2 | — |
| [C4_refinement_24000_bpsk_bch_p32_r4_null](C4_refinement_24000_bpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | 0 | 1 | 8401.95 | — |
| [C4_refinement_24000_bpsk_bch_p32_r64_null](C4_refinement_24000_bpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | 0 | 1 | 16803.9 | — |
| [C4_refinement_24000_bpsk_bch_p64_r16_null](C4_refinement_24000_bpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 14305.2 | — |
| [C4_refinement_24000_bpsk_soft_null](C4_refinement_24000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_refinement_24000_diversity_commensurate_both_null](C4_refinement_24000_diversity_commensurate_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_commensurate_lower_null](C4_refinement_24000_diversity_commensurate_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_commensurate_upper_null](C4_refinement_24000_diversity_commensurate_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_offset137_both_null](C4_refinement_24000_diversity_offset137_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_offset137_lower_null](C4_refinement_24000_diversity_offset137_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_offset137_upper_null](C4_refinement_24000_diversity_offset137_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_wide137_both_null](C4_refinement_24000_diversity_wide137_both_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_wide137_lower_null](C4_refinement_24000_diversity_wide137_lower_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_diversity_wide137_upper_null](C4_refinement_24000_diversity_wide137_upper_null/7446529.json) | assert / quick | pass | 0 | 1 | 5577.42 | — |
| [C4_refinement_24000_qpsk_bch_null](C4_refinement_24000_qpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.5 | — |
| [C4_refinement_24000_qpsk_bch_p16_r16_null](C4_refinement_24000_qpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 26770.3 | — |
| [C4_refinement_24000_qpsk_bch_p32_r4_null](C4_refinement_24000_qpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | 0 | 1 | 16814.1 | — |
| [C4_refinement_24000_qpsk_bch_p32_r64_null](C4_refinement_24000_qpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | 0 | 1 | 33607.9 | — |
| [C4_refinement_24000_qpsk_bch_p64_r16_null](C4_refinement_24000_qpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | 0 | 1 | 28615.1 | — |
| [C4_refinement_24000_qpsk_soft_null](C4_refinement_24000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |

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
| [D4_refinement_10000_8psk_bch_null](D4_refinement_10000_8psk_bch_null/7446529.json) | assert / quick | pass | — | — | 2349.33 | 50 |
| [D4_refinement_10000_8psk_soft_null](D4_refinement_10000_8psk_soft_null/7446529.json) | assert / quick | pass | — | — | 2338.67 | 54 |
| [D4_refinement_10000_bpsk_bch_null](D4_refinement_10000_bpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 1128 | 80 |
| [D4_refinement_10000_bpsk_bch_p16_r16_null](D4_refinement_10000_bpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | — | — | 1066.67 | 83 |
| [D4_refinement_10000_bpsk_bch_p32_r4_null](D4_refinement_10000_bpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | — | — | 669.333 | 96 |
| [D4_refinement_10000_bpsk_bch_p32_r64_null](D4_refinement_10000_bpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | — | — | 1344 | 81 |
| [D4_refinement_10000_bpsk_bch_p64_r16_null](D4_refinement_10000_bpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | — | — | 1157.33 | 80 |
| [D4_refinement_10000_bpsk_soft_null](D4_refinement_10000_bpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 813.333 | 89 |
| [D4_refinement_10000_diversity_commensurate_both_null](D4_refinement_10000_diversity_commensurate_both_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_commensurate_lower_null](D4_refinement_10000_diversity_commensurate_lower_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_commensurate_upper_null](D4_refinement_10000_diversity_commensurate_upper_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_offset137_both_null](D4_refinement_10000_diversity_offset137_both_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_offset137_lower_null](D4_refinement_10000_diversity_offset137_lower_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_offset137_upper_null](D4_refinement_10000_diversity_offset137_upper_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_wide137_both_null](D4_refinement_10000_diversity_wide137_both_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_wide137_lower_null](D4_refinement_10000_diversity_wide137_lower_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_diversity_wide137_upper_null](D4_refinement_10000_diversity_wide137_upper_null/7446529.json) | assert / quick | pass | — | — | 440 | 208 |
| [D4_refinement_10000_qpsk_bch_null](D4_refinement_10000_qpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 2224 | 57 |
| [D4_refinement_10000_qpsk_bch_p16_r16_null](D4_refinement_10000_qpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | — | — | 2133.33 | 65 |
| [D4_refinement_10000_qpsk_bch_p32_r4_null](D4_refinement_10000_qpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | — | — | 1325.33 | 65 |
| [D4_refinement_10000_qpsk_bch_p32_r64_null](D4_refinement_10000_qpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | — | — | 2650.67 | 61 |
| [D4_refinement_10000_qpsk_bch_p64_r16_null](D4_refinement_10000_qpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | — | — | 2208 | 56 |
| [D4_refinement_10000_qpsk_soft_null](D4_refinement_10000_qpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 1632 | 69 |
| [D4_refinement_24000_8psk_bch_null](D4_refinement_24000_8psk_bch_null/7446529.json) | assert / quick | pass | — | — | 2586.67 | 21 |
| [D4_refinement_24000_8psk_soft_null](D4_refinement_24000_8psk_soft_null/7446529.json) | assert / quick | pass | — | — | 2485.33 | 23 |
| [D4_refinement_24000_bpsk_bch_null](D4_refinement_24000_bpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 2450.67 | 30 |
| [D4_refinement_24000_bpsk_bch_p16_r16_null](D4_refinement_24000_bpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | — | — | 2469.33 | 31 |
| [D4_refinement_24000_bpsk_bch_p32_r4_null](D4_refinement_24000_bpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | — | — | 1600 | 39 |
| [D4_refinement_24000_bpsk_bch_p32_r64_null](D4_refinement_24000_bpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | — | — | 2728 | 30 |
| [D4_refinement_24000_bpsk_bch_p64_r16_null](D4_refinement_24000_bpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | — | — | 2450.67 | 30 |
| [D4_refinement_24000_bpsk_soft_null](D4_refinement_24000_bpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 1970.67 | 43 |
| [D4_refinement_24000_diversity_commensurate_both_null](D4_refinement_24000_diversity_commensurate_both_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_commensurate_lower_null](D4_refinement_24000_diversity_commensurate_lower_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_commensurate_upper_null](D4_refinement_24000_diversity_commensurate_upper_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_offset137_both_null](D4_refinement_24000_diversity_offset137_both_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_offset137_lower_null](D4_refinement_24000_diversity_offset137_lower_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_offset137_upper_null](D4_refinement_24000_diversity_offset137_upper_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_wide137_both_null](D4_refinement_24000_diversity_wide137_both_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_wide137_lower_null](D4_refinement_24000_diversity_wide137_lower_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_diversity_wide137_upper_null](D4_refinement_24000_diversity_wide137_upper_null/7446529.json) | assert / quick | pass | — | — | 1077.33 | 83 |
| [D4_refinement_24000_qpsk_bch_null](D4_refinement_24000_qpsk_bch_null/7446529.json) | assert / quick | pass | — | — | 2506.67 | 24 |
| [D4_refinement_24000_qpsk_bch_p16_r16_null](D4_refinement_24000_qpsk_bch_p16_r16_null/7446529.json) | assert / quick | pass | — | — | 2496 | 24 |
| [D4_refinement_24000_qpsk_bch_p32_r4_null](D4_refinement_24000_qpsk_bch_p32_r4_null/7446529.json) | assert / quick | pass | — | — | 2029.33 | 23 |
| [D4_refinement_24000_qpsk_bch_p32_r64_null](D4_refinement_24000_qpsk_bch_p32_r64_null/7446529.json) | assert / quick | pass | — | — | 2757.33 | 23 |
| [D4_refinement_24000_qpsk_bch_p64_r16_null](D4_refinement_24000_qpsk_bch_p64_r16_null/7446529.json) | assert / quick | pass | — | — | 2514.67 | 23 |
| [D4_refinement_24000_qpsk_soft_null](D4_refinement_24000_qpsk_soft_null/7446529.json) | assert / quick | pass | — | — | 2450.67 | 26 |

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
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 77.76 | 89 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 75.6267 | 28 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_moderate](E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 57.5733 | 88 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2195.12 | 80 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2204.51 | 80 |
| [E2_refinement_followup_10000_8psk_bch_high_lat_quiet](E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2209.63 | 80 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_disturbed](E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 75.3067 | 93 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 77.4933 | 25 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_moderate](E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 68.9067 | 93 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2193.63 | 84 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2203.76 | 84 |
| [E2_refinement_followup_10000_8psk_soft_high_lat_quiet](E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2215.49 | 84 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.32 | 39 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.96 | 48 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 165.973 | 122 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 174.693 | 120 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 158 | 122 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1045.81 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1046.13 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1057.87 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.96 | 50 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.32 | 48 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 173.067 | 122 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 172.64 | 124 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 167.68 | 123 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1006.13 | 113 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1015.73 | 113 |
| [E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1013.17 | 113 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 82.6133 | 123 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 90.9867 | 124 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 84.2933 | 123 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 525.867 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 525.227 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 525.52 | 111 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 78.3467 | 48 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 77.12 | 48 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 67.92 | 97 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1378.21 | 110 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1396.13 | 110 |
| [E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1399.33 | 110 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.64 | 48 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.96 | 51 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 54 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 157.013 | 119 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 166.64 | 121 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 158.613 | 122 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1072.16 | 110 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1070.13 | 110 |
| [E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1074.83 | 110 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.96 | 52 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 118.907 | 130 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 130.453 | 130 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_moderate](E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 110.24 | 130 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 756.773 | 119 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 756.667 | 119 |
| [E2_refinement_followup_10000_bpsk_soft_high_lat_quiet](E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 766.053 | 119 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.86667 | 95 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.45333 | 97 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.70667 | 95 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 404.72 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 401.733 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 410.693 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.70667 | 95 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1.70667 | 96 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.70667 | 91 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 408.987 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 416.347 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 414.747 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.17333 | 95 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1.81333 | 96 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.38667 | 91 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 409.52 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 415.707 | 254 |
| [E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 415.92 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.84 | 94 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.66667 | 95 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.38667 | 94 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 415.813 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 409.2 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 415.067 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.24 | 92 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1.70667 | 92 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.6 | 95 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 408.453 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 417.733 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 415.387 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.45333 | 93 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.13333 | 94 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 0.96 | 93 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 407.173 | 254 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 415.707 | 253 |
| [E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 415.6 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.89333 | 93 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.02667 | 97 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.98667 | 94 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 412.4 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 413.573 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 413.787 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.41333 | 91 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.02667 | 94 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.17333 | 91 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 411.44 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 415.707 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 412.933 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.02667 | 95 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1.81333 | 96 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.17333 | 91 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 411.013 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 415.813 | 254 |
| [E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 414.853 | 254 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.64 | 33 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 194.347 | 103 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 181.333 | 102 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 153.787 | 105 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2046.69 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2053.73 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2072.19 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 177.493 | 104 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 179.76 | 103 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 184.96 | 106 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2004.59 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2023.89 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2019.41 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.64 | 30 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.64 | 37 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 153.6 | 105 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 161.92 | 104 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 159.627 | 104 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1041.25 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1041.89 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1040.43 | 95 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 63.5733 | 32 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 66.1333 | 32 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 59.8133 | 70 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2735.71 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2786.05 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2773.25 | 88 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.32 | 24 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.64 | 23 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 169.52 | 98 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 175.627 | 100 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 160.667 | 100 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2112 | 90 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2110.4 | 90 |
| [E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2117.33 | 90 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 139.173 | 107 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 145.12 | 110 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_moderate](E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 117.84 | 108 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1516.35 | 99 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1521.36 | 99 |
| [E2_refinement_followup_10000_qpsk_soft_high_lat_quiet](E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1535.87 | 99 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 3.2 | 26 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 3.84 | 27 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_disturbed](E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 6 | 19 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 513.813 | 49 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 495.147 | 49 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_moderate](E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 492.907 | 49 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2400.27 | 37 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2402.61 | 37 |
| [E2_refinement_followup_24000_8psk_bch_high_lat_quiet](E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2400.48 | 37 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 6.4 | 24 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 4.48 | 24 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_disturbed](E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 5.92 | 22 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 483.6 | 51 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 465.867 | 51 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_moderate](E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 463.707 | 51 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2424.88 | 39 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2427.87 | 39 |
| [E2_refinement_followup_24000_8psk_soft_high_lat_quiet](E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2426.59 | 39 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 44.08 | 88 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 49.44 | 89 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 39.04 | 36 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1219.79 | 58 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1194.32 | 58 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1179.68 | 58 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2314.88 | 48 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2316.8 | 48 |
| [E2_refinement_followup_24000_bpsk_bch_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2318.08 | 48 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 55.6 | 93 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 56.32 | 98 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 31.04 | 88 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1194.19 | 62 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1221.04 | 61 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1208.11 | 61 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2262.99 | 51 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2262.24 | 51 |
| [E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2269.81 | 51 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 7.6 | 96 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 10.88 | 103 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 8.88 | 99 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 534.133 | 68 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 520.373 | 68 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 514.56 | 68 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1193.71 | 56 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1194.35 | 56 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1197.36 | 56 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 18.32 | 36 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 18.72 | 90 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 18.56 | 37 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1038.05 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1033.52 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1024.59 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2888.43 | 46 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2901.65 | 46 |
| [E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2879.47 | 46 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 23.92 | 34 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 51.28 | 95 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 39.84 | 89 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1145.15 | 58 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1145.31 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1124.45 | 57 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2304.32 | 46 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2303.57 | 46 |
| [E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2305.6 | 46 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 32.16 | 110 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 36.96 | 109 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 29.12 | 108 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 962.827 | 71 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 939.44 | 71 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_moderate](E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 917.893 | 71 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1798.8 | 59 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1798.91 | 59 |
| [E2_refinement_followup_24000_bpsk_soft_high_lat_quiet](E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1803.39 | 59 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 168.747 | 127 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 154.107 | 127 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 149.627 | 127 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 995.467 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 979.467 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 994.613 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 148.453 | 126 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 141.493 | 127 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 134.56 | 126 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1013.07 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1006.99 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1012.32 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 142.96 | 125 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 137.36 | 126 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 135.84 | 126 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1013.28 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1006.77 | 115 |
| [E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1014.45 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 38 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 192.747 | 128 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 193.12 | 127 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 183.467 | 127 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1012.43 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1006.03 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1005.17 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 144.72 | 124 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 135.333 | 124 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 134.48 | 125 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1013.39 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1007.84 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1007.31 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.32 | 36 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 133.173 | 124 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 142.48 | 126 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 128.213 | 125 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1013.71 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1012.96 | 115 |
| [E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1012.96 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.64 | 45 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 38 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 172.48 | 127 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 160.053 | 127 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 147.147 | 127 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1017.76 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1016.91 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1014.77 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 38 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 147.333 | 126 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 146.613 | 127 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 130.8 | 126 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1010.29 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1009.33 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1012.75 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 146.347 | 125 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 141.6 | 127 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 138.507 | 126 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1012.32 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1013.17 | 115 |
| [E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet](E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1008.48 | 115 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 22.56 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 29.36 | 29 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 19.76 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1007.92 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 992.907 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 955.227 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2389.09 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2388.99 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2388.99 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 20 | 30 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 28 | 29 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 18.88 | 30 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 999.2 | 52 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1034.88 | 52 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1034.03 | 52 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2415.87 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2415.76 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2415.87 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 14 | 29 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 18.88 | 29 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 16.96 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 722.667 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 705.04 | 52 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 685.227 | 52 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1619.39 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1619.28 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1619.39 | 40 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 3.92 | 25 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 6.72 | 25 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 4.48 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 635.493 | 48 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 635.52 | 49 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 593.52 | 48 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2918.61 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2920.96 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2922.03 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 15.2 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 23.04 | 28 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 18.08 | 27 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 954.853 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 947.413 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 925.547 | 51 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2372.99 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2373.41 | 39 |
| [E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet](E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2373.41 | 39 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 18.56 | 31 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 26.08 | 85 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed](E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 17.28 | 30 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 991.787 | 54 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 980 | 54 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_moderate](E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 945.92 | 54 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2429.57 | 42 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2429.36 | 42 |
| [E2_refinement_followup_24000_qpsk_soft_high_lat_quiet](E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2429.57 | 42 |

### Simulated channel E2 local metric definitions

| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |
| --- | --- | --- | --- | --- |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.00743 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.00381 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_disturbed | 0.00981 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.09496333333333333 | 0.5233333333333333 | 77.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.09423333333333334 | 0.5666666666666667 | 75.62666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_moderate | 0.08633333333333333 | 0.49666666666666665 | 57.57333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.6750466666666667 | 1.0 | 2195.12 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.6772633333333333 | 1.0 | 2204.5066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_bch_high_lat_quiet | 0.67936 | 1.0 | 2209.6266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.00733 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.0037199999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_disturbed | 0.00977 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.09289333333333333 | 0.56 | 75.30666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.09411 | 0.5666666666666667 | 77.49333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_moderate | 0.08879333333333334 | 0.5233333333333333 | 68.90666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.6748166666666666 | 1.0 | 2193.6266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.6773766666666666 | 1.0 | 2203.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_8psk_soft_high_lat_quiet | 0.6810566666666666 | 1.0 | 2215.4933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.0218 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.014610000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed | 0.01895 | 0.02 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.27013333333333334 | 0.8433333333333334 | 165.97333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.27465 | 0.8533333333333334 | 174.69333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_moderate | 0.2580033333333333 | 0.84 | 158.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6770633333333334 | 1.0 | 1045.8133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6776 | 1.0 | 1046.1333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_high_lat_quiet | 0.6836533333333333 | 1.0 | 1057.8666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed | 0.01529 | 0.01 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed | 0.01228 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_disturbed | 0.0174 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate | 0.29975666666666667 | 0.8933333333333333 | 173.06666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate | 0.29213 | 0.8466666666666667 | 172.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_moderate | 0.29217 | 0.8833333333333333 | 167.68 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet | 0.6891866666666666 | 1.0 | 1006.1333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet | 0.69415 | 1.0 | 1015.7333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p16_r16_high_lat_quiet | 0.69264 | 1.0 | 1013.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed | 0.021070000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed | 0.02298 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_disturbed | 0.01618 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate | 0.23269333333333336 | 0.8266666666666667 | 82.61333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate | 0.2397866666666667 | 0.8433333333333334 | 90.98666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_moderate | 0.23155666666666666 | 0.86 | 84.29333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet | 0.37209 | 1.0 | 525.8666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet | 0.37195999999999996 | 1.0 | 525.2266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r4_high_lat_quiet | 0.3719633333333333 | 1.0 | 525.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed | 0.01351 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed | 0.007940000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_disturbed | 0.03144 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate | 0.15953333333333333 | 0.5333333333333333 | 78.34666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate | 0.13766333333333333 | 0.49 | 77.12 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_moderate | 0.14103 | 0.48333333333333334 | 67.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet | 0.8725766666666668 | 1.0 | 1378.2133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet | 0.8823600000000001 | 1.0 | 1396.1333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p32_r64_high_lat_quiet | 0.8846033333333332 | 1.0 | 1399.3333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed | 0.019950000000000002 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed | 0.0154 | 0.01 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_disturbed | 0.02222 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate | 0.28789333333333333 | 0.87 | 157.01333333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate | 0.28936 | 0.86 | 166.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_moderate | 0.28526666666666667 | 0.8566666666666667 | 158.61333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet | 0.67408 | 1.0 | 1072.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet | 0.67272 | 1.0 | 1070.1333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_bch_p64_r16_high_lat_quiet | 0.6754433333333334 | 1.0 | 1074.8266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.0215 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.01652 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed | 0.01796 | 0.02 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.27199666666666666 | 0.8266666666666667 | 118.90666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.28069333333333335 | 0.8533333333333334 | 130.45333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_moderate | 0.2543333333333333 | 0.84 | 110.24 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6771333333333333 | 1.0 | 756.7733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6776 | 1.0 | 756.6666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_bpsk_soft_high_lat_quiet | 0.6836666666666666 | 1.0 | 766.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate | 0.026143333333333334 | 0.04 | 1.8666666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate | 0.03347 | 0.056666666666666664 | 2.453333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_moderate | 0.030433333333333337 | 0.03666666666666667 | 1.7066666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet | 0.65962 | 1.0 | 404.72 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet | 0.6533866666666667 | 0.9933333333333333 | 401.73333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_both_high_lat_quiet | 0.6653633333333334 | 1.0 | 410.6933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate | 0.020933333333333335 | 0.03666666666666667 | 1.7066666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate | 0.02679 | 0.043333333333333335 | 1.7066666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_moderate | 0.02424 | 0.03666666666666667 | 1.7066666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet | 0.66352 | 1.0 | 408.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet | 0.6724533333333333 | 1.0 | 416.3466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_lower_high_lat_quiet | 0.6708866666666666 | 1.0 | 414.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate | 0.019880000000000002 | 0.02666666666666667 | 1.1733333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate | 0.026533333333333332 | 0.03666666666666667 | 1.8133333333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_moderate | 0.02342 | 0.02666666666666667 | 1.3866666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet | 0.6636966666666667 | 1.0 | 409.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet | 0.6725933333333333 | 1.0 | 415.70666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_commensurate_upper_high_lat_quiet | 0.6722766666666666 | 1.0 | 415.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate | 0.03091666666666667 | 0.06666666666666667 | 3.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate | 0.03308666666666667 | 0.056666666666666664 | 2.6666666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_moderate | 0.03252666666666666 | 0.03666666666666667 | 1.3866666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet | 0.6727 | 1.0 | 415.81333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet | 0.66355 | 0.9966666666666667 | 409.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_both_high_lat_quiet | 0.6704233333333334 | 1.0 | 415.06666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate | 0.024723333333333333 | 0.03666666666666667 | 2.24 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate | 0.025943333333333336 | 0.03333333333333333 | 1.7066666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_moderate | 0.02096 | 0.03666666666666667 | 1.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet | 0.6637599999999999 | 1.0 | 408.4533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet | 0.6736000000000001 | 1.0 | 417.73333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_lower_high_lat_quiet | 0.67157 | 1.0 | 415.38666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate | 0.02068666666666667 | 0.043333333333333335 | 2.453333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate | 0.024663333333333332 | 0.04 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_moderate | 0.017663333333333333 | 0.02666666666666667 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet | 0.6603233333333334 | 1.0 | 407.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet | 0.6727 | 1.0 | 415.70666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_offset137_upper_high_lat_quiet | 0.6699900000000001 | 1.0 | 415.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate | 0.025746666666666668 | 0.043333333333333335 | 1.8933333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate | 0.03407666666666667 | 0.05 | 2.026666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_moderate | 0.031323333333333335 | 0.06 | 2.986666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet | 0.6663966666666667 | 1.0 | 412.4 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet | 0.6675266666666667 | 0.9966666666666667 | 413.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_both_high_lat_quiet | 0.6707266666666666 | 1.0 | 413.7866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate | 0.01965333333333333 | 0.03333333333333333 | 1.4133333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate | 0.024116666666666668 | 0.04666666666666667 | 2.026666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_moderate | 0.019663333333333335 | 0.02666666666666667 | 1.1733333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet | 0.6659366666666667 | 1.0 | 411.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet | 0.6724333333333333 | 1.0 | 415.70666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_lower_high_lat_quiet | 0.6679466666666666 | 1.0 | 412.93333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate | 0.02013 | 0.04 | 2.026666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate | 0.025599999999999998 | 0.043333333333333335 | 1.8133333333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_moderate | 0.020296666666666668 | 0.02666666666666667 | 1.1733333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet | 0.6653933333333333 | 1.0 | 411.0133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet | 0.6703533333333334 | 1.0 | 415.81333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_diversity_wide137_upper_high_lat_quiet | 0.6708433333333332 | 1.0 | 414.85333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.01303 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.00943 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed | 0.01303 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.16247999999999999 | 0.81 | 194.34666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.15707000000000002 | 0.8 | 181.33333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_moderate | 0.14325333333333334 | 0.7466666666666667 | 153.78666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6765866666666667 | 1.0 | 2046.6933333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6785333333333333 | 1.0 | 2053.733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_high_lat_quiet | 0.6840233333333333 | 1.0 | 2072.1866666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed | 0.00639 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed | 0.006750000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_disturbed | 0.00754 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate | 0.14794 | 0.7733333333333333 | 177.49333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate | 0.15013333333333334 | 0.7633333333333333 | 179.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_moderate | 0.14984666666666666 | 0.8033333333333333 | 184.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet | 0.6885966666666667 | 1.0 | 2004.5866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet | 0.6946666666666667 | 1.0 | 2023.8933333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p16_r16_high_lat_quiet | 0.6931633333333334 | 1.0 | 2019.4133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed | 0.01555 | 0.01 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed | 0.01617 | 0.01 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_disturbed | 0.01351 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate | 0.19628666666666666 | 0.9366666666666666 | 153.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate | 0.19859 | 0.94 | 161.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_moderate | 0.19614666666666666 | 0.94 | 159.62666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet | 0.37209 | 1.0 | 1041.2533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet | 0.37221333333333334 | 1.0 | 1041.8933333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r4_high_lat_quiet | 0.37188 | 1.0 | 1040.4266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed | 0.00367 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed | 0.00627 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_disturbed | 0.0086 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate | 0.05425666666666667 | 0.3933333333333333 | 63.57333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate | 0.059626666666666675 | 0.38 | 66.13333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_moderate | 0.05120333333333334 | 0.39666666666666667 | 59.81333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet | 0.8687400000000001 | 1.0 | 2735.7066666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet | 0.8837766666666667 | 1.0 | 2786.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p32_r64_high_lat_quiet | 0.8803466666666666 | 1.0 | 2773.2533333333336 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed | 0.01286 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed | 0.0102 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_disturbed | 0.01614 | 0.01 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate | 0.17763666666666666 | 0.7933333333333333 | 169.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate | 0.18152333333333334 | 0.78 | 175.62666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_moderate | 0.17562 | 0.7533333333333333 | 160.66666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet | 0.6734 | 1.0 | 2112.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet | 0.67272 | 1.0 | 2110.4 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_bch_p64_r16_high_lat_quiet | 0.67494 | 1.0 | 2117.3333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.01081 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.00877 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed | 0.01367 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.15657333333333334 | 0.8066666666666666 | 139.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.16047999999999998 | 0.7833333333333333 | 145.12 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_moderate | 0.14287666666666665 | 0.7466666666666667 | 117.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.67653 | 1.0 | 1516.3466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.6785333333333333 | 1.0 | 1521.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_10000_qpsk_soft_high_lat_quiet | 0.6841333333333334 | 1.0 | 1535.8666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.20738 | 0.07 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.20817 | 0.07 | 3.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_disturbed | 0.22396999999999997 | 0.09 | 6.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.28631666666666666 | 0.9933333333333333 | 513.8133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.28191 | 0.9933333333333333 | 495.14666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_moderate | 0.2806666666666667 | 1.0 | 492.9066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6904066666666667 | 1.0 | 2400.266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6910000000000001 | 1.0 | 2402.6133333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_bch_high_lat_quiet | 0.6903566666666666 | 1.0 | 2400.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.20987999999999998 | 0.12 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.20362 | 0.1 | 4.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_disturbed | 0.22399999999999998 | 0.12 | 5.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.28659 | 0.9966666666666667 | 483.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.28172 | 0.9966666666666667 | 465.8666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_moderate | 0.27996 | 1.0 | 463.70666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.69019 | 1.0 | 2424.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.6908566666666667 | 1.0 | 2427.866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_8psk_soft_high_lat_quiet | 0.6907266666666666 | 1.0 | 2426.5866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.31396999999999997 | 0.51 | 44.08 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.31864000000000003 | 0.46 | 49.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed | 0.34264000000000006 | 0.37 | 39.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5647233333333334 | 1.0 | 1219.7866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5595533333333333 | 1.0 | 1194.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_moderate | 0.5539233333333333 | 1.0 | 1179.68 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.6900433333333333 | 1.0 | 2314.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.6900533333333333 | 1.0 | 2316.8 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_high_lat_quiet | 0.6902833333333334 | 1.0 | 2318.08 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed | 0.33075000000000004 | 0.48 | 55.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed | 0.31383 | 0.48 | 56.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_disturbed | 0.30712 | 0.28 | 31.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate | 0.5753266666666668 | 1.0 | 1194.1866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate | 0.5777333333333333 | 1.0 | 1221.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_moderate | 0.5803866666666667 | 1.0 | 1208.1066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet | 0.7008166666666666 | 1.0 | 2262.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet | 0.7008666666666666 | 1.0 | 2262.24 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p16_r16_high_lat_quiet | 0.7023333333333333 | 1.0 | 2269.8133333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed | 0.22672 | 0.22 | 7.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed | 0.2359 | 0.29 | 10.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_disturbed | 0.22384 | 0.22 | 8.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate | 0.41389 | 1.0 | 534.1333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate | 0.41289000000000003 | 1.0 | 520.3733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_moderate | 0.41391333333333336 | 1.0 | 514.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet | 0.3976166666666667 | 1.0 | 1193.7066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet | 0.39760333333333336 | 1.0 | 1194.3466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r4_high_lat_quiet | 0.39760333333333336 | 1.0 | 1197.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed | 0.38061 | 0.16 | 18.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed | 0.41197 | 0.18 | 18.72 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_disturbed | 0.44142000000000003 | 0.19 | 18.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate | 0.49953000000000003 | 0.9833333333333333 | 1038.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate | 0.49089333333333335 | 0.98 | 1033.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_moderate | 0.48208 | 0.9933333333333333 | 1024.5866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet | 0.8921133333333334 | 1.0 | 2888.4266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet | 0.8956700000000001 | 1.0 | 2901.653333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p32_r64_high_lat_quiet | 0.89061 | 1.0 | 2879.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed | 0.30598 | 0.31 | 23.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed | 0.30818 | 0.44 | 51.28 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_disturbed | 0.31062 | 0.36 | 39.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate | 0.5537766666666667 | 1.0 | 1145.1466666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate | 0.55409 | 1.0 | 1145.3066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_moderate | 0.55206 | 1.0 | 1124.4533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet | 0.6841166666666667 | 1.0 | 2304.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet | 0.6842666666666667 | 1.0 | 2303.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_bch_p64_r16_high_lat_quiet | 0.6844399999999999 | 1.0 | 2305.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.31297 | 0.43 | 32.16 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.32025 | 0.41 | 36.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed | 0.33845 | 0.32 | 29.12 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.5647566666666667 | 1.0 | 962.8266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.55883 | 1.0 | 939.44 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_moderate | 0.5547133333333333 | 1.0 | 917.8933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.6900533333333333 | 1.0 | 1798.8 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.6900633333333334 | 1.0 | 1798.9066666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_bpsk_soft_high_lat_quiet | 0.69096 | 1.0 | 1803.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed | 0.01448 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed | 0.02414 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_disturbed | 0.0308 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate | 0.27756000000000003 | 0.8466666666666667 | 168.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate | 0.2815533333333333 | 0.84 | 154.10666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_moderate | 0.27282 | 0.82 | 149.62666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet | 0.67229 | 1.0 | 995.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet | 0.6629866666666666 | 1.0 | 979.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_both_high_lat_quiet | 0.6718700000000001 | 1.0 | 994.6133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed | 0.01829 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed | 0.02323 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_disturbed | 0.02675 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate | 0.24770666666666666 | 0.8266666666666667 | 148.45333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate | 0.25148 | 0.85 | 141.49333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_moderate | 0.24512 | 0.8133333333333334 | 134.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet | 0.68313 | 1.0 | 1013.0666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet | 0.6792199999999999 | 1.0 | 1006.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_lower_high_lat_quiet | 0.6824866666666667 | 1.0 | 1012.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed | 0.018779999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed | 0.021840000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_disturbed | 0.02528 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate | 0.24248333333333336 | 0.8266666666666667 | 142.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate | 0.24825666666666668 | 0.8433333333333334 | 137.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_moderate | 0.24535666666666667 | 0.8166666666666667 | 135.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet | 0.6832033333333334 | 1.0 | 1013.28 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet | 0.6794133333333334 | 1.0 | 1006.7733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_commensurate_upper_high_lat_quiet | 0.6836933333333334 | 1.0 | 1014.4533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed | 0.01645 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed | 0.020390000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_disturbed | 0.024700000000000003 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate | 0.3165133333333333 | 0.8966666666666666 | 192.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate | 0.3222766666666667 | 0.9233333333333333 | 193.12 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_moderate | 0.3114266666666667 | 0.87 | 183.46666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet | 0.6821133333333332 | 1.0 | 1012.4266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet | 0.67821 | 1.0 | 1006.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_both_high_lat_quiet | 0.67823 | 1.0 | 1005.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed | 0.013720000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed | 0.01558 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_disturbed | 0.0248 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate | 0.24538000000000001 | 0.8033333333333333 | 144.72 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate | 0.25064 | 0.8566666666666667 | 135.33333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_moderate | 0.24413 | 0.8233333333333334 | 134.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet | 0.6826666666666668 | 1.0 | 1013.3866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet | 0.6800233333333333 | 1.0 | 1007.84 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_lower_high_lat_quiet | 0.6809200000000001 | 1.0 | 1007.3066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed | 0.01394 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed | 0.02266 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_disturbed | 0.02466 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate | 0.24306000000000003 | 0.7966666666666666 | 133.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate | 0.25317666666666666 | 0.85 | 142.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_moderate | 0.23947 | 0.8066666666666666 | 128.21333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet | 0.6831733333333333 | 1.0 | 1013.7066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet | 0.6825 | 1.0 | 1012.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_offset137_upper_high_lat_quiet | 0.6828933333333334 | 1.0 | 1012.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed | 0.024 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed | 0.02704 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_disturbed | 0.03202 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate | 0.28226333333333337 | 0.8466666666666667 | 172.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate | 0.2902333333333333 | 0.83 | 160.05333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_moderate | 0.2768733333333333 | 0.8266666666666667 | 147.14666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet | 0.6849733333333333 | 1.0 | 1017.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet | 0.6843933333333334 | 1.0 | 1016.9066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_both_high_lat_quiet | 0.6835366666666667 | 1.0 | 1014.7733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed | 0.01602 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed | 0.014530000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_disturbed | 0.03031 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate | 0.24260666666666666 | 0.8266666666666667 | 147.33333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate | 0.2546833333333333 | 0.8366666666666667 | 146.61333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_moderate | 0.24623666666666666 | 0.7933333333333333 | 130.8 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet | 0.6822566666666666 | 1.0 | 1010.2933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet | 0.6804966666666666 | 1.0 | 1009.3333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_lower_high_lat_quiet | 0.6830266666666667 | 1.0 | 1012.7466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed | 0.01536 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed | 0.015449999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_disturbed | 0.02028 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate | 0.24345 | 0.8233333333333334 | 146.34666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate | 0.2533866666666667 | 0.8266666666666667 | 141.6 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_moderate | 0.24916000000000002 | 0.81 | 138.50666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet | 0.6821900000000001 | 1.0 | 1012.32 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet | 0.68249 | 1.0 | 1013.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_diversity_wide137_upper_high_lat_quiet | 0.6810566666666666 | 1.0 | 1008.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.26587 | 0.31 | 22.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.25587 | 0.35 | 29.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed | 0.27549 | 0.24 | 19.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.4473333333333333 | 1.0 | 1007.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.4427933333333333 | 1.0 | 992.9066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_moderate | 0.43326000000000003 | 1.0 | 955.2266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.6920266666666667 | 1.0 | 2389.0933333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.6920233333333333 | 1.0 | 2388.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_high_lat_quiet | 0.69202 | 1.0 | 2388.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed | 0.26211 | 0.25 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed | 0.25476 | 0.34 | 28.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_disturbed | 0.25056 | 0.25 | 18.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate | 0.4425533333333333 | 1.0 | 999.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate | 0.45278 | 1.0 | 1034.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_moderate | 0.45071 | 1.0 | 1034.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet | 0.7033733333333333 | 1.0 | 2415.866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet | 0.7033733333333333 | 1.0 | 2415.76 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p16_r16_high_lat_quiet | 0.7033566666666666 | 1.0 | 2415.866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed | 0.20722000000000002 | 0.26 | 14.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed | 0.21591000000000002 | 0.36 | 18.88 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_disturbed | 0.20687 | 0.34 | 16.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate | 0.38603333333333334 | 1.0 | 722.6666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate | 0.3842233333333333 | 1.0 | 705.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_moderate | 0.3822433333333333 | 1.0 | 685.2266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet | 0.3980866666666667 | 1.0 | 1619.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet | 0.3980633333333333 | 1.0 | 1619.28 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r4_high_lat_quiet | 0.3980666666666667 | 1.0 | 1619.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed | 0.29045000000000004 | 0.05 | 3.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed | 0.27832999999999997 | 0.09 | 6.72 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_disturbed | 0.31384 | 0.07 | 4.48 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate | 0.27914666666666665 | 0.9666666666666667 | 635.4933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate | 0.27657333333333334 | 0.9633333333333334 | 635.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_moderate | 0.25663 | 0.9733333333333334 | 593.52 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet | 0.8943966666666667 | 1.0 | 2918.6133333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet | 0.8950933333333334 | 1.0 | 2920.96 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p32_r64_high_lat_quiet | 0.8954533333333334 | 1.0 | 2922.0266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed | 0.25419 | 0.26 | 15.2 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed | 0.25636 | 0.29 | 23.04 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_disturbed | 0.24767 | 0.2 | 18.08 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate | 0.45489666666666667 | 1.0 | 954.8533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate | 0.45584 | 1.0 | 947.4133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_moderate | 0.44841 | 1.0 | 925.5466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet | 0.6859833333333333 | 1.0 | 2372.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet | 0.6860200000000001 | 1.0 | 2373.4133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_bch_p64_r16_high_lat_quiet | 0.6860033333333333 | 1.0 | 2373.4133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.26315 | 0.29 | 18.56 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.25120000000000003 | 0.24 | 26.08 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed | 0.27294 | 0.2 | 17.28 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.4453566666666667 | 1.0 | 991.7866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.4428533333333333 | 1.0 | 980.0 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_moderate | 0.43272333333333335 | 1.0 | 945.92 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.6920266666666667 | 1.0 | 2429.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.6920166666666666 | 1.0 | 2429.36 | Unavailable: audit definitions/standby instrumentation |
| E2_refinement_followup_24000_qpsk_soft_high_lat_quiet | 0.6920166666666666 | 1.0 | 2429.5733333333333 | Unavailable: audit definitions/standby instrumentation |

## Simulated channel group E3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group E4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel — Defects found

Modem cases and power-calibration assertions are reported separately. The latter audit the saved RF measurements; they do not add channel runs. [Power audit](power-audit/SUMMARY.md). [Combined runtime, including the interrupted runner](REPORT.md).

- **xfail** [E_power_fullband_10000](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_fullband_10000/7446529.json) — The diversity branch gain increases measured power by about B/branch_width relative to full-band BPSK.
- **xfail** [E_power_fullband_24000](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_fullband_24000/7446529.json) — The diversity branch gain increases measured power by about B/branch_width relative to full-band BPSK.
- **xfail** [E_power_nominal_10000_bpsk_bch](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_nominal_10000_bpsk_bch/7446529.json) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- **xfail** [E_power_nominal_10000_diversity_commensurate_both](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_nominal_10000_diversity_commensurate_both/7446529.json) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- **xfail** [E_power_nominal_24000_bpsk_bch](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_nominal_24000_bpsk_bch/7446529.json) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- **xfail** [E_power_nominal_24000_diversity_commensurate_both](https://github.com/adamdeprince/goblin-cannon/blob/main/results/refinement/power-audit/E_power_nominal_24000_diversity_commensurate_both/7446529.json) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.

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

See [TESTING.md](../../TESTING.md) and [source audit/questions](../../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 192 / 192 | 24.203 | 1800 | yes |
| full / selected rerun | 414 / 414 | 127.758 | 1800 | yes |
| full / selected rerun | 216 / 216 | 74.508 | 1800 | yes |
| full / selected rerun | 264 / 414 | 1703.360 | 1800 | yes |
| quick / selected rerun | 92 / 92 | 3.155 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
