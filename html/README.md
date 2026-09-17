# Goblin Cannon simulated channel HTML report

Open `index.html` directly, or serve this directory:

```sh
python3 -m http.server 8000 --directory html
```

The benchmark tables, test ledger and RF explorer publish the saved
`results/recovery-improvements` campaign. The browser selects recorded cases; it does not
simulate RF. The static tables remain readable without JavaScript.

The latest refinement section publishes `results/refinement`: 23 configurations
per bandwidth, BCH combinations, three diversity spacings with matched
single-copy controls, and five pilot/retraining schedules. It includes 1,328
AVX-512 cases and 46 quiet-host latency cases. `refinement-explorer.js` filters
the saved comparisons; its static table defaults to 24 kHz moderate fading.
Run `python3 scripts/validate_refinement_power.py` and
`python3 scripts/refinement_results.py` before updating the HTML. The report
includes the interrupted run's elapsed time without reducing case durations.

The power audit retains six xfails: the noise reference disagrees with measured
RRC power, and diversity gain compensation changes actual power relative to
full-band BPSK. All 54 matched lower/upper/both controls pass. The configured
30 dB is not actual pre-fade 30 dB, and cross-family results are not equal-power
comparisons. This calibration caveat also applies to the earlier sections.

The earlier encoding section publishes `results/encoding-improvements`: 21
configurations, both bandwidths, three polar presets and three sustained seeds.
It includes all 672 noise points and 42 quiet-host latency measurements, with
interleaver and diversity wait charged as added buffering. The patent-screen
link states the implementation boundaries and exclusions. Regenerate it with
`python3 scripts/encoding_results.py` before updating the HTML.
`encoding_html.py` supplies the static moderate-channel table;
`encoding-explorer.js` selects the saved comparisons and noise curves.
No absent observation is replaced by zero and no expected latency failure is
presented as a pass.

The earlier PSK section publishes `results/psk-improvements` separately, preserving
the earlier source provenance. Its two bandwidths and three polar presets each
compare eleven configurations over three seeds. Noise curves retain all sixteen
SNR points; the 44 latency records come from naamah. Regenerate the completed
PSK report with `python3 scripts/psk_results.py` before updating the HTML.
That exporter rejects missing cases, mixed source hashes, changed durations,
nonidentical determinism reruns and mismatched host sidecars. `psk_html.py`
renders a static 24 kHz moderate table; `psk-explorer.js` exposes every saved
comparison and noise curve. No browser calculation synthesizes new RF results.

After updating the recorded campaign, regenerate and check the publication:

```sh
python3 scripts/update_html_results.py
python3 scripts/update_html_results.py --check
```

After a quiet-host latency rerun, refresh its comparison and validation manifest
with `python3 scripts/compare_recovery_latency.py` before regenerating the HTML.

The exporter checks case/status totals against `VALIDATION.json`, verifies the
tested source hash, and pairs each latency record with its host sidecar. It
reads `latency_results_directory` in the campaign manifest for a separate
quiet-host selection. That selection must contain the same twelve case/seed
pairs and parameters as the AVX-512 baseline, except for the recorded revision
and ISA requirement. Its source hash must match. The latency table links to
the measured host sidecars; the original AVX-512 records remain in place. It
writes the marked section of `index.html` and `simulated-channel.js`. The
latter retains full parameters for 90 RF and 90 production-message selections
from the first seed, plus 12 latency configurations. A separate long-run table
links all three seeds for each of 18 configurations. Result links point to the original JSON, including seeds and
the tested source snapshot's hash. Host timing is separate from deterministic
sample-clock metrics.

The polar before/after table compares all 18 configurations across the same
three seeds, links all 108 baseline/updated records, and counts paired goodput
increases. Its ten-second screens remain separate from the longer updated-profile
runs. The route geometry, fixed-SNR fading simulation and measured software
latency each state their scope; none establishes actual route availability.

Edit presentation in `evidence.css` and `rf-explorer.js`; edit generated copy in
`scripts/recovery_html.py` (called by `scripts/update_html_results.py`). The
exporter requires a completed campaign manifest; incomplete runs cannot replace
the published report. Asset URLs include content hashes so a refreshed page
loads its matching scripts. A cached older page retains its static table when
newer data needs controls it does not have. Keep unobserved BER distinct from zero, RF
frame goodput distinct from application goodput, and added processing latency
distinct from total latency. Do not describe these measurements as a radio
deployment or a validated route latency.

## Production deployment

Production URL: <https://cannon.goblinreactor.com/>.
The rsync destination is `hail::distribution/cannon.goblinreactor.com/`.

From the repository root, check the generated report, commit and push the
changes, then upload the assets before the page that references them:

```sh
python3 scripts/update_html_results.py --check

rsync --archive --checksum --itemize-changes \
  html/evidence.css html/rf-explorer.js html/psk-explorer.js html/encoding-explorer.js html/refinement-explorer.js html/simulated-channel.js html/goblin.png \
  hail::distribution/cannon.goblinreactor.com/

rsync --archive --checksum --itemize-changes \
  html/index.html hail::distribution/cannon.goblinreactor.com/
```

Add `--dry-run` to preview either transfer. Passing explicit files preserves the
destination directory's permissions. After publishing, verify the public page
and its assets and exercise the RF explorer.
