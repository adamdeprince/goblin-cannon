#!/usr/bin/env python3
"""Simulated channel CLI/protobuf serialization checks; no RPC is sent."""
import json
import sys
from pathlib import Path
from google.protobuf.json_format import MessageToDict

import configure_local_radios as cli
from market_config import ensure_python_grpc_stubs


def main():
    pb, _ = ensure_python_grpc_stubs()
    cases = []
    for mode in ("qpsk", "8psk"):
        for pilot, recovery in ((16,16), (32,16), (64,16), (32,4), (32,64)):
            sys.argv = ["configure", "--modulation", mode, "--bch-payload", "--soft-demapping",
                        "--no-carrier-correction", "--warm-recovery", "--elapsed-time-tracking", "--compact-message-header", "--pilot-interval-symbols", str(pilot),
                        "--recovery-interval-frames", str(recovery)]
            request = cli.make_restart_request(pb, cli.parse_args())
            decoded = pb.RestartRequest.FromString(request.SerializeToString())
            assert decoded.bch_payload and decoded.soft_demapping and not decoded.carrier_correction
            assert decoded.warm_recovery and decoded.elapsed_time_tracking and decoded.compact_message_header
            assert decoded.pilot_interval_symbols == pilot and decoded.recovery_interval_frames == recovery
            cases.append(dict(mode=mode, pilot=pilot, recovery=recovery, status="pass",
                              parameters=MessageToDict(decoded,preserving_proto_field_name=True)))
    for separation in (12000, 12137, 13337):
        for branch, mask in (("both",3), ("lower",1), ("upper",2)):
            sys.argv = ["configure", "--modulation", "bpsk", "--audio-waveform", "bpsk_frequency_diversity",
                        "--diversity-branch-bandwidth-hz", "9600", "--diversity-separation-hz", str(separation),
                        "--diversity-branch", branch]
            request = cli.make_restart_request(pb, cli.parse_args())
            decoded = pb.RestartRequest.FromString(request.SerializeToString())
            assert decoded.diversity_branch_bandwidth_hz == 9600
            assert decoded.diversity_separation_hz == separation and decoded.diversity_branch_mask == mask
            cases.append(dict(separation=separation, branch=branch, status="pass",
                              parameters=MessageToDict(decoded,preserving_proto_field_name=True)))
    output = Path(__file__).resolve().parents[1] / "results/disturbed-recovery/validation-meta/PYTHON_GRPC.json"
    output.parent.mkdir(parents=True, exist_ok=True)
    source=json.loads((output.parents[1]/"MEASUREMENT_SOURCE.json").read_text())
    output.write_text(json.dumps(dict(report_header="simulated channel CLI/protobuf serialization checks",
        kind="assert", tier="quick", seed=7446529,
        parameters=dict(source,seed=7446529,channel_model="none: CLI/protobuf check only"),
        scope="Deterministic parameter enumeration; no RPC. CTest covers actual gRPC round trips.",
        cases=cases), indent=2) + "\n")
    print(f"simulated channel: {len(cases)} CLI/protobuf checks passed; {output}")


if __name__ == "__main__":
    main()
