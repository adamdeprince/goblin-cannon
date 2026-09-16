# Goblin Cannon simulated channel HTML report

Open `index.html` directly, or serve this directory:

```sh
python3 -m http.server 8000 --directory html
```

The benchmark tables, test ledger and RF explorer publish the saved
`results/fixes-2-5` campaign. The browser selects recorded cases; it does not
simulate RF. The static tables remain readable without JavaScript.

After updating the recorded campaign, regenerate and check the publication:

```sh
python3 scripts/update_html_results.py
python3 scripts/update_html_results.py --check
```

The exporter checks case/status totals against `VALIDATION.json`, verifies the
tested source hash, and pairs each latency record with its host sidecar. It
writes the marked section of `index.html` and `simulated-channel.js`. The
latter retains full parameters for all 54 polar configurations and 12 latency
configurations. Result links point to the original JSON, including seeds and
the tested source snapshot's hash. Host timing is separate from deterministic
sample-clock metrics.

Edit presentation in `evidence.css` and `rf-explorer.js`; edit generated copy in
`scripts/update_html_results.py`. Keep unobserved BER distinct from zero, RF
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
  html/evidence.css html/rf-explorer.js html/simulated-channel.js html/goblin.png \
  hail::distribution/cannon.goblinreactor.com/

rsync --archive --checksum --itemize-changes \
  html/index.html hail::distribution/cannon.goblinreactor.com/
```

Add `--dry-run` to preview either transfer. Passing explicit files preserves the
destination directory's permissions. After publishing, verify the public page
and its assets and exercise the RF explorer.
