# Goblin Cannon simulated channel current results

The production message path now uses OpenSSL AES-256-GCM. All results below use
simulated channels; none represents transmission or RF equipment measurements.

[Current report, parameters and open thresholds](aead/SUMMARY.md) ·
[Validation manifest](aead/VALIDATION.json) ·
[CPU and buffering profile](aead/PROFILE.md)

## Simulated channel security

All three A8 co-channel cases pass authentication and source-integrity checks.
At −10 dB SIR the receiver counts 359 authentication failures and delivers no
foreign or corrupt payloads. D6 rejects 43 tampered records and 16 replays;
two separate sender processes use 16 distinct nonces under the same key.

Nine expected-failing assertions across nine cases remain in the current
recovery-profile selection: seven residual-offset/gain cases, the auction
starvation policy conflict, and coordinated key rotation. Authenticated key IDs
and durable epoch negotiation provide rotation groundwork; overlapping keys and
mid-stream retirement remain unimplemented. The report reconciles this scope
with the older brief's 13-assertion count.

## Simulated channel latency

The requested 12-case B5 suite passes: worst added p99.9 is **1.055 ms** against
the unchanged **2.1 ms** allowance. The 12 current recovery-profile configurations
also pass, with a worst of **1.118 ms**. The report includes the requested
before/after table and separate transmission/modem reference and stage timings.

## Simulated channel polar delivery and validation

The current-format polar matrix covers BPSK, QPSK and 8-PSK, each with convolutional
and BCH coding, in both bandwidths and all three high-latitude presets. Three
seeds preserve 300/300/100-second quiet/moderate/disturbed durations. The site
shows these current measurements. Configured 30 dB remains an uncalibrated noise
reference; these finite traces do not establish route availability.

The selected campaign records 424 runs, including 12 byte-identical repeated
message runs. Both avx10 and naamah pass 21/21 CTest tests. The full A1–E4 matrix,
recorded-band noise and soak were not rerun. Combined quick selections exceed
two minutes; the report retains each invocation's duration.
