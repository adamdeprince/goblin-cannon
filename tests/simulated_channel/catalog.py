"""Declared simulated channel matrix. No adaptive reductions of grids/durations."""
from __future__ import annotations

from dataclasses import dataclass, field
from itertools import product
from math import ceil, floor
from pathlib import Path

SEED = 0x71A001
SNR_GRID = tuple(range(0, 31, 2))
MODULATIONS = ("qpsk", "8psk", "16qam", "64qam", "256qam", "1024qam",
               "16qci", "64qci", "256qci", "1024qci")
BITS = dict(zip(MODULATIONS, (2, 3, 4, 6, 8, 10, 4, 6, 8, 10)))
BITS["bpsk"] = 1
RATES = ("1/2", "2/3", "3/4")
PROFILES = (10000, 24000)
# Verified against F.520-2 Annex 1 and F.1487 Annex 3. Spread is 2*sigma.
PRESETS = {
    "ccir_good": (0.5, 0.1), "ccir_poor": (2.0, 1.0),
    "mid_lat_quiet": (0.5, 0.1), "mid_lat_moderate": (1.0, 0.5),
    "mid_lat_disturbed": (2.0, 1.0), "high_lat_quiet": (1.0, 0.5),
    "high_lat_moderate": (3.0, 10.0), "high_lat_disturbed": (7.0, 30.0),
    "low_lat_disturbed": (6.0, 10.0),
}
STAGE_ORDER = ("channel", "interferers", "impulsive_noise", "dropout", "agc",
               "clipping", "band_limiting", "sample_rate_mismatch",
               "residual_offset_drift", "audio_jitter")
# None is serialized as JSON null and converted to +infinity only for the probe.
DEFAULTS = dict(
    mode="rf", modulation="qpsk", bandwidth_hz=24000, sample_rate_hz=48000,
    duration_s=2.0, chunk_samples=256, frame_symbols=64, training_symbols=64,
    fec="none", carrier_correction=0, seed=SEED, require_avx512=1,
    sample_clock_recovery=1, adaptive_equalization=1, recursive_equalization=1, equalizer_feedforward_taps=3, equalizer_feedback_taps=4, pilot_interval_symbols=32,
    channel_model="null", snr_db=None, delay_spread_ms=0.0, doppler_spread_hz=1.0,
    path0_db=0.0, path1_db=0.0, pure_noise=0, phase_rad=0.0,
    cw_hz=0.0, cw_sir_db=None, data_sir_db=None, interferer_start_s=0.0,
    impulse_ms=0.0, impulses_per_second=0.0, impulse_above_noise_db=0.0,
    dropout_start_s=0.0, dropout_duration_s=0.0,
    agc_step_db=0.0, agc_start_s=0.1, agc_attack_ms=1.0, agc_decay_ms=100.0,
    clip_amplitude=None, soft_clip=0, calibrate_clip=0,
    filter_bandwidth_hz=0.0, group_delay_ripple_ms=0.0,
    notch_center_hz=0.0, notch_width_hz=0.0, notch_depth_db=0.0,
    clock_ppm=0.0, residual_offset_hz=0.0, residual_drift_hz_per_second=0.0,
    sample_slip_index=-1, sample_slip=0, pattern="random",
    message_interval_s=0.01, jitter_ms=0.0, audio_event="", audio_event_s=0.5, audio_jitter_buffer_samples=48,
    overload=1.0, capacity_messages_per_s=100.0, instruments=16, flood=0,
    semantics="duplicate",
    selected_messages="",
    receive_tail_samples=2,
    equalizer_delay_symbols=0,
    compact_header=0, header_modulation="qpsk", differential_mapping="none",
    recovery_interval_frames=0, fractionally_spaced_equalization=0,
    equalizer_reselect_interval=0, aggregate_metrics=0,
    direct_survival=1.0, soak=0, noise_file="",host_timing=0,auction_intake=0,source_load_factor=0,
)
OPEN_THRESHOLDS = {
    "A4.ber_delta": ("0 absolute excess BER in the noise-free regression; select a confidence interval for noisy runs", "No radio residual-offset budget or BER margin is specified."),
    "C2.acquisition_seconds": ("one complete preamble/training/header plus one audio block", "The configured startup lengths give a measurable lower bound; approval needed."),
    "C3.recovery_frames": ("2 frames after a new valid epoch preamble", "The current stream needs an epoch preamble to reacquire; a deadline without one is undefined."),
    "C4.pattern_ber_margin": ("a paired confidence interval, with its significance level selected by Adam", "Equal finite-sample BER is not a statistical scrambler test."),
    "D1.newest_latency_ms": ("one frame duration + 2.1 ms, as proposed in the brief", "Needs agreement on whether serialization, FEC lookahead and startup are included."),
    "D2.freshness_agreement_ms": ("compare paired freshness distributions; select a quantile margin", "Equal survival fractions do not imply equal burst structure."),
    "D2.target_survival_margin": ("select a confidence interval for channel calibration; direct erasures round to the nearest whole frame", "A finite SNR grid cannot guarantee exactly 30%, 50%, or 80% channel survival."),
    "D3.instrument_delay_ms": ("one frame duration + 2.1 ms", "Strict bid priority and starvation freedom can conflict under sustained overload."),
    "D6.rotation_loss_frames": ("one epoch startup plus the in-flight frame", "There is no coordinated rotation protocol to measure yet."),
    "E3.memory_growth_bytes": ("zero steady growth after warmup; choose an allocator/RSS allowance", "Host RSS varies and includes harness allocations."),
    "E3.queue_depth": ("configured ring capacity plus one pending auction bid", "Must distinguish queue capacity from newest-message freshness."),
    "E3.latency_change": ("a paired percentile tolerance chosen from baseline variability", "Exact equality across different fading realizations is not a usable acceptance rule."),
}

@dataclass
class Case:
    name: str
    group: str
    kind: str
    tier: str
    parameters: dict
    checks: tuple[str, ...] = ()
    thresholds: tuple[str, ...] = ()
    unavailable: str | None = None
    notes: list[str] = field(default_factory=list)


def case(group, name, kind, tier, *, checks=(), thresholds=(), unavailable=None, notes=(), **kwargs):
    parameters = DEFAULTS | kwargs
    return Case(f"{group}_{name}", group, kind, tier, parameters,
                tuple(checks), tuple(thresholds), unavailable, list(notes))


def preset(name):
    delay, doppler = PRESETS[name]
    return dict(channel_model="watterson", delay_spread_ms=delay, doppler_spread_hz=doppler)


def matrix():
    cases = []
    add = cases.append
    # Ten seconds per point is a declared screening duration. It is not the
    # much longer F.1487 statistical test length. C1 reports censored bounds.
    for bw, mod, fec, channel, snr in product(PROFILES, MODULATIONS, RATES, PRESETS, SNR_GRID):
        add(case("A1", f"{bw}_{mod}_{fec.replace('/', '-')}_{channel}_{snr}dB", "characterize", "full",
                 bandwidth_hz=bw, modulation=mod, fec=fec, snr_db=snr,
                 duration_s=10, **preset(channel),
                 notes=["10 s screening trace; not F.1487 Annex 3 statistical-duration compliance."]))
    for delay, gain, mod in product((0.5, 1, 2, 3, 5, 7), (0, -6), ("qpsk", "16qam", "64qam")):
        add(case("A2", f"{mod}_{delay}ms_{gain}dB", "characterize", "full", modulation=mod,
                 channel_model="watterson", delay_spread_ms=delay, doppler_spread_hz=1,
                 path1_db=gain, snr_db=30, duration_s=10))
    for spread, mod in product((0.1, 0.5, 1, 3, 10, 30), ("qpsk", "16qam", "64qam")):
        add(case("A3", f"{mod}_{spread}Hz", "characterize", "full", modulation=mod,
                 channel_model="watterson", delay_spread_ms=2, doppler_spread_hz=spread, snr_db=30, duration_s=10))
    # Fiber-configured equalizer spans, including a short-filter control. These
    # supplement the original A1/A2/A3 grids; none of their points are replaced.
    for bw, mod, channel, span in product(PROFILES, ("qpsk", "16qam", "64qam"),
                                        ("high_lat_quiet", "high_lat_moderate", "high_lat_disturbed"),
                                        ("short", "causal", "delayed")):
        echo = ceil(PRESETS[channel][0] * bw * 0.8 / 1000)
        forward = 2*echo+3 if span=="delayed" else 3
        feedback = 4 if span=="short" else echo+4
        training = 64 if span=="short" else max(256,2*forward)
        add(case("A2", f"polar_{bw}_{mod}_{channel}_{span}", "characterize", "full",
                 bandwidth_hz=bw, modulation=mod, fec="1/2", snr_db=30, duration_s=10,
                 equalizer_feedforward_taps=forward, equalizer_feedback_taps=feedback,
                 equalizer_delay_symbols=echo if span=="delayed" else 0, training_symbols=training,
                 **preset(channel), notes=["Declared fiber configuration; 10 s screening trace. Decision delay is modem residence, reported separately from added software buffering."]))
    for bw, mod in product(PROFILES, ("qpsk", "16qam", "64qam")):
        for offset in (0, -1, 1, -3, 3, -5, 5):
            add(case("A4", f"{bw}_{mod}_offset_{offset}", "assert", "quick", bandwidth_hz=bw,
                     modulation=mod, residual_offset_hz=offset, duration_s=10,
                     checks=("sync_held",), thresholds=("A4.ber_delta",)))
        add(case("A4", f"{bw}_{mod}_drift_10min", "assert", "quick", bandwidth_hz=bw,
                 modulation=mod, residual_drift_hz_per_second=1/60, duration_s=600, chunk_samples=2048,
                 checks=("sync_held",), thresholds=("A4.ber_delta",)))
        for ppm in (-200, -50, 50, 200):
            add(case("A4", f"{bw}_{mod}_{ppm}ppm_10min", "assert" if abs(ppm)==50 else "characterize", "quick",
                     bandwidth_hz=bw, modulation=mod, clock_ppm=ppm, duration_s=600, chunk_samples=2048,
                     checks=("no_frame_boundary_loss",) if abs(ppm)==50 else ()))
    for width, depth, center, mod in product((1000, 2000, 3000, 4000), (20, 30, 40), (0, 6000, 11000), ("qpsk", "16qam", "64qam")):
        add(case("A5", f"{mod}_{width}_{depth}_{center}", "characterize", "full", modulation=mod,
                 notch_width_hz=width, notch_depth_db=depth, notch_center_hz=center, snr_db=30, duration_s=10))
    for length, frequency, height in product((0.1, 0.5, 1, 5), (1, 10, 100), (20, 30, 40)):
        add(case("A6", f"{length}ms_{frequency}Hz_{height}dB", "characterize", "full", **preset("mid_lat_moderate"),
                 impulse_ms=length, impulses_per_second=frequency, impulse_above_noise_db=height, snr_db=30, duration_s=10))
    for hz, sir, mod in product(range(-12000, 12001, 2000), (20, 10, 0, -10), ("qpsk", "16qam", "64qam")):
        add(case("A7", f"{mod}_{hz}Hz_{sir}dB", "characterize", "full", modulation=mod,
                 cw_hz=hz, cw_sir_db=sir, snr_db=30, duration_s=10))
    for sir in (10, 0, -10):
        add(case("A8", f"cochannel_{sir}dB", "assert", "full", mode="messages", fec="1/2", chunk_samples=48,
                 data_sir_db=sir, interferer_start_s=0.505, duration_s=10,
                 checks=("authenticated_delivery", "no_corrupt_messages")))
    for loss in (2, 30, 300):
        add(case("A9", f"dropout_{loss}s", "assert", "full", mode="messages", fec="1/2", chunk_samples=48,
                 **preset("high_lat_moderate"), snr_db=30, dropout_start_s=2, dropout_duration_s=loss,
                 duration_s=loss+12, checks=("no_stale_messages",),
                 notes=["Continuous transmitter; no fabricated recovery preamble or receiver reset."]))
    for bw, db, attack, decay, mod in product(PROFILES, (-20, 20), (1, 10), (100, 1000), ("qpsk", "16qam", "64qam")):
        add(case("B1", f"{bw}_{mod}_{db}dB_{attack}_{decay}", "assert", "quick", bandwidth_hz=bw, modulation=mod,
                 agc_step_db=db, agc_attack_ms=attack, agc_decay_ms=decay, checks=("sync_held",)))
    for bw, mod, soft, top in product(PROFILES, ("qpsk", "16qam", "64qam"), (0, 1), (1, 5, 10)):
        add(case("B2", f"{bw}_{mod}_{'soft' if soft else 'hard'}_{top}pct", "characterize", "quick", bandwidth_hz=bw, modulation=mod,
                 soft_clip=soft, notes=[f"Calibrate threshold at top {top}% of clean waveform amplitude distribution."],
                 clipping_percent=top))
    for bw, ripple, mod in product(PROFILES, (0.5, 1, 2), ("qpsk", "16qam", "64qam")):
        add(case("B3", f"{bw}_{mod}_{ripple}ms", "characterize", "quick", bandwidth_hz=bw, modulation=mod,
                 filter_bandwidth_hz=bw, group_delay_ripple_ms=ripple,
                 notes=["Single-carrier modem: no edge subcarriers or frequency-indexed edge symbols. Report total BER."]))
    for event in ("jitter", "underrun", "overrun"):
        add(case("B4", event, "assert", "quick", mode="messages", fec="1/2", chunk_samples=48,
                 bandwidth_hz=10000,
                 jitter_ms=2 if event=="jitter" else 0, audio_event="" if event=="jitter" else event,
                 checks=("audio_gap_reported", "no_corrupt_messages")))
    for bw, mod in product(PROFILES, ("qpsk", "16qam", "64qam")):
        add(case("B5", f"{bw}_{mod}_null", "assert", "quick", bandwidth_hz=bw, modulation=mod,
                 mode="messages", fec="1/2", chunk_samples=48, duration_s=12,
                 host_timing=1,auction_intake=1,
                 checks=("latency_2_1ms", "source_events_on_tick"),
                 notes=["2.1 ms applies to added processing/buffering, per Adam. Paired one-sample reference reports intrinsic transmission/modem/FEC/startup delay separately; total source-to-sink remains reported."]))
        echo=ceil(PRESETS["high_lat_quiet"][0]*bw*0.8/1000)
        add(case("B5", f"{bw}_{mod}_polar_span_null", "assert", "full", bandwidth_hz=bw, modulation=mod,
                 mode="messages", fec="1/2", chunk_samples=48, duration_s=12, host_timing=1, auction_intake=1,
                 equalizer_feedforward_taps=2*echo+3, equalizer_feedback_taps=echo+4,
                 equalizer_delay_symbols=echo, training_symbols=256, checks=("latency_2_1ms", "source_events_on_tick"),
                 notes=["Null simulated channel with the longer high_lat_quiet equalizer configuration. Serial quiet-host measurement; the same 2.1 ms added-processing/buffering allowance applies."]))
    add(case("C1", "ber_tables", "characterize", "full", mode="analysis",
             notes=["Aggregate A1. Report BER targets as censored when comparisons are insufficient; no interpolation across unmeasured points."]))
    add(case("C1", "standard_comparison", "assert", "full", mode="capability",
             unavailable="Current waveform has different framing, FEC/interleaving and rate map; no comparable MIL-STD conformance assertion.",
             notes=["Appendix D Tables D-I/D-II omit 10 kHz; standard waveform IDs are not implemented."]))
    for bw,snr in product(PROFILES,(0, 3, 6, 10)):
        add(case("C2", f"{bw}_acquire_{snr}dB", "assert", "quick", bandwidth_hz=bw, snr_db=snr,
                 checks=("acquired",), thresholds=("C2.acquisition_seconds",)))
    add(case("C2", "noise_10min", "assert", "quick", duration_s=600, pure_noise=1, snr_db=0,
             checks=("zero_false_acquisitions",)))
    for bw in PROFILES:
        add(case("C2", f"{bw}_cw_preamble", "assert", "quick", bandwidth_hz=bw, cw_hz=0, cw_sir_db=0,
                 checks=("acquired",), thresholds=("C2.acquisition_seconds",)))
    for bw,sign in product(PROFILES,(-1, 1)):
        add(case("C3", f"{bw}_sample_{sign}", "assert", "quick", bandwidth_hz=bw, sample_slip=sign,
                 mode="messages",fec="1/2",chunk_samples=48,
                 sample_slip_index=24000+SEED%1000, checks=("correct_message_lengths",), thresholds=("C3.recovery_frames",)))
    for mode in ("bit_insert", "bit_delete"):
        add(case("C3", mode, "assert", "quick", mode="semantics", semantics=mode,
                 checks=("correct_message_lengths",), thresholds=("C3.recovery_frames",)))
    for bw, mod, pattern_name in product(PROFILES, ("qpsk", "16qam", "64qam"), ("zeros", "ones", "alternating", "repeating", "random")):
        add(case("C4", f"{bw}_{mod}_{pattern_name}", "assert", "quick", bandwidth_hz=bw, modulation=mod, pattern=pattern_name,
                 fec="1/2", snr_db=30, thresholds=("C4.pattern_ber_margin",)))
    add(case("C4", "generated_messages", "assert", "quick", mode="semantics", semantics="patterns",
             checks=("all_messages_delivered", "correct_message_lengths"),
             notes=["256 seeded variable-length messages, 2–1024 bytes; delimiter-safe payload grammar. The separate data_path regression also exercises the 65,535-byte application limit."]))
    add(case("C4", "empty_maximum_frames", "assert", "quick", mode="capability",
             unavailable="Empty RF frames are invalid; RF symbol count is configurable. The 65,535-byte application-message limit is covered separately by the data_path regression."))
    add(case("C5", "mode_change", "assert", "quick", mode="capability",
             unavailable="No mid-stream rate/interleaver change: matched parameters change by out-of-band epoch restart; interleaver absent."))
    for overload in (1.5, 3, 10):
        add(case("D1", f"overload_{overload}", "assert", "full", mode="scheduler", duration_s=60,
                 overload=overload, checks=("no_superseded_transmissions", "bounded_scheduler_queue"), thresholds=("D1.newest_latency_ms",)))
    for survival in (0.3, 0.5, 0.8):
        add(case("D2", f"survival_{survival}", "characterize", "full", mode="paired_survival", duration_s=60,
                 target_survival=survival,survival_calibration_presets=["mid_lat_moderate","ccir_good"],
                 survival_snr_grid_db=list(SNR_GRID),survival_refinement_rounds=8,
                 notes=["Preserve both declared SNR grids, then refine measured crossing brackets; never rescale receiver outcomes to match a target."]))
        add(case("D2", f"freshness_agreement_{survival}", "assert", "full", mode="analysis",
                 target_survival=survival, thresholds=("D2.freshness_agreement_ms","D2.target_survival_margin")))
    for flood in (0, 1):
        add(case("D3", f"auction_{'flood' if flood else 'contention'}", "assert", "quick", mode="scheduler",
                 duration_s=600, overload=10, flood=flood, checks=("no_starvation", "no_priority_inversion"), thresholds=("D3.instrument_delay_ms",)))
    for semantics in ("duplicate", "out_of_order", "wrap", "fec_failure"):
        add(case("D4", semantics, "assert", "quick", mode="semantics", semantics=semantics,
                 checks={"duplicate":("no_duplicates",), "out_of_order":("no_stale_messages",),
                         "wrap":("sequence_wrap_supported",), "fec_failure":("fec_gap_reported",)}[semantics]))
    add(case("D5", "dual_path", "assert", "quick", mode="capability",
             unavailable="Fiber is the configuration/control path; no parallel fiber data-delivery arbiter exists."))
    add(case("D6", "crypto_errors_replay_restart", "assert", "full", mode="crypto",
             checks=("authenticated_delivery", "no_nonce_reuse", "replays_rejected")))
    add(case("D6", "key_rotation", "assert", "full", mode="crypto", checks=("rotation_supported",), thresholds=("D6.rotation_loss_frames",)))
    for model in ("null", "watterson", "composed"):
        kwargs=preset("high_lat_moderate") if model!="null" else {}
        if model=="composed":kwargs|=dict(clock_ppm=50,impulse_ms=1,impulses_per_second=10,impulse_above_noise_db=20,agc_step_db=20)
        add(case("E1", model, "assert", "quick", mode="determinism", snr_db=20, checks=("identical_json", "chunk_invariant"), **kwargs))
    for name in PRESETS:
        add(case("E2", name, "characterize", "full", mode="messages", fec="1/2", chunk_samples=48,
                 **preset(name), snr_db=30, duration_s=60,
                 notes=["STAC detailed audit attachment requires login. Lock uptime and a local one-second delivery-window proxy are reported; exact STAC metrics remain null."]))
    add(case("E3", "high_lat_moderate_4h", "assert", "soak", mode="soak", **preset("high_lat_moderate"),
             duration_s=14400, fec="1/2", snr_db=30, chunk_samples=48,
             checks=("no_counter_drift",), thresholds=("E3.memory_growth_bytes", "E3.queue_depth", "E3.latency_change")))
    add(case("E4", "recorded_noise", "characterize", "full", mode="recording",
             unavailable="Awaiting receive-only recordings and provenance manifest; no synthetic substitute is labeled a recording."))
    cases.extend(polar_campaign())
    cases.extend(psk_campaign())
    return cases


RECOVERY_PROFILE = dict(compact_header=1, recovery_interval_frames=16,
                        fractionally_spaced_equalization=1, equalizer_reselect_interval=256)


def polar_campaign():
    """Declared A/B screens plus F.1487 duration-term message campaigns."""
    cases=[]
    variants={"legacy":{},"compact":dict(compact_header=1),
              "recovery":dict(compact_header=1,recovery_interval_frames=16),
              "reselect":dict(compact_header=1,recovery_interval_frames=16,equalizer_reselect_interval=256),
              "fractional":RECOVERY_PROFILE}
    for bw,mod,channel in product(PROFILES,("qpsk","16qam","64qam"),
                                  ("high_lat_quiet","high_lat_moderate","high_lat_disturbed")):
        echo=ceil(PRESETS[channel][0]*bw*.8/1000)
        span=dict(equalizer_feedforward_taps=2*echo+3,equalizer_feedback_taps=echo+4,
                  equalizer_delay_symbols=echo,training_symbols=max(256,2*(2*echo+3)))
        common=dict(bandwidth_hz=bw,modulation=mod,fec="1/2",snr_db=30,**span,**preset(channel))
        for variant,settings in variants.items():
            for group,mode in (("A2","rf"),("E2","messages")):
                cases.append(case(group,f"recovery_{bw}_{mod}_{channel}_{variant}","characterize","full",
                    **common,**settings,mode=mode,duration_s=10,chunk_samples=48 if mode=="messages" else 256,
                    auction_intake=1 if mode=="messages" else 0,
                    campaign="polar_screen",rf_profile=variant,
                    notes=["Matched-seed simulated channel A/B screen; raw RF results and production post-FEC message results are separate measurements."]))
        # This is a statistical planning target, not an acceptance threshold.
        # Even after marker overhead, 100/(1e-3*rate) is below the Doppler term
        # for these configurations. Report the exact two terms in the manifest.
        n=16*64;rate=bw*.8;sps=48000/rate;half=4
        controls=floor((64-1+half)*sps)+1+floor((span["training_symbols"]+166-1+half)*sps)+1
        symbols=n+max(8,span["equalizer_feedforward_taps"]+span["equalizer_feedback_taps"])+n//32*2+echo
        segment_samples=controls+floor((symbols-1+half)*sps)+1
        planned_rate=n*BITS[mod]*.5/(segment_samples/48000)
        duration=ceil(max(3000/PRESETS[channel][1],100/(1e-3*planned_rate)))
        cases.append(case("E2",f"polar_long_{bw}_{mod}_{channel}","characterize","full",**common,**RECOVERY_PROFILE,
            mode="messages",chunk_samples=48,duration_s=duration,aggregate_metrics=1,auction_intake=1,
            campaign="polar_long",rf_profile="fractional",planning_ber=1e-3,
            planned_user_bit_rate_bps=planned_rate,itu_doppler_duration_s=3000/PRESETS[channel][1],
            itu_bit_duration_s=100/(1e-3*planned_rate),
            notes=["F.1487 Annex 3 duration planning at BER 1e-3; production message delivery characterization, not a BER certification or a 1e-5-duration claim.",
                   "Independent seeds must be reported individually; aggregation counts every delivered message.",
                   "24 kHz Watterson is a bandwidth extrapolation beyond the Recommendation's validation scope."]))
    return cases


PSK_VARIANTS = {
    "qpsk_reference": dict(modulation="qpsk"),
    "qpsk_bpsk_header": dict(modulation="qpsk", header_modulation="bpsk"),
    "bpsk_qpsk_header": dict(modulation="bpsk"),
    "bpsk": dict(modulation="bpsk", header_modulation="bpsk"),
    "8psk_qpsk_header": dict(modulation="8psk"),
    "8psk_bpsk_header": dict(modulation="8psk", header_modulation="bpsk"),
    "16qam_reference": dict(modulation="16qam"),
    "64qam_reference": dict(modulation="64qam"),
    "dbpsk": dict(modulation="bpsk", header_modulation="bpsk", differential_mapping="dbpsk"),
    "dqpsk": dict(modulation="qpsk", header_modulation="bpsk", differential_mapping="dqpsk"),
    "pi4_dqpsk": dict(modulation="qpsk", header_modulation="bpsk", differential_mapping="pi4_dqpsk"),
}


def psk_campaign():
    """New matched PSK experiments; the original matrix/durations stay intact."""
    cases=[]
    for bw,variant in product(PROFILES,PSK_VARIANTS):
        settings=RECOVERY_PROFILE | PSK_VARIANTS[variant]
        common=dict(bandwidth_hz=bw,fec="1/2",rf_profile="psk",psk_variant=variant,**settings)
        cases.append(case("C4",f"psk_{bw}_{variant}_null","assert","quick",**common,
            mode="rf",duration_s=1,campaign="psk_quick",checks=("sync_held","no_frame_boundary_loss","zero_bit_errors")))
        for span in ("short","long"):
            geometry={} if span=="short" else dict(equalizer_feedforward_taps=2*ceil(bw*.8/1000)+3,
                equalizer_feedback_taps=ceil(bw*.8/1000)+4,equalizer_delay_symbols=ceil(bw*.8/1000),training_symbols=256)
            cases.append(case("B5",f"psk_{bw}_{variant}_{span}_null","assert","quick" if span=="short" else "full",
                **common,**geometry,mode="messages",chunk_samples=48,duration_s=12,host_timing=1,auction_intake=1,
                campaign="psk_latency",checks=("latency_2_1ms","source_events_on_tick")))
        for channel in ("high_lat_quiet","high_lat_moderate","high_lat_disturbed"):
            echo=ceil(PRESETS[channel][0]*bw*.8/1000)
            geometry=dict(equalizer_feedforward_taps=2*echo+3,equalizer_feedback_taps=echo+4,
                          equalizer_delay_symbols=echo,training_symbols=max(256,2*(2*echo+3)))
            for group,mode in (("A2","rf"),("E2","messages")):
                cases.append(case(group,f"psk_screen_{bw}_{variant}_{channel}","characterize","full",
                    **common,**geometry,**preset(channel),snr_db=30,mode=mode,chunk_samples=48 if mode=="messages" else 256,
                    duration_s=10,auction_intake=int(mode=="messages"),campaign="psk_screen",
                    notes=["Matched PSK screen; header-only variants retain identical payload modulation and equalizer geometry."]))
            # A separate, explicitly bounded follow-up, not a replacement for
            # the earlier 6000-second quiet campaign or an F.1487 duration claim.
            duration=100 if channel=="high_lat_disturbed" else 300
            cases.append(case("E2",f"psk_followup_{bw}_{variant}_{channel}","characterize","full",
                **common,**geometry,**preset(channel),snr_db=30,mode="messages",chunk_samples=48,
                duration_s=duration,aggregate_metrics=1,auction_intake=1,campaign="psk_followup",
                notes=["Matched new PSK follow-up: quiet/moderate/disturbed 300/300/100 s per seed; not F.1487 statistical-duration qualification.",
                       "The original 6000/300/100 s recovery campaign remains a separate result set; do not use unequal-duration runs as the before/after comparison."]))
    for bw,variant,snr in product(PROFILES,PSK_VARIANTS,SNR_GRID):
        settings=RECOVERY_PROFILE | PSK_VARIANTS[variant]
        cases.append(case("C1",f"psk_snr_{bw}_{variant}_{snr}dB","characterize","full",
            bandwidth_hz=bw,fec="1/2",rf_profile="psk",psk_variant=variant,**settings,
            mode="rf",duration_s=10,snr_db=snr,campaign="psk_snr",
            notes=["Null multipath plus AWGN; equal nominal symbol energy, all 0–30 dB points retained; no operating-limit assertion."]))
    return cases


def full_parameters(c, revision, source_digest):
    p=c.parameters.copy()
    bits=BITS[p["modulation"]]
    symbol_rate=p["bandwidth_hz"]/1.25
    p |= dict(stage_order=list(STAGE_ORDER), interleaver="none (not implemented)",
              measurement_layer={"rf":"RF symbols and optional post-Viterbi source bits", "messages":"production message pipeline",
                                 "scheduler":"auction submit to simulated transmitter service; downstream unmeasured",
                                 "semantics":"production framer/deframer API", "crypto":"production crypto API"}.get(p["mode"],p["mode"]),
              waveform="Goblin Cannon single-carrier RRC; not a certified Appendix D waveform",
              symbol_rate_hz=symbol_rate, raw_bit_rate_bps=symbol_rate*bits,
              snr_definition="nominal unit-mean-constellation complex-sample signal/noise power before fading; not 3 kHz SNR or Eb/N0",
              doppler_definition="2*sigma of Gaussian power spectrum; zero path carrier shifts",
              path_gains_db=[p["path0_db"],p["path1_db"]],
              stage_seeds=dict(gaussian_noise=p["seed"],impulses=p["seed"]^0x192734AF,
                               rayleigh_path0=p["seed"]^0x638AD923,rayleigh_path1=p["seed"]^0xC94F216B,
                               payload=p["seed"]^0xC011AB1E,interferer=p["seed"]^0xE294183B),
              path_power_normalization="sum of mean path powers = 1", seed_policy="mt19937 Box-Muller; independent XOR-derived stage seeds; counter-based payload",
              rrc_rolloff=0.25, shaping_span_symbols=8, tx_gain=0.65,
              constellation_profile="mil_std_188_110c_wbhf", receiver_oversampling=1,
              pilot_sequence=[0, (1<<bits)-1],
              header_repetition=3, acquisition_symbols=64, acquisition_seed=0xA5A50001,
              header_format="epoch32_counter64_crc32_conv_k7_rate_half" if p["compact_header"] else "legacy_32_byte_repeated",
              header_air_symbols=(332 if p["header_modulation"]=="bpsk" else 166) if p["compact_header"] else (768 if p["header_modulation"]=="bpsk" else 384),
              differential_detection=("coherent" if p["differential_mapping"]=="none" else "adjacent equalized complex sample product; absolute pilots restart reference; no frequency estimate"),
              differential_phase_degrees={"none":None,"dbpsk":[0,180],"dqpsk":[0,90,-90,180],"pi4_dqpsk":[45,135,-45,-135]}[p["differential_mapping"]],
              header_training_modulation="qpsk",
              papr_scope="finite clean pulse-shaped RF waveform, including acquisition, training, headers, pilots and tails; no PA model or power increase assumed",
              rf_payload_budget="requested audio seconds times complete-waveform payload duty; finite payload completed including partial-segment startup/tail",
              header_embedded_training=dict(interval_data_symbols=16,length_symbols=4,source="equalizer training sequence") if p["compact_header"] else None,
              training_seed=0x5A5A0002,
              equalizer=dict(enabled=bool(p["adaptive_equalization"]), feedforward_taps=p["equalizer_feedforward_taps"], feedback_taps=p["equalizer_feedback_taps"],
                             recursive_tracking=bool(p["recursive_equalization"]), rls_forgetting_factor=0.985,
                             samples_per_symbol=2 if p["fractionally_spaced_equalization"] else 1,
                             actual_feedforward_coefficients=(2*p["equalizer_feedforward_taps"]-1) if p["fractionally_spaced_equalization"] else p["equalizer_feedforward_taps"],
                             support_reselection_reliable_updates=p["equalizer_reselect_interval"],
                             support_candidate_estimator="shadow NLMS on inactive coefficients; active RLS coefficients retained",
                             rls_initial_covariance_diagonal=0.1, rls_maximum_covariance_diagonal=1.0,
                             recursive_common_phase_step=0.3, recursive_common_phase_frequency_estimator=False,
                             recursive_phase_detector="imag(forward * conjugate(desired - feedback)) / max(abs(desired - feedback)^2, 0.25)",
                             recursive_phase_scope="feedforward signal only; feedback decisions remain in the corrected constellation",
                             recursive_phase_decision_power_ratio_range=[0.7,1.5], recursive_phase_detector_limit=0.5,
                             decision_delay_symbols=p["equalizer_delay_symbols"], maximum_active_forward_taps=12, maximum_active_feedback_taps=12,
                             decision_directed_relative_error_limit_during_gain_change=0.1,
                             decision_gain_change_power_ratio_range=[0.7,1.5], gain_excursion_updates="known symbols only",
                             recursive_pilot_updates="supervised even on slicer disagreement",
                             pilot_gain_estimator="positive real least-squares scale",
                             pilot_gain_tracking=True, pilot_gain_phase_limit_rad=0.5 if p["recursive_equalization"] else 0.2,
                             pilot_gain_deadband=[0.95,1.05] if p["recursive_equalization"] else [0.8,1.25],
                             pilot_gain_trigger="power excursion; recursive tracking remains active until gain returns within 5% of baseline",
                             pilot_gain_power_ratio_trigger=[0.3,3], pilot_gain_power_ema=[0.125,0.002]),
              timing_recovery=dict(enabled=bool(p["sample_clock_recovery"]), detector="Gardner", proportional_gain=0.001,
                                   integral_gain=5e-7, maximum_clock_ppm=1000, rrc_table_steps_per_symbol=1024),
              thresholds=dict(acquisition=0.25,pilot=0.08,symbol=0.08),
              acquisition_sidelobe_guard_samples=48, frame_counter_start=7000,
              scheduler_transmit_ring_capacity=8, scheduler_log_ring_capacity=64,
              message_sequence_numbers=True, message_sequence_wire_bytes=5, maximum_message_bytes=65535,
              scheduler_policy="One replaceable bid until framer claim; newer same-key market update supersedes regardless of bid; highest bid per wire byte, newest on ties; no age boost",
              message_input_ring_capacity=1024, message_output_ring_capacity=1024,
              source_event_clock="Integral sample periods derived from event index; variable overload periods accumulated; source tick misses checked for aligned B5 events",
              sample_clock_resampler="linear fractional interpolation", audio_filter="129-tap Hamming-window FIR + two first-order edge allpasses",
              audio_jitter_model="Seeded block delay begins at audio_event_s; monotonic arrivals; production deadline check rejects arrivals beyond declared playout slack",
              gaussian_fading_filter="129 taps at 32*spread Hz; stationary initialized history; linear audio interpolation",
              agc_envelope="linear dB attack to requested step; 50 ms hold; linear dB decay to baseline",
              impulse_arrivals="periodic at declared rate; Gaussian burst RMS relative to Gaussian floor",
              crypto="AES-128-CTR, fixed test key/counter, no AEAD", sync_timestamp_enabled=False,
              aes_key_generation="16 low bytes of seeded counter pattern" if p["mode"]=="crypto" else "16 zero bytes (test fixture only)",
              aes_initial_counter_hex="00"*16, convolutional_constraint_length=7,
              convolutional_generators_octal=["171","133"], decoded_bit_confidence_threshold=0.20,
              git_commit=revision, source_tree_sha256=source_digest,
              source_revision_note="git_commit is the base revision; source_tree_sha256 identifies the tested working-tree snapshot",
              modeled_propagation_delay_s=0, execution="simulated channel")
    return p
