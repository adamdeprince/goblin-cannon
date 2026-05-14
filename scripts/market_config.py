from __future__ import annotations

import importlib
import importlib.util
import shutil
import re
import subprocess
import sys
from dataclasses import dataclass
from decimal import Decimal, ROUND_HALF_UP
from pathlib import Path
from typing import Any

try:
    import tomllib
except ModuleNotFoundError:  # pragma: no cover - Python < 3.11 fallback.
    import tomli as tomllib  # type: ignore[no-redef]


REPO_ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = REPO_ROOT / "config" / "demo_instruments.toml"
PROTO_PATH = REPO_ROOT / "proto" / "wbhf_modem" / "control" / "v1" / "receiver_control.proto"
GENERATED_DIR = REPO_ROOT / "build" / "python_grpc"
SYMBOLS_HEADER = REPO_ROOT / "include" / "wbhf_modem" / "symbols.hpp"
SYMBOL_MIN_BYTE = 2
TOTAL_SYMBOL_COUNT = 254


@dataclass(frozen=True)
class Instrument:
    asset_class: str
    symbol: str
    radio_symbol: int
    minimum_price_increment: Decimal
    unit: str
    massive_symbol: str
    front: bool = False
    description: str = ""


@dataclass(frozen=True)
class MassiveConfig:
    rest_base_url: str = "https://api.massive.com"
    stock_websocket_url: str = "wss://socket.massive.com/stocks"
    future_websocket_url: str = "wss://socket.massive.com/futures"
    forex_websocket_url: str = "wss://socket.massive.com/forex"
    crypto_websocket_url: str = "wss://socket.massive.com/crypto"


@dataclass(frozen=True)
class DemoConfig:
    receiver_address: str
    transmitter_address: str
    massive: MassiveConfig
    instruments: list[Instrument]


def read_clients_constant() -> int:
    text = SYMBOLS_HEADER.read_text(encoding="utf-8")
    match = re.search(r"inline\s+constexpr\s+std::size_t\s+Clients\s*=\s*(\d+)\s*;", text)
    if not match:
        raise RuntimeError(f"could not parse Clients constant from {SYMBOLS_HEADER}")
    return int(match.group(1))


def parse_increment(raw: Any, symbol: str) -> Decimal:
    if isinstance(raw, dict):
        numerator = Decimal(str(raw["numerator"]))
        denominator = Decimal(str(raw["denominator"]))
        if denominator == 0:
            raise ValueError(f"{symbol} minimum_price_increment denominator must be nonzero")
        return numerator / denominator
    value = Decimal(str(raw))
    if value <= 0:
        raise ValueError(f"{symbol} minimum_price_increment must be positive")
    return value


def default_massive_symbol(asset_class: str, symbol: str) -> str:
    if asset_class == "currency":
        return symbol.replace("-", "/")
    return symbol


def load_demo_config(path: Path = DEFAULT_CONFIG) -> DemoConfig:
    with path.open("rb") as f:
        data = tomllib.load(f)

    control = data.get("control", {})
    massive_raw = data.get("massive", {})
    massive = MassiveConfig(
        rest_base_url=str(massive_raw.get("rest_base_url", "https://api.massive.com")).rstrip("/"),
        stock_websocket_url=str(massive_raw.get("stock_websocket_url", "wss://socket.massive.com/stocks")),
        future_websocket_url=str(massive_raw.get("future_websocket_url", "wss://socket.massive.com/futures")),
        forex_websocket_url=str(massive_raw.get("forex_websocket_url", "wss://socket.massive.com/forex")),
        crypto_websocket_url=str(massive_raw.get("crypto_websocket_url", "wss://socket.massive.com/crypto")),
    )

    instruments: list[Instrument] = []
    for raw in data.get("instruments", []):
        asset_class = str(raw["asset_class"]).lower()
        symbol = str(raw["symbol"]).upper()
        massive_symbol = str(raw.get("massive_symbol", default_massive_symbol(asset_class, symbol))).upper()
        instruments.append(
            Instrument(
                asset_class=asset_class,
                symbol=symbol,
                radio_symbol=int(raw["radio_symbol"]),
                minimum_price_increment=parse_increment(raw["minimum_price_increment"], symbol),
                unit=str(raw.get("unit", "")),
                massive_symbol=massive_symbol,
                front=bool(raw.get("front", False)),
                description=str(raw.get("description", "")),
            )
        )

    return DemoConfig(
        receiver_address=str(control.get("receiver_address", "127.0.0.1:50051")),
        transmitter_address=str(control.get("transmitter_address", "127.0.0.1:50052")),
        massive=massive,
        instruments=instruments,
    )


def validate_market_symbols(instruments: list[Instrument], clients: int) -> None:
    market_symbol_max = 256 - clients - 1
    seen_symbols: set[int] = set()
    seen_names: set[tuple[str, str]] = set()
    for instrument in instruments:
        if instrument.radio_symbol < SYMBOL_MIN_BYTE or instrument.radio_symbol > market_symbol_max:
            raise ValueError(
                f"{instrument.symbol} radio_symbol={instrument.radio_symbol} is outside "
                f"market range [{SYMBOL_MIN_BYTE}, {market_symbol_max}]"
            )
        if instrument.radio_symbol in seen_symbols:
            raise ValueError(f"duplicate radio_symbol={instrument.radio_symbol}")
        seen_symbols.add(instrument.radio_symbol)

        key = (instrument.asset_class, instrument.symbol)
        if key in seen_names:
            raise ValueError(f"duplicate instrument {instrument.asset_class}:{instrument.symbol}")
        seen_names.add(key)


def price_to_units(price: Decimal, instrument: Instrument) -> int:
    units = price / instrument.minimum_price_increment
    return int(units.quantize(Decimal("1"), rounding=ROUND_HALF_UP))


def midpoint_to_units(bid: Any, ask: Any, instrument: Instrument) -> int | None:
    if bid is None or ask is None:
        return None
    bid_dec = Decimal(str(bid))
    ask_dec = Decimal(str(ask))
    if bid_dec <= 0 or ask_dec <= 0:
        return None
    return price_to_units((bid_dec + ask_dec) / Decimal("2"), instrument)


def ensure_python_grpc_stubs() -> tuple[Any, Any]:
    GENERATED_DIR.mkdir(parents=True, exist_ok=True)
    output_pb = GENERATED_DIR / "wbhf_modem" / "control" / "v1" / "receiver_control_pb2.py"
    output_grpc = GENERATED_DIR / "wbhf_modem" / "control" / "v1" / "receiver_control_pb2_grpc.py"
    if (
        not output_pb.exists()
        or not output_grpc.exists()
        or output_pb.stat().st_mtime < PROTO_PATH.stat().st_mtime
        or output_grpc.stat().st_mtime < PROTO_PATH.stat().st_mtime
    ):
        if importlib.util.find_spec("grpc_tools.protoc") is not None:
            command = [
                sys.executable,
                "-m",
                "grpc_tools.protoc",
                f"--proto_path={REPO_ROOT / 'proto'}",
                f"--python_out={GENERATED_DIR}",
                f"--grpc_python_out={GENERATED_DIR}",
                str(PROTO_PATH),
            ]
        else:
            protoc = shutil.which("protoc")
            grpc_plugin = shutil.which("grpc_python_plugin")
            if not protoc or not grpc_plugin:
                raise RuntimeError(
                    "grpcio-tools or protoc plus grpc_python_plugin is required to generate Python gRPC stubs. "
                    "Install with: python3 -m pip install grpcio grpcio-tools"
                )
            command = [
                protoc,
                f"--proto_path={REPO_ROOT / 'proto'}",
                f"--python_out={GENERATED_DIR}",
                f"--grpc_out={GENERATED_DIR}",
                f"--plugin=protoc-gen-grpc={grpc_plugin}",
                str(PROTO_PATH),
            ]

        result = subprocess.run(command, check=False)
        if result.returncode != 0:
            raise RuntimeError("failed to generate Python gRPC stubs")

    sys.path.insert(0, str(GENERATED_DIR))
    pb2 = importlib.import_module("wbhf_modem.control.v1.receiver_control_pb2")
    pb2_grpc = importlib.import_module("wbhf_modem.control.v1.receiver_control_pb2_grpc")
    return pb2, pb2_grpc
