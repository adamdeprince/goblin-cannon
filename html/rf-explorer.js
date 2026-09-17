/* Select recorded simulated channel results. No browser-side RF model. */
(() => {
  "use strict";
  const evidence = globalThis.GoblinChannelResults;
  const explorer = document.getElementById("rf-explorer");
  if (!evidence || !explorer) return;

  const modes = { qpsk: "QPSK / 4-QAM", "16qam": "16-QAM", "64qam": "64-QAM" };
  const presets = ["quiet", "moderate", "disturbed"];
  const controls = Object.fromEntries(
    ["bandwidth", "modulation", "span", "preset", ...(evidence.schema_version === 2 ? ["layer"] : [])]
      .map(key => [key, document.getElementById(`rf-${key}`)])
  );
  // A previously cached page can load newer assets during publication.
  // Keep its static evidence visible when it lacks the new controls.
  if (Object.values(controls).some(control => !control)) return;
  const put = (id, value) => { document.getElementById(`rf-${id}`).textContent = value; };
  const percent = value => value == null ? "Unobserved" : `${(value * 100).toFixed(2)}%`;
  const count = value => value.toLocaleString("en-US");

  function update() {
    const selected = Object.fromEntries(Object.entries(controls).map(([key, input]) => [key, input.value]));
    const messages = selected.layer === "messages";
    const rows = (messages ? evidence.messages : evidence.polar).filter(row => row.parameters.bandwidth_hz === Number(selected.bandwidth)
      && row.parameters.modulation === selected.modulation && row.span === selected.span);
    const row = rows.find(candidate => candidate.preset === selected.preset);
    if (!row) return; // The static table stays available if the data schema changes.
    const p = row.parameters;
    const m = row.metrics;
    const o = row.observations;
    const complete = messages ? o.messages_delivered === o.messages_consumed_by_framer : o.frames_survived === o.frames_sent;
    const outcome = explorer.querySelector(".rf-outcome");
    outcome.dataset.reception = complete ? "complete" : "limited";
    put("outcome-title", messages ? (o.messages_delivered > 0 ? "Useful messages delivered after FEC." : "No useful messages delivered in this trace.") : complete ? "All RF frames survived this trace."
      : o.frames_survived === 0 ? "No bit-exact RF frames survived." : "RF frame loss in this trace.");
    put("outcome-note", `${p.bandwidth_hz / 1000} kHz · ${modes[p.modulation]} · high-latitude ${row.preset}. `
      + (o.valid_headers === 0 ? "No header was validated. " : `${o.valid_headers} header(s) validated; ${o.lock_losses} lock loss(es). `)
      + "This ten-second characterization has no pass/fail threshold and does not establish route availability.");
    if (evidence.schema_version === 2) {
      put("survival-label", messages ? "Delivered / framed messages" : "Bit-exact RF frame survival");
      put("ber-label", messages ? "Delivered freshness p99.9" : "Observed BER before FEC");
      put("goodput-label", messages ? "Useful message goodput" : "Raw RF-frame goodput");
      put("goodput-note", messages ? "After production FEC and deframing" : "Before application FEC and deframing");
    }
    put("survival", percent(messages ? m.message_delivery_fraction_of_framed : m.frame_survival_fraction));
    put("frames", messages ? `${count(o.messages_delivered)} / ${count(o.messages_consumed_by_framer)} framed; ${count(o.messages_created)} created`
      : `${count(o.frames_survived)} of ${count(o.frames_sent)} RF frames`);
    put("ber", messages ? (m.freshness_ms.p99_9 == null ? "Unobserved" : `${m.freshness_ms.p99_9.toFixed(2)} ms`)
      : m.ber == null ? "Unobserved" : m.ber === 0 ? "0 observed" : m.ber.toExponential(2));
    put("observed", messages ? `Longest delivery silence: ${(m.delivery_silence_ms.max / 1000).toFixed(3)} s`
      : `${count(o.bits_compared)} / ${count(o.bits_sent)} bits compared (${percent(m.bit_observation_fraction)})`);
    put("goodput", m.goodput_bps == null ? "Unobserved" : `${(m.goodput_bps / 1000).toFixed(2)} kbit/s`);
    put("lock", `${o.valid_headers} / ${o.lock_losses}`);
    put("acquisition", m.acquisition_time_s == null ? "Preamble acquisition unobserved"
      : `${(m.acquisition_time_s * 1000).toFixed(2)} ms to preamble (not validated header)`);
    put("parameters", `${p.delay_spread_ms} ms delay spread · ${p.doppler_spread_hz} Hz Doppler spread · `
      + `${p.path_gains_db.join(" / ")} dB path gains · ${p.snr_db} dB nominal SNR · `
      + `${p.equalizer_feedforward_taps} forward / ${p.equalizer_feedback_taps} feedback taps · `
      + `${p.equalizer_delay_symbols} symbols decision delay · ${p.training_symbols} training symbols · `
      + (evidence.schema_version === 2 ? `${p.equalizer.samples_per_symbol} matched samples/symbol · marker every ${p.recovery_interval_frames || "no"} frame(s) · ` : "")
      + `${p.frame_symbols} symbols/frame · rate ${p.fec} configured · interleaver: ${p.interleaver} · `
      + `${(p.sample_rate_hz / 1000)} ksample/s · ${o.simulated_seconds.toFixed(3)} s including startup/tail · `
      + `seed ${p.seed} (0x${p.seed.toString(16).toUpperCase()})`);
    document.getElementById("rf-record").href = row.source;

    const chart = document.getElementById("rf-comparison");
    chart.replaceChildren();
    for (const preset of presets) {
      const peer = rows.find(candidate => candidate.preset === preset);
      const fraction = messages ? peer.metrics.message_delivery_fraction_of_framed : peer.metrics.frame_survival_fraction;
      const bar = document.createElement("div");
      bar.className = "rf-bar-row";
      const label = document.createElement("div");
      label.className = "rf-bar-label";
      label.textContent = preset[0].toUpperCase() + preset.slice(1);
      const parameters = document.createElement("small");
      parameters.textContent = `${peer.parameters.delay_spread_ms} ms / ${peer.parameters.doppler_spread_hz} Hz`;
      label.append(parameters);
      const track = document.createElement("div");
      track.className = "rf-bar-track";
      track.setAttribute("aria-hidden", "true");
      const fill = document.createElement("div");
      fill.className = "rf-bar-fill";
      fill.style.width = `${Math.max(0, Math.min(1, fraction ?? 0)) * 100}%`;
      track.append(fill);
      const value = document.createElement("div");
      value.className = "rf-bar-value";
      value.textContent = percent(fraction);
      bar.append(label, track, value);
      chart.append(bar);
    }
  }

  Object.values(controls).forEach(control => control.addEventListener("change", update));
  update();
  explorer.hidden = false;
})();
