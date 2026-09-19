/* Display current recorded simulated channels; no browser-generated RF results. */
(() => {
  "use strict";
  const data = globalThis.GoblinChannelResults;
  if (!data || data.schema_version !== 3) return;
  const controls = Object.fromEntries(["bandwidth", "modulation", "coding", "preset", "layer"]
    .map(key => [key, document.getElementById(`rf-${key}`)]));
  if (Object.values(controls).some(value => !value)) return;
  const presets = ["quiet", "moderate", "disturbed"];
  const spread = (values, scale = 1, digits = 2) => {
    const numbers = values.filter(value => value !== null).map(value => value * scale);
    if (!numbers.length) return "Unobserved";
    const low = Math.min(...numbers), high = Math.max(...numbers);
    return (low === high ? low.toFixed(digits) : `${low.toFixed(digits)}–${high.toFixed(digits)}`) +
      (numbers.length === values.length ? "" : " (some unobserved)");
  };
  const put = (id, value) => { document.getElementById(id).textContent = value; };
  const link = (href, label) => {
    const a = document.createElement("a"); a.href = href; a.textContent = label; return a;
  };

  function update() {
    const selected = Object.fromEntries(Object.entries(controls).map(([key, input]) => [key, input.value]));
    const variant = `${selected.modulation}_${selected.coding}`;
    const row = data.rows.find(r => r.bandwidth === +selected.bandwidth && r.variant === variant && r.preset === selected.preset);
    if (!row) return;
    const messages = selected.layer === "messages";
    const duration = messages ? row.duration : 10;
    put("rf-outcome-title", messages ? (Math.max(...row.goodput) > 0 ? "Useful messages delivered after FEC." : "No useful messages delivered in these traces.") : "RF decisions before message FEC.");
    put("rf-outcome-note", `${row.bandwidth / 1000} kHz · ${row.label} · high-latitude ${row.preset}. ${duration} seconds per seed. ` +
      (messages ? "Only complete, authenticated records reach the message sink." : "Missing bits are excluded from conditional BER and counted in the observed-bit fraction."));
    const fields = messages ? [
      ["Delivered / framed messages", spread(row.delivery, 100) + "%", "Range across three seeds"],
      ["Useful goodput", spread(row.goodput), "Useful bits per second"],
      ["Delivered freshness p99.9", spread(row.freshness), "Milliseconds from source creation"],
      ["Longest delivery silence", spread(row.silence, .001, 3), "Seconds, including terminal silence"]
    ] : [
      ["Bit-exact RF frame survival", spread(row.survival, 100) + "%", "Range across three seeds"],
      ["Conditional BER", spread(row.ber, 1, 5), "Errors / compared bits"],
      ["Observed-bit fraction", spread(row.observed, 100) + "%", "Compared / transmitted bits"],
      ["Measured TX sample power", spread(row.measured_power, 1, 4), "Before fading; calibrated noise reference"]
    ];
    fields.forEach(([label, value, unit], i) => {
      put(`rf-metric-label-${i}`, label); put(`rf-metric-${i}`, value);
      if (i) put(`rf-unit-${i}`, unit);
    });
    const comparison = document.getElementById("rf-comparison");
    comparison.replaceChildren();
    for (const preset of presets) {
      const r = data.rows.find(r => r.bandwidth === row.bandwidth && r.variant === variant && r.preset === preset);
      const values = messages ? r.delivery : r.survival;
      const bar = document.createElement("div"); bar.className = "rf-bar-row";
      const label = document.createElement("span"); label.className = "rf-bar-label"; label.textContent = preset;
      const tracks = document.createElement("div"); tracks.className = "rf-seed-tracks";
      values.forEach((value, i) => {
        const track = document.createElement("div"); track.className = "rf-bar-track";
        track.title = `Seed ${data.manifest.seeds[i]}: ${value === null ? "unobserved" : (100 * value).toFixed(3) + "%"}`;
        const fill = document.createElement("div"); fill.className = "rf-bar-fill";
        fill.style.width = `${100 * Math.max(0, Math.min(1, value || 0))}%`;
        track.append(fill); tracks.append(track);
      });
      const value = document.createElement("span"); value.className = "rf-bar-value"; value.textContent = spread(values, 100) + "%";
      bar.append(label, tracks, value); comparison.append(bar);
    }
    comparison.hidden = false;
    const p = row.parameters;
    put("rf-parameters", `Configured SNR ${p.snr_db} dB · delay spread ${p.delay_spread_ms} ms · Doppler spread ${p.doppler_spread_hz} Hz (2σ) · per-path Doppler shift ${p.doppler_shift_hz.join(" / ")} Hz · residual carrier frequency offset ${p.residual_offset_hz} Hz · paths ${p.path_gains_db.join(" / ")} dB. ` +
      `Equalizer ${p.equalizer_feedforward_taps}/${p.equalizer_feedback_taps} taps, ${p.equalizer_delay_symbols}-symbol delay; ${p.training_symbols} training symbols. ` +
      (messages ? `Fresh goodput ${spread(row.fresh_goodput)} bit/s; authentication failures ${spread(row.auth_failures, 1, 0)}; corrupt deliveries ${spread(row.corrupt, 1, 0)}. ` : "") +
      "Seed ranges are not confidence intervals.");
    const sources = document.getElementById("rf-sources"); sources.replaceChildren();
    (messages ? row.sources : row.rf_sources).forEach((source, i) => sources.append(link(source, `Seed ${data.manifest.seeds[i]} parameters + metrics`)));

    put("current-table-caption", `Simulated channel · ${row.bandwidth / 1000} kHz ${row.preset} · current useful delivery`);
    const tbody = document.querySelector("#current-delivery-table tbody"); tbody.replaceChildren();
    for (const r of data.rows.filter(r => r.bandwidth === row.bandwidth && r.preset === row.preset)) {
      const tr = document.createElement("tr"); const th = document.createElement("th"); th.scope = "row"; th.textContent = r.label; tr.append(th);
      for (const value of [spread(r.goodput), spread(r.fresh_goodput), spread(r.delivery, 100), spread(r.freshness), spread(r.silence, .001, 3)]) {
        const td = document.createElement("td"); td.textContent = value; tr.append(td);
      }
      const links = document.createElement("td");
      r.sources.forEach((source, i) => { if (i) links.append(" · "); links.append(link(source, String(data.manifest.seeds[i]))); });
      tr.append(links); tbody.append(tr);
    }
  }
  Object.values(controls).forEach(control => control.addEventListener("change", update));
  document.getElementById("rf-controls").hidden = false;
  update();
})();
