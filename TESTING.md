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
A1 uses **10 simulated seconds per point**, the original ten constellations,
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

### BCH, diversity and cadence simulated channel comparison

The [refinement report](results/refinement/REPORT.md) compares coherent
QPSK/8-PSK+BCH, configurable BPSK frequency diversity, and independent changes
to pilot spacing and full retraining. The new controls are opt-in; all
configuration travels over fiber/gRPC.

```sh
python3 tests/simulated_channel/run.py --tier quick --campaign refinement_quick --jobs 4 --results results/refinement
python3 tests/simulated_channel/run.py --tier full --campaign refinement_snr --jobs 8 --results results/refinement
python3 tests/simulated_channel/run.py --tier full --campaign refinement_screen --seeds 7446529 7446530 7446531 --jobs 8 --results results/refinement
python3 tests/simulated_channel/run.py --tier full --campaign refinement_delay --seeds 7446529 7446530 7446531 --jobs 8 --results results/refinement
python3 tests/simulated_channel/run.py --tier full --campaign refinement_followup --seeds 7446529 7446530 7446531 --jobs 8 --results results/refinement
# On naamah, after the regression suite completes, run without concurrent tests:
python3 tests/simulated_channel/run.py --tier full --campaign refinement_latency --jobs 1 --allow-non-avx512 --results results/refinement/naamah-latency
```

This separate matrix declares 23 configurations per bandwidth: six PSK/FEC
combinations, nine diversity controls, and eight additional cadence settings.
It has 92 quick assertions, 192 ten-second AWGN points, 414 ten-second RF
screens, 216 ten-second off-preset message screens, 414 sustained message
cases, and 46 twelve-second serial latency cases. Sustained quiet/moderate/
disturbed durations are 300/300/100 seconds for every configuration and seed.
The original matrices and their recorded runtime limits are retained.

QPSK/8-PSK+BCH use `--modulation qpsk|8psk --bch-payload --soft-demapping`
with `--no-carrier-correction`. The payload BCH decoder is still a hard
decoder; soft metrics also protect the RF header. Exact complete tested
configurations, including the equalizer span, are in each result JSON.

For diversity, select `--audio-waveform bpsk_frequency_diversity --modulation
bpsk --symbol-rate-hz 0`, then set `--diversity-branch-bandwidth-hz` and
`--diversity-separation-hz`. Zero retains the original half-band geometry.
The copies must not overlap or extend outside the configured audio bandwidth.
`--diversity-branch both|lower|upper` selects two equal-power copies or a
single full-power control at exactly the same symbol rate and framing.
Total nominal power is held constant as width or copy count changes.
The power audit found that this nominal convention disagrees with measured
RRC power: at width 0.4B, diversity emits about 2.5× full-band BPSK power.
Lower/upper/both controls match each other. The noise reference also misstates
actual pre-fade SNR. `python3 scripts/validate_refinement_power.py` retains six
exact-source xfails and 54 matched-control assertions using the existing RF
measurements. Do not interpret these or earlier cross-family runs as equal
actual power; see [the calibration audit](results/refinement/power-audit/SUMMARY.md).
The width/rate convention uses the current 0.25 RRC rolloff profile. Other
rolloffs are outside this campaign's spectral-spacing validation.

The new diversity grid uses branch width 0.4B and center separations B/2,
B/2+137 Hz, and 0.55B+137 Hz. The same Watterson channel acts on both copies.
Per-result metadata records actual center frequencies, occupied span, power
split, rounded channel delay and analytical center-response correlation.
Extra 2.75/3.25 ms and 6.75/7.25 ms delays test sensitivity around the moderate
and disturbed presets; they are not new ITU channel presets.

`--pilot-interval-symbols` varies the existing known-symbol pair cadence.
`--recovery-interval-frames` varies the existing full preamble/training/header
interval without restarting FEC or encryption. The five schedules are
(pilot symbols, recovery frames) = (16,16), (32,16), (64,16), (32,4), (32,64).
Each result records the complete segment airtime and payload airtime fraction.
No frequency tracker is added. B5 uses the longer 3 ms equalizer setup;
transmission, retraining and modem residence remain in the paired intrinsic
reference, while diversity combining wait counts against the 2.1 ms allowance.

`python3 scripts/refinement_results.py --snapshot` saves a reproducible source
archive before measurements. After collecting all results, host regression
evidence and three repeated cases, run the power audit above, then
`python3 scripts/refinement_results.py`
validates coverage and provenance and generates the comparison report.
The report includes the interrupted runner's elapsed time and any runtime
overrun. A resumed run must keep the original source digest, base revision,
seeds and parameters; `--resume` reuses only matching saved records.

After `python3 scripts/update_html_results.py`, the optional Playwright check
`node scripts/validate_refinement_html.cjs [URL] [output.json]` verifies every
comparison filter against its linked raw records, all 46 host latency rows,
mobile layout and the static table without JavaScript. Set `CHROME_PATH` to
use an installed browser; omit URL to check the local page.

### Conventional encoding simulated channel comparison

The [encoding report](results/encoding-improvements/REPORT.md) compares 21
configurations at 10 and 24 kHz. It includes fixed-constellation soft bit
metrics, K9 convolutional rates 1/2 and 1/3, plain Walsh-8 spreading,
shortened BCH(58,40,7), rectangular interleaving, noncoherent 4/8-FSK and
two-subband BPSK diversity. The [patent screen](results/encoding-improvements/PATENT_SCREEN.md)
records the historical implementation boundaries and excluded designs. It is
a public-record engineering screen, not worldwide patent clearance.

```sh
python3 tests/simulated_channel/run.py --tier quick --campaign encoding_quick --jobs 8 --results results/encoding-improvements
python3 tests/simulated_channel/run.py --tier full --campaign encoding_screen --seeds 7446529 7446530 7446531 --jobs 8 --results results/encoding-improvements
python3 tests/simulated_channel/run.py --tier full --campaign encoding_snr --jobs 8 --results results/encoding-improvements
python3 tests/simulated_channel/run.py --tier full --campaign encoding_followup --seeds 7446529 7446530 7446531 --jobs 8 --results results/encoding-improvements
# On naamah, build without the AVX-512 requirement and measure serially:
python3 tests/simulated_channel/run.py --tier full --campaign encoding_latency --jobs 1 --allow-non-avx512 --results results/encoding-improvements/naamah-latency
```

The quick campaign has 84 cases. Full selections contain 756 channel screens,
672 AWGN points, 378 sustained message cases and 42 latency measurements.
Screens and SNR points last 10 seconds for coherent modes and 30 for FSK;
sustained quiet/moderate/disturbed runs last 300/300/100 seconds for every
configuration and seed. B5 uses 12 seconds for coherent modes and 30 for FSK.
These declared durations are retained even when a runtime allowance is exceeded.
The complete original matrix and its runtime findings remain separate.

All new options are explicit in `RestartRequest` and
`scripts/configure_local_radios.py`; both endpoints receive matching settings
over fiber/gRPC. For example, add the following to the existing radio setup
command to select soft BPSK with the longer half-rate code:

```sh
--modulation bpsk --bandwidth-hz 24000 --symbol-rate-hz 0 \
--no-carrier-correction --soft-demapping --fec k9-1/2
```

The exact equalizer, training and recovery settings used by a measurement are
in its JSON; the example does not reproduce an entire polar test configuration.
Additional options are `--bch-payload`, `--walsh-bits 3`,
`--interleaver-rows R --interleaver-columns C`, and
`--audio-waveform fsk4|fsk8|bpsk_frequency_diversity`.
FSK4 uses QPSK bit labels; FSK8 uses 8-PSK labels, selected with
`--modulation qpsk|8psk`. Its physical signal is a tone, not a PSK symbol.
`--fsk-useful-ms 4 --fsk-guard-ms 8` selects the longer guard experiment.
Diversity requires BPSK and recurring recovery markers; its two half-band
copies share the original total transmit power. `--diversity-wait-ms` controls
the maximum wait for a matching second copy.

The payload order is source bytes → convolutional **or** BCH FEC → AES-CTR →
optional Walsh spreading → optional block interleaving → waveform. BCH replaces
convolutional payload coding; the protected RF header keeps its own code.
Ordinary BCH decoding corrects up to three hard bit errors per shortened word.
Soft demapping uses exhaustive Euclidean bit distances and known-pilot noise
estimates, with the existing fixed constellation. New soft experiments use
Viterbi hard output followed by the existing message CRC; post-Viterbi confidence
is not a calibrated probability. Soft demapping with differential mappings is
currently rejected. CRC does not provide AEAD authentication.

FSK acquires from its own tone preamble and coded tone header. It uses energy
detection and per-frame timing acquisition, with no RLS, Gardner or carrier
frequency loop. Coherent modes retain the existing RLS and clock recovery.
FSK's long serialization needs an appropriate control-plane timestamp window
if timestamp checks are enabled; the simulation disables that check as in
earlier campaigns. It does not change the production replay rule.

Nominal full-band sample power is held fixed, including FSK and diversity.
The half-band BPSK control distinguishes slower symbols from a diversity gain.
The fixed 5/12 kHz center separation is commensurate with the presets' integer-ms
path delays: the two-path channel response repeats at those centers. These
comparisons therefore do not establish a gain from decorrelated frequency paths.
Interleaver and diversity combining waits are disabled in B5's intrinsic
reference and charged to **added buffering**. Their 2.1 ms failures remain
visible. Fresh goodput additionally excludes a correct delivery if a newer
source-created message exists for its key; this uses simulator observations
without feeding source truth to the receiver.

The `goblin_cannon_channel_coding` and `goblin_cannon_audio_waveform` quick
assertions use seeds 7446533 and 7446534. They cover analytical soft metrics,
every three-bit BCH error pattern on the zero codeword, generated codewords,
stream chunk boundaries and absolute-position recovery, unchanged legacy
bytes, fixed-power FSK, residual phase/offset and production-message recovery.
After collecting all records and host evidence, regenerate the report with
`python3 scripts/encoding_results.py`.

### PSK simulated channel comparison

The PSK campaign compares eleven configurations at both bandwidths: QPSK
with either header, BPSK with either header, 8-PSK with either header, coherent
16-QAM/64-QAM controls, and DBPSK/DQPSK/π/4-DQPSK with BPSK headers. Compare
differential formats with their matching coherent BPSK-header control.
All keep carrier correction off and recovery-profile equalization on.

```sh
ctest --test-dir build --output-on-failure
python3 tests/simulated_channel/run.py --tier quick --campaign psk_quick --results results/psk-improvements
python3 tests/simulated_channel/run.py --tier full --campaign psk_screen --seeds 7446529 7446530 7446531 --jobs 8 --results results/psk-improvements
python3 tests/simulated_channel/run.py --tier full --campaign psk_snr --jobs 8 --results results/psk-improvements
python3 tests/simulated_channel/run.py --tier full --campaign psk_followup --seeds 7446529 7446530 7446531 --jobs 8 --results results/psk-improvements
# On naamah, after building without the AVX-512 requirement; run serially:
python3 tests/simulated_channel/run.py --tier quick --campaign psk_latency --jobs 1 --allow-non-avx512 --results results/psk-improvements/naamah-latency
python3 tests/simulated_channel/run.py --tier full --campaign psk_latency --jobs 1 --allow-non-avx512 --results results/psk-improvements/naamah-latency
```

Screens last ten seconds per seed. The independent follow-up uses
300/300/100 seconds on quiet/moderate/disturbed, respectively, retaining every
delivery in aggregate metrics. It does not replace the previous 6,000-second
quiet campaign or establish an F.1487 BER operating limit. Noise curves retain
all sixteen 0–30 dB points at equal nominal symbol energy; SNR is not Eb/N0.
PAPR is measured over clean pulse-shaped RF samples including controls and
tails; no PA backoff gain is assumed. The 22 serial twelve-second short-span
latency measurements necessarily exceed the quick-tier runtime allowance;
the execution report records that overrun without shortening the runs.

`goblin_cannon_psk` uses seed 7446532 for known phase vectors, generated
payloads, arbitrary common phase/drift, absolute pilots, chunk invariance,
configuration mismatch rejection and production-message dropout recovery.
The π/4 mapping uses 00/01/10/11 → +45/+135/−45/−135 degrees, as documented by
[Keysight](https://helpfiles.keysight.com/csg/89600B/Webhelp/Subsystems/digdemod/content/dlg_digdemod_fmt_pi4dqpsk.htm).
Differential mapping does not replace acquisition, equalization or header
decoding. Both endpoints are configured through the existing fiber control
interface; compact headers bind settings into the CRC without adding a
parameter-negotiation channel.

### Simulated channel result files

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
