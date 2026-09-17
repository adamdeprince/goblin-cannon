# Goblin Cannon simulated channel AEAD results

OpenSSL AES-256-GCM authenticates production messages before sink delivery. The tag replaces message CRC integrity; RF-header CRCs screen framing only.

424 recorded runs / 412 unique case/seed/profile combinations. 9 expected-failing assertions across 9 cases remain in the current recovery-profile security selection. Six crypto assertions are fixed.

## Simulated channel scope and defect count

The brief's 1.019 ms / 13 assertions in 11 cases are from fixes-2-5. The newer recovery-profile ledger had 15 assertions in 13 cases; six crypto assertions now pass, leaving nine assertions in nine cases. Different profiles are never silently combined.

## Simulated channel A8: co-channel rejection

| SIR dB | Delivered | Authentication failures | FEC gaps | Foreign/corrupt delivered | Result |
| ---: | ---: | ---: | ---: | ---: | --- |
| [-10](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/A8_cochannel_-10dB/7446529.json) | 19 | 359 | 3 | 0 | pass |
| [0](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/A8_cochannel_0dB/7446529.json) | 19 | 0 | 1 | 0 | pass |
| [10](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/A8_cochannel_10dB/7446529.json) | 381 | 0 | 2 | 0 | pass |

A zero authentication count means no invalid complete record reached authentication in that trace. It is not a fabricated rejection count. The wrong-key RF/gRPC regression and D6 separately exercise actual verification failures.

## Simulated channel D6: errors, replay and process restart

| Observation | Count |
| --- | ---: |
| tamper_attempts | 43 |
| authentication_failures | 43 |
| replay_rejections | 16 |
| replay_deliveries | 0 |
| nonces_observed | 16 |
| reused_nonces_after_process_restart | 0 |
| valid_authenticated_deliveries | 16 |

Two distinct sender processes reserve epochs from one persisted journal with the same key. Every observed wire nonce is distinct. Key IDs are authenticated, but two-key overlap and coordinated mid-stream retirement remain `xfail`.

## Simulated channel B5: requested 12-case comparison

Added processing/buffering p99.9 in milliseconds. Old values are the brief's saved fixes-2-5 baseline; new values are serial naamah measurements with the same declared RF configuration. Total latency and the intrinsic transmission/modem reference are separate columns.

| Case | Old added | New added | Change µs | Total p99.9 | Intrinsic p99.9 | Result |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| [B5_10000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_16qam_null/7446529.host.json) | 0.862837 | 0.851479 | -11.4 | 39.009 | 38.188 | pass |
| [B5_10000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_16qam_polar_span_null/7446529.host.json) | 0.961891 | 1.002085 | 40.2 | 40.033 | 39.292 | pass |
| [B5_10000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_64qam_null/7446529.host.json) | 0.965252 | 1.003817 | 38.6 | 30.016 | 29.187 | pass |
| [B5_10000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_64qam_polar_span_null/7446529.host.json) | 0.955205 | 0.998979 | 43.8 | 32.000 | 31.167 | pass |
| [B5_10000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_qpsk_null/7446529.host.json) | 0.965769 | 0.982297 | 16.5 | 66.005 | 65.292 | pass |
| [B5_10000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_10000_qpsk_polar_span_null/7446529.host.json) | 0.910487 | 0.856285 | -54.2 | 83.002 | 82.688 | pass |
| [B5_24000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_16qam_null/7446529.host.json) | 0.755446 | 1.055395 | 299.9 | 22.082 | 21.750 | pass |
| [B5_24000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_16qam_polar_span_null/7446529.host.json) | 0.712733 | 1.050668 | 337.9 | 23.072 | 22.854 | pass |
| [B5_24000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_64qam_null/7446529.host.json) | 0.971146 | 1.020406 | 49.3 | 11.998 | 11.604 | pass |
| [B5_24000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_64qam_polar_span_null/7446529.host.json) | 1.019444 | 1.050326 | 30.9 | 10.102 | 9.250 | pass |
| [B5_24000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_qpsk_null/7446529.host.json) | 0.959394 | 0.990569 | 31.2 | 34.016 | 33.063 | pass |
| [B5_24000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/B5_24000_qpsk_polar_span_null/7446529.host.json) | 0.857044 | 1.027175 | 170.1 | 40.038 | 39.146 | pass |

## Simulated channel B5: current recovery profile

| Case | Added p99.9 ms | Total p99.9 ms | Intrinsic p99.9 ms | Result |
| --- | ---: | ---: | ---: | --- |
| [B5_10000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_16qam_null/7446529.host.json) | 1.008624 | 78.038 | 77.292 | pass |
| [B5_10000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_16qam_polar_span_null/7446529.host.json) | 0.969823 | 106.011 | 105.875 | pass |
| [B5_10000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_64qam_null/7446529.host.json) | 1.048407 | 69.006 | 68.062 | pass |
| [B5_10000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_64qam_polar_span_null/7446529.host.json) | 1.078016 | 97.034 | 96.875 | pass |
| [B5_10000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_qpsk_null/7446529.host.json) | 0.968812 | 104.006 | 103.917 | pass |
| [B5_10000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_10000_qpsk_polar_span_null/7446529.host.json) | 0.983144 | 133.007 | 132.563 | pass |
| [B5_24000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_16qam_null/7446529.host.json) | 1.094368 | 38.995 | 38.021 | pass |
| [B5_24000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_16qam_polar_span_null/7446529.host.json) | 1.094295 | 53.930 | 53.208 | pass |
| [B5_24000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_64qam_null/7446529.host.json) | 1.117963 | 25.100 | 24.417 | pass |
| [B5_24000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_64qam_polar_span_null/7446529.host.json) | 1.115913 | 40.115 | 39.604 | pass |
| [B5_24000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_qpsk_null/7446529.host.json) | 1.028078 | 50.019 | 49.313 | pass |
| [B5_24000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/B5_24000_qpsk_polar_span_null/7446529.host.json) | 1.082405 | 65.058 | 64.292 | pass |

Both tables use the unchanged 2.1 ms allowance. `.host.json` files retain measured stage call durations and source-to-framer timings. Canonical JSON retains deterministic added buffering, serialization estimates and modem/FEC residence; per-stage percentiles are not summed.

## Simulated channel B5: crypto profile

20,000 measured calls per size after 1,000 warmup calls, on naamah. EVP contexts are initialized once and reused. Times are microseconds; this profile excludes FEC/framing and journal startup.

| Body bytes | Seal p99.9 µs | Verify/open p99.9 µs |
| ---: | ---: | ---: |
| 3 | 0.280 | 0.261 |
| 16 | 0.210 | 0.201 |
| 128 | 0.350 | 0.380 |
| 1024 | 0.501 | 0.601 |
| 65534 | 22.733 | 26.801 |

The first cold EVP context setup took 936.452 µs before any message was created. There is no per-frame context creation or re-keying. Longer authenticated records change phase relative to 1 ms audio blocks; inspect `PROFILE.md` for the largest per-configuration regressions, deterministic buffering and matched pre-AEAD CPU measurements.

## Simulated channel A2/E2: current polar delivery

Ranges cover three independent seeds, not confidence intervals. Quiet/moderate/disturbed durations are 300/300/100 seconds per seed; raw RF screens remain ten seconds. The source uses the real airtime auction and every delivered message has passed GCM.

| Band kHz | Configuration | Preset | Useful bit/s | Fresh bit/s | Delivered / framed % | Freshness p99.9 ms | Longest silence s |
| ---: | --- | --- | ---: | ---: | ---: | ---: | ---: |
| 10 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_soft_high_lat_quiet/7446529.json) | quiet | 210.93–215.09 | 46.45–47.31 | 96.21–98.10 | 189.00 | 0.593 |
| 10 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_soft_high_lat_moderate/7446529.json) | moderate | 9.17–11.17 | 4.05–5.09 | 4.34–5.30 | 201.00 | 12.429–18.337 |
| 10 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_soft_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 10 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_bch_high_lat_quiet/7446529.json) | quiet | 292.99–297.68 | 280.19–285.20 | 96.87–98.41 | 165.00 | 0.486–0.555 |
| 10 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_bch_high_lat_moderate/7446529.json) | moderate | 19.09–20.24 | 16.21–17.49 | 6.55–6.95 | 174.00–177.00 | 9.964–11.191 |
| 10 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_bpsk_bch_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 10 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_soft_high_lat_quiet/7446529.json) | quiet | 425.84–432.88 | 425.84–432.88 | 97.11–98.71 | 135.00 | 0.379–0.380 |
| 10 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_soft_high_lat_moderate/7446529.json) | moderate | 13.87–17.89 | 13.87–17.89 | 3.28–4.24 | 142.00–146.00 | 12.035–15.208 |
| 10 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_soft_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 10 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_bch_high_lat_quiet/7446529.json) | quiet | 589.20–597.84 | 589.20–597.84 | 97.39–98.82 | 122.00 | 0.349–0.350 |
| 10 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_bch_high_lat_moderate/7446529.json) | moderate | 21.95–26.32 | 21.95–26.32 | 3.77–4.52 | 130.00–131.00 | 8.595–19.392 |
| 10 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_qpsk_bch_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 10 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_soft_high_lat_quiet/7446529.json) | quiet | 637.15–643.44 | 637.15–643.44 | 96.86–97.81 | 117.00 | 0.363–0.526 |
| 10 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_soft_high_lat_moderate/7446529.json) | moderate | 7.23–8.32 | 7.23–8.32 | 1.14–1.31 | 54.00–125.00 | 19.600–28.037 |
| 10 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_soft_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 10 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_bch_high_lat_quiet/7446529.json) | quiet | 881.15–887.01 | 881.15–887.01 | 97.11–97.76 | 108.00 | 0.324–0.395 |
| 10 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_bch_high_lat_moderate/7446529.json) | moderate | 10.88–11.92 | 10.88–11.92 | 1.24–1.37 | 43.00–113.00 | 14.903–28.456 |
| 10 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_10000_8psk_bch_high_lat_disturbed/7446529.json) | disturbed | 0.00 | 0.00 | 0.00 | Unobserved | 100.000 |
| 24 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_soft_high_lat_quiet/7446529.json) | quiet | 506.93–508.00 | 506.93–508.00 | 99.19–99.40 | 89.00 | 0.255–0.324 |
| 24 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_soft_high_lat_moderate/7446529.json) | moderate | 181.31–192.48 | 181.31–192.48 | 38.69–41.10 | 100.00–101.00 | 1.186–1.786 |
| 24 | [BPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_soft_high_lat_disturbed/7446529.json) | disturbed | 1.84–2.56 | 1.84–2.56 | 0.54–0.72 | 124.00–132.00 | 21.564–46.392 |
| 24 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_bch_high_lat_quiet/7446529.json) | quiet | 699.17–701.09 | 699.17–701.09 | 99.18–99.46 | 78.00 | 0.181–0.238 |
| 24 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_bch_high_lat_moderate/7446529.json) | moderate | 262.00–276.88 | 262.00–276.88 | 40.53–42.85 | 89.00–90.00 | 0.852–1.139 |
| 24 | [BPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_bpsk_bch_high_lat_disturbed/7446529.json) | disturbed | 0.88–4.80 | 0.88–4.80 | 0.20–0.98 | 56.00–59.00 | 19.666–42.119 |
| 24 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_soft_high_lat_quiet/7446529.json) | quiet | 1022.03 | 1022.03 | 99.98 | 66.00 | 0.053 |
| 24 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_soft_high_lat_moderate/7446529.json) | moderate | 314.48–333.81 | 314.48–333.81 | 33.55–35.62 | 78.00 | 1.035–1.549 |
| 24 | [QPSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_soft_high_lat_disturbed/7446529.json) | disturbed | 2.48–5.44 | 2.48–5.44 | 0.36–0.77 | 40.00–103.00 | 17.640–31.868 |
| 24 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_bch_high_lat_quiet/7446529.json) | quiet | 1409.15–1409.57 | 1409.15–1409.57 | 99.95–99.98 | 60.00 | 0.075–0.150 |
| 24 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_bch_high_lat_moderate/7446529.json) | moderate | 438.75–462.88 | 438.75–462.88 | 33.93–35.82 | 71.00–72.00 | 1.124–1.582 |
| 24 | [QPSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_qpsk_bch_high_lat_disturbed/7446529.json) | disturbed | 3.76–7.68 | 3.76–7.68 | 0.39–0.79 | 39.00–94.00 | 15.378–30.652 |
| 24 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_soft_high_lat_quiet/7446529.json) | quiet | 1527.63–1529.33 | 1527.63–1529.33 | 99.63–99.74 | 58.00 | 0.143–0.156 |
| 24 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_soft_high_lat_moderate/7446529.json) | moderate | 232.13–249.39 | 232.13–249.39 | 16.52–17.75 | 69.00–70.00 | 1.786–2.061 |
| 24 | [8-PSK · convolutional](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_soft_high_lat_disturbed/7446529.json) | disturbed | 0.64–1.20 | 0.64–1.20 | 0.06–0.12 | 30.00–37.00 | 34.682–82.215 |
| 24 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_bch_high_lat_quiet/7446529.json) | quiet | 2083.63–2090.99 | 2083.63–2090.99 | 99.48–99.83 | 45.00 | 0.141–0.149 |
| 24 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_bch_high_lat_moderate/7446529.json) | moderate | 309.65–330.48 | 309.65–330.48 | 16.01–17.09 | 61.00–63.00 | 1.715–2.180 |
| 24 | [8-PSK · BCH](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/E2_refinement_followup_24000_8psk_bch_high_lat_disturbed/7446529.json) | disturbed | 0.32–2.08 | 0.32–2.08 | 0.02–0.15 | 23.00–34.00 | 34.673–99.687 |

## Simulated channel remaining test groups

| Group | Status counts |
| --- | --- |
| A4 | xfail: 2 |
| A8 | pass: 3 |
| B1 | xfail: 5 |
| B4 | pass: 3 |
| C4 | pass: 1 |
| D3 | xfail: 1 |
| D4 | pass: 92 |
| D6 | pass: 1, xfail: 1 |
| E1 | pass: 3 |

## Simulated channel validation and runtime

Both avx10 and naamah pass 21/21 CTest tests, including the production wrong-key RF/gRPC counter regression. The Python harness passes 14 checks; CLI/protobuf serialization passes 19. Logs and browser evidence are in `validation-meta/`.

| Selection | Tier | Runs | Wall seconds | Invocation budget seconds |
| --- | --- | ---: | ---: | ---: |
| [Security](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/EXECUTION-full-selection-a62b4aec6e39.json) | full | 5 | 1.053 | 1800 |
| [Security](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/EXECUTION-quick-selection-823d23d587d8.json) | quick | 107 | 30.093 | 120 |
| [Polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/EXECUTION-full-selection-2adf8925d945.json) | full | 108 | 43.122 | 1800 |
| [Polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/EXECUTION-full-selection-ecf0622ce5bc.json) | full | 108 | 871.234 | 1800 |
| [Polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/polar/EXECUTION-quick-selection-9db8832189ef.json) | quick | 72 | 3.559 | 120 |
| [Brief B5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/EXECUTION-full-selection-6c744d4ccc3f.json) | full | 6 | 78.416 | 1800 |
| [Brief B5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/brief-latency/EXECUTION-quick-selection-b612eb6261b3.json) | quick | 6 | 76.590 | 120 |
| [Current B5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/EXECUTION-full-selection-2d68204b188f.json) | full | 6 | 78.563 | 1800 |
| [Current B5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/naamah-latency/EXECUTION-quick-selection-0eb949462e18.json) | quick | 6 | 76.793 | 120 |

These are selected invocations, not complete tiers. Their combined quick runtime exceeds 120 seconds, including the two separately measured B5 profiles; no counts or durations were reduced. The slow-FSK unit recovery trace was extended from 30 to 120 simulated seconds to fit complete authenticated records around its dropout, with its delivery assertions retained.


## Simulated channel defects found

| Case | Assertion | Finding |
| --- | --- | --- |
| [A4_10000_64qam_drift_10min](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/A4_10000_64qam_drift_10min/7446529.json) | sync_held | With the recovery profile and carrier correction off, the 10 kHz 64-QAM ten-minute drift trace loses lock 1113 times; first loss occurs at 247.808 seconds. |
| [A4_10000_64qam_offset_5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/A4_10000_64qam_offset_5/7446529.json) | sync_held | With the recovery profile and carrier correction off, 10 kHz 64-QAM loses lock once at +5 Hz residual offset. |
| [B1_10000_64qam_-20dB_10_100](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/B1_10000_64qam_-20dB_10_100/7446529.json) | sync_held | The recovery profile loses lock once during this 10 kHz 64-QAM -20 dB gain excursion. |
| [B1_10000_64qam_-20dB_1_100](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/B1_10000_64qam_-20dB_1_100/7446529.json) | sync_held | The recovery profile loses lock once during this 10 kHz 64-QAM -20 dB gain excursion. |
| [B1_24000_64qam_-20dB_1_100](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/B1_24000_64qam_-20dB_1_100/7446529.json) | sync_held | The recovery profile loses lock once during this 24 kHz 64-QAM -20 dB gain excursion. |
| [B1_24000_64qam_20dB_10_100](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/B1_24000_64qam_20dB_10_100/7446529.json) | sync_held | The recovery profile loses lock twice during this 24 kHz 64-QAM +20 dB gain excursion. |
| [B1_24000_64qam_20dB_10_1000](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/B1_24000_64qam_20dB_10_1000/7446529.json) | sync_held | The recovery profile loses lock once during this 24 kHz 64-QAM +20 dB gain excursion. |
| [D3_auction_flood](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/D3_auction_flood/7446529.json) | no_starvation | Policy conflict: strict bid priority permits starvation during an endless higher-bid flood; Adam rejected increasing priority with age. No cross-key expiry/decay interval is approved. |
| [D6_key_rotation](https://github.com/adamdeprince/goblin-cannon/blob/main/results/aead/D6_key_rotation/7446529.json) | rotation_supported | AES-256-GCM, authenticated key IDs, durable epochs and restart negotiation are implemented; overlapping receive keys and coordinated mid-stream old-key retirement are not. |

## Simulated channel open thresholds

All unapproved thresholds remain `THRESHOLD_TBD`; no acceptance threshold changed.

| Threshold | Proposed value | Reason |
| --- | --- | --- |
| A4.ber_delta: THRESHOLD_TBD | 0 absolute excess BER in the noise-free regression; select a confidence interval for noisy runs | No radio residual-offset budget or BER margin is specified. |
| C2.acquisition_seconds: THRESHOLD_TBD | one complete preamble/training/header plus one audio block | The configured startup lengths give a measurable lower bound; approval needed. |
| C3.recovery_frames: THRESHOLD_TBD | 2 frames after a new valid epoch preamble | The current stream needs an epoch preamble to reacquire; a deadline without one is undefined. |
| C4.pattern_ber_margin: THRESHOLD_TBD | a paired confidence interval, with its significance level selected by Adam | Equal finite-sample BER is not a statistical scrambler test. |
| D1.newest_latency_ms: THRESHOLD_TBD | one frame duration + 2.1 ms, as proposed in the brief | Needs agreement on whether serialization, FEC lookahead and startup are included. |
| D2.freshness_agreement_ms: THRESHOLD_TBD | compare paired freshness distributions; select a quantile margin | Equal survival fractions do not imply equal burst structure. |
| D2.target_survival_margin: THRESHOLD_TBD | select a confidence interval for channel calibration; direct erasures round to the nearest whole frame | A finite SNR grid cannot guarantee exactly 30%, 50%, or 80% channel survival. |
| D3.instrument_delay_ms: THRESHOLD_TBD | one frame duration + 2.1 ms | Strict bid priority and starvation freedom can conflict under sustained overload. |
| D6.rotation_loss_frames: THRESHOLD_TBD | one epoch startup plus the in-flight frame | There is no coordinated rotation protocol to measure yet. |
| E3.memory_growth_bytes: THRESHOLD_TBD | zero steady growth after warmup; choose an allocator/RSS allowance | Host RSS varies and includes harness allocations. |
| E3.queue_depth: THRESHOLD_TBD | configured ring capacity plus one pending auction bid | Must distinguish queue capacity from newest-message freshness. |
| E3.latency_change: THRESHOLD_TBD | a paired percentile tolerance chosen from baseline variability | Exact equality across different fading realizations is not a usable acceptance rule. |

## Simulated channel limits and reproducibility

- Only the six ordinary BPSK/QPSK/8-PSK coding configurations were rerun for current polar delivery.
- Configured 30 dB retains the uncalibrated nominal noise reference; measured sample power is reported. These are not actual-30-dB availability estimates.
- High-latitude presets are simulated channels, not observations of the 71-degree route. No recorded-band noise or soak was run.
- The 24 kHz two-path model extends beyond ITU-R F.1487's validated bandwidth scope.
- Physical radio/audio devices and network sockets are outside the paced software loopback.
- The combined quick selections, including both B5 profiles, exceed two minutes. Each selected invocation fits its tier, but this does not establish the whole quick tier's CI runtime.
- 12 independently repeated authenticated message runs have byte-identical canonical JSON. Host measurements are excluded.
- Base commit `44d318b7b279dd0546f00a4b4b295f51d7160260`; tested source SHA-256 `5b5d0b660023e9c7df281a4171786fe546cb36534cfda9e4bcb56823d6a9e7bf`. `SOURCE.json` and `source-snapshot.tar.gz` preserve the tested files.
- Report-description source SHA-256 `2f7fcf1115a8893e4aad78609919d67844af2af0df62cd3f1625686d6b85a155`. `METADATA_CORRECTION.json` records corrections to three stale CTR/CRC/Walsh labels. A byte comparison verifies that all compiled source and simulation controls match the measurement snapshot; metrics, assertions and measured-source IDs are unchanged. `REPORT_SOURCE.json` preserves the corrected formatter.
- `EXECUTION_*.json` preserves durations, host details and each exact selection. This is a selected campaign, not the complete A1–E4 matrix.
