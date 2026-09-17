/* Compare the simulated channel website with its underlying result records.
 * Requires Playwright; optionally set CHROME_PATH for an installed browser.
 * Usage: node scripts/validate_refinement_html.cjs [URL] [output.json]
 */
const { chromium } = require("playwright");
const assert = require("node:assert/strict");
const fs = require("node:fs");
const path = require("node:path");
const { pathToFileURL } = require("node:url");
const root = path.resolve(__dirname, "..");
const target = process.argv[2] || pathToFileURL(path.join(root, "html/index.html")).href;
const output = process.argv[3];
const read = source => JSON.parse(fs.readFileSync(path.join(root, source.split("/blob/main/")[1]), "utf8"));
const spread = (values, scale = 1, places = 2) => {
  const observed = values.filter(x => x !== null).map(x => x * scale);
  if (!observed.length) return "Unobserved";
  const low = Math.min(...observed), high = Math.max(...observed);
  return (low === high ? low.toFixed(places) : `${low.toFixed(places)}–${high.toFixed(places)}`) +
    (observed.length === values.length ? "" : " (some unobserved)");
};

(async () => {
  const browser = await chromium.launch({ headless: true, executablePath: process.env.CHROME_PATH });
  try {
    const page = await browser.newPage({ viewport: { width: 1440, height: 1000 } });
    const errors = [];
    page.on("pageerror", e => errors.push(String(e)));
    if (target.startsWith("file:")) await page.route(/^https?:/, request => request.abort());
    await page.goto(target);
    await page.waitForSelector("#refinement-controls:not([hidden])");
    const data = await page.evaluate(() => globalThis.GoblinRefinementResults);
    let comparisons = 0;
    for (const bandwidth of [10000, 24000]) {
      for (const preset of ["quiet", "moderate", "disturbed"]) {
        for (const family of ["coding", "diversity", "cadence"]) {
          await page.selectOption("#refinement-bandwidth", String(bandwidth));
          await page.selectOption("#refinement-preset", preset);
          await page.selectOption("#refinement-family", family);
          const rows = page.locator("#refinement-delivery-table tbody tr");
          const expected = data.rows.filter(r => r.bandwidth === bandwidth && r.preset === preset &&
            (r.experiment === family || (family === "cadence" && ["bpsk_bch", "qpsk_bch"].includes(r.variant))));
          assert.equal(await rows.count(), { coding: 6, diversity: 9, cadence: 10 }[family]);
          assert.equal(expected.length, await rows.count());
          for (const [i, r] of expected.entries()) {
            const records = r.sources.map(read);
            for (const record of records) {
              assert.equal(record.parameters.source_tree_sha256, data.manifest.source_tree_sha256);
              assert.equal(record.parameters.carrier_correction, 0);
              assert.equal(record.parameters.bandwidth_hz, bandwidth);
            }
            assert.deepEqual(records.map(r => r.seed), data.manifest.seeds);
            const cells = await rows.nth(i).locator("td").allInnerTexts();
            assert.deepEqual(cells.slice(0, 5), [
              spread(records.map(r => r.metrics.goodput_bps)),
              spread(records.map(r => r.metrics.fresh_goodput_bps)),
              spread(records.map(r => r.metrics.freshness_ms.p99_9)),
              spread(records.map(r => r.metrics.delivery_silence_ms.max), .001, 3),
              (records[0].parameters.cadence_plan.payload_airtime_fraction * 100).toFixed(1) + "%"
            ], r.label);
            assert.equal(await rows.nth(i).locator("th").innerText(), r.label);
            assert.deepEqual(await rows.nth(i).locator("a").evaluateAll(nodes => nodes.map(n => n.href)), r.sources);
            ++comparisons;
          }
        }
      }
    }
    await page.locator("#refinement-results details summary").first().click();
    const timing = page.locator("#refinement-latency-table tbody tr");
    assert.equal(await timing.count(), 46);
    for (const [i, r] of data.latency.entries()) {
      const host = read(r.source).observations, canonical = read(r.record);
      const values = v => v === null ? "Unobserved" : v.toFixed(3);
      const cells = await timing.nth(i).locator("td").allInnerTexts();
      assert.deepEqual(cells, [String(canonical.observations.messages_delivered),
        values(host.host_added_software_latency_ms_percentiles.p99_9),
        values(host.host_latency_ms_percentiles.p99_9),
        values(canonical.latency_reference.metrics.latency_ms.p50) + " / " +
          values(canonical.latency_reference.metrics.latency_ms.p99_9),
        host.added_software_latency_assertion.status]);
      assert.equal(await timing.nth(i).locator("a").getAttribute("href"), r.source);
    }
    assert.equal(await page.locator("#encoding-delivery-table tbody tr").count(), 21);
    await page.selectOption("#refinement-bandwidth", "24000");
    await page.selectOption("#refinement-preset", "moderate");
    await page.selectOption("#refinement-family", "coding");
    if (output) await page.locator("#refinement-delivery-table").screenshot({ path: output.replace(/\.json$/, "-desktop.png") });
    await page.setViewportSize({ width: 390, height: 844 });
    assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false, "Mobile overflow");
    if (output) await page.locator("#refinement-controls").screenshot({ path: output.replace(/\.json$/, "-mobile.png") });
    const nojs = await browser.newPage({ javaScriptEnabled: false, viewport: { width: 390, height: 844 } });
    if (target.startsWith("file:")) await nojs.route(/^https?:/, request => request.abort());
    await nojs.goto(target);
    assert.equal(await nojs.locator("#refinement-delivery-table tbody tr").count(), 6);
    assert.equal(await nojs.locator("#refinement-controls").isVisible(), false);
    assert.deepEqual(errors, []);
    const report = { report_header: "simulated channel refinement HTML verification", url: target,
      status: "pass", source_tree_sha256: data.manifest.source_tree_sha256, comparison_rows: comparisons,
      seed_links: comparisons * 3, latency_configurations: 46, mobile_width: 390, no_javascript_rows: 6,
      previous_encoding_rows: 21, page_errors: errors };
    if (output) fs.writeFileSync(output, JSON.stringify(report, null, 2) + "\n");
    console.log(JSON.stringify(report));
  } finally {
    await browser.close();
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
