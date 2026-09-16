#!/usr/bin/env python3
"""Stream Massive quote midpoints into the transmitter as bank-relative deltas."""

from __future__ import annotations

import argparse
import asyncio
import json
import math
import os
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    import websockets
except ModuleNotFoundError:  # pragma: no cover - dependency check happens at runtime.
    websockets = None  # type: ignore[assignment]

from market_config import (
    DEFAULT_CONFIG,
    SYMBOL_MIN_BYTE,
    TOTAL_SYMBOL_COUNT,
    Instrument,
    ShadowBidConfig,
    ensure_python_grpc_stubs,
    load_demo_config,
    midpoint_to_units,
    read_clients_constant,
    validate_market_symbols,
)
from update_demo_stock_bank import resolve_front_futures
from market_shm import MarketDataShmProducer


BASE254_RADIX = 254
BASE254_MIN_BYTE = 2
MESSAGE_CRC_BYTES = 4
INT64_MIN = -(1 << 63)
INT64_MAX = (1 << 63) - 1


@dataclass(frozen=True)
class FeedSpec:
    name: str
    websocket_url: str
    subscribe_prefix: str
    event_type: str
    symbol_field: str
    bid_field: str
    ask_field: str
    instruments: list[Instrument]


class BankCache:
    def __init__(self, bank: int, instruments: list[Instrument], market_symbol_count: int) -> None:
        self.bank = bank
        self.instruments = instruments
        self.market_symbol_count = market_symbol_count
        self.prices_units = [0] * market_symbol_count
        self.generation = 0
        self.ready = False

    def update(self, prices_units: list[int], generation: int) -> None:
        if len(prices_units) != self.market_symbol_count:
            raise RuntimeError(
                f"bank snapshot contains {len(prices_units)} prices; "
                f"expected {self.market_symbol_count}"
            )
        self.prices_units = list(prices_units)
        self.generation = generation
        self.ready = all(self.base_for_symbol(instrument.radio_symbol) is not None for instrument in self.instruments)

    def base_for_symbol(self, radio_symbol: int) -> int | None:
        index = radio_symbol - SYMBOL_MIN_BYTE
        if index < 0 or index >= len(self.prices_units):
            return None
        value = self.prices_units[index]
        return value if value > 0 else None


@dataclass
class ShadowPriceState:
    prev_units: int | None = None
    prev_time_ms: float | None = None
    last_sent_units: int | None = None
    bank_generation: int = 0


class ShadowBidder:
    def __init__(self, config: ShadowBidConfig, instruments: list[Instrument]) -> None:
        if config.k_cents <= 0:
            raise ValueError("shadow_bid.k_cents must be positive")
        if config.velocity_h_ms < 0:
            raise ValueError("shadow_bid.velocity_h_ms must be non-negative")
        self.config = config
        self.by_symbol = {instrument.radio_symbol: instrument for instrument in instruments}
        self.state: dict[int, ShadowPriceState] = {
            instrument.radio_symbol: ShadowPriceState() for instrument in instruments
        }

    def sync_bank(self, cache: BankCache, instrument: Instrument) -> None:
        state = self.state[instrument.radio_symbol]
        if state.bank_generation == cache.generation and state.last_sent_units is not None:
            return
        base = cache.base_for_symbol(instrument.radio_symbol)
        if base is None:
            return
        state.last_sent_units = base
        state.bank_generation = cache.generation

    def record_received(self, instrument: Instrument, units: int, now_ms: float) -> None:
        state = self.state[instrument.radio_symbol]
        state.prev_units = units
        state.prev_time_ms = now_ms

    def record_sent(self, instrument: Instrument, units: int) -> None:
        self.state[instrument.radio_symbol].last_sent_units = units

    def compute_bid_cents(self,
                          instrument: Instrument,
                          units_now: int,
                          billable_bytes: int,
                          now_ms: float) -> int:
        if billable_bytes <= 0:
            raise ValueError("billable_bytes must be positive")
        if units_now <= 0:
            return int(math.ceil(self.config.k_cents))

        state = self.state[instrument.radio_symbol]
        if state.last_sent_units is None or state.prev_units is None:
            return max(1, int(math.ceil(self.config.k_cents)))
        if state.last_sent_units <= 0 or state.prev_units <= 0:
            return max(1, int(math.ceil(self.config.k_cents)))

        dt_ms = 0.0 if state.prev_time_ms is None else max(0.0, now_ms - state.prev_time_ms)
        last_sent_term = abs(math.log(units_now) - math.log(state.last_sent_units))
        if dt_ms > 0.0:
            velocity_term = self.config.velocity_h_ms * abs(math.log(units_now) - math.log(state.prev_units)) / dt_ms
        else:
            velocity_term = 0.0
        raw_bid = self.config.k_cents * instrument.weight * (last_sent_term + velocity_term) / billable_bytes
        return max(1, int(math.ceil(raw_bid)))


def zigzag_encode_i64(value: int) -> int:
    if value < INT64_MIN or value > INT64_MAX:
        raise OverflowError("delta does not fit int64")
    return ((value << 1) ^ (value >> 63)) & ((1 << 64) - 1)


def encode_base254_varuint(value: int) -> bytes:
    if value < 0:
        raise ValueError("varuint value must be non-negative")
    out = bytearray()
    while True:
        out.append(BASE254_MIN_BYTE + (value % BASE254_RADIX))
        value //= BASE254_RADIX
        if value == 0:
            return bytes(out)


def encode_bank_symbol_delta(bank: int, radio_symbol: int, delta_units: int) -> bytes:
    return bytes((bank, radio_symbol)) + encode_base254_varuint(zigzag_encode_i64(delta_units))


def radio_billable_bytes(payload: bytes) -> int:
    return len(payload) + (MESSAGE_CRC_BYTES if len(payload) > 1 else 0)


def parse_events(raw: str | bytes) -> list[dict[str, Any]]:
    data = json.loads(raw)
    if isinstance(data, dict):
        return [data]
    if isinstance(data, list):
        return [event for event in data if isinstance(event, dict)]
    return []


def status_text(event: dict[str, Any]) -> str:
    return f"{event.get('status', '')} {event.get('message', '')}".strip().lower()


def feed_symbol_aliases(instrument: Instrument) -> set[str]:
    symbol = instrument.massive_symbol.upper()
    aliases = {symbol}
    compact = symbol.replace("/", "").replace("-", "")
    aliases.add(compact)
    if instrument.asset_class == "currency":
        aliases.add(f"C:{compact}")
        aliases.add(f"C:{symbol}")
    if instrument.asset_class == "crypto":
        aliases.add(f"X:{symbol}")
        aliases.add(f"X:{compact}")
    return aliases


async def authenticate_and_subscribe(ws: Any, api_key: str, spec: FeedSpec, auth_timeout: float) -> None:
    await ws.send(json.dumps({"action": "auth", "params": api_key}))
    deadline = asyncio.get_running_loop().time() + auth_timeout
    while True:
        timeout = max(0.1, deadline - asyncio.get_running_loop().time())
        raw = await asyncio.wait_for(ws.recv(), timeout=timeout)
        for event in parse_events(raw):
            if event.get("ev") != "status":
                continue
            text = status_text(event)
            if "auth_failed" in text or ("auth" in text and "fail" in text):
                raise RuntimeError(f"Massive {spec.name} websocket authentication failed: {event}")
            if "auth_success" in text or ("auth" in text and "success" in text):
                params = ",".join(f"{spec.subscribe_prefix}.{i.massive_symbol}" for i in spec.instruments)
                await ws.send(json.dumps({"action": "subscribe", "params": params}))
                print(f"{spec.name}: subscribed to {params}")
                return
        if asyncio.get_running_loop().time() >= deadline:
            raise TimeoutError(f"timed out waiting for Massive {spec.name} websocket authentication")


async def refresh_bank_forever(
    stub: Any,
    pb2: Any,
    cache: BankCache,
    interval_seconds: float,
    grpc_timeout: float,
) -> None:
    last_ready_generation = 0
    while True:
        try:
            snapshot = await stub.GetBank(pb2.BankSelect(bank=cache.bank), timeout=grpc_timeout)
            cache.update(list(snapshot.prices_units), int(snapshot.generation))
            if cache.ready and cache.generation != last_ready_generation:
                print(f"bank {cache.bank} ready generation={cache.generation}")
                last_ready_generation = cache.generation
        except Exception as exc:  # noqa: BLE001 - keep the stream alive while control catches up.
            print(f"bank refresh failed: {exc}", file=sys.stderr)
        await asyncio.sleep(interval_seconds)


class MarketDataPublisher:
    def __init__(self, producer: MarketDataShmProducer) -> None:
        self.producer = producer
        self.dropped = 0

    def publish(self, payload: bytes, bid_cents: int) -> bool:
        accepted = self.producer.try_push(payload, bid_cents)
        if not accepted:
            self.dropped += 1
            if self.dropped == 1 or self.dropped % 1000 == 0:
                print(f"market shared-memory ring dropped {self.dropped} updates", file=sys.stderr)
        return accepted


async def stream_feed_once(
    spec: FeedSpec,
    api_key: str,
    cache: BankCache,
    bidder: ShadowBidder,
    publisher: MarketDataPublisher,
    auth_timeout: float,
) -> None:
    if websockets is None:
        raise RuntimeError("websockets is required. Install with: python3 -m pip install websockets")

    by_feed_symbol: dict[str, Instrument] = {}
    for instrument in spec.instruments:
        for alias in feed_symbol_aliases(instrument):
            by_feed_symbol[alias] = instrument
    async with websockets.connect(spec.websocket_url, ping_interval=20.0, close_timeout=2.0) as ws:
        await authenticate_and_subscribe(ws, api_key, spec, auth_timeout)
        skipped_no_bank = 0
        async for raw in ws:
            for event in parse_events(raw):
                if event.get("ev") != spec.event_type:
                    continue
                feed_symbol = str(event.get(spec.symbol_field, "")).upper()
                instrument = by_feed_symbol.get(feed_symbol)
                if instrument is None:
                    continue
                units = midpoint_to_units(event.get(spec.bid_field), event.get(spec.ask_field), instrument)
                if units is None:
                    continue
                now_ms = asyncio.get_running_loop().time() * 1000.0
                if not cache.ready:
                    bidder.record_received(instrument, units, now_ms)
                    skipped_no_bank += 1
                    if skipped_no_bank == 1 or skipped_no_bank % 1000 == 0:
                        print(f"{spec.name}: skipped {skipped_no_bank} quote updates waiting for bank data")
                    continue
                bidder.sync_bank(cache, instrument)
                base = cache.base_for_symbol(instrument.radio_symbol)
                if base is None:
                    bidder.record_received(instrument, units, now_ms)
                    continue
                delta = units - base
                try:
                    payload = encode_bank_symbol_delta(cache.bank, instrument.radio_symbol, delta)
                except OverflowError as exc:
                    print(f"{spec.name}: skipping {instrument.symbol}: {exc}", file=sys.stderr)
                    bidder.record_received(instrument, units, now_ms)
                    continue
                if bidder.state[instrument.radio_symbol].last_sent_units == units:
                    bidder.record_received(instrument, units, now_ms)
                    continue
                bid_cents = bidder.compute_bid_cents(instrument, units, radio_billable_bytes(payload), now_ms)
                accepted = publisher.publish(payload, bid_cents)
                bidder.record_received(instrument, units, now_ms)
                if accepted:
                    bidder.record_sent(instrument, units)


async def stream_feed_forever(
    spec: FeedSpec,
    api_key: str,
    cache: BankCache,
    bidder: ShadowBidder,
    publisher: MarketDataPublisher,
    args: argparse.Namespace,
) -> None:
    while True:
        try:
            await stream_feed_once(
                spec,
                api_key,
                cache,
                bidder,
                publisher,
                args.auth_timeout,
            )
        except Exception as exc:  # noqa: BLE001 - reconnect unless the process is stopped.
            print(f"{spec.name}: websocket disconnected: {exc}", file=sys.stderr)
            await asyncio.sleep(args.reconnect_seconds)


async def run(args: argparse.Namespace) -> None:
    api_key = os.environ.get("MASSIVE_KEY")
    if not api_key:
        raise RuntimeError("MASSIVE_KEY is not set")

    config = load_demo_config(args.config)
    transmitter_address = args.transmitter or config.transmitter_address
    clients = read_clients_constant()
    selected_instruments = config.instruments
    if args.asset_class:
        allowed = {asset_class.lower() for asset_class in args.asset_class}
        selected_instruments = [instrument for instrument in selected_instruments if instrument.asset_class in allowed]
    validate_market_symbols(selected_instruments, clients)
    instruments = resolve_front_futures(selected_instruments, config, api_key, args.http_timeout)
    market_symbol_count = TOTAL_SYMBOL_COUNT - clients

    try:
        import grpc  # type: ignore[import-not-found]
    except ModuleNotFoundError as exc:
        raise RuntimeError("grpcio is required. Install with: python3 -m pip install grpcio grpcio-tools") from exc

    pb2, pb2_grpc = ensure_python_grpc_stubs()
    cache = BankCache(args.bank, instruments, market_symbol_count)
    bidder = ShadowBidder(config.shadow_bid, instruments)
    publisher = MarketDataPublisher(MarketDataShmProducer(args.market_shm_path, args.market_shm_timeout))
    specs = [
        FeedSpec(
            name="stocks",
            websocket_url=args.stock_websocket_url or config.massive.stock_websocket_url,
            subscribe_prefix="Q",
            event_type="Q",
            symbol_field="sym",
            bid_field="bp",
            ask_field="ap",
            instruments=[i for i in instruments if i.asset_class == "stock"],
        ),
        FeedSpec(
            name="futures",
            websocket_url=args.future_websocket_url or config.massive.future_websocket_url,
            subscribe_prefix="Q",
            event_type="Q",
            symbol_field="sym",
            bid_field="bp",
            ask_field="ap",
            instruments=[i for i in instruments if i.asset_class == "future"],
        ),
        FeedSpec(
            name="forex",
            websocket_url=args.forex_websocket_url or config.massive.forex_websocket_url,
            subscribe_prefix="C",
            event_type="C",
            symbol_field="p",
            bid_field="b",
            ask_field="a",
            instruments=[i for i in instruments if i.asset_class == "currency"],
        ),
        FeedSpec(
            name="crypto",
            websocket_url=args.crypto_websocket_url or config.massive.crypto_websocket_url,
            subscribe_prefix="XQ",
            event_type="XQ",
            symbol_field="pair",
            bid_field="bp",
            ask_field="ap",
            instruments=[i for i in instruments if i.asset_class == "crypto"],
        ),
    ]
    specs = [spec for spec in specs if spec.instruments]

    async with grpc.aio.insecure_channel(transmitter_address) as channel:
        stub = pb2_grpc.TransmitterControlStub(channel)
        tasks = [
            asyncio.create_task(refresh_bank_forever(stub, pb2, cache, args.bank_refresh_seconds, args.grpc_timeout))
        ]
        tasks.extend(asyncio.create_task(stream_feed_forever(spec, api_key, cache, bidder, publisher, args)) for spec in specs)
        try:
            await asyncio.gather(*tasks)
        finally:
            publisher.producer.close()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Stream Massive stock/futures/forex/crypto quote midpoint deltas into the Goblin Cannon transmitter."
    )
    parser.add_argument("bank", type=int, choices=(0, 1), help="bank delimiter to use for emitted messages")
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG, help="instrument config TOML")
    parser.add_argument("--transmitter", help="transmitter gRPC address; overrides config")
    parser.add_argument("--market-shm-path", type=Path, default=Path("/dev/shm/goblin_cannon_market_data_ring"))
    parser.add_argument("--market-shm-timeout", type=float, default=5.0)
    parser.add_argument("--stock-websocket-url", help="Massive stocks websocket URL; overrides config")
    parser.add_argument("--future-websocket-url", help="Massive futures websocket URL; overrides config")
    parser.add_argument("--forex-websocket-url", help="Massive forex websocket URL; overrides config")
    parser.add_argument("--crypto-websocket-url", help="Massive crypto websocket URL; overrides config")
    parser.add_argument(
        "--asset-class",
        action="append",
        choices=("stock", "future", "currency", "crypto"),
        help="limit streaming to one asset class; can be repeated",
    )
    parser.add_argument("--http-timeout", type=float, default=3.0, help="Massive REST timeout for front futures")
    parser.add_argument("--grpc-timeout", type=float, default=0.05, help="bank-control gRPC timeout in seconds")
    parser.add_argument("--auth-timeout", type=float, default=10.0, help="websocket auth timeout in seconds")
    parser.add_argument("--bank-refresh-seconds", type=float, default=1.0, help="bank snapshot polling interval")
    parser.add_argument("--reconnect-seconds", type=float, default=1.0, help="delay before websocket reconnect")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    asyncio.run(run(args))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
