/* Saved simulated channel comparisons; no RF simulation runs in the browser. */
(() => {
  "use strict";
  const data = globalThis.GoblinPskResults;
  const controls = document.getElementById("psk-controls");
  if (!data || !controls) return;
  const band = document.getElementById("psk-bandwidth");
  const preset = document.getElementById("psk-preset");
  const mode = document.getElementById("psk-mode");
  const spread = (values, scale = 1, places = 2) => {
    const v = values.filter(x => x !== null).map(x => x * scale);
    if (!v.length) return "Unobserved";
    const lo = Math.min(...v), hi = Math.max(...v);
    return (lo === hi ? lo.toFixed(places) : `${lo.toFixed(places)}–${hi.toFixed(places)}`) +
      (v.length !== values.length ? " (some unobserved)" : "");
  };
  const cell = (row, text, heading = false) => {
    const el = document.createElement(heading ? "th" : "td");
    if (heading) el.scope = "row";
    el.textContent = text; row.append(el); return el;
  };
  const link = (parent, href, text) => {
    const a = document.createElement("a"); a.href = href; a.textContent = text; parent.append(a);
  };
  function render() {
    const bandwidth = Number(band.value);
    const rows = data.rows.filter(r => r.bandwidth === bandwidth && r.preset === preset.value);
    if (rows.length !== 11) return;
    const body = document.querySelector("#psk-delivery-table tbody");
    body.replaceChildren();
    for (const r of rows) {
      const tr = document.createElement("tr"); cell(tr, r.label, true);
      cell(tr, spread(r.goodput)); cell(tr, spread(r.delivery, 100) + "%");
      cell(tr, spread(r.freshness)); cell(tr, spread(r.silence, .001, 3));
      const sources = cell(tr, "");
      r.sources.forEach((u, i) => { if (i) sources.append(" / "); link(sources, u, data.manifest.seeds[i]); });
      body.append(tr);
    }
    document.getElementById("psk-context").textContent = `${bandwidth / 1000} kHz · ${preset.value} · ${rows[0].duration} seconds per seed · 30 dB nominal SNR.`;
    const papr = data.papr.find(r => r.bandwidth === bandwidth && r.variant === mode.value);
    document.getElementById("psk-papr").textContent = `${papr.label} · ${bandwidth / 1000} kHz measured PAPR: ${spread(papr.db)} dB.`;
    const noise = document.querySelector("#psk-noise-table tbody"); noise.replaceChildren();
    const value = (v, scale = 1) => v === null ? "Unobserved" : Number((v * scale).toPrecision(5)).toString();
    for (const r of data.noise.filter(r => r.bandwidth === bandwidth && r.variant === mode.value)) {
      const tr = document.createElement("tr"); cell(tr, r.snr, true); cell(tr, value(r.ber));
      cell(tr, value(r.coded_ber)); cell(tr, value(r.observed, 100) + "%");
      cell(tr, value(r.frame_survival, 100) + "%"); link(cell(tr, ""), r.source, "JSON"); noise.append(tr);
    }
  }
  controls.hidden = false;
  for (const element of [band, preset, mode]) element.addEventListener("change", render);
  render();
})();
