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
| THRESHOLD_TBD | 99 |
| characterized | 186 |
| pass | 84 |
| unavailable | 3 |
| xfail | 11 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 90 | 0 | 0 | 0 |
| A3 | 18 | 0 | 0 | 0 |
| A4 | 72 | 0 | 48 | 0 |
| A5 | 0 | 0 | 0 | 0 |
| A6 | 0 | 0 | 0 | 0 |
| A7 | 0 | 0 | 0 | 0 |
| A8 | 3 | 3 | 0 | 0 |
| A9 | 3 | 3 | 0 | 0 |
| B1 | 48 | 0 | 0 | 0 |
| B2 | 36 | 0 | 0 | 0 |
| B3 | 18 | 0 | 0 | 0 |
| B4 | 3 | 0 | 0 | 0 |
| B5 | 12 | 0 | 0 | 0 |
| C1 | 0 | 0 | 0 | 0 |
| C2 | 11 | 2 | 8 | 0 |
| C3 | 6 | 0 | 6 | 0 |
| C4 | 32 | 0 | 30 | 1 |
| C5 | 1 | 0 | 0 | 1 |
| D1 | 3 | 0 | 3 | 0 |
| D2 | 6 | 0 | 3 | 0 |
| D3 | 2 | 1 | 1 | 0 |
| D4 | 4 | 0 | 0 | 0 |
| D5 | 1 | 0 | 0 | 1 |
| D6 | 2 | 2 | 0 | 0 |
| E1 | 3 | 0 | 0 | 0 |
| E2 | 9 | 0 | 0 | 0 |
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
| [A2_16qam_0.5ms_-6dB](A2_16qam_0.5ms_-6dB/7446529.json) | characterize / full | characterized | 0.130859 | 0 | 0 | — |
| [A2_16qam_0.5ms_0dB](A2_16qam_0.5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_16qam_1ms_-6dB](A2_16qam_1ms_-6dB/7446529.json) | characterize / full | characterized | 0.136719 | 0 | 0 | — |
| [A2_16qam_1ms_0dB](A2_16qam_1ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_16qam_2ms_-6dB](A2_16qam_2ms_-6dB/7446529.json) | characterize / full | characterized | 0.145833 | 0 | 0 | — |
| [A2_16qam_2ms_0dB](A2_16qam_2ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_16qam_3ms_-6dB](A2_16qam_3ms_-6dB/7446529.json) | characterize / full | characterized | 0.121094 | 0 | 0 | — |
| [A2_16qam_3ms_0dB](A2_16qam_3ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_16qam_5ms_-6dB](A2_16qam_5ms_-6dB/7446529.json) | characterize / full | characterized | 0.101562 | 0 | 0 | — |
| [A2_16qam_5ms_0dB](A2_16qam_5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_16qam_7ms_-6dB](A2_16qam_7ms_-6dB/7446529.json) | characterize / full | characterized | 0.104167 | 0 | 0 | — |
| [A2_16qam_7ms_0dB](A2_16qam_7ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_0.5ms_-6dB](A2_64qam_0.5ms_-6dB/7446529.json) | characterize / full | characterized | 0.166667 | 0 | 0 | — |
| [A2_64qam_0.5ms_0dB](A2_64qam_0.5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_1ms_-6dB](A2_64qam_1ms_-6dB/7446529.json) | characterize / full | characterized | 0.179688 | 0 | 0 | — |
| [A2_64qam_1ms_0dB](A2_64qam_1ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_2ms_-6dB](A2_64qam_2ms_-6dB/7446529.json) | characterize / full | characterized | 0.226562 | 0 | 0 | — |
| [A2_64qam_2ms_0dB](A2_64qam_2ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_3ms_-6dB](A2_64qam_3ms_-6dB/7446529.json) | characterize / full | characterized | 0.214844 | 0 | 0 | — |
| [A2_64qam_3ms_0dB](A2_64qam_3ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_5ms_-6dB](A2_64qam_5ms_-6dB/7446529.json) | characterize / full | characterized | 0.220486 | 0 | 0 | — |
| [A2_64qam_5ms_0dB](A2_64qam_5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_64qam_7ms_-6dB](A2_64qam_7ms_-6dB/7446529.json) | characterize / full | characterized | 0.1875 | 0 | 0 | — |
| [A2_64qam_7ms_0dB](A2_64qam_7ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_disturbed_causal](A2_polar_10000_16qam_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_disturbed_delayed](A2_polar_10000_16qam_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_disturbed_short](A2_polar_10000_16qam_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_moderate_causal](A2_polar_10000_16qam_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_moderate_delayed](A2_polar_10000_16qam_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_moderate_short](A2_polar_10000_16qam_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_16qam_high_lat_quiet_causal](A2_polar_10000_16qam_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 0.000506757 | 0.231946 | 6926.05 | — |
| [A2_polar_10000_16qam_high_lat_quiet_delayed](A2_polar_10000_16qam_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0.00115636 | 0.113849 | 3398.5 | — |
| [A2_polar_10000_16qam_high_lat_quiet_short](A2_polar_10000_16qam_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_disturbed_causal](A2_polar_10000_64qam_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_disturbed_delayed](A2_polar_10000_64qam_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_disturbed_short](A2_polar_10000_64qam_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_moderate_causal](A2_polar_10000_64qam_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_moderate_delayed](A2_polar_10000_64qam_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_moderate_short](A2_polar_10000_64qam_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_64qam_high_lat_quiet_causal](A2_polar_10000_64qam_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 0.00914634 | 0.0127443 | 570.814 | — |
| [A2_polar_10000_64qam_high_lat_quiet_delayed](A2_polar_10000_64qam_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0.00218414 | 0.0118946 | 532.588 | — |
| [A2_polar_10000_64qam_high_lat_quiet_short](A2_polar_10000_64qam_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_disturbed_causal](A2_polar_10000_qpsk_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_disturbed_delayed](A2_polar_10000_qpsk_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_disturbed_short](A2_polar_10000_qpsk_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_moderate_causal](A2_polar_10000_qpsk_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_moderate_delayed](A2_polar_10000_qpsk_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_moderate_short](A2_polar_10000_qpsk_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_10000_qpsk_high_lat_quiet_causal](A2_polar_10000_qpsk_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 0 | 1 | 14923.1 | — |
| [A2_polar_10000_qpsk_high_lat_quiet_delayed](A2_polar_10000_qpsk_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0 | 1 | 14918.3 | — |
| [A2_polar_10000_qpsk_high_lat_quiet_short](A2_polar_10000_qpsk_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_disturbed_causal](A2_polar_24000_16qam_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_disturbed_delayed](A2_polar_24000_16qam_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | 0.421875 | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_disturbed_short](A2_polar_24000_16qam_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_moderate_causal](A2_polar_24000_16qam_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | 0.214844 | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_moderate_delayed](A2_polar_24000_16qam_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | 0.210938 | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_moderate_short](A2_polar_24000_16qam_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_16qam_high_lat_quiet_causal](A2_polar_24000_16qam_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 0.00209316 | 0.046034 | 3315.23 | — |
| [A2_polar_24000_16qam_high_lat_quiet_delayed](A2_polar_24000_16qam_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0.000503178 | 0.103754 | 7469.69 | — |
| [A2_polar_24000_16qam_high_lat_quiet_short](A2_polar_24000_16qam_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_disturbed_causal](A2_polar_24000_64qam_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_disturbed_delayed](A2_polar_24000_64qam_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_disturbed_short](A2_polar_24000_64qam_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_moderate_causal](A2_polar_24000_64qam_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | 0.231771 | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_moderate_delayed](A2_polar_24000_64qam_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | 0.294271 | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_moderate_short](A2_polar_24000_64qam_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_64qam_high_lat_quiet_causal](A2_polar_24000_64qam_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 0.005 | 0.00779037 | 841.558 | — |
| [A2_polar_24000_64qam_high_lat_quiet_delayed](A2_polar_24000_64qam_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0.0026194 | 0.0276204 | 2982.78 | — |
| [A2_polar_24000_64qam_high_lat_quiet_short](A2_polar_24000_64qam_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_disturbed_causal](A2_polar_24000_qpsk_high_lat_disturbed_causal/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_disturbed_delayed](A2_polar_24000_qpsk_high_lat_disturbed_delayed/7446529.json) | characterize / full | characterized | 0.4375 | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_disturbed_short](A2_polar_24000_qpsk_high_lat_disturbed_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_moderate_causal](A2_polar_24000_qpsk_high_lat_moderate_causal/7446529.json) | characterize / full | characterized | 0.145089 | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_moderate_delayed](A2_polar_24000_qpsk_high_lat_moderate_delayed/7446529.json) | characterize / full | characterized | 0.176339 | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_moderate_short](A2_polar_24000_qpsk_high_lat_moderate_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_polar_24000_qpsk_high_lat_quiet_causal](A2_polar_24000_qpsk_high_lat_quiet_causal/7446529.json) | characterize / full | characterized | 8.30087e-06 | 0.999646 | 35989.4 | — |
| [A2_polar_24000_qpsk_high_lat_quiet_delayed](A2_polar_24000_qpsk_high_lat_quiet_delayed/7446529.json) | characterize / full | characterized | 0 | 1 | 35990.9 | — |
| [A2_polar_24000_qpsk_high_lat_quiet_short](A2_polar_24000_qpsk_high_lat_quiet_short/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_0.5ms_-6dB](A2_qpsk_0.5ms_-6dB/7446529.json) | characterize / full | characterized | 0.0298577 | 0.00708215 | 255.296 | — |
| [A2_qpsk_0.5ms_0dB](A2_qpsk_0.5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_1ms_-6dB](A2_qpsk_1ms_-6dB/7446529.json) | characterize / full | characterized | 0.017131 | 0.00849858 | 306.355 | — |
| [A2_qpsk_1ms_0dB](A2_qpsk_1ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_2ms_-6dB](A2_qpsk_2ms_-6dB/7446529.json) | characterize / full | characterized | 0.0512908 | 0.00814448 | 293.59 | — |
| [A2_qpsk_2ms_0dB](A2_qpsk_2ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_3ms_-6dB](A2_qpsk_3ms_-6dB/7446529.json) | characterize / full | characterized | 0.0246875 | 0.0092068 | 331.885 | — |
| [A2_qpsk_3ms_0dB](A2_qpsk_3ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_5ms_-6dB](A2_qpsk_5ms_-6dB/7446529.json) | characterize / full | characterized | 0.0215872 | 0.0092068 | 331.885 | — |
| [A2_qpsk_5ms_0dB](A2_qpsk_5ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_qpsk_7ms_-6dB](A2_qpsk_7ms_-6dB/7446529.json) | characterize / full | characterized | 0.0125762 | 0.0092068 | 331.885 | — |
| [A2_qpsk_7ms_0dB](A2_qpsk_7ms_0dB/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |

## Simulated channel group A3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A3_16qam_0.1Hz](A3_16qam_0.1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_16qam_0.5Hz](A3_16qam_0.5Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_16qam_10Hz](A3_16qam_10Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_16qam_1Hz](A3_16qam_1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_16qam_30Hz](A3_16qam_30Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_16qam_3Hz](A3_16qam_3Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_0.1Hz](A3_64qam_0.1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_0.5Hz](A3_64qam_0.5Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_10Hz](A3_64qam_10Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_1Hz](A3_64qam_1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_30Hz](A3_64qam_30Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_64qam_3Hz](A3_64qam_3Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_0.1Hz](A3_qpsk_0.1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_0.5Hz](A3_qpsk_0.5Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_10Hz](A3_qpsk_10Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_1Hz](A3_qpsk_1Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_30Hz](A3_qpsk_30Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A3_qpsk_3Hz](A3_qpsk_3Hz/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |

## Simulated channel group A4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A4_10000_16qam_-200ppm_10min](A4_10000_16qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_-50ppm_10min](A4_10000_16qam_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_200ppm_10min](A4_10000_16qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_50ppm_10min](A4_10000_16qam_50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_drift_10min](A4_10000_16qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 30114.3 | — |
| [A4_10000_16qam_offset_-1](A4_10000_16qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_-3](A4_10000_16qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_-5](A4_10000_16qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_0](A4_10000_16qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_1](A4_10000_16qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_3](A4_10000_16qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_16qam_offset_5](A4_10000_16qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29920.2 | — |
| [A4_10000_64qam_-200ppm_10min](A4_10000_64qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0480769 | 0 | 0 | — |
| [A4_10000_64qam_-50ppm_10min](A4_10000_64qam_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 45171.5 | — |
| [A4_10000_64qam_200ppm_10min](A4_10000_64qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.102604 | 0 | 0 | — |
| [A4_10000_64qam_50ppm_10min](A4_10000_64qam_50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 45171.5 | — |
| [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 5.16493e-07 | 0.999901 | 45167 | — |
| [A4_10000_64qam_offset_-1](A4_10000_64qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_-3](A4_10000_64qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_-5](A4_10000_64qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 2.21355e-06 | 0.99915 | 44842.1 | — |
| [A4_10000_64qam_offset_0](A4_10000_64qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_1](A4_10000_64qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_3](A4_10000_64qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 44880.3 | — |
| [A4_10000_qpsk_-200ppm_10min](A4_10000_qpsk_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_-50ppm_10min](A4_10000_qpsk_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_200ppm_10min](A4_10000_qpsk_200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_50ppm_10min](A4_10000_qpsk_50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_drift_10min](A4_10000_qpsk_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 15057.2 | — |
| [A4_10000_qpsk_offset_-1](A4_10000_qpsk_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_-3](A4_10000_qpsk_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_-5](A4_10000_qpsk_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_0](A4_10000_qpsk_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_1](A4_10000_qpsk_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_3](A4_10000_qpsk_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_10000_qpsk_offset_5](A4_10000_qpsk_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14960.1 | — |
| [A4_24000_16qam_-200ppm_10min](A4_24000_16qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 72279 | — |
| [A4_24000_16qam_-50ppm_10min](A4_24000_16qam_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 72279 | — |
| [A4_24000_16qam_200ppm_10min](A4_24000_16qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 6.91732e-08 | 0.999994 | 72278.6 | — |
| [A4_24000_16qam_50ppm_10min](A4_24000_16qam_50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 72279 | — |
| [A4_24000_16qam_drift_10min](A4_24000_16qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72279 | — |
| [A4_24000_16qam_offset_-1](A4_24000_16qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_-3](A4_24000_16qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_-5](A4_24000_16qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_0](A4_24000_16qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_1](A4_24000_16qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_3](A4_24000_16qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_16qam_offset_5](A4_24000_16qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 72083.2 | — |
| [A4_24000_64qam_-200ppm_10min](A4_24000_64qam_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0.0403312 | 1.18055e-05 | 1.27994 | — |
| [A4_24000_64qam_-50ppm_10min](A4_24000_64qam_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 108419 | — |
| [A4_24000_64qam_200ppm_10min](A4_24000_64qam_200ppm_10min/7446529.json) | characterize / quick | characterized | 0.105655 | 0 | 0 | — |
| [A4_24000_64qam_50ppm_10min](A4_24000_64qam_50ppm_10min/7446529.json) | assert / quick | pass | 1.07603e-07 | 0.999988 | 108417 | — |
| [A4_24000_64qam_drift_10min](A4_24000_64qam_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108419 | — |
| [A4_24000_64qam_offset_-1](A4_24000_64qam_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-3](A4_24000_64qam_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_-5](A4_24000_64qam_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_0](A4_24000_64qam_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_1](A4_24000_64qam_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_3](A4_24000_64qam_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_64qam_offset_5](A4_24000_64qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 108125 | — |
| [A4_24000_qpsk_-200ppm_10min](A4_24000_qpsk_-200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_-50ppm_10min](A4_24000_qpsk_-50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_200ppm_10min](A4_24000_qpsk_200ppm_10min/7446529.json) | characterize / quick | characterized | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_50ppm_10min](A4_24000_qpsk_50ppm_10min/7446529.json) | assert / quick | pass | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_drift_10min](A4_24000_qpsk_drift_10min/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36139.5 | — |
| [A4_24000_qpsk_offset_-1](A4_24000_qpsk_offset_-1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_-3](A4_24000_qpsk_offset_-3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_-5](A4_24000_qpsk_offset_-5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_0](A4_24000_qpsk_offset_0/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_1](A4_24000_qpsk_offset_1/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_3](A4_24000_qpsk_offset_3/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |
| [A4_24000_qpsk_offset_5](A4_24000_qpsk_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 36041.6 | — |

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
| A4_10000_64qam_drift_10min | 0.0 | 5.164930622807256e-07 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-1 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-3 | 0.0 | 0.0 | True | THRESHOLD_TBD |
| A4_10000_64qam_offset_-5 | 0.0 | 2.213545125330925e-06 | True | THRESHOLD_TBD |
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
| [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json) | assert / full | xfail | — | — | 120 | 36 |
| [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json) | assert / full | xfail | — | — | 120 | 36 |
| [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json) | assert / full | xfail | — | — | 3098.4 | 31 |

## Simulated channel group A9

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A9_dropout_2s](A9_dropout_2s/7446529.json) | assert / full | xfail | — | — | 0 | — |
| [A9_dropout_300s](A9_dropout_300s/7446529.json) | assert / full | xfail | — | — | 0 | — |
| [A9_dropout_30s](A9_dropout_30s/7446529.json) | assert / full | xfail | — | — | 0 | — |

## Simulated channel group B1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B1_10000_16qam_-20dB_10_100](B1_10000_16qam_-20dB_10_100/7446529.json) | assert / quick | pass | 0.000564484 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_-20dB_10_1000](B1_10000_16qam_-20dB_10_1000/7446529.json) | assert / quick | pass | 0.000564484 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_-20dB_1_100](B1_10000_16qam_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000531279 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_-20dB_1_1000](B1_10000_16qam_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000531279 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_10_100](B1_10000_16qam_20dB_10_100/7446529.json) | assert / quick | pass | 0.000166025 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_10_1000](B1_10000_16qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0.000166025 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_1_100](B1_10000_16qam_20dB_1_100/7446529.json) | assert / quick | pass | 0.000166025 | 0.995763 | 29030.3 | — |
| [B1_10000_16qam_20dB_1_1000](B1_10000_16qam_20dB_1_1000/7446529.json) | assert / quick | pass | 0.000166025 | 0.995763 | 29030.3 | — |
| [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446529.json) | assert / quick | pass | 0.00126179 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_-20dB_10_1000](B1_10000_64qam_-20dB_10_1000/7446529.json) | assert / quick | pass | 0.00126179 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000708372 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_-20dB_1_1000](B1_10000_64qam_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000708372 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_20dB_10_100](B1_10000_64qam_20dB_10_100/7446529.json) | assert / quick | pass | 0.000807987 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_20dB_10_1000](B1_10000_64qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0.000807987 | 0.991525 | 43359.6 | — |
| [B1_10000_64qam_20dB_1_100](B1_10000_64qam_20dB_1_100/7446529.json) | assert / quick | pass | 0.000365254 | 0.995763 | 43545.5 | — |
| [B1_10000_64qam_20dB_1_1000](B1_10000_64qam_20dB_1_1000/7446529.json) | assert / quick | pass | 0.000365254 | 0.995763 | 43545.5 | — |
| [B1_10000_qpsk_-20dB_10_100](B1_10000_qpsk_-20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_-20dB_10_1000](B1_10000_qpsk_-20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_-20dB_1_100](B1_10000_qpsk_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000630894 | 0.995763 | 14515.2 | — |
| [B1_10000_qpsk_-20dB_1_1000](B1_10000_qpsk_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000630894 | 0.995763 | 14515.2 | — |
| [B1_10000_qpsk_20dB_10_100](B1_10000_qpsk_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_10_1000](B1_10000_qpsk_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_1_100](B1_10000_qpsk_20dB_1_100/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_10000_qpsk_20dB_1_1000](B1_10000_qpsk_20dB_1_1000/7446529.json) | assert / quick | pass | 0 | 1 | 14577.1 | — |
| [B1_24000_16qam_-20dB_10_100](B1_24000_16qam_-20dB_10_100/7446529.json) | assert / quick | pass | 0.000325116 | 0.99292 | 70793.6 | — |
| [B1_24000_16qam_-20dB_10_1000](B1_24000_16qam_-20dB_10_1000/7446529.json) | assert / quick | pass | 0.000325116 | 0.99292 | 70793.6 | — |
| [B1_24000_16qam_-20dB_1_100](B1_24000_16qam_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000255942 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_-20dB_1_1000](B1_24000_16qam_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000255942 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_10_100](B1_24000_16qam_20dB_10_100/7446529.json) | assert / quick | pass | 2.07521e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_10_1000](B1_24000_16qam_20dB_10_1000/7446529.json) | assert / quick | pass | 2.07521e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_1_100](B1_24000_16qam_20dB_1_100/7446529.json) | assert / quick | pass | 4.15041e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_16qam_20dB_1_1000](B1_24000_16qam_20dB_1_1000/7446529.json) | assert / quick | pass | 4.15041e-05 | 0.99823 | 71172.4 | — |
| [B1_24000_64qam_-20dB_10_100](B1_24000_64qam_-20dB_10_100/7446529.json) | assert / quick | pass | 0.000594892 | 0.99292 | 106190 | — |
| [B1_24000_64qam_-20dB_10_1000](B1_24000_64qam_-20dB_10_1000/7446529.json) | assert / quick | pass | 0.000594892 | 0.99292 | 106190 | — |
| [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000253636 | 0.99823 | 106759 | — |
| [B1_24000_64qam_-20dB_1_1000](B1_24000_64qam_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000253636 | 0.99823 | 106759 | — |
| [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446529.json) | assert / quick | pass | 0.000378149 | 0.99292 | 106190 | — |
| [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0.000378149 | 0.99292 | 106190 | — |
| [B1_24000_64qam_20dB_1_100](B1_24000_64qam_20dB_1_100/7446529.json) | assert / quick | pass | 0.000193686 | 0.99823 | 106759 | — |
| [B1_24000_64qam_20dB_1_1000](B1_24000_64qam_20dB_1_1000/7446529.json) | assert / quick | pass | 0.000193686 | 0.99823 | 106759 | — |
| [B1_24000_qpsk_-20dB_10_100](B1_24000_qpsk_-20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_-20dB_10_1000](B1_24000_qpsk_-20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_-20dB_1_100](B1_24000_qpsk_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000179851 | 0.99823 | 35586.2 | — |
| [B1_24000_qpsk_-20dB_1_1000](B1_24000_qpsk_-20dB_1_1000/7446529.json) | assert / quick | pass | 0.000179851 | 0.99823 | 35586.2 | — |
| [B1_24000_qpsk_20dB_10_100](B1_24000_qpsk_20dB_10_100/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_10_1000](B1_24000_qpsk_20dB_10_1000/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_1_100](B1_24000_qpsk_20dB_1_100/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |
| [B1_24000_qpsk_20dB_1_1000](B1_24000_qpsk_20dB_1_1000/7446529.json) | assert / quick | pass | 0 | 1 | 35649.3 | — |

### Simulated channel B1 affected-frame errors

Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.

| Case | Affected frames | Affected frame error rate |
| --- | --- | --- |
| B1_10000_16qam_-20dB_10_100 | 21 | 0.047619047619047616 |
| B1_10000_16qam_-20dB_10_1000 | 127 | 0.007874015748031496 |
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
| B1_24000_16qam_-20dB_10_100 | 48 | 0.08333333333333333 |
| B1_24000_16qam_-20dB_10_1000 | 302 | 0.013245033112582781 |
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
| [B2_10000_16qam_hard_10pct](B2_10000_16qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_16qam_hard_1pct](B2_10000_16qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_16qam_hard_5pct](B2_10000_16qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_16qam_soft_10pct](B2_10000_16qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_16qam_soft_1pct](B2_10000_16qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_16qam_soft_5pct](B2_10000_16qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 29154.2 | — |
| [B2_10000_64qam_hard_10pct](B2_10000_64qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0.000343118 | 0.919492 | 40199.8 | — |
| [B2_10000_64qam_hard_1pct](B2_10000_64qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 43731.3 | — |
| [B2_10000_64qam_hard_5pct](B2_10000_64qam_hard_5pct/7446529.json) | characterize / quick | characterized | 3.32049e-05 | 0.987288 | 43173.7 | — |
| [B2_10000_64qam_soft_10pct](B2_10000_64qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0.000431664 | 0.894068 | 39084.6 | — |
| [B2_10000_64qam_soft_1pct](B2_10000_64qam_soft_1pct/7446529.json) | characterize / quick | characterized | 2.21366e-05 | 0.995763 | 43545.5 | — |
| [B2_10000_64qam_soft_5pct](B2_10000_64qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0.000177093 | 0.949153 | 41500.9 | — |
| [B2_10000_qpsk_hard_10pct](B2_10000_qpsk_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_10000_qpsk_hard_1pct](B2_10000_qpsk_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_10000_qpsk_hard_5pct](B2_10000_qpsk_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_10000_qpsk_soft_10pct](B2_10000_qpsk_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_10000_qpsk_soft_1pct](B2_10000_qpsk_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_10000_qpsk_soft_5pct](B2_10000_qpsk_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 14577.1 | — |
| [B2_24000_16qam_hard_10pct](B2_24000_16qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_16qam_hard_1pct](B2_24000_16qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_16qam_hard_5pct](B2_24000_16qam_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_16qam_soft_10pct](B2_24000_16qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_16qam_soft_1pct](B2_24000_16qam_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_16qam_soft_5pct](B2_24000_16qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 71298.7 | — |
| [B2_24000_64qam_hard_10pct](B2_24000_64qam_hard_10pct/7446529.json) | characterize / quick | characterized | 0.000355091 | 0.916814 | 98046.8 | — |
| [B2_24000_64qam_hard_1pct](B2_24000_64qam_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 106948 | — |
| [B2_24000_64qam_hard_5pct](B2_24000_64qam_hard_5pct/7446529.json) | characterize / quick | characterized | 7.37851e-05 | 0.975221 | 104297 | — |
| [B2_24000_64qam_soft_10pct](B2_24000_64qam_soft_10pct/7446529.json) | characterize / quick | characterized | 0.000488826 | 0.865487 | 92554.5 | — |
| [B2_24000_64qam_soft_1pct](B2_24000_64qam_soft_1pct/7446529.json) | characterize / quick | characterized | 9.22314e-06 | 0.99646 | 106569 | — |
| [B2_24000_64qam_soft_5pct](B2_24000_64qam_soft_5pct/7446529.json) | characterize / quick | characterized | 0.000184463 | 0.941593 | 100698 | — |
| [B2_24000_qpsk_hard_10pct](B2_24000_qpsk_hard_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |
| [B2_24000_qpsk_hard_1pct](B2_24000_qpsk_hard_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |
| [B2_24000_qpsk_hard_5pct](B2_24000_qpsk_hard_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |
| [B2_24000_qpsk_soft_10pct](B2_24000_qpsk_soft_10pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |
| [B2_24000_qpsk_soft_1pct](B2_24000_qpsk_soft_1pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |
| [B2_24000_qpsk_soft_5pct](B2_24000_qpsk_soft_5pct/7446529.json) | characterize / quick | characterized | 0 | 1 | 35649.3 | — |

## Simulated channel group B3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B3_10000_16qam_0.5ms](B3_10000_16qam_0.5ms/7446529.json) | characterize / quick | characterized | 0.000199375 | 0.991525 | 28995.5 | — |
| [B3_10000_16qam_1ms](B3_10000_16qam_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 29119.4 | — |
| [B3_10000_16qam_2ms](B3_10000_16qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 29119.4 | — |
| [B3_10000_64qam_0.5ms](B3_10000_64qam_0.5ms/7446529.json) | characterize / quick | characterized | 0.00537634 | 0.0466102 | 2044.55 | — |
| [B3_10000_64qam_1ms](B3_10000_64qam_1ms/7446529.json) | characterize / quick | characterized | 0.0188301 | 0.0423729 | 1858.68 | — |
| [B3_10000_64qam_2ms](B3_10000_64qam_2ms/7446529.json) | characterize / quick | characterized | 7.75348e-05 | 0.983051 | 43121.4 | — |
| [B3_10000_qpsk_0.5ms](B3_10000_qpsk_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14559.7 | — |
| [B3_10000_qpsk_1ms](B3_10000_qpsk_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14559.7 | — |
| [B3_10000_qpsk_2ms](B3_10000_qpsk_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.995763 | 14559.7 | — |
| [B3_24000_16qam_0.5ms](B3_24000_16qam_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71209.9 | — |
| [B3_24000_16qam_1ms](B3_24000_16qam_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71209.9 | — |
| [B3_24000_16qam_2ms](B3_24000_16qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 71209.9 | — |
| [B3_24000_64qam_0.5ms](B3_24000_64qam_0.5ms/7446529.json) | characterize / quick | characterized | 0.00562169 | 0.040708 | 4355.92 | — |
| [B3_24000_64qam_1ms](B3_24000_64qam_1ms/7446529.json) | characterize / quick | characterized | 1.8458e-05 | 0.99469 | 106436 | — |
| [B3_24000_64qam_2ms](B3_24000_64qam_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 106815 | — |
| [B3_24000_qpsk_0.5ms](B3_24000_qpsk_0.5ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35604.9 | — |
| [B3_24000_qpsk_1ms](B3_24000_qpsk_1ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35604.9 | — |
| [B3_24000_qpsk_2ms](B3_24000_qpsk_2ms/7446529.json) | characterize / quick | characterized | 0 | 0.99823 | 35604.9 | — |

## Simulated channel group B4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B4_jitter](B4_jitter/7446529.json) | assert / quick | pass | — | — | 396 | 173 |
| [B4_overrun](B4_overrun/7446529.json) | assert / quick | pass | — | — | 396 | 173 |
| [B4_underrun](B4_underrun/7446529.json) | assert / quick | pass | — | — | 396 | 173 |

## Simulated channel group B5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json) | assert / quick | pass | — | — | 3100.67 | 12 |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 3094.67 | 13 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json) | assert / quick | pass | — | — | 3103.33 | 8 |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 3097.33 | 9 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 2256.67 | 31 |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 2252.67 | 32 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | pass | — | — | 3111.33 | 5 |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 3107.33 | 6 |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json) | assert / quick | pass | — | — | 3111.33 | 4 |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 3107.33 | 5 |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json) | assert / quick | pass | — | — | 3111.33 | 11 |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 3107.33 | 10 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 11.000586000001533 | 12.029504000000024 | 11.666666666666659 | 0.862837333333033 | 0.8656493333333302 | pass |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.host.json) | 12.99816799999931 | 13.009709999999952 | 12.31250000000017 | 0.9618913333326873 | 0.9680433333334459 | pass |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 8.000415999999788 | 8.061050000000014 | 7.8125 | 0.9652523333333338 | 0.9655823333333817 | pass |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.host.json) | 9.000118999999529 | 9.04077499999989 | 8.937500000000043 | 0.9552053333333745 | 0.9605663333331904 | pass |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 26.000083000000007 | 31.00366500000007 | 30.312500000000853 | 0.9657689999997814 | 0.9657689999997814 | pass |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.host.json) | 26.9990739999999 | 32.09798700000022 | 31.437500000000895 | 0.9104870000000709 | 0.9104870000000709 | pass |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 5.000477000000281 | 5.03032400000003 | 4.666666666667041 | 0.755445999999993 | 0.7555960000000246 | pass |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.host.json) | 6.000780000000816 | 6.053870999999766 | 5.770833333334835 | 0.7127326666666596 | 0.7129926666665787 | pass |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | 4.000313000000588 | 4.040578999999989 | 3.270833333333556 | 0.9711459999999228 | 0.986870333333556 | pass |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.host.json) | 5.000647000000136 | 5.110966000000161 | 4.354166666667325 | 1.0194443333333414 | 1.0269383333332271 | pass |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | 9.000339999998275 | 11.000095000000002 | 10.541666666666664 | 0.9593943333333357 | 0.9594043333333584 | pass |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.host.json) | 10.000041999999931 | 10.04329300000073 | 9.979166666667538 | 0.8570436666666676 | 0.8963586666665968 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_10000_16qam_null | host_source_to_framer_ms | 0.0012319999997956188 | 0.9983400000000003 | 5.397858999999998 |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.00018000000068241206 | 0.001401999999983694 | 0.004729000000000191 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.0020039999999998948 | 0.00506000000122242 | 0.00922700000000054 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.001151999999393638 | 0.0015929999994668265 |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.9664699999998305 | 0.9982300000000027 | 1.2531519999985363 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.030076999999906207 | 0.04063700000012105 | 0.39511799999999986 |
| B5_10000_16qam_polar_span_null | host_source_to_framer_ms | 0.0014229999996118181 | 0.00441799999961745 | 0.013705999999988339 |
| B5_10000_16qam_polar_span_null | host_intake_per_message_ms | 0.00018000000068241206 | 0.0008219999996228466 | 0.003335999999999617 |
| B5_10000_16qam_polar_span_null | host_tx_per_block_ms | 0.0019940000000051583 | 0.003516000000036712 | 0.00683300000048348 |
| B5_10000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006909999985538207 | 0.0008619999999999114 | 0.0010019999999721918 |
| B5_10000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.9437160000000944 | 0.998139000000009 | 1.031192 |
| B5_10000_16qam_polar_span_null | host_rx_per_block_ms | 0.0525299999996065 | 0.05614599999997916 | 2.2701270000000107 |
| B5_10000_64qam_null | host_source_to_framer_ms | 0.0010520000000013852 | 0.003986999999927576 | 5.393962000000002 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.00018000000023832285 | 0.001002000000083214 | 0.0032869999999993876 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.0022550000000620685 | 0.004869000000073953 | 0.00966800000000434 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0009209999998205376 | 0.0018529999998850855 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.9577339999999879 | 0.9981090000000005 | 1.0630530000002025 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.03823200000052651 | 0.05212899999995635 | 0.3914610000000096 |
| B5_10000_64qam_polar_span_null | host_source_to_framer_ms | 0.0011319999995151875 | 0.01351600000000508 | 0.013735999999653359 |
| B5_10000_64qam_polar_span_null | host_intake_per_message_ms | 0.00016999999985500835 | 0.008817000000327369 | 0.008886999999901946 |
| B5_10000_64qam_polar_span_null | host_tx_per_block_ms | 0.0022950000000410142 | 0.011420999999955939 | 0.03615800000034142 |
| B5_10000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0009119999999640527 | 0.00739400000071555 |
| B5_10000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.927015000000253 | 0.9982489999999927 | 1.031814 |
| B5_10000_64qam_polar_span_null | host_rx_per_block_ms | 0.06935199999968944 | 0.10382700000022282 | 2.1882029999999997 |
| B5_10000_qpsk_null | host_source_to_framer_ms | 4.003759999999801 | 9.0167000000001 | 9.0167000000001 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.00017099999993774873 | 0.0012329999998783592 | 0.003556999999999519 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.001794000000998608 | 0.0035159999995926228 | 0.00902699999999479 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0008819999999243322 | 0.001222999999994645 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.9759580000006096 | 0.998190000000003 | 1.01919 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.020899999999102192 | 0.028262999999917326 | 0.39699200000001267 |
| B5_10000_qpsk_polar_span_null | host_source_to_framer_ms | 4.982031999999998 | 9.027760999999995 | 9.027760999999995 |
| B5_10000_qpsk_polar_span_null | host_intake_per_message_ms | 0.0001999999987845058 | 0.0025150000000362382 | 0.0033559999999994983 |
| B5_10000_qpsk_polar_span_null | host_tx_per_block_ms | 0.0018239999999281054 | 0.004618999999983497 | 0.030146999999924873 |
| B5_10000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006909999994419991 | 0.0010019999994170803 | 0.0015030000000137989 |
| B5_10000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.9376950000010709 | 0.9981799999999995 | 1.0184879999999998 |
| B5_10000_qpsk_polar_span_null | host_rx_per_block_ms | 0.05910199999981103 | 0.11980700000013833 | 2.31858900000001 |
| B5_24000_16qam_null | host_source_to_framer_ms | 0.002584999999943882 | 0.008014999999916839 | 7.6415370000000005 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.00017999999979423364 | 0.0011820000000023478 | 0.003305999999999795 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.015338999999947589 | 0.019948000000269417 | 0.024787000000081605 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0009920000003660334 | 0.0014129999998946374 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.9239599999997239 | 0.9975679999999999 | 1.0759770000001723 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.059373000000917386 | 0.07345899999999794 | 0.6365249999999989 |
| B5_24000_16qam_polar_span_null | host_source_to_framer_ms | 0.002175000000104177 | 0.005541000000164331 | 0.005770999999654691 |
| B5_24000_16qam_polar_span_null | host_intake_per_message_ms | 0.0002009999997554246 | 0.0006909999999971106 | 0.0032169999999998034 |
| B5_24000_16qam_polar_span_null | host_tx_per_block_ms | 0.015289000000251463 | 0.016530999999986307 | 0.02170099999987407 |
| B5_24000_16qam_polar_span_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0009120000008522311 | 0.0013320000000760501 |
| B5_24000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.8691650000001161 | 0.9977990000000005 | 1.0247799999999998 |
| B5_24000_16qam_polar_span_null | host_rx_per_block_ms | 0.1137359999994203 | 0.12696100000120225 | 2.7992489999999965 |
| B5_24000_64qam_null | host_source_to_framer_ms | 0.0020439999985910617 | 0.004657999999935214 | 7.6926939999999995 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.0002009999997554246 | 0.0009920000001439888 | 0.0038169999999997095 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.015929999999997335 | 0.019145999999636842 | 0.026620999999948936 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.0006909999998860883 | 0.0008719999993189731 | 0.0011730000002430074 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.9022990000002729 | 0.9977090000000003 | 1.038726 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.08049200000037615 | 0.09458899999970072 | 0.686840000000001 |
| B5_24000_64qam_polar_span_null | host_source_to_framer_ms | 0.0016729999998688072 | 0.006702999999941284 | 0.0068130000006050295 |
| B5_24000_64qam_polar_span_null | host_intake_per_message_ms | 0.00018999999995550354 | 0.0008510000002459606 | 0.0039379999999984705 |
| B5_24000_64qam_polar_span_null | host_tx_per_block_ms | 0.01615100000051939 | 0.02221200000018797 | 0.026751000000047043 |
| B5_24000_64qam_polar_span_null | host_channel_per_block_ms | 0.0006710000000076377 | 0.0008920000000856021 | 0.0018830000000358282 |
| B5_24000_64qam_polar_span_null | host_audio_wait_per_block_ms | 0.8525339999998494 | 0.997889 | 1.1035590000001427 |
| B5_24000_64qam_polar_span_null | host_rx_per_block_ms | 0.12985600000003927 | 0.15597500000019693 | 2.7788509999999986 |
| B5_24000_qpsk_null | host_source_to_framer_ms | 0.004088000000013192 | 2.0122389999999992 | 7.6679270000000015 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.00015999999991578306 | 0.0011520000000007913 | 0.0037170000000003034 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.015109000001345407 | 0.01686199999983984 | 0.02422599999999872 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.0006909999985538207 | 0.0008120000014599782 | 0.0011620000002210418 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.9443780000015778 | 0.997669 | 1.021514 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.038894000000233575 | 0.04363299999887715 | 0.6626849999999996 |
| B5_24000_qpsk_polar_span_null | host_source_to_framer_ms | 0.004898999999891629 | 0.00806599999991775 | 0.008366000001203133 |
| B5_24000_qpsk_polar_span_null | host_intake_per_message_ms | 0.00015100000005929815 | 0.0012019999999987596 | 0.003186000000000508 |
| B5_24000_qpsk_polar_span_null | host_tx_per_block_ms | 0.014828000000299824 | 0.01659099999962166 | 0.025418000000110297 |
| B5_24000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0008919999991974237 | 0.0013429999992098374 |
| B5_24000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.8889830000000098 | 0.997768999999999 | 1.0224259999999998 |
| B5_24000_qpsk_polar_span_null | host_rx_per_block_ms | 0.0945890000005889 | 0.10306499999934715 | 2.7573899999999982 |

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
| [C2_10000_acquire_0dB](C2_10000_acquire_0dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.1 | — |
| [C2_10000_acquire_10dB](C2_10000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.1 | — |
| [C2_10000_acquire_3dB](C2_10000_acquire_3dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.1 | — |
| [C2_10000_acquire_6dB](C2_10000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.1 | — |
| [C2_10000_cw_preamble](C2_10000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14577.1 | — |
| [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json) | assert / quick | xfail | — | 0 | 0 | — |
| [C2_24000_acquire_10dB](C2_24000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.3 | — |
| [C2_24000_acquire_3dB](C2_24000_acquire_3dB/7446529.json) | assert / quick | xfail | — | 0 | 0 | — |
| [C2_24000_acquire_6dB](C2_24000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 2.76694e-05 | 0.99823 | 35586.2 | — |
| [C2_24000_cw_preamble](C2_24000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.3 | — |
| [C2_noise_10min](C2_noise_10min/7446529.json) | assert / quick | pass | — | — | 0 | — |

## Simulated channel group C3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C3_10000_sample_-1](C3_10000_sample_-1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 1876 | 515 |
| [C3_10000_sample_1](C3_10000_sample_1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 1876 | 515 |
| [C3_24000_sample_-1](C3_24000_sample_-1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 612 | 36 |
| [C3_24000_sample_1](C3_24000_sample_1/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | 612 | 36 |
| [C3_bit_delete](C3_bit_delete/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | — | — |
| [C3_bit_insert](C3_bit_insert/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | — | — |

## Simulated channel group C4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C4_10000_16qam_alternating](C4_10000_16qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29153.9 | — |
| [C4_10000_16qam_ones](C4_10000_16qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29153.9 | — |
| [C4_10000_16qam_random](C4_10000_16qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29153.9 | — |
| [C4_10000_16qam_repeating](C4_10000_16qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29153.9 | — |
| [C4_10000_16qam_zeros](C4_10000_16qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 29153.9 | — |
| [C4_10000_64qam_alternating](C4_10000_64qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43730.8 | — |
| [C4_10000_64qam_ones](C4_10000_64qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43730.8 | — |
| [C4_10000_64qam_random](C4_10000_64qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43730.8 | — |
| [C4_10000_64qam_repeating](C4_10000_64qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43730.8 | — |
| [C4_10000_64qam_zeros](C4_10000_64qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 43730.8 | — |
| [C4_10000_qpsk_alternating](C4_10000_qpsk_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14576.9 | — |
| [C4_10000_qpsk_ones](C4_10000_qpsk_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14576.9 | — |
| [C4_10000_qpsk_random](C4_10000_qpsk_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14576.9 | — |
| [C4_10000_qpsk_repeating](C4_10000_qpsk_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14576.9 | — |
| [C4_10000_qpsk_zeros](C4_10000_qpsk_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 14576.9 | — |
| [C4_24000_16qam_alternating](C4_24000_16qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71298.9 | — |
| [C4_24000_16qam_ones](C4_24000_16qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71298.9 | — |
| [C4_24000_16qam_random](C4_24000_16qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71298.9 | — |
| [C4_24000_16qam_repeating](C4_24000_16qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71298.9 | — |
| [C4_24000_16qam_zeros](C4_24000_16qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 71298.9 | — |
| [C4_24000_64qam_alternating](C4_24000_64qam_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106948 | — |
| [C4_24000_64qam_ones](C4_24000_64qam_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106948 | — |
| [C4_24000_64qam_random](C4_24000_64qam_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106948 | — |
| [C4_24000_64qam_repeating](C4_24000_64qam_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106948 | — |
| [C4_24000_64qam_zeros](C4_24000_64qam_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 106948 | — |
| [C4_24000_qpsk_alternating](C4_24000_qpsk_alternating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.2 | — |
| [C4_24000_qpsk_ones](C4_24000_qpsk_ones/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.2 | — |
| [C4_24000_qpsk_random](C4_24000_qpsk_random/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.2 | — |
| [C4_24000_qpsk_repeating](C4_24000_qpsk_repeating/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.2 | — |
| [C4_24000_qpsk_zeros](C4_24000_qpsk_zeros/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 35649.2 | — |
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
| [D1_overload_1.5](D1_overload_1.5/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | 10 |
| [D1_overload_10](D1_overload_10/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | 10 |
| [D1_overload_3](D1_overload_3/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | 10 |

### Simulated channel D1 source-to-sink overload

Offered wire bits are 1.5×, 3×, or 10× nominal steady payload capacity, including sequence metadata, CRC, FEC and pilot overhead. Startup is included in measured delivery latency.

| Case | Created / delivered | Queue maximum | Superseded at framer | Delivered stale | p99.9 ms | First / last window p99.9 ms |
| --- | --- | --- | --- | --- | --- | --- |
| D1_overload_1.5 | 6526 / 4344 | 1 | 0 | 0 | 27.125000000004285 | 27.125000000009393 / 27.12499999915252 |
| D1_overload_10 | 42649 / 4259 | 1 | 0 | 4 | 24.256249972431476 | 26.35000000000018 / 24.256249952493647 |
| D1_overload_3 | 13042 / 4341 | 1 | 0 | 0 | 26.583333333330074 | 26.5833333333374 / 26.583333332467873 |

## Simulated channel group D2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D2_freshness_agreement_0.3](D2_freshness_agreement_0.3/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | — |
| [D2_freshness_agreement_0.5](D2_freshness_agreement_0.5/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | — |
| [D2_freshness_agreement_0.8](D2_freshness_agreement_0.8/7446529.json) | assert / full | THRESHOLD_TBD | — | — | — | — |
| [D2_survival_0.3](D2_survival_0.3/7446529.json) | characterize / full | characterized | — | — | — | — |
| [D2_survival_0.5](D2_survival_0.5/7446529.json) | characterize / full | characterized | — | — | — | — |
| [D2_survival_0.8](D2_survival_0.8/7446529.json) | characterize / full | characterized | — | — | — | — |

### Simulated channel D2 freshness comparison

| Target frame survival | Measured channel survival | Channel freshness p99.9 ms | Erasure freshness p99.9 ms |
| --- | --- | --- | --- |
| 0.3 | 0.21320300325825187 | 3413.0000000000005 | 14168.499999999998 |
| 0.5 | 0.6825329366765831 | 3413.0000000000005 | 14168.499999999998 |
| 0.8 | 0.7254568635784105 | 14165 | 14168.999999999998 |

## Simulated channel group D3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D3_auction_contention](D3_auction_contention/7446529.json) | assert / quick | THRESHOLD_TBD | — | — | — | 10 |
| [D3_auction_flood](D3_auction_flood/7446529.json) | assert / quick | xfail | — | — | — | 1.00001 |

## Simulated channel group D4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D4_duplicate](D4_duplicate/7446529.json) | assert / quick | pass | — | — | — | — |
| [D4_fec_failure](D4_fec_failure/7446529.json) | assert / quick | pass | — | — | — | — |
| [D4_out_of_order](D4_out_of_order/7446529.json) | assert / quick | pass | — | — | — | — |
| [D4_wrap](D4_wrap/7446529.json) | assert / quick | pass | — | — | — | — |

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
| [E2_ccir_good](E2_ccir_good/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_ccir_poor](E2_ccir_poor/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_high_lat_disturbed](E2_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_high_lat_moderate](E2_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_high_lat_quiet](E2_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_low_lat_disturbed](E2_low_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_mid_lat_disturbed](E2_mid_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_mid_lat_moderate](E2_mid_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_mid_lat_quiet](E2_mid_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 0 | — |

### Simulated channel E2 local metric definitions

| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |
| --- | --- | --- | --- | --- |
| E2_ccir_good | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_ccir_poor | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_high_lat_moderate | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_high_lat_quiet | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_low_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_mid_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_mid_lat_moderate | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_mid_lat_quiet | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |

## Simulated channel group E3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group E4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel — Defects found

- **xfail** — Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
  Cases: [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json), [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json), [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json), [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json).
- **xfail** — With a co-channel interferer at -10 dB SIR, the message sink receives payloads outside the expected source stream; authenticated delivery is not implemented.
  Cases: [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json).
- **xfail** — The high_lat_moderate trace does not validate a header; dropout recovery and stale-message rejection cannot be established.
  Cases: [A9_dropout_2s](A9_dropout_2s/7446529.json), [A9_dropout_300s](A9_dropout_300s/7446529.json), [A9_dropout_30s](A9_dropout_30s/7446529.json).
- **xfail** — At the requested low SNR, the receiver detects the preamble but loses lock without validating a header.
  Cases: [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json), [C2_24000_acquire_3dB](C2_24000_acquire_3dB/7446529.json).
- **xfail** — Policy conflict: strict bid priority permits starvation during an endless higher-bid flood; Adam rejected increasing priority with age. No cross-key expiry/decay interval is approved.
  Cases: [D3_auction_flood](D3_auction_flood/7446529.json).
- **xfail** — Restarting the production AES-CTR generator with the unchanged key and default counter repeats its keystream.
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
| quick / selected rerun | 120 / 120 | 132.085 | 120 | **NO** |
| full / selected rerun | 44 / 134 | 90.533 | 1800 | yes |
| full / selected rerun | 90 / 90 | 9.744 | 1800 | yes |
| quick / selected rerun | 117 / 237 | 9.977 | 120 | yes |
| quick / selected rerun | 6 / 6 | 76.976 | 120 | yes |
| full / selected rerun | 6 / 6 | 78.686 | 1800 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
