# Goblin Cannon simulated channel tests

These tests exercise the production C++ library in simulation. No result is a
radio-equipment measurement. The original audit preserved production behavior;
Adam subsequently authorized fixes #1–5. Follow-up results retain their own
source hashes and are stored separately from the original audit. See the
[continuous recovery campaign](results/recovery-improvements/REPORT.md) for the
protected header, recurring markers, tap reselection, half-symbol input and
three-seed production-message measurements. See the
[fixes #2–5 validation](results/fixes-2-5/FIXES.md) for tracking, equalization,
latency, freshness and receiver results, and the earlier
[24 kHz fix validation](results/24khz-header-fix/FIX.md).

The [HTML report](html/index.html) presents the measured processing budget,
case statuses, and recorded polar configurations. Its
[publication guide](html/README.md) explains how to regenerate it from the
saved result JSON without rerunning a channel simulation.

## Build the simulated channel harness

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DGOBLIN_CANNON_TEST_REQUIRE_AVX512=ON
cmake --build build -j 4
```

Use an x86-64 host; `avx10` provides AVX-512 validation and `naamah` provides
the quiet-host AVX2 latency comparison. Required packages
on Ubuntu are CMake, Ninja, a C++23 compiler, `libgrpc++-dev`,
`protobuf-compiler-grpc`, `protobuf-compiler`, `libprotobuf-dev`, `libssl-dev`,
and Python 3.11+. The matrix runner uses only Python's standard library.

## Run a simulated channel tier

```sh
python3 tests/simulated_channel/run.py --tier quick --jobs 4
python3 tests/simulated_channel/run.py --tier full --jobs 4
# Manual only: this preserves one continuous, paced four-hour stream.
python3 tests/simulated_channel/run.py --tier soak --jobs 1
```

Every matrix case has exactly one `quick`, `full`, or `soak` tier and one
`assert` or `characterize` kind. Select a group with `--group A4`; select a case
with `--case NAME`; inspect the complete parameter manifest with `--list`.
`--probe PATH`, `--results PATH`, and `--seed INTEGER` are explicit overrides.
AVX-512 dispatch is required unless `--allow-non-avx512` is supplied and recorded.

Tier budgets are 120 seconds, 1,800 seconds, and 4–12 hours. Long quick cases
still process every sample in their specified ten-minute simulated duration.
The runner reports budget overruns; it never reduces a duration or grid.
A1 uses **10 simulated seconds per point**, all ten supported constellations,
three implemented FEC rates, both bandwidths, all nine presets, and 0–30 dB SNR
in 2 dB steps. These are screening curves. They do not establish F.1487's much
longer statistical-duration operating limits; C1 marks such limits unestablished.

When using a source copy without `.git`, pass `--git-commit COMMIT` and
`--source-digest SHA256` from the originating workspace. Obtain the latter with:

```sh
PYTHONPATH=tests/simulated_channel python3 -c 'from run import source_digest; print(source_digest())'
```

## Run a quiet-host simulated channel latency check

On `naamah`, configure with `-DGOBLIN_CANNON_TEST_REQUIRE_AVX512=OFF`; its
Threadripper PRO 5995WX supports AVX2. After building and running CTest, run B5
with one worker so validation jobs do not compete during wall-clock measurement:

```sh
python3 tests/simulated_channel/run.py --tier quick --group B5 --profile recovery --jobs 1 \
  --allow-non-avx512 --results results/recovery-improvements/naamah-latency
python3 tests/simulated_channel/run.py --tier full --group B5 --profile recovery --jobs 1 \
  --allow-non-avx512 --results results/recovery-improvements/naamah-latency
```

Supply the revision/source-digest arguments above when using a source copy.
Use a separate output directory for each repetition to retain host observations.
The [recovery-profile naamah comparison](results/recovery-improvements/naamah-latency/COMPARISON.md)
preserves all twelve configurations, full parameters, host metadata and stage
timings alongside the unchanged `avx10` baseline. The
[earlier comparison](results/naamah/COMPARISON.md) retains three repetitions of
the original profile. The current B5 assertion applies **2.1 ms to added processing and
buffering**, as Adam specified. It pairs each delivered message with a
one-sample production-stack reference replaying the messages selected by the
auction at their original source creation times. Subtraction happens per message
before percentiles; unmatched messages fail the harness. Total source-to-sink
latency, intrinsic reference, serialization estimates, RRC/equalizer/FEC residence,
and host stage-call durations are reported separately. Startup stays in total
latency and the intrinsic reference. Source overload is retained.
The full-tier B5 selection uses the longer equalizer spans from the
high-latitude quiet configuration, through a null simulated channel. Both
selections retain the original twelve-second duration. Integral-sample source
deadlines are calculated from the event index; a separate assertion rejects
source events that slip across their aligned audio tick.

## Read simulated channel results

- `results/<test_name>/<seed>.json`: full configuration, revision/source hash,
  observations, metric definitions, assertions, and open thresholds.
- `results/SUMMARY.md`: group tables, every expected failure, open thresholds,
  and limitations. Group CSVs retain the full parameters and metrics for plotting.
- `results/EXECUTION.json`: **non-canonical** host runtime observations. These
  vary with scheduling and are not included in seeded byte-equality checks.
  `EXECUTION-quick.json` and `EXECUTION-full.json` preserve complete tier timings;
  selected reruns have separate files and cannot erase a budget overrun.
- Soak `.host.json` files similarly hold non-canonical resident-memory samples
  with the full test parameters. Per-hour deterministic latency/counter metrics
  remain in the canonical result. The soak bounds are still `THRESHOLD_TBD`.
- B5 `.host.json` files hold measured source-to-sink wall latency and stage call
  timings, including the real auction, TX/RX framing/FEC/crypto/modem and paced
  simulated audio buffering. OS scheduling is included. Stage durations are per
  call, not an additive decomposition of each message's latency. No physical
  audio device or network socket is represented by this loopback.

`characterize` never gates on a BER target. Assertions use only stated brief
requirements; missing margins stay `THRESHOLD_TBD`, as confirmed by Adam.
Measurements and proposed values remain available for later review; proposed
values are not enforced. Reviewed production defects
are listed by exact case/assertion in `expected_failures.json`; tests still run.
A new failure, harness error, or unexpected pass fails the runner. Unsupported
conditional features and missing inputs are `unavailable`, never passes.

As confirmed by Adam, the new matrix disables the existing combined
carrier/phase correction switch.
The matrix enables sample-clock recovery and sparse recursive equalization
(RLS) with a phase-only complex coefficient; no frequency tracker is enabled.
Its default span is three feedforward and four feedback taps. A2 additionally
compares short, causal and delayed spans on all three high-latitude presets,
both bandwidths and QPSK/16-QAM/64-QAM. All spans, training lengths and decision
delays are explicit in the manifests; the original grids are preserved.
BER is conditional on observed bits; missing bits
and frames are reported separately. Frame survival includes missing frames.
Message latency uses creation-to-delivery sample-clock time including startup
and audio buffering. B5 additionally reports non-canonical host measurements.
Exact STAC comparability is not claimed. See the [audit questions](tests/simulated_channel/QUESTIONS.md).

`acquisition_time_s` follows the existing receiver's `acquisition_found` event:
first preamble detection. A valid header is separately required by C2's assertion;
detecting a preamble alone does not pass that test. `reacquisition_time_s` uses the
first validated header after signal return. Acquisition deadlines remain open.

D1 keeps the isolated auction test and also runs a null-channel overload stream
through the actual auction, framer, FEC, crypto, modem and sink. The latter offers
wire bytes (including CRC and sequence metadata) at each multiple of the declared steady payload bit
rate. Results retain newest-only per-key latency and ten chronological windows.
D3's contention and flood checks isolate the auction so RF acquisition does not
hide starvation. Newer same-key market bids replace the standing winner even
when their bid is lower; higher bids from other keys compete until the framer
claims a message. Fees are reserved at that claim. Old bids receive no age
boost. Unconditional starvation freedom during an endless higher-bid flood
remains incompatible with this priority policy, and its test remains an xfail.
No unapproved cross-key age-decay interval is imposed.
D2 preserves 0–30 dB grids on `mid_lat_moderate` and `ccir_good`, then performs
eight refinements of observed SNR crossing brackets. Every trial lasts 60
simulated seconds. Requested and measured survival fractions are kept separate.

## Extend the simulated channel

`tests/channel_simulator.hpp` is the single simulator shared with the original
regression tests. Its order is channel → interferers → impulsive noise → dropout
→ AGC → clipping → band-limiting → sample-clock mismatch → residual offset/drift
→ audio delivery jitter. Each stage is controlled by explicit parameters.

Add a stage's configuration/state to that header, parse it in the test-only C++
probe, and add its defaults and metadata to `catalog.py`. Keep state and PRNG
draws independent of input chunk boundaries. Extend E1's repeated/chunked checks.
Declare its location in the order; do not add a second independent simulator.

For a test, add a `Case` to `catalog.py` with its kind, tier, parameters, and a
stated assertion or characterization. Put new open margins in `OPEN_THRESHOLDS`.
The test-only adapters call public production APIs. Keep fixes in the library
and keep test inputs/acceptance criteria independent of those fixes. Mark a new
defect xfail with its exact reason and retain its observations for review.

## Recorded-noise simulated channel cases

E4 is unavailable until recordings are supplied. `--recordings manifest.json`
accepts a list of entries with `path`, `sha256`, `sample_rate_hz`, `format`,
`frequency_hz`, `utc`, `receiver_location`, `source_url`, and `permission`.
The supported format is `fc32_iq_le` at 48 ksample/s. Conversion must be explicit
and documented; the runner never loops a short capture or fabricates provenance.

## Other simulated channel checks

```sh
python3 -m unittest discover -s tests/simulated_channel -p 'test_*.py'
ctest --test-dir build --output-on-failure
```

For CI, configure `-DGOBLIN_CANNON_RUN_SIMULATED_CHANNEL_QUICK=ON`, then run
`ctest --test-dir build -L quick --output-on-failure`. This includes the complete
matrix, original regressions, and Python harness checks. Source copies without
`.git` also need `-DGOBLIN_CANNON_TEST_GIT_COMMIT=COMMIT`. The current `avx10`
quick matrix exceeds the requested two-minute budget; enabling CI does not hide
that finding. It remains an explicit, opt-in CTest entry while that is unresolved.

The older ten CTest entries remain regression checks for their original
configuration, including carrier correction enabled. Their pass does not satisfy
the new brief's radio/software boundary; the new matrix records that distinction.

## Configure the simulated channel fixes

### Simulated channel recovery campaign

The optional recovery profile adds a protected 16-byte header, recurring
acquisition/training blocks, half-symbol-spaced equalization and periodic sparse
RLS tap reselection. Both endpoints configure these over fiber. No mode changes
or frequency tracker are carried in the waveform. Legacy wire settings remain
available for A/B measurements.

```sh
# Acceptance matrix with the new profile (B5 separately on a quiet host).
python3 tests/simulated_channel/run.py --tier quick --profile recovery --exclude-group B5 --results results/recovery-improvements
python3 tests/simulated_channel/run.py --tier full --profile recovery --campaign matrix --exclude-group B5 --results results/recovery-improvements

# Each change separately, raw RF and production post-FEC message measurements.
python3 tests/simulated_channel/run.py --tier full --campaign polar_screen --results results/recovery-improvements

# Full-duration independent replicates: 6000 / 300 / 100 simulated seconds
# for high-latitude quiet / moderate / disturbed, at both bandwidths and all
# three primary modulations. No duration is reduced for a runtime budget.
python3 tests/simulated_channel/run.py --tier full --campaign polar_long --seeds 7446529 7446530 7446531 --results results/recovery-improvements
```

The long campaign meets both F.1487 Annex 3 duration terms **for the declared
BER 1e-3 planning target** and records them per result. It measures application
delivery, not certified BER performance or a BER 1e-5 operating envelope. The
24 kHz channel model remains a bandwidth extrapolation. Long runs retain exact
sample-clock histograms of every delivery instead of per-message JSON vectors;
the 6000-second observations are not decimated. Seeds are separate files.

Results include first lock loss, completed RF recovery intervals, any unfinished
RF outage, message delivery relative to both created and framed messages,
freshness and delivery-silence intervals. Silence includes startup and the
right-censored end of a run; no new outage acceptance threshold is assumed.
An RF probe budgets its payload using the complete waveform duty cycle, including
marker airtime, then completes that finite payload. Partial-segment startup and
pulse tails are included in its recorded actual duration. A message probe runs
for the declared duration. Audio durations are never reduced to meet a runtime budget.

Set `--compact-header --recovery-interval-frames 16
--fractionally-spaced-equalization --equalizer-reselect-interval 256` in
`scripts/configure_local_radios.py`, together with `--no-carrier-correction`
and the existing adaptive/recursive equalization settings. The tap count is a
symbol span: half-symbol sampling uses `2*N-1` feedforward coefficients with the
same decision delay. More frequent markers spend more airtime on recovery and
can reduce goodput on an already stable channel. The A/B campaign records that
cost instead of assuming every option improves every channel.
To reproduce a particular measurement, also match its bandwidth, symbol rate,
frame size, pilot cadence, training length and equalizer span from the saved
parameters; the four recovery flags alone do not select those values.

Recovery seeks the existing continuous CTR keystream and aligns the punctured
Viterbi decoder at the next source-byte boundary; it never resets the transmitter
counter to zero. Uncertain recovery bytes and partial messages are discarded
with downstream gaps. With timestamp validation enabled, the initial session
timestamp must first have been validated; a later CRC-protected header does not
bypass that check. Mid-stream joining in the simulation uses its explicitly
declared disabled timestamp check. AEAD and restart nonce safety remain separate
open defects.

The two endpoints must receive matching settings over the fiber gRPC control
path. `RestartRequest` and `scripts/configure_local_radios.py` expose
`sample_clock_recovery`, `recursive_equalization`, `equalizer_delay_symbols`,
feedforward/feedback tap counts, training length and `message_sequence_numbers`.
Use carrier correction off and adaptive/recursive equalization on for this
acceptance boundary. The library retains the legacy NLMS option. Equalizer
lookahead adds the declared number of symbols of modem residence.

The default realtime message format adds five base-254 bytes for a 32-bit serial
number covered by the existing CRC. Both endpoints must enable this format
together; `message_sequence_numbers=false` selects the legacy format. Per-key
serial comparison suppresses duplicates and stale arrivals across audio resets
and handles wraparound. A new receiver/session clears the high-water marks.
This sequencing does not provide cryptographic authentication or restart-safe
replay protection; the separate AES-CTR/AEAD/nonce findings remain open.

Audio integrations should call `push_audio_block(samples, first_sample, valid)`
on the realtime or controlled receiver. The monotonically increasing device
sample position detects lost/repeated buffers; `valid=false` reports an underrun.
For delivery jitter, `push_timed_audio_block` additionally accepts the arrival
position in the same device sample clock and the configured playout slack. Late
blocks produce a gap even when their sample positions are contiguous.
`DelimitedMessageObserver::on_message_gap` and `RealtimeReceiveResult::gap_events`
expose discontinuities, FEC uncertainty and malformed/checksum failures. The raw
`push_samples` API cannot infer device events for which no metadata is supplied.

The source auction coalesces unsent market updates. Once serialization begins,
newer source data cannot retract bits already in flight. Receiver suppression
uses newer **received** sequence numbers; it cannot infer unseen source updates.
