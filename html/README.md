# Goblin Cannon simulated channel HTML report

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

Open `index.html` directly, or serve this directory:

```sh
python3 -m http.server 8000 --directory html
```

The report publishes current `results/disturbed-recovery` measurements. Historical performance
panels are removed. The browser selects saved results; it does not simulate RF.
Static tables remain readable without JavaScript.

The main explorer includes BPSK, QPSK and 8-PSK, each with convolutional or BCH
payload coding, both bandwidths and the three polar presets. Three seeds cover
each configuration. Authenticated-message traces last 300/300/100 seconds for
quiet/moderate/disturbed; raw RF screens remain ten seconds. The latency table
shows the twelve original configurations and twelve additional PSK/coding
configurations using the 7 ms equalizer span, measured serially on naamah.
Matched lower/upper/both diversity controls have their own table.

Authentication failures, foreign/corrupt deliveries, nonce-restart checks and
remaining expected failures have explicit tables. The noise reference and
diversity power are corrected; measured RF sample power is visible. None of these finite
simulated channels establishes availability on the 71-degree route.

## Simulated channel publication

After collecting the completed selections, regenerate and check the publication:

```sh
python3 scripts/disturbed_results.py --snapshot
python3 scripts/disturbed_results.py
python3 scripts/update_html_results.py
python3 scripts/update_html_results.py --check
```

`disturbed_results.py` validates all selected records against their saved measurement
archive and the hashes of the original 908 records, pairs latency records with
host sidecars, and verifies byte-identical repeat runs. It writes the current
report, validation manifest and compact presentation dataset. Later documentation
and metadata-reader changes do not replace the original measured source. The
snapshot command saves a separate report-source archive when the working source
differs from the measurement archive.
The fresh calibrated baseline is measured with the same source and channel
parameters; older uncalibrated measurements are not its control group.

`update_html_results.py` renders the marked region of `index.html` and
`simulated-channel.js` through `scripts/disturbed_html.py`. Edit presentation in
`evidence.css` and `rf-explorer.js`; edit generated copy in `disturbed_html.py`.
Asset URLs include content hashes. A check rejects publication data that differs
from the validated records.

`scripts/validate_aead_html.cjs` uses Playwright and accepts a local or public URL
and an optional result JSON path. It checks all 72 explorer views, 216 source
links, all latency and diversity rows, the defect table, mobile layout and the static
fallback. Set `CHROME_PATH` when using an installed Chrome binary.

Keep unobserved BER distinct from zero, raw RF survival distinct from application
goodput, and added processing/buffering distinct from transmission/modem delays.
Host timing is stored separately from deterministic simulated-time results.

The carrier frequency offset sweep has its own records in `results/carrier-offset`.
On the x86 validation host, run `python3 scripts/carrier_offset_campaign.py` to
measure the full declared grid, both signs and all three seeds. Then publish the
measured tolerance without changing the original delivery results:

```sh
python3 scripts/carrier_offset_results.py
python3 scripts/disturbed_results.py
python3 scripts/update_channel_docs.py
python3 scripts/update_html_results.py
python3 scripts/carrier_offset_results.py --check
python3 scripts/update_channel_docs.py --check
python3 scripts/update_html_results.py --check
```

The channel definitions and boundary text come from `channel_metadata.py` and
`scripts/channel_description.py`. `scripts/update_channel_docs.py` keeps the
marked Markdown paragraphs synchronized with the measured tolerance. Original
run records and source archives retain their bytes and deprecated metadata names;
the readers normalize them without changing observations or metrics.

## Production deployment

Production URL: <https://cannon.goblinreactor.com/>.
The rsync destination is `hail::distribution/cannon.goblinreactor.com/`.

From the repository root, check the generated report, commit and push the
changes, then upload the assets before the page that references them:

```sh
python3 scripts/carrier_offset_results.py --check
python3 scripts/update_channel_docs.py --check
python3 scripts/update_html_results.py --check

rsync --archive --checksum --itemize-changes \
  html/evidence.css html/rf-explorer.js html/simulated-channel.js html/goblin.png \
  hail::distribution/cannon.goblinreactor.com/

rsync --archive --checksum --itemize-changes \
  html/index.html hail::distribution/cannon.goblinreactor.com/
```

Add `--dry-run` to preview either transfer. Passing explicit files preserves the
destination directory's permissions. After publishing, verify the public page
and its assets and exercise the RF explorer. This deploys the website; upgrading
radio endpoints separately requires the provisioning steps in `AEAD.md`.
