/* Verify current simulated channel HTML against saved canonical measurements. */
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
  const a = values.filter(x => x !== null).map(x => x * scale);
  if (!a.length) return "Unobserved";
  const low = Math.min(...a), high = Math.max(...a);
  return (low === high ? low.toFixed(places) : `${low.toFixed(places)}–${high.toFixed(places)}`) +
    (a.length === values.length ? "" : " (some unobserved)");
};

(async () => {
  const browser = await chromium.launch({ headless: true, executablePath: process.env.CHROME_PATH });
  try {
    const page = await browser.newPage({ viewport: { width: 1440, height: 1000 } });
    const errors = []; page.on("pageerror", e => errors.push(String(e)));
    if (target.startsWith("file:")) await page.route(/^https?:/, request => request.abort());
    await page.goto(target);
    await page.waitForSelector("#rf-controls:not([hidden])");
    const data = await page.evaluate(() => globalThis.GoblinChannelResults);
    assert.equal(data.schema_version, 3);
    let views = 0, sourceLinks = 0;
    for (const bandwidth of [10000, 24000]) for (const modulation of ["bpsk", "qpsk", "8psk"])
      for (const coding of ["soft", "bch"]) for (const preset of ["quiet", "moderate", "disturbed"]) {
        await page.selectOption("#rf-bandwidth", String(bandwidth));
        await page.selectOption("#rf-modulation", modulation);
        await page.selectOption("#rf-coding", coding);
        await page.selectOption("#rf-preset", preset);
        const row = data.rows.find(r => r.bandwidth === bandwidth && r.variant === `${modulation}_${coding}` && r.preset === preset);
        assert.ok(row);
        for (const layer of ["messages", "rf"]) {
          await page.selectOption("#rf-layer", layer);
          const sources = layer === "messages" ? row.sources : row.rf_sources;
          const records = sources.map(read);
          for (const record of records) assert.equal(record.parameters.source_tree_sha256, data.manifest.source_tree_sha256);
          assert.deepEqual(records.map(r => r.seed), data.manifest.seeds);
          const values = layer === "messages" ? [
            spread(records.map(r => r.metrics.message_delivery_fraction_of_framed), 100) + "%",
            spread(records.map(r => r.metrics.goodput_bps)), spread(records.map(r => r.metrics.freshness_ms.p99_9)),
            spread(records.map(r => r.metrics.delivery_silence_ms.max), .001, 3)
          ] : [spread(records.map(r => r.metrics.frame_survival_fraction), 100) + "%",
            spread(records.map(r => r.metrics.ber), 1, 5), spread(records.map(r => r.metrics.bit_observation_fraction), 100) + "%",
            spread(records.map(r => r.observations.tx_mean_sample_power), 1, 4)];
          for (let i = 0; i < 4; ++i) assert.equal(await page.locator(`#rf-metric-${i}`).innerText(), values[i]);
          assert.deepEqual(await page.locator("#rf-sources a").evaluateAll(nodes => nodes.map(n => n.href)), sources);
          assert.equal(await page.locator(".rf-seed-tracks .rf-bar-track").count(), 9);
          views++; sourceLinks += sources.length;
        }
      }
    const rows = page.locator("#current-latency-table tbody tr");
    assert.equal(await rows.count(), data.latency.length);
    for (const [i, r] of data.latency.filter(r => r.profile === "naamah-latency").entries()) {
      const host = read(r.source).observations, record = read(r.record);
      assert.deepEqual(await rows.nth(i).locator("td").allInnerTexts(), [
        host.host_added_software_latency_ms_percentiles.p99_9.toFixed(3),
        host.host_latency_ms_percentiles.p99_9.toFixed(3),
        record.latency_reference.metrics.latency_ms.p50.toFixed(3) + " / " + record.latency_reference.metrics.latency_ms.p99_9.toFixed(3),
        host.added_software_latency_assertion.status]);
    }
    assert.equal(await page.locator("#current-defect-table tbody tr").count(), data.manifest.remaining_assertions);
    assert.equal(await page.locator("#current-auth-table tbody tr").count(), 3);
    await page.locator("#rf-simulation details").filter({ has: page.locator("#current-diversity-table") }).locator("summary").click();
    const diversityRows = page.locator("#current-diversity-table tbody tr");
    assert.equal(await diversityRows.count(), data.diversity.length);
    for (const [i, row] of data.diversity.entries()) {
      const expected = ["lower", "upper", "both"].map(branch =>
        spread(row.branches[branch].sources.map(source => read(source).metrics.fresh_goodput_bps)));
      assert.deepEqual(await diversityRows.nth(i).locator("td").allInnerTexts(), expected);
    }
    const sweep = JSON.parse(fs.readFileSync(path.join(root, "results/carrier-offset/DATA.json"), "utf8"));
    const sweepRows = page.locator("#carrier-offset-sweep tbody tr");
    await page.locator("#carrier-offset-sweep summary").click();
    assert.equal(await sweepRows.count(), sweep.rows.length);
    const meanAndRange = (values, places) => `${(values.reduce((a, b) => a + b) / values.length).toFixed(places)}\n${Math.min(...values).toFixed(places)}–${Math.max(...values).toFixed(places)}`;
    for (const [i, row] of sweep.rows.entries()) {
      const records = row.sources.map(read);
      for (const record of records) {
        assert.equal(record.parameters.residual_offset_hz, row.carrier_frequency_offset_hz);
        assert.equal(record.parameters.carrier_correction, 0);
        assert.equal(record.parameters.source_tree_sha256, sweep.source_tree_sha256);
      }
      assert.equal(await sweepRows.nth(i).locator("td").nth(0).innerText(), meanAndRange(records.map(r => 100 * r.metrics.message_delivery_fraction_of_framed), 4));
      assert.equal(await sweepRows.nth(i).locator("td").nth(1).innerText(), meanAndRange(records.map(r => r.metrics.fresh_goodput_bps), 2));
      assert.deepEqual(await sweepRows.nth(i).locator("a").evaluateAll(nodes => nodes.map(n => n.href)), row.sources);
    }
    assert.ok((await page.locator(".channel-boundary").innerText()).includes(`already removed to within ${sweep.tolerance_hz} Hz. It performs no Doppler-shift correction.`));
    assert.equal(await page.locator("#current-delivery-table tbody tr").count(), 6);
    assert.deepEqual(await page.evaluate(() => [...document.querySelectorAll('a[href^="#"]')].map(a => a.hash.slice(1)).filter(id => id && !document.getElementById(id))), []);
    assert.equal(await page.evaluate(() => [globalThis.GoblinPskResults, globalThis.GoblinEncodingResults, globalThis.GoblinRefinementResults].every(x => x === undefined)), true);
    assert.equal(await page.locator("#encoding-results, #psk-results, #refinement-controls").count(), 0);
    await page.selectOption("#rf-bandwidth", "24000"); await page.selectOption("#rf-modulation", "qpsk");
    await page.selectOption("#rf-preset", "disturbed"); await page.selectOption("#rf-layer", "messages");
    if (output) await page.locator("#rf-explorer").screenshot({ path: output.replace(/\.json$/, "-desktop.png") });
    await page.setViewportSize({ width: 390, height: 844 });
    await page.locator("#test-results details, #rf-simulation details").evaluateAll(nodes => nodes.forEach(n => n.open = true));
    assert.equal(await page.evaluate(() => document.documentElement.scrollWidth > innerWidth), false, "Mobile overflow");
    if (output) await page.locator("#rf-explorer").screenshot({ path: output.replace(/\.json$/, "-mobile.png") });
    const nojs = await browser.newPage({ javaScriptEnabled: false, viewport: { width: 390, height: 844 } });
    if (target.startsWith("file:")) await nojs.route(/^https?:/, request => request.abort());
    await nojs.goto(target);
    assert.equal(await nojs.locator("#current-delivery-table tbody tr").count(), 6);
    assert.equal(await nojs.locator("#carrier-offset-sweep tbody tr").count(), sweep.rows.length);
    assert.equal(await nojs.locator("#rf-controls").isVisible(), false);
    assert.deepEqual(errors, []);
    const report = { report_header: "simulated channel disturbed recovery HTML verification", url: target,
      status: "pass", source_tree_sha256: data.manifest.source_tree_sha256, explorer_views: views, source_links: sourceLinks,
      latency_rows: data.latency.length, diversity_rows: data.diversity.length,
      defects: data.manifest.remaining_assertions, no_javascript_rows: 6,
      carrier_offset_rows: sweep.rows.length, carrier_offset_tolerance_hz: sweep.tolerance_hz,
      mobile_width: 390, page_errors: errors };
    if (output) fs.writeFileSync(output, JSON.stringify(report, null, 2) + "\n");
    console.log(JSON.stringify(report));
  } finally { await browser.close(); }
})().catch(error => { console.error(error); process.exitCode = 1; });
