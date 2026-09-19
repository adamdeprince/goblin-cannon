# Goblin Cannon simulated channel regression tests

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

The broader A–E test brief is implemented by the [simulated channel harness](../TESTING.md).
This page describes the original carrier-correction-enabled regressions and
the added profile, equalizer-delay, buffering and data-path regressions. The clean-profile
tests use carrier correction off and adaptive equalization on, matching the
radio/software boundary in the brief.

Run the thirteen channel test groups with:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target goblin_cannon_channel_tests
ctest --test-dir build -L channel --output-on-failure
```

On an AVX-512 host such as `avx10`, configure with
`-DGOBLIN_CANNON_TEST_REQUIRE_AVX512=ON`. Each channel test then checks the
runtime demapper selection and fails unless the AVX-512 kernel is selected.
The executable prints the selected implementation even when this check is off.

The tests pass IQ samples through a deterministic channel before feeding the
real acquisition correlator and RF receiver. Both ends receive matching modem
settings, as they would through the slower fiber control link. The tests add no
RF parameter negotiation, retransmission, or interleaving.

## Passing conditions for the simulated channel regressions

| Group | Conditions and assertions |
| --- | --- |
| Acquisition | Gains 0.1–2.0, rotations through ±180°, and noise; exact preamble location. Phase estimates and coarse carrier frequency offset estimates at ±0.5 and ±10 Hz. |
| Noise | QPSK (4-QAM) at 14 dB, 16QAM at 24 dB, and 64QAM at 34 dB; silence and noise alone cannot acquire or emit payload, including scan windows too short to compare sidelobes. |
| Phase | All three modulations: ±0.1 Hz carrier frequency offset; ±135° with ±30 Hz carrier frequency offset; 180° with a 50 Hz/s carrier-frequency drift; and a continuous-phase 10 Hz carrier frequency offset step during the payload. Smaller rotations are ±20° for QPSK, ±10° for 16QAM, and ±1° for 64QAM. |
| Fading | Smooth attenuation from 0 to 12 dB at 5 Hz for QPSK; 0 to 6 dB at 2 Hz for 16QAM; 0 to 3 dB at 1 Hz for 64QAM. |
| Combined | All three use +10° phase. QPSK: 6 dB fading at 5 Hz, 24 dB SNR. 16QAM: 6 dB fading at 2 Hz, 30 dB SNR. 64QAM: 3 dB fading at 1 Hz, 36 dB SNR. |
| Recovery | All three modulations: a complete fade with receiver noise, 90° phase step, and −10 dB noise burst must cause lock loss within two pilot intervals, filter allowance, and one input chunk of observation delay. A later epoch with different gain, phase, and frequency must reacquire without resetting the receiver. |
| Equalization | All three modulations: echoes at 1, 3, and 7 ms, echo amplitude 0.45 relative to the direct path, 0.5 Hz relative echo Doppler shift, 10 Hz common carrier frequency offset, and 1.1 rad common phase. All payload symbols must be correct; training error must be less than half the error without equalization. The same samples must fail to decode completely without equalization for 16QAM and 64QAM. |
| Streaming | All three modulations: corrected symbols, frame counters, and tracking state must survive output buffers of 1, 7, and 128 symbols, including draining with no new input. Reset must discard the previous stream's tracking state. |
| Configuration | Invalid tap counts and insufficient training are rejected. Disabling both correction loops must disable compensation. The main test executable also checks gRPC round trips, explicit false/zero settings, and defaults for older clients. |
| Sample support | Drained QPSK blocks of 32 and 33 symbols decode completely without padding at 2, 2.5, 3.125, 5 and 6 samples/symbol. Withholding the last required sample must withhold the last symbol; delivering that sample must release it exactly once. |
| Clean profiles | QPSK, 16-QAM and 64-QAM at 24 kHz and 10 kHz with carrier correction off and adaptive equalization on. After a 17-sample leading delay, input chunks of 1, 48, 157 and 512 samples must yield a valid header, exactly 1,024 correct payload symbols, and correct frame counters/offsets. |
| Decision delay | Carrier correction off, recursive equalization on; QPSK/16-QAM/64-QAM with 1, 8 and 32 symbols of lookahead must recover exact payload and frame positions. |
| Transmit chunks | Transmit buffers of 1, 2, 5, 48, 193 and 257 samples must produce byte-identical finite RF audio, including the final pilot group. |
| Data path | Seeded concurrent market coalescing, framer-time budget reservation, log backpressure, serial duplicate/stale/wrap handling, bounded partial messages, and explicit FEC/audio/deadline gaps. |

The original rejection test no longer assumes that an equal-power echo must
cause loss of lock: a working equalizer can legitimately decode it. Echo
reception is covered by the existing equalization checks and the explicit A2
polar span characterizations.

The noisy carrier, equalization, streaming, and reacquisition cases use 24 dB
for QPSK, 30 dB for 16QAM, and 36 dB for 64QAM. These are regression test points,
not measured operating limits or a recommendation to use 64QAM on the route.
The acquisition preamble and control header use QPSK for every payload modulation.

The sample-support and clean-profile tests are `assert` / `quick` tests. Both
use payload seed `0xC011AB1E` and print it with their case parameters. Clean
profiles use the brief's 0.25 rolloff, 64 training symbols, three feedforward
and four feedback taps. Their regressions target a decoder readiness check
that rounded the matched filter's right edge up, leaving the last header
symbol unavailable when that edge fell between audio samples.

The decoding cases require acquisition, a valid header, no lock loss, all 4,096
payload symbols correct, and correct frame counters and offsets. Each has a clean
control and three fixed noise seeds, with 37- and 157-sample receive chunks. They
use 48 ksample/s, 9.6 ksymbol/s, 64-symbol frames, and a pilot pair every 32 payload
symbols. Noise cases also exercise 24 ksymbol/s (two samples per symbol).
The pilot and payload confidence thresholds are both 0.08, matching the existing
RF test profile; acquisition requires both peak prominence and normalized
correlation of at least 0.25.

The equalization cases use 1,024 QPSK training symbols, three feedforward taps,
and `ceil(delay_seconds * symbol_rate) + 8` feedback taps (18, 37, and 76).
Startup pilot counts grow to cover those spans. These are epoch startup costs;
the steady-state equalizer processes each symbol as it arrives. Training uses
12 passes over the already received sequence. Its normalized RMS error is
reported as `RfSyncEstimate::training_evm` and must be below 0.25 in these tests.
QPSK can tolerate some echoes without equalization, so its comparison checks the
reduction in training error without requiring the bypassed receiver to fail.

SNR means **complex-sample signal power divided by complex noise power before
fading**. It is neither Eb/N0 nor a 3 kHz receiver-bandwidth SNR. Gaussian noise
has independent I/Q components; its power and mean are checked separately. The
noise floor stays fixed as the signal fades. The fading envelope is sinusoidal
in dB, starts at 0 dB attenuation, and reaches the stated maximum attenuation.

## What the simulated channel says about a route reaching 71° latitude

The current recovery cases inject complete fades, a phase step, and a noise
burst. Equalization tests separately use 1, 3, and 7 ms echo delays with a
0.5 Hz relative echo Doppler shift. These deterministic-echo regressions do not
measure Gaussian Doppler spread. The Watterson campaigns use independent
Gaussian fading paths with the explicitly labeled presets above. Their
recorded durations and delivery metrics remain separate from these short
carrier-correction-enabled regressions.

The positive equalization cases use a weaker, slowly rotating echo; the
fade, phase-step and noise-burst cases exercise loss and recovery with the default short
equalizer. Neither set specifies a maximum tolerable channel or predicts
polar-link availability. Longer feedback spans need longer training, and a
causal decision-feedback equalizer can propagate decision errors during deep
fades. The newer A2 span sweep exercises sample-clock recovery and delayed
equalization separately; see the [follow-up results](../results/fixes-2-5/FIXES.md).

The legacy implementation uses a normalized LMS update with known-symbol training and
decision-directed tracking; see the [liquid-dsp equalization description](https://www.liquidsdr.org/doc/equalization/)
for the adaptation model. The RF wire header is unchanged. Tap counts and
training sequences are supplied to both ends through the control link.

Latitude alone does not specify the channel. [NOAA's polar-cap absorption
documentation](https://www.swpc.noaa.gov/content/global-d-region-absorption-prediction-documentation)
describes the roles of geomagnetic location, particle flux, and illumination.
Route endpoints, operating frequency, time, and measured channel conditions
are needed to select representative longer-running channel simulations.
