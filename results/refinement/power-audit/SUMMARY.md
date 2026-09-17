# Simulated channel — power calibration audit

The transmitter-power observations reveal two defects: the nominal SNR reference is not the actual pre-channel signal power, and diversity width compensation changes actual power relative to full-band BPSK. Production behavior and the original measurements are retained. Matched lower/upper/both diversity controls do have equal measured power within the existing 2% finite-waveform tolerance.

| Assertion | Seed | Power ratio(s) | Status |
| --- | --- | --- | --- |
| [E_power_nominal_10000_bpsk_bch](E_power_nominal_10000_bpsk_bch/7446529.json) | 7446529 | 5.953015 | xfail |
| [E_power_nominal_10000_diversity_commensurate_both](E_power_nominal_10000_diversity_commensurate_both/7446529.json) | 7446529 | 14.878862 | xfail |
| [E_power_fullband_10000](E_power_fullband_10000/7446529.json) | 7446529 | 2.499383 | xfail |
| [E_power_controls_10000_commensurate_quiet](E_power_controls_10000_commensurate_quiet/7446529.json) | 7446529 | 1.000000 / 1.000012 | pass |
| [E_power_controls_10000_commensurate_quiet](E_power_controls_10000_commensurate_quiet/7446530.json) | 7446530 | 1.000000 / 0.999959 | pass |
| [E_power_controls_10000_commensurate_quiet](E_power_controls_10000_commensurate_quiet/7446531.json) | 7446531 | 1.000000 / 1.000044 | pass |
| [E_power_controls_10000_commensurate_moderate](E_power_controls_10000_commensurate_moderate/7446529.json) | 7446529 | 1.000000 / 0.999949 | pass |
| [E_power_controls_10000_commensurate_moderate](E_power_controls_10000_commensurate_moderate/7446530.json) | 7446530 | 1.000000 / 0.999988 | pass |
| [E_power_controls_10000_commensurate_moderate](E_power_controls_10000_commensurate_moderate/7446531.json) | 7446531 | 1.000000 / 0.999927 | pass |
| [E_power_controls_10000_commensurate_disturbed](E_power_controls_10000_commensurate_disturbed/7446529.json) | 7446529 | 1.000000 / 0.999984 | pass |
| [E_power_controls_10000_commensurate_disturbed](E_power_controls_10000_commensurate_disturbed/7446530.json) | 7446530 | 1.000000 / 1.000038 | pass |
| [E_power_controls_10000_commensurate_disturbed](E_power_controls_10000_commensurate_disturbed/7446531.json) | 7446531 | 1.000000 / 1.000039 | pass |
| [E_power_controls_10000_offset137_quiet](E_power_controls_10000_offset137_quiet/7446529.json) | 7446529 | 1.000000 / 0.999999 | pass |
| [E_power_controls_10000_offset137_quiet](E_power_controls_10000_offset137_quiet/7446530.json) | 7446530 | 1.000000 / 1.000015 | pass |
| [E_power_controls_10000_offset137_quiet](E_power_controls_10000_offset137_quiet/7446531.json) | 7446531 | 1.000000 / 1.000048 | pass |
| [E_power_controls_10000_offset137_moderate](E_power_controls_10000_offset137_moderate/7446529.json) | 7446529 | 1.000000 / 1.000055 | pass |
| [E_power_controls_10000_offset137_moderate](E_power_controls_10000_offset137_moderate/7446530.json) | 7446530 | 1.000000 / 1.000126 | pass |
| [E_power_controls_10000_offset137_moderate](E_power_controls_10000_offset137_moderate/7446531.json) | 7446531 | 1.000000 / 1.000071 | pass |
| [E_power_controls_10000_offset137_disturbed](E_power_controls_10000_offset137_disturbed/7446529.json) | 7446529 | 1.000000 / 1.000012 | pass |
| [E_power_controls_10000_offset137_disturbed](E_power_controls_10000_offset137_disturbed/7446530.json) | 7446530 | 1.000000 / 0.999994 | pass |
| [E_power_controls_10000_offset137_disturbed](E_power_controls_10000_offset137_disturbed/7446531.json) | 7446531 | 1.000000 / 0.999964 | pass |
| [E_power_controls_10000_wide137_quiet](E_power_controls_10000_wide137_quiet/7446529.json) | 7446529 | 1.000000 / 1.000005 | pass |
| [E_power_controls_10000_wide137_quiet](E_power_controls_10000_wide137_quiet/7446530.json) | 7446530 | 1.000000 / 0.999983 | pass |
| [E_power_controls_10000_wide137_quiet](E_power_controls_10000_wide137_quiet/7446531.json) | 7446531 | 1.000000 / 0.999999 | pass |
| [E_power_controls_10000_wide137_moderate](E_power_controls_10000_wide137_moderate/7446529.json) | 7446529 | 1.000000 / 1.000001 | pass |
| [E_power_controls_10000_wide137_moderate](E_power_controls_10000_wide137_moderate/7446530.json) | 7446530 | 1.000000 / 0.999973 | pass |
| [E_power_controls_10000_wide137_moderate](E_power_controls_10000_wide137_moderate/7446531.json) | 7446531 | 1.000000 / 1.000011 | pass |
| [E_power_controls_10000_wide137_disturbed](E_power_controls_10000_wide137_disturbed/7446529.json) | 7446529 | 1.000000 / 1.000000 | pass |
| [E_power_controls_10000_wide137_disturbed](E_power_controls_10000_wide137_disturbed/7446530.json) | 7446530 | 1.000000 / 1.000014 | pass |
| [E_power_controls_10000_wide137_disturbed](E_power_controls_10000_wide137_disturbed/7446531.json) | 7446531 | 1.000000 / 0.999998 | pass |
| [E_power_nominal_24000_bpsk_bch](E_power_nominal_24000_bpsk_bch/7446529.json) | 7446529 | 2.480782 | xfail |
| [E_power_nominal_24000_diversity_commensurate_both](E_power_nominal_24000_diversity_commensurate_both/7446529.json) | 7446529 | 6.197819 | xfail |
| [E_power_fullband_24000](E_power_fullband_24000/7446529.json) | 7446529 | 2.498333 | xfail |
| [E_power_controls_24000_commensurate_quiet](E_power_controls_24000_commensurate_quiet/7446529.json) | 7446529 | 1.000000 / 0.999999 | pass |
| [E_power_controls_24000_commensurate_quiet](E_power_controls_24000_commensurate_quiet/7446530.json) | 7446530 | 1.000000 / 1.000015 | pass |
| [E_power_controls_24000_commensurate_quiet](E_power_controls_24000_commensurate_quiet/7446531.json) | 7446531 | 1.000000 / 1.000007 | pass |
| [E_power_controls_24000_commensurate_moderate](E_power_controls_24000_commensurate_moderate/7446529.json) | 7446529 | 1.000000 / 1.000008 | pass |
| [E_power_controls_24000_commensurate_moderate](E_power_controls_24000_commensurate_moderate/7446530.json) | 7446530 | 1.000000 / 1.000022 | pass |
| [E_power_controls_24000_commensurate_moderate](E_power_controls_24000_commensurate_moderate/7446531.json) | 7446531 | 1.000000 / 1.000013 | pass |
| [E_power_controls_24000_commensurate_disturbed](E_power_controls_24000_commensurate_disturbed/7446529.json) | 7446529 | 1.000000 / 0.999988 | pass |
| [E_power_controls_24000_commensurate_disturbed](E_power_controls_24000_commensurate_disturbed/7446530.json) | 7446530 | 1.000000 / 0.999979 | pass |
| [E_power_controls_24000_commensurate_disturbed](E_power_controls_24000_commensurate_disturbed/7446531.json) | 7446531 | 1.000000 / 1.000041 | pass |
| [E_power_controls_24000_offset137_quiet](E_power_controls_24000_offset137_quiet/7446529.json) | 7446529 | 1.000000 / 0.999949 | pass |
| [E_power_controls_24000_offset137_quiet](E_power_controls_24000_offset137_quiet/7446530.json) | 7446530 | 1.000000 / 0.999989 | pass |
| [E_power_controls_24000_offset137_quiet](E_power_controls_24000_offset137_quiet/7446531.json) | 7446531 | 1.000000 / 1.000015 | pass |
| [E_power_controls_24000_offset137_moderate](E_power_controls_24000_offset137_moderate/7446529.json) | 7446529 | 1.000000 / 0.999989 | pass |
| [E_power_controls_24000_offset137_moderate](E_power_controls_24000_offset137_moderate/7446530.json) | 7446530 | 1.000000 / 0.999991 | pass |
| [E_power_controls_24000_offset137_moderate](E_power_controls_24000_offset137_moderate/7446531.json) | 7446531 | 1.000000 / 0.999991 | pass |
| [E_power_controls_24000_offset137_disturbed](E_power_controls_24000_offset137_disturbed/7446529.json) | 7446529 | 1.000000 / 1.000018 | pass |
| [E_power_controls_24000_offset137_disturbed](E_power_controls_24000_offset137_disturbed/7446530.json) | 7446530 | 1.000000 / 0.999970 | pass |
| [E_power_controls_24000_offset137_disturbed](E_power_controls_24000_offset137_disturbed/7446531.json) | 7446531 | 1.000000 / 1.000019 | pass |
| [E_power_controls_24000_wide137_quiet](E_power_controls_24000_wide137_quiet/7446529.json) | 7446529 | 1.000000 / 1.000002 | pass |
| [E_power_controls_24000_wide137_quiet](E_power_controls_24000_wide137_quiet/7446530.json) | 7446530 | 1.000000 / 0.999997 | pass |
| [E_power_controls_24000_wide137_quiet](E_power_controls_24000_wide137_quiet/7446531.json) | 7446531 | 1.000000 / 0.999994 | pass |
| [E_power_controls_24000_wide137_moderate](E_power_controls_24000_wide137_moderate/7446529.json) | 7446529 | 1.000000 / 0.999997 | pass |
| [E_power_controls_24000_wide137_moderate](E_power_controls_24000_wide137_moderate/7446530.json) | 7446530 | 1.000000 / 0.999998 | pass |
| [E_power_controls_24000_wide137_moderate](E_power_controls_24000_wide137_moderate/7446531.json) | 7446531 | 1.000000 / 0.999990 | pass |
| [E_power_controls_24000_wide137_disturbed](E_power_controls_24000_wide137_disturbed/7446529.json) | 7446529 | 1.000000 / 1.000015 | pass |
| [E_power_controls_24000_wide137_disturbed](E_power_controls_24000_wide137_disturbed/7446530.json) | 7446530 | 1.000000 / 0.999990 | pass |
| [E_power_controls_24000_wide137_disturbed](E_power_controls_24000_wide137_disturbed/7446531.json) | 7446531 | 1.000000 / 1.000004 | pass |

## Simulated channel — Defects found

- `E_power_nominal_10000_bpsk_bch` (7446529) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- `E_power_nominal_10000_diversity_commensurate_both` (7446529) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- `E_power_fullband_10000` (7446529) — The diversity branch gain increases measured power by about B/branch_width relative to full-band BPSK.
- `E_power_nominal_24000_bpsk_bch` (7446529) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- `E_power_nominal_24000_diversity_commensurate_both` (7446529) — The noise reference assumes sample-energy-normalized RRC taps; the transmitter uses symbol-time RRC amplitudes.
- `E_power_fullband_24000` (7446529) — The diversity branch gain increases measured power by about B/branch_width relative to full-band BPSK.

## Simulated channel — pre-fade SNR interpretation

Measured pre-fade SNR is the configured nominal SNR plus 10 log10(measured power / nominal reference power). It is not the instantaneous SNR through a fade.

| Band | Waveform | Configured nominal SNR | Measured pre-fade SNR |
| --- | --- | ---: | ---: |
| 10 kHz | bpsk_bch | 30 dB | 37.747 dB |
| 10 kHz | diversity_commensurate_both | 30 dB | 41.726 dB |
| 24 kHz | bpsk_bch | 30 dB | 33.946 dB |
| 24 kHz | diversity_commensurate_both | 30 dB | 37.922 dB |
