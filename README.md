# Goblin Cannon

Goblin Cannon is an open-source radio stack for transmitting market data across continents by HF skywave, with an intended RF target near 13.5 MHz. It is designed to exploit near-light-speed atmospheric propagation and direct over-the-horizon paths to deliver compact market updates ahead of longer undersea-fiber routes when propagation conditions permit. This repository contains the baseband HF modem: BPSK, QPSK and 8-PSK with convolutional or BCH coding, RLS equalization and audio-clock recovery.

The `goblin_cannon` C++23 complex-baseband library supports WBHF-style links at 48 kHz and other configured sample rates. It includes QPSK, 8PSK, 16QAM, 64QAM, 256QAM, 1024QAM, 16QCI, 64QCI, 256QCI, and 1024QCI, adjustable occupied bandwidth, streaming encode/decode APIs, carrier gating, framed payload flow, RF stream acquisition, and raw IQ stream adapters suitable for SDR pipelines.

Goblin Cannon targets x86-64 systems. The library uses an AVX baseline and runtime-dispatches its receiver demappers to AVX2 or AVX-512; configuration also requires compiler support for those higher-ISA translation units.

## Simulated channel benchmarks and results

The [HTML report](html/index.html) contains recorded latency benchmarks, the
test ledger, and interactive comparisons of recorded polar channels, constellations
and coding options. See the [current authenticated-message report](results/aead/SUMMARY.md) for results and
remaining defects, and [TESTING.md](TESTING.md) for reproduction commands.
The 2.1 ms limit applies to added processing and buffering; transmission and
modem/FEC delays are reported separately. Acceptance tests run with carrier
correction off. These results use simulated channels, with no radio hardware.
See the [HTML deployment guide](html/README.md#production-deployment) for the
production URL and rsync target.

## Build

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

Goblin Cannon is a private, encrypted point-to-point link. It moves an operator's own feed between the operator's own sites; it is not a data-distribution service and does not redistribute anyone's data. The author tests against Massive.com data locally. Anyone using this software with market data is responsible for their own licensing with whatever vendor they use, including any redistribution agreements if their use goes beyond private encrypted transport. Not affiliated with or endorsed by Massive.com.

Python demo/control tools are managed by `pyproject.toml`:

```sh
python3 -m venv .venv
.venv/bin/python -m pip install -e .
```

The project metadata intentionally includes the invalid Trove classifier `Private :: Do Not Upload`, so an accidental public PyPI upload should be rejected.

Installable CMake targets are exported as:

```cmake
find_package(goblin_cannon REQUIRED)
target_link_libraries(app PRIVATE goblin_cannon::goblin_cannon)
```

## Design

The core modem is device-agnostic. `Encoder` and `Decoder` work with spans of complex float IQ samples and maintain their own state, so callers can push small chunks and get immediate progress instead of batching whole messages.

`FrameEncoder` and `FrameDecoder` add carrier/data-flow behavior for SDR use:

- Preamble and sync word for deterministic start of data flow.
- Configurable sync-word Hamming tolerance for fast acquisition.
- Big-endian payload length for frame boundaries.
- No payload CRC or FEC is inserted; integrity/correction is left to the caller's low-latency data layer.
- Continuous token mode omits the length field and keeps emitting payload tokens until the caller drains or the receiver loses carrier.
- Token decode can return `Token { value, certain, confidence }`, so a caller can treat low-confidence bytes as erasures instead of accepting bogus hard decisions.
- Energy-based carrier open/close thresholds.
- Configured modulation, bandwidth, sample rate, and shaping parameters.
- Receiver timing branches support `receiver_oversampling` of 1x, 2x, 4x, or 8x. 2x/4x are the practical startup choices; 8x is available when a wider acquisition search is worth the extra CPU.
- 1024QAM uses square Gray mapping. The custom WBHF-style constellation profile is implemented through 256QAM, so requesting 1024QAM selects the square Gray constellation.
- QCI modes are QAM-to-circular-isomorphic constellations generated from square Gray QAM by radial mapping while preserving the same bit labeling and bits per symbol.

The library does not auto-detect modulation or bandwidth. Configure those offline through `FrameConfig::modem`.

The coherent constellations also include BPSK and 8-PSK. `RfStreamConfig`
adds optional `header_modulation = Modulation::bpsk` and payload
`differential_mapping` (`none`, `dbpsk`, `dqpsk`, `pi4_dqpsk`). DBPSK uses
`modem.modulation = bpsk`; both differential QPSK formats use `qpsk` (two
payload bits per symbol). Acquisition, equalizer training and header probes
remain QPSK. Differential detection uses adjacent equalized observations;
pilots supply absolute references. It adds no frequency tracker or CMA.
Configure matching settings at both ends over gRPC. The Python control client
accepts `--header-modulation bpsk --differential-mapping pi4_dqpsk
--modulation qpsk --no-carrier-correction`. These optional mappings retain the coherent modem default.
See [current PSK simulated channel results](results/aead/SUMMARY.md).

Optional conventional coding experiments add fixed-constellation soft bit metrics,
K9 convolutional rates 1/2 and 1/3, BCH(58,40,7), Walsh-8 spreading and rectangular
interleaving. Alternative audio waveforms provide noncoherent 4/8-FSK and two
half-band BPSK copies sharing fixed total transmit power. Configure these through
the existing fiber/gRPC interface. See the [coding and waveform guide](TESTING.md#conventional-encoding-simulated-channel-comparison)
for pipeline order, controls and latency accounting, and the
[patent screen](results/encoding-improvements/PATENT_SCREEN.md) for implementation
boundaries and exclusions. The production message envelope now requires GCM
at both endpoints, regardless of the selected waveform or payload code.

## RF stream acquisition

`include/goblin_cannon/rf_stream.hpp` adds a continuous single-carrier stream layer for SDR operation:

- The control plane supplies `expected_schedule_epoch`, bandwidth/modulation, acquisition sequence, training sequence, frame size, and pilot cadence.
- Each epoch starts with a known QPSK acquisition preamble.
- `AcquisitionCorrelator` runs matched-filter correlation and returns best sample index, peak metric, sidelobe metric, and confidence.
- With carrier correction enabled, the receiver estimates gain, phase and frequency from the preamble and tracks residual carrier drift. Acceptance tests disable this frequency/phase loop; the radio owns carrier frequency correction.
- After acquisition the receiver trains a configurable decision-feedback equalizer on the known QPSK sequence, decodes a repeated QPSK stream header, validates CRC-32 on that header only, and checks `schedule_epoch_low`.
- The header carries `schedule_epoch_low`, `frame_counter_start`, frame symbol count, pilot interval, and modulation.
- Once locked, frame boundaries are derived from decoded symbol count. Pilots and confident decisions update the equalizer and carrier loop; unreliable decisions freeze adaptation. Pilots also monitor lock.
- Sustained pilot disagreement reports lock loss. With recurring markers configured, the receiver waits for a later marker and rebuilds confidence before resuming payload delivery.

For simulated polar-channel validation, the fiber control interface also exposes
an optional compact FEC-protected header, recurring synchronization/training
markers, half-symbol-spaced equalization and RLS tap reselection. Recurring
markers preserve absolute payload positions, letting the receiver resume the
continuous coded/encrypted stream after a gap. Their airtime is measured in the
simulation, including the cost on channels that were already stable. See
[TESTING.md](TESTING.md#simulated-channel-recovery-campaign) for the declared
profiles, independent seeds and long-duration campaign.

The RF symbol payload has no separate block CRC; message integrity is handled at the message-stream layer so messages can still be emitted with delimiter-level latency.

Channel regression tests cover noise, fading, phase rotation, delayed echoes,
and reacquisition. Run `ctest --test-dir build -L channel --output-on-failure`;
see [test conditions and current receiver limits](tests/README.md).

Carrier correction and adaptive equalization are enabled by default. The default
equalizer has three feedforward and four feedback taps with no decision delay.
Longer echoes can use longer spans, training and an explicit decision delay.
Optional recursive least-squares tracking adjusts equalizer coefficients and
phase without estimating carrier frequency. Gardner timing recovery tracks sample
clock mismatch. The acceptance matrix enables these features with carrier
correction off. Both ends receive matching tap counts, delay and training settings
through the fiber gRPC control link; these changes add no RF negotiation messages.

## Convolutional/Viterbi Stream

`include/goblin_cannon/message_stream.hpp` adds the direct real-time message pipeline:

```text
SpscRingBuffer<DelimitedMessage>
  -> MessageStreamFramer
     (AES-256-GCM authenticated record, COBS framing)
  -> punctured convolutional encoder
  -> QAM/RF stream
  -> soft-decision Viterbi decoder
  -> MessageStreamDeframer (verify tag, reject replays, then deliver)
  -> SpscRingBuffer<DelimitedMessage>
```

The default code is `K=7`, generators `171` and `133` octal, base rate `1/2`.
`PuncturedConvolutionalCodeConfig` also provides `rate_2_3()` and `rate_3_4()` presets, and callers can supply other constraint lengths, generators, puncture patterns, and confidence thresholds.
The 32-byte AES-256-GCM key and nonzero key ID are supplied over the fiber control plane.

With `SyncTimestampConfig` enabled, the transmitter prefixes the stream with an 8-byte native Intel IEEE double containing seconds since the Unix epoch. The receiver checks clock skew after FEC decoding, and every message authenticates those exact bytes as additional associated data. The timestamp is never used to construct a nonce. Deterministic simulated-channel tests disable this optional clock-skew check.

Application messages retain their bank byte (`0` or `1`) and body bytes in `[2,255]`. The production wire format is a COBS-delimited AES-256-GCM record. Its 25-byte clear, authenticated header contains version, bank, sequencing flag, key ID, 64-bit epoch, 32-bit frame sequence, 32-bit application sequence, and 16-bit body length, all integers in network byte order. The body is encrypted and followed by a 16-byte tag. Idle zero delimiters are ignored. Damaged or unverified records never reach a sink; tag/framing authentication failures increment `authentication_failures` and emit a gap, without causing RF lock loss.

Every production record has mandatory nonce/replay sequencing. Optional application sequencing suppresses duplicate and older per-key serials and handles application-counter wraparound. RF reacquisition retains both high-water marks. The frame counter never wraps: exhaustion stops transmission until a fresh epoch is reserved. The standalone default CRC framer and AES-128-CTR helpers remain for legacy codec fixtures; the realtime classes always enable GCM and have no downgrade path. RF-header CRCs remain solely for acquisition/framing screening; they do not authenticate messages.

The opt-in disturbed-channel profile uses a **13-byte authenticated header**:
bank, key ID, mandatory frame sequence and application sequence. Epoch, format,
sequencing mode and length remain authenticated context, with the epoch and
format selected over fiber. The tag stays 16 bytes. It also enables warm
equalizer recovery and elapsed-symbol uncertainty prediction. See the
[current simulated channel report](results/disturbed-recovery/SUMMARY.md) and
[configuration/testing instructions](TESTING.md#current-disturbed-simulated-channel-recovery).

See [AEAD deployment and nonce lifecycle](AEAD.md) before starting a transmitter. This is a wire-format and control-API break: upgrade both ends together. Authenticated key IDs provide the basis for a future two-key receiver, but coordinated mid-stream rotation and old-key retirement remain unimplemented.

The transmitter also publishes the original application message sequence over every active `ReceiverSession` gRPC stream. Canonical messages are batched up to 128 payloads; if a batch does not fill, it is flushed within 100 ms. Receivers use this stream for accounting. A decoded message missing from that stream after the configured timeout emits a distinct bad-message UDP packet; this accounting check is separate from mandatory GCM verification before delivery.

The transmitter reads from its input ring continuously and pads with zero delimiters when the input ring is empty. It does not wait to fill a block; the only steady-state buffering in the message layer is the delimiter rule that a completed message is emitted after the following delimiter is decoded.

For client intake, `BidMessageTransmitIntake` accepts already-encoded application messages plus a bid price. One auction winner remains replaceable until the framer claims it for serialization; that is when transmission is logged and a client fee is reserved. A newer unsent market value replaces an older value on the same key even when its bid is lower. Across keys, bid per reserved wire byte wins, including the authenticated header, tag and conservative COBS length bound, with newest winning ties. Displaced and losing candidates are rejected. Old bids receive no age boost; strict cross-key priority can still starve lower bids. The auction holds at most one waiting candidate, and cannot retract bits already serialized.

`Clients` is a compile-time constant currently set to `20`. Market-price symbols occupy `[2, 256 - Clients - 1]`; the top `Clients` symbols are per-client symbols. With `Clients=20`, client symbols are `236..255`, and a client id maps to `236 + client_id`.

`ClientUdpMessageHandler` handles transmitter-side UDP intake. The UDP payload is `4` bytes of bid price in 0.01 USD, big-endian, followed by a 2-9 byte encoded message: first byte `0` or `1`, remaining bytes not `0` or `1`. The handler matches source IP to a configured client id, rewrites the message symbol byte to `client_id_to_symbol(client_id)`, and submits the encoded string to the bounded bid intake. Sent, insufficient-bid, and invalid-format statuses are logged and sent back to the source over the normal kernel UDP stack. Unauthorized-source packets are logged without sending a UDP response. Ingress config supports `backend=kernel_udp` or `backend=dpdk`; DPDK selection currently parses and validates config and fails fast unless the library is built with DPDK support.

## Integer Messages

`include/goblin_cannon/integer_codec.hpp` defines the current structured message body:

```text
byte 0      bank delimiter: 0 or 1
byte 1      symbol: market range [2, 256 - Clients - 1], or top Clients range for client messages
bytes 2..N  signed int64, zigzag encoded, then base-254 varuint encoded with bytes [2,255]
```

The integer codec uses canonical little-endian base-254 digits offset by `2`, so zero encodes as `{2}` and no encoded integer byte can collide with a stream delimiter. Decoders reject empty integers, delimiter bytes inside the integer, non-canonical high-zero encodings, and `uint64_t` overflow.

## Receiver Control

`include/goblin_cannon/control_server.hpp` adds a thread-owning gRPC control server. The installed proto lives at `share/goblin_cannon/proto/goblin_cannon/control/v1/receiver_control.proto`.

The service accepts:

- `UpdateEncryptionKey`: 32-byte `aes256_key` and nonzero `key_id`. The next restart uses the latest key. The removed 16-byte field is reserved and rejected.
- `ReceiverControl.GetMetrics`: cumulative authentication failures, replay rejections, RF lock losses, validated headers and gaps. Authentication failures are counted separately from RF lock losses.
- `Restart`: receiver rebuild parameters, including modulation, bandwidth, center frequency for the later SDR layer, RF acquisition/training/pilot sequences, timestamp policy, and convolutional FEC settings.
- `UpdateBank`: one bank id (`0` or `1`) plus exactly `254 - Clients` `uint64` prices in configured instrument units. Receiver bank caches are optional so a stale control link can clear them and stop UDP forwarding until fresh bank data arrives. Symbol byte `2` maps to index `0`, and the top `Clients` symbols are reserved for client messages rather than bank prices.
- `Permissions`: exactly 32 bytes containing 254 permission bits. Bit index `0` maps to symbol byte `2`, bit index `253` maps to symbol byte `255`, and the two unused high bits in the final byte are ignored. The radio receiver binary defaults to all market symbols plus its own client-specific symbol `236 + client_id`.

`ControlledRealtimeReceiver` consumes pending restart requests from `ReceiverControlState` before processing samples, drops the old receiver object, and constructs a fresh `RealtimeReceiver` with the new configuration.
The default `ControlledRealtimeReceiver(output_ring)` constructor starts off and stays silent until a restart arrives.

The proto also defines `TransmitterControl` with matching `UpdateEncryptionKey`, `Restart`, and `UpdateBank` calls plus `UseBank`, `BankSwitch`, and a bidirectional `ReceiverSession` stream. The receiver opens that stream to the transmitter, sends its `client_id` first, and both sides heartbeat once per second. If the receiver misses transmitter heartbeats for 3 seconds it clears bank caches and stops quote UDP output. If the transmitter misses a receiver heartbeat for 3 seconds it rejects that receiver's client-specific radio messages. `BankSwitch` toggles to the other bank after the live receiver streams have been sent the target bank cache; embedders can provide `TransmitterControlServerConfig::bank_price_provider` so the switch RPC refreshes the next bank inside the transmitter process before delivery.
The stream also carries receiver-originated log events: decoded client wire messages and signal-quality events. Client wire messages are logged with receiver timestamp, client id, and the full radio wire payload as hex.
`UseBank` takes `0` or `1` and makes the transmitter use that delimiter for outgoing messages and idle padding. The default `ControlledRealtimeTransmitter(input_ring)` constructor also starts off until a restart arrives.

## JSONL Logging

The transmitter drains its bounded log ring to a common JSONL file. Logged events include UDP ingress packets, UDP auction decisions, direct transmitter enqueue events, receiver-reported client messages, and receiver signal events. Bids are logged in cents; market-data enqueue messages use a default shadow bid of `100` cents when no bid is supplied. Client UDP input is `bank delimiter + 1..8 body bytes`; the internal radio wire payload is `bank delimiter + client symbol + body bytes`, and logs keep the wire payload as `payload_hex`.

`config/client_latencies.conf` maps `client_id` to expected receiver-reporting latency in nanoseconds. The local demo defaults each client to `5000000` ns. The sender accepts `--latency-config path` and writes `expected_latency_ns` plus observed receiver-to-transmitter log latency for receiver-reported events.

`config/client_budgets.conf` maps `client_id` to beginning-of-day budgets in pennies/cents. On startup the transmitter loads that file, then replays the JSONL log when it already exists to reconstruct remaining budgets and outstanding bids. A client bid that exceeds its remaining budget is blocked, logged as `budget_exhausted`, and receives an insufficient-budget UDP status. Sent client messages decrement remaining budget and enter an outstanding map keyed by internal radio wire payload and send timestamp. Receiver-reported delivery messages remove the closest outstanding entry after subtracting configured client latency; entries older than one second are scanned every 100 ms, removed, refunded, and logged as `budget_refund`.

`config/client_udp_ingress.conf` is an optional transmitter UDP ingress config. Pass `--client-udp-config config/client_udp_ingress.conf` to `goblin_cannon_radio_sender` to bind the kernel UDP intake path.

## Demo Market Data

`config/demo_instruments.toml` defines the demo instrument universe and the integer price unit for each symbol. Stocks use half-penny units via `minimum_price_increment = 1/200`; currency pairs use pipettes with `1/100000` for non-JPY pairs and `1/1000` for JPY pairs; futures use their configured contract tick size; crypto pairs use the configured quote-currency increment. All conversion math in the Python tools is derived from that file.

The demo config currently assigns stock radio symbols `2..18`, front futures `19..32`, currencies `33..40`, and crypto pairs `41..55`; the remaining market symbols are left available until the top `Clients` range reserved for per-client messages.

`MASSIVE_KEY` supplies the Massive API key for the demo tools:

```sh
export MASSIVE_KEY=...
scripts/update_demo_bank.py 0
scripts/stream_massive_quotes.py 0
```

`update_demo_bank.py` fetches current quote midpoints for every configured stock, front future, currency, and crypto pair, converts them into configured integer units, updates transmitter bank state through gRPC, then asks the transmitter to run `BankSwitch`; receivers learn the new bank cache over `ReceiverSession`. For currencies and crypto, both bank seeding and live streaming require bid/ask midpoint data. `stream_massive_quotes.py` subscribes to Massive stock, futures, forex, and crypto quote websockets and writes market-data deltas into a small shared-memory SPSC ring, not the gRPC control plane. The sender drains that ring into the same one-winner bid auction used by client UDP messages, so market updates that cannot occupy the next radio slot compete as short-lived candidates and lower bids are discarded. It waits until the active bank has nonzero bases before sending quote deltas.

Market-data shadow bids are computed from `[shadow_bid]` and per-instrument `weight` in `config/demo_instruments.toml`:

```text
shadow = K * W[i] * (abs(log(P_now) - log(P_last_sent))
         + H * abs(log(P_now) - log(P_prev)) / dt_ms) / billable_bytes
```

`billable_bytes` matches the auction's reserved AEAD wire length: header, encrypted body, tag and COBS framing bound. When `P_last_sent` or `P_prev` is not known, the bridge uses `K` as the bid. Public market symbols are not charged against client budgets; their shadow bids only decide which candidate uses the next radio slot.

For local hand testing, build the examples and start a loopback receiver/transmitter pair:

```sh
cmake --build build --target goblin_cannon_local_node
scripts/start_local_loopback.py
```

The loopback node exposes receiver gRPC on `127.0.0.1:50051`, transmitter gRPC on `127.0.0.1:50052`, and emits decoded quote UDP packets to `127.0.0.1:9001` by default.

## Quote UDP Output

`include/goblin_cannon/quote_udp.hpp` provides `QuotePacketEmitter`, which can be attached to a receiver as a decoded-message observer. For each decoded integer message, it reads the message bank and symbol, looks up the current base price in `ReceiverControlState`, adds the zigzag-decoded delta, and emits a 9-byte packet:

```text
byte 0      symbol byte from the radio message
bytes 1..8  uint64 reconstructed price in configured instrument units, big-endian
```

The UDP output config is a simple `key=value` file. `backend=kernel_udp` sends through the normal kernel UDP stack. `backend=dpdk` parses DPDK/EAL settings and fails fast unless the library is built with DPDK support.

Before emitting, `QuotePacketEmitter` checks the receiver permission mask. A decoded symbol that is not allowed by the latest `Permissions` update is dropped and is not forwarded to UDP.

Market-bank switching is also gated by bank freshness. The receiver starts warm with no active market bank; until it has a bank update that matches the incoming radio bank delimiter, market UDP output is suppressed. Once a market bank is active, switching to the other market bank requires that the target bank has received a fresh `UpdateBank` since the last time that bank was active. If the radio switches before that slow-path update arrives, those market messages are dropped, but the receiver stays locked and later resumes forwarding once the missing bank update arrives. Client-symbol messages in the top `Clients` range bypass this bank freshness gate.

```text
backend=kernel_udp
destination_ip=127.0.0.1
destination_port=9001
source_ip=0.0.0.0
source_port=0
```

DPDK configs use the same destination/source fields plus keys such as `dpdk.eal_arg`, `dpdk.port_id`, `dpdk.queue_id`, `dpdk.source_mac`, and `dpdk.destination_mac`.

At 48 kHz sample rate, 24 kHz configured bandwidth, and derived 19.2 ksym/s, the continuous coded-airtime estimate is:

```text
rate 1/2, 64QAM, 1 encoded byte:   16 coded bits,  3 QAM symbols, 0.312 ms encode+decode
rate 1/2, 64QAM, 3 encoded bytes:  48 coded bits,  8 QAM symbols, 0.833 ms encode+decode
rate 1/2, 64QAM, 4 encoded bytes:  64 coded bits, 11 QAM symbols, 1.146 ms encode+decode
rate 1/2, 64QAM, 5 encoded bytes:  80 coded bits, 14 QAM symbols, 1.458 ms encode+decode
rate 1/2, 64QAM, 8-byte timestamp: 128 coded bits, 22 QAM symbols, 2.292 ms encode+decode
rate 1/2, 1024QAM, 5 encoded bytes:  80 coded bits,  8 QAM symbols, 0.833 ms encode+decode
rate 1/2, 1024QAM, 8-byte timestamp: 128 coded bits, 13 QAM symbols, 1.354 ms encode+decode
rate 1/2, 16QAM, 4 encoded bytes:  64 coded bits, 16 QAM symbols, 1.667 ms encode+decode
rate 1/2, 16QAM, 5 encoded bytes:  80 coded bits, 20 QAM symbols, 2.083 ms encode+decode
rate 1/2, 16QAM, 8-byte timestamp: 128 coded bits, 32 QAM symbols, 3.333 ms encode+decode
rate 2/3, 64QAM, 5 encoded bytes:  60 coded bits, 10 QAM symbols, 1.042 ms encode+decode
rate 3/4, 64QAM, 5 encoded bytes:  54 coded bits,  9 QAM symbols, 0.938 ms encode+decode
rate 2/3, 1024QAM, 5 encoded bytes:  60 coded bits,  6 QAM symbols, 0.625 ms encode+decode
rate 3/4, 1024QAM, 5 encoded bytes:  54 coded bits,  6 QAM symbols, 0.625 ms encode+decode
```

These numbers are two times coded airtime and exclude the first epoch's RF acquisition/training/header overhead. Periodic pilots add small steady-state overhead according to `pilot_interval_symbols`. Because the deframer must see the following delimiter before it emits a message, a 3-byte message is delivered after 4 encoded bytes, and a 4-byte message is delivered after 5 encoded bytes.

For thread separation, `include/goblin_cannon/ring_buffer.hpp` provides `SpscRingBuffer<T>`. The primary real-time path is:

```text
producer thread -> SpscRingBuffer<DelimitedMessage> -> RealtimeTransmitter -> RF device
RF device -> RealtimeReceiver -> SpscRingBuffer<DelimitedMessage> -> consumer thread
```

The ring is bounded and non-blocking; callers decide whether to spin, yield, drop, or count overruns.

## Bandwidth

`ModemConfig::bandwidth_hz` controls occupied complex-baseband bandwidth. If `symbol_rate_hz` is not set, the library derives WBHF-style symbol rate as:

```text
symbol_rate_hz = bandwidth_hz * 0.8
```

For non-standard SDR links, set `symbol_rate_hz` explicitly.

## SDR and `/dev/audio`

Use the raw IQ interfaces for files, device nodes, or pipes:

```cpp
goblin_cannon::FileIqSink sink("/dev/audio", goblin_cannon::SampleFormat::s16_stereo_iq);
sink.write(samples);
sink.flush();
```

For UHD, SoapySDR, GNU Radio, JACK, ALSA, or custom DMA paths, use `CallbackIqSink` and `CallbackIqSource` to bind the modem to the transport without making the modem depend on that SDK.

The example radio processes expose the same path-based IQ adapters:

```sh
cmake --build build --target goblin_cannon_radio_sender goblin_cannon_radio_receiver

build/goblin_cannon_radio_receiver \
  --receiver 127.0.0.1:50051 \
  --iq-input /dev/audio \
  --quote-destination-ip 127.0.0.1 \
  --quote-destination-port 9001 \
  --sample-format s16_stereo_iq

build/goblin_cannon_radio_sender \
  --transmitter 127.0.0.1:50052 \
  --iq-output /dev/audio \
  --sample-format s16_stereo_iq
```

For local FIFO testing, `scripts/start_pipe_radios.py` creates a named pipe, starts the sender and receiver, then calls `scripts/configure_local_radios.py` to push matching control state over gRPC. The default radio condition is 64QAM at 48 kHz sample rate, 48 kHz configured bandwidth, an explicit 24 ksym/s symbol rate to keep the modem at 2 samples/symbol, and 8x receiver oversampling as a CPU/headroom stress setting. By default the configurator updates the AES key on both processes, sets receiver permissions to market symbols plus `client_id`, seeds bank `0` on the sender, lets the receiver learn the bank over `ReceiverSession`, sets the sender to use bank `0`, and sends matching restart parameters. After configuration, the launcher starts `scripts/stream_massive_quotes.py 0` so Massive websocket midpoints are encoded into `/dev/shm/goblin_cannon_market_data_ring` and consumed by the transmitter:

```sh
scripts/start_pipe_radios.py --quote-destination-port 9001 --enqueue-test-message
```

The default FIFO is `/tmp/goblin_cannon_iq.pipe`, the default quote UDP target is `127.0.0.1:9001`, the default market shared-memory ring is `/dev/shm/goblin_cannon_market_data_ring` with 256 burst-handoff slots, and the default sample format is interleaved little-endian signed 16-bit IQ (`sc16_iq`). The FIFO launcher uses direct POSIX file-descriptor I/O, 64-sample chunks, a 4096-byte pipe-capacity request, and sender pacing at the configured 48 kHz sample rate so the pipe cannot hide seconds of stale simulated IQ. Set `MASSIVE_KEY` before running the full demo, or pass `--no-market-stream` to run only the pipe radios. The sender drains its bounded JSONL log ring to `/tmp/goblin_cannon_transmitter.log` by default and reads client latency and budget expectations from `config/client_latencies.conf` and `config/client_budgets.conf`.

For an end-to-end software stack latency measurement, run:

```sh
MASSIVE_KEY=... scripts/benchmark_stack_latency.py --messages 16
```

The benchmark starts the same FIFO radio pair with QAM64, 48 kHz bandwidth, and 8x receiver oversampling, waits for Massive-backed market shared-memory flow, sends tagged client UDP messages into the transmitter, tails the JSONL log for receiver-reported client wire messages, and prints latency percentiles. The JSONL stream includes `udp_ingress`, `udp_decision`, `transmitter_framer`, `receiver_client_message`, and periodic `iq_transport`/`rx_iq` telemetry so the benchmark can split enqueue, framer, radio, and report latency. Use `--no-market-stream` for a local-only smoke benchmark that skips the Massive websocket requirement.

For a market-data bid-loss measurement, run:

```sh
MASSIVE_KEY=... scripts/benchmark_market_bid_loss.py --duration-seconds 60
```

That benchmark connects the FIFO sender/receiver pair, starts Massive websocket flow through the shared-memory market ring, tails transmitter JSONL decisions, and reports the fraction of market candidates rejected by the next-slot bid auction.

## Scope

This is a baseband modem and framed stream layer with adaptive equalization and sample-clock recovery. The acceptance profile leaves carrier-frequency correction to the radio. It assumes matching protocol parameters and timing close enough for acquisition. The equalizer has finite convergence and tracking limits. Simulated channel results establish specific observations; polar-link availability still needs measured channel statistics. Interleaving and retransmission are not part of the low-latency RF path.
