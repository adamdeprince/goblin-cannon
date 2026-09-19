# Goblin Cannon simulated channel — 24 kHz header fix

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

The clean 24 kHz profile now validates its header and delivers correct payloads
with carrier correction off and adaptive equalization on. The only production
change is the matched-filter readiness boundary in `src/modem.cpp`.

## Simulated channel cause and correction

At 48 ksample/s and 19.2 ksymbol/s there are 2.5 samples per symbol. For some
symbols the matched filter's right edge lies between samples. The decoder used
`ceil` to decide whether enough samples were available, while the filter itself
ends at `floor`. That withheld the last training/header symbol. Retrying the
same fixed-size header block could never satisfy the extra-sample requirement.

The readiness check now uses `floor`, matching the filter's inclusive boundary.
No padding, additional buffering, waveform changes or carrier tracking were
introduced. [Production patch](production-fix.patch).

## Simulated channel regression evidence

Both new strict regressions failed against the original receiver and passed
after the fix. Each is tagged `quick` / `assert`.

| Check | Result |
| --- | --- |
| Finite matched-filter blocks | All 10 combinations of 2 / 2.5 / 3.125 / 5 / 6 samples per symbol and 32 / 33 symbols pass. Withholding the last required sample withholds the last symbol; supplying it releases the symbol exactly once. |
| Complete RF reception | All 24 combinations of 10 / 24 kHz, QPSK / 16-QAM / 64-QAM, and 1 / 48 / 157 / 512-sample input chunks pass. Valid header, exactly 1,024 correct payload symbols, correct frame counters/offsets, no lock loss. |
| avx10, AVX-512 | 13/13 CTest entries pass. |
| naamah, AVX2 | 13/13 CTest entries pass. |
| Complete quick acceptance matrix | 243 cases in 206.333 seconds; the 120-second tier budget remains exceeded. |
| A8, A9 and D6 follow-up | Eight cases in 7.697 seconds. |
| Quiet-host B5 follow-up | Six original 12-second cases, one worker, 72.323 seconds total. |

The 10-second zero-offset 24 kHz controls each deliver all 2,824 RF frames with
zero measured BER for QPSK, 16-QAM and 64-QAM. Their BER comparison margins remain
`THRESHOLD_TBD`; the synchronization assertions now pass.

[Baseline failures](baseline-regressions.log), [avx10 CTest output](fixed-ctest-detailed.log),
[naamah CTest output](naamah-b5/fixed-ctest-detailed.log),
[parameters and source hashes](VALIDATION.json), [host configurations](HOSTS.json).

## Simulated channel remaining failures

Removed 33 resolved expected-failure entries and updated 32 reasons that had
previously attributed failures to the clean-header defect. Acceptance thresholds
and channel parameters were unchanged. The re-evaluated 251 avx10 cases contain
17 passes, 88 `THRESHOLD_TBD`, 66 characterizations, 77 expected failures and
three unavailable cases. Original execution logs retain the initial unexpected
passes; [the review](EXPECTED_FAILURE_REVIEW.json) records every expectation change.

Clock mismatch, AGC excursions, low-SNR acquisition, high-latitude/dropout
recovery, scheduler semantics, integrity and latency findings remain separate.
The full characterization sweep and soak were not rerun for this fix.

Getting past the header exposed one additional existing failure: A8 at -10 dB
co-channel SIR delivered 2,672 messages outside the expected source stream.
That exact assertion is retained as `xfail` for separate integrity work. The
observed count includes invalid or non-source payloads; it is not a count of
AEAD failures, because authenticated delivery is not implemented.

## Simulated channel 24 kHz quiet-host message delivery

These are one serial B5 follow-up on `naamah`, with startup included and the
same seed and parameters as the original cases. Previously all three delivered
zero messages. A message still in flight when the 12-second fixture ends is
included in the created count.

| Modulation | Delivered / created | p50 ms | p99.9 ms | 2.1 ms assertion |
| --- | ---: | ---: | ---: | --- |
| QPSK / 4-QAM | 1,199 / 1,200 | 7.000 | 27.039 | xfail |
| 16-QAM | 1,200 / 1,200 | 4.000 | 22.041 | xfail |
| 64-QAM | 1,200 / 1,200 | 3.004 | 21.091 | xfail |

[Acceptance tables and retained defects](SUMMARY.md) ·
[Quiet-host timing and stage breakdown](naamah-b5/SUMMARY.md).
