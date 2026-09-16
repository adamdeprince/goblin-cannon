# Goblin Cannon simulated channel — fixes #2–5

Clock/gain recovery, delayed adaptive equalization, transmit buffering, and source/receiver freshness handling are implemented. The polar channel remains a limitation: QPSK now survives the quiet screening traces, while moderate/disturbed reception remains unresolved.

Carrier correction is **off** in the acceptance matrix. The equalizer adjusts phase without estimating or accumulating a carrier frequency. Both endpoints receive matching settings over fiber gRPC.

## Simulated channel changes

| Finding | Change |
| --- | --- |
| #2 Clock and gain tracking | Fractional matched-filter timing with Gardner sample-clock recovery; supervised positive-real gain correction through AGC steps; protected adaptation during ambiguous level changes. |
| #3 Fading and multipath | Sparse recursive least-squares tracking, longer configurable feedforward/feedback spans, and a decision delay for precursor echoes. Phase correction applies to the feedforward signal; feedback decisions stay in the corrected constellation. |
| #4 Processing/buffering | Drain ready transmit audio before accepting another symbol; finish terminal pilots consistently across output chunk sizes; leave the auction winner replaceable during startup. Apply 2.1 ms to added processing/buffering against a matched one-sample reference. |
| #5 Freshness and receiver semantics | Replace unsent same-key market values even when the new bid is lower; claim and charge only at serialization. Add per-key serial duplicate/stale suppression, wrap handling, bounded message assembly, and explicit FEC/checksum/audio/deadline gaps. |

Old bids receive no age boost. Cross-key selection still uses bid per wire byte, with newest winning ties. No unapproved age-decay timescale was introduced.

## Simulated channel verification

| Check | Result |
| --- | --- |
| Release C++/gRPC builds and CTest | 16/16 pass on `avx10` (AVX-512) and `naamah` (AVX2). |
| A4 clock/residual tracking | All 60 stated synchronization/boundary assertions pass for each of two seeds; all ten-minute traces retained. BER margins remain `THRESHOLD_TBD`. The 12 ±200 ppm cases per seed remain characterizations. |
| B1 gain steps | All 48 cases pass for each seed; affected-frame error rates remain reported. |
| B4 / D4 | Audio jitter/underrun/overrun gaps and duplicate/stale/wrap/FEC checks pass. |
| B5 added software latency | All 12 null-channel configurations pass on quiet `naamah`, serially, with 12-second traces and 48-sample audio buffers. |
| D1 overload | No superseded candidate reaches the framer at 1.5×, 3× or 10× load; maximum pending auction depth is one. |
| E1 / harness | Three repeated deterministic scenarios pass; all nine Python harness checks pass. |

The main report contains **383 cases**: 99 `THRESHOLD_TBD`, 186 `characterized`, 84 `pass`, 3 `unavailable`, 11 `xfail`. The independent seed adds 120 A4/B1 cases. No unexpected assertion failure or harness error remains in these selections.

Primary seed: `0x71A001` (7446529); independent seed: `0x71A002` (7446530). This is selected full-tier regression coverage, not a rerun of the entire characterization grid or soak.

## Simulated channel added processing and buffering

Quiet-host wall-clock p99.9, in milliseconds; limit **2.1 ms**. The long span uses the high-latitude quiet equalizer configuration through a null channel.

| Bandwidth | Modulation | Short span | Long span |
| --- | --- | ---: | ---: |
| 10 kHz | QPSK / 4-QAM | 0.966 | 0.910 |
| 10 kHz | 16-QAM | 0.863 | 0.962 |
| 10 kHz | 64-QAM | 0.965 | 0.955 |
| 24 kHz | QPSK / 4-QAM | 0.959 | 0.857 |
| 24 kHz | 16-QAM | 0.755 | 0.713 |
| 24 kHz | 64-QAM | 0.971 | 1.019 |

Total source-to-sink percentiles, intrinsic transmission/modem/startup reference, serialization estimates, RRC/equalizer/FEC residence, and CPU stage-call timings are reported separately in [the B5 tables](SUMMARY.md#simulated-channel-group-b5). Reference subtraction pairs message identities before computing percentiles; unmatched messages are a harness error. This loopback includes paced simulated audio buffering and OS scheduling, with no physical audio device or network socket.

The source generator now derives integral-sample deadlines from event indices. An explicit assertion catches a source event drifting across its aligned audio tick due to floating-point accumulation. Canonical sample-clock metrics stay deterministic; host timings are separate `.host.json` sidecars.

## Simulated channel polar screening

Ten seconds per point, nominal 30 dB SNR, rate-1/2 coding, equal-mean-power Watterson paths, seed `0x71A001`. The table shows complete, bit-exact RF frames for the declared delayed equalizer. These counts are characterization results, not a route-availability guarantee.

| Bandwidth | Modulation | Quiet | Moderate | Disturbed |
| --- | --- | ---: | ---: | ---: |
| 10 kHz | QPSK / 4-QAM | 1,177 / 1,177 | 0 / 1,177 | 0 / 1,177 |
| 10 kHz | 16-QAM | 134 / 1,177 | 0 / 1,177 | 0 / 1,177 |
| 10 kHz | 64-QAM | 14 / 1,177 | 0 / 1,177 | 0 / 1,177 |
| 24 kHz | QPSK / 4-QAM | 2,824 / 2,824 | 0 / 2,824 | 0 / 2,824 |
| 24 kHz | 16-QAM | 293 / 2,824 | 0 / 2,824 | 0 / 2,824 |
| 24 kHz | 64-QAM | 78 / 2,824 | 0 / 2,824 | 0 / 2,824 |

All short, causal and delayed span controls are retained in [A2](SUMMARY.md#simulated-channel-group-a2). Moderate/disturbed channels still prevent reliable header acquisition, and continuous streams still need a fresh transmitter epoch/preamble after loss of lock. The model at 24 kHz extrapolates F.1487 beyond its approximately 12 kHz stated scope; ten-second traces do not establish its statistical-duration operating limits.

## Simulated channel freshness under overload

| Offered load | Created / delivered | Queue max | Superseded at framer | Delivered after newer source creation |
| --- | ---: | ---: | ---: | ---: |
| 1.5× | 6,526 / 4,344 | 1 | 0 | 0 |
| 3× | 13,042 / 4,341 | 1 | 0 | 0 |
| 10× | 42,649 / 4,259 | 1 | 0 | 4 |

The four 10× observations became old while already in flight. Source coalescing cannot retract serialized bits, and a receiver cannot infer a newer source value it has not received. Newer-*received* serial suppression and same-key source replacement pass; the stronger remote-creation-time freshness contract remains a design question.

## Simulated channel defects and open thresholds

- **Polar reception:** moderate/disturbed acquisition and dropout recovery remain unresolved; 16-QAM and 64-QAM also lose many frames on the quiet preset.
- **Crypto #6:** AES-CTR plus CRC has no AEAD authentication; restart repeats the default key/counter keystream; coordinated key retirement is absent. The -10 dB co-channel trace still delivers non-source payloads. Message serials suppress same-session replays but do not solve these crypto defects.
- **Scheduling policy:** strict cross-key bid priority can starve a lower bidder during an endless higher-bid flood. Its test remains xfail; no aging priority boost was added.
- **Low-SNR acquisition:** the 24 kHz, 0 and 3 dB cases still fail to validate their headers.
- **Runtime:** the A4/B1 quick subset alone took 132.085 seconds on four-worker `avx10`, exceeding the whole-tier 120-second budget. Remaining quick cases and quiet-host timing add time. All durations, samples and points are retained.
- **Missing inputs/features:** E4 has no recordings. C5 mid-stream rate/interleaver changes and D5 parallel fiber data delivery remain conditional/unavailable. The soak and complete full matrix were not rerun.
- **Thresholds:** all unapproved BER, acquisition, recovery, freshness and soak margins remain `THRESHOLD_TBD`. See the [open-threshold table](SUMMARY.md#simulated-channel--open-thresholds) and [questions for Adam](../../tests/simulated_channel/QUESTIONS.md).

The [expected-failure review](EXPECTED_FAILURE_REVIEW.json) removes 70 resolved assertions from the pre-task registry and retains 13 failing assertions across eleven cases. The original audit and its result files are preserved. No acceptance threshold was weakened to obtain these passes; B5 follows Adam's explicit processing/buffering budget clarification.

## Simulated channel compatibility and reproduction

Both endpoints must enable the new realtime sequence format together: five base-254 bytes carry a 32-bit serial protected by the existing CRC. The legacy format remains selectable. Sequence history survives audio resets; a new session/receiver clears it. Configure the equalizer span, decision delay, training length, carrier-off boundary and matching wire format over gRPC. Audio drivers must supply sample positions/validity or timed block metadata to expose device discontinuities.

[Run commands and impairment extension guide](../../TESTING.md) · [Generated group tables](SUMMARY.md) · [Independent-seed evidence](additional-seed/SUMMARY.md) · [Host configurations](HOSTS.json) · [Validation manifest](VALIDATION.json) · [Task-only patch](changes.patch) · [Changed-file hashes](CHANGES.json)

Tested working-tree source SHA-256: `47db6749035027cc522e7fddff6f31d9ddf54eb3ff940f6ee07def6371639d86`. The base git commit is `adb3e6d72fac540712255792a1836df655ca4f4f`; the fixes were uncommitted working-tree changes when measured. The [source snapshot](source-snapshot.tar.gz) and [pre-task working-tree snapshot](pre-task-source.tar.gz) make the task-only patch reproducible without including unrelated rename/UI changes. The patch was applied to an isolated copy and every resulting file matched the final snapshot.
