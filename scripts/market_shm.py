"""Shared-memory SPSC ring for market-data messages."""

from __future__ import annotations

import mmap
import struct
import time
from pathlib import Path


MAGIC = 0x544B4D57
VERSION = 1
HEADER_BYTES = 128
SLOT_METADATA_BYTES = 24

MAGIC_OFFSET = 0
VERSION_OFFSET = 4
CAPACITY_OFFSET = 8
PAYLOAD_BYTES_OFFSET = 12
SLOT_STRIDE_OFFSET = 16
READ_SEQ_OFFSET = 24
WRITE_SEQ_OFFSET = 32
DROPPED_FULL_OFFSET = 40
DROPPED_OVERSIZE_OFFSET = 48
INVALID_RECORDS_OFFSET = 56

SLOT_SEQ_OFFSET = 0
SLOT_BID_OFFSET = 8
SLOT_SIZE_OFFSET = 16
SLOT_FLAGS_OFFSET = 20
SLOT_PAYLOAD_OFFSET = 24


def _u32(mm: mmap.mmap, offset: int) -> int:
    return struct.unpack_from("<I", mm, offset)[0]


def _u64(mm: mmap.mmap, offset: int) -> int:
    return struct.unpack_from("<Q", mm, offset)[0]


def _store_u64(mm: mmap.mmap, offset: int, value: int) -> None:
    struct.pack_into("<Q", mm, offset, value & ((1 << 64) - 1))


def _fetch_add_u64(mm: mmap.mmap, offset: int, value: int) -> None:
    _store_u64(mm, offset, _u64(mm, offset) + value)


class MarketDataShmProducer:
    def __init__(self, path: Path, wait_timeout: float = 5.0) -> None:
        self.path = path
        deadline = time.monotonic() + wait_timeout
        while not path.exists():
            if time.monotonic() >= deadline:
                raise TimeoutError(f"timed out waiting for market shared-memory ring: {path}")
            time.sleep(0.01)

        self.file = path.open("r+b")
        self.mm = mmap.mmap(self.file.fileno(), 0)
        while _u32(self.mm, MAGIC_OFFSET) != MAGIC:
            if time.monotonic() >= deadline:
                raise TimeoutError(f"market shared-memory ring was not initialized: {path}")
            time.sleep(0.01)
        if _u32(self.mm, VERSION_OFFSET) != VERSION:
            raise RuntimeError("market shared-memory ring version mismatch")
        self.capacity = _u32(self.mm, CAPACITY_OFFSET)
        self.payload_bytes = _u32(self.mm, PAYLOAD_BYTES_OFFSET)
        self.slot_stride = _u32(self.mm, SLOT_STRIDE_OFFSET)
        if self.capacity <= 0 or self.payload_bytes < 2 or self.slot_stride < SLOT_METADATA_BYTES + self.payload_bytes:
            raise RuntimeError("market shared-memory ring has invalid dimensions")

    def close(self) -> None:
        self.mm.close()
        self.file.close()

    def try_push(self, payload: bytes, bid_cents: int) -> bool:
        if len(payload) < 2:
            _fetch_add_u64(self.mm, INVALID_RECORDS_OFFSET, 1)
            return False
        if len(payload) > self.payload_bytes:
            _fetch_add_u64(self.mm, DROPPED_OVERSIZE_OFFSET, 1)
            return False

        read_seq = _u64(self.mm, READ_SEQ_OFFSET)
        write_seq = _u64(self.mm, WRITE_SEQ_OFFSET)
        if write_seq - read_seq >= self.capacity:
            _fetch_add_u64(self.mm, DROPPED_FULL_OFFSET, 1)
            return False

        slot_offset = HEADER_BYTES + (write_seq % self.capacity) * self.slot_stride
        _store_u64(self.mm, slot_offset + SLOT_SEQ_OFFSET, 0)
        _store_u64(self.mm, slot_offset + SLOT_BID_OFFSET, bid_cents)
        struct.pack_into("<I", self.mm, slot_offset + SLOT_SIZE_OFFSET, len(payload))
        struct.pack_into("<I", self.mm, slot_offset + SLOT_FLAGS_OFFSET, 0)
        self.mm[slot_offset + SLOT_PAYLOAD_OFFSET:slot_offset + SLOT_PAYLOAD_OFFSET + len(payload)] = payload
        _store_u64(self.mm, slot_offset + SLOT_SEQ_OFFSET, write_seq + 1)
        _store_u64(self.mm, WRITE_SEQ_OFFSET, write_seq + 1)
        return True

    def stats(self) -> dict[str, int]:
        return {
            "read_seq": _u64(self.mm, READ_SEQ_OFFSET),
            "write_seq": _u64(self.mm, WRITE_SEQ_OFFSET),
            "dropped_full": _u64(self.mm, DROPPED_FULL_OFFSET),
            "dropped_oversize": _u64(self.mm, DROPPED_OVERSIZE_OFFSET),
            "invalid_records": _u64(self.mm, INVALID_RECORDS_OFFSET),
        }

    def __enter__(self) -> "MarketDataShmProducer":
        return self

    def __exit__(self, _exc_type: object, _exc: object, _tb: object) -> None:
        self.close()
