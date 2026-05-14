#!/usr/bin/env python3
"""Benchmark end-to-end software latency through the local pipe radio stack."""

from __future__ import annotations

import argparse
import json
import math
import os
import signal
import socket
import subprocess
import sys
import time
from pathlib import Path
from typing import Any

from market_config import read_clients_constant


REPO_ROOT = Path(__file__).resolve().parents[1]


def tool_python() -> str:
    venv_python = REPO_ROOT / ".venv" / "bin" / "python"
    if venv_python.exists():
        return str(venv_python)
    return sys.executable


def now_ns() -> int:
    return time.time_ns()


def client_symbol(client_id: int, clients: int) -> int:
    if client_id < 0 or client_id >= clients:
        raise ValueError(f"client-id must be in [0, {clients - 1}]")
    return 256 - clients + client_id


def client_body(sequence: int, size: int) -> bytes:
    if size < 1 or size > 8:
        raise ValueError("client body size must be in [1,8]")
    return bytes(2 + ((sequence * 17 + i * 29) % 254) for i in range(size))


def percentile(values: list[int], pct: float) -> int:
    if not values:
        return 0
    ordered = sorted(values)
    index = min(len(ordered) - 1, max(0, math.ceil((pct / 100.0) * len(ordered)) - 1))
    return ordered[index]


def ns_to_ms(value: int) -> float:
    return value / 1_000_000.0


class JsonlTail:
    def __init__(self, path: Path) -> None:
        self.path = path
        self.offset = 0

    def read_new(self) -> list[dict[str, Any]]:
        if not self.path.exists():
            return []
        records: list[dict[str, Any]] = []
        with self.path.open("rb") as f:
            f.seek(self.offset)
            while True:
                line = f.readline()
                if not line:
                    break
                if not line.endswith(b"\n"):
                    f.seek(-len(line), os.SEEK_CUR)
                    break
                self.offset = f.tell()
                try:
                    records.append(json.loads(line))
                except json.JSONDecodeError:
                    continue
        return records


def write_client_udp_config(path: Path, listen_ip: str, listen_port: int, client_id: int, source_ip: str) -> None:
    path.write_text(
        "\n".join(
            [
                "backend=kernel_udp",
                f"listen_ip={listen_ip}",
                f"listen_port={listen_port}",
                f"client.{client_id}.ip={source_ip}",
                "",
            ]
        ),
        encoding="utf-8",
    )


def write_budget_config(path: Path, clients: int, budget_cents: int) -> None:
    path.write_text(
        "".join(f"client.{client_id}.budget_pennies={budget_cents}\n" for client_id in range(clients)),
        encoding="utf-8",
    )


def terminate(process: subprocess.Popen[object] | None) -> None:
    if process is None or process.poll() is not None:
        return
    process.terminate()
    try:
        process.wait(timeout=5.0)
    except subprocess.TimeoutExpired:
        process.kill()
        process.wait(timeout=5.0)


def wait_for_market_flow(process: subprocess.Popen[object],
                         tail: JsonlTail,
                         required: int,
                         timeout_seconds: float) -> int:
    if required <= 0:
        return 0
    deadline = time.monotonic() + timeout_seconds
    seen = 0
    while time.monotonic() < deadline:
        if process.poll() is not None:
            raise RuntimeError(f"radio launcher exited early with code {process.returncode}")
        for record in tail.read_new():
            if record.get("event") != "transmitter_enqueue":
                continue
            payload_hex = str(record.get("payload_hex", ""))
            try:
                payload = bytes.fromhex(payload_hex)
            except ValueError:
                continue
            if len(payload) >= 2 and 2 <= payload[1] <= 235 and int(record.get("bid_cents", 0)) == 100:
                seen += 1
                if seen >= required:
                    return seen
        time.sleep(0.05)
    raise TimeoutError(f"timed out waiting for {required} Massive-backed market enqueue events; saw {seen}")


def send_client_messages(args: argparse.Namespace, clients: int) -> dict[str, dict[str, int]]:
    symbol = client_symbol(args.client_id, clients)
    sent: dict[str, dict[str, int]] = {}
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind((args.client_source_ip, 0))
        for sequence in range(args.messages):
            body = client_body(sequence, args.client_body_bytes)
            udp_message = bytes([args.bank]) + body
            wire_payload = bytes([args.bank, symbol]) + body
            packet = int(args.bid_cents).to_bytes(4, "big") + udp_message
            timestamp = now_ns()
            sock.sendto(packet, (args.client_udp_host, args.client_udp_port))
            sent[wire_payload.hex()] = {
                "sequence": sequence,
                "app_send_ns": timestamp,
                "tx_sent_ns": 0,
                "receiver_ts_ns": 0,
                "tx_report_ns": 0,
            }
            time.sleep(args.send_interval_ms / 1000.0)
    return sent


def collect_results(process: subprocess.Popen[object],
                    tail: JsonlTail,
                    sent: dict[str, dict[str, int]],
                    timeout_seconds: float) -> None:
    deadline = time.monotonic() + timeout_seconds
    complete = 0
    while time.monotonic() < deadline:
        if process.poll() is not None:
            raise RuntimeError(f"radio launcher exited early with code {process.returncode}")
        for record in tail.read_new():
            payload_hex = str(record.get("payload_hex", ""))
            entry = sent.get(payload_hex)
            if entry is None:
                continue
            event = record.get("event")
            status = record.get("status")
            if event == "udp_decision":
                if status == "sent":
                    entry["tx_sent_ns"] = int(record.get("ts_ns", 0))
                elif status in {"budget_exhausted", "rejected"}:
                    entry["rejected_ns"] = int(record.get("ts_ns", 0))
            elif event == "receiver_client_message":
                entry["receiver_ts_ns"] = int(record.get("receiver_ts_ns", 0))
                entry["tx_report_ns"] = int(record.get("ts_ns", 0))
        complete = sum(1 for item in sent.values() if item["tx_report_ns"] != 0)
        if complete == len(sent):
            return
        time.sleep(0.02)
    missing = [item["sequence"] for item in sent.values() if item["tx_report_ns"] == 0]
    raise TimeoutError(f"timed out waiting for {len(missing)} receiver client messages: {missing}")


def summarize(sent: dict[str, dict[str, int]], result_path: Path | None) -> dict[str, Any]:
    app_to_report = [item["tx_report_ns"] - item["app_send_ns"] for item in sent.values()]
    app_to_receiver = [item["receiver_ts_ns"] - item["app_send_ns"] for item in sent.values()]
    tx_to_receiver = [
        item["receiver_ts_ns"] - item["tx_sent_ns"]
        for item in sent.values()
        if item["tx_sent_ns"] and item["receiver_ts_ns"]
    ]
    receiver_to_report = [item["tx_report_ns"] - item["receiver_ts_ns"] for item in sent.values()]
    enqueue_delay = [
        item["tx_sent_ns"] - item["app_send_ns"]
        for item in sent.values()
        if item["tx_sent_ns"]
    ]

    def stats(values: list[int]) -> dict[str, float]:
        return {
            "count": len(values),
            "min_ms": ns_to_ms(min(values)) if values else 0.0,
            "p50_ms": ns_to_ms(percentile(values, 50)),
            "p90_ms": ns_to_ms(percentile(values, 90)),
            "p99_ms": ns_to_ms(percentile(values, 99)),
            "max_ms": ns_to_ms(max(values)) if values else 0.0,
        }

    summary = {
        "messages": len(sent),
        "app_send_to_transmitter_report": stats(app_to_report),
        "app_send_to_receiver_timestamp": stats(app_to_receiver),
        "transmitter_sent_to_receiver_timestamp": stats(tx_to_receiver),
        "receiver_timestamp_to_transmitter_report": stats(receiver_to_report),
        "app_send_to_transmitter_sent_log": stats(enqueue_delay),
    }

    print(json.dumps(summary, indent=2, sort_keys=True))
    if result_path is not None:
        result_path.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
    return summary


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Benchmark local WBHF software-stack latency with Massive flow.")
    parser.add_argument("--build-dir", type=Path, default=REPO_ROOT / "build")
    parser.add_argument("--fifo", type=Path, default=Path("/tmp/wbhf_latency_bench_iq.pipe"))
    parser.add_argument("--log-file", type=Path, default=Path("/tmp/wbhf_latency_bench.jsonl"))
    parser.add_argument("--receiver", default="127.0.0.1:52051")
    parser.add_argument("--transmitter", default="127.0.0.1:52052")
    parser.add_argument("--quote-destination-port", type=int, default=9201)
    parser.add_argument("--client-id", type=int, default=0)
    parser.add_argument("--client-source-ip", default="127.0.0.1")
    parser.add_argument("--client-udp-host", default="127.0.0.1")
    parser.add_argument("--client-udp-port", type=int, default=9210)
    parser.add_argument("--messages", type=int, default=16)
    parser.add_argument("--client-body-bytes", type=int, default=8)
    parser.add_argument("--bid-cents", type=int, default=500)
    parser.add_argument("--budget-cents", type=int, default=1_000_000)
    parser.add_argument("--bank", type=int, choices=(0, 1), default=0)
    parser.add_argument("--send-interval-ms", type=float, default=1000.0)
    parser.add_argument("--modulation", default="64qam")
    parser.add_argument("--bandwidth-hz", type=float, default=48000.0)
    parser.add_argument("--symbol-rate-hz", type=float, default=24000.0)
    parser.add_argument("--market-events-required", type=int, default=1)
    parser.add_argument("--market-flow-timeout", type=float, default=45.0)
    parser.add_argument("--startup-warmup-seconds", type=float, default=3.0)
    parser.add_argument("--receive-timeout-seconds", type=float, default=20.0)
    parser.add_argument("--no-market-stream", action="store_true")
    parser.add_argument("--keep-log", action="store_true")
    parser.add_argument("--result-json", type=Path)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.messages <= 0:
        raise RuntimeError("--messages must be positive")
    if not args.no_market_stream and not os.environ.get("MASSIVE_KEY"):
        raise RuntimeError("MASSIVE_KEY must be set, or pass --no-market-stream for a local-only smoke benchmark")

    clients = read_clients_constant()
    client_symbol(args.client_id, clients)
    if not args.keep_log:
        try:
            args.log_file.unlink()
        except FileNotFoundError:
            pass

    client_udp_config = Path(f"/tmp/wbhf_latency_client_udp_{os.getpid()}.conf")
    budget_config = Path(f"/tmp/wbhf_latency_client_budget_{os.getpid()}.conf")
    write_client_udp_config(client_udp_config, "127.0.0.1", args.client_udp_port, args.client_id, args.client_source_ip)
    write_budget_config(budget_config, clients, args.budget_cents)

    cmd = [
        tool_python(),
        str(REPO_ROOT / "scripts" / "start_pipe_radios.py"),
        "--build-dir",
        str(args.build_dir),
        "--fifo",
        str(args.fifo),
        "--receiver",
        args.receiver,
        "--transmitter",
        args.transmitter,
        "--client-id",
        str(args.client_id),
        "--quote-destination-port",
        str(args.quote_destination_port),
        "--modulation",
        args.modulation,
        "--bandwidth-hz",
        str(args.bandwidth_hz),
        "--symbol-rate-hz",
        str(args.symbol_rate_hz),
        "--market-bank",
        str(args.bank),
        "--transmitter-log-file",
        str(args.log_file),
        "--client-udp-config",
        str(client_udp_config),
        "--client-budget-config",
        str(budget_config),
        "--keep-fifo",
    ]
    if args.no_market_stream:
        cmd.append("--no-market-stream")

    process: subprocess.Popen[object] | None = None
    try:
        process = subprocess.Popen(cmd)
        tail = JsonlTail(args.log_file)
        time.sleep(args.startup_warmup_seconds)
        market_seen = wait_for_market_flow(
            process,
            tail,
            0 if args.no_market_stream else args.market_events_required,
            args.market_flow_timeout,
        )
        if not args.no_market_stream:
            print(f"observed {market_seen} Massive-backed market enqueue event(s)")

        sent = send_client_messages(args, clients)
        collect_results(process, tail, sent, args.receive_timeout_seconds)
        summarize(sent, args.result_json)
        return 0
    finally:
        terminate(process)
        try:
            client_udp_config.unlink()
        except FileNotFoundError:
            pass
        try:
            budget_config.unlink()
        except FileNotFoundError:
            pass


if __name__ == "__main__":
    raise SystemExit(main())
