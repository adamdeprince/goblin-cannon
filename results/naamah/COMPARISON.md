# Goblin Cannon simulated channel — naamah latency retest

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

Built and tested the existing B5 cases on `naamah` (AMD Ryzen Threadripper PRO 5995WX, AVX2, GCC 16.1, Release). Installed the missing gRPC dependencies. The 11 CTest entries passed in 6.40 seconds.

All six B5 cases ran three times, one worker at a time, with their original 12-second duration and seed `7446529`. Carrier correction remained off and adaptive equalization remained on. Canonical result JSON was byte-identical across the three repetitions for every case. Host wall-clock observations remain separate.

The measured path is source creation through auction, framing, FEC, crypto, modem and paced 1 ms simulated audio buffers to sink delivery. Startup is included. Physical audio drivers and network sockets are not represented.

The quieter host did not materially change these latency measurements. Sample-clock metrics and delivered message IDs match the original `avx10` runs exactly. The deterministic path already takes 77 / 67 / 63 ms at p99.9 for QPSK / 16-QAM / 64-QAM on the 10 kHz profile, before CPU/OS time is measured. All six B5 cases retain their reviewed expected failures; the 24 kHz cases still deliver no messages.

## Simulated channel — comparison with avx10

The prior `avx10` run used AVX-512 and four matrix workers. `naamah` uses AVX2 and one worker. CPU, ISA and concurrency differ; this is a comparison of recorded observations, not an isolated measurement of scheduler noise.

| Profile | Modulation | avx10 p99.9 ms | naamah p99.9 ms, repeats 1 / 2 / 3 | Sample-clock p99.9 ms | 2.1 ms assertion |
| --- | --- | ---: | --- | ---: | --- |
| 10 kHz | 16qam | 67.018 | 67.024 / 67.017 / 67.023 | 67.000 | xfail / xfail / xfail |
| 10 kHz | 64qam | 63.032 | 63.034 / 63.033 / 63.032 | 63.000 | xfail / xfail / xfail |
| 10 kHz | qpsk | 77.014 | 77.013 / 77.012 / 77.012 | 77.000 | xfail / xfail / xfail |
| 24 kHz | 16qam | no deliveries | no deliveries / no deliveries / no deliveries | no deliveries | xfail / xfail / xfail |
| 24 kHz | 64qam | no deliveries | no deliveries / no deliveries / no deliveries | no deliveries | xfail / xfail / xfail |
| 24 kHz | qpsk | no deliveries | no deliveries / no deliveries / no deliveries | no deliveries | xfail / xfail / xfail |

## Simulated channel — individual observations

| Case | Repeat | Delivered / created | p50 ms | p99 ms | p99.9 ms | Max ms |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| [B5_10000_16qam_null](repeat-1/B5_10000_16qam_null/7446529.host.json) | 1 | 1196 / 1200 | 9.000 | 9.006 | 67.024 | 73.048 |
| [B5_10000_16qam_null](repeat-2/B5_10000_16qam_null/7446529.host.json) | 2 | 1196 / 1200 | 9.000 | 9.006 | 67.017 | 73.048 |
| [B5_10000_16qam_null](repeat-3/B5_10000_16qam_null/7446529.host.json) | 3 | 1196 / 1200 | 9.000 | 9.006 | 67.023 | 73.045 |
| [B5_10000_64qam_null](repeat-1/B5_10000_64qam_null/7446529.host.json) | 1 | 1196 / 1200 | 6.001 | 7.001 | 63.034 | 71.047 |
| [B5_10000_64qam_null](repeat-2/B5_10000_64qam_null/7446529.host.json) | 2 | 1196 / 1200 | 6.001 | 7.001 | 63.033 | 71.053 |
| [B5_10000_64qam_null](repeat-3/B5_10000_64qam_null/7446529.host.json) | 3 | 1196 / 1200 | 6.001 | 7.004 | 63.032 | 71.010 |
| [B5_10000_qpsk_null](repeat-1/B5_10000_qpsk_null/7446529.host.json) | 1 | 1194 / 1200 | 16.000 | 17.001 | 77.013 | 80.036 |
| [B5_10000_qpsk_null](repeat-2/B5_10000_qpsk_null/7446529.host.json) | 2 | 1194 / 1200 | 16.000 | 17.001 | 77.012 | 80.038 |
| [B5_10000_qpsk_null](repeat-3/B5_10000_qpsk_null/7446529.host.json) | 3 | 1194 / 1200 | 16.000 | 17.001 | 77.012 | 80.039 |
| [B5_24000_16qam_null](repeat-1/B5_24000_16qam_null/7446529.host.json) | 1 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_16qam_null](repeat-2/B5_24000_16qam_null/7446529.host.json) | 2 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_16qam_null](repeat-3/B5_24000_16qam_null/7446529.host.json) | 3 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_64qam_null](repeat-1/B5_24000_64qam_null/7446529.host.json) | 1 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_64qam_null](repeat-2/B5_24000_64qam_null/7446529.host.json) | 2 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_64qam_null](repeat-3/B5_24000_64qam_null/7446529.host.json) | 3 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_qpsk_null](repeat-1/B5_24000_qpsk_null/7446529.host.json) | 1 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_qpsk_null](repeat-2/B5_24000_qpsk_null/7446529.host.json) | 2 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |
| [B5_24000_qpsk_null](repeat-3/B5_24000_qpsk_null/7446529.host.json) | 3 | 0 / 1200 | no deliveries | no deliveries | no deliveries | no deliveries |

## Simulated channel — startup diagnostic

The following characterization selects messages created at least one second after stream start, using recorded sample-clock creation times. It does not replace the complete-run results or alter the 2.1 ms assertion.

| Case | Selected delivered messages, repeats 1 / 2 / 3 | p99.9 ms, repeats 1 / 2 / 3 |
| --- | --- | --- |
| B5_10000_16qam_null | 1100 / 1100 / 1100 | 9.011 / 9.013 / 9.010 |
| B5_10000_64qam_null | 1100 / 1100 / 1100 | 7.008 / 7.002 / 7.025 |
| B5_10000_qpsk_null | 1099 / 1099 / 1099 | 17.005 / 17.006 / 17.002 |
| B5_24000_16qam_null | 0 / 0 / 0 | no deliveries / no deliveries / no deliveries |
| B5_24000_64qam_null | 0 / 0 / 0 | no deliveries / no deliveries / no deliveries |
| B5_24000_qpsk_null | 0 / 0 / 0 | no deliveries / no deliveries / no deliveries |

## Simulated channel — stage call durations

Stage times are measured per call and do not add up to per-message latency. TX and RX include their internal framing/FEC/crypto work; queue residence remains in the source-to-sink measurement.

| Case | Stage | p99.9 ms, repeats 1 / 2 / 3 |
| --- | --- | --- |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.998 / 0.998 / 0.998 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.002 / 0.001 / 0.001 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.026 / 0.025 / 0.025 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.003 / 0.003 / 0.003 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.998 / 0.998 / 1.049 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.001 / 0.001 / 0.002 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.035 / 0.038 / 0.048 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.003 / 0.004 / 0.005 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.999 / 0.998 / 0.998 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.001 / 0.001 / 0.001 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.020 / 0.020 / 0.020 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.003 / 0.003 / 0.003 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.998 / 0.998 / 0.998 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.001 / 0.002 / 0.002 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.275 / 0.281 / 0.259 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.011 / 0.013 / 0.013 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.998 / 0.998 / 0.998 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.001 / 0.002 / 0.002 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.258 / 0.231 / 0.263 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.014 / 0.012 / 0.014 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.998 / 0.998 / 0.998 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.001 / 0.001 / 0.001 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.003 / 0.001 / 0.002 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.306 / 0.206 / 0.304 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.014 / 0.010 / 0.014 |

## Simulated channel — retained evidence

[Comparison JSON](COMPARISON.json) includes full parameters and explicit differences from `avx10`. [Host environment and commands](VALIDATION.host.json) include CPU flags, compiler/library versions, CMake configuration, source digest, load and CPU counters before/after each repetition. The original `avx10` result files are retained in the parent results directory.

[Repetition 1](repeat-1/SUMMARY.md), [repetition 2](repeat-2/SUMMARY.md), [repetition 3](repeat-3/SUMMARY.md), and [CTest log](ctest.log). Reproduce the comparison with `python3 results/naamah/compare.py`.
