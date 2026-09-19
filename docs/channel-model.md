# Channel quantities and the radio/software boundary

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

The F.1487 name for Doppler spread is "frequency spread". The simulator uses the
recommendation's 2σ convention, so its 30 Hz parameter is already a 30 Hz width,
with σ = 15 Hz. No preset or recorded delivery value is rescaled.

The spread and shift are independent channel parameters. The two Watterson tap
spectra are centered at zero; the simulator currently fixes their mean shifts
at zero. Its independent output stage adds `residual_offset_hz` and
`residual_drift_hz_per_second`, after filtering and sample-clock resampling.
The legacy deterministic echo's `echo_frequency_offset_hz` is a relative echo
Doppler shift. Its `fade_rate_hz` is a sinusoidal attenuation rate.

## Parameters and record compatibility

`doppler_spread_hz` always means the 2σ Doppler spread of each Gaussian tap
spectrum. The test probe accepts `doppler` and `doppler_hz` as deprecated aliases,
warns on their use, and rejects contradictory values. No separate public
`--doppler` flag exists: the test probe takes `key=value` arguments.

New run metadata uses `doppler_spread_definition`, `doppler_spread_convention`,
`doppler_shift_definition`, and `doppler_shift_hz`. For Watterson runs,
`doppler_shift_hz` is the two-element list `[0, 0]`; it is descriptive metadata,
not an input that enables independent tap shifts. Null-channel runs use `null`
because they have no fading paths. The constant output offset is recorded
separately as `residual_offset_hz`.

Historical `doppler_definition` metadata is a deprecated convention field;
readers normalize its known value to the canonical definition and convention.
`itu_doppler_duration_s` remains a deprecated reader alias for
`itu_doppler_spread_duration_s`. Historical A3 case IDs encode Doppler spread;
A4 `offset` and `drift` IDs encode carrier frequency offset and frequency drift.
Case identifiers and original JSON/CSV evidence are retained. Source archives
also retain their original bytes, including legacy spellings.

`tests/simulated_channel/recorded_runs.json` pins the SHA-256 of every original
record. The harness test loads all 908, verifies their hashes and metrics,
checks their channel parameters, and distinguishes the two residual-error tests.
The HTML publisher verifies the original measurement archive independently of
later documentation or metadata-reader changes; it never relabels that archive
as newly measured source.

The carrier-offset sweep has its own source snapshot and canonical records in
`results/carrier-offset`. Its zero-offset controls must reproduce the published
quiet-preset observations and metrics exactly before a tolerance is reported.
