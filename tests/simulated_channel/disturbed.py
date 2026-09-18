"""Declared simulated channel recovery experiment; fixed grids and durations."""
from itertools import product
from math import ceil


def campaign():
    from catalog import case, preset, PRESETS, RECOVERY_PROFILE, refinement_span, REFINEMENT_CODING
    cases = []
    for band, variant in product((10000, 24000), REFINEMENT_CODING):
        settings = dict(RECOVERY_PROFILE, bandwidth_hz=band, fec="1/2", soft_demapping=1,
                        modulation=variant.split("_")[0], bch_payload=int(variant.endswith("bch")),
                        rf_profile="disturbed", refinement_variant=variant)
        for channel in ("high_lat_quiet", "high_lat_moderate", "high_lat_disturbed"):
            span = refinement_span(band, settings, PRESETS[channel][0])
            short = dict(training_symbols=max(128, ceil(1.4*span["equalizer_feedforward_taps"])),
                         recovery_interval_frames=8)
            variants = dict(baseline={}, combined=dict(warm_recovery=1, elapsed_time_tracking=1,
                                                      compact_message_header=1, **short))
            if channel == "high_lat_disturbed" and variant in ("bpsk_bch", "qpsk_bch"):
                variants.update(warm=dict(warm_recovery=1, **short),
                                time=dict(elapsed_time_tracking=1), compact=dict(compact_message_header=1))
            for change, options in variants.items():
                common = settings | span | preset(channel) | options
                name = f"disturbed_{band}_{variant}_{channel}_{change}"
                cases.append(case("A2", name, "characterize", "full", **common, mode="rf", snr_db=30,
                    duration_s=10, campaign="disturbed_screen", recovery_variant=change))
                cases.append(case("E2", name, "characterize", "full", **common, mode="messages", snr_db=30,
                    duration_s=100 if channel.endswith("disturbed") else 300, chunk_samples=48,
                    aggregate_metrics=1, auction_intake=1, campaign="disturbed_followup", recovery_variant=change,
                    notes=["Fixed power after RRC calibration; full 128-bit authentication tag; carrier correction off.",
                           "Baseline and changed receivers use identical channel seeds; finite trace comparisons are characterization."]))
        # The full new signal path must retain null-channel correctness.
        clean = settings | dict(warm_recovery=1, elapsed_time_tracking=1, compact_message_header=1,
                                training_symbols=128, recovery_interval_frames=8)
        for group, mode in (("C4", "rf"), ("D4", "messages")):
            checks = ("sync_held", "no_frame_boundary_loss", "zero_bit_errors") if mode=="rf" else (
                "messages_observed", "no_corrupt_messages", "no_duplicates")
            cases.append(case(group, f"disturbed_{band}_{variant}_null", "assert", "quick", **clean,
                mode=mode, duration_s=3, chunk_samples=48, auction_intake=int(mode=="messages"),
                campaign="disturbed_quick", checks=checks))
        span=refinement_span(band,settings,7)
        latency=clean | span | dict(training_symbols=max(128,ceil(1.4*span["equalizer_feedforward_taps"])))
        cases.append(case("B5",f"disturbed_{band}_{variant}_latency","assert","full",**latency,
            mode="messages",duration_s=12,chunk_samples=48,host_timing=1,auction_intake=1,
            campaign="disturbed_latency",checks=("latency_2_1ms","source_events_on_tick"),
            notes=["Quiet-host null simulated channel with the actual 7 ms disturbed equalizer span; transmission/modem residence reported separately."]))
    # Same observed two-path channel for both branches; these are NOT
    # independent fading realizations. Fixed geometry declared before runs.
    for band, spacing, mask in product((10000,24000), ("commensurate","offset137","wide137"), (1,2,3)):
        separation = {"commensurate":band*.5,"offset137":band*.5+137,"wide137":band*.55+137}[spacing]
        branch = {1:"lower",2:"upper",3:"both"}[mask]
        settings = dict(RECOVERY_PROFILE, bandwidth_hz=band, fec="1/2", soft_demapping=1,
            modulation="bpsk", bch_payload=1, audio_waveform="bpsk_frequency_diversity",
            diversity_branch_bandwidth_hz=band*.4, diversity_separation_hz=separation, diversity_branch_mask=mask,
            warm_recovery=1, elapsed_time_tracking=1, compact_message_header=1,
            rf_profile="disturbed", refinement_variant=f"diversity_{spacing}_{branch}")
        for channel in ("high_lat_moderate","high_lat_disturbed"):
            span=refinement_span(band,settings,PRESETS[channel][0])
            common=settings | span | preset(channel) | dict(training_symbols=max(128,ceil(1.4*span["equalizer_feedforward_taps"])),recovery_interval_frames=8)
            cases.append(case("E2", f"disturbed_{band}_diversity_{spacing}_{branch}_{channel}", "characterize","full",
                **common,mode="messages",snr_db=30,duration_s=100 if channel.endswith("disturbed") else 300,
                chunk_samples=48,aggregate_metrics=1,auction_intake=1,campaign="disturbed_diversity"))
        for delay in (6.75,7.25):
            span=refinement_span(band,settings,delay)
            common=settings | span | dict(training_symbols=max(128,ceil(1.4*span["equalizer_feedforward_taps"])),recovery_interval_frames=8)
            cases.append(case("A2",f"disturbed_{band}_diversity_{spacing}_{branch}_{delay}ms","characterize","full",
                **common,channel_model="watterson",delay_spread_ms=delay,doppler_spread_hz=30,snr_db=30,
                mode="messages",duration_s=100,chunk_samples=48,aggregate_metrics=1,auction_intake=1,campaign="disturbed_delay"))
    return cases
