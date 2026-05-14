#!/usr/bin/env python3
"""Start local sender/receiver radio processes connected by a FIFO."""

from __future__ import annotations

import argparse
import os
import signal
import stat
import subprocess
import sys
import time
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]


def tool_python() -> str:
    venv_python = REPO_ROOT / ".venv" / "bin" / "python"
    if venv_python.exists():
        return str(venv_python)
    return sys.executable


def ensure_fifo(path: Path) -> None:
    if path.exists():
        mode = path.stat().st_mode
        if not stat.S_ISFIFO(mode):
            raise RuntimeError(f"{path} exists but is not a FIFO")
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    os.mkfifo(path)


def terminate(processes: list[subprocess.Popen[object]]) -> None:
    for process in processes:
        if process.poll() is None:
            process.terminate()
    deadline = time.monotonic() + 3.0
    for process in processes:
        remaining = max(0.0, deadline - time.monotonic())
        try:
            process.wait(timeout=remaining)
        except subprocess.TimeoutExpired:
            process.kill()
    for process in processes:
        if process.poll() is None:
            process.wait()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Start WBHF sender/receiver over a named pipe.")
    parser.add_argument("--build-dir", type=Path, default=REPO_ROOT / "build")
    parser.add_argument("--fifo", type=Path, default=Path("/tmp/wbhf_iq.pipe"))
    parser.add_argument("--receiver", default="127.0.0.1:50051")
    parser.add_argument("--transmitter", default="127.0.0.1:50052")
    parser.add_argument("--client-id", type=int, default=0)
    parser.add_argument("--quote-destination-ip", default="127.0.0.1")
    parser.add_argument("--quote-destination-port", type=int, default=9001)
    parser.add_argument("--sample-format", default="sc16_iq")
    parser.add_argument("--chunk-samples", type=int, default=256)
    parser.add_argument("--modulation", default="64qam")
    parser.add_argument("--bandwidth-hz", type=float, default=48000.0)
    parser.add_argument("--symbol-rate-hz", type=float, default=24000.0)
    parser.add_argument("--market-bank", type=int, choices=(0, 1), default=0)
    parser.add_argument("--no-market-stream", action="store_true", help="do not start the Massive websocket bridge")
    parser.add_argument("--market-grpc-timeout", type=float, default=0.05)
    parser.add_argument("--bank-refresh-seconds", type=float, default=1.0)
    parser.add_argument("--transmitter-log-file", type=Path, default=Path("/tmp/wbhf_transmitter.log"))
    parser.add_argument("--transmitter-log-capacity", type=int, default=65536)
    parser.add_argument("--client-latency-config", type=Path, default=REPO_ROOT / "config" / "client_latencies.conf")
    parser.add_argument("--enqueue-test-message", action="store_true")
    parser.add_argument("--keep-fifo", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.transmitter_log_capacity <= 0:
        raise RuntimeError("--transmitter-log-capacity must be positive")
    sender = args.build_dir / "wbhf_radio_sender"
    receiver = args.build_dir / "wbhf_radio_receiver"
    if not sender.exists() or not receiver.exists():
        raise RuntimeError(
            f"missing radio binaries; build them with: cmake --build {args.build_dir} "
            "--target wbhf_radio_sender wbhf_radio_receiver"
        )

    ensure_fifo(args.fifo)
    processes: list[subprocess.Popen[object]] = []

    receiver_cmd = [
        str(receiver),
        "--receiver",
        args.receiver,
        "--transmitter-control",
        args.transmitter,
        "--client-id",
        str(args.client_id),
        "--iq-input",
        str(args.fifo),
        "--quote-destination-ip",
        args.quote_destination_ip,
        "--quote-destination-port",
        str(args.quote_destination_port),
        "--sample-format",
        args.sample_format,
        "--chunk-samples",
        str(args.chunk_samples),
    ]
    sender_cmd = [
        str(sender),
        "--transmitter",
        args.transmitter,
        "--iq-output",
        str(args.fifo),
        "--sample-format",
        args.sample_format,
        "--chunk-samples",
        str(args.chunk_samples),
        "--log-file",
        str(args.transmitter_log_file),
        "--log-capacity",
        str(args.transmitter_log_capacity),
        "--latency-config",
        str(args.client_latency_config),
    ]
    configure_cmd = [
        tool_python(),
        str(REPO_ROOT / "scripts" / "configure_local_radios.py"),
        "--receiver",
        args.receiver,
        "--transmitter",
        args.transmitter,
        "--modulation",
        args.modulation,
        "--bandwidth-hz",
        str(args.bandwidth_hz),
        "--symbol-rate-hz",
        str(args.symbol_rate_hz),
        "--active-bank",
        str(args.market_bank),
        "--client-id",
        str(args.client_id),
    ]
    if args.enqueue_test_message:
        configure_cmd.append("--enqueue-test-message")
    market_cmd = [
        tool_python(),
        str(REPO_ROOT / "scripts" / "stream_massive_quotes.py"),
        str(args.market_bank),
        "--transmitter",
        args.transmitter,
        "--grpc-timeout",
        str(args.market_grpc_timeout),
        "--bank-refresh-seconds",
        str(args.bank_refresh_seconds),
    ]

    def stop_on_signal(signum: int, _frame: object) -> None:
        print(f"received signal {signum}, stopping radios")
        terminate(processes)
        raise SystemExit(128 + signum)

    signal.signal(signal.SIGINT, stop_on_signal)
    signal.signal(signal.SIGTERM, stop_on_signal)

    try:
        processes.append(subprocess.Popen(receiver_cmd))
        processes.append(subprocess.Popen(sender_cmd))
        subprocess.run(configure_cmd, check=True)
        if not args.no_market_stream:
            if not os.environ.get("MASSIVE_KEY"):
                raise RuntimeError("MASSIVE_KEY must be set unless --no-market-stream is used")
            processes.append(subprocess.Popen(market_cmd))
        print(
            f"pipe radios running: fifo={args.fifo} receiver={args.receiver} "
            f"transmitter={args.transmitter} quote_udp={args.quote_destination_ip}:{args.quote_destination_port} "
            f"market_stream={'off' if args.no_market_stream else 'on'} log={args.transmitter_log_file}"
        )
        while all(process.poll() is None for process in processes):
            time.sleep(0.5)
        return next((process.returncode or 0 for process in processes if process.poll() is not None), 0)
    finally:
        terminate(processes)
        if not args.keep_fifo:
            try:
                args.fifo.unlink()
            except FileNotFoundError:
                pass


if __name__ == "__main__":
    raise SystemExit(main())
