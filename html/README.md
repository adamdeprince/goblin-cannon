# Goblin Cannon simulated channel HTML report

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

`disturbed_results.py` validates all selected records against the current tested source
hash, pairs latency records with host sidecars, and verifies byte-identical
repeat runs. It writes the current report, validation manifest and compact
presentation dataset. The snapshot preserves the tested files independently of
the enclosing commit. Run it before committing; the recorded base commit and
source hash describe the tested worktree.
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

## Production deployment

Production URL: <https://cannon.goblinreactor.com/>.
The rsync destination is `hail::distribution/cannon.goblinreactor.com/`.

From the repository root, check the generated report, commit and push the
changes, then upload the assets before the page that references them:

```sh
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
