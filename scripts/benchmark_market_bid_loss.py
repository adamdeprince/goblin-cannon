#!/usr/bin/env python3
"""Benchmark Massive market-data shadow-bid loss through the local radio pair."""

from __future__ import annotations

import argparse
import json
import mmap
import os
import signal
import subprocess
import sys
import time
from pathlib import Path
from typing import Any

from market_config import read_clients_constant
from market_shm import (
    DROPPED_FULL_OFFSET,
    DROPPED_OVERSIZE_OFFSET,
    INVALID_RECORDS_OFFSET,
    READ_SEQ_OFFSET,
    WRITE_SEQ_OFFSET,
    _u64,
)


REPO_ROOT = Path(__file__).resolve().parents[1]
SYMBOL_MIN = 2


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


def tool_python() -> str:
    venv_python = REPO_ROOT / ".venv" / "bin" / "python"
    return str(venv_python) if venv_python.exists() else sys.executable


def terminate(process: subprocess.Popen[object] | None) -> None:
    if process is None or process.poll() is not None:
        return
    process.send_signal(signal.SIGTERM)
    try:
        process.wait(timeout=5.0)
    except subprocess.TimeoutExpired:
        process.kill()
        process.wait(timeout=5.0)


def market_payload(record: dict[str, Any], market_symbol_max: int) -> bool:
    payload_hex = str(record.get("payload_hex", ""))
    try:
        payload = bytes.fromhex(payload_hex)
    except ValueError:
        return False
    return len(payload) >= 2 and SYMBOL_MIN <= payload[1] <= market_symbol_max


def summarize(records: list[dict[str, Any]], market_symbol_max: int) -> dict[str, Any]:
    decisions = [
        record for record in records
        if record.get("event") == "udp_decision" and market_payload(record, market_symbol_max)
    ]
    sent_decisions = [record for record in decisions if record.get("status") == "sent"]
    rejected_decisions = [record for record in decisions if record.get("status") == "rejected"]
    budget_rejected = [record for record in decisions if record.get("status") == "budget_exhausted"]
    framed = [
        record for record in records
        if record.get("event") == "transmitter_framer" and market_payload(record, market_symbol_max)
    ]
    enqueued = [
        record for record in records
        if record.get("event") == "transmitter_enqueue" and market_payload(record, market_symbol_max)
    ]
    denominator = len(sent_decisions) + len(rejected_decisions)
    bids = [int(record.get("bid_cents", 0)) for record in decisions if int(record.get("bid_cents", 0)) > 0]

    return {
        "market_symbol_max": market_symbol_max,
        "market_decisions": len(decisions),
        "market_sent_decisions": len(sent_decisions),
        "market_rejected_bad_bid": len(rejected_decisions),
        "market_budget_rejected": len(budget_rejected),
        "market_transmitter_enqueue_logs": len(enqueued),
        "market_framed_for_radio": len(framed),
        "bad_bid_loss_rate": (len(rejected_decisions) / denominator) if denominator else 0.0,
        "framed_per_sent_decision": (len(framed) / len(sent_decisions)) if sent_decisions else 0.0,
        "shadow_bid_cents_min": min(bids) if bids else 0,
        "shadow_bid_cents_p50": sorted(bids)[len(bids) // 2] if bids else 0,
        "shadow_bid_cents_max": max(bids) if bids else 0,
    }


def read_market_shm_stats(path: Path) -> dict[str, int]:
    if not path.exists():
        return {
            "market_shm_read_seq": 0,
            "market_shm_write_seq": 0,
            "market_shm_dropped_full": 0,
            "market_shm_dropped_oversize": 0,
            "market_shm_invalid_records": 0,
        }
    with path.open("r+b") as file:
        with mmap.mmap(file.fileno(), 0) as mm:
            return {
                "market_shm_read_seq": _u64(mm, READ_SEQ_OFFSET),
                "market_shm_write_seq": _u64(mm, WRITE_SEQ_OFFSET),
                "market_shm_dropped_full": _u64(mm, DROPPED_FULL_OFFSET),
                "market_shm_dropped_oversize": _u64(mm, DROPPED_OVERSIZE_OFFSET),
                "market_shm_invalid_records": _u64(mm, INVALID_RECORDS_OFFSET),
            }


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Measure market-data shadow-bid rejection rate with Massive flow.")
    parser.add_argument("--build-dir", type=Path, default=REPO_ROOT / "build")
    parser.add_argument("--fifo", type=Path, default=Path("/tmp/wbhf_market_bid_bench_iq.pipe"))
    parser.add_argument("--log-file", type=Path, default=Path("/tmp/wbhf_market_bid_bench.jsonl"))
    parser.add_argument("--market-shm-path", type=Path, default=Path(f"/dev/shm/wbhf_market_bid_bench_{os.getpid()}.ring"))
    parser.add_argument("--receiver", default="127.0.0.1:54051")
    parser.add_argument("--transmitter", default="127.0.0.1:54052")
    parser.add_argument("--quote-destination-port", type=int, default=9401)
    parser.add_argument("--client-id", type=int, default=0)
    parser.add_argument("--duration-seconds", type=float, default=60.0)
    parser.add_argument("--warmup-seconds", type=float, default=10.0)
    parser.add_argument("--chunk-samples", type=int, default=64)
    parser.add_argument("--pipe-capacity-bytes", type=int, default=4096)
    parser.add_argument(
        "--market-asset-class",
        action="append",
        choices=("stock", "future", "currency", "crypto"),
        help="asset classes to stream during the benchmark; repeat for multiple classes",
    )
    parser.add_argument("--result-json", type=Path)
    parser.add_argument("--keep-log", action="store_true")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if not os.environ.get("MASSIVE_KEY"):
        raise RuntimeError("MASSIVE_KEY must be set")
    if args.duration_seconds <= 0:
        raise RuntimeError("--duration-seconds must be positive")
    if not args.keep_log:
        try:
            args.log_file.unlink()
        except FileNotFoundError:
            pass

    clients = read_clients_constant()
    market_symbol_max = 256 - clients - 1
    cmd = [
        tool_python(),
        str(REPO_ROOT / "scripts" / "start_pipe_radios.py"),
        "--build-dir", str(args.build_dir),
        "--fifo", str(args.fifo),
        "--receiver", args.receiver,
        "--transmitter", args.transmitter,
        "--client-id", str(args.client_id),
        "--quote-destination-port", str(args.quote_destination_port),
        "--chunk-samples", str(args.chunk_samples),
        "--pipe-capacity-bytes", str(args.pipe_capacity_bytes),
        "--transmitter-log-file", str(args.log_file),
        "--market-shm-path", str(args.market_shm_path),
        "--keep-fifo",
        "--keep-market-shm",
    ]
    for asset_class in (args.market_asset_class or ["stock"]):
        cmd.extend(["--market-asset-class", asset_class])

    process: subprocess.Popen[object] | None = None
    try:
        process = subprocess.Popen(cmd)
        tail = JsonlTail(args.log_file)
        deadline = time.monotonic() + args.warmup_seconds
        while time.monotonic() < deadline:
            if process.poll() is not None:
                raise RuntimeError(f"radio launcher exited early with code {process.returncode}")
            tail.read_new()
            time.sleep(0.1)

        records: list[dict[str, Any]] = []
        deadline = time.monotonic() + args.duration_seconds
        while time.monotonic() < deadline:
            if process.poll() is not None:
                raise RuntimeError(f"radio launcher exited early with code {process.returncode}")
            records.extend(tail.read_new())
            time.sleep(0.05)
        records.extend(tail.read_new())

        summary = summarize(records, market_symbol_max)
        summary.update(read_market_shm_stats(args.market_shm_path))
        print(json.dumps(summary, indent=2, sort_keys=True))
        if args.result_json is not None:
            args.result_json.write_text(json.dumps(summary, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        return 0
    finally:
        terminate(process)
        try:
            args.market_shm_path.unlink()
        except FileNotFoundError:
            pass


if __name__ == "__main__":
    raise SystemExit(main())
