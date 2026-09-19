# Simulated channel latency regression profile

<!-- BEGIN CHANNEL CONTRACT -->

For the recorded acceptance profile:

The modem assumes the radio hands it audio with the carrier frequency offset already removed to within 10 Hz. It performs no Doppler-shift correction. Delay spread, Doppler spread, fading, phase rotation, multipath and noise are the modem's problem, and are what the recorded runs measure.

This boundary describes the recorded acceptance profile. The carrier-offset sweep uses 24 kHz QPSK+BCH, the combined recovery settings, the high-latitude quiet preset, 30 dB nominal SNR and three 300-second traces per offset. The tolerance applies to that measured configuration and the tested offset grid. Other modes and historical receiver versions have no tolerance established by this sweep. The library retains an optional carrier-correction loop, enabled by default; the recorded acceptance profile explicitly disables it. Equalizer phase tracking does not estimate a mean carrier frequency offset or perform AFC.

<!-- END CHANNEL CONTRACT -->

The 12 brief configurations all remain under 2.1 ms. The largest per-configuration increases were investigated before accepting the result. These are measured host observations, separate from deterministic channel metrics.

## Simulated channel buffering and CPU measurements

| Case | Brief added p99.9 ms | Current added p99.9 ms | Deterministic buffer increase µs | Matched pre-AEAD added p99.9 ms | TX call p99.9 change µs | RX call p99.9 change µs |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| B5_24000_16qam_null | 0.755446 | 1.055395 | 229.166667 | 0.786433 | 5.750000 | 17.523000 |
| B5_24000_16qam_polar_span_null | 0.712733 | 1.050668 | 312.500000 | 0.721628 | -8.677000 | 29.726000 |
| B5_24000_qpsk_polar_span_null | 0.857044 | 1.027175 | 125.000000 | 0.858113 | -0.280000 | -4.729000 |

Authenticated records are longer than CRC records, changing where their ends fall inside the 1 ms audio blocks. The one-sample references show buffering increases of 125–312.5 µs in these cases. Those increases are included in the 2.1 ms check, not subtracted away.

The matched pre-AEAD build is the verified source snapshot `1279f74e940aad991bf328e3b7cd796ea496b24bd9e05c78e3a6c6a8cec322e8` from the preceding implementation, measured serially on the same naamah host. Its complete parameters and source identity are retained under `profile/pre-aead/`. Some decoder changes occurred between the brief’s older baseline and that snapshot; the tables distinguish them.

Across these three cases, the current TX/RX call p99.9 changes versus the matched build range from −8.7 to +29.7 µs. These are per-call measurements, not additive per-message attribution. The GCM-only profile reports 0.280 µs seal and 0.261 µs verify/open p99.9 for a three-byte body. Contexts are reused, and each call supplies only a fresh nonce. This evidence points to audio-block alignment, with modest surrounding pipeline cost, rather than per-frame OpenSSL allocation or re-keying.

At the maximum 65,534-byte body, seal/verify p99.9 are 22.733/26.801 µs. First-use provider/context initialization is reported separately (936.452 µs); it occurs before source messages are created. No startup time was silently removed from an in-flight message.
