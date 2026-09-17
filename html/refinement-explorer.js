/* Saved simulated channel measurements; no RF simulation in this browser. */
(() => {
  "use strict";
  const data = globalThis.GoblinRefinementResults;
  const controls = document.getElementById("refinement-controls");
  if (!data || !controls) return;
  const band = document.getElementById("refinement-bandwidth");
  const preset = document.getElementById("refinement-preset");
  const family = document.getElementById("refinement-family");
  const spread = (values, scale = 1, places = 2) => {
    const v = values.filter(x => x !== null).map(x => x * scale);
    if (!v.length) return "Unobserved";
    const lo = Math.min(...v), hi = Math.max(...v);
    return (lo === hi ? lo.toFixed(places) : `${lo.toFixed(places)}–${hi.toFixed(places)}`) +
      (v.length === values.length ? "" : " (some unobserved)");
  };
  const cell = (row, text, heading = false) => {
    const element = document.createElement(heading ? "th" : "td");
    if (heading) element.scope = "row";
    element.textContent = text; row.append(element); return element;
  };
  function render() {
    const bandwidth = Number(band.value);
    const rows = data.rows.filter(r => r.bandwidth === bandwidth && r.preset === preset.value &&
      (r.experiment === family.value || (family.value === "cadence" && ["bpsk_bch", "qpsk_bch"].includes(r.variant))));
    const body = document.querySelector("#refinement-delivery-table tbody");
    body.replaceChildren();
    for (const r of rows) {
      const tr = document.createElement("tr");
      cell(tr, r.label, true); cell(tr, spread(r.goodput)); cell(tr, spread(r.fresh_goodput));
      cell(tr, spread(r.freshness)); cell(tr, spread(r.silence, .001, 3));
      cell(tr, (r.cadence.payload_airtime_fraction * 100).toFixed(1) + "%");
      const sources = cell(tr, "");
      r.sources.forEach((source, i) => {
        if (i) sources.append(" / ");
        const a = document.createElement("a"); a.href = source; a.textContent = data.manifest.seeds[i]; sources.append(a);
      });
      body.append(tr);
    }
    const explanations = {
      coding: "BCH replaces rate-1/2 payload coding with rate 40/58. Gains include the changed code rate.",
      diversity: "Same branch width, data rate and total power; lower/upper are single-copy controls. Both copies share the channel.",
      cadence: "Pilot spacing and full retraining vary independently; p32/r16 is the baseline. Airtime includes all recurring control blocks."
    };
    document.getElementById("refinement-context").textContent = `${bandwidth / 1000} kHz · ${preset.value} · ${rows[0].duration} seconds per seed · ${explanations[family.value]}`;
  }
  controls.hidden = false;
  for (const el of [band, preset, family]) el.addEventListener("change", render);
  render();
})();
