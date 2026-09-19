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
| B5 | 6 | 6 | 0 | 0 |
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
| Not run (36 declared cases) | — | not_run | — | — | — | — |

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
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json) | assert / quick | xfail | — | — | 3107.33 | 67 |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json) | assert / quick | xfail | — | — | 3107.33 | 63 |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json) | assert / quick | xfail | — | — | 3102.67 | 77 |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json) | assert / quick | xfail | — | — | 0 | — |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json) | assert / quick | xfail | — | — | 0 | — |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json) | assert / quick | xfail | — | — | 0 | — |

### Simulated channel B5 measured host loopback

Wall-clock source creation to sink delivery, paced with simulated audio blocks. These non-canonical observations include OS scheduling and CPU work; no physical audio device is represented.

| Case | p50 ms | p99 ms | p99.9 ms | Max ms | 2.1 ms assertion |
| --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](B5_10000_16qam_null/7446529.host.json) | 9.000114000000892 | 9.005693999999842 | 67.02319800000001 | 73.04490100000001 | xfail |
| [B5_10000_64qam_null](B5_10000_64qam_null/7446529.host.json) | 6.001123999999969 | 7.004301000000268 | 63.03239399999999 | 71.009935 | xfail |
| [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.host.json) | 16.000115999999842 | 17.001128999999615 | 77.01164 | 80.039443 | xfail |
| [B5_24000_16qam_null](B5_24000_16qam_null/7446529.host.json) | None | None | None | None | xfail |
| [B5_24000_64qam_null](B5_24000_64qam_null/7446529.host.json) | None | None | None | None | xfail |
| [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.host.json) | None | None | None | None | xfail |

#### Simulated channel B5 stage call durations

TX and RX include their framing/FEC/crypto work. Per-call durations do not add up to per-message latency; queue residence is included in end-to-end measurements.

| Case | Stage | p50 ms | p99.9 ms | Max ms |
| --- | --- | --- | --- | --- |
| B5_10000_16qam_null | host_intake_per_message_ms | 0.0003399999997100167 | 0.0012619999998353393 | 0.0023439999999999967 |
| B5_10000_16qam_null | host_tx_per_block_ms | 0.0018740000005124102 | 0.002715000000000356 | 0.0035870000000270963 |
| B5_10000_16qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0009319999998425033 | 0.0013629999999764664 |
| B5_10000_16qam_null | host_audio_wait_per_block_ms | 0.9754040000000685 | 0.9982870000000005 | 1.0165020000000007 |
| B5_10000_16qam_null | host_rx_per_block_ms | 0.02127000000129442 | 0.02512699999999979 | 0.2057079999999989 |
| B5_10000_64qam_null | host_intake_per_message_ms | 0.0004909999999913595 | 0.002474999998725025 | 0.0028049999999946174 |
| B5_10000_64qam_null | host_tx_per_block_ms | 0.0022250000002443926 | 0.005149999999787269 | 0.05465299999984907 |
| B5_10000_64qam_null | host_channel_per_block_ms | 0.0006820000000296034 | 0.0012830000000185748 | 0.0020029999998616432 |
| B5_10000_64qam_null | host_audio_wait_per_block_ms | 0.9660460000002757 | 1.048661999999645 | 1.9794120000007354 |
| B5_10000_64qam_null | host_rx_per_block_ms | 0.03033800000018516 | 0.04792100000017285 | 0.20829299999999829 |
| B5_10000_qpsk_null | host_intake_per_message_ms | 0.0003409999997927571 | 0.0014130000014489497 | 0.0025640000000000046 |
| B5_10000_qpsk_null | host_tx_per_block_ms | 0.001723000000453112 | 0.002924999999986966 | 0.0039570000001099 |
| B5_10000_qpsk_null | host_channel_per_block_ms | 0.0006819999995855142 | 0.0009519999997209538 | 0.0013519999999545007 |
| B5_10000_qpsk_null | host_audio_wait_per_block_ms | 0.9840600000003974 | 0.9984680000000024 | 1.019858 |
| B5_10000_qpsk_null | host_rx_per_block_ms | 0.013084999999968261 | 0.020187999998810824 | 0.20957600000000298 |
| B5_24000_16qam_null | host_intake_per_message_ms | 0.0002600000001962144 | 0.0018640000001290957 | 0.002333999999999995 |
| B5_24000_16qam_null | host_tx_per_block_ms | 0.00879699999956074 | 0.013064999999645721 | 0.019226000000038823 |
| B5_24000_16qam_null | host_channel_per_block_ms | 0.00040100000031628724 | 0.000761000000792933 | 0.0013320000000760501 |
| B5_24000_16qam_null | host_audio_wait_per_block_ms | 0.8101110000007239 | 0.9977859999999996 | 1.018576 |
| B5_24000_16qam_null | host_rx_per_block_ms | 0.18027099999998186 | 0.2591400000007127 | 1.6303419999994517 |
| B5_24000_64qam_null | host_intake_per_message_ms | 0.00027099999977409084 | 0.0021939999999999998 | 0.0022239999999951188 |
| B5_24000_64qam_null | host_tx_per_block_ms | 0.009096999999957944 | 0.013615999999938566 | 0.020208000000007664 |
| B5_24000_64qam_null | host_channel_per_block_ms | 0.00040999999928459374 | 0.0007709999998439798 | 0.001431999999995659 |
| B5_24000_64qam_null | host_audio_wait_per_block_ms | 0.8097910000000041 | 0.997866 | 1.018595 |
| B5_24000_64qam_null | host_rx_per_block_ms | 0.18029099999994358 | 0.26346799999998893 | 1.600364999999826 |
| B5_24000_qpsk_null | host_intake_per_message_ms | 0.00027100000110635847 | 0.0022050000000051195 | 0.002684999999999999 |
| B5_24000_qpsk_null | host_tx_per_block_ms | 0.008565999999987639 | 0.014177000000614726 | 0.019447000000005765 |
| B5_24000_qpsk_null | host_channel_per_block_ms | 0.00040100000031628724 | 0.0008110000000033368 | 0.001582999999999446 |
| B5_24000_qpsk_null | host_audio_wait_per_block_ms | 0.8100010000005042 | 0.9979869999999988 | 1.0254280000001614 |
| B5_24000_qpsk_null | host_rx_per_block_ms | 0.18062199999935302 | 0.30387399999999565 | 1.5595680000002332 |

## Simulated channel group C1

| Case | Kind / tier | Status | BER | Frame survival | Goodput bit/s | p99.9 ms |
| --- | --- | --- | ---: | ---: | ---: | ---: |
| Not run (2 declared cases) | — | not_run | — | — | — | — |

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
| Not run (32 declared cases) | — | not_run | — | — | — | — |

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

Offered wire bits are 1.5×, 3×, or 10× nominal steady payload capacity, including CRC, FEC and pilot overhead. Startup is included in measured delivery latency.

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
| Not run (4 declared cases) | — | not_run | — | — | — | — |

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
| Not run (9 declared cases) | — | not_run | — | — | — | — |

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

- **xfail** — Source-to-sink latency including startup and audio buffering exceeds the 2.1 ms allowance.
  Cases: [B5_10000_16qam_null](B5_10000_16qam_null/7446529.json), [B5_10000_64qam_null](B5_10000_64qam_null/7446529.json), [B5_10000_qpsk_null](B5_10000_qpsk_null/7446529.json).
- **xfail** — The 24 kHz / 19.2 ksymbol/s receiver stalls in training even for the clean control; no valid header is delivered.
  Cases: [B5_24000_16qam_null](B5_24000_16qam_null/7446529.json), [B5_24000_64qam_null](B5_24000_64qam_null/7446529.json), [B5_24000_qpsk_null](B5_24000_qpsk_null/7446529.json).

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

- Production modem, framing, scheduler and crypto behavior was not changed for this test brief.
- Carrier correction is disabled through the existing switch; this also disables its coupled phase PLL. The adaptive equalizer remains enabled.
- 24 kHz use of the F.1487 model is an extrapolation beyond that recommendation's approximately 12 kHz scope.
- A1 uses declared 10-second screening traces. The requested grids and long 600-second quick cases are not reduced to meet a runtime budget.
- BER excludes erased/unobserved bits: inspect bit observation fraction and frame survival alongside it. No acquisition is never reported as zero BER.
- Symbol-probe goodput counts correct RF-frame bits; message-probe goodput counts application bytes. They are labeled separately in JSON.
- Canonical sample-clock latency includes startup and audio buffering. B5's separate paced host observations include real CPU/OS scheduling through auction, framing, FEC, crypto and modem. Physical audio devices and network sockets are outside this simulated loopback.
- Usable-time is an explicitly labeled local one-second delivery-window proxy. Exact STAC comparability is unavailable pending audit definitions/standby instrumentation.
- Conditional unsupported features, missing recordings, unrun soak cases, and open thresholds are never counted as passes.
- D6 cannot count AEAD authentication failures at A1 error rates because production exposes AES-CTR/CRC only. Its replay check exercises captured framed messages at the deframer; it does not claim an encrypted RF replay audit with wall-clock timestamp validation.
- D1 includes both isolated auction service and a null-channel auction-to-radio-to-sink overload fixture at 10 kHz/QPSK/rate-1/2. D3 isolates auction service. Per-key newest-message and chronological-window latency observations are retained; unapproved delay margins remain open.

See [TESTING.md](../TESTING.md) and [source audit/questions](../tests/simulated_channel/QUESTIONS.md).

## Simulated channel runtime observations

| Tier / selection | Executed / selected cases | Seconds | Budget seconds | Within budget |
| --- | --- | ---: | ---: | --- |
| quick / selected rerun | 6 / 6 | 72.326 | 120 | yes |
Execution wall time is a non-canonical host observation. An overrun preserves all durations, sample counts and grid points; a selected rerun is not a replacement tier timing.
