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
| characterized | 1806 |
| pass | 84 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 378 | 0 | 0 | 0 |
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
| C1 | 672 | 0 | 0 | 0 |
| C2 | 0 | 0 | 0 | 0 |
| C3 | 0 | 0 | 0 | 0 |
| C4 | 42 | 0 | 0 | 0 |
| C5 | 0 | 0 | 0 | 0 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 0 | 0 | 0 | 0 |
| D4 | 42 | 0 | 0 | 0 |
| D5 | 0 | 0 | 0 | 0 |
| D6 | 0 | 0 | 0 | 0 |
| E1 | 0 | 0 | 0 | 0 |
| E2 | 756 | 0 | 0 | 0 |
| E3 | 0 | 0 | 0 | 0 |
| E4 | 0 | 0 | 0 | 0 |

## Simulated channel group A1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (8640 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group A2

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [A2_encoding_screen_10000_16qam_reference_high_lat_disturbed](A2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_disturbed](A2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_disturbed](A2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.460938 | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_moderate](A2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.271552 | 0.00131752 | 25.4928 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_moderate](A2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.221387 | 0.00658762 | 127.464 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_moderate](A2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.130912 | 0.0382082 | 739.292 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_quiet](A2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 8.62329e-05 | 0.912548 | 18347.3 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_quiet](A2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000290023 | 0.930292 | 18704 | — |
| [A2_encoding_screen_10000_16qam_reference_high_lat_quiet](A2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000507323 | 0.888466 | 17859.9 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_disturbed](A2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.507812 | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_disturbed](A2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.324219 | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_disturbed](A2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.460938 | 0 | 0 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_moderate](A2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.271552 | 0.00131752 | 25.4928 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_moderate](A2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.226753 | 0.00658762 | 127.464 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_moderate](A2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.140676 | 0.0382082 | 739.292 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_quiet](A2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 8.62329e-05 | 0.912548 | 18347.3 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_quiet](A2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.000290023 | 0.930292 | 18704 | — |
| [A2_encoding_screen_10000_16qam_soft_high_lat_quiet](A2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000507323 | 0.888466 | 17859.9 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.498047 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.493924 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.425625 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_moderate](A2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.102069 | 0.183136 | 886.184 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_moderate](A2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0978442 | 0.198946 | 959.701 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_moderate](A2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.131211 | 0.246377 | 1192.21 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_quiet](A2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_quiet](A2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4614.03 | — |
| [A2_encoding_screen_10000_bpsk_bch_high_lat_quiet](A2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4616.82 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.485352 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.483567 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0870058 | 0.303907 | 1333.82 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.110365 | 0.157742 | 690.73 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.091094 | 0.256151 | 1124.22 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.888268 | 4058.23 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.955307 | 4364.75 | — |
| [A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.865922 | 3956.06 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.265625 | 0.00255754 | 6.35072 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.27214 | 0.0383632 | 95.2607 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.351283 | 0.0179028 | 44.455 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.962406 | 2455.36 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.882206 | 2250.75 | — |
| [A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.9599 | 2444.17 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.129167 | 0.0230179 | 57.1564 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.123077 | 0.0332481 | 82.5593 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.165761 | 0.0204604 | 50.8057 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.842105 | 2148.44 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.882206 | 2250.75 | — |
| [A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.839599 | 2137.25 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.482537 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.434896 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.271739 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0705758 | 0.206522 | 995.474 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.115068 | 0.190217 | 916.884 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.106668 | 0.241848 | 1165.75 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.916667 | 4596.68 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.916667 | 4596.68 | — |
| [A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.916667 | 4596.68 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.494141 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.477431 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.465074 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.139328 | 0.194444 | 939.199 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.125 | 0.191799 | 926.421 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.140288 | 0.253968 | 1226.71 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917513 | 4609.38 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917513 | 4609.38 | — |
| [A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918782 | 4615.75 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.490234 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.484776 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.333333 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0643572 | 0.181818 | 879.831 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.117172 | 0.205534 | 991.404 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.119442 | 0.251647 | 1217.74 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4613.8 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4613.8 | — |
| [A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4616.99 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.422222 | 0.00283286 | 12.6964 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.485243 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.472862 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.126592 | 0.202899 | 981.62 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.118696 | 0.221344 | 1069.27 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0893016 | 0.249012 | 1204.72 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.66 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.414773 | 0.00424929 | 19.0427 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.46875 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.378472 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.147416 | 0.183136 | 886.096 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.1221 | 0.162055 | 781.709 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0737645 | 0.27141 | 1313.21 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4613.34 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4613.34 | — |
| [A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.32 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.5625 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.493566 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.35625 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.145364 | 0.183136 | 886.008 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.136317 | 0.177866 | 858.918 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_moderate](A2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.102238 | 0.243742 | 1179.22 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_reference_high_lat_quiet](A2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.66 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.485352 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.460813 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0870058 | 0.303907 | 1333.82 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.114411 | 0.157742 | 690.73 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.091094 | 0.256151 | 1124.22 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.888268 | 4058.23 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.955307 | 4364.75 | — |
| [A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.865922 | 3956.06 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.505515 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.470486 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.3125 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.146747 | 0.183136 | 886.008 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.137665 | 0.177866 | 858.918 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_moderate](A2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.106661 | 0.247694 | 1198.34 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4612.88 | — |
| [A2_encoding_screen_10000_bpsk_soft_high_lat_quiet](A2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.66 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.364583 | 0.00566572 | 25.3928 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.414773 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.390625 | 0 | 0 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.156314 | 0.171278 | 828.723 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.167714 | 0.183136 | 883.706 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.155495 | 0.214756 | 1039.09 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 4613.34 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 4613.34 | — |
| [A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 4617.32 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0282452 | 0.222222 | 16.6147 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0265152 | 0.5 | 37.3831 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0608259 | 0.166667 | 12.461 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0163043 | 0.25 | 12.461 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0204918 | 0.25 | 12.461 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0267857 | 0.333333 | 16.6147 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.00672043 | 0.916667 | 44.1329 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0140224 | 0.272727 | 38.5026 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0284926 | 0.454545 | 64.171 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0243309 | 0.272727 | 38.5026 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.00520833 | 0 | 0 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0266667 | 0.4 | 35.5882 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0291821 | 0.333333 | 31.3725 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0429478 | 0.2 | 18.8235 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.515625 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.484375 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.484375 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_moderate](A2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.104589 | 0.0988142 | 956.028 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_moderate](A2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.125334 | 0.0711462 | 688.341 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_moderate](A2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.142529 | 0.106719 | 1032.51 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_quiet](A2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_quiet](A2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_encoding_screen_10000_qpsk_reference_high_lat_quiet](A2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.76 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.388393 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.421875 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.515625 | 0 | 0 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_moderate](A2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.108406 | 0.0988142 | 956.028 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_moderate](A2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.122863 | 0.0711462 | 688.341 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_moderate](A2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.13879 | 0.106719 | 1032.51 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_quiet](A2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_quiet](A2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.917617 | 9224.61 | — |
| [A2_encoding_screen_10000_qpsk_soft_high_lat_quiet](A2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.918885 | 9235.76 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_disturbed](A2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.478449 | 0 | 0 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_disturbed](A2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.480699 | 0 | 0 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_disturbed](A2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.481227 | 0.000788022 | 25.4773 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_moderate](A2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0692598 | 0.102017 | 4391.91 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_moderate](A2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0590574 | 0.124555 | 5362.21 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_moderate](A2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0806911 | 0.099051 | 4264.24 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_quiet](A2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.00047738 | 0.970636 | 45684.4 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_quiet](A2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.0010531 | 0.953235 | 44865.4 | — |
| [A2_encoding_screen_24000_16qam_reference_high_lat_quiet](A2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000767574 | 0.954323 | 44907 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_disturbed](A2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.482107 | 0 | 0 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_disturbed](A2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.480651 | 0 | 0 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_disturbed](A2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.48044 | 0.000788022 | 25.4773 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_moderate](A2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0692598 | 0.102017 | 4391.91 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_moderate](A2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0603269 | 0.124555 | 5362.21 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_moderate](A2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.080822 | 0.099051 | 4264.24 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_quiet](A2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.00047738 | 0.970636 | 45684.4 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_quiet](A2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.0010531 | 0.953235 | 44865.4 | — |
| [A2_encoding_screen_24000_16qam_soft_high_lat_quiet](A2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000767574 | 0.954323 | 44907 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.449421 | 0.0299448 | 242.057 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.466079 | 0.0141844 | 114.658 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.45692 | 0.0260047 | 210.207 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_moderate](A2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0794452 | 0.580415 | 6244.45 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_moderate](A2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.05 | 0.532344 | 5727.27 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_moderate](A2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.102669 | 0.484866 | 5216.48 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_quiet](A2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11756.9 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_quiet](A2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11756.9 | — |
| [A2_encoding_screen_24000_bpsk_bch_high_lat_quiet](A2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000475351 | 0.98259 | 11557.7 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.420455 | 0.0765993 | 578.876 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.411351 | 0.0673401 | 508.902 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.438171 | 0.030303 | 229.006 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0905118 | 0.465372 | 4591.88 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0737909 | 0.486084 | 4793.05 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.100405 | 0.475081 | 4687.68 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999402 | 10682 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999402 | 10682 | — |
| [A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 10683.5 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.458576 | 0.00245399 | 12.7932 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.420699 | 0.00122699 | 6.3966 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](A2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.426779 | 0.00490798 | 25.5864 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.12319 | 0.395556 | 2267.52 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.239551 | 0.231111 | 1324.84 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](A2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.214835 | 0.288889 | 1656.05 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.981953 | 5916.81 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.998938 | 6019.15 | — |
| [A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](A2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.983015 | 5921.6 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.459792 | 0.00245399 | 12.7932 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.452163 | 0 | 0 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.431373 | 0.00736196 | 38.3796 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.129343 | 0.362222 | 2076.44 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.199579 | 0.243333 | 1394.91 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.235202 | 0.258889 | 1484.08 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.897028 | 5405.08 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.981953 | 5916.81 | — |
| [A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](A2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 0.932059 | 5614.57 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.446067 | 0.0360577 | 290.781 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.450634 | 0.0224359 | 180.93 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.448538 | 0.0304487 | 245.548 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0790516 | 0.557692 | 5991.98 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0599879 | 0.516827 | 5552.91 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0742603 | 0.488582 | 5249.44 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 11731.4 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 11731.4 | — |
| [A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.00131107 | 0.98739 | 11583.4 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.441491 | 0.033123 | 267.606 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.439215 | 0.0315457 | 254.863 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.458092 | 0.022082 | 178.404 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0660004 | 0.585511 | 6297.16 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.063736 | 0.528504 | 5684.05 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.085082 | 0.506532 | 5447.75 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999455 | 11751.9 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999455 | 11751.9 | — |
| [A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000429023 | 0.990196 | 11643 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.460399 | 0.0181245 | 146.494 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.444806 | 0.0291568 | 235.665 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](A2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.44084 | 0.034673 | 280.25 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0630931 | 0.58457 | 6288.55 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0619361 | 0.519881 | 5592.66 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](A2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.10087 | 0.480712 | 5171.3 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](A2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000431988 | 0.982599 | 11559.1 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.446381 | 0.0291568 | 235.665 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.449404 | 0.0197006 | 159.233 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.459981 | 0.0165485 | 133.756 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0801032 | 0.574733 | 6185.83 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0593986 | 0.539739 | 5809.19 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0948179 | 0.488731 | 5260.19 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.00128307 | 0.982599 | 11559.1 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.45986 | 0.0267928 | 216.557 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.436979 | 0.036249 | 292.989 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](A2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.43374 | 0.0417652 | 337.574 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0696658 | 0.586595 | 6313.5 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0596521 | 0.54745 | 5892.17 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](A2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.096214 | 0.481613 | 5183.58 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.2 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.2 | — |
| [A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](A2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000993229 | 0.978793 | 11514.7 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.444126 | 0.0330969 | 267.511 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.457694 | 0.0228526 | 184.71 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.44207 | 0.0283688 | 229.296 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0623003 | 0.598458 | 6441.18 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0731704 | 0.518387 | 5579.37 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_moderate](A2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0996747 | 0.494662 | 5324.02 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_reference_high_lat_quiet](A2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.0054664 | 0.978793 | 11514.4 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.422262 | 0.0765993 | 578.876 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.415455 | 0.0673401 | 508.902 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.442185 | 0.030303 | 229.006 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0905118 | 0.465372 | 4591.88 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0737909 | 0.486084 | 4793.05 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.100405 | 0.475081 | 4687.68 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999402 | 10682 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999402 | 10682 | — |
| [A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 10683.5 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.441954 | 0.0378251 | 305.727 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.460471 | 0.0228526 | 184.71 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.445084 | 0.0283688 | 229.296 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0623003 | 0.598458 | 6441.18 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0730265 | 0.519573 | 5592.14 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_moderate](A2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0996747 | 0.494662 | 5324.02 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11760.7 | — |
| [A2_encoding_screen_24000_bpsk_soft_high_lat_quiet](A2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.0054664 | 0.978793 | 11514.4 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.397066 | 0.0299448 | 242.067 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.3859 | 0.0307329 | 248.437 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](A2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.395626 | 0.0252167 | 203.846 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0671797 | 0.581602 | 6257.41 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0809597 | 0.496736 | 5344.34 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](A2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0849375 | 0.506825 | 5452.89 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.000408108 | 0.99728 | 11730.8 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 11756.4 | — |
| [A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](A2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0.000440749 | 0.98259 | 11558 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0166331 | 0.388889 | 26.9989 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0131048 | 0.666667 | 47.7673 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0285326 | 0.277778 | 18.6916 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0340909 | 0.166667 | 6.74973 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0126812 | 0.333333 | 15.0571 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0307971 | 0.166667 | 8.30736 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0337157 | 0.181818 | 25.6684 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.021141 | 0.363636 | 51.3368 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0359108 | 0.363636 | 51.3368 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.00213068 | 0.954545 | 134.759 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | 0 | 0 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](A2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0 | 0.0666667 | 6.2745 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.00646204 | 0.466667 | 41.8627 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0349363 | 0.133333 | 12.549 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](A2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.034163 | 0.2 | 16.7647 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | 0.00248491 | 0.933333 | 85.7842 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | 0.00106496 | 0.933333 | 85.7842 | — |
| [A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](A2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.480557 | 0.00157604 | 25.4773 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.469937 | 0.00945626 | 152.864 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](A2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.478571 | 0.00394011 | 63.6932 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_moderate](A2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0520663 | 0.470937 | 10137.3 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_moderate](A2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.0384189 | 0.403321 | 8681.86 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_moderate](A2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0672988 | 0.310202 | 6677.37 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_quiet](A2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_quiet](A2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_encoding_screen_24000_qpsk_reference_high_lat_quiet](A2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23528.4 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | 0.475394 | 0.00394011 | 63.6932 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | 0.470695 | 0.00945626 | 152.864 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](A2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | 0.480494 | 0.00394011 | 63.6932 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_moderate](A2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | 0.0520663 | 0.470937 | 10137.3 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_moderate](A2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | 0.038326 | 0.412811 | 8886.14 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_moderate](A2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | 0.0678726 | 0.310202 | 6677.37 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_quiet](A2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_quiet](A2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | 0 | 0.999456 | 23520.4 | — |
| [A2_encoding_screen_24000_qpsk_soft_high_lat_quiet](A2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | 0 | 1 | 23528.4 | — |

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
| Not run (98 declared cases) | — | not_run | — | — | — | — |

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
| [C1_encoding_snr_10000_16qam_reference_0dB](C1_encoding_snr_10000_16qam_reference_0dB/7446529.json) | characterize / full | characterized | 0.022576 | 0.0142077 | 320.569 | — |
| [C1_encoding_snr_10000_16qam_reference_10dB](C1_encoding_snr_10000_16qam_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_12dB](C1_encoding_snr_10000_16qam_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_14dB](C1_encoding_snr_10000_16qam_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_16dB](C1_encoding_snr_10000_16qam_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_18dB](C1_encoding_snr_10000_16qam_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_20dB](C1_encoding_snr_10000_16qam_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_22dB](C1_encoding_snr_10000_16qam_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_24dB](C1_encoding_snr_10000_16qam_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_26dB](C1_encoding_snr_10000_16qam_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_28dB](C1_encoding_snr_10000_16qam_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_2dB](C1_encoding_snr_10000_16qam_reference_2dB/7446529.json) | characterize / full | characterized | 0.00466667 | 0.382514 | 8920.11 | — |
| [C1_encoding_snr_10000_16qam_reference_30dB](C1_encoding_snr_10000_16qam_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_reference_4dB](C1_encoding_snr_10000_16qam_reference_4dB/7446529.json) | characterize / full | characterized | 0.000568065 | 0.873224 | 20377.7 | — |
| [C1_encoding_snr_10000_16qam_reference_6dB](C1_encoding_snr_10000_16qam_reference_6dB/7446529.json) | characterize / full | characterized | 1.70847e-05 | 0.995628 | 23235.7 | — |
| [C1_encoding_snr_10000_16qam_reference_8dB](C1_encoding_snr_10000_16qam_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_0dB](C1_encoding_snr_10000_16qam_soft_0dB/7446529.json) | characterize / full | characterized | 0.022576 | 0.0142077 | 320.569 | — |
| [C1_encoding_snr_10000_16qam_soft_10dB](C1_encoding_snr_10000_16qam_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_12dB](C1_encoding_snr_10000_16qam_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_14dB](C1_encoding_snr_10000_16qam_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_16dB](C1_encoding_snr_10000_16qam_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_18dB](C1_encoding_snr_10000_16qam_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_20dB](C1_encoding_snr_10000_16qam_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_22dB](C1_encoding_snr_10000_16qam_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_24dB](C1_encoding_snr_10000_16qam_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_26dB](C1_encoding_snr_10000_16qam_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_28dB](C1_encoding_snr_10000_16qam_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_2dB](C1_encoding_snr_10000_16qam_soft_2dB/7446529.json) | characterize / full | characterized | 0.00466667 | 0.382514 | 8920.11 | — |
| [C1_encoding_snr_10000_16qam_soft_30dB](C1_encoding_snr_10000_16qam_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_16qam_soft_4dB](C1_encoding_snr_10000_16qam_soft_4dB/7446529.json) | characterize / full | characterized | 0.000568065 | 0.873224 | 20377.7 | — |
| [C1_encoding_snr_10000_16qam_soft_6dB](C1_encoding_snr_10000_16qam_soft_6dB/7446529.json) | characterize / full | characterized | 1.70847e-05 | 0.995628 | 23235.7 | — |
| [C1_encoding_snr_10000_16qam_soft_8dB](C1_encoding_snr_10000_16qam_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 23337.7 | — |
| [C1_encoding_snr_10000_bpsk_bch_0dB](C1_encoding_snr_10000_bpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_10dB](C1_encoding_snr_10000_bpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_12dB](C1_encoding_snr_10000_bpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_14dB](C1_encoding_snr_10000_bpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_16dB](C1_encoding_snr_10000_bpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_18dB](C1_encoding_snr_10000_bpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_20dB](C1_encoding_snr_10000_bpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_22dB](C1_encoding_snr_10000_bpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_24dB](C1_encoding_snr_10000_bpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_26dB](C1_encoding_snr_10000_bpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_28dB](C1_encoding_snr_10000_bpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_2dB](C1_encoding_snr_10000_bpsk_bch_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_30dB](C1_encoding_snr_10000_bpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_4dB](C1_encoding_snr_10000_bpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_6dB](C1_encoding_snr_10000_bpsk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bch_8dB](C1_encoding_snr_10000_bpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.31 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_0dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_10dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_12dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_14dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_16dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_18dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_20dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_22dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_24dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_26dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_28dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_2dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_30dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_4dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_6dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_bpsk_header_reference_8dB](C1_encoding_snr_10000_bpsk_bpsk_header_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_diversity_0dB](C1_encoding_snr_10000_bpsk_diversity_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_10dB](C1_encoding_snr_10000_bpsk_diversity_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_12dB](C1_encoding_snr_10000_bpsk_diversity_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_14dB](C1_encoding_snr_10000_bpsk_diversity_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_16dB](C1_encoding_snr_10000_bpsk_diversity_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_18dB](C1_encoding_snr_10000_bpsk_diversity_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_20dB](C1_encoding_snr_10000_bpsk_diversity_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_22dB](C1_encoding_snr_10000_bpsk_diversity_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_24dB](C1_encoding_snr_10000_bpsk_diversity_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_26dB](C1_encoding_snr_10000_bpsk_diversity_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_28dB](C1_encoding_snr_10000_bpsk_diversity_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_2dB](C1_encoding_snr_10000_bpsk_diversity_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_30dB](C1_encoding_snr_10000_bpsk_diversity_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_4dB](C1_encoding_snr_10000_bpsk_diversity_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_6dB](C1_encoding_snr_10000_bpsk_diversity_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_diversity_8dB](C1_encoding_snr_10000_bpsk_diversity_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_0dB](C1_encoding_snr_10000_bpsk_halfband_control_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_10dB](C1_encoding_snr_10000_bpsk_halfband_control_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_12dB](C1_encoding_snr_10000_bpsk_halfband_control_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_14dB](C1_encoding_snr_10000_bpsk_halfband_control_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_16dB](C1_encoding_snr_10000_bpsk_halfband_control_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_18dB](C1_encoding_snr_10000_bpsk_halfband_control_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_20dB](C1_encoding_snr_10000_bpsk_halfband_control_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_22dB](C1_encoding_snr_10000_bpsk_halfband_control_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_24dB](C1_encoding_snr_10000_bpsk_halfband_control_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_26dB](C1_encoding_snr_10000_bpsk_halfband_control_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_28dB](C1_encoding_snr_10000_bpsk_halfband_control_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_2dB](C1_encoding_snr_10000_bpsk_halfband_control_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_30dB](C1_encoding_snr_10000_bpsk_halfband_control_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_4dB](C1_encoding_snr_10000_bpsk_halfband_control_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_6dB](C1_encoding_snr_10000_bpsk_halfband_control_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_halfband_control_8dB](C1_encoding_snr_10000_bpsk_halfband_control_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 2917.76 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_0dB](C1_encoding_snr_10000_bpsk_interleave2048_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_10dB](C1_encoding_snr_10000_bpsk_interleave2048_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_12dB](C1_encoding_snr_10000_bpsk_interleave2048_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_14dB](C1_encoding_snr_10000_bpsk_interleave2048_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_16dB](C1_encoding_snr_10000_bpsk_interleave2048_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_18dB](C1_encoding_snr_10000_bpsk_interleave2048_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_20dB](C1_encoding_snr_10000_bpsk_interleave2048_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_22dB](C1_encoding_snr_10000_bpsk_interleave2048_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_24dB](C1_encoding_snr_10000_bpsk_interleave2048_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_26dB](C1_encoding_snr_10000_bpsk_interleave2048_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_28dB](C1_encoding_snr_10000_bpsk_interleave2048_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_2dB](C1_encoding_snr_10000_bpsk_interleave2048_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_30dB](C1_encoding_snr_10000_bpsk_interleave2048_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_4dB](C1_encoding_snr_10000_bpsk_interleave2048_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_6dB](C1_encoding_snr_10000_bpsk_interleave2048_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave2048_8dB](C1_encoding_snr_10000_bpsk_interleave2048_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_0dB](C1_encoding_snr_10000_bpsk_interleave256_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_10dB](C1_encoding_snr_10000_bpsk_interleave256_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_12dB](C1_encoding_snr_10000_bpsk_interleave256_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_14dB](C1_encoding_snr_10000_bpsk_interleave256_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_16dB](C1_encoding_snr_10000_bpsk_interleave256_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_18dB](C1_encoding_snr_10000_bpsk_interleave256_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_20dB](C1_encoding_snr_10000_bpsk_interleave256_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_22dB](C1_encoding_snr_10000_bpsk_interleave256_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_24dB](C1_encoding_snr_10000_bpsk_interleave256_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_26dB](C1_encoding_snr_10000_bpsk_interleave256_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_28dB](C1_encoding_snr_10000_bpsk_interleave256_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_2dB](C1_encoding_snr_10000_bpsk_interleave256_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_30dB](C1_encoding_snr_10000_bpsk_interleave256_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_4dB](C1_encoding_snr_10000_bpsk_interleave256_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_6dB](C1_encoding_snr_10000_bpsk_interleave256_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave256_8dB](C1_encoding_snr_10000_bpsk_interleave256_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5830.73 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_0dB](C1_encoding_snr_10000_bpsk_interleave32_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_10dB](C1_encoding_snr_10000_bpsk_interleave32_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_12dB](C1_encoding_snr_10000_bpsk_interleave32_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_14dB](C1_encoding_snr_10000_bpsk_interleave32_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_16dB](C1_encoding_snr_10000_bpsk_interleave32_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_18dB](C1_encoding_snr_10000_bpsk_interleave32_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_20dB](C1_encoding_snr_10000_bpsk_interleave32_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_22dB](C1_encoding_snr_10000_bpsk_interleave32_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_24dB](C1_encoding_snr_10000_bpsk_interleave32_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_26dB](C1_encoding_snr_10000_bpsk_interleave32_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_28dB](C1_encoding_snr_10000_bpsk_interleave32_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_2dB](C1_encoding_snr_10000_bpsk_interleave32_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_30dB](C1_encoding_snr_10000_bpsk_interleave32_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_4dB](C1_encoding_snr_10000_bpsk_interleave32_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_6dB](C1_encoding_snr_10000_bpsk_interleave32_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_interleave32_8dB](C1_encoding_snr_10000_bpsk_interleave32_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_0dB](C1_encoding_snr_10000_bpsk_k9_half_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_10dB](C1_encoding_snr_10000_bpsk_k9_half_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_12dB](C1_encoding_snr_10000_bpsk_k9_half_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_14dB](C1_encoding_snr_10000_bpsk_k9_half_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_16dB](C1_encoding_snr_10000_bpsk_k9_half_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_18dB](C1_encoding_snr_10000_bpsk_k9_half_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_20dB](C1_encoding_snr_10000_bpsk_k9_half_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_22dB](C1_encoding_snr_10000_bpsk_k9_half_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_24dB](C1_encoding_snr_10000_bpsk_k9_half_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_26dB](C1_encoding_snr_10000_bpsk_k9_half_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_28dB](C1_encoding_snr_10000_bpsk_k9_half_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_2dB](C1_encoding_snr_10000_bpsk_k9_half_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_30dB](C1_encoding_snr_10000_bpsk_k9_half_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_4dB](C1_encoding_snr_10000_bpsk_k9_half_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_6dB](C1_encoding_snr_10000_bpsk_k9_half_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_half_8dB](C1_encoding_snr_10000_bpsk_k9_half_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_0dB](C1_encoding_snr_10000_bpsk_k9_third_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_10dB](C1_encoding_snr_10000_bpsk_k9_third_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_12dB](C1_encoding_snr_10000_bpsk_k9_third_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_14dB](C1_encoding_snr_10000_bpsk_k9_third_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_16dB](C1_encoding_snr_10000_bpsk_k9_third_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_18dB](C1_encoding_snr_10000_bpsk_k9_third_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_20dB](C1_encoding_snr_10000_bpsk_k9_third_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_22dB](C1_encoding_snr_10000_bpsk_k9_third_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_24dB](C1_encoding_snr_10000_bpsk_k9_third_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_26dB](C1_encoding_snr_10000_bpsk_k9_third_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_28dB](C1_encoding_snr_10000_bpsk_k9_third_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_2dB](C1_encoding_snr_10000_bpsk_k9_third_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_30dB](C1_encoding_snr_10000_bpsk_k9_third_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_4dB](C1_encoding_snr_10000_bpsk_k9_third_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_6dB](C1_encoding_snr_10000_bpsk_k9_third_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_k9_third_8dB](C1_encoding_snr_10000_bpsk_k9_third_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.04 | — |
| [C1_encoding_snr_10000_bpsk_reference_0dB](C1_encoding_snr_10000_bpsk_reference_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_10dB](C1_encoding_snr_10000_bpsk_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_12dB](C1_encoding_snr_10000_bpsk_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_14dB](C1_encoding_snr_10000_bpsk_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_16dB](C1_encoding_snr_10000_bpsk_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_18dB](C1_encoding_snr_10000_bpsk_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_20dB](C1_encoding_snr_10000_bpsk_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_22dB](C1_encoding_snr_10000_bpsk_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_24dB](C1_encoding_snr_10000_bpsk_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_26dB](C1_encoding_snr_10000_bpsk_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_28dB](C1_encoding_snr_10000_bpsk_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_2dB](C1_encoding_snr_10000_bpsk_reference_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_30dB](C1_encoding_snr_10000_bpsk_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_4dB](C1_encoding_snr_10000_bpsk_reference_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_6dB](C1_encoding_snr_10000_bpsk_reference_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_reference_8dB](C1_encoding_snr_10000_bpsk_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_0dB](C1_encoding_snr_10000_bpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_10dB](C1_encoding_snr_10000_bpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_12dB](C1_encoding_snr_10000_bpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_14dB](C1_encoding_snr_10000_bpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_16dB](C1_encoding_snr_10000_bpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_18dB](C1_encoding_snr_10000_bpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_20dB](C1_encoding_snr_10000_bpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_22dB](C1_encoding_snr_10000_bpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_24dB](C1_encoding_snr_10000_bpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_26dB](C1_encoding_snr_10000_bpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_28dB](C1_encoding_snr_10000_bpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_2dB](C1_encoding_snr_10000_bpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_30dB](C1_encoding_snr_10000_bpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_4dB](C1_encoding_snr_10000_bpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_6dB](C1_encoding_snr_10000_bpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_8dB](C1_encoding_snr_10000_bpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5834.32 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_0dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_10dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_12dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_14dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_16dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_18dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_20dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_22dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_24dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_26dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_28dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_2dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_30dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_4dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_6dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_soft_bpsk_header_8dB](C1_encoding_snr_10000_bpsk_soft_bpsk_header_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5204.65 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_0dB](C1_encoding_snr_10000_bpsk_walsh8_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_10dB](C1_encoding_snr_10000_bpsk_walsh8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_12dB](C1_encoding_snr_10000_bpsk_walsh8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_14dB](C1_encoding_snr_10000_bpsk_walsh8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_16dB](C1_encoding_snr_10000_bpsk_walsh8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_18dB](C1_encoding_snr_10000_bpsk_walsh8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_20dB](C1_encoding_snr_10000_bpsk_walsh8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_22dB](C1_encoding_snr_10000_bpsk_walsh8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_24dB](C1_encoding_snr_10000_bpsk_walsh8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_26dB](C1_encoding_snr_10000_bpsk_walsh8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_28dB](C1_encoding_snr_10000_bpsk_walsh8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_2dB](C1_encoding_snr_10000_bpsk_walsh8_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_30dB](C1_encoding_snr_10000_bpsk_walsh8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_4dB](C1_encoding_snr_10000_bpsk_walsh8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_6dB](C1_encoding_snr_10000_bpsk_walsh8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_bpsk_walsh8_8dB](C1_encoding_snr_10000_bpsk_walsh8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 5833.61 | — |
| [C1_encoding_snr_10000_fsk4_guard4_0dB](C1_encoding_snr_10000_fsk4_guard4_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_10dB](C1_encoding_snr_10000_fsk4_guard4_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_12dB](C1_encoding_snr_10000_fsk4_guard4_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_14dB](C1_encoding_snr_10000_fsk4_guard4_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_16dB](C1_encoding_snr_10000_fsk4_guard4_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_18dB](C1_encoding_snr_10000_fsk4_guard4_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_20dB](C1_encoding_snr_10000_fsk4_guard4_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_22dB](C1_encoding_snr_10000_fsk4_guard4_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_24dB](C1_encoding_snr_10000_fsk4_guard4_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_26dB](C1_encoding_snr_10000_fsk4_guard4_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_28dB](C1_encoding_snr_10000_fsk4_guard4_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_2dB](C1_encoding_snr_10000_fsk4_guard4_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_30dB](C1_encoding_snr_10000_fsk4_guard4_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_4dB](C1_encoding_snr_10000_fsk4_guard4_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_6dB](C1_encoding_snr_10000_fsk4_guard4_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard4_8dB](C1_encoding_snr_10000_fsk4_guard4_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_10000_fsk4_guard8_0dB](C1_encoding_snr_10000_fsk4_guard8_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_10dB](C1_encoding_snr_10000_fsk4_guard8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_12dB](C1_encoding_snr_10000_fsk4_guard8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_14dB](C1_encoding_snr_10000_fsk4_guard8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_16dB](C1_encoding_snr_10000_fsk4_guard8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_18dB](C1_encoding_snr_10000_fsk4_guard8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_20dB](C1_encoding_snr_10000_fsk4_guard8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_22dB](C1_encoding_snr_10000_fsk4_guard8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_24dB](C1_encoding_snr_10000_fsk4_guard8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_26dB](C1_encoding_snr_10000_fsk4_guard8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_28dB](C1_encoding_snr_10000_fsk4_guard8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_2dB](C1_encoding_snr_10000_fsk4_guard8_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_30dB](C1_encoding_snr_10000_fsk4_guard8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_4dB](C1_encoding_snr_10000_fsk4_guard8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_6dB](C1_encoding_snr_10000_fsk4_guard8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk4_guard8_8dB](C1_encoding_snr_10000_fsk4_guard8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_10000_fsk8_guard4_0dB](C1_encoding_snr_10000_fsk8_guard4_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_10dB](C1_encoding_snr_10000_fsk8_guard4_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_12dB](C1_encoding_snr_10000_fsk8_guard4_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_14dB](C1_encoding_snr_10000_fsk8_guard4_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_16dB](C1_encoding_snr_10000_fsk8_guard4_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_18dB](C1_encoding_snr_10000_fsk8_guard4_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_20dB](C1_encoding_snr_10000_fsk8_guard4_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_22dB](C1_encoding_snr_10000_fsk8_guard4_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_24dB](C1_encoding_snr_10000_fsk8_guard4_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_26dB](C1_encoding_snr_10000_fsk8_guard4_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_28dB](C1_encoding_snr_10000_fsk8_guard4_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_2dB](C1_encoding_snr_10000_fsk8_guard4_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_30dB](C1_encoding_snr_10000_fsk8_guard4_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_4dB](C1_encoding_snr_10000_fsk8_guard4_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_6dB](C1_encoding_snr_10000_fsk8_guard4_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard4_8dB](C1_encoding_snr_10000_fsk8_guard4_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_10000_fsk8_guard8_0dB](C1_encoding_snr_10000_fsk8_guard8_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_10dB](C1_encoding_snr_10000_fsk8_guard8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_12dB](C1_encoding_snr_10000_fsk8_guard8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_14dB](C1_encoding_snr_10000_fsk8_guard8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_16dB](C1_encoding_snr_10000_fsk8_guard8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_18dB](C1_encoding_snr_10000_fsk8_guard8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_20dB](C1_encoding_snr_10000_fsk8_guard8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_22dB](C1_encoding_snr_10000_fsk8_guard8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_24dB](C1_encoding_snr_10000_fsk8_guard8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_26dB](C1_encoding_snr_10000_fsk8_guard8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_28dB](C1_encoding_snr_10000_fsk8_guard8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_2dB](C1_encoding_snr_10000_fsk8_guard8_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_30dB](C1_encoding_snr_10000_fsk8_guard8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_4dB](C1_encoding_snr_10000_fsk8_guard8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_6dB](C1_encoding_snr_10000_fsk8_guard8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_fsk8_guard8_8dB](C1_encoding_snr_10000_fsk8_guard8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_10000_qpsk_reference_0dB](C1_encoding_snr_10000_qpsk_reference_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_10dB](C1_encoding_snr_10000_qpsk_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_12dB](C1_encoding_snr_10000_qpsk_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_14dB](C1_encoding_snr_10000_qpsk_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_16dB](C1_encoding_snr_10000_qpsk_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_18dB](C1_encoding_snr_10000_qpsk_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_20dB](C1_encoding_snr_10000_qpsk_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_22dB](C1_encoding_snr_10000_qpsk_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_24dB](C1_encoding_snr_10000_qpsk_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_26dB](C1_encoding_snr_10000_qpsk_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_28dB](C1_encoding_snr_10000_qpsk_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_2dB](C1_encoding_snr_10000_qpsk_reference_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_30dB](C1_encoding_snr_10000_qpsk_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_4dB](C1_encoding_snr_10000_qpsk_reference_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_6dB](C1_encoding_snr_10000_qpsk_reference_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_reference_8dB](C1_encoding_snr_10000_qpsk_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_0dB](C1_encoding_snr_10000_qpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_10dB](C1_encoding_snr_10000_qpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_12dB](C1_encoding_snr_10000_qpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_14dB](C1_encoding_snr_10000_qpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_16dB](C1_encoding_snr_10000_qpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_18dB](C1_encoding_snr_10000_qpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_20dB](C1_encoding_snr_10000_qpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_22dB](C1_encoding_snr_10000_qpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_24dB](C1_encoding_snr_10000_qpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_26dB](C1_encoding_snr_10000_qpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_28dB](C1_encoding_snr_10000_qpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_2dB](C1_encoding_snr_10000_qpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_30dB](C1_encoding_snr_10000_qpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_4dB](C1_encoding_snr_10000_qpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_6dB](C1_encoding_snr_10000_qpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_10000_qpsk_soft_8dB](C1_encoding_snr_10000_qpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 11668.6 | — |
| [C1_encoding_snr_24000_16qam_reference_0dB](C1_encoding_snr_24000_16qam_reference_0dB/7446529.json) | characterize / full | characterized | 0.193229 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_reference_10dB](C1_encoding_snr_24000_16qam_reference_10dB/7446529.json) | characterize / full | characterized | 0.00328844 | 0.482916 | 27097.3 | — |
| [C1_encoding_snr_24000_16qam_reference_12dB](C1_encoding_snr_24000_16qam_reference_12dB/7446529.json) | characterize / full | characterized | 0.000395097 | 0.90615 | 50848.6 | — |
| [C1_encoding_snr_24000_16qam_reference_14dB](C1_encoding_snr_24000_16qam_reference_14dB/7446529.json) | characterize / full | characterized | 1.06783e-05 | 0.997267 | 55961.9 | — |
| [C1_encoding_snr_24000_16qam_reference_16dB](C1_encoding_snr_24000_16qam_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_18dB](C1_encoding_snr_24000_16qam_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_20dB](C1_encoding_snr_24000_16qam_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_22dB](C1_encoding_snr_24000_16qam_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_24dB](C1_encoding_snr_24000_16qam_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_26dB](C1_encoding_snr_24000_16qam_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_28dB](C1_encoding_snr_24000_16qam_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_2dB](C1_encoding_snr_24000_16qam_reference_2dB/7446529.json) | characterize / full | characterized | 0.144291 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_reference_30dB](C1_encoding_snr_24000_16qam_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_reference_4dB](C1_encoding_snr_24000_16qam_reference_4dB/7446529.json) | characterize / full | characterized | 0.0963235 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_reference_6dB](C1_encoding_snr_24000_16qam_reference_6dB/7446529.json) | characterize / full | characterized | 0.0514732 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_reference_8dB](C1_encoding_snr_24000_16qam_reference_8dB/7446529.json) | characterize / full | characterized | 0.0176729 | 0.0341686 | 1917.49 | — |
| [C1_encoding_snr_24000_16qam_soft_0dB](C1_encoding_snr_24000_16qam_soft_0dB/7446529.json) | characterize / full | characterized | 0.193623 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_soft_10dB](C1_encoding_snr_24000_16qam_soft_10dB/7446529.json) | characterize / full | characterized | 0.00328844 | 0.482916 | 27097.3 | — |
| [C1_encoding_snr_24000_16qam_soft_12dB](C1_encoding_snr_24000_16qam_soft_12dB/7446529.json) | characterize / full | characterized | 0.000395097 | 0.90615 | 50848.6 | — |
| [C1_encoding_snr_24000_16qam_soft_14dB](C1_encoding_snr_24000_16qam_soft_14dB/7446529.json) | characterize / full | characterized | 1.06783e-05 | 0.997267 | 55961.9 | — |
| [C1_encoding_snr_24000_16qam_soft_16dB](C1_encoding_snr_24000_16qam_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_18dB](C1_encoding_snr_24000_16qam_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_20dB](C1_encoding_snr_24000_16qam_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_22dB](C1_encoding_snr_24000_16qam_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_24dB](C1_encoding_snr_24000_16qam_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_26dB](C1_encoding_snr_24000_16qam_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_28dB](C1_encoding_snr_24000_16qam_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_2dB](C1_encoding_snr_24000_16qam_soft_2dB/7446529.json) | characterize / full | characterized | 0.144291 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_soft_30dB](C1_encoding_snr_24000_16qam_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 56115.3 | — |
| [C1_encoding_snr_24000_16qam_soft_4dB](C1_encoding_snr_24000_16qam_soft_4dB/7446529.json) | characterize / full | characterized | 0.0963235 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_soft_6dB](C1_encoding_snr_24000_16qam_soft_6dB/7446529.json) | characterize / full | characterized | 0.0514732 | 0 | 0 | — |
| [C1_encoding_snr_24000_16qam_soft_8dB](C1_encoding_snr_24000_16qam_soft_8dB/7446529.json) | characterize / full | characterized | 0.0176729 | 0.0341686 | 1917.49 | — |
| [C1_encoding_snr_24000_bpsk_bch_0dB](C1_encoding_snr_24000_bpsk_bch_0dB/7446529.json) | characterize / full | characterized | 0.000397749 | 0.925285 | 12979 | — |
| [C1_encoding_snr_24000_bpsk_bch_10dB](C1_encoding_snr_24000_bpsk_bch_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_12dB](C1_encoding_snr_24000_bpsk_bch_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_14dB](C1_encoding_snr_24000_bpsk_bch_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_16dB](C1_encoding_snr_24000_bpsk_bch_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_18dB](C1_encoding_snr_24000_bpsk_bch_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_20dB](C1_encoding_snr_24000_bpsk_bch_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_22dB](C1_encoding_snr_24000_bpsk_bch_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_24dB](C1_encoding_snr_24000_bpsk_bch_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_26dB](C1_encoding_snr_24000_bpsk_bch_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_28dB](C1_encoding_snr_24000_bpsk_bch_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_2dB](C1_encoding_snr_24000_bpsk_bch_2dB/7446529.json) | characterize / full | characterized | 2.13648e-05 | 0.998633 | 14008.3 | — |
| [C1_encoding_snr_24000_bpsk_bch_30dB](C1_encoding_snr_24000_bpsk_bch_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_4dB](C1_encoding_snr_24000_bpsk_bch_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_6dB](C1_encoding_snr_24000_bpsk_bch_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bch_8dB](C1_encoding_snr_24000_bpsk_bch_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14027.5 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_0dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_0dB/7446529.json) | characterize / full | characterized | 0.000614373 | 0.922018 | 11567.9 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_10dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_12dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_14dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_16dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_18dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_20dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_22dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_24dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_26dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_28dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_2dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_30dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_4dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_6dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_bpsk_header_reference_8dB](C1_encoding_snr_24000_bpsk_bpsk_header_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_diversity_0dB](C1_encoding_snr_24000_bpsk_diversity_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_10dB](C1_encoding_snr_24000_bpsk_diversity_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_12dB](C1_encoding_snr_24000_bpsk_diversity_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_14dB](C1_encoding_snr_24000_bpsk_diversity_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_16dB](C1_encoding_snr_24000_bpsk_diversity_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_18dB](C1_encoding_snr_24000_bpsk_diversity_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_20dB](C1_encoding_snr_24000_bpsk_diversity_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_22dB](C1_encoding_snr_24000_bpsk_diversity_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_24dB](C1_encoding_snr_24000_bpsk_diversity_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_26dB](C1_encoding_snr_24000_bpsk_diversity_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_28dB](C1_encoding_snr_24000_bpsk_diversity_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_2dB](C1_encoding_snr_24000_bpsk_diversity_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_30dB](C1_encoding_snr_24000_bpsk_diversity_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_4dB](C1_encoding_snr_24000_bpsk_diversity_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_6dB](C1_encoding_snr_24000_bpsk_diversity_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_diversity_8dB](C1_encoding_snr_24000_bpsk_diversity_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_0dB](C1_encoding_snr_24000_bpsk_halfband_control_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_10dB](C1_encoding_snr_24000_bpsk_halfband_control_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_12dB](C1_encoding_snr_24000_bpsk_halfband_control_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_14dB](C1_encoding_snr_24000_bpsk_halfband_control_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_16dB](C1_encoding_snr_24000_bpsk_halfband_control_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_18dB](C1_encoding_snr_24000_bpsk_halfband_control_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_20dB](C1_encoding_snr_24000_bpsk_halfband_control_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_22dB](C1_encoding_snr_24000_bpsk_halfband_control_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_24dB](C1_encoding_snr_24000_bpsk_halfband_control_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_26dB](C1_encoding_snr_24000_bpsk_halfband_control_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_28dB](C1_encoding_snr_24000_bpsk_halfband_control_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_2dB](C1_encoding_snr_24000_bpsk_halfband_control_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_30dB](C1_encoding_snr_24000_bpsk_halfband_control_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_4dB](C1_encoding_snr_24000_bpsk_halfband_control_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_6dB](C1_encoding_snr_24000_bpsk_halfband_control_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_halfband_control_8dB](C1_encoding_snr_24000_bpsk_halfband_control_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 7014.16 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_0dB](C1_encoding_snr_24000_bpsk_interleave2048_0dB/7446529.json) | characterize / full | characterized | 0.000537488 | 0.91682 | 12857.9 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_10dB](C1_encoding_snr_24000_bpsk_interleave2048_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_12dB](C1_encoding_snr_24000_bpsk_interleave2048_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_14dB](C1_encoding_snr_24000_bpsk_interleave2048_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_16dB](C1_encoding_snr_24000_bpsk_interleave2048_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_18dB](C1_encoding_snr_24000_bpsk_interleave2048_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_20dB](C1_encoding_snr_24000_bpsk_interleave2048_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_22dB](C1_encoding_snr_24000_bpsk_interleave2048_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_24dB](C1_encoding_snr_24000_bpsk_interleave2048_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_26dB](C1_encoding_snr_24000_bpsk_interleave2048_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_28dB](C1_encoding_snr_24000_bpsk_interleave2048_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_2dB](C1_encoding_snr_24000_bpsk_interleave2048_2dB/7446529.json) | characterize / full | characterized | 2.15418e-05 | 0.998621 | 14005.1 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_30dB](C1_encoding_snr_24000_bpsk_interleave2048_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_4dB](C1_encoding_snr_24000_bpsk_interleave2048_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_6dB](C1_encoding_snr_24000_bpsk_interleave2048_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave2048_8dB](C1_encoding_snr_24000_bpsk_interleave2048_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.4 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_0dB](C1_encoding_snr_24000_bpsk_interleave256_0dB/7446529.json) | characterize / full | characterized | 0.000488281 | 0.921077 | 12917.7 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_10dB](C1_encoding_snr_24000_bpsk_interleave256_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_12dB](C1_encoding_snr_24000_bpsk_interleave256_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_14dB](C1_encoding_snr_24000_bpsk_interleave256_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_16dB](C1_encoding_snr_24000_bpsk_interleave256_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_18dB](C1_encoding_snr_24000_bpsk_interleave256_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_20dB](C1_encoding_snr_24000_bpsk_interleave256_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_22dB](C1_encoding_snr_24000_bpsk_interleave256_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_24dB](C1_encoding_snr_24000_bpsk_interleave256_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_26dB](C1_encoding_snr_24000_bpsk_interleave256_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_28dB](C1_encoding_snr_24000_bpsk_interleave256_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_2dB](C1_encoding_snr_24000_bpsk_interleave256_2dB/7446529.json) | characterize / full | characterized | 3.5641e-05 | 0.997719 | 13992.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_30dB](C1_encoding_snr_24000_bpsk_interleave256_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_4dB](C1_encoding_snr_24000_bpsk_interleave256_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_6dB](C1_encoding_snr_24000_bpsk_interleave256_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave256_8dB](C1_encoding_snr_24000_bpsk_interleave256_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14024.6 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_0dB](C1_encoding_snr_24000_bpsk_interleave32_0dB/7446529.json) | characterize / full | characterized | 0.000427671 | 0.924374 | 12967 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_10dB](C1_encoding_snr_24000_bpsk_interleave32_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_12dB](C1_encoding_snr_24000_bpsk_interleave32_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_14dB](C1_encoding_snr_24000_bpsk_interleave32_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_16dB](C1_encoding_snr_24000_bpsk_interleave32_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_18dB](C1_encoding_snr_24000_bpsk_interleave32_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_20dB](C1_encoding_snr_24000_bpsk_interleave32_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_22dB](C1_encoding_snr_24000_bpsk_interleave32_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_24dB](C1_encoding_snr_24000_bpsk_interleave32_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_26dB](C1_encoding_snr_24000_bpsk_interleave32_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_28dB](C1_encoding_snr_24000_bpsk_interleave32_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_2dB](C1_encoding_snr_24000_bpsk_interleave32_2dB/7446529.json) | characterize / full | characterized | 2.13602e-05 | 0.998633 | 14009 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_30dB](C1_encoding_snr_24000_bpsk_interleave32_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_4dB](C1_encoding_snr_24000_bpsk_interleave32_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_6dB](C1_encoding_snr_24000_bpsk_interleave32_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_interleave32_8dB](C1_encoding_snr_24000_bpsk_interleave32_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.2 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_0dB](C1_encoding_snr_24000_bpsk_k9_half_0dB/7446529.json) | characterize / full | characterized | 0.000375105 | 0.926196 | 12993.1 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_10dB](C1_encoding_snr_24000_bpsk_k9_half_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_12dB](C1_encoding_snr_24000_bpsk_k9_half_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_14dB](C1_encoding_snr_24000_bpsk_k9_half_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_16dB](C1_encoding_snr_24000_bpsk_k9_half_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_18dB](C1_encoding_snr_24000_bpsk_k9_half_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_20dB](C1_encoding_snr_24000_bpsk_k9_half_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_22dB](C1_encoding_snr_24000_bpsk_k9_half_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_24dB](C1_encoding_snr_24000_bpsk_k9_half_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_26dB](C1_encoding_snr_24000_bpsk_k9_half_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_28dB](C1_encoding_snr_24000_bpsk_k9_half_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_2dB](C1_encoding_snr_24000_bpsk_k9_half_2dB/7446529.json) | characterize / full | characterized | 1.42385e-05 | 0.999089 | 14015.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_30dB](C1_encoding_snr_24000_bpsk_k9_half_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_4dB](C1_encoding_snr_24000_bpsk_k9_half_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_6dB](C1_encoding_snr_24000_bpsk_k9_half_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_half_8dB](C1_encoding_snr_24000_bpsk_k9_half_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_0dB](C1_encoding_snr_24000_bpsk_k9_third_0dB/7446529.json) | characterize / full | characterized | 0.000450099 | 0.922096 | 12935.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_10dB](C1_encoding_snr_24000_bpsk_k9_third_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_12dB](C1_encoding_snr_24000_bpsk_k9_third_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_14dB](C1_encoding_snr_24000_bpsk_k9_third_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_16dB](C1_encoding_snr_24000_bpsk_k9_third_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_18dB](C1_encoding_snr_24000_bpsk_k9_third_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_20dB](C1_encoding_snr_24000_bpsk_k9_third_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_22dB](C1_encoding_snr_24000_bpsk_k9_third_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_24dB](C1_encoding_snr_24000_bpsk_k9_third_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_26dB](C1_encoding_snr_24000_bpsk_k9_third_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_28dB](C1_encoding_snr_24000_bpsk_k9_third_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_2dB](C1_encoding_snr_24000_bpsk_k9_third_2dB/7446529.json) | characterize / full | characterized | 7.11886e-06 | 0.999544 | 14022.4 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_30dB](C1_encoding_snr_24000_bpsk_k9_third_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_4dB](C1_encoding_snr_24000_bpsk_k9_third_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_6dB](C1_encoding_snr_24000_bpsk_k9_third_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_k9_third_8dB](C1_encoding_snr_24000_bpsk_k9_third_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.8 | — |
| [C1_encoding_snr_24000_bpsk_reference_0dB](C1_encoding_snr_24000_bpsk_reference_0dB/7446529.json) | characterize / full | characterized | 0.000370449 | 0.919362 | 12897.2 | — |
| [C1_encoding_snr_24000_bpsk_reference_10dB](C1_encoding_snr_24000_bpsk_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_12dB](C1_encoding_snr_24000_bpsk_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_14dB](C1_encoding_snr_24000_bpsk_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_16dB](C1_encoding_snr_24000_bpsk_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_18dB](C1_encoding_snr_24000_bpsk_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_20dB](C1_encoding_snr_24000_bpsk_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_22dB](C1_encoding_snr_24000_bpsk_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_24dB](C1_encoding_snr_24000_bpsk_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_26dB](C1_encoding_snr_24000_bpsk_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_28dB](C1_encoding_snr_24000_bpsk_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_2dB](C1_encoding_snr_24000_bpsk_reference_2dB/7446529.json) | characterize / full | characterized | 7.11926e-06 | 0.999544 | 14022.2 | — |
| [C1_encoding_snr_24000_bpsk_reference_30dB](C1_encoding_snr_24000_bpsk_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_4dB](C1_encoding_snr_24000_bpsk_reference_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_6dB](C1_encoding_snr_24000_bpsk_reference_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_reference_8dB](C1_encoding_snr_24000_bpsk_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_0dB](C1_encoding_snr_24000_bpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0.000367603 | 0.926651 | 12999.5 | — |
| [C1_encoding_snr_24000_bpsk_soft_10dB](C1_encoding_snr_24000_bpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_12dB](C1_encoding_snr_24000_bpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_14dB](C1_encoding_snr_24000_bpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_16dB](C1_encoding_snr_24000_bpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_18dB](C1_encoding_snr_24000_bpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_20dB](C1_encoding_snr_24000_bpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_22dB](C1_encoding_snr_24000_bpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_24dB](C1_encoding_snr_24000_bpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_26dB](C1_encoding_snr_24000_bpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_28dB](C1_encoding_snr_24000_bpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_2dB](C1_encoding_snr_24000_bpsk_soft_2dB/7446529.json) | characterize / full | characterized | 7.11926e-06 | 0.999544 | 14022.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_30dB](C1_encoding_snr_24000_bpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_4dB](C1_encoding_snr_24000_bpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_6dB](C1_encoding_snr_24000_bpsk_soft_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_8dB](C1_encoding_snr_24000_bpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.6 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_0dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_0dB/7446529.json) | characterize / full | characterized | 0.000614373 | 0.922018 | 11567.9 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_10dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_12dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_14dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_16dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_18dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_20dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_22dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_24dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_26dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_28dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_2dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_30dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_4dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_6dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_soft_bpsk_header_8dB](C1_encoding_snr_24000_bpsk_soft_bpsk_header_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 12546.2 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_0dB](C1_encoding_snr_24000_bpsk_walsh8_0dB/7446529.json) | characterize / full | characterized | 0.000480163 | 0.921185 | 12922.5 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_10dB](C1_encoding_snr_24000_bpsk_walsh8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_12dB](C1_encoding_snr_24000_bpsk_walsh8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_14dB](C1_encoding_snr_24000_bpsk_walsh8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_16dB](C1_encoding_snr_24000_bpsk_walsh8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_18dB](C1_encoding_snr_24000_bpsk_walsh8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_20dB](C1_encoding_snr_24000_bpsk_walsh8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_22dB](C1_encoding_snr_24000_bpsk_walsh8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_24dB](C1_encoding_snr_24000_bpsk_walsh8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_26dB](C1_encoding_snr_24000_bpsk_walsh8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_28dB](C1_encoding_snr_24000_bpsk_walsh8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_2dB](C1_encoding_snr_24000_bpsk_walsh8_2dB/7446529.json) | characterize / full | characterized | 1.42393e-05 | 0.999089 | 14015.6 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_30dB](C1_encoding_snr_24000_bpsk_walsh8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_4dB](C1_encoding_snr_24000_bpsk_walsh8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_6dB](C1_encoding_snr_24000_bpsk_walsh8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_bpsk_walsh8_8dB](C1_encoding_snr_24000_bpsk_walsh8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 14028.4 | — |
| [C1_encoding_snr_24000_fsk4_guard4_0dB](C1_encoding_snr_24000_fsk4_guard4_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_10dB](C1_encoding_snr_24000_fsk4_guard4_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_12dB](C1_encoding_snr_24000_fsk4_guard4_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_14dB](C1_encoding_snr_24000_fsk4_guard4_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_16dB](C1_encoding_snr_24000_fsk4_guard4_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_18dB](C1_encoding_snr_24000_fsk4_guard4_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_20dB](C1_encoding_snr_24000_fsk4_guard4_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_22dB](C1_encoding_snr_24000_fsk4_guard4_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_24dB](C1_encoding_snr_24000_fsk4_guard4_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_26dB](C1_encoding_snr_24000_fsk4_guard4_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_28dB](C1_encoding_snr_24000_fsk4_guard4_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_2dB](C1_encoding_snr_24000_fsk4_guard4_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_30dB](C1_encoding_snr_24000_fsk4_guard4_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_4dB](C1_encoding_snr_24000_fsk4_guard4_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_6dB](C1_encoding_snr_24000_fsk4_guard4_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard4_8dB](C1_encoding_snr_24000_fsk4_guard4_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 72.6894 | — |
| [C1_encoding_snr_24000_fsk4_guard8_0dB](C1_encoding_snr_24000_fsk4_guard8_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_10dB](C1_encoding_snr_24000_fsk4_guard8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_12dB](C1_encoding_snr_24000_fsk4_guard8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_14dB](C1_encoding_snr_24000_fsk4_guard8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_16dB](C1_encoding_snr_24000_fsk4_guard8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_18dB](C1_encoding_snr_24000_fsk4_guard8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_20dB](C1_encoding_snr_24000_fsk4_guard8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_22dB](C1_encoding_snr_24000_fsk4_guard8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_24dB](C1_encoding_snr_24000_fsk4_guard8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_26dB](C1_encoding_snr_24000_fsk4_guard8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_28dB](C1_encoding_snr_24000_fsk4_guard8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_2dB](C1_encoding_snr_24000_fsk4_guard8_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_30dB](C1_encoding_snr_24000_fsk4_guard8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_4dB](C1_encoding_snr_24000_fsk4_guard8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_6dB](C1_encoding_snr_24000_fsk4_guard8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk4_guard8_8dB](C1_encoding_snr_24000_fsk4_guard8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 48.2865 | — |
| [C1_encoding_snr_24000_fsk8_guard4_0dB](C1_encoding_snr_24000_fsk8_guard4_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_10dB](C1_encoding_snr_24000_fsk8_guard4_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_12dB](C1_encoding_snr_24000_fsk8_guard4_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_14dB](C1_encoding_snr_24000_fsk8_guard4_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_16dB](C1_encoding_snr_24000_fsk8_guard4_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_18dB](C1_encoding_snr_24000_fsk8_guard4_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_20dB](C1_encoding_snr_24000_fsk8_guard4_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_22dB](C1_encoding_snr_24000_fsk8_guard4_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_24dB](C1_encoding_snr_24000_fsk8_guard4_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_26dB](C1_encoding_snr_24000_fsk8_guard4_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_28dB](C1_encoding_snr_24000_fsk8_guard4_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_2dB](C1_encoding_snr_24000_fsk8_guard4_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_30dB](C1_encoding_snr_24000_fsk8_guard4_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_4dB](C1_encoding_snr_24000_fsk8_guard4_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_6dB](C1_encoding_snr_24000_fsk8_guard4_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard4_8dB](C1_encoding_snr_24000_fsk8_guard4_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 141.176 | — |
| [C1_encoding_snr_24000_fsk8_guard8_0dB](C1_encoding_snr_24000_fsk8_guard8_0dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_10dB](C1_encoding_snr_24000_fsk8_guard8_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_12dB](C1_encoding_snr_24000_fsk8_guard8_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_14dB](C1_encoding_snr_24000_fsk8_guard8_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_16dB](C1_encoding_snr_24000_fsk8_guard8_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_18dB](C1_encoding_snr_24000_fsk8_guard8_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_20dB](C1_encoding_snr_24000_fsk8_guard8_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_22dB](C1_encoding_snr_24000_fsk8_guard8_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_24dB](C1_encoding_snr_24000_fsk8_guard8_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_26dB](C1_encoding_snr_24000_fsk8_guard8_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_28dB](C1_encoding_snr_24000_fsk8_guard8_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_2dB](C1_encoding_snr_24000_fsk8_guard8_2dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_30dB](C1_encoding_snr_24000_fsk8_guard8_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_4dB](C1_encoding_snr_24000_fsk8_guard8_4dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_6dB](C1_encoding_snr_24000_fsk8_guard8_6dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_fsk8_guard8_8dB](C1_encoding_snr_24000_fsk8_guard8_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 92.0587 | — |
| [C1_encoding_snr_24000_qpsk_reference_0dB](C1_encoding_snr_24000_qpsk_reference_0dB/7446529.json) | characterize / full | characterized | 0.0196951 | 0.194989 | 5469.63 | — |
| [C1_encoding_snr_24000_qpsk_reference_10dB](C1_encoding_snr_24000_qpsk_reference_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_12dB](C1_encoding_snr_24000_qpsk_reference_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_14dB](C1_encoding_snr_24000_qpsk_reference_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_16dB](C1_encoding_snr_24000_qpsk_reference_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_18dB](C1_encoding_snr_24000_qpsk_reference_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_20dB](C1_encoding_snr_24000_qpsk_reference_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_22dB](C1_encoding_snr_24000_qpsk_reference_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_24dB](C1_encoding_snr_24000_qpsk_reference_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_26dB](C1_encoding_snr_24000_qpsk_reference_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_28dB](C1_encoding_snr_24000_qpsk_reference_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_2dB](C1_encoding_snr_24000_qpsk_reference_2dB/7446529.json) | characterize / full | characterized | 0.00302551 | 0.77221 | 21666 | — |
| [C1_encoding_snr_24000_qpsk_reference_30dB](C1_encoding_snr_24000_qpsk_reference_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_reference_4dB](C1_encoding_snr_24000_qpsk_reference_4dB/7446529.json) | characterize / full | characterized | 0.00018865 | 0.983144 | 27584.7 | — |
| [C1_encoding_snr_24000_qpsk_reference_6dB](C1_encoding_snr_24000_qpsk_reference_6dB/7446529.json) | characterize / full | characterized | 3.55943e-06 | 0.999544 | 28044.8 | — |
| [C1_encoding_snr_24000_qpsk_reference_8dB](C1_encoding_snr_24000_qpsk_reference_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_0dB](C1_encoding_snr_24000_qpsk_soft_0dB/7446529.json) | characterize / full | characterized | 0.0196265 | 0.197267 | 5533.55 | — |
| [C1_encoding_snr_24000_qpsk_soft_10dB](C1_encoding_snr_24000_qpsk_soft_10dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_12dB](C1_encoding_snr_24000_qpsk_soft_12dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_14dB](C1_encoding_snr_24000_qpsk_soft_14dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_16dB](C1_encoding_snr_24000_qpsk_soft_16dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_18dB](C1_encoding_snr_24000_qpsk_soft_18dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_20dB](C1_encoding_snr_24000_qpsk_soft_20dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_22dB](C1_encoding_snr_24000_qpsk_soft_22dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_24dB](C1_encoding_snr_24000_qpsk_soft_24dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_26dB](C1_encoding_snr_24000_qpsk_soft_26dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_28dB](C1_encoding_snr_24000_qpsk_soft_28dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_2dB](C1_encoding_snr_24000_qpsk_soft_2dB/7446529.json) | characterize / full | characterized | 0.00302551 | 0.77221 | 21666 | — |
| [C1_encoding_snr_24000_qpsk_soft_30dB](C1_encoding_snr_24000_qpsk_soft_30dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |
| [C1_encoding_snr_24000_qpsk_soft_4dB](C1_encoding_snr_24000_qpsk_soft_4dB/7446529.json) | characterize / full | characterized | 0.00018865 | 0.983144 | 27584.7 | — |
| [C1_encoding_snr_24000_qpsk_soft_6dB](C1_encoding_snr_24000_qpsk_soft_6dB/7446529.json) | characterize / full | characterized | 3.55943e-06 | 0.999544 | 28044.8 | — |
| [C1_encoding_snr_24000_qpsk_soft_8dB](C1_encoding_snr_24000_qpsk_soft_8dB/7446529.json) | characterize / full | characterized | 0 | 1 | 28057.6 | — |

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
| [C4_encoding_10000_16qam_reference_null](C4_encoding_10000_16qam_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 23159.2 | — |
| [C4_encoding_10000_16qam_soft_null](C4_encoding_10000_16qam_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 23159.2 | — |
| [C4_encoding_10000_bpsk_bch_null](C4_encoding_10000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 5786.27 | — |
| [C4_encoding_10000_bpsk_bpsk_header_reference_null](C4_encoding_10000_bpsk_bpsk_header_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 5163.94 | — |
| [C4_encoding_10000_bpsk_diversity_null](C4_encoding_10000_bpsk_diversity_null/7446529.json) | assert / quick | pass | 0 | 1 | 2894.35 | — |
| [C4_encoding_10000_bpsk_halfband_control_null](C4_encoding_10000_bpsk_halfband_control_null/7446529.json) | assert / quick | pass | 0 | 1 | 2894.35 | — |
| [C4_encoding_10000_bpsk_interleave2048_null](C4_encoding_10000_bpsk_interleave2048_null/7446529.json) | assert / quick | pass | 0 | 1 | 5773.12 | — |
| [C4_encoding_10000_bpsk_interleave256_null](C4_encoding_10000_bpsk_interleave256_null/7446529.json) | assert / quick | pass | 0 | 1 | 5777.79 | — |
| [C4_encoding_10000_bpsk_interleave32_null](C4_encoding_10000_bpsk_interleave32_null/7446529.json) | assert / quick | pass | 0 | 1 | 5787.62 | — |
| [C4_encoding_10000_bpsk_k9_half_null](C4_encoding_10000_bpsk_k9_half_null/7446529.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_encoding_10000_bpsk_k9_third_null](C4_encoding_10000_bpsk_k9_third_null/7446529.json) | assert / quick | pass | 0 | 1 | 5788.35 | — |
| [C4_encoding_10000_bpsk_reference_null](C4_encoding_10000_bpsk_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_encoding_10000_bpsk_soft_bpsk_header_null](C4_encoding_10000_bpsk_soft_bpsk_header_null/7446529.json) | assert / quick | pass | 0 | 1 | 5163.94 | — |
| [C4_encoding_10000_bpsk_soft_null](C4_encoding_10000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 5789.08 | — |
| [C4_encoding_10000_bpsk_walsh8_null](C4_encoding_10000_bpsk_walsh8_null/7446529.json) | assert / quick | pass | 0 | 1 | 5787.62 | — |
| [C4_encoding_10000_fsk4_guard4_null](C4_encoding_10000_fsk4_guard4_null/7446529.json) | assert / quick | pass | 0 | 1 | 65.4198 | — |
| [C4_encoding_10000_fsk4_guard8_null](C4_encoding_10000_fsk4_guard8_null/7446529.json) | assert / quick | pass | 0 | 1 | 28.0372 | — |
| [C4_encoding_10000_fsk8_guard4_null](C4_encoding_10000_fsk8_guard4_null/7446529.json) | assert / quick | pass | 0 | 1 | 102.205 | — |
| [C4_encoding_10000_fsk8_guard8_null](C4_encoding_10000_fsk8_guard8_null/7446529.json) | assert / quick | pass | 0 | 1 | 66.9111 | — |
| [C4_encoding_10000_qpsk_reference_null](C4_encoding_10000_qpsk_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_encoding_10000_qpsk_soft_null](C4_encoding_10000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 11579.6 | — |
| [C4_encoding_24000_16qam_reference_null](C4_encoding_24000_16qam_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 55934.2 | — |
| [C4_encoding_24000_16qam_soft_null](C4_encoding_24000_16qam_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 55934.2 | — |
| [C4_encoding_24000_bpsk_bch_null](C4_encoding_24000_bpsk_bch_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981.1 | — |
| [C4_encoding_24000_bpsk_bpsk_header_reference_null](C4_encoding_24000_bpsk_bpsk_header_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 12535.1 | — |
| [C4_encoding_24000_bpsk_diversity_null](C4_encoding_24000_bpsk_diversity_null/7446529.json) | assert / quick | pass | 0 | 1 | 6990.51 | — |
| [C4_encoding_24000_bpsk_halfband_control_null](C4_encoding_24000_bpsk_halfband_control_null/7446529.json) | assert / quick | pass | 0 | 1 | 6990.51 | — |
| [C4_encoding_24000_bpsk_interleave2048_null](C4_encoding_24000_bpsk_interleave2048_null/7446529.json) | assert / quick | pass | 0 | 1 | 13969.5 | — |
| [C4_encoding_24000_bpsk_interleave256_null](C4_encoding_24000_bpsk_interleave256_null/7446529.json) | assert / quick | pass | 0 | 1 | 13971.4 | — |
| [C4_encoding_24000_bpsk_interleave32_null](C4_encoding_24000_bpsk_interleave32_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981 | — |
| [C4_encoding_24000_bpsk_k9_half_null](C4_encoding_24000_bpsk_k9_half_null/7446529.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_encoding_24000_bpsk_k9_third_null](C4_encoding_24000_bpsk_k9_third_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981.7 | — |
| [C4_encoding_24000_bpsk_reference_null](C4_encoding_24000_bpsk_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_encoding_24000_bpsk_soft_bpsk_header_null](C4_encoding_24000_bpsk_soft_bpsk_header_null/7446529.json) | assert / quick | pass | 0 | 1 | 12535.1 | — |
| [C4_encoding_24000_bpsk_soft_null](C4_encoding_24000_bpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 13982.5 | — |
| [C4_encoding_24000_bpsk_walsh8_null](C4_encoding_24000_bpsk_walsh8_null/7446529.json) | assert / quick | pass | 0 | 1 | 13981 | — |
| [C4_encoding_24000_fsk4_guard4_null](C4_encoding_24000_fsk4_guard4_null/7446529.json) | assert / quick | pass | 0 | 1 | 65.4198 | — |
| [C4_encoding_24000_fsk4_guard8_null](C4_encoding_24000_fsk4_guard8_null/7446529.json) | assert / quick | pass | 0 | 1 | 28.0372 | — |
| [C4_encoding_24000_fsk8_guard4_null](C4_encoding_24000_fsk8_guard4_null/7446529.json) | assert / quick | pass | 0 | 1 | 102.205 | — |
| [C4_encoding_24000_fsk8_guard8_null](C4_encoding_24000_fsk8_guard8_null/7446529.json) | assert / quick | pass | 0 | 1 | 66.9111 | — |
| [C4_encoding_24000_qpsk_reference_null](C4_encoding_24000_qpsk_reference_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |
| [C4_encoding_24000_qpsk_soft_null](C4_encoding_24000_qpsk_soft_null/7446529.json) | assert / quick | pass | 0 | 1 | 27966.4 | — |

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
| [D4_encoding_10000_16qam_reference_messages](D4_encoding_10000_16qam_reference_messages/7446529.json) | assert / quick | pass | — | — | 2349.33 | 51 |
| [D4_encoding_10000_16qam_soft_messages](D4_encoding_10000_16qam_soft_messages/7446529.json) | assert / quick | pass | — | — | 2349.33 | 51 |
| [D4_encoding_10000_bpsk_bch_messages](D4_encoding_10000_bpsk_bch_messages/7446529.json) | assert / quick | pass | — | — | 1128 | 80 |
| [D4_encoding_10000_bpsk_bpsk_header_reference_messages](D4_encoding_10000_bpsk_bpsk_header_reference_messages/7446529.json) | assert / quick | pass | — | — | 717.333 | 108 |
| [D4_encoding_10000_bpsk_diversity_messages](D4_encoding_10000_bpsk_diversity_messages/7446529.json) | assert / quick | pass | — | — | 394.667 | 168 |
| [D4_encoding_10000_bpsk_halfband_control_messages](D4_encoding_10000_bpsk_halfband_control_messages/7446529.json) | assert / quick | pass | — | — | 394.667 | 168 |
| [D4_encoding_10000_bpsk_interleave2048_messages](D4_encoding_10000_bpsk_interleave2048_messages/7446529.json) | assert / quick | pass | — | — | 74.6667 | 320 |
| [D4_encoding_10000_bpsk_interleave256_messages](D4_encoding_10000_bpsk_interleave256_messages/7446529.json) | assert / quick | pass | — | — | 637.333 | 118 |
| [D4_encoding_10000_bpsk_interleave32_messages](D4_encoding_10000_bpsk_interleave32_messages/7446529.json) | assert / quick | pass | — | — | 813.333 | 93 |
| [D4_encoding_10000_bpsk_k9_half_messages](D4_encoding_10000_bpsk_k9_half_messages/7446529.json) | assert / quick | pass | — | — | 813.333 | 92 |
| [D4_encoding_10000_bpsk_k9_third_messages](D4_encoding_10000_bpsk_k9_third_messages/7446529.json) | assert / quick | pass | — | — | 538.667 | 112 |
| [D4_encoding_10000_bpsk_reference_messages](D4_encoding_10000_bpsk_reference_messages/7446529.json) | assert / quick | pass | — | — | 813.333 | 89 |
| [D4_encoding_10000_bpsk_soft_bpsk_header_messages](D4_encoding_10000_bpsk_soft_bpsk_header_messages/7446529.json) | assert / quick | pass | — | — | 717.333 | 108 |
| [D4_encoding_10000_bpsk_soft_messages](D4_encoding_10000_bpsk_soft_messages/7446529.json) | assert / quick | pass | — | — | 813.333 | 89 |
| [D4_encoding_10000_bpsk_walsh8_messages](D4_encoding_10000_bpsk_walsh8_messages/7446529.json) | assert / quick | pass | — | — | 301.333 | 154 |
| [D4_encoding_10000_fsk4_guard4_messages](D4_encoding_10000_fsk4_guard4_messages/7446529.json) | assert / quick | pass | — | — | 10.4 | 4777 |
| [D4_encoding_10000_fsk4_guard8_messages](D4_encoding_10000_fsk4_guard8_messages/7446529.json) | assert / quick | pass | — | — | 6.4 | 7167 |
| [D4_encoding_10000_fsk8_guard4_messages](D4_encoding_10000_fsk8_guard4_messages/7446529.json) | assert / quick | pass | — | — | 20 | 2491 |
| [D4_encoding_10000_fsk8_guard8_messages](D4_encoding_10000_fsk8_guard8_messages/7446529.json) | assert / quick | pass | — | — | 12.5333 | 3739 |
| [D4_encoding_10000_qpsk_reference_messages](D4_encoding_10000_qpsk_reference_messages/7446529.json) | assert / quick | pass | — | — | 1632 | 69 |
| [D4_encoding_10000_qpsk_soft_messages](D4_encoding_10000_qpsk_soft_messages/7446529.json) | assert / quick | pass | — | — | 1632 | 69 |
| [D4_encoding_24000_16qam_reference_messages](D4_encoding_24000_16qam_reference_messages/7446529.json) | assert / quick | pass | — | — | 2597.33 | 21 |
| [D4_encoding_24000_16qam_soft_messages](D4_encoding_24000_16qam_soft_messages/7446529.json) | assert / quick | pass | — | — | 2597.33 | 21 |
| [D4_encoding_24000_bpsk_bch_messages](D4_encoding_24000_bpsk_bch_messages/7446529.json) | assert / quick | pass | — | — | 2450.67 | 30 |
| [D4_encoding_24000_bpsk_bpsk_header_reference_messages](D4_encoding_24000_bpsk_bpsk_header_reference_messages/7446529.json) | assert / quick | pass | — | — | 1762.67 | 51 |
| [D4_encoding_24000_bpsk_diversity_messages](D4_encoding_24000_bpsk_diversity_messages/7446529.json) | assert / quick | pass | — | — | 973.333 | 74 |
| [D4_encoding_24000_bpsk_halfband_control_messages](D4_encoding_24000_bpsk_halfband_control_messages/7446529.json) | assert / quick | pass | — | — | 973.333 | 74 |
| [D4_encoding_24000_bpsk_interleave2048_messages](D4_encoding_24000_bpsk_interleave2048_messages/7446529.json) | assert / quick | pass | — | — | 186.667 | 198 |
| [D4_encoding_24000_bpsk_interleave256_messages](D4_encoding_24000_bpsk_interleave256_messages/7446529.json) | assert / quick | pass | — | — | 1552 | 55 |
| [D4_encoding_24000_bpsk_interleave32_messages](D4_encoding_24000_bpsk_interleave32_messages/7446529.json) | assert / quick | pass | — | — | 1970.67 | 43 |
| [D4_encoding_24000_bpsk_k9_half_messages](D4_encoding_24000_bpsk_k9_half_messages/7446529.json) | assert / quick | pass | — | — | 1970.67 | 44 |
| [D4_encoding_24000_bpsk_k9_third_messages](D4_encoding_24000_bpsk_k9_third_messages/7446529.json) | assert / quick | pass | — | — | 1306.67 | 53 |
| [D4_encoding_24000_bpsk_reference_messages](D4_encoding_24000_bpsk_reference_messages/7446529.json) | assert / quick | pass | — | — | 1970.67 | 43 |
| [D4_encoding_24000_bpsk_soft_bpsk_header_messages](D4_encoding_24000_bpsk_soft_bpsk_header_messages/7446529.json) | assert / quick | pass | — | — | 1762.67 | 51 |
| [D4_encoding_24000_bpsk_soft_messages](D4_encoding_24000_bpsk_soft_messages/7446529.json) | assert / quick | pass | — | — | 1970.67 | 43 |
| [D4_encoding_24000_bpsk_walsh8_messages](D4_encoding_24000_bpsk_walsh8_messages/7446529.json) | assert / quick | pass | — | — | 736 | 82 |
| [D4_encoding_24000_fsk4_guard4_messages](D4_encoding_24000_fsk4_guard4_messages/7446529.json) | assert / quick | pass | — | — | 10.4 | 4777 |
| [D4_encoding_24000_fsk4_guard8_messages](D4_encoding_24000_fsk4_guard8_messages/7446529.json) | assert / quick | pass | — | — | 6.4 | 7167 |
| [D4_encoding_24000_fsk8_guard4_messages](D4_encoding_24000_fsk8_guard4_messages/7446529.json) | assert / quick | pass | — | — | 20 | 2491 |
| [D4_encoding_24000_fsk8_guard8_messages](D4_encoding_24000_fsk8_guard8_messages/7446529.json) | assert / quick | pass | — | — | 12.5333 | 3739 |
| [D4_encoding_24000_qpsk_reference_messages](D4_encoding_24000_qpsk_reference_messages/7446529.json) | assert / quick | pass | — | — | 2450.67 | 26 |
| [D4_encoding_24000_qpsk_soft_messages](D4_encoding_24000_qpsk_soft_messages/7446529.json) | assert / quick | pass | — | — | 2450.67 | 26 |

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
| [E2_encoding_followup_10000_16qam_reference_high_lat_disturbed](E2_encoding_followup_10000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_reference_high_lat_disturbed](E2_encoding_followup_10000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_reference_high_lat_disturbed](E2_encoding_followup_10000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_reference_high_lat_moderate](E2_encoding_followup_10000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 21.5467 | 19 |
| [E2_encoding_followup_10000_16qam_reference_high_lat_moderate](E2_encoding_followup_10000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 16.64 | 19 |
| [E2_encoding_followup_10000_16qam_reference_high_lat_moderate](E2_encoding_followup_10000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 16.8533 | 19 |
| [E2_encoding_followup_10000_16qam_reference_high_lat_quiet](E2_encoding_followup_10000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2140.93 | 81 |
| [E2_encoding_followup_10000_16qam_reference_high_lat_quiet](E2_encoding_followup_10000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2141.47 | 81 |
| [E2_encoding_followup_10000_16qam_reference_high_lat_quiet](E2_encoding_followup_10000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2154.16 | 81 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_disturbed](E2_encoding_followup_10000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_soft_high_lat_disturbed](E2_encoding_followup_10000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_soft_high_lat_disturbed](E2_encoding_followup_10000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_16qam_soft_high_lat_moderate](E2_encoding_followup_10000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 39.04 | 19 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_moderate](E2_encoding_followup_10000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 32.48 | 19 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_moderate](E2_encoding_followup_10000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 30.9333 | 19 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_quiet](E2_encoding_followup_10000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2159.39 | 81 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_quiet](E2_encoding_followup_10000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2159.71 | 81 |
| [E2_encoding_followup_10000_16qam_soft_high_lat_quiet](E2_encoding_followup_10000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2170.48 | 81 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.32 | 39 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.96 | 48 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_moderate](E2_encoding_followup_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 165.973 | 122 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_moderate](E2_encoding_followup_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 174.693 | 120 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_moderate](E2_encoding_followup_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 158 | 122 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_quiet](E2_encoding_followup_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1045.81 | 111 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_quiet](E2_encoding_followup_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1046.13 | 111 |
| [E2_encoding_followup_10000_bpsk_bch_high_lat_quiet](E2_encoding_followup_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1057.87 | 111 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 109.867 | 151 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 105.28 | 150 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 103.973 | 151 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 689.333 | 140 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 689.653 | 140 |
| [E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 694.88 | 140 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.94667 | 229 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 4.48 | 96 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 6.50667 | 225 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 359.333 | 222 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 362.32 | 222 |
| [E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 367.867 | 222 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.14667 | 95 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 3.73333 | 96 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 5.12 | 95 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 378 | 222 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 380.347 | 222 |
| [E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 378.64 | 222 |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 72.32 | 363 |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 72.96 | 364 |
| [E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 75.7333 | 363 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.32 | 82 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 86 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 66.9333 | 160 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 65.92 | 160 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 61.6267 | 159 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 612.133 | 148 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 612.347 | 148 |
| [E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 621.2 | 148 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 52 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 117.92 | 134 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 124.08 | 134 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 113.093 | 134 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 756.56 | 122 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 756.987 | 122 |
| [E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 766.053 | 122 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.64 | 52 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 120.507 | 133 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 122.773 | 133 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 114.747 | 134 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 755.173 | 122 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 756.773 | 122 |
| [E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 764.88 | 122 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 64.1067 | 155 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 63.6 | 168 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 61.5467 | 154 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 502.32 | 143 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 503.067 | 143 |
| [E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 509.787 | 143 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.64 | 52 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 111.44 | 130 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 118.08 | 130 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_moderate](E2_encoding_followup_10000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 102.987 | 131 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 756.667 | 119 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 756.667 | 119 |
| [E2_encoding_followup_10000_bpsk_reference_high_lat_quiet](E2_encoding_followup_10000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 766.16 | 119 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0.32 | 64 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 117.653 | 151 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 112.747 | 150 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 111.44 | 151 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 689.333 | 140 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 689.76 | 140 |
| [E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 694.88 | 140 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.96 | 52 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 118.907 | 130 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 130.453 | 130 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_moderate](E2_encoding_followup_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 110.24 | 130 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 756.773 | 119 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 756.667 | 119 |
| [E2_encoding_followup_10000_bpsk_soft_high_lat_quiet](E2_encoding_followup_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 766.053 | 119 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 19.7067 | 197 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 18.9867 | 197 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 16.96 | 196 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 280.827 | 185 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 280.933 | 185 |
| [E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 285.307 | 185 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.62667 | 4783 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 4.37333 | 4785 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.73333 | 4782 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 11.3867 | 4784 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 11.3867 | 4784 |
| [E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 11.3867 | 4784 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.66667 | 7172 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 3.2 | 7174 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.56 | 7172 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 7.57333 | 7172 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 7.57333 | 7172 |
| [E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 7.57333 | 7172 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 8.64 | 2494 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 8.72 | 2494 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 7.36 | 2494 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 21.52 | 2493 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 21.52 | 2493 |
| [E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 20.9867 | 2493 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 5.65333 | 3742 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 6.29333 | 3742 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 4.58667 | 3742 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 13.7333 | 3740 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 14.3733 | 3740 |
| [E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 14.16 | 3740 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_moderate](E2_encoding_followup_10000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 104.187 | 108 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_moderate](E2_encoding_followup_10000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 103.893 | 111 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_moderate](E2_encoding_followup_10000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 86.4 | 109 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_quiet](E2_encoding_followup_10000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1515.28 | 99 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_quiet](E2_encoding_followup_10000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1520.72 | 99 |
| [E2_encoding_followup_10000_qpsk_reference_high_lat_quiet](E2_encoding_followup_10000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1535.44 | 99 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_moderate](E2_encoding_followup_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 139.173 | 107 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_moderate](E2_encoding_followup_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 145.12 | 110 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_moderate](E2_encoding_followup_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 117.84 | 108 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_quiet](E2_encoding_followup_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1516.35 | 99 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_quiet](E2_encoding_followup_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1521.36 | 99 |
| [E2_encoding_followup_10000_qpsk_soft_high_lat_quiet](E2_encoding_followup_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1535.87 | 99 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_disturbed](E2_encoding_followup_24000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_16qam_reference_high_lat_disturbed](E2_encoding_followup_24000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 1.28 | 20 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_disturbed](E2_encoding_followup_24000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_16qam_reference_high_lat_moderate](E2_encoding_followup_24000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 191.573 | 46 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_moderate](E2_encoding_followup_24000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 185.413 | 46 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_moderate](E2_encoding_followup_24000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 174.133 | 46 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_quiet](E2_encoding_followup_24000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2344.93 | 38 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_quiet](E2_encoding_followup_24000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2327.39 | 38 |
| [E2_encoding_followup_24000_16qam_reference_high_lat_quiet](E2_encoding_followup_24000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2343.65 | 38 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_disturbed](E2_encoding_followup_24000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 1.6 | 15 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_disturbed](E2_encoding_followup_24000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 1.6 | 21 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_disturbed](E2_encoding_followup_24000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0.32 | 13 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_moderate](E2_encoding_followup_24000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 261.12 | 46 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_moderate](E2_encoding_followup_24000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 255.173 | 46 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_moderate](E2_encoding_followup_24000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 243.84 | 46 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_quiet](E2_encoding_followup_24000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2380.83 | 38 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_quiet](E2_encoding_followup_24000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2373.04 | 38 |
| [E2_encoding_followup_24000_16qam_soft_high_lat_quiet](E2_encoding_followup_24000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2382.45 | 38 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 44.08 | 88 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 49.44 | 89 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 39.04 | 36 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_moderate](E2_encoding_followup_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1219.79 | 58 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_moderate](E2_encoding_followup_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1194.32 | 58 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_moderate](E2_encoding_followup_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1179.68 | 58 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_quiet](E2_encoding_followup_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2314.88 | 48 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_quiet](E2_encoding_followup_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2316.8 | 48 |
| [E2_encoding_followup_24000_bpsk_bch_high_lat_quiet](E2_encoding_followup_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2318.08 | 48 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 32.96 | 108 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 35.2 | 118 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 31.04 | 115 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 811.733 | 80 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 816.427 | 80 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 795.253 | 80 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1641.63 | 68 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1643.55 | 68 |
| [E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1639.39 | 68 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.64 | 56 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 1.6 | 53 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.48 | 53 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 229.36 | 114 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 230.613 | 114 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate](E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 217.52 | 114 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 900.8 | 102 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 907.2 | 102 |
| [E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet](E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 898.987 | 102 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0.96 | 56 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 1.6 | 56 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 2.56 | 50 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 213.36 | 114 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 209.067 | 114 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 194.64 | 114 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 919.36 | 102 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 918.08 | 102 |
| [E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 918.613 | 102 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 25.7333 | 168 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 24.5333 | 168 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 22.0533 | 168 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 181.12 | 156 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 181.12 | 156 |
| [E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 181.76 | 156 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 23.44 | 116 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 22.56 | 114 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 20.24 | 115 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 720.693 | 83 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 713.733 | 83 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 698.053 | 83 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1460.85 | 71 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1460 | 71 |
| [E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1462.45 | 71 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 27.84 | 106 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 38.64 | 110 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 32.16 | 105 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 954.56 | 72 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 941.493 | 72 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 918.507 | 72 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1801.25 | 61 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1799.55 | 61 |
| [E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1802.75 | 61 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 27.2 | 111 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 36.32 | 109 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 35.12 | 103 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 954.133 | 72 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 938.507 | 72 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 912.987 | 72 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1796.45 | 60 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1797.2 | 60 |
| [E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1801.47 | 60 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 14.16 | 111 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 17.92 | 111 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 12.64 | 113 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 607.92 | 81 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 586.72 | 81 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 576.907 | 81 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1199.25 | 69 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1200.11 | 69 |
| [E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1202.13 | 69 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 28 | 110 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 32.8 | 109 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 23.76 | 100 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 939.493 | 71 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 918.587 | 71 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_moderate](E2_encoding_followup_24000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 897.173 | 71 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1798.8 | 59 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1799.01 | 59 |
| [E2_encoding_followup_24000_bpsk_reference_high_lat_quiet](E2_encoding_followup_24000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1803.28 | 59 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 37.12 | 110 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 36.48 | 118 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 32.96 | 115 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 833.813 | 80 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 834.347 | 80 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 811.013 | 80 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1641.63 | 68 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1643.55 | 68 |
| [E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1639.39 | 68 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 32.16 | 110 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 36.96 | 109 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 29.12 | 108 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 962.827 | 71 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 939.44 | 71 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_moderate](E2_encoding_followup_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 917.893 | 71 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1798.8 | 59 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1798.91 | 59 |
| [E2_encoding_followup_24000_bpsk_soft_high_lat_quiet](E2_encoding_followup_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1803.39 | 59 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 3.12 | 136 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 3.84 | 123 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 4.4 | 131 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 287.12 | 99 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 279.173 | 99 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 273.067 | 99 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 672.48 | 87 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 673.227 | 87 |
| [E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 673.013 | 87 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.49333 | 4784 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 4.66667 | 4786 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.52 | 4786 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 11.1733 | 4784 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 11.3867 | 4784 |
| [E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 11.1733 | 4784 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.56 | 7174 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 3.52 | 7173 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.52 | 7173 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 7.57333 | 7173 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 7.57333 | 7171 |
| [E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 7.46667 | 7172 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 7.57333 | 2494 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 10.2133 | 2494 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 7.36 | 2494 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 21.52 | 2492 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 21.52 | 2493 |
| [E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 21.52 | 2492 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 6.82667 | 3742 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 6.37333 | 3742 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate](E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 5.97333 | 3742 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 14.3733 | 3741 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 14.3733 | 3741 |
| [E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet](E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 14.3733 | 3741 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 9.68 | 31 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 14.32 | 85 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed](E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 10.88 | 30 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_moderate](E2_encoding_followup_24000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 831.653 | 54 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_moderate](E2_encoding_followup_24000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 833.707 | 54 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_moderate](E2_encoding_followup_24000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 798.907 | 54 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_quiet](E2_encoding_followup_24000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2429.47 | 42 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_quiet](E2_encoding_followup_24000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2428.93 | 42 |
| [E2_encoding_followup_24000_qpsk_reference_high_lat_quiet](E2_encoding_followup_24000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2429.25 | 42 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 18.56 | 31 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 26.08 | 85 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed](E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 17.28 | 30 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_moderate](E2_encoding_followup_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 991.787 | 54 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_moderate](E2_encoding_followup_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 980 | 54 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_moderate](E2_encoding_followup_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 945.92 | 54 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_quiet](E2_encoding_followup_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2429.57 | 42 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_quiet](E2_encoding_followup_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2429.36 | 42 |
| [E2_encoding_followup_24000_qpsk_soft_high_lat_quiet](E2_encoding_followup_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2429.57 | 42 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_disturbed](E2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_reference_high_lat_disturbed](E2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_reference_high_lat_disturbed](E2_encoding_screen_10000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_reference_high_lat_moderate](E2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.2 | 16 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_moderate](E2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 12.8 | 19 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_moderate](E2_encoding_screen_10000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 48 | 17 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_quiet](E2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2068 | 80 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_quiet](E2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2061.6 | 81 |
| [E2_encoding_screen_10000_16qam_reference_high_lat_quiet](E2_encoding_screen_10000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2122.4 | 80 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_disturbed](E2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_soft_high_lat_disturbed](E2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_soft_high_lat_disturbed](E2_encoding_screen_10000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_16qam_soft_high_lat_moderate](E2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 12.8 | 16 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_moderate](E2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 27.2 | 19 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_moderate](E2_encoding_screen_10000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 64 | 17 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_quiet](E2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2080.8 | 80 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_quiet](E2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2068 | 81 |
| [E2_encoding_screen_10000_16qam_soft_high_lat_quiet](E2_encoding_screen_10000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2148 | 80 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_moderate](E2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 179.2 | 102 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_moderate](E2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 136.8 | 116 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_moderate](E2_encoding_screen_10000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 212 | 120 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_quiet](E2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1016 | 111 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_quiet](E2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 961.6 | 110 |
| [E2_encoding_screen_10000_bpsk_bch_high_lat_quiet](E2_encoding_screen_10000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1038.4 | 111 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 121.6 | 149 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 76.8 | 147 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 149.6 | 148 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 683.2 | 139 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 683.2 | 140 |
| [E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 664 | 139 |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 3.2 | 94 |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 6.4 | 95 |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 360.8 | 222 |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 341.6 | 222 |
| [E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 341.6 | 221 |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 8 | 95 |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.2 | 84 |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 380 | 221 |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 380 | 222 |
| [E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 360.8 | 221 |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 67.2 | 363 |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 54.4 | 364 |
| [E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 73.6 | 363 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 68.8 | 154 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 35.2 | 84 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 85.6 | 154 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 584.8 | 148 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 546.4 | 147 |
| [E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 604 | 148 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 107.2 | 129 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 109.6 | 59 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 135.2 | 133 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 732 | 120 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 690.4 | 121 |
| [E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 751.2 | 120 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 101.6 | 130 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 96 | 130 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 143.2 | 130 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 728.8 | 122 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 690.4 | 121 |
| [E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 751.2 | 122 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 64 | 148 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 55.2 | 168 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 76.8 | 153 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 484 | 142 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 455.2 | 143 |
| [E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 500 | 142 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 101.6 | 127 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 118.4 | 121 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_moderate](E2_encoding_screen_10000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 132.8 | 128 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 732 | 119 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 690.4 | 119 |
| [E2_encoding_screen_10000_bpsk_reference_high_lat_quiet](E2_encoding_screen_10000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 751.2 | 119 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 134.4 | 149 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 80 | 147 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 156 | 148 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 683.2 | 139 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 683.2 | 140 |
| [E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 664 | 139 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 111.2 | 127 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 121.6 | 121 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_moderate](E2_encoding_screen_10000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 142.4 | 128 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 732 | 119 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 690.4 | 119 |
| [E2_encoding_screen_10000_bpsk_soft_high_lat_quiet](E2_encoding_screen_10000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 751.2 | 119 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 15.2 | 194 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 12.8 | 194 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 22.4 | 196 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 271.2 | 184 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 248.8 | 184 |
| [E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 280.8 | 185 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.2 | 3584 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 6.4 | 4780 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.13333 | 3583 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 10.4 | 4778 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 10.4 | 4778 |
| [E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 10.4 | 4777 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1.06667 | 5364 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 3.2 | 7167 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.13333 | 5373 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 6.4 | 7168 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 6.4 | 7167 |
| [E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 6.4 | 7168 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 6.4 | 1649 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 5.06667 | 2483 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.13333 | 1650 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 20 | 2491 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 20 | 2493 |
| [E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 20 | 2491 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 8.53333 | 3740 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 6.4 | 3741 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 2.13333 | 2464 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 12.5333 | 3739 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 12.5333 | 3739 |
| [E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 12.5333 | 3739 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_moderate](E2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 85.6 | 33 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_moderate](E2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 57.6 | 35 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_moderate](E2_encoding_screen_10000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 137.6 | 103 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_quiet](E2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1471.2 | 100 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_quiet](E2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1397.6 | 99 |
| [E2_encoding_screen_10000_qpsk_reference_high_lat_quiet](E2_encoding_screen_10000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1506.4 | 100 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_moderate](E2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 124 | 34 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_moderate](E2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 116.8 | 37 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_moderate](E2_encoding_screen_10000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 175.2 | 108 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_quiet](E2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1471.2 | 100 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_quiet](E2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1397.6 | 99 |
| [E2_encoding_screen_10000_qpsk_soft_high_lat_quiet](E2_encoding_screen_10000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1506.4 | 100 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_disturbed](E2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_16qam_reference_high_lat_disturbed](E2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 3.2 | 14 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_disturbed](E2_encoding_screen_24000_16qam_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_16qam_reference_high_lat_moderate](E2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 227.2 | 12 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_moderate](E2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 237.6 | 46 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_moderate](E2_encoding_screen_24000_16qam_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 180.8 | 46 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_quiet](E2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2239.2 | 38 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_quiet](E2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2250.4 | 38 |
| [E2_encoding_screen_24000_16qam_reference_high_lat_quiet](E2_encoding_screen_24000_16qam_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2232.8 | 38 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_disturbed](E2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_16qam_soft_high_lat_disturbed](E2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 3.2 | 14 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_disturbed](E2_encoding_screen_24000_16qam_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_16qam_soft_high_lat_moderate](E2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 297.6 | 12 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_moderate](E2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 304.8 | 46 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_moderate](E2_encoding_screen_24000_16qam_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 227.2 | 46 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_quiet](E2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2320.8 | 38 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_quiet](E2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2272.8 | 38 |
| [E2_encoding_screen_24000_16qam_soft_high_lat_quiet](E2_encoding_screen_24000_16qam_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2318.4 | 38 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 47.2 | 34 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 40 | 30 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 60.8 | 34 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_moderate](E2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1230.4 | 58 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_moderate](E2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1128.8 | 58 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_moderate](E2_encoding_screen_24000_bpsk_bch_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1032 | 58 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_quiet](E2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2256 | 47 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_quiet](E2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2256 | 47 |
| [E2_encoding_screen_24000_bpsk_bch_high_lat_quiet](E2_encoding_screen_24000_bpsk_bch_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2224 | 48 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 41.6 | 38 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 41.6 | 109 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 25.6 | 32 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 720 | 80 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 790.4 | 79 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 747.2 | 79 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1597.6 | 67 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1597.6 | 68 |
| [E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1600.8 | 68 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 3.2 | 53 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed](E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 5.6 | 45 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 288.8 | 114 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 169.6 | 112 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate](E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 224.8 | 114 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 860.8 | 102 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 902.4 | 102 |
| [E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet](E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 902.4 | 102 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 3.2 | 43 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 295.2 | 111 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 172.8 | 111 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 207.2 | 111 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 883.2 | 102 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 902.4 | 102 |
| [E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet](E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 902.4 | 102 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 26.4 | 168 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 25.6 | 167 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 15.2 | 165 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 176 | 156 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 176 | 156 |
| [E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 163.2 | 156 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 26.4 | 116 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 14.4 | 52 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 45.6 | 114 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 728 | 83 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 714.4 | 82 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 599.2 | 83 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1419.2 | 71 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1419.2 | 71 |
| [E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1409.6 | 71 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 38.4 | 42 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 31.2 | 35 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed](E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 24 | 35 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 979.2 | 72 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 961.6 | 72 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate](E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 803.2 | 72 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1762.4 | 60 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1762.4 | 61 |
| [E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet](E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1724 | 60 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 25.6 | 37 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 43.2 | 34 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 53.6 | 37 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 979.2 | 72 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 952 | 72 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 804 | 69 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1759.2 | 61 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1762.4 | 61 |
| [E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1720.8 | 61 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 16.8 | 49 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 9.6 | 44 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed](E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 11.2 | 39 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 666.4 | 81 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 555.2 | 81 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate](E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 465.6 | 81 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1174.4 | 69 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1174.4 | 69 |
| [E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet](E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1171.2 | 69 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 27.2 | 40 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 30.4 | 33 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 29.6 | 34 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1010.4 | 71 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 869.6 | 71 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_moderate](E2_encoding_screen_24000_bpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 752 | 68 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1762.4 | 59 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1762.4 | 59 |
| [E2_encoding_screen_24000_bpsk_reference_high_lat_quiet](E2_encoding_screen_24000_bpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1733.6 | 59 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 44.8 | 38 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 48 | 109 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 28.8 | 34 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 736 | 80 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 806.4 | 79 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 765.6 | 79 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1597.6 | 67 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1597.6 | 68 |
| [E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1600.8 | 68 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 33.6 | 40 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 40 | 33 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 32 | 34 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1032 | 71 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 903.2 | 71 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_moderate](E2_encoding_screen_24000_bpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 768.8 | 68 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 1762.4 | 59 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 1762.4 | 59 |
| [E2_encoding_screen_24000_bpsk_soft_high_lat_quiet](E2_encoding_screen_24000_bpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 1733.6 | 59 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 5.6 | 52 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 9.6 | 61 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed](E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 12 | 126 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 306.4 | 98 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 282.4 | 98 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate](E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 224 | 98 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 657.6 | 89 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 657.6 | 90 |
| [E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet](E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 635.2 | 89 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 5.06667 | 3585 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 5.06667 | 3585 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 1.06667 | 3583 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 10.4 | 4778 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 10.4 | 4778 |
| [E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 10.4 | 4777 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 3.2 | 5373 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 2.13333 | 5366 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.2 | 5374 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 6.4 | 7168 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 6.4 | 7167 |
| [E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 6.4 | 7168 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 5.33333 | 2494 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 12.5333 | 2491 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 5.33333 | 2494 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 20 | 2491 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 20 | 2492 |
| [E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 20 | 2492 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed](E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 0 | — |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 2.13333 | 3727 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 5.06667 | 3742 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate](E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 3.2 | 3740 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 12.5333 | 3739 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 12.5333 | 3741 |
| [E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet](E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 12.5333 | 3739 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 10.4 | 23 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 12 | 25 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed](E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 6.4 | 20 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_moderate](E2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 978.4 | 54 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_moderate](E2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 857.6 | 54 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_moderate](E2_encoding_screen_24000_qpsk_reference_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 591.2 | 53 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_quiet](E2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2352.8 | 42 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_quiet](E2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2352.8 | 42 |
| [E2_encoding_screen_24000_qpsk_reference_high_lat_quiet](E2_encoding_screen_24000_qpsk_reference_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2356 | 42 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446529.json) | characterize / full | characterized | — | — | 25.6 | 24 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446530.json) | characterize / full | characterized | — | — | 27.2 | 25 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed](E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed/7446531.json) | characterize / full | characterized | — | — | 6.4 | 20 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_moderate](E2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446529.json) | characterize / full | characterized | — | — | 1136 | 54 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_moderate](E2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446530.json) | characterize / full | characterized | — | — | 1012.8 | 54 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_moderate](E2_encoding_screen_24000_qpsk_soft_high_lat_moderate/7446531.json) | characterize / full | characterized | — | — | 678.4 | 53 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_quiet](E2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446529.json) | characterize / full | characterized | — | — | 2352.8 | 42 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_quiet](E2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446530.json) | characterize / full | characterized | — | — | 2352.8 | 42 |
| [E2_encoding_screen_24000_qpsk_soft_high_lat_quiet](E2_encoding_screen_24000_qpsk_soft_high_lat_quiet/7446531.json) | characterize / full | characterized | — | — | 2356 | 42 |

### Simulated channel E2 local metric definitions

| Preset | Lock uptime | Delivery-window usable-time proxy | Goodput bit/s | STAC exact comparison |
| --- | --- | --- | --- | --- |
| E2_encoding_followup_10000_16qam_reference_high_lat_disturbed | 0.00532 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_disturbed | 0.0037099999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_disturbed | 0.005560000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_moderate | 0.07567333333333334 | 0.2633333333333333 | 21.546666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_moderate | 0.07265333333333333 | 0.22 | 16.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_moderate | 0.07017666666666666 | 0.22 | 16.85333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_quiet | 0.6667033333333333 | 1.0 | 2140.9333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_quiet | 0.6664399999999999 | 1.0 | 2141.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_reference_high_lat_quiet | 0.66939 | 1.0 | 2154.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_disturbed | 0.00817 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_disturbed | 0.00445 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_disturbed | 0.0067800000000000004 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_moderate | 0.07711333333333334 | 0.38666666666666666 | 39.04 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_moderate | 0.07490999999999999 | 0.36333333333333334 | 32.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_moderate | 0.07221666666666667 | 0.36333333333333334 | 30.933333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_quiet | 0.6667033333333333 | 1.0 | 2159.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_quiet | 0.6664399999999999 | 1.0 | 2159.7066666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_16qam_soft_high_lat_quiet | 0.66939 | 1.0 | 2170.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed | 0.0218 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed | 0.014610000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_disturbed | 0.01895 | 0.02 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_moderate | 0.27013333333333334 | 0.8433333333333334 | 165.97333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_moderate | 0.27465 | 0.8533333333333334 | 174.69333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_moderate | 0.2580033333333333 | 0.84 | 158.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_quiet | 0.6770633333333334 | 1.0 | 1045.8133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_quiet | 0.6776 | 1.0 | 1046.1333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bch_high_lat_quiet | 0.6836533333333333 | 1.0 | 1057.8666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.02092 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.02205 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.02727 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.25464333333333333 | 0.7966666666666666 | 109.86666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.25509666666666664 | 0.8033333333333333 | 105.28 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.25304333333333334 | 0.8166666666666667 | 103.97333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6161866666666667 | 1.0 | 689.3333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6163833333333333 | 1.0 | 689.6533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6201333333333333 | 1.0 | 694.88 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate | 0.05592 | 0.07666666666666666 | 3.9466666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate | 0.05904333333333334 | 0.08333333333333333 | 4.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_moderate | 0.061783333333333336 | 0.12666666666666668 | 6.506666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet | 0.6466766666666666 | 1.0 | 359.3333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet | 0.64944 | 0.9933333333333333 | 362.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_diversity_high_lat_quiet | 0.6586133333333334 | 1.0 | 367.8666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate | 0.04491333333333333 | 0.07333333333333333 | 3.1466666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate | 0.05108333333333333 | 0.07666666666666666 | 3.7333333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_moderate | 0.043783333333333334 | 0.10333333333333333 | 5.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet | 0.6729366666666666 | 1.0 | 378.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet | 0.67627 | 1.0 | 380.3466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_halfband_control_high_lat_quiet | 0.6750033333333334 | 1.0 | 378.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed | 0.02341 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed | 0.0152 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_disturbed | 0.018009999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate | 0.2686266666666666 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate | 0.27042666666666665 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_moderate | 0.2629933333333333 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet | 0.6766266666666667 | 0.98 | 72.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet | 0.6776 | 0.99 | 72.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave2048_high_lat_quiet | 0.6836666666666666 | 0.9966666666666667 | 75.73333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed | 0.022629999999999997 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed | 0.0161 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_disturbed | 0.01594 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate | 0.2685366666666667 | 0.67 | 66.93333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate | 0.26911666666666667 | 0.6833333333333333 | 65.92 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_moderate | 0.25386000000000003 | 0.6533333333333333 | 61.626666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet | 0.6771333333333333 | 1.0 | 612.1333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet | 0.6771733333333333 | 1.0 | 612.3466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave256_high_lat_quiet | 0.6836666666666666 | 1.0 | 621.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed | 0.02561 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed | 0.01669 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_disturbed | 0.01843 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate | 0.26662 | 0.8133333333333334 | 117.92 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate | 0.2721133333333333 | 0.83 | 124.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_moderate | 0.2532566666666667 | 0.8533333333333334 | 113.09333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet | 0.6771333333333333 | 1.0 | 756.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet | 0.6776 | 1.0 | 756.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_interleave32_high_lat_quiet | 0.6836666666666666 | 1.0 | 766.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed | 0.0206 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed | 0.01451 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_disturbed | 0.01771 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate | 0.26837333333333335 | 0.81 | 120.50666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate | 0.27924666666666664 | 0.8433333333333334 | 122.77333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_moderate | 0.25695666666666667 | 0.84 | 114.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet | 0.6762166666666667 | 1.0 | 755.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet | 0.6776 | 1.0 | 756.7733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_half_high_lat_quiet | 0.6828333333333333 | 1.0 | 764.88 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed | 0.02096 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed | 0.015969999999999998 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_disturbed | 0.017920000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate | 0.26923 | 0.72 | 64.10666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate | 0.2708466666666667 | 0.7233333333333334 | 63.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_moderate | 0.26130666666666663 | 0.6933333333333334 | 61.54666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet | 0.67698 | 1.0 | 502.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet | 0.6776 | 1.0 | 503.06666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_k9_third_high_lat_quiet | 0.6836666666666666 | 1.0 | 509.7866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed | 0.01631 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed | 0.012430000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_disturbed | 0.01533 | 0.01 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_moderate | 0.26461 | 0.8133333333333334 | 111.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_moderate | 0.27253666666666665 | 0.8366666666666667 | 118.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_moderate | 0.2503933333333333 | 0.8366666666666667 | 102.98666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_quiet | 0.6771333333333333 | 1.0 | 756.6666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_quiet | 0.6776 | 1.0 | 756.6666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_reference_high_lat_quiet | 0.6836666666666666 | 1.0 | 766.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.02045 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.02236 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.02766 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.2569766666666667 | 0.8233333333333334 | 117.65333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.25836333333333333 | 0.81 | 112.74666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.25705333333333336 | 0.8366666666666667 | 111.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6161866666666667 | 1.0 | 689.3333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6163833333333333 | 1.0 | 689.76 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6201333333333333 | 1.0 | 694.88 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed | 0.0215 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed | 0.01652 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_disturbed | 0.01796 | 0.02 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_moderate | 0.27199666666666666 | 0.8266666666666667 | 118.90666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_moderate | 0.28069333333333335 | 0.8533333333333334 | 130.45333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_moderate | 0.2543333333333333 | 0.84 | 110.24 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_quiet | 0.6771333333333333 | 1.0 | 756.7733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_quiet | 0.6776 | 1.0 | 756.6666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_soft_high_lat_quiet | 0.6836666666666666 | 1.0 | 766.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed | 0.02408 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed | 0.01625 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_disturbed | 0.01974 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate | 0.29861333333333334 | 0.41333333333333333 | 19.706666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate | 0.30105333333333334 | 0.39666666666666667 | 18.986666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_moderate | 0.28348999999999996 | 0.3433333333333333 | 16.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet | 0.6771333333333333 | 1.0 | 280.82666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet | 0.6776 | 1.0 | 280.93333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_bpsk_walsh8_high_lat_quiet | 0.68326 | 1.0 | 285.3066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate | 0.23552 | 0.11333333333333333 | 3.6266666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate | 0.2372266666666667 | 0.13666666666666666 | 4.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_moderate | 0.23040000000000002 | 0.11666666666666667 | 3.7333333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet | 0.29866666666666664 | 0.3566666666666667 | 11.386666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet | 0.29866666666666664 | 0.3566666666666667 | 11.386666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard4_high_lat_quiet | 0.29866666666666664 | 0.3566666666666667 | 11.386666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_disturbed | 0.00768 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate | 0.2340033333333333 | 0.08333333333333333 | 2.6666666666666665 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate | 0.25088 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_moderate | 0.23655666666666667 | 0.08 | 2.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet | 0.29800333333333334 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet | 0.2980066666666667 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk4_guard8_high_lat_quiet | 0.29800333333333334 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed | 0.00512 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate | 0.2781866666666667 | 0.27 | 8.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate | 0.29013333333333335 | 0.2733333333333333 | 8.72 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_moderate | 0.2730666666666667 | 0.23 | 7.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6733333333333333 | 21.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6733333333333333 | 21.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard4_high_lat_quiet | 0.37205333333333335 | 0.6566666666666666 | 20.986666666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed | 0.00768 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_disturbed | 0.01536 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate | 0.29952 | 0.17666666666666667 | 5.653333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate | 0.28416 | 0.19666666666666666 | 6.293333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_moderate | 0.27136 | 0.14333333333333334 | 4.586666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet | 0.36864 | 0.43 | 13.733333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet | 0.37632 | 0.45 | 14.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_fsk8_guard8_high_lat_quiet | 0.37376 | 0.44333333333333336 | 14.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed | 0.00781 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed | 0.00846 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_disturbed | 0.011120000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_moderate | 0.15305666666666667 | 0.7333333333333333 | 104.18666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_moderate | 0.15647666666666665 | 0.7266666666666667 | 103.89333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_moderate | 0.13968999999999998 | 0.6666666666666666 | 86.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_quiet | 0.67653 | 1.0 | 1515.28 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_quiet | 0.6785333333333333 | 1.0 | 1520.72 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_reference_high_lat_quiet | 0.6841333333333334 | 1.0 | 1535.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed | 0.01081 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed | 0.00877 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_disturbed | 0.01367 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_moderate | 0.15657333333333334 | 0.8066666666666666 | 139.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_moderate | 0.16047999999999998 | 0.7833333333333333 | 145.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_moderate | 0.14287666666666665 | 0.7466666666666667 | 117.84 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_quiet | 0.67653 | 1.0 | 1516.3466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_quiet | 0.6785333333333333 | 1.0 | 1521.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_10000_qpsk_soft_high_lat_quiet | 0.6841333333333334 | 1.0 | 1535.8666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_disturbed | 0.16963 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_disturbed | 0.17006 | 0.04 | 1.28 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_disturbed | 0.17922000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_moderate | 0.21669000000000002 | 0.87 | 191.57333333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_moderate | 0.21396 | 0.8666666666666667 | 185.41333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_moderate | 0.21045999999999998 | 0.8766666666666667 | 174.13333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_quiet | 0.6796366666666667 | 1.0 | 2344.9333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_quiet | 0.6778233333333333 | 1.0 | 2327.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_reference_high_lat_quiet | 0.6799 | 1.0 | 2343.653333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_disturbed | 0.18084 | 0.03 | 1.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_disturbed | 0.17742000000000002 | 0.05 | 1.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_disturbed | 0.19436 | 0.01 | 0.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_moderate | 0.2172666666666667 | 0.9533333333333334 | 261.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_moderate | 0.21464 | 0.9533333333333334 | 255.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_moderate | 0.21148333333333333 | 0.9533333333333334 | 243.84 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_quiet | 0.6796366666666667 | 1.0 | 2380.826666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_quiet | 0.6778233333333333 | 1.0 | 2373.04 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_16qam_soft_high_lat_quiet | 0.6799 | 1.0 | 2382.4533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed | 0.31396999999999997 | 0.51 | 44.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed | 0.31864000000000003 | 0.46 | 49.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_disturbed | 0.34264000000000006 | 0.37 | 39.04 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_moderate | 0.5647233333333334 | 1.0 | 1219.7866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_moderate | 0.5595533333333333 | 1.0 | 1194.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_moderate | 0.5539233333333333 | 1.0 | 1179.68 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_quiet | 0.6900433333333333 | 1.0 | 2314.88 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_quiet | 0.6900533333333333 | 1.0 | 2316.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bch_high_lat_quiet | 0.6902833333333334 | 1.0 | 2318.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.3296 | 0.42 | 32.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.32256999999999997 | 0.42 | 35.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.31959 | 0.36 | 31.04 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.5066666666666667 | 1.0 | 811.7333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.5034666666666666 | 1.0 | 816.4266666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.50112 | 1.0 | 795.2533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6299866666666667 | 1.0 | 1641.6266666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6303866666666668 | 1.0 | 1643.5466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.62917 | 1.0 | 1639.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed | 0.045579999999999996 | 0.02 | 0.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed | 0.04447 | 0.05 | 1.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_disturbed | 0.05602 | 0.06 | 2.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate | 0.43536666666666674 | 0.9533333333333334 | 229.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate | 0.44026999999999994 | 0.9666666666666667 | 230.61333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_moderate | 0.43296333333333337 | 0.9433333333333334 | 217.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet | 0.6752433333333333 | 1.0 | 900.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet | 0.6791766666666667 | 1.0 | 907.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_diversity_high_lat_quiet | 0.6741066666666666 | 1.0 | 898.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed | 0.049850000000000005 | 0.03 | 0.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed | 0.050309999999999994 | 0.05 | 1.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_disturbed | 0.062240000000000004 | 0.05 | 2.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate | 0.4051166666666667 | 0.9433333333333334 | 213.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate | 0.40232 | 0.94 | 209.06666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_moderate | 0.39294666666666667 | 0.93 | 194.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet | 0.6866166666666668 | 1.0 | 919.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet | 0.6859466666666666 | 1.0 | 918.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_halfband_control_high_lat_quiet | 0.6858033333333334 | 1.0 | 918.6133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed | 0.30935 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed | 0.31788 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_disturbed | 0.33841 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate | 0.5706600000000001 | 0.5233333333333333 | 25.733333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate | 0.5605933333333333 | 0.51 | 24.533333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_moderate | 0.5579166666666666 | 0.48 | 22.053333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet | 0.6902266666666667 | 1.0 | 181.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet | 0.6902033333333334 | 1.0 | 181.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave2048_high_lat_quiet | 0.6902366666666666 | 1.0 | 181.76 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed | 0.3144 | 0.36 | 23.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed | 0.31903 | 0.34 | 22.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_disturbed | 0.33907 | 0.31 | 20.24 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate | 0.56536 | 1.0 | 720.6933333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate | 0.5612233333333333 | 1.0 | 713.7333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_moderate | 0.5557866666666667 | 1.0 | 698.0533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet | 0.6901433333333333 | 1.0 | 1460.8533333333332 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet | 0.68998 | 1.0 | 1460.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave256_high_lat_quiet | 0.6904366666666667 | 1.0 | 1462.4533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed | 0.3107 | 0.37 | 27.84 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed | 0.31795 | 0.44 | 38.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_disturbed | 0.34184 | 0.37 | 32.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate | 0.5657933333333334 | 1.0 | 954.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate | 0.5604433333333334 | 1.0 | 941.4933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_moderate | 0.5540700000000001 | 1.0 | 918.5066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet | 0.69044 | 1.0 | 1801.2533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet | 0.69007 | 1.0 | 1799.5466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_interleave32_high_lat_quiet | 0.6909200000000001 | 1.0 | 1802.7466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed | 0.31398 | 0.41 | 27.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed | 0.3177 | 0.4 | 36.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_disturbed | 0.33819000000000005 | 0.36 | 35.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate | 0.56494 | 1.0 | 954.1333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate | 0.5571866666666667 | 1.0 | 938.5066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_moderate | 0.55544 | 1.0 | 912.9866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet | 0.6892166666666666 | 1.0 | 1796.4533333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet | 0.6897033333333333 | 1.0 | 1797.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_half_high_lat_quiet | 0.6903266666666668 | 1.0 | 1801.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed | 0.31236 | 0.29 | 14.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed | 0.31538 | 0.34 | 17.92 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_disturbed | 0.33952 | 0.23 | 12.64 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate | 0.5670933333333333 | 1.0 | 607.92 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate | 0.5584600000000001 | 1.0 | 586.72 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_moderate | 0.5548500000000001 | 1.0 | 576.9066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet | 0.6906833333333334 | 1.0 | 1199.2533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet | 0.6905266666666666 | 1.0 | 1200.1066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_k9_third_high_lat_quiet | 0.6910266666666667 | 1.0 | 1202.1333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed | 0.3011 | 0.38 | 28.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed | 0.30088000000000004 | 0.39 | 32.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_disturbed | 0.31467 | 0.27 | 23.76 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_moderate | 0.5621366666666666 | 1.0 | 939.4933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_moderate | 0.5556266666666666 | 1.0 | 918.5866666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_moderate | 0.5534566666666667 | 1.0 | 897.1733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_quiet | 0.6900533333333333 | 1.0 | 1798.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_quiet | 0.6900633333333334 | 1.0 | 1799.0133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_reference_high_lat_quiet | 0.69096 | 1.0 | 1803.28 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.33597 | 0.43 | 37.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.32843000000000006 | 0.42 | 36.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.32382 | 0.37 | 32.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.5065666666666666 | 1.0 | 833.8133333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.5044500000000001 | 1.0 | 834.3466666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.5018199999999999 | 1.0 | 811.0133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6299866666666667 | 1.0 | 1641.6266666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6303866666666668 | 1.0 | 1643.5466666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.62917 | 1.0 | 1639.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed | 0.31297 | 0.43 | 32.16 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed | 0.32025 | 0.41 | 36.96 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_disturbed | 0.33845 | 0.32 | 29.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_moderate | 0.5647566666666667 | 1.0 | 962.8266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_moderate | 0.55883 | 1.0 | 939.44 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_moderate | 0.5547133333333333 | 1.0 | 917.8933333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_quiet | 0.6900533333333333 | 1.0 | 1798.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_quiet | 0.6900633333333334 | 1.0 | 1798.9066666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_soft_high_lat_quiet | 0.69096 | 1.0 | 1803.3866666666668 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed | 0.31396999999999997 | 0.09 | 3.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed | 0.32095 | 0.12 | 3.84 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_disturbed | 0.34430999999999995 | 0.13 | 4.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate | 0.5771566666666667 | 1.0 | 287.12 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate | 0.57361 | 0.9966666666666667 | 279.17333333333335 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_moderate | 0.5680366666666666 | 1.0 | 273.06666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet | 0.6894399999999999 | 1.0 | 672.48 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet | 0.6898 | 1.0 | 673.2266666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_bpsk_walsh8_high_lat_quiet | 0.6897066666666667 | 1.0 | 673.0133333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed | 0.00512 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate | 0.23040000000000002 | 0.11 | 3.493333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate | 0.23381333333333335 | 0.14666666666666667 | 4.666666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_moderate | 0.22698666666666667 | 0.11 | 3.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet | 0.29696 | 0.35 | 11.173333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet | 0.29866666666666664 | 0.3566666666666667 | 11.386666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard4_high_lat_quiet | 0.29696 | 0.35 | 11.173333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_disturbed | 0.00768 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate | 0.23656333333333332 | 0.08 | 2.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate | 0.24935666666666667 | 0.11 | 3.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_moderate | 0.23912000000000003 | 0.11 | 3.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet | 0.2980066666666667 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet | 0.29801 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk4_guard8_high_lat_quiet | 0.2980066666666667 | 0.23333333333333334 | 7.466666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed | 0.00512 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate | 0.2816 | 0.23666666666666666 | 7.573333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate | 0.30549333333333334 | 0.32 | 10.213333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_moderate | 0.27648 | 0.23 | 7.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6733333333333333 | 21.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6733333333333333 | 21.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6733333333333333 | 21.52 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed | 0.01536 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_disturbed | 0.01536 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate | 0.30207999999999996 | 0.21333333333333335 | 6.826666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate | 0.29952 | 0.2 | 6.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_moderate | 0.29184000000000004 | 0.18666666666666668 | 5.973333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet | 0.37632 | 0.45 | 14.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet | 0.37632 | 0.45 | 14.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_fsk8_guard8_high_lat_quiet | 0.37632 | 0.45 | 14.373333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed | 0.24512 | 0.18 | 9.68 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed | 0.23532 | 0.19 | 14.32 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_disturbed | 0.25429999999999997 | 0.15 | 10.88 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_moderate | 0.44405333333333336 | 1.0 | 831.6533333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_moderate | 0.44199000000000005 | 1.0 | 833.7066666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_moderate | 0.43116666666666664 | 0.9966666666666667 | 798.9066666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_quiet | 0.6920266666666667 | 1.0 | 2429.4666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_quiet | 0.6920166666666666 | 1.0 | 2428.9333333333334 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_reference_high_lat_quiet | 0.6920166666666666 | 1.0 | 2429.2533333333336 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed | 0.26315 | 0.29 | 18.56 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed | 0.25120000000000003 | 0.24 | 26.08 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_disturbed | 0.27294 | 0.2 | 17.28 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_moderate | 0.4453566666666667 | 1.0 | 991.7866666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_moderate | 0.4428533333333333 | 1.0 | 980.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_moderate | 0.43272333333333335 | 1.0 | 945.92 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_quiet | 0.6920266666666667 | 1.0 | 2429.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_quiet | 0.6920166666666666 | 1.0 | 2429.36 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_followup_24000_qpsk_soft_high_lat_quiet | 0.6920166666666666 | 1.0 | 2429.5733333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_disturbed | 0.0062 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_moderate | 0.0621 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_moderate | 0.0668 | 0.2 | 12.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_moderate | 0.08199999999999999 | 0.4 | 48.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_quiet | 0.6614 | 1.0 | 2068.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_quiet | 0.658 | 1.0 | 2061.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_reference_high_lat_quiet | 0.6826 | 1.0 | 2122.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_disturbed | 0.0031 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_disturbed | 0.0043 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_disturbed | 0.0062 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_moderate | 0.0621 | 0.2 | 12.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_moderate | 0.06870000000000001 | 0.4 | 27.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_moderate | 0.0839 | 0.4 | 64.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_quiet | 0.6614 | 1.0 | 2080.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_quiet | 0.658 | 1.0 | 2068.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_16qam_soft_high_lat_quiet | 0.6826 | 1.0 | 2148.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed | 0.0223 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed | 0.022 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_disturbed | 0.0126 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_moderate | 0.26 | 0.8 | 179.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_moderate | 0.23610000000000003 | 1.0 | 136.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_moderate | 0.2727 | 1.0 | 212.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_quiet | 0.6719999999999999 | 1.0 | 1016.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_quiet | 0.644 | 1.0 | 961.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bch_high_lat_quiet | 0.686 | 1.0 | 1038.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.0158 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.0631 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.2884 | 0.9 | 121.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.19090000000000001 | 0.8 | 76.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_moderate | 0.2884 | 1.0 | 149.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.624 | 1.0 | 683.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.624 | 1.0 | 683.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_bpsk_header_reference_high_lat_quiet | 0.61 | 1.0 | 664.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate | 0.0774 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate | 0.049 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_moderate | 0.07970000000000001 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet | 0.661 | 1.0 | 360.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet | 0.6333 | 1.0 | 341.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_diversity_high_lat_quiet | 0.6333 | 1.0 | 341.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate | 0.06720000000000001 | 0.2 | 8.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate | 0.054900000000000004 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_moderate | 0.0454 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet | 0.6887 | 1.0 | 380.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet | 0.6887 | 1.0 | 380.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_halfband_control_high_lat_quiet | 0.661 | 1.0 | 360.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed | 0.0316 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed | 0.036 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_disturbed | 0.011300000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate | 0.2141 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate | 0.2285 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_moderate | 0.2794 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet | 0.6719999999999999 | 1.0 | 67.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet | 0.644 | 0.9 | 54.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave2048_high_lat_quiet | 0.686 | 1.0 | 73.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed | 0.0316 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed | 0.0246 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_disturbed | 0.0114 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate | 0.2609 | 0.8 | 68.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate | 0.2427 | 0.5 | 35.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_moderate | 0.28690000000000004 | 1.0 | 85.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet | 0.6719999999999999 | 1.0 | 584.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet | 0.644 | 1.0 | 546.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave256_high_lat_quiet | 0.686 | 1.0 | 604.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed | 0.0223 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed | 0.0258 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_disturbed | 0.012199999999999999 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate | 0.23199999999999998 | 0.8 | 107.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate | 0.2332 | 1.0 | 109.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_moderate | 0.2761 | 0.9 | 135.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet | 0.6719999999999999 | 1.0 | 732.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet | 0.644 | 1.0 | 690.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_interleave32_high_lat_quiet | 0.686 | 1.0 | 751.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed | 0.0223 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed | 0.0258 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_disturbed | 0.0118 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate | 0.2259 | 0.9 | 101.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate | 0.2424 | 0.9 | 96.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_moderate | 0.2931 | 1.0 | 143.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet | 0.6719999999999999 | 1.0 | 728.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet | 0.644 | 1.0 | 690.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_half_high_lat_quiet | 0.686 | 1.0 | 751.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed | 0.0223 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed | 0.0229 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_disturbed | 0.012199999999999999 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate | 0.21989999999999998 | 0.8 | 64.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate | 0.233 | 0.7 | 55.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_moderate | 0.28759999999999997 | 0.8 | 76.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet | 0.6719999999999999 | 1.0 | 484.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet | 0.644 | 1.0 | 455.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_k9_third_high_lat_quiet | 0.686 | 1.0 | 500.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed | 0.0158 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed | 0.019700000000000002 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_disturbed | 0.0075 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_moderate | 0.2318 | 0.9 | 101.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_moderate | 0.26349999999999996 | 0.9 | 118.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_moderate | 0.2965 | 1.0 | 132.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_quiet | 0.6719999999999999 | 1.0 | 732.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_quiet | 0.644 | 1.0 | 690.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_reference_high_lat_quiet | 0.686 | 1.0 | 751.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.0158 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.0785 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.2884 | 0.9 | 134.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.1953 | 0.8 | 80.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_moderate | 0.2884 | 1.0 | 156.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.624 | 1.0 | 683.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.624 | 1.0 | 683.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_bpsk_header_high_lat_quiet | 0.61 | 1.0 | 664.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed | 0.0316 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed | 0.0228 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_disturbed | 0.0118 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_moderate | 0.23370000000000002 | 0.9 | 111.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_moderate | 0.26749999999999996 | 0.9 | 121.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_moderate | 0.3024 | 1.0 | 142.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_quiet | 0.6719999999999999 | 1.0 | 732.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_quiet | 0.644 | 1.0 | 690.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_soft_high_lat_quiet | 0.686 | 1.0 | 751.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed | 0.0299 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed | 0.0229 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_disturbed | 0.0118 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate | 0.2952 | 0.5 | 15.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate | 0.2834 | 0.3 | 12.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_moderate | 0.3247 | 0.4 | 22.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet | 0.6719999999999999 | 1.0 | 271.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet | 0.644 | 1.0 | 248.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_bpsk_walsh8_high_lat_quiet | 0.686 | 1.0 | 280.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate | 0.22186666666666666 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate | 0.2730666666666667 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_moderate | 0.23893333333333333 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate | 0.2048 | 0.03333333333333333 | 1.0666666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate | 0.2048 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_moderate | 0.2304 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate | 0.22186666666666666 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate | 0.29013333333333335 | 0.16666666666666666 | 5.066666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_moderate | 0.23893333333333333 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_disturbed | 0.0256 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate | 0.3384 | 0.26666666666666666 | 8.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate | 0.31276666666666664 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_moderate | 0.2616 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet | 0.3640666666666667 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet | 0.3640666666666667 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_fsk8_guard8_high_lat_quiet | 0.3640666666666667 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed | 0.0039 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed | 0.0031 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_disturbed | 0.0062 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_moderate | 0.1332 | 0.8 | 85.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_moderate | 0.145 | 0.7 | 57.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_moderate | 0.1668 | 0.9 | 137.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_quiet | 0.6719999999999999 | 1.0 | 1471.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_quiet | 0.644 | 1.0 | 1397.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_reference_high_lat_quiet | 0.686 | 1.0 | 1506.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed | 0.010100000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed | 0.0062 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_disturbed | 0.022 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_moderate | 0.1351 | 0.9 | 124.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_moderate | 0.145 | 0.9 | 116.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_moderate | 0.1668 | 1.0 | 175.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_quiet | 0.6719999999999999 | 1.0 | 1471.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_quiet | 0.644 | 1.0 | 1397.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_10000_qpsk_soft_high_lat_quiet | 0.686 | 1.0 | 1506.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_disturbed | 0.1719 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_disturbed | 0.18 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_disturbed | 0.1857 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_moderate | 0.2354 | 1.0 | 227.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_moderate | 0.21869999999999998 | 0.8 | 237.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_moderate | 0.20299999999999999 | 0.8 | 180.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_quiet | 0.6833 | 1.0 | 2239.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_quiet | 0.6723 | 1.0 | 2250.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_reference_high_lat_quiet | 0.6807000000000001 | 1.0 | 2232.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_disturbed | 0.1664 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_disturbed | 0.17880000000000001 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_disturbed | 0.19090000000000001 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_moderate | 0.2354 | 1.0 | 297.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_moderate | 0.22000000000000003 | 1.0 | 304.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_moderate | 0.2057 | 0.8 | 227.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_quiet | 0.6833 | 1.0 | 2320.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_quiet | 0.6723 | 1.0 | 2272.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_16qam_soft_high_lat_quiet | 0.6807000000000001 | 1.0 | 2318.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed | 0.3346 | 0.4 | 47.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed | 0.34900000000000003 | 0.4 | 40.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_disturbed | 0.32530000000000003 | 0.6 | 60.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_moderate | 0.5921000000000001 | 1.0 | 1230.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_moderate | 0.548 | 1.0 | 1128.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_moderate | 0.5126999999999999 | 1.0 | 1032.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_quiet | 0.6924 | 1.0 | 2256.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_quiet | 0.6925 | 1.0 | 2256.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bch_high_lat_quiet | 0.6873 | 1.0 | 2224.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.36669999999999997 | 0.5 | 41.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.3256 | 0.5 | 41.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_disturbed | 0.2669 | 0.3 | 25.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.483 | 1.0 | 720.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.49589999999999995 | 1.0 | 790.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_moderate | 0.499 | 1.0 | 747.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.629 | 1.0 | 1597.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.629 | 1.0 | 1597.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_bpsk_header_reference_high_lat_quiet | 0.6291 | 1.0 | 1600.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed | 0.0921 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed | 0.033 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_disturbed | 0.0615 | 0.2 | 5.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate | 0.48200000000000004 | 1.0 | 288.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate | 0.40750000000000003 | 0.9 | 169.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_moderate | 0.47030000000000005 | 1.0 | 224.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet | 0.6665 | 1.0 | 860.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet | 0.6899 | 1.0 | 902.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_diversity_high_lat_quiet | 0.6900000000000001 | 1.0 | 902.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed | 0.0608 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed | 0.040999999999999995 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_disturbed | 0.0581 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate | 0.4426 | 1.0 | 295.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate | 0.3705 | 0.9 | 172.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_moderate | 0.41130000000000005 | 1.0 | 207.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet | 0.6783 | 1.0 | 883.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet | 0.6899 | 1.0 | 902.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_halfband_control_high_lat_quiet | 0.6900000000000001 | 1.0 | 902.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed | 0.33039999999999997 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed | 0.3493 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_disturbed | 0.3237 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate | 0.6022000000000001 | 0.7 | 26.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate | 0.557 | 0.7 | 25.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_moderate | 0.5438 | 0.5 | 15.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet | 0.6924 | 1.0 | 176.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet | 0.6925 | 1.0 | 176.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave2048_high_lat_quiet | 0.6769999999999999 | 1.0 | 163.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed | 0.3289 | 0.3 | 26.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed | 0.3332 | 0.2 | 14.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_disturbed | 0.3307 | 0.5 | 45.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate | 0.5783 | 1.0 | 728.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate | 0.563 | 1.0 | 714.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_moderate | 0.5432 | 1.0 | 599.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet | 0.6924 | 1.0 | 1419.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet | 0.6925 | 1.0 | 1419.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave256_high_lat_quiet | 0.6926 | 1.0 | 1409.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed | 0.32 | 0.4 | 38.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed | 0.3417 | 0.5 | 31.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_disturbed | 0.3069 | 0.4 | 24.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate | 0.5644 | 1.0 | 979.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate | 0.5686 | 1.0 | 961.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_moderate | 0.5422 | 1.0 | 803.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet | 0.6924 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet | 0.6925 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_interleave32_high_lat_quiet | 0.6854 | 1.0 | 1724.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed | 0.3341 | 0.4 | 25.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed | 0.3389 | 0.4 | 43.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_disturbed | 0.313 | 0.5 | 53.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate | 0.5923 | 1.0 | 979.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate | 0.5586 | 1.0 | 952.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_moderate | 0.5628 | 1.0 | 804.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet | 0.6924 | 1.0 | 1759.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet | 0.6925 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_half_high_lat_quiet | 0.682 | 1.0 | 1720.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed | 0.3345 | 0.3 | 16.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed | 0.337 | 0.2 | 9.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_disturbed | 0.3161 | 0.2 | 11.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate | 0.6109 | 1.0 | 666.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate | 0.5445 | 1.0 | 555.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_moderate | 0.5396 | 1.0 | 465.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet | 0.6924 | 1.0 | 1174.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet | 0.6925 | 1.0 | 1174.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_k9_third_high_lat_quiet | 0.6926 | 1.0 | 1171.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed | 0.30379999999999996 | 0.4 | 27.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed | 0.3306 | 0.5 | 30.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_disturbed | 0.302 | 0.4 | 29.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_moderate | 0.5974 | 1.0 | 1010.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_moderate | 0.5407 | 1.0 | 869.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_moderate | 0.5406 | 1.0 | 752.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_quiet | 0.6924 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_quiet | 0.6925 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_reference_high_lat_quiet | 0.6873 | 1.0 | 1733.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.3745 | 0.6 | 44.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.337 | 0.6 | 48.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_disturbed | 0.2826 | 0.3 | 28.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.483 | 1.0 | 736.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.49589999999999995 | 1.0 | 806.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_moderate | 0.499 | 1.0 | 765.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.629 | 1.0 | 1597.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.629 | 1.0 | 1597.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_bpsk_header_high_lat_quiet | 0.6291 | 1.0 | 1600.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed | 0.3225 | 0.5 | 33.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed | 0.3462 | 0.5 | 40.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_disturbed | 0.3176 | 0.4 | 32.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_moderate | 0.5974 | 1.0 | 1032.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_moderate | 0.5453 | 1.0 | 903.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_moderate | 0.5406 | 1.0 | 768.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_quiet | 0.6924 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_quiet | 0.6925 | 1.0 | 1762.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_soft_high_lat_quiet | 0.6873 | 1.0 | 1733.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed | 0.3328 | 0.2 | 5.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed | 0.3527 | 0.3 | 9.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_disturbed | 0.32320000000000004 | 0.4 | 12.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate | 0.5921000000000001 | 1.0 | 306.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate | 0.5581 | 1.0 | 282.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_moderate | 0.5626 | 1.0 | 224.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet | 0.6924 | 1.0 | 657.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet | 0.6925 | 1.0 | 657.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_bpsk_walsh8_high_lat_quiet | 0.682 | 1.0 | 635.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate | 0.256 | 0.16666666666666666 | 5.066666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate | 0.256 | 0.16666666666666666 | 5.066666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_moderate | 0.18773333333333334 | 0.03333333333333333 | 1.0666666666666667 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard4_high_lat_quiet | 0.29013333333333335 | 0.3333333333333333 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate | 0.2304 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate | 0.2048 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_moderate | 0.2048 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk4_guard8_high_lat_quiet | 0.2816 | 0.2 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate | 0.256 | 0.16666666666666666 | 5.333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate | 0.3072 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_moderate | 0.3072 | 0.16666666666666666 | 5.333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard4_high_lat_quiet | 0.37546666666666667 | 0.6333333333333333 | 20.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed | 0.0 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_disturbed | 0.0256 | 0.0 | 0.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate | 0.23603333333333334 | 0.06666666666666667 | 2.1333333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate | 0.31276666666666664 | 0.16666666666666666 | 5.066666666666666 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_moderate | 0.23600000000000002 | 0.1 | 3.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet | 0.3640666666666667 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet | 0.3640333333333333 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_fsk8_guard8_high_lat_quiet | 0.3640333333333333 | 0.4 | 12.533333333333333 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed | 0.2624 | 0.2 | 10.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed | 0.2451 | 0.2 | 12.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_disturbed | 0.2479 | 0.1 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_moderate | 0.4885 | 1.0 | 978.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_moderate | 0.438 | 1.0 | 857.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_moderate | 0.3779 | 0.9 | 591.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_quiet | 0.6924 | 1.0 | 2352.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_quiet | 0.6925 | 1.0 | 2352.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_reference_high_lat_quiet | 0.6925 | 1.0 | 2356.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed | 0.266 | 0.4 | 25.6 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed | 0.26070000000000004 | 0.3 | 27.2 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_disturbed | 0.2559 | 0.1 | 6.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_moderate | 0.4885 | 1.0 | 1136.0 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_moderate | 0.44589999999999996 | 1.0 | 1012.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_moderate | 0.3811 | 1.0 | 678.4 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_quiet | 0.6924 | 1.0 | 2352.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_quiet | 0.6925 | 1.0 | 2352.8 | Unavailable: audit definitions/standby instrumentation |
| E2_encoding_screen_24000_qpsk_soft_high_lat_quiet | 0.6925 | 1.0 | 2356.0 | Unavailable: audit definitions/standby instrumentation |

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

See [TESTING.md](../../TESTING.md) and [source audit/questions](../../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 672 / 672 | 80.920 | 1800 | yes |
| full / selected rerun | 378 / 378 | 2125.085 | 1800 | **NO** |
| full / selected rerun | 756 / 756 | 211.195 | 1800 | yes |
| quick / selected rerun | 84 / 84 | 3.277 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
