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
| pass | 3 |

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
| B5 | 3 | 0 | 0 | 0 |
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
| Not run (582 declared cases) | — | not_run | — | — | — | — |

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
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | pass | — | — | 3111.33 | 5 |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.json) | assert / full | pass | — | — | 3107.33 | 6 |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.json) | assert / full | pass | — | — | 3107.33 | 10 |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

2.1 ms applies to added processing/buffering. The intrinsic reference replays the actual selected messages at their original creation times, through the production stack with one-sample blocks. Values are paired by message identity before computing percentiles.

| Case | Total p50 ms | Total p99.9 ms | Intrinsic reference p99.9 ms | Added p99.9 ms | Added max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | 5.001086000000043 | 5.095725000000106 | 4.666666666667041 | 0.7864329999999198 | 0.8312879999998746 | pass |
| [B5_24000_16qam_polar_span_null](B5_24000_16qam_polar_span_null/7446529.host.json) | 6.000828999999541 | 6.075550000000263 | 5.770833333334835 | 0.7216276666666133 | 0.7341006666665706 | pass |
| [B5_24000_qpsk_polar_span_null](B5_24000_qpsk_polar_span_null/7446529.host.json) | 9.999807999999888 | 10.063769000000278 | 9.979166666667538 | 0.8581126666666883 | 0.8590446666666427 | pass |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_24000_16qam_null | host_source_to_framer_ms | 0.0026550000002956153 | 0.012743999999287325 | 7.639581 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.000290999999874586 | 0.0018329999997845903 | 0.003647000000000719 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.01617099999950966 | 0.027743000000413076 | 0.030849000000721105 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.0006810000012791306 | 0.0015530000005981037 | 0.002555000000015184 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.8986110000002157 | 0.9978690000000002 | 1.012105 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.08338799999996205 | 0.13692899999995234 | 0.633179000000001 |
| B5_24000_16qam_polar_span_null | host_source_to_framer_ms | 0.0023540000002597594 | 0.011471999999734805 | 0.021641000000016675 |
| B5_24000_16qam_polar_span_null | host_intake_per_message_ms | 0.00024100000040050418 | 0.001251999998785891 | 0.0035869999999993407 |
| B5_24000_16qam_polar_span_null | host_tx_per_block_ms | 0.012093000000490406 | 0.03582799999968245 | 0.06080500000038569 |
| B5_24000_16qam_polar_span_null | host_channel_per_block_ms | 0.0005409999994654413 | 0.009808999999805224 | 0.020057999999600895 |
| B5_24000_16qam_polar_span_null | host_audio_wait_per_block_ms | 0.8685839999991174 | 0.9984089999999995 | 1.019019 |
| B5_24000_16qam_polar_span_null | host_rx_per_block_ms | 0.11808299999982452 | 0.18604199999927573 | 2.816370999999998 |
| B5_24000_qpsk_polar_span_null | host_source_to_framer_ms | 0.004408000000566403 | 0.011020999998834213 | 0.012413999999960623 |
| B5_24000_qpsk_polar_span_null | host_intake_per_message_ms | 0.0002909999992084522 | 0.0019240000002085367 | 0.003186000000000508 |
| B5_24000_qpsk_polar_span_null | host_tx_per_block_ms | 0.015047999999850958 | 0.027170999999270862 | 0.029636000000721197 |
| B5_24000_qpsk_polar_span_null | host_channel_per_block_ms | 0.0006810000001689076 | 0.0016229999997285915 | 0.0034469999992126077 |
| B5_24000_qpsk_polar_span_null | host_audio_wait_per_block_ms | 0.8746359999998177 | 0.9986410000000014 | 1.0172350000000001 |
| B5_24000_qpsk_polar_span_null | host_rx_per_block_ms | 0.10872600000055854 | 0.15715800000037916 | 2.9120320000000017 |

#### Simulated channel B5 transmission and modem residence

Analytical estimates explain the intrinsic reference; they are not used to subtract latency or gate the allowance. Message serialization includes coding and mean pilot duty. Byte/symbol alignment, actual pilot positions and startup remain in the separately reported reference.

| Case | Serialization p50 ms | TX RRC ms | RX RRC ms | Equalizer delay ms | Viterbi lookahead ms |
| --- | --- | --- | --- | --- | --- |
| B5_24000_16qam_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 0 | 0.9684244791666666 |
| B5_24000_16qam_polar_span_null | 2.8776041666666665 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 0.9684244791666666 |
| B5_24000_qpsk_polar_span_null | 5.755208333333333 | 0.20833333333333334 | 0.20833333333333334 | 1.0416666666666667 | 1.9368489583333333 |

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
| Not run (142 declared cases) | — | not_run | — | — | — | — |

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
| Not run (92 declared cases) | — | not_run | — | — | — | — |

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
| Not run (639 declared cases) | — | not_run | — | — | — | — |

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

See [TESTING.md](../../../../../goblin-cannon-refinement.AZmSt3/TESTING.md) and [source audit/questions](../../../../../goblin-cannon-refinement.AZmSt3/tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| full / selected rerun | 2 / 2 | 26.565 | 1800 | yes |
| quick / selected rerun | 1 / 1 | 13.001 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
