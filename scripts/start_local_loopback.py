#!/usr/bin/env python3
"""Start a local transmitter/receiver loopback node for manual testing."""

from __future__ import annotations

import argparse
import subprocess
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Start the Goblin Cannon local loopback node.")
    parser.add_argument("--build-dir", type=Path, default=REPO_ROOT / "build")
    parser.add_argument("--receiver", default="127.0.0.1:50051")
    parser.add_argument("--transmitter", default="127.0.0.1:50052")
    parser.add_argument("--quote-destination-ip", default="127.0.0.1")
    parser.add_argument("--quote-destination-port", type=int, default=9001)
    parser.add_argument("--modulation", default="64qam")
    parser.add_argument("--bandwidth-hz", type=float, default=48000.0)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    binary = args.build_dir / "goblin_cannon_local_node"
    if not binary.exists():
        raise RuntimeError(f"{binary} does not exist; build it with: cmake --build {args.build_dir} --target goblin_cannon_local_node")
    command = [
        str(binary),
        "--receiver",
        args.receiver,
        "--transmitter",
        args.transmitter,
        "--quote-destination-ip",
        args.quote_destination_ip,
        "--quote-destination-port",
        str(args.quote_destination_port),
        "--modulation",
        args.modulation,
        "--bandwidth-hz",
        str(args.bandwidth_hz),
    ]
    return subprocess.call(command)


if __name__ == "__main__":
    raise SystemExit(main())
