# Questions and decisions from the simulated channel audit

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

Doppler shift: a mean frequency offset of the received signal relative to the transmitted carrier; a translation of the whole spectrum. Hz. Caused by bulk ionospheric motion plus transmitter/receiver LO error. Removing it is a frequency-tracking (AFC) problem.

Doppler spread: the width of the Doppler power spectrum of a propagation path, i.e. the fading rate. Hz. In the Watterson / ITU-R F.1487 model it is the width of the Gaussian spectrum applied to each tap. It is not an offset and no AFC removes it; it appears as fast fading and phase rotation the equalizer must track. 30 Hz means a coherence time on the order of tens of milliseconds.

| High-latitude preset | Delay spread (ms) | Doppler spread (Hz) | F.1487 Annex 3 |
| --- | ---: | ---: | --- |
| Quiet | 1 | 0.5 | §4.1 |
| Moderate | 3 | 10 | §4.2 |
| Disturbed | 7 | 30 | §4.3 |

Gaussian spectrum per tap; Doppler spread is the 2-sigma width, not sigma. Thus 30 Hz means σ = 15 Hz. The two taps fade independently; delay spread is their differential delay. Mean per-path Doppler shift is a separate parameter; these presets use zero. [Recommendation, Annex 1 §2 and Annex 3 §§1, 4.1–4.3](https://www.itu.int/dms_pubrec/itu-r/rec/f/R-REC-F.1487-0-200005-I!!PDF-E.pdf).

The original 908 recorded runs all disable carrier correction. All 722 Watterson runs use zero mean per-path Doppler shift and zero injected residual carrier frequency offset or drift. Across all 908 runs, 906 configure zero residual offset and drift; the two null-channel exceptions are a +5 Hz carrier frequency offset test and a +1 Hz/minute carrier-frequency drift test.

The carrier-offset sweep and its individual records are published in [the measurement report](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/SUMMARY.md). Historical results retain their original receiver versions and measurements.

<!-- END CHANNEL CONTRACT -->

Adam authorized fixes #1–5 after the original audit. Each follow-up report
identifies its tested working-tree snapshot; historical observations are retained.

## Recorded decisions for the simulated channel

- Carrier correction stays **off**. Adaptive equalization stays on. The new
  recursive equalizer has a first-order phase coefficient and no frequency
  estimate/accumulator; sample-clock recovery changes sampling instants only.
- **2.1 ms applies to added processing/buffering.** Total latency, transmission,
  modem/FEC residence and startup are reported separately. Host wall time lives
  in non-canonical sidecars; seeded simulation metrics remain deterministic.
  Latency validation runs serially on the quieter `naamah`; AVX-512 validation
  runs on `avx10`.
- Age does not increase a bid's priority. Newer unsent same-key market values
  replace older values regardless of bid. Cross-key bids retain price-per-wire-byte
  priority until serialization begins. No age-based priority boost is added.
- Acceptance margins remain `THRESHOLD_TBD`. Proposals are recorded, never enforced.
- No live receive recordings are available. E4 remains awaiting recordings.
- Fiber supplies matching endpoint configuration over gRPC. No over-radio
  parameter-change protocol is added.

## Remaining design questions for the simulated channel

1. **Bid decay and starvation:** no cross-key age-decay timescale or expiry has
   been specified. If time-based devaluation is wanted in addition to same-key
   replacement, what half-life/expiry should apply? Strict price priority still
   permits starvation during an endless higher-bid flood; D3 retains that policy
   conflict explicitly rather than raising old bids.
2. **Freshness at the sink:** a receiver can suppress values behind a newer
   received serial number. It cannot know that a newer value has just been
   created at the remote source. Once serialization begins, an update cannot
   retract bits already in flight. Should D1/A9's stronger creation-time rule
   be narrowed to source coalescing plus newer-received suppression?
3. **Crypto:** AES-128-CTR plus CRC is not AEAD. What AEAD, session/replay,
   restart-safe nonce allocation and coordinated key-retirement contract should
   replace it? The new message serial numbers are not authentication and do not
   solve same-key/default-counter reuse on restart. This is outside fixes #2–5.
4. **Polar acceptance:** which BER, useful-message goodput, freshness and outage
   targets should govern the route? The recovery campaign includes ten-second
   A/B screens and three independent long runs per primary configuration.
   Recurring markers remove the need to restart a transmitter after ordinary
   lock loss, but moderate/disturbed channels remain difficult. Marker cadence
   trades recovery opportunities against useful airtime; it is fiber configured.
5. **Waveform comparability:** the code has ten constellations, RRC shaping, custom
   QPSK startup/header, punctured convolutional coding and no interleaver. It does
   not implement Appendix D waveform-number/rate/interleaver mappings; 10 kHz is
   not a Table D-I bandwidth. Which standard configurations should be implemented
   before enforcing MIL-STD performance limits?
6. **Wideband channel model:** F.1487 states applicability to approximately 12 kHz.
   Is extrapolation of its two-path model to 24 kHz acceptable for screening
   pending measured statistics?
7. **Statistical duration:** F.1487 recommends
   `max(3000/doppler_spread_hz, 100/(BER*data_rate))` seconds. At 0.1 Hz its first term alone
   is 30,000 seconds. A1 retains all grid points but its declared 10-second traces
   cannot establish those limits. The separate polar campaign uses the complete
   6000/300/100-second Doppler spread terms and checks the bit-duration term at a 1e-3
   planning target. BER 1e-5 characterization and all other presets still need
   their own duration planning; message-delivery results are not BER certification.
8. **SNR convention:** retain SNR per complex baseband sample, or adopt a specified
   receiver noise bandwidth? Current results cannot be directly compared to
   standard 3 kHz SNR tables without conversion.
9. **STAC definitions:** the detailed audit attachment requires login. Supply its
   adjustment/standby definitions before asserting exact E2 comparability. Local
   uptime and one-second usable-window definitions are explicit in each result.
10. **Runtime:** the complete quick tier exceeds 120 seconds on four-vCPU avx10.
    All ten-minute traces and paired drift controls are retained. Increase CI
    resources or revise the budget?
11. **D2 calibration:** equal survival fractions do not imply equal burst structure.
    Select a freshness-agreement margin and target-survival tolerance before
    judging channel fading against independent direct erasures.
12. **Initial session validation:** recurrent RF headers preserve continuous FEC
    and CTR positions. A receiver with timestamp validation enabled must have
    validated the initial timestamp before resuming at a later marker. It does
    not trust an unauthenticated later header as a replacement. Should an
    authenticated fiber session establish this context for late joining?
13. **Overload reference with markers:** D1's existing offered-load fixture uses
    nominal payload capacity after pilots and FEC, before periodic marker airtime.
    Its 1.5×/3×/10× labels therefore impose a higher load relative to the recovery
    profile's complete-waveform capacity. Retaining this fixture preserves the
    offered stream for comparison, but it is not an exact calibration to that
    profile's new airtime capacity. Should a separate marker-aware calibration
    accompany the existing stress cases?

## Resolved interfaces in the simulated channel

- Fix #1 corrected finite matched-filter support at 2.5 samples/symbol.
- The realtime wire format now has optional 32-bit serials, five base-254 bytes
  covered by CRC; both endpoints must switch together. The default realtime
  configuration enables it; standalone framing retains the legacy default.
  Per-key duplicate/stale suppression survives an audio reset. A new session or
  receiver clears serial history. Maximum application message size is 65,535 bytes.
- `push_audio_block` supplies device sample positions and validity on both the
  raw realtime and controlled receiver. An observer gap event distinguishes
  audio discontinuity, FEC uncertainty, malformed/checksum data and lost RF lock.
  The timed variant also checks arrival against the playout slack. Physical drivers
  must supply these metadata; simulated tests exercise both APIs.
- Equalizer tap counts, decision delay, recursive adaptation, sample-clock recovery
  and message sequencing are exposed over gRPC. A2 preserves the original sweep
  and adds explicit short/causal/delayed polar configurations.
- D5 remains conditional: fiber is a control path, with no parallel market-data
  delivery arbiter. C5 remains conditional: rate changes restart matched epochs;
  no mid-stream interleaver-change feature exists.
- B3 reports total BER because this single-carrier modem has no edge subcarriers.
- All nine requested channel presets were verified. F.1487 has an inconsistent
  cross-reference to the former poor channel; `ccir_poor` follows F.520-2's
  **2 ms / 1 Hz**. High-latitude quiet/moderate/disturbed use **1/.5, 3/10, 7/30**
  as delay spread in ms / Doppler spread in Hz. No preset value remains unverified.

## Primary sources for the simulated channel

- [ITU-R F.1487](https://www.itu.int/dms_pubrec/itu-r/rec/f/R-REC-F.1487-0-200005-I!!PDF-E.pdf), Annex 1 (Gaussian power spectrum, Doppler spread = 2σ), Annex 3 (presets and test length).
- [ITU-R F.520-2](https://www.itu.int/dms_pubrec/itu-r/rec/f/R-REC-F.520-2-199203-W!!PDF-E.pdf), Annex 1 §2.2 (good/moderate/poor).
- [MIL-STD-188-110C, DLA copy](https://quicksearch.dla.mil/Transient/D1A6E2FA29A74374ABCEEDAF36DDA384.pdf), Appendix D Tables D-I/D-II (bandwidth, symbol rate and waveform mapping). DLA transient links can expire; use ASSIST for a fresh copy.
- [STAC audit landing page](https://docs.stacresearch.com/RFT230516) (attachment requires login), [public summary](https://docs.stacresearch.com/news/RFT230516), and [STAC presentation](https://docs.stacresearch.com/system/files/resource/files/STAC-Summit-19-October-2023-STAC-Network.pdf).
