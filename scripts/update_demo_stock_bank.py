#!/usr/bin/env python3
"""Update the transmitter price bank from Massive quote midpoints and request a bank switch.

The Massive API key is read from MASSIVE_KEY. Price units are derived from each
instrument's minimum_price_increment in config/demo_instruments.toml.
"""

from __future__ import annotations

import argparse
import json
import os
import urllib.error
import urllib.parse
import urllib.request
from datetime import date
from decimal import Decimal
from pathlib import Path
from typing import Any

from market_config import (
    DEFAULT_CONFIG,
    SYMBOL_MIN_BYTE,
    TOTAL_SYMBOL_COUNT,
    DemoConfig,
    Instrument,
    ensure_python_grpc_stubs,
    load_demo_config,
    price_to_units,
    read_clients_constant,
    validate_market_symbols,
)


def fetch_json(url: str, timeout_seconds: float) -> Any:
    request = urllib.request.Request(url, headers={"Accept": "application/json"})
    with urllib.request.urlopen(request, timeout=timeout_seconds) as response:
        return json.loads(response.read().decode("utf-8"))


def try_fetch_json(url: str, timeout_seconds: float) -> Any | None:
    try:
        return fetch_json(url, timeout_seconds)
    except urllib.error.HTTPError as exc:
        if exc.code in (400, 404):
            return None
        raise


def quote_midpoint_from_mapping(quote: Any) -> Decimal | None:
    if not isinstance(quote, dict):
        return None
    for bid_key, ask_key in (
        ("bid_price", "ask_price"),
        ("bp", "ap"),
        ("bid", "ask"),
        ("b", "a"),
        ("p", "P"),
    ):
        bid = quote.get(bid_key)
        ask = quote.get(ask_key)
        if bid is None or ask is None:
            continue
        bid_dec = Decimal(str(bid))
        ask_dec = Decimal(str(ask))
        if bid_dec <= 0 or ask_dec <= 0:
            continue
        return (bid_dec + ask_dec) / Decimal("2")
    return None


def quote_midpoint_from_results(data: Any) -> Decimal | None:
    results = data.get("results") if isinstance(data, dict) else None
    if not results:
        return None
    quote = results[0] if isinstance(results, list) else results
    return quote_midpoint_from_mapping(quote)


def quote_midpoint_from_forex_last(data: Any) -> Decimal | None:
    last = data.get("last") if isinstance(data, dict) else None
    return quote_midpoint_from_mapping(last)


def quote_midpoint_from_snapshot_item(item: Any) -> Decimal | None:
    if not isinstance(item, dict):
        return None
    midpoint = quote_midpoint_from_mapping(item)
    if midpoint is not None:
        return midpoint
    for key in ("last_quote", "quote"):
        midpoint = quote_midpoint_from_mapping(item.get(key))
        if midpoint is not None:
            return midpoint
    return None


def quote_midpoint_from_snapshot(data: Any, accepted_tickers: set[str]) -> Decimal | None:
    results = data.get("results") if isinstance(data, dict) else None
    if not results:
        return None
    if isinstance(results, dict):
        results = [results]
    if not isinstance(results, list):
        return None
    for item in results:
        if not isinstance(item, dict):
            continue
        ticker = str(item.get("ticker", "")).upper()
        if ticker and accepted_tickers and ticker not in accepted_tickers:
            continue
        midpoint = quote_midpoint_from_snapshot_item(item)
        if midpoint is not None:
            return midpoint
    return None


def api_url(base_url: str, path: str, params: dict[str, str]) -> str:
    query = urllib.parse.urlencode(params)
    return f"{base_url}{path}?{query}"


def resolve_front_future(
    instrument: Instrument,
    config: DemoConfig,
    api_key: str,
    timeout_seconds: float,
) -> Instrument:
    if not instrument.front:
        return instrument
    params = {
        "product_code": instrument.symbol,
        "active": "true",
        "date": date.today().isoformat(),
        "limit": "1000",
        "sort": "days_to_maturity.asc",
        "apiKey": api_key,
    }
    data = fetch_json(api_url(config.massive.rest_base_url, "/futures/v1/contracts", params), timeout_seconds)
    results = data.get("results") if isinstance(data, dict) else None
    if not results:
        raise RuntimeError(f"Massive returned no active futures contracts for {instrument.symbol}")
    candidates = [item for item in results if isinstance(item, dict) and item.get("ticker")]
    candidates.sort(key=lambda item: item.get("days_to_maturity", 1 << 30))
    front_ticker = str(candidates[0]["ticker"]).upper()
    return Instrument(
        asset_class=instrument.asset_class,
        symbol=instrument.symbol,
        radio_symbol=instrument.radio_symbol,
        minimum_price_increment=instrument.minimum_price_increment,
        unit=instrument.unit,
        massive_symbol=front_ticker,
        weight=instrument.weight,
        front=instrument.front,
        description=instrument.description,
    )


def resolve_front_futures(
    instruments: list[Instrument],
    config: DemoConfig,
    api_key: str,
    timeout_seconds: float,
) -> list[Instrument]:
    resolved: list[Instrument] = []
    for instrument in instruments:
        if instrument.asset_class == "future":
            resolved.append(resolve_front_future(instrument, config, api_key, timeout_seconds))
        else:
            resolved.append(instrument)
    return resolved


def fetch_stock_units(instrument: Instrument, config: DemoConfig, api_key: str, timeout_seconds: float) -> int:
    encoded = urllib.parse.quote(instrument.massive_symbol, safe="")
    params = {"limit": "1", "order": "desc", "sort": "timestamp", "apiKey": api_key}
    data = fetch_json(api_url(config.massive.rest_base_url, f"/v3/quotes/{encoded}", params), timeout_seconds)
    midpoint = quote_midpoint_from_results(data)
    if midpoint is None:
        fallback = fetch_json(
            api_url(config.massive.rest_base_url, f"/v2/last/nbbo/{encoded}", {"apiKey": api_key}),
            timeout_seconds,
        )
        midpoint = quote_midpoint_from_results(fallback)
    if midpoint is None:
        raise RuntimeError(f"Massive did not return a usable bid/ask quote for {instrument.symbol}")
    return price_to_units(midpoint, instrument)


def fetch_future_units(instrument: Instrument, config: DemoConfig, api_key: str, timeout_seconds: float) -> int:
    encoded = urllib.parse.quote(instrument.massive_symbol, safe="")
    params = {"limit": "1", "sort": "timestamp.desc", "apiKey": api_key}
    data = fetch_json(api_url(config.massive.rest_base_url, f"/futures/v1/quotes/{encoded}", params), timeout_seconds)
    midpoint = quote_midpoint_from_results(data)
    if midpoint is None:
        raise RuntimeError(f"Massive did not return a usable futures quote for {instrument.symbol}")
    return price_to_units(midpoint, instrument)


def fetch_currency_units(instrument: Instrument, config: DemoConfig, api_key: str, timeout_seconds: float) -> int:
    fx_ticker = "C:" + instrument.massive_symbol.replace("/", "")
    encoded = urllib.parse.quote(fx_ticker, safe="")
    params = {"limit": "1", "order": "desc", "sort": "timestamp", "apiKey": api_key}
    data = fetch_json(api_url(config.massive.rest_base_url, f"/v3/quotes/{encoded}", params), timeout_seconds)
    midpoint = quote_midpoint_from_results(data)
    if midpoint is None:
        base, quote = instrument.massive_symbol.split("/", 1)
        fallback = fetch_json(
            api_url(config.massive.rest_base_url, f"/v1/last_quote/currencies/{base}/{quote}", {"apiKey": api_key}),
            timeout_seconds,
        )
        midpoint = quote_midpoint_from_forex_last(fallback)
    if midpoint is None:
        raise RuntimeError(f"Massive did not return a usable forex quote for {instrument.symbol}")
    return price_to_units(midpoint, instrument)


def crypto_ticker_candidates(instrument: Instrument) -> list[str]:
    pair = instrument.massive_symbol.upper()
    candidates = [pair, f"X:{pair}", pair.replace("-", ""), f"X:{pair.replace('-', '')}"]
    out: list[str] = []
    for candidate in candidates:
        if candidate not in out:
            out.append(candidate)
    return out


def fetch_crypto_units(instrument: Instrument, config: DemoConfig, api_key: str, timeout_seconds: float) -> int:
    params = {"limit": "1", "order": "desc", "sort": "timestamp", "apiKey": api_key}
    for ticker in crypto_ticker_candidates(instrument):
        encoded = urllib.parse.quote(ticker, safe="")
        data = try_fetch_json(api_url(config.massive.rest_base_url, f"/v3/quotes/{encoded}", params), timeout_seconds)
        midpoint = quote_midpoint_from_results(data) if data is not None else None
        if midpoint is not None:
            return price_to_units(midpoint, instrument)

    accepted = set(crypto_ticker_candidates(instrument))
    for ticker in (f"X:{instrument.massive_symbol.upper()}", instrument.massive_symbol.upper()):
        data = try_fetch_json(
            api_url(
                config.massive.rest_base_url,
                "/v3/snapshot",
                {"type": "crypto", "ticker": ticker, "limit": "1", "apiKey": api_key},
            ),
            timeout_seconds,
        )
        midpoint = quote_midpoint_from_snapshot(data, accepted) if data is not None else None
        if midpoint is not None:
            return price_to_units(midpoint, instrument)

    raise RuntimeError(f"Massive did not return a usable bid/ask crypto quote for {instrument.symbol}")


def fetch_units(instrument: Instrument, config: DemoConfig, api_key: str, timeout_seconds: float) -> int:
    if instrument.asset_class == "stock":
        return fetch_stock_units(instrument, config, api_key, timeout_seconds)
    if instrument.asset_class == "future":
        return fetch_future_units(instrument, config, api_key, timeout_seconds)
    if instrument.asset_class == "currency":
        return fetch_currency_units(instrument, config, api_key, timeout_seconds)
    if instrument.asset_class == "crypto":
        return fetch_crypto_units(instrument, config, api_key, timeout_seconds)
    raise ValueError(f"unsupported asset_class={instrument.asset_class!r}")


def build_price_bank(
    instruments: list[Instrument],
    config: DemoConfig,
    api_key: str,
    timeout_seconds: float,
    clients: int,
) -> list[int]:
    market_symbol_count = TOTAL_SYMBOL_COUNT - clients
    prices = [0] * market_symbol_count
    for instrument in instruments:
        units = fetch_units(instrument, config, api_key, timeout_seconds)
        prices[instrument.radio_symbol - SYMBOL_MIN_BYTE] = units
        print(
            f"{instrument.radio_symbol:3d} {instrument.asset_class:8s} "
            f"{instrument.symbol:8s} feed={instrument.massive_symbol:10s} "
            f"increment={instrument.minimum_price_increment} units={units}"
        )
    return prices


def require_ack(ack: Any, operation: str) -> None:
    if not getattr(ack, "ok", False):
        raise RuntimeError(f"{operation} failed: {getattr(ack, 'message', '')}")


def update_controls(
    bank: int,
    prices: list[int],
    transmitter_address: str,
) -> None:
    try:
        import grpc  # type: ignore[import-not-found]
    except ModuleNotFoundError as exc:
        raise RuntimeError("grpcio is required. Install with: python3 -m pip install grpcio grpcio-tools") from exc

    pb2, pb2_grpc = ensure_python_grpc_stubs()
    request = pb2.BankUpdate(bank=bank, prices_units=prices)

    with grpc.insecure_channel(transmitter_address) as channel:
        stub = pb2_grpc.TransmitterControlStub(channel)
        ack = stub.UpdateBank(request)
        require_ack(ack, f"transmitter UpdateBank({bank})")
        print(f"transmitter UpdateBank generation={ack.generation}")
        ack = stub.BankSwitch(pb2.BankSwitchRequest())
        require_ack(ack, "transmitter BankSwitch")
        print(f"transmitter BankSwitch generation={ack.generation}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Update a WBHF demo price bank from Massive quotes and request BankSwitch.")
    parser.add_argument("bank", type=int, choices=(0, 1), help="next bank number to update before BankSwitch")
    parser.add_argument("--config", type=Path, default=DEFAULT_CONFIG, help="instrument config TOML")
    parser.add_argument("--receiver", help="ignored compatibility option; receivers learn banks from the transmitter stream")
    parser.add_argument("--transmitter", help="transmitter gRPC address; overrides config")
    parser.add_argument("--timeout", type=float, default=3.0, help="Massive HTTP timeout in seconds")
    parser.add_argument("--dry-run", action="store_true", help="fetch and print prices without calling gRPC")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    api_key = os.environ.get("MASSIVE_KEY")
    if not api_key:
        raise RuntimeError("MASSIVE_KEY is not set")

    config = load_demo_config(args.config)
    transmitter_address = args.transmitter or config.transmitter_address

    clients = read_clients_constant()
    validate_market_symbols(config.instruments, clients)
    instruments = resolve_front_futures(config.instruments, config, api_key, args.timeout)
    prices = build_price_bank(instruments, config, api_key, args.timeout, clients)
    if args.dry_run:
        print("dry run: gRPC update skipped")
        return 0

    update_controls(args.bank, prices, transmitter_address)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
