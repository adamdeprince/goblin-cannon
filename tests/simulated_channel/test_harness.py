"""Quick/assert E1 unit checks for the simulated channel harness itself."""
import copy
import json
import unittest

from catalog import matrix, full_parameters, DEFAULTS, OPEN_THRESHOLDS
from metrics import summarize, percentiles, latency_above_reference
from run import canonical, evaluate


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
        raw["aead_supported"]=1
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
            self.assertGreaterEqual(p["duration_s"],p["itu_doppler_duration_s"])
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


if __name__=="__main__":
    unittest.main()
