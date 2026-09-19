"""Quick/assert E1 unit checks for the simulated channel harness itself."""
import copy
import json
import unittest
import hashlib
from pathlib import Path
import subprocess

from catalog import matrix, full_parameters, DEFAULTS, OPEN_THRESHOLDS
from metrics import summarize, percentiles, latency_above_reference
from run import canonical, evaluate
from channel_metadata import normalize_parameters, normalize_record, DOPPLER_SPREAD_DEFINITION

ROOT = Path(__file__).resolve().parents[2]


class SimulatedChannelHarness(unittest.TestCase):
    tier="quick"
    kind="assert"
    group="E1"

    def test_matrix_identity_and_markers(self):
        cases=matrix()
        self.assertEqual(len(cases),len({c.name for c in cases}))
        for c in cases:
            self.assertIn(c.tier,("quick","full","soak"))
            self.assertIn(c.kind,("assert","characterize"))
            self.assertTrue(DEFAULTS.keys()<=c.parameters.keys())
            self.assertTrue(set(c.thresholds)<=OPEN_THRESHOLDS.keys())
        self.assertEqual(sum(c.group=="A1" for c in cases),2*10*3*9*16)
        for c in cases:
            if c.group=="A4" and ("10min" in c.name):
                self.assertEqual(c.parameters["duration_s"],600)

    def test_parameters_are_complete_and_json_finite(self):
        for c in matrix():
            p=full_parameters(c,"test-commit","test-snapshot")
            for name in ("channel_model","delay_spread_ms","doppler_spread_hz","snr_db",
                         "cw_sir_db","frame_symbols","symbol_rate_hz","fec","interleaver",
                         "seed","git_commit","source_tree_sha256","stage_order"):
                self.assertIn(name,p)
            self.assertEqual(json.loads(canonical(p)),p)

    def test_all_908_published_records_parse_without_changes(self):
        manifest=json.loads(Path(__file__).with_name("recorded_runs.json").read_text())
        self.assertEqual(len(manifest),908)
        watterson=offsets=drifts=0
        for name,digest in manifest.items():
            raw=(ROOT/name).read_bytes()
            self.assertEqual(hashlib.sha256(raw).hexdigest(),digest,name)
            original=json.loads(raw)
            record=normalize_record(original,warn=False)
            self.assertEqual(record["metrics"],original["metrics"],name)
            p=record["parameters"]
            self.assertEqual(p["carrier_correction"],0,name)
            self.assertEqual(p["doppler_spread_hz"],original["parameters"]["doppler_spread_hz"],name)
            self.assertEqual(p["doppler_spread_definition"],DOPPLER_SPREAD_DEFINITION,name)
            self.assertIn("doppler_definition",original["parameters"],name)
            offsets+=bool(p["residual_offset_hz"])
            drifts+=bool(p["residual_drift_hz_per_second"])
            if p["channel_model"]=="watterson":
                watterson+=1
                self.assertEqual(p["doppler_shift_hz"],[0,0],name)
                self.assertEqual(p["residual_offset_hz"],0,name)
                self.assertEqual(p["residual_drift_hz_per_second"],0,name)
        self.assertEqual((watterson,offsets,drifts),(722,1,1))

    def test_deprecated_channel_aliases_and_conflicts(self):
        for name in ("doppler","doppler_hz"):
            with self.assertWarns(DeprecationWarning):
                self.assertEqual(normalize_parameters({name:30}),{"doppler_spread_hz":30})
            with self.assertRaises(ValueError):
                normalize_parameters({name:30,"doppler_spread_hz":15})
        with self.assertWarns(DeprecationWarning):
            self.assertEqual(normalize_parameters({"itu_doppler_duration_s":100}),
                             {"itu_doppler_spread_duration_s":100})

    def test_probe_deprecated_spread_inputs_match_canonical(self):
        binary=ROOT/"build/goblin_cannon_simulated_channel_probe"
        if not binary.exists():
            self.skipTest("compiled C++ simulation probe is not available on this host")
        base=[str(binary),"mode=model","channel_model=watterson","duration_s=0.1","require_avx512=0"]
        canonical_result=subprocess.run(base+["doppler_spread_hz=30"],capture_output=True,check=True,text=True)
        for name in ("doppler","doppler_hz"):
            alias_result=subprocess.run(base+[f"{name}=30"],capture_output=True,check=True,text=True)
            self.assertEqual(alias_result.stdout,canonical_result.stdout)
            self.assertIn("deprecated",alias_result.stderr)
            conflict=subprocess.run(base+[f"{name}=30","doppler_spread_hz=15"],capture_output=True,text=True)
            self.assertNotEqual(conflict.returncode,0)

    def test_unobserved_bits_are_not_zero_ber(self):
        m=summarize(dict(bits_sent=1000,bits_compared=0,bit_errors=0,frames_sent=10,frames_survived=0))
        self.assertIsNone(m["ber"])
        self.assertEqual(m["bit_observation_fraction"],0)
        self.assertEqual(m["frame_survival_fraction"],0)
        self.assertEqual(m["frame_error_rate"],1)
        self.assertIsNone(m["latency_ms"]["p99_9"])

    def test_metric_denominators(self):
        m=summarize(dict(bits_sent=1000,bits_compared=800,bit_errors=8,frames_sent=10,
                         frames_survived=7,simulated_seconds=2,useful_bits_delivered=600,
                         locked_seconds=1,latency_ms=[1,2,3]))
        self.assertEqual(m["ber"],.01)
        self.assertEqual(m["frame_error_rate"],.3)
        self.assertEqual(m["frame_survival_fraction"],.7)
        self.assertEqual(m["goodput_bps"],300)
        self.assertEqual(m["uptime_fraction"],.5)

    def test_percentiles_and_missing_values(self):
        self.assertEqual(percentiles(list(range(1,1001))),dict(p50=500,p99=990,p99_9=999,max=1000))
        self.assertTrue(all(x is None for x in percentiles([]).values()))

    def test_latency_attribution_pairs_messages_and_requires_coverage(self):
        reference=dict(delivered_ids=[1,2,3],latency_ms=[20,10,4])
        raw=dict(delivered_ids=[3,1],latency_ms=[5,20.5],host_latency_ms=[6,21])
        self.assertEqual(latency_above_reference(raw,reference),[1,.5])
        self.assertEqual(latency_above_reference(raw,reference,"host_latency_ms"),[2,1])
        with self.assertRaises(ValueError):
            latency_above_reference(raw,dict(delivered_ids=[1],latency_ms=[20]))
        with self.assertRaises(ValueError):
            latency_above_reference(dict(delivered_ids=[1,1],latency_ms=[1,2]),reference)

    def test_expected_failure_does_not_mask_a_new_assertion(self):
        c=next(c for c in matrix() if c.group=="A8")
        raw=dict(aead_supported=0,corrupted_messages_delivered=1)
        known={c.name+".authenticated_delivery":"Known lack of AEAD."}
        status,checks=evaluate(c,raw,summarize(raw),known)
        self.assertEqual(status,"fail")
        self.assertEqual([r["status"] for r in checks],["xfail","fail"])
        raw.update(aead_supported=1,authentication_failure_counter_available=1,authentication_failures=0)
        status,checks=evaluate(c,raw,summarize(raw),known)
        self.assertEqual(checks[0]["status"],"xpass")

    def test_characterization_does_not_acquire_acceptance_thresholds(self):
        c=next(c for c in matrix() if c.group=="A1")
        status,checks=evaluate(c,{},summarize({}),{})
        self.assertEqual(status,"characterized")
        self.assertEqual(checks,[])

    def test_result_serialization_is_stable(self):
        c=matrix()[0]
        one=full_parameters(c,"commit","digest")
        two=copy.deepcopy(one)
        self.assertEqual(canonical(one),canonical(two))

    def test_polar_campaign_keeps_declared_durations(self):
        cases=[c for c in matrix() if c.parameters.get("campaign")=="polar_long"]
        self.assertEqual(len(cases),18)
        for c in cases:
            p=c.parameters
            self.assertGreaterEqual(p["duration_s"],p["itu_doppler_spread_duration_s"])
            self.assertGreaterEqual(p["duration_s"],p["itu_bit_duration_s"])
            self.assertEqual(p["carrier_correction"],0)
            self.assertEqual(c.kind,"characterize")
            self.assertTrue(p["aggregate_metrics"])

    def test_aggregate_delivery_metrics_keep_every_observation(self):
        p=dict(p50=1,p99=3,p99_9=3,max=3,observations=1000)
        m=summarize(dict(simulated_seconds=10,latency_sample_clock_ms=p,
                         messages_delivered=1000,messages_created=1200,messages_consumed_by_framer=1100,
                         usable_window_seconds=8,delivery_silence_ms=p))
        self.assertEqual(m["latency_ms"],p)
        self.assertEqual(m["message_delivery_fraction_of_framed"],1000/1100)
        self.assertEqual(m["usable_time_fraction"],.8)
        self.assertNotIn("latency_ms",m["missing_metric_reasons"])

    def test_psk_campaign_preserves_boundary_and_declared_durations(self):
        cases=[c for c in matrix() if c.parameters.get("rf_profile")=="psk"]
        self.assertEqual(sum(c.parameters["campaign"]=="psk_screen" for c in cases),132)
        self.assertEqual(sum(c.parameters["campaign"]=="psk_followup" for c in cases),66)
        self.assertEqual(sum(c.parameters["campaign"]=="psk_snr" for c in cases),352)
        for c in cases:
            p=full_parameters(c,"commit","digest")
            self.assertEqual(p["carrier_correction"],0)
            self.assertTrue(p["adaptive_equalization"] and p["sample_clock_recovery"])
            self.assertEqual(p["header_air_symbols"],332 if p["header_modulation"]=="bpsk" else 166)
            if p["campaign"]=="psk_followup":
                self.assertEqual(p["duration_s"],100 if "disturbed" in c.name else 300)
            # Unknown assertion names must fail here, before expensive runs.
            evaluate(c,{},summarize({}),{})

    def test_encoding_campaign_has_real_parameters_and_fixed_power(self):
        cases=[c for c in matrix() if c.parameters.get("rf_profile")=="encoding"]
        self.assertEqual(sum(c.parameters["campaign"]=="encoding_quick" for c in cases),84)
        self.assertEqual(sum(c.parameters["campaign"]=="encoding_followup" for c in cases),126)
        for c in cases:
            p=full_parameters(c,"commit","digest")
            self.assertEqual(p["carrier_correction"],0)
            if p["campaign"]=="encoding_followup" and not p["audio_waveform"].startswith("fsk"):
                from math import ceil
                echo=ceil(p["delay_spread_ms"]*p["symbol_rate_hz"]/1000)
                self.assertEqual(p["equalizer_feedforward_taps"],2*echo+3)
                self.assertEqual(p["equalizer_feedback_taps"],echo+4)
                self.assertEqual(p["training_symbols"],max(256,2*(2*echo+3)))
            self.assertAlmostEqual(p["nominal_sample_power"],(.65*p["tx_gain_multiplier"])**2)
            if p["campaign"]=="encoding_followup":
                self.assertEqual(p["duration_s"],100 if "disturbed" in c.name else 300)
            if p["audio_waveform"].startswith("fsk"):
                self.assertEqual(p["shaping_span_symbols"],0)
                self.assertEqual(p["symbol_rate_hz"],1000/(p["fsk_useful_ms"]+p["fsk_guard_ms"]))
                self.assertFalse(p["equalizer"]["enabled"])
            if p["fec"]=="k9-1/3":
                self.assertEqual(p["convolutional_generators_octal"],["557","663","711"])
            evaluate(c,{},summarize({}),{})

    def test_refinement_comparisons_hold_power_rate_and_delays(self):
        from collections import Counter
        cases=[c for c in matrix() if c.parameters.get("rf_profile")=="refinement"]
        self.assertEqual(Counter(c.parameters["campaign"] for c in cases),dict(
            refinement_quick=92,refinement_latency=46,refinement_screen=138,
            refinement_followup=138,refinement_delay=72,refinement_snr=192))
        for c in cases:
            p=full_parameters(c,"commit","digest")
            self.assertFalse(p["carrier_correction"])
            self.assertTrue(p["adaptive_equalization"] and p["sample_clock_recovery"])
            self.assertAlmostEqual(p["nominal_sample_power"],(.65*p["tx_gain_multiplier"])**2)
            self.assertLess(p["cadence_plan"]["payload_airtime_fraction"],1)
            if p["experiment"]=="diversity":
                d=p["diversity"]
                self.assertEqual(p["symbol_rate_hz"],p["bandwidth_hz"]*.4/1.25)
                self.assertLessEqual(d["occupied_span_hz"],p["bandwidth_hz"])
                self.assertEqual(d["branches"]*d["per_branch_power_fraction"],1)
                if p["channel_model"]=="watterson":
                    self.assertGreaterEqual(d["center_response_correlation_magnitude"],0)
                    self.assertLessEqual(d["center_response_correlation_magnitude"],1+1e-15)
            if p["campaign"]=="refinement_followup":
                self.assertEqual(p["duration_s"],100 if "disturbed" in c.name else 300)
            evaluate(c,{},summarize({}),{})


    def test_disturbed_ablation_preserves_channel_and_authentication(self):
        cases=[c for c in matrix() if c.parameters.get("campaign")=="disturbed_followup"]
        indexed={c.name:c for c in cases}
        for c in cases:
            p=full_parameters(c,"commit","digest")
            self.assertEqual(p["aead_tag_bytes"],16)
            self.assertFalse(p["carrier_correction"])
            self.assertEqual(p["duration_s"],100 if p["delay_spread_ms"]==7 else 300)
            if p["recovery_variant"]=="baseline":continue
            base=indexed[c.name.rsplit("_",1)[0]+"_baseline"].parameters
            for key in ("seed","snr_db","delay_spread_ms","doppler_spread_hz","path0_db","path1_db","duration_s","tx_gain_multiplier"):
                self.assertEqual(p[key],base[key])
            if p["compact_message_header"]:self.assertEqual(p["aead_header_bytes"],13)


if __name__=="__main__":
    unittest.main()
