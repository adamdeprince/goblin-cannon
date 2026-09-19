# Carrier frequency offset tolerance in the simulated quiet channel

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

A constant carrier frequency offset is applied at channel output, after filtering and sample-clock resampling. Per-path Doppler shift is zero; Doppler spread stays at 0.5 Hz. Carrier correction remains disabled. The zero-offset observations and metrics exactly match the three published quiet controls.

The measured bound is **10 Hz** in either direction. Every seed and both offset signs stay within 0.1 percentage points of the paired 0 Hz delivery value, at every tested magnitude up to the reported bound. This is a sampled bound, not a continuous-frequency guarantee. The zero-offset delivery range across seeds is 0.0334 percentage points. Delivery collapses by ±320 Hz under the declared 1%-of-baseline criterion.

| Carrier frequency offset (Hz) | Delivery %: mean [seed range] | Fresh goodput bit/s: mean [seed range] | Largest paired delivery change (percentage points) | Within 0.1 points for every seed |
| ---: | ---: | ---: | ---: | :---: |
| [-320](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-320Hz/7446529.json) | 0.0000 [0.0000–0.0000] | 0.00 [0.00–0.00] | 99.9532 | no |
| [-160](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-160Hz/7446529.json) | 26.6631 [24.1050–29.3882] | 425.33 [384.67–469.23] | 75.8149 | no |
| [-80](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-80Hz/7446529.json) | 89.9969 [89.4536–90.6692] | 1435.68 [1427.09–1446.32] | 10.4662 | no |
| [-40](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-40Hz/7446529.json) | 99.3989 [99.2720–99.5057] | 1585.74 [1583.81–1587.44] | 0.6479 | no |
| [-20](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-20Hz/7446529.json) | 99.9622 [99.9532–99.9666] | 1594.65 [1594.51–1594.72] | 0.0334 | yes |
| [-10](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-10Hz/7446529.json) | 99.9488 [99.9332–99.9666] | 1594.47 [1594.29–1594.72] | 0.0468 | yes |
| [-5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-5Hz/7446529.json) | 99.9354 [99.8798–99.9666] | 1594.22 [1593.33–1594.72] | 0.0534 | yes |
| [-2](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-2Hz/7446529.json) | 99.9310 [99.8998–99.9532] | 1594.15 [1593.65–1594.51] | 0.0200 | yes |
| [-1](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-1Hz/7446529.json) | 99.8931 [99.8731–99.9265] | 1593.55 [1593.23–1594.08] | 0.0801 | yes |
| [-0.5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_-0.5Hz/7446529.json) | 99.9443 [99.9265–99.9733] | 1594.36 [1594.08–1594.83] | 0.0200 | yes |
| [+0](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_0Hz/7446529.json) | 99.9354 [99.9199–99.9532] | 1594.22 [1593.97–1594.51] | 0.0000 | yes |
| [+0.5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_0.5Hz/7446529.json) | 99.9488 [99.9332–99.9599] | 1594.44 [1594.19–1594.61] | 0.0401 | yes |
| [+1](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_1Hz/7446529.json) | 99.9421 [99.9265–99.9666] | 1594.33 [1594.08–1594.72] | 0.0134 | yes |
| [+2](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_2Hz/7446529.json) | 99.9132 [99.8798–99.9466] | 1593.87 [1593.33–1594.40] | 0.0735 | yes |
| [+5](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_5Hz/7446529.json) | 99.9488 [99.9332–99.9733] | 1594.44 [1594.19–1594.83] | 0.0200 | yes |
| [+10](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_10Hz/7446529.json) | 99.9399 [99.9265–99.9532] | 1594.29 [1594.08–1594.51] | 0.0200 | yes |
| [+20](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_20Hz/7446529.json) | 99.8887 [99.8330–99.9466] | 1593.49 [1592.64–1594.40] | 0.1202 | no |
| [+40](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_40Hz/7446529.json) | 99.1384 [99.0182–99.2119] | 1581.53 [1579.68–1582.67] | 0.9150 | no |
| [+80](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_80Hz/7446529.json) | 87.0291 [85.8002–87.7839] | 1388.40 [1368.91–1400.29] | 14.1197 | no |
| [+160](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_160Hz/7446529.json) | 31.6903 [29.3548–34.3842] | 505.60 [468.53–549.12] | 70.5651 | no |
| [+320](https://github.com/adamdeprince/goblin-cannon/blob/main/results/carrier-offset/E2_carrier_offset_24000_qpsk_bch_quiet_320Hz/7446529.json) | 0.0000 [0.0000–0.0000] | 0.00 [0.00–0.00] | 99.9532 | no |

Delivery is authenticated messages delivered / messages framed. Fresh goodput uses the existing source-key freshness metric. Each offset has three full 300-second traces, seeds 7446529–7446531. All individual records and their source snapshot are retained here; the original 908-record campaign is unchanged.

Reproduce with `python3 scripts/carrier_offset_campaign.py`, then `python3 scripts/carrier_offset_results.py`. The runner measures 0, ±0.5, ±1, ±2, ±5, ±10 and ±20 Hz, doubling the magnitude afterward until mean delivery in both directions is at most 1% of the 0 Hz value. It uses the original canonical run schema and metric calculation.
