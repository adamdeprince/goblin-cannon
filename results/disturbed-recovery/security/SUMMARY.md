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
| THRESHOLD_TBD | 10 |
| pass | 20 |
| xfail | 5 |

## Simulated channel coverage at a glance

| Group | Recorded cases | Expected failures | Open thresholds | Unavailable |
| --- | ---: | ---: | ---: | ---: |
| A1 | 0 | 0 | 0 | 0 |
| A2 | 0 | 0 | 0 | 0 |
| A3 | 0 | 0 | 0 | 0 |
| A4 | 2 | 1 | 1 | 0 |
| A5 | 0 | 0 | 0 | 0 |
| A6 | 0 | 0 | 0 | 0 |
| A7 | 0 | 0 | 0 | 0 |
| A8 | 3 | 0 | 0 | 0 |
| A9 | 0 | 0 | 0 | 0 |
| B1 | 5 | 1 | 0 | 0 |
| B2 | 0 | 0 | 0 | 0 |
| B3 | 0 | 0 | 0 | 0 |
| B4 | 3 | 0 | 0 | 0 |
| B5 | 0 | 0 | 0 | 0 |
| C1 | 0 | 0 | 0 | 0 |
| C2 | 11 | 1 | 9 | 0 |
| C3 | 0 | 0 | 0 | 0 |
| C4 | 1 | 0 | 0 | 0 |
| C5 | 0 | 0 | 0 | 0 |
| D1 | 0 | 0 | 0 | 0 |
| D2 | 0 | 0 | 0 | 0 |
| D3 | 1 | 1 | 0 | 0 |
| D4 | 4 | 0 | 0 | 0 |
| D5 | 0 | 0 | 0 | 0 |
| D6 | 2 | 1 | 0 | 0 |
| E1 | 3 | 0 | 0 | 0 |
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
| [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json) | assert / quick | xfail | 0.00346812 | 0.771778 | 20626.6 | — |
| [A4_10000_64qam_offset_5](A4_10000_64qam_offset_5/7446529.json) | assert / quick | THRESHOLD_TBD | 0.000115988 | 0.978479 | 26029.5 | — |

### Simulated channel A4 paired BER observations

| Case | Reference BER | BER minus reference | Matched duration | Acceptance |
| --- | --- | --- | --- | --- |
| A4_10000_64qam_drift_10min | 0.0 | 0.0034681209374910517 | True | THRESHOLD_TBD |

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
| [A8_cochannel_-10dB](A8_cochannel_-10dB/7446529.json) | assert / full | pass | — | — | 45.6 | 296 |
| [A8_cochannel_0dB](A8_cochannel_0dB/7446529.json) | assert / full | pass | — | — | 45.6 | 296 |
| [A8_cochannel_10dB](A8_cochannel_10dB/7446529.json) | assert / full | pass | — | — | 1140.8 | 6046 |

## Simulated channel group A9

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (3 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group B1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [B1_10000_64qam_-20dB_10_100](B1_10000_64qam_-20dB_10_100/7446529.json) | assert / quick | pass | 0.0019456 | 0.985714 | 25978.8 | — |
| [B1_10000_64qam_-20dB_1_100](B1_10000_64qam_-20dB_1_100/7446529.json) | assert / quick | pass | 0.000430276 | 0.992857 | 26168.1 | — |
| [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json) | assert / quick | xfail | 0.000263574 | 0.964179 | 61686.5 | — |
| [B1_24000_64qam_20dB_10_100](B1_24000_64qam_20dB_10_100/7446529.json) | assert / quick | pass | 0.00116158 | 0.976119 | 62452.7 | — |
| [B1_24000_64qam_20dB_10_1000](B1_24000_64qam_20dB_10_1000/7446529.json) | assert / quick | pass | 0.000841948 | 0.970149 | 62069.6 | — |

### Simulated channel B1 affected-frame errors

Frames are selected conservatively by audio-block and RRC-support overlap with the AGC excursion; full selection parameters are in JSON.

| Case | Affected frames | Affected frame error rate |
| --- | --- | --- |
| B1_10000_64qam_-20dB_10_100 | 11 | 0.18181818181818182 |
| B1_10000_64qam_-20dB_1_100 | 11 | 0.09090909090909091 |
| B1_24000_64qam_-20dB_1_100 | 25 | 0.48 |
| B1_24000_64qam_20dB_10_100 | 26 | 0.3076923076923077 |
| B1_24000_64qam_20dB_10_1000 | 177 | 0.05649717514124294 |

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
| [B4_jitter](B4_jitter/7446529.json) | assert / quick | pass | — | — | 84 | 379 |
| [B4_overrun](B4_overrun/7446529.json) | assert / quick | pass | — | — | 348 | 1616 |
| [B4_underrun](B4_underrun/7446529.json) | assert / quick | pass | — | — | 348 | 1616 |

## Simulated channel group B5

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (156 declared cases) | — | not_run | — | — | — | — |

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
| [C2_10000_acquire_0dB](C2_10000_acquire_0dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0.0211208 | 0.164286 | 1401.35 | — |
| [C2_10000_acquire_10dB](C2_10000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 8785.82 | — |
| [C2_10000_acquire_3dB](C2_10000_acquire_3dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0.00151532 | 0.892857 | 7839.09 | — |
| [C2_10000_acquire_6dB](C2_10000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 8785.82 | — |
| [C2_10000_cw_preamble](C2_10000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 8785.82 | — |
| [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json) | assert / quick | xfail | — | 0 | 0 | — |
| [C2_24000_acquire_10dB](C2_24000_acquire_10dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 21328.3 | — |
| [C2_24000_acquire_3dB](C2_24000_acquire_3dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0.0349616 | 0.041791 | 833.022 | — |
| [C2_24000_acquire_6dB](C2_24000_acquire_6dB/7446529.json) | assert / quick | THRESHOLD_TBD | 0.00418635 | 0.710448 | 15135.1 | — |
| [C2_24000_cw_preamble](C2_24000_cw_preamble/7446529.json) | assert / quick | THRESHOLD_TBD | 0 | 1 | 21328.3 | — |
| [C2_noise_10min](C2_noise_10min/7446529.json) | assert / quick | pass | — | — | 0 | — |

## Simulated channel group C3

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (6 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group C4

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [C4_generated_messages](C4_generated_messages/7446529.json) | assert / quick | pass | — | — | — | — |

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
| Not run (1 declared cases) | — | not_run | — | — | — | — |

## Simulated channel group D6

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| [D6_crypto_errors_replay_restart](D6_crypto_errors_replay_restart/7446529.json) | assert / full | pass | — | — | — | — |
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

- **xfail** — With warm recovery and elapsed-time prediction, 10 kHz 64-QAM loses lock 1112 times in the ten-minute residual-drift trace; first loss is at 304 s. Carrier correction remains off.
  Cases: [A4_10000_64qam_drift_10min](A4_10000_64qam_drift_10min/7446529.json).
- **xfail** — With warm recovery and elapsed-time prediction, 24 kHz 64-QAM loses lock once in the -20 dB / 1 ms attack / 100 ms decay trace.
  Cases: [B1_24000_64qam_-20dB_1_100](B1_24000_64qam_-20dB_1_100/7446529.json).
- **xfail** — At the requested low SNR, the receiver detects the preamble but loses lock without validating a header.
  Cases: [C2_24000_acquire_0dB](C2_24000_acquire_0dB/7446529.json).
- **xfail** — Policy conflict: strict bid priority permits starvation during an endless higher-bid flood; Adam rejected increasing priority with age. No cross-key expiry/decay interval is approved.
  Cases: [D3_auction_flood](D3_auction_flood/7446529.json).
- **xfail** — Both 25-byte and fiber-selected 13-byte authenticated headers retain key IDs, full GCM tags and durable epochs; two-key overlap and coordinated mid-stream retirement remain unimplemented.
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
- D6 audits production AES-256-GCM tampering, replay and persisted restart epochs. A8 measures authentication rejection through the simulated RF path. Full A1-rate coverage and coordinated key rotation remain open.
- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.

See [TESTING.md](../../../TESTING.md) and [source audit/questions](../../../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 5 / 5 | 0.775 | 1800 | yes |
| quick / selected rerun | 30 / 30 | 37.186 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
