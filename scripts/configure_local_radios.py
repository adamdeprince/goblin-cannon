#!/usr/bin/env python3
"""Configure local Goblin Cannon sender/receiver processes over gRPC."""

from __future__ import annotations

import argparse
import time

from market_config import (
    DEFAULT_CONFIG,
    TOTAL_SYMBOL_COUNT,
    ensure_python_grpc_stubs,
    load_demo_config,
    read_clients_constant,
)


UINT32_MASK = 0xFFFFFFFF
SYMBOL_PERMISSION_MASK_BYTES = (TOTAL_SYMBOL_COUNT + 7) // 8


def default_qpsk_sequence(symbols: int, seed: int) -> list[int]:
    state = seed if seed != 0 else 0x13579BDF
    out: list[int] = []
    for _ in range(symbols):
        state ^= (state << 13) & UINT32_MASK
        state &= UINT32_MASK
        state ^= state >> 17
        state &= UINT32_MASK
        state ^= (state << 5) & UINT32_MASK
        state &= UINT32_MASK
        out.append(state & 0x3)
    return out


def modulation_value(pb2: object, value: str) -> int:
    mapping = {
        "bpsk": "MODULATION_BPSK",
        "qpsk": "MODULATION_QPSK",
        "8psk": "MODULATION_8PSK",
        "16qam": "MODULATION_16QAM",
        "64qam": "MODULATION_64QAM",
        "256qam": "MODULATION_256QAM",
        "1024qam": "MODULATION_1024QAM",
        "16qci": "MODULATION_16QCI",
        "16-qci": "MODULATION_16QCI",
        "64qci": "MODULATION_64QCI",
        "64-qci": "MODULATION_64QCI",
        "256qci": "MODULATION_256QCI",
        "256-qci": "MODULATION_256QCI",
        "1024qci": "MODULATION_1024QCI",
        "1024-qci": "MODULATION_1024QCI",
    }
    try:
        return getattr(pb2, mapping[value.lower()])
    except KeyError as exc:
        raise ValueError(f"unsupported modulation: {value}") from exc


def session_key() -> bytes:
    return bytes((0x41 + i * 17) & 0xFF for i in range(16))


def make_restart_request(pb2: object, args: argparse.Namespace) -> object:
    request = pb2.RestartRequest()
    request.expected_schedule_epoch = args.expected_schedule_epoch
    request.modulation = modulation_value(pb2, args.modulation)
    request.bandwidth_hz = args.bandwidth_hz
    request.center_frequency_hz = args.center_frequency_hz
    request.sample_rate_hz = args.sample_rate_hz
    request.symbol_rate_hz = args.symbol_rate_hz
    request.receiver_oversampling = args.receiver_oversampling
    request.symbols_per_frame = args.symbols_per_frame
    request.pilot_interval_symbols = args.pilot_interval_symbols
    request.header_repetition = args.header_repetition
    request.acquisition_sequence.extend(default_qpsk_sequence(64, 0x12345678))
    request.equalizer_training_sequence.extend(default_qpsk_sequence(args.training_symbols, 0x87654321))
    request.carrier_correction = args.carrier_correction
    request.adaptive_equalization = args.adaptive_equalization
    request.sample_clock_recovery = args.sample_clock_recovery
    request.recursive_equalization = args.recursive_equalization
    request.message_sequence_numbers = args.message_sequence_numbers
    request.equalizer_delay_symbols = args.equalizer_delay_symbols
    request.equalizer_feedforward_taps = args.equalizer_feedforward_taps
    request.equalizer_feedback_taps = args.equalizer_feedback_taps
    request.compact_header = args.compact_header
    request.header_modulation = modulation_value(pb2, args.header_modulation)
    request.differential_mapping = getattr(pb2, {
        "none": "DIFFERENTIAL_NONE", "dbpsk": "DIFFERENTIAL_DBPSK",
        "dqpsk": "DIFFERENTIAL_DQPSK", "pi4_dqpsk": "DIFFERENTIAL_PI4_DQPSK",
    }[args.differential_mapping])
    request.recovery_interval_frames = args.recovery_interval_frames
    request.fractionally_spaced_equalization = args.fractionally_spaced_equalization
    request.equalizer_reselect_interval = args.equalizer_reselect_interval
    request.pilot_sequence.extend([0, 1] if args.modulation.lower()=="bpsk" else [0, 1, 2, 3])
    request.soft_demapping = args.soft_demapping
    request.bch_payload = args.bch_payload
    request.walsh_bits = args.walsh_bits
    request.interleaver_rows = args.interleaver_rows
    request.interleaver_columns = args.interleaver_columns
    request.audio_waveform = getattr(pb2, {
        "single_carrier": "AUDIO_SINGLE_CARRIER", "fsk4": "AUDIO_FSK4", "fsk8": "AUDIO_FSK8",
        "bpsk_frequency_diversity": "AUDIO_BPSK_FREQUENCY_DIVERSITY",
    }[args.audio_waveform])
    request.fsk_useful_ms = args.fsk_useful_ms
    request.fsk_guard_ms = args.fsk_guard_ms
    request.diversity_wait_ms = args.diversity_wait_ms
    request.fec.constraint_length = 7
    request.fec.generator0 = 0o171
    request.fec.generator1 = 0o133
    if args.fec == "k9-1/2":
        request.fec.constraint_length = 9
        request.fec.generator0, request.fec.generator1 = 0o753, 0o561
    elif args.fec == "k9-1/3":
        request.fec.constraint_length = 9
        request.fec.generator0, request.fec.generator1, request.fec.generator2 = 0o557, 0o663, 0o711
    request.fec.puncture_pattern.extend([1, 1, 1] if args.fec == "k9-1/3" else [1, 1])
    # Conventional Viterbi hard output goes through the existing message CRC.
    request.fec.decoded_bit_confidence_threshold = 0.0 if args.soft_demapping or args.walsh_bits or args.audio_waveform != "single_carrier" else 0.20
    request.sync_timestamp_enabled = args.sync_timestamp
    request.sync_timestamp_max_skew_seconds = args.sync_timestamp_max_skew_seconds
    request.acquisition_confidence_threshold = 0.35
    request.pilot_confidence_threshold = 0.20
    request.symbol_confidence_threshold = 0.18
    request.frame_counter_start = args.frame_counter_start
    request.rrc_rolloff = 0.25
    request.filter_span_symbols = 8
    return request


def require_ack(ack: object, operation: str) -> None:
    if not getattr(ack, "ok", False):
        raise RuntimeError(f"{operation} failed: {getattr(ack, 'message', '')}")


def channel_ready(grpc: object, address: str, timeout_seconds: float) -> object:
    deadline = time.monotonic() + timeout_seconds
    last_error: BaseException | None = None
    while time.monotonic() < deadline:
        channel = grpc.insecure_channel(address)
        try:
            grpc.channel_ready_future(channel).result(timeout=0.25)
            return channel
        except Exception as exc:  # noqa: BLE001 - retry until startup deadline.
            last_error = exc
            channel.close()
            time.sleep(0.05)
    raise TimeoutError(f"timed out waiting for gRPC server at {address}: {last_error}")


def allow_all_permissions() -> bytes:
    mask = bytearray([0xFF] * SYMBOL_PERMISSION_MASK_BYTES)
    unused_bits = len(mask) * 8 - TOTAL_SYMBOL_COUNT
    if unused_bits:
        mask[-1] &= 0xFF >> unused_bits
    return bytes(mask)


def default_receiver_permissions(client_id: int, clients: int) -> bytes:
    if client_id < 0 or client_id >= clients:
        raise ValueError(f"client_id must be in [0, {clients - 1}]")
    mask = bytearray(SYMBOL_PERMISSION_MASK_BYTES)
    market_symbol_max = 255 - clients
    for symbol in range(2, market_symbol_max + 1):
        index = symbol - 2
        mask[index // 8] |= 1 << (index % 8)
    client_symbol = 256 - clients + client_id
    index = client_symbol - 2
    mask[index // 8] |= 1 << (index % 8)
    return bytes(mask)


def seed_bank(pb2: object, transmitter_stub: object, clients: int, bank: int) -> None:
    market_symbol_count = TOTAL_SYMBOL_COUNT - clients
    prices = [1_000_000 + bank * 100_000 + i for i in range(market_symbol_count)]
    request = pb2.BankUpdate(bank=bank, prices_units=prices)
    require_ack(transmitter_stub.UpdateBank(request), f"transmitter UpdateBank({bank})")


def banks_to_seed(args: argparse.Namespace) -> list[int]:
    if args.seed_both_banks:
        return [0, 1]
    banks = [0]
    if args.active_bank != 0:
        banks.append(args.active_bank)
    return banks


def configure(args: argparse.Namespace) -> None:
    try:
        import grpc  # type: ignore[import-not-found]
    except ModuleNotFoundError as exc:
        raise RuntimeError("grpcio is required. Install with: python3 -m pip install grpcio grpcio-tools") from exc

    pb2, pb2_grpc = ensure_python_grpc_stubs()
    restart = make_restart_request(pb2, args)
    key = session_key()

    receiver_channel = channel_ready(grpc, args.receiver, args.startup_timeout)
    transmitter_channel = channel_ready(grpc, args.transmitter, args.startup_timeout)
    try:
        receiver = pb2_grpc.ReceiverControlStub(receiver_channel)
        transmitter = pb2_grpc.TransmitterControlStub(transmitter_channel)

        require_ack(receiver.UpdateEncryptionKey(pb2.EncryptionKeyUpdate(aes128_key=key)), "receiver key update")
        require_ack(transmitter.UpdateEncryptionKey(pb2.EncryptionKeyUpdate(aes128_key=key)), "transmitter key update")
        print("updated AES-128 key on receiver and sender")

        clients = read_clients_constant()
        if not args.no_permissions:
            mask = allow_all_permissions() if args.allow_all_permissions else default_receiver_permissions(args.client_id, clients)
            permissions = pb2.PermissionsUpdate(allowed_symbol_mask=mask)
            require_ack(receiver.Permissions(permissions), "receiver permissions")
            scope = "all symbols" if args.allow_all_permissions else f"market symbols plus client {args.client_id}"
            print(f"updated receiver permissions to allow {scope}")

        require_ack(receiver.Restart(restart), "receiver restart")
        require_ack(transmitter.Restart(restart), "transmitter restart")

        if not args.no_bank_seed:
            for bank in banks_to_seed(args):
                seed_bank(pb2, transmitter, clients, bank)
                print(f"seeded bank {bank} on sender; receiver will learn it from the transmitter stream")
            require_ack(transmitter.UseBank(pb2.UseBankRequest(bank=args.active_bank)), "transmitter UseBank")
            print(f"set sender active bank to {args.active_bank}")

        if args.enqueue_test_message:
            payload = bytes([args.active_bank, 2, 2])
            require_ack(transmitter.EnqueueMessage(pb2.TransmitMessage(payload=payload, bid_cents=100)),
                        "transmitter test message")

        print(
            f"configured receiver={args.receiver} transmitter={args.transmitter} "
            f"modulation={args.modulation} bandwidth_hz={args.bandwidth_hz}"
        )
    finally:
        receiver_channel.close()
        transmitter_channel.close()


def parse_args() -> argparse.Namespace:
    config = load_demo_config(DEFAULT_CONFIG)
    parser = argparse.ArgumentParser(description="Push matching local radio connection data over gRPC.")
    parser.add_argument("--receiver", default=config.receiver_address)
    parser.add_argument("--transmitter", default=config.transmitter_address)
    parser.add_argument("--modulation", default="64qam")
    parser.add_argument("--bandwidth-hz", type=float, default=48000.0)
    parser.add_argument("--sample-rate-hz", type=float, default=48000.0)
    parser.add_argument("--symbol-rate-hz", type=float, default=24000.0)
    parser.add_argument("--center-frequency-hz", type=float, default=7_100_000.0)
    parser.add_argument("--expected-schedule-epoch", type=int, default=1)
    parser.add_argument("--frame-counter-start", type=int, default=1)
    parser.add_argument("--receiver-oversampling", type=int, default=8)
    parser.add_argument("--symbols-per-frame", type=int, default=64)
    parser.add_argument("--pilot-interval-symbols", type=int, default=32)
    parser.add_argument("--header-repetition", type=int, default=3)
    parser.add_argument("--training-symbols", type=int, default=64)
    parser.add_argument("--carrier-correction", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--adaptive-equalization", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--sample-clock-recovery", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--recursive-equalization", action=argparse.BooleanOptionalAction, default=False)
    parser.add_argument("--message-sequence-numbers", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--equalizer-delay-symbols", type=int, default=0)
    parser.add_argument("--equalizer-feedforward-taps", type=int, default=3)
    parser.add_argument("--equalizer-feedback-taps", type=int, default=4)
    parser.add_argument("--compact-header", action=argparse.BooleanOptionalAction, default=False)
    parser.add_argument("--fec", choices=("1/2", "k9-1/2", "k9-1/3"), default="1/2")
    parser.add_argument("--soft-demapping", action=argparse.BooleanOptionalAction, default=False)
    parser.add_argument("--bch-payload", action=argparse.BooleanOptionalAction, default=False)
    parser.add_argument("--walsh-bits", type=int, choices=(0, 3), default=0)
    parser.add_argument("--interleaver-rows", type=int, default=0)
    parser.add_argument("--interleaver-columns", type=int, default=0)
    parser.add_argument("--audio-waveform", choices=("single_carrier", "fsk4", "fsk8", "bpsk_frequency_diversity"), default="single_carrier")
    parser.add_argument("--fsk-useful-ms", type=float, default=4)
    parser.add_argument("--diversity-wait-ms", type=float, default=1)
    parser.add_argument("--fsk-guard-ms", type=float, default=8)
    parser.add_argument("--header-modulation", choices=("qpsk", "bpsk"), default="qpsk")
    parser.add_argument("--differential-mapping", choices=("none", "dbpsk", "dqpsk", "pi4_dqpsk"), default="none")
    parser.add_argument("--recovery-interval-frames", type=int, default=0)
    parser.add_argument("--fractionally-spaced-equalization", action=argparse.BooleanOptionalAction, default=False)
    parser.add_argument("--equalizer-reselect-interval", type=int, default=0)
    parser.add_argument("--sync-timestamp", action="store_true")
    parser.add_argument("--sync-timestamp-max-skew-seconds", type=float, default=0.1)
    parser.add_argument("--active-bank", type=int, choices=(0, 1), default=0)
    parser.add_argument("--client-id", type=int, default=0)
    parser.add_argument("--no-bank-seed", action="store_true")
    parser.add_argument("--seed-both-banks", action="store_true", help="seed bank 0 and bank 1 instead of only bank 0")
    parser.add_argument("--no-permissions", action="store_true", help="skip the default receiver permissions update")
    parser.add_argument("--allow-all-permissions", action="store_true", help="override the client-specific default permission mask")
    parser.add_argument("--enqueue-test-message", action="store_true")
    parser.add_argument("--startup-timeout", type=float, default=5.0)
    return parser.parse_args()


def main() -> int:
    configure(parse_args())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
