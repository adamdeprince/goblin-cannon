"""Metrics and assertions for the simulated channel. Missing data stays null."""
from __future__ import annotations

import math


def ratio(numerator, denominator):
    return numerator/denominator if denominator else None


def percentiles(values):
    values=sorted(values)
    if not values:
        return dict(p50=None, p99=None, p99_9=None, max=None)
    def pick(p):
        return values[max(0, math.ceil(p*len(values))-1)]
    return dict(p50=pick(.5), p99=pick(.99), p99_9=pick(.999), max=values[-1])


def latency_above_reference(raw, reference, latency_key="latency_ms"):
    """Paired by message identity, not by percentile subtraction.

    Keep signed differences so a reference mismatch cannot be hidden by clipping.
    Missing reference deliveries invalidate the comparison instead of silently
    selecting the subset that happened to arrive in both runs.
    """
    ref_ids=reference.get("delivered_ids", [])
    ids=raw.get("delivered_ids", [])
    values=raw.get(latency_key, [])
    if len(ref_ids)!=len(set(ref_ids)) or len(ids)!=len(set(ids)):
        raise ValueError("duplicate message identity in latency comparison")
    if len(values)!=len(ids) or len(reference.get("latency_ms", []))!=len(ref_ids):
        raise ValueError("latency and identity counts differ")
    baseline=dict(zip(ref_ids,reference.get("latency_ms", [])))
    missing=[identity for identity in ids if identity not in baseline]
    if missing:
        raise ValueError(f"{len(missing)} delivered messages have no intrinsic-latency reference")
    return [latency-baseline[identity] for identity,latency in zip(ids,values)]


def summarize(raw):
    duration=raw.get("simulated_seconds", 0)
    sent=raw.get("frames_sent", 0)
    survived=raw.get("frames_survived", 0)
    metrics=dict(
        fresh_goodput_bps=ratio(raw.get("fresh_useful_bits_delivered",0),duration) if "fresh_useful_bits_delivered" in raw else None,
        ber=ratio(raw.get("bit_errors", 0), raw.get("bits_compared", 0)),
        coded_ber=ratio(raw.get("coded_bit_errors", 0), raw.get("coded_bits_compared", 0)),
        bit_observation_fraction=ratio(raw.get("bits_compared", 0), raw.get("bits_sent", 0)),
        frame_error_rate=ratio(sent-survived, sent),
        frame_survival_fraction=ratio(survived, sent),
        goodput_bps=ratio(raw["useful_bits_delivered"], duration) if "useful_bits_delivered" in raw else None,
        uptime_fraction=ratio(raw.get("locked_seconds", 0), duration) if "locked_seconds" in raw else None,
        usable_time_fraction=None,
        stac_adjusted_goodput=None, stac_usable_time_fraction=None,
        acquisition_time_s=raw.get("acquisition_time_s"),
        reacquisition_time_s=raw.get("reacquisition_time_s"),
        latency_ms=percentiles(raw.get("latency_ms", [])),
        added_software_latency_ms=percentiles(raw.get("added_software_latency_ms", [])),
        message_survival_fraction=ratio(raw["messages_delivered"], raw.get("messages_created", 0)) if "messages_delivered" in raw else None,
        freshness_ms=percentiles(raw.get("latency_ms", [])),
        message_delivery_fraction_of_framed=ratio(raw.get("messages_delivered",0),raw.get("messages_consumed_by_framer",0)),
        first_lock_loss_s=raw.get("first_lock_loss_s"),
        first_message_delivery_s=raw.get("first_message_delivery_s"),
        delivery_silence_ms=raw.get("delivery_silence_ms"),
        rf_recovery_ms=raw.get("rf_recovery_ms"),
        unrecovered_rf_outage_s=raw.get("unrecovered_rf_outage_s"),
        terminal_delivery_silence_s=raw.get("terminal_delivery_silence_s"),
    )
    if "latency_sample_clock_ms" in raw:
        metrics["latency_ms"]=metrics["freshness_ms"]=raw["latency_sample_clock_ms"]
    if "usable_window_seconds" in raw:
        metrics["usable_time_fraction"]=ratio(raw["usable_window_seconds"],duration)
    if "delivery_times_s" in raw and duration:
        # Explicit local proxy, not an assertion of STAC definition equivalence.
        occupied={int(t) for t in raw["delivery_times_s"] if 0<=t<duration}
        metrics["usable_time_fraction"]=sum(min(1.,duration-t) for t in occupied)/duration
    for source,target in (("newest_latency_ms_by_key","newest_latency_ms_by_key"),
                          ("latency_ms_by_window","latency_ms_by_window")):
        if source in raw:metrics[target]={key:percentiles(values) for key,values in raw[source].items()}
    if "agc_affected_frames" in raw:
        metrics["agc_affected_frame_error_rate"]=ratio(raw["agc_affected_frames"]-raw["agc_affected_frames_survived"],raw["agc_affected_frames"])
    if "boundary_probe" in raw:
        metrics["recovery_after_sample_slip_frames"]=raw["boundary_probe"]["observations"].get("recovery_after_sample_slip_frames")
    metrics["missing_metric_reasons"]={
        "stac_adjusted_goodput":"Audit attachment requires login; adjustment and standby definitions unverified.",
        "stac_usable_time_fraction":"No production standby-time instrumentation; local proxy is separately labeled.",
    }
    if not raw.get("bits_compared"):
        metrics["missing_metric_reasons"]["ber"]="No comparable RF bits observed, or this probe does not expose bit decisions."
    if not raw.get("latency_ms") and not raw.get("latency_sample_clock_ms",{}).get("observations"):
        metrics["missing_metric_reasons"]["latency_ms"]="No messages delivered, or this is a symbol-level probe."
    if "useful_bits_delivered" not in raw:
        metrics["missing_metric_reasons"]["goodput_bps"]="Probe does not observe delivered application/RF bits."
    if not raw.get("reacquisition_time_s"):
        metrics["missing_metric_reasons"]["reacquisition_time_s"]="No post-dropout valid header observed, or no dropout in this case."
    return metrics


def check(name, raw, metrics):
    """Return the violated requirement, or None. No implicit BER tolerance."""
    conditions={
        "zero_bit_errors":(raw.get("bits_compared",0)>0 and raw.get("bit_errors",1)==0,"Null simulated channel did not produce bit-exact payload decisions."),
        "sync_held":(raw.get("valid_headers",0)>0 and raw.get("lock_losses",0)==0 and raw.get("symbols_received",0)>=raw.get("symbols_sent",1),"Receiver did not hold sync for the complete payload."),
        "no_frame_boundary_loss":(raw.get("valid_headers",0)>0 and raw.get("frame_boundary_errors",0)==0 and raw.get("frames_complete",0)==raw.get("frames_sent",1),"Missing or misaligned frame boundaries after clock/sample impairment."),
        "acquired":(raw.get("valid_headers",0)>0,"No validated stream header at the requested acquisition condition."),
        "zero_false_acquisitions":(raw.get("acquisitions",0)==0,"Pure noise caused a preamble acquisition during the full 600-second trace."),
        "authenticated_delivery":(raw.get("aead_supported",0)==1 and raw.get("authentication_failure_counter_available",0)==1 and "authentication_failures" in raw and ("tamper_attempts" not in raw or raw["tamper_attempts"]>0 and raw["authentication_failures"]==raw["tamper_attempts"] and raw.get("corrupted_messages_delivered",1)==0),"AEAD verification/counter evidence is missing, a tampered record escaped, or rejection was not counted."),
        "messages_observed":(raw.get("messages_delivered",0)>0,"No message delivery observed."),
        "no_corrupt_messages":(raw.get("corrupted_messages_delivered",0)==0,"A delivered application message differs from the source."),
        "no_stale_messages":(raw.get("messages_delivered",0)>0 and raw.get("stale_messages_delivered",0)==0,"Stale messages were delivered, or no delivery established this property."),
        "audio_gap_reported":(raw.get("audio_gap_api",0)==1,"Injected audio discontinuities/deadline misses did not produce the expected downstream gap events."),
        "latency_2_1ms":(metrics["added_software_latency_ms"]["p99_9"] is not None and metrics["added_software_latency_ms"]["p99_9"]<=2.1,"Added software/buffering p99.9 exceeds 2.1 ms, or no paired deliveries were measured."),
        "source_events_on_tick":(raw.get("source_tick_misses",1)==0,"An integral-sample source event missed its aligned simulated audio tick."),
        "correct_message_lengths":(raw.get("wrong_length_or_payload_delivered",0)==0,"Deframer delivered a message with an unexpected payload or length."),
        "all_messages_delivered":(raw.get("messages_delivered",0)==raw.get("messages_created",1),"Generated valid messages failed to round-trip exactly."),
        "no_superseded_transmissions":(raw.get("superseded_messages_transmitted",0)==0 and raw.get("pipeline",{}).get("observations",{}).get("superseded_messages_consumed",0)==0,"The auction transmitted or passed to the framer a message superseded at its source key."),
        "bounded_scheduler_queue":(raw.get("queue_depth_max",0)<=9,"Queue exceeded its configured capacity (8) plus the single pending bid."),
        "no_starvation":(raw.get("starved_instruments",0)==0,"At least one contending instrument received no airtime in 600 seconds."),
        "no_priority_inversion":(raw.get("priority_inversions",0)==0,"A queued lower-priority winner transmitted before a ready higher-priority bid."),
        "no_duplicates":(raw.get("duplicate_messages_delivered",0)==0,"Receiver delivered a repeated valid message again."),
        "sequence_wrap_supported":(raw.get("sequence_number_api",0)==1,"The message envelope has no sequence number or wraparound semantics."),
        "fec_gap_reported":(raw.get("explicit_fec_gap_api",0)==1,"Uncertain/FEC-failed data is discarded without a downstream gap event."),
        "no_nonce_reuse":(raw.get("nonces_observed",0)>=16 and raw.get("reused_nonces_after_process_restart",1)==0,"Distinct sender processes reused an AES-GCM nonce or supplied no restart evidence."),
        "replays_rejected":(raw.get("replay_rejections",0)>0 and raw.get("replay_deliveries",1)==0,"Replayed authenticated records reached the sink, or no rejection was exercised."),
        "rotation_supported":(raw.get("coordinated_key_rotation_api",0)==1,"Authenticated key IDs and fresh-epoch restart exist; two-key overlap and coordinated mid-stream retirement are not implemented."),
        "identical_json":(raw.get("identical_json",0)==1,"Repeated seeded probe output is not byte-identical."),
        "chunk_invariant":(raw.get("chunk_invariant",0)==1,"Changing input chunk boundaries changed the simulated channel samples."),
        "no_counter_drift":(raw.get("messages_delivered",0)>0 and raw.get("counter_drift",1)==0,"Invalid delivered counters were observed, or no deliveries established the soak counter property."),
    }
    ok,reason=conditions[name]
    return None if ok else reason


METRIC_DEFINITIONS = {
    "ber":"erroneous bits / compared received RF bits; lost bits excluded and observation fraction reported",
    "coded_ber":"post-payload-FEC bit errors / compared decoded source bits; missing data is not zero BER",
    "frame_error_rate":"(missing + corrupted RF symbol frames) / transmitted frames",
    "frame_survival_fraction":"complete, bit-exact RF symbol frames / transmitted frames",
    "goodput_bps":"delivered useful message bits/s for message probes; error-free raw RF frame bits/s for RF probes (not application goodput)",
    "uptime_fraction":"receiver-locked simulated sample time / complete observation time, including startup",
    "usable_time_fraction":"local proxy: fraction of one-second windows containing at least one correct delivered message; not the STAC audited definition",
    "latency_ms":"creation at source to delivery at sink on the simulated sample clock, including startup and audio block residence; excludes unmeasured CPU/OS/device time",
    "added_software_latency_ms":"per-message source-to-sink latency minus a paired one-sample-block production-stack reference; retains signed differences; reference includes serialization, modem/FEC and epoch startup",
    "latency_percentiles":"nearest-rank p50, p99, p99.9 and max; null if no deliveries",
    "reacquisition_time_s":"first validated header after dropout end minus dropout end; null when no recovery observed",
    "message_delivery_fraction_of_framed":"correct messages delivered / messages claimed by the production framer, including startup and terminal censoring; excludes source auction rejections",
    "delivery_silence_ms":"correct-delivery intervals, including startup and right-censored ending, at audio sample-clock resolution; no outage threshold assumed",
    "rf_recovery_ms":"declared RF lock loss to next validated header, excluding planned marker transitions; incomplete outage reported separately",
}
