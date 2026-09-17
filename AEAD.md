# AES-256-GCM message path

The production realtime path uses OpenSSL AES-256-GCM before payload FEC. The
target x86_64 hosts provide AES-NI and PCLMULQDQ. EVP contexts and key schedules
are retained; each record supplies an explicit 96-bit nonce and a 128-bit tag.
Decryption keeps plaintext in private scratch storage until tag verification
succeeds. There is no plaintext/CRC fallback on the realtime path.
The implementation uses the library's [EVP authenticated-encryption API](https://docs.openssl.org/3.4/man3/EVP_EncryptInit/).

## Provisioning and restart

Provision an epoch journal **once**, in a private persistent directory owned by
the transmitter account:

```sh
install -d -m 700 /var/lib/goblin-cannon
build/goblin_cannon_epoch init /var/lib/goblin-cannon/tx-epochs
export GOBLIN_CANNON_EPOCH_STATE=/var/lib/goblin-cannon/tx-epochs
```

The library also accepts `RealtimePipelineConfig.transmitter_epoch_path`.
Initialization uses exclusive creation; runtime reservation never creates a
missing file. Each reservation locks the journal, appends a strictly increasing
64-bit epoch and its complement, and calls `fsync` before returning it. Partial,
damaged, exhausted or inaccessible journals stop startup. Reservations have
single-use ownership, so copying a configuration cannot start two transmitters
with the same epoch. Per-record sequence numbers start at 1 and stop before
wraparound. The nonce is `uint64_be(epoch) || uint32_be(frame_sequence)`.
Clock time never participates in nonce allocation.

Keep this journal with the key's transmitter domain across restarts. Do not
restore an older journal, truncate it, provision a second journal under the
same key, or clone the key/journal to another active host. Losing or rolling
back state requires a **new key before reprovisioning**. Independent transmitters
and opposite directions need independent keys unless they share the same
durable allocator. As with any persisted nonce counter, administrative rollback
of storage is outside the journal's crash-safety guarantee.

Both endpoints must upgrade together. On the trusted fiber control connection:

1. Set the same 32-byte `aes256_key` and nonzero `key_id` at both ends.
2. Restart the transmitter; its `ControlAck.transmitter_epoch` is already durable.
3. Pass that epoch as `RestartRequest.expected_schedule_epoch` to the receiver.

`scripts/configure_local_radios.py` performs this ordering for the demo. Its
fixed demo key is a fixture, not a deployment secret. A restarted receiver must
negotiate a fresh transmitter epoch instead of rejoining an old session with
empty replay state. The controlled receiver rejects non-increasing restart
epochs; the direct C++ receiver requires an explicitly configured nonzero epoch.

## Authenticated record

| Offset | Bytes | Field |
| ---: | ---: | --- |
| 0 | 1 | Format version (1) |
| 1 | 1 | Bank (0/1) |
| 2 | 1 | Application sequencing enabled (0/1) |
| 3 | 4 | Key ID |
| 7 | 8 | Transmitter epoch |
| 15 | 4 | Mandatory frame sequence |
| 19 | 4 | Application sequence |
| 23 | 2 | Encrypted body length |
| 25 | length | Ciphertext, excluding the bank byte |
| 25 + length | 16 | GCM tag |

Integers are big-endian. All 25 header bytes are associated data. If enabled,
the stream's exact eight timestamp bytes are also associated data. COBS escapes
the entire record; a zero delimiter separates records. Header parsing is bounded
before verification; unauthenticated values never update replay state or reach
application routing. Valid records from another epoch and repeated/older frame
sequences are rejected. Application sequences retain per-bank/instrument
duplicate/staleness checks and uint32 serial arithmetic.

`authentication_failures` counts failed tags, unknown key IDs, and malformed
authentication envelopes. `replay_rejections` counts authenticated records rejected
by epoch/frame sequencing. Neither resets the modem or increments lock loss.
Both appear in `ReceiverControl.GetMetrics`; authentication failures also appear
as `authentication_failure` events in the receiver session stream.

RF-header CRCs screen acquisition/framing only. Production message records have
no CRC trailer. Legacy standalone codec fixtures still exercise the old CRC and
CTR helper APIs, separately from the mandatory production AEAD path.

## Remaining work

The authenticated key ID allows a future key ring to select a preinitialized
context. This change supports key replacement at a coordinated fresh-epoch
restart. It does **not** implement two-key overlap, mid-stream changeover, or
coordinated old-key retirement; `D6_key_rotation` remains an expected failure.

## Simulated channel validation

`goblin_cannon_aead_tests` is tagged `quick;assert;D6;simulated_channel`. It checks
a published AES-256-GCM vector, reused EVP contexts, every header/ciphertext/tag
byte, full-size messages, replay after reacquisition and epoch change, separate
sender process restarts, concurrent reservations, and torn/missing state.
The modem regression also feeds wrong-key records through the RF/FEC receiver
and reads actual rejection counters over gRPC, asserting zero lock losses and
zero sink deliveries.

`scripts/aead_campaign.py` selects A8/D6, remaining recovery-profile defects,
message/audio regressions, both 12-case B5 profiles, and the six BPSK/QPSK/8-PSK
coding configurations. It uses the existing channel simulator and preserves
declared seeds and durations. See `results/aead/SUMMARY.md` for measurements;
host timing stays in separate `.host.json` files.
