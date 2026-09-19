# Goblin Cannon simulated channel recovery findings

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

All measurements use a simulated channel. No radio transmission, physical audio device, or route availability measurement is represented. Carrier correction is off; adaptive equalization is on. Open acceptance margins remain `THRESHOLD_TBD`.

## Simulated channel changes

1. **Recover during a continuous stream.** Optional acquisition/training markers recur every configured number of RF frames. Absolute frame counters let the receiver resume convolutional decoding and seek the continuous AES-CTR stream without restarting the transmitter or reusing its initial keystream. Partial messages emit gap events. The campaign uses one marker per 16 frames.
2. **Protect a shorter header.** A 16-byte epoch/counter/CRC header uses rate-1/2 K=7 coding plus known training probes: 166 QPSK symbols instead of the legacy 384, a 56.8% reduction. Mode, pilot cadence and frame size stay fiber configured and are bound by the header CRC. Training and acquisition are additional airtime.
3. **Update the equalizer support.** Shadow NLMS candidates allow periodic reselection of sparse RLS coefficients. The optional T/2 input uses two matched samples per symbol while retaining the declared symbol span. The campaign reselects after 256 reliable updates. No frequency tracker was added.
4. **Measure useful delivery.** The production auction/framer/FEC/crypto/modem/sink path reports delivered useful bits, messages delivered/created and delivered/framed, freshness, delivery silence, RF recovery and terminal unrecovered intervals. Raw RF observations remain separate.
5. **Retain longer independent runs.** Three seeds cover both bandwidths, QPSK/16-QAM/64-QAM and all three high-latitude presets. Quiet/moderate/disturbed durations are 6000/300/100 seconds per seed. Every sample and message is counted; exact sample-clock histograms replace per-message JSON vectors.

All four wire/equalizer settings are optional and exposed over the fiber gRPC control service. Defaults preserve the legacy waveform for matched A/B comparisons. Timestamp-enabled late joining still requires initial session validation; a later CRC header cannot replace it.

## Simulated channel principal findings

- At 10 kHz in the long quiet-channel traces, 16-QAM delivers **2.655–2.661 kbit/s**, ahead of 64-QAM at **2.173–2.180 kbit/s**. QPSK delivers **1.758–1.763 kbit/s** with fewer losses.
- At 24 kHz on the quiet preset, QPSK delivers **3.006–3.007 kbit/s**, with **99.96–99.98%** of framed messages delivered. 16-QAM delivers **2.891–2.893 kbit/s**; 64-QAM delivers **2.119–2.129 kbit/s**.
- Moderate fading remains lossy: 24 kHz QPSK delivers **799–834 bit/s** and **36.5–38.1%** of framed messages. On the disturbed preset, it delivers only **9.68–14.32 bit/s**, with silence as long as **22.305 seconds**. All three 10 kHz constellations deliver zero useful messages in the disturbed traces.
- Recovery is a useful improvement, but these results do not establish a dependable high-latitude service. Freshness and outage acceptance targets remain open.

## Simulated channel validation

- **17/17 CTest entries** passed, including the **11 Python harness checks**, which also passed separately. New C++ regressions cover chunk boundaries, all primary constellations at both bandwidths, continuous CTR seeking, all three punctured FEC rates, late joining and dropout recovery through the shared simulator. Existing tests with carrier correction enabled retain their original regression scope.
- **9,920 canonical cases:** 99 THRESHOLD_TBD, 9,721 characterized, 82 pass, 5 unavailable, 13 xfail. Characterizations and open thresholds are not passes.
- The original quick/full matrix retains all ten constellations, three FEC rates, both bandwidths, every preset and every SNR point. A/B screens contain 540 cases; longer production-message runs contain 54 cases.
- E1 repeats all three representative cases byte-identically. Both acquisition assertions previously failing at 24 kHz and 0/3 dB now pass with the recovery profile; acquisition-time margins remain open. All twelve ±50 ppm frame-boundary assertions pass.
- A9 now passes its staleness assertion after 2-second, 30-second and 300-second dropouts. The first validated headers after signal return arrive in **171 ms, 20 ms and 318 ms**, respectively; **39, 58 and 47 correct messages** are delivered after return. These declared seeded observations do not establish an unapproved recovery-time acceptance threshold.
- The manual four-hour soak was not rerun. E4 remains unavailable because no recordings exist. Conditional C5/D5 features remain unavailable.

D1 retains its existing offered stream: the 1.5×/3×/10× labels reference nominal payload capacity after pilots and FEC, before recurring-marker airtime. The resulting overload is higher relative to the recovery profile's complete-waveform capacity. It remains a stress test; exact load-factor calibration including markers is an open harness limitation.

## Simulated channel short A/B comparisons

Useful application bits/s after production FEC and framing. Each cell is the range over seeds 7446529, 7446530 and 7446531, each retaining ten simulated seconds at 30 dB nominal SNR. All five variants use the same delay-spanning equalizer geometry. The variants add features cumulatively, so these measurements include acquisition/training airtime and startup.

| Bandwidth / modulation / preset | Legacy | Compact header | + Recurring markers | + Tap reselection | + T/2 input |
| --- | ---: | ---: | ---: | ---: | ---: |
| 10 kHz / QPSK / 4-QAM / quiet | [1,077.60–2,239.20](E2_recovery_10000_qpsk_high_lat_quiet_legacy/7446529.json) | [1,085.60–2,247.20](E2_recovery_10000_qpsk_high_lat_quiet_compact/7446529.json) | [1,397.60–1,506.40](E2_recovery_10000_qpsk_high_lat_quiet_recovery/7446529.json) | [1,397.60–1,506.40](E2_recovery_10000_qpsk_high_lat_quiet_reselect/7446529.json) | [1,397.60–1,506.40](E2_recovery_10000_qpsk_high_lat_quiet_fractional/7446529.json) |
| 10 kHz / QPSK / 4-QAM / moderate | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_moderate_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_moderate_compact/7446529.json) | [56.00–121.60](E2_recovery_10000_qpsk_high_lat_moderate_recovery/7446529.json) | [39.20–118.40](E2_recovery_10000_qpsk_high_lat_moderate_reselect/7446529.json) | [57.60–137.60](E2_recovery_10000_qpsk_high_lat_moderate_fractional/7446529.json) |
| 10 kHz / QPSK / 4-QAM / disturbed | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_disturbed_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_disturbed_compact/7446529.json) | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_disturbed_recovery/7446529.json) | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_disturbed_reselect/7446529.json) | [0.00–0.00](E2_recovery_10000_qpsk_high_lat_disturbed_fractional/7446529.json) |
| 10 kHz / 16-QAM / quiet | [230.40–811.20](E2_recovery_10000_16qam_high_lat_quiet_legacy/7446529.json) | [249.60–1,266.40](E2_recovery_10000_16qam_high_lat_quiet_compact/7446529.json) | [2,018.40–2,087.20](E2_recovery_10000_16qam_high_lat_quiet_recovery/7446529.json) | [2,061.60–2,100.00](E2_recovery_10000_16qam_high_lat_quiet_reselect/7446529.json) | [2,061.60–2,122.40](E2_recovery_10000_16qam_high_lat_quiet_fractional/7446529.json) |
| 10 kHz / 16-QAM / moderate | [0.00–0.00](E2_recovery_10000_16qam_high_lat_moderate_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_16qam_high_lat_moderate_compact/7446529.json) | [0.00–67.20](E2_recovery_10000_16qam_high_lat_moderate_recovery/7446529.json) | [0.00–60.80](E2_recovery_10000_16qam_high_lat_moderate_reselect/7446529.json) | [3.20–48.00](E2_recovery_10000_16qam_high_lat_moderate_fractional/7446529.json) |
| 10 kHz / 16-QAM / disturbed | [0.00–0.00](E2_recovery_10000_16qam_high_lat_disturbed_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_16qam_high_lat_disturbed_compact/7446529.json) | [0.00–0.00](E2_recovery_10000_16qam_high_lat_disturbed_recovery/7446529.json) | [0.00–0.00](E2_recovery_10000_16qam_high_lat_disturbed_reselect/7446529.json) | [0.00–0.00](E2_recovery_10000_16qam_high_lat_disturbed_fractional/7446529.json) |
| 10 kHz / 64-QAM / quiet | [38.40–366.40](E2_recovery_10000_64qam_high_lat_quiet_legacy/7446529.json) | [36.00–373.60](E2_recovery_10000_64qam_high_lat_quiet_compact/7446529.json) | [1,334.40–1,688.80](E2_recovery_10000_64qam_high_lat_quiet_recovery/7446529.json) | [1,540.80–1,823.20](E2_recovery_10000_64qam_high_lat_quiet_reselect/7446529.json) | [1,572.00–1,816.00](E2_recovery_10000_64qam_high_lat_quiet_fractional/7446529.json) |
| 10 kHz / 64-QAM / moderate | [0.00–0.00](E2_recovery_10000_64qam_high_lat_moderate_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_64qam_high_lat_moderate_compact/7446529.json) | [0.00–6.40](E2_recovery_10000_64qam_high_lat_moderate_recovery/7446529.json) | [0.00–6.40](E2_recovery_10000_64qam_high_lat_moderate_reselect/7446529.json) | [0.00–9.60](E2_recovery_10000_64qam_high_lat_moderate_fractional/7446529.json) |
| 10 kHz / 64-QAM / disturbed | [0.00–0.00](E2_recovery_10000_64qam_high_lat_disturbed_legacy/7446529.json) | [0.00–0.00](E2_recovery_10000_64qam_high_lat_disturbed_compact/7446529.json) | [0.00–0.00](E2_recovery_10000_64qam_high_lat_disturbed_recovery/7446529.json) | [0.00–0.00](E2_recovery_10000_64qam_high_lat_disturbed_reselect/7446529.json) | [0.00–0.00](E2_recovery_10000_64qam_high_lat_disturbed_fractional/7446529.json) |
| 24 kHz / QPSK / 4-QAM / quiet | [951.20–3,088.80](E2_recovery_24000_qpsk_high_lat_quiet_legacy/7446529.json) | [1,490.40–3,093.60](E2_recovery_24000_qpsk_high_lat_quiet_compact/7446529.json) | [2,352.80–2,356.00](E2_recovery_24000_qpsk_high_lat_quiet_recovery/7446529.json) | [2,352.80–2,356.00](E2_recovery_24000_qpsk_high_lat_quiet_reselect/7446529.json) | [2,352.80–2,356.00](E2_recovery_24000_qpsk_high_lat_quiet_fractional/7446529.json) |
| 24 kHz / QPSK / 4-QAM / moderate | [0.00–76.80](E2_recovery_24000_qpsk_high_lat_moderate_legacy/7446529.json) | [0.00–86.40](E2_recovery_24000_qpsk_high_lat_moderate_compact/7446529.json) | [496.00–752.80](E2_recovery_24000_qpsk_high_lat_moderate_recovery/7446529.json) | [582.40–783.20](E2_recovery_24000_qpsk_high_lat_moderate_reselect/7446529.json) | [591.20–978.40](E2_recovery_24000_qpsk_high_lat_moderate_fractional/7446529.json) |
| 24 kHz / QPSK / 4-QAM / disturbed | [0.00–0.00](E2_recovery_24000_qpsk_high_lat_disturbed_legacy/7446529.json) | [0.00–7.20](E2_recovery_24000_qpsk_high_lat_disturbed_compact/7446529.json) | [0.00–7.20](E2_recovery_24000_qpsk_high_lat_disturbed_recovery/7446529.json) | [6.40–8.00](E2_recovery_24000_qpsk_high_lat_disturbed_reselect/7446529.json) | [6.40–12.00](E2_recovery_24000_qpsk_high_lat_disturbed_fractional/7446529.json) |
| 24 kHz / 16-QAM / quiet | [0.00–676.00](E2_recovery_24000_16qam_high_lat_quiet_legacy/7446529.json) | [0.00–280.80](E2_recovery_24000_16qam_high_lat_quiet_compact/7446529.json) | [2,215.20–2,292.80](E2_recovery_24000_16qam_high_lat_quiet_recovery/7446529.json) | [2,139.20–2,264.00](E2_recovery_24000_16qam_high_lat_quiet_reselect/7446529.json) | [2,232.80–2,250.40](E2_recovery_24000_16qam_high_lat_quiet_fractional/7446529.json) |
| 24 kHz / 16-QAM / moderate | [0.00–0.00](E2_recovery_24000_16qam_high_lat_moderate_legacy/7446529.json) | [0.00–0.00](E2_recovery_24000_16qam_high_lat_moderate_compact/7446529.json) | [104.80–178.40](E2_recovery_24000_16qam_high_lat_moderate_recovery/7446529.json) | [181.60–199.20](E2_recovery_24000_16qam_high_lat_moderate_reselect/7446529.json) | [180.80–237.60](E2_recovery_24000_16qam_high_lat_moderate_fractional/7446529.json) |
| 24 kHz / 16-QAM / disturbed | [0.00–0.00](E2_recovery_24000_16qam_high_lat_disturbed_legacy/7446529.json) | [0.00–0.00](E2_recovery_24000_16qam_high_lat_disturbed_compact/7446529.json) | [0.00–0.00](E2_recovery_24000_16qam_high_lat_disturbed_recovery/7446529.json) | [0.00–2.40](E2_recovery_24000_16qam_high_lat_disturbed_reselect/7446529.json) | [0.00–3.20](E2_recovery_24000_16qam_high_lat_disturbed_fractional/7446529.json) |
| 24 kHz / 64-QAM / quiet | [0.00–204.00](E2_recovery_24000_64qam_high_lat_quiet_legacy/7446529.json) | [0.00–213.60](E2_recovery_24000_64qam_high_lat_quiet_compact/7446529.json) | [1,492.80–1,573.60](E2_recovery_24000_64qam_high_lat_quiet_recovery/7446529.json) | [1,625.60–1,824.80](E2_recovery_24000_64qam_high_lat_quiet_reselect/7446529.json) | [1,606.40–1,868.00](E2_recovery_24000_64qam_high_lat_quiet_fractional/7446529.json) |
| 24 kHz / 64-QAM / moderate | [0.00–0.00](E2_recovery_24000_64qam_high_lat_moderate_legacy/7446529.json) | [0.00–0.00](E2_recovery_24000_64qam_high_lat_moderate_compact/7446529.json) | [5.60–37.60](E2_recovery_24000_64qam_high_lat_moderate_recovery/7446529.json) | [25.60–51.20](E2_recovery_24000_64qam_high_lat_moderate_reselect/7446529.json) | [16.00–64.00](E2_recovery_24000_64qam_high_lat_moderate_fractional/7446529.json) |
| 24 kHz / 64-QAM / disturbed | [0.00–0.00](E2_recovery_24000_64qam_high_lat_disturbed_legacy/7446529.json) | [0.00–0.00](E2_recovery_24000_64qam_high_lat_disturbed_compact/7446529.json) | [0.00–0.00](E2_recovery_24000_64qam_high_lat_disturbed_recovery/7446529.json) | [0.00–0.00](E2_recovery_24000_64qam_high_lat_disturbed_reselect/7446529.json) | [0.00–0.00](E2_recovery_24000_64qam_high_lat_disturbed_fractional/7446529.json) |

Recurring markers substantially improve useful high-order-QAM delivery after lock loss. Stable quiet-channel QPSK spends airtime on markers it seldom needs and can deliver less useful data. Tap reselection and T/2 sampling help some faster-fading cases; improvements are not uniform. Higher constellation order is not automatically higher useful throughput.

## Simulated channel longer production-message runs

Ranges below are minimum–maximum across independent seeds, not confidence intervals. Source offers 100 updates/s to the one-winner auction. Delivered/framed excludes updates superseded before framing; delivered/created is separately retained in every JSON. The generated integer payload size changes with message identity, so short and long campaigns are not a fixed-payload goodput comparison. Freshness is creation-to-delivery sample-clock time, including transmission, modem delays, startup and buffering. Silence includes startup and the right-censored end of the run.

| Bandwidth / modulation / preset | Seconds per seed | Useful bit/s | Delivered / framed | Freshness p99.9 ms | Maximum silence s | Seed records |
| --- | ---: | ---: | ---: | ---: | ---: | --- |
| 10 kHz / QPSK / 4-QAM / quiet | 6000 | 1,758.45–1,763.12 | 98.24–98.52% | 101.00–101.00 | 0.33–0.53 | [7446529](E2_polar_long_10000_qpsk_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_10000_qpsk_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_10000_qpsk_high_lat_quiet/7446531.json) |
| 10 kHz / QPSK / 4-QAM / moderate | 300 | 86.40–104.19 | 5.79–6.98% | 108.00–111.00 | 5.06–5.87 | [7446529](E2_polar_long_10000_qpsk_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_10000_qpsk_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_10000_qpsk_high_lat_moderate/7446531.json) |
| 10 kHz / QPSK / 4-QAM / disturbed | 100 | 0.00–0.00 | 0.00–0.00% | Unobserved | 100.00–100.00 | [7446529](E2_polar_long_10000_qpsk_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_10000_qpsk_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_10000_qpsk_high_lat_disturbed/7446531.json) |
| 10 kHz / 16-QAM / quiet | 6000 | 2,654.70–2,661.04 | 95.28–95.51% | 81.00–81.00 | 0.55–0.62 | [7446529](E2_polar_long_10000_16qam_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_10000_16qam_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_10000_16qam_high_lat_quiet/7446531.json) |
| 10 kHz / 16-QAM / moderate | 300 | 16.64–21.55 | 0.78–1.01% | 19.00–19.00 | 11.49–28.42 | [7446529](E2_polar_long_10000_16qam_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_10000_16qam_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_10000_16qam_high_lat_moderate/7446531.json) |
| 10 kHz / 16-QAM / disturbed | 100 | 0.00–0.00 | 0.00–0.00% | Unobserved | 100.00–100.00 | [7446529](E2_polar_long_10000_16qam_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_10000_16qam_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_10000_16qam_high_lat_disturbed/7446531.json) |
| 10 kHz / 64-QAM / quiet | 6000 | 2,173.06–2,179.93 | 78.00–78.24% | 77.00–77.00 | 2.18–2.38 | [7446529](E2_polar_long_10000_64qam_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_10000_64qam_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_10000_64qam_high_lat_quiet/7446531.json) |
| 10 kHz / 64-QAM / moderate | 300 | 1.07–1.71 | 0.05–0.08% | 21.00–24.00 | 77.06–118.68 | [7446529](E2_polar_long_10000_64qam_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_10000_64qam_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_10000_64qam_high_lat_moderate/7446531.json) |
| 10 kHz / 64-QAM / disturbed | 100 | 0.00–0.00 | 0.00–0.00% | Unobserved | 100.00–100.00 | [7446529](E2_polar_long_10000_64qam_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_10000_64qam_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_10000_64qam_high_lat_disturbed/7446531.json) |
| 24 kHz / QPSK / 4-QAM / quiet | 6000 | 3,006.49–3,007.11 | 99.96–99.98% | 42.00–42.00 | 0.15–0.18 | [7446529](E2_polar_long_24000_qpsk_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_24000_qpsk_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_24000_qpsk_high_lat_quiet/7446531.json) |
| 24 kHz / QPSK / 4-QAM / moderate | 300 | 798.91–833.71 | 36.53–38.12% | 54.00–54.00 | 1.10–1.58 | [7446529](E2_polar_long_24000_qpsk_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_24000_qpsk_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_24000_qpsk_high_lat_moderate/7446531.json) |
| 24 kHz / QPSK / 4-QAM / disturbed | 100 | 9.68–14.32 | 0.59–0.86% | 30.00–85.00 | 14.00–22.30 | [7446529](E2_polar_long_24000_qpsk_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_24000_qpsk_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_24000_qpsk_high_lat_disturbed/7446531.json) |
| 24 kHz / 16-QAM / quiet | 6000 | 2,891.29–2,893.02 | 95.83–95.89% | 38.00–38.00 | 0.44–0.69 | [7446529](E2_polar_long_24000_16qam_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_24000_16qam_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_24000_16qam_high_lat_quiet/7446531.json) |
| 24 kHz / 16-QAM / moderate | 300 | 174.13–191.57 | 7.97–8.77% | 46.00–46.00 | 3.51–4.06 | [7446529](E2_polar_long_24000_16qam_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_24000_16qam_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_24000_16qam_high_lat_moderate/7446531.json) |
| 24 kHz / 16-QAM / disturbed | 100 | 0.00–1.28 | 0.00–0.08% | 20.00–20.00 (1/3 runs observed) | 44.75–100.00 | [7446529](E2_polar_long_24000_16qam_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_24000_16qam_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_24000_16qam_high_lat_disturbed/7446531.json) |
| 24 kHz / 64-QAM / quiet | 6000 | 2,118.90–2,128.85 | 70.20–70.54% | 36.00–36.00 | 2.78–2.96 | [7446529](E2_polar_long_24000_64qam_high_lat_quiet/7446529.json) / [7446530](E2_polar_long_24000_64qam_high_lat_quiet/7446530.json) / [7446531](E2_polar_long_24000_64qam_high_lat_quiet/7446531.json) |
| 24 kHz / 64-QAM / moderate | 300 | 25.49–31.39 | 1.16–1.44% | 10.00–45.00 | 9.83–15.95 | [7446529](E2_polar_long_24000_64qam_high_lat_moderate/7446529.json) / [7446530](E2_polar_long_24000_64qam_high_lat_moderate/7446530.json) / [7446531](E2_polar_long_24000_64qam_high_lat_moderate/7446531.json) |
| 24 kHz / 64-QAM / disturbed | 100 | 0.00–0.00 | 0.00–0.00% | Unobserved | 100.00–100.00 | [7446529](E2_polar_long_24000_64qam_high_lat_disturbed/7446529.json) / [7446530](E2_polar_long_24000_64qam_high_lat_disturbed/7446530.json) / [7446531](E2_polar_long_24000_64qam_high_lat_disturbed/7446531.json) |

These long durations satisfy the two F.1487 test-length terms at the recorded **BER 1e-3 planning target**. They are production-message characterizations, not BER 1e-5 certification or established operating limits. The original A1 grid remains a ten-second screen. F.1487’s approximately 12 kHz model scope makes the 24 kHz tests an explicit extrapolation. [ITU-R F.1487, Annex 3](https://www.itu.int/dms_pubrec/itu-r/rec/f/R-REC-F.1487-0-200005-I!!PDF-E.pdf).

## Simulated channel added processing and buffering

**All 12 B5 configurations pass the 2.1 ms added-processing/buffering assertion on both hosts.** The quiet-host rerun on **naamah (AVX2)** records added p99.9 of **0.962–1.110 ms**, compared with **0.961–1.085 ms** on avx10 (AVX-512). All 17 CTest entries passed on naamah before its twelve serial timing runs. [Quiet-host measurements, comparison and build metadata](naamah-latency/COMPARISON.md).

No physical audio hardware is included. Host timing is non-canonical and is kept outside the seeded byte-equality check. Each measured message is paired with a one-sample simulated reference before subtracting intrinsic transmission/modem/startup time; percentiles are not subtracted from one another. The table below preserves the original **avx10 baseline**, measured serially before other campaign jobs.

| Configuration | Added p50 ms | Added p99 ms | Added p99.9 ms | Added max ms | Total p99.9 ms | Intrinsic reference p99.9 ms |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 0.315 | 0.960 | 0.989 | 0.989 | 51.004 | 50.313 |
| [B5_10000_16qam_polar_span_null](B5_10000_16qam_polar_span_null/7446529.host.json) | 0.316 | 0.959 | 0.976 | 0.976 | 80.004 | 79.188 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 0.376 | 0.942 | 0.989 | 0.989 | 47.007 | 46.938 |
| [B5_10000_64qam_polar_span_null](B5_10000_64qam_polar_span_null/7446529.host.json) | 0.375 | 0.936 | 0.981 | 0.981 | 76.009 | 75.813 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 0.461 | 0.959 | 0.961 | 0.961 | 70.001 | 69.187 |
| [B5_10000_qpsk_polar_span_null](B5_10000_qpsk_polar_span_null/7446529.host.json) | 0.440 | 0.942 | 0.968 | 0.968 | 99.001 | 98.313 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 0.438 | 0.953 | 1.025 | 1.026 | 21.325 | 20.958 |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.host.json) | 0.401 | 1.010 | 1.085 | 1.085 | 37.031 | 36.104 |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | 0.801 | 0.996 | 1.043 | 1.072 | 20.020 | 19.521 |
| [B5_24000_64qam_polar_span_null](B5_24000_64qam_polar_span_null/7446529.host.json) | 0.769 | 0.998 | 1.074 | 1.074 | 35.022 | 34.708 |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | 0.312 | 0.967 | 1.009 | 1.017 | 26.018 | 25.187 |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.host.json) | 0.315 | 0.989 | 1.054 | 1.054 | 41.020 | 40.333 |

Passing the added-processing allowance does not imply a 2.1 ms source-to-sink link. The long-run freshness table includes tens of milliseconds of transmission and modem/training delay even in quiet conditions. Stage-call timings and analytical modem residence estimates are in [SUMMARY.md](SUMMARY.md).

The naamah rerun uses committed source `86d72bb8ecb63343d8eb32286ed810a59163ac97`, with the same tested source digest as the avx10 campaign. All twelve canonical results match across hosts after excluding only revision and ISA metadata. Host timing observations remain separate and differ between runs. The twelve follow-up records live in `naamah-latency/`; the original 9,920-case ledger and its runtime findings remain unchanged.

## Simulated channel defects found

- **sync_held** — [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json), seed 7446529: With the recovery profile and carrier correction off, the 10 kHz 64-QAM ten-minute drift trace loses lock 1113 times; first loss occurs at 247.808 seconds.
- **sync_held** — [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446529.json), seed 7446529: With the recovery profile and carrier correction off, 10 kHz 64-QAM loses lock once at +5 Hz residual offset.
- **authenticated_delivery** — [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json), seed 7446529: Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
- **no_corrupt_messages** — [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json), seed 7446529: With a co-channel interferer at -10 dB SIR, the message sink receives payloads outside the expected source stream; authenticated delivery is not implemented.
- **authenticated_delivery** — [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json), seed 7446529: Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
- **authenticated_delivery** — [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json), seed 7446529: Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
- **sync_held** — [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446529.json), seed 7446529: The recovery profile loses lock once during this 10 kHz 64-QAM -20 dB gain excursion.
- **sync_held** — [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446529.json), seed 7446529: The recovery profile loses lock once during this 10 kHz 64-QAM -20 dB gain excursion.
- **sync_held** — [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json), seed 7446529: The recovery profile loses lock once during this 24 kHz 64-QAM -20 dB gain excursion.
- **sync_held** — [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446529.json), seed 7446529: The recovery profile loses lock twice during this 24 kHz 64-QAM +20 dB gain excursion.
- **sync_held** — [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446529.json), seed 7446529: The recovery profile loses lock once during this 24 kHz 64-QAM +20 dB gain excursion.
- **no_starvation** — [D3_auction_flood](D3_auction_flood/7446529.json), seed 7446529: Policy conflict: strict bid priority permits starvation during an endless higher-bid flood; Adam rejected increasing priority with age. No cross-key expiry/decay interval is approved.
- **authenticated_delivery** — [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json), seed 7446529: Production provides AES-CTR plus CRC, with no AEAD authentication or authentication-failure counter.
- **no_nonce_reuse** — [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json), seed 7446529: Restarting the production AES-CTR generator with the unchanged key and default counter repeats its keystream.
- **rotation_supported** — [D6_key_rotation](D6_key_rotation/7446529.json), seed 7446529: No coordinated mid-stream key-rotation and old-key retirement contract is exposed.

The seven new 64-QAM residual-offset/drift and gain-step failures retain the original sync-held assertion. They were reviewed and marked profile-specific xfail; no threshold was relaxed and no frequency tracker was added. Low-SNR acquisition and dropout-recovery improvements remove only the recovery profile’s obsolete expected failures. [The review ledger](EXPECTED_FAILURE_REVIEW.json) preserves original assertion states and proves that measurements did not change.

## Simulated channel runtime and provenance

| Selection | Cases executed | Wall seconds |
| --- | ---: | ---: |
| quick | 237 | 258.362 |
| latency-quick | 6 | 77.690 |
| latency-full | 6 | 79.776 |
| polar-screen | 540 | 120.102 |
| polar-long | 54 | 3152.625 |
| full-matrix | 9077 | 1127.282 |

Combined quick runtime: **336.052 s**, above 120 s. Combined full runtime including all independent polar repeats: **4479.784 s**, above 1,800 s. Splitting serial latency and CPU-heavy selections does not reset a tier budget. All specified samples, seeds and grid points were retained.
These sums cover the matrix selections. The separately recorded CTest run took **6.46 seconds** and includes the Python checks. The quick tier exceeds its budget even before those regression checks are added.

Tested base commit: `39b4fe468c4bea566d5698151eb47bb8b999d91c`. Tested source SHA-256: `ed6bc5eaa2c79850c88b9cb33e76e741c0df7f227c7b5d469d48a878796a1072`. The commit identifies the base revision; the digest and [source snapshot](source-snapshot.tar.gz) identify the working-tree implementation actually tested. [HOST.json](HOST.json), [CAMPAIGN.json](CAMPAIGN.json), [VALIDATION.json](VALIDATION.json), execution manifests and raw logs record the host, compiler, commands, exit statuses and selected parameter records. Original logs preserve failures observed before expectation review.

## Simulated channel open thresholds and decisions

Every proposed value remains unenforced. No acceptance target for route availability, moderate/disturbed useful goodput, delivered freshness or recovery outage has been approved. The results do not establish a dependable 71°N route. Exact STAC audit comparability remains unavailable; local lock uptime and one-second delivery-window usable time are explicitly labeled proxies.

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

Outstanding design questions and verified preset sources are in [QUESTIONS.md](../../tests/simulated_channel/QUESTIONS.md). Reproduction commands and impairment-stage guidance are in [TESTING.md](../../TESTING.md).
