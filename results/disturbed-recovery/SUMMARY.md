# Goblin Cannon simulated channel — disturbed recovery

All four experiments are implemented and measured: warm equalizer recovery with varied known startup symbols and shorter recurring training; uncertainty prediction through rejected decisions; a fiber-selected 13-byte authenticated header; and frequency diversity with matched measured power. Carrier correction remains off. The GCM tag remains 16 bytes.

Fresh calibrated baselines use the same source, channel seeds and full durations as the changed receiver. The earlier noise reference underestimated RRC sample power and diversity width compensation increased transmit power. Those errors are corrected before these comparisons. No per-fade normalization is used.

At 24 kHz on the disturbed preset, QPSK+BCH fresh goodput changes from 2.24–7.36 to 38.00–46.48 bit/s. Longest delivery silences change from 20.308–31.871 to 4.483–7.062 seconds. This is useful but still intermittent delivery. Uncertainty aging alone produces 0.96–2.56 bit/s; it is not a standalone improvement on these traces.

The recipe remains selectable: quiet 24 kHz 8-PSK+BCH falls from 2071.89–2080.96 to 1944.91–1950.45 fresh bit/s. At 10 kHz, disturbed delivery remains essentially absent (one message in one seed for each QPSK coding choice). These controls do not provide a universal channel improvement.

Two-copy frequency diversity at 24 kHz delivers only 0.00–0.32 fresh bit/s on the disturbed preset. It improves over its narrow single-copy controls on moderate fading, but remains far behind the full-band configurations. All 54 null-channel compact-diversity assertions pass; the poor fading result is retained.

908 recorded runs; 5 failing assertions across 5 cases. Three seeds: 7446529, 7446530, 7446531. Quiet/moderate/disturbed message durations are 300/300/100 seconds per seed; raw RF screens are ten seconds. Off-preset diversity traces are 100 seconds. Ranges are finite-seed ranges, not confidence intervals.

## Simulated channel A2 — current RF screening

| Band | Coding | Preset | Conditional BER | Frame survival % | Observed bits % |
| --- | --- | --- | --- | --- | --- |
| 10 kHz | BPSK · convolutional | quiet | 0.00000 | 84.42–96.29 | 84.53–96.42 |
| 10 kHz | BPSK · convolutional | moderate | 0.05678–0.08532 | 20.44–37.08 | 39.08–53.31 |
| 10 kHz | BPSK · convolutional | disturbed | 0.24531–0.37500 | 0.18–0.92 | 1.29–3.67 |
| 10 kHz | BPSK · BCH | quiet | 0.00000 | 84.40–96.29 | 84.52–96.42 |
| 10 kHz | BPSK · BCH | moderate | 0.06917–0.08354 | 27.73–32.96 | 42.73–52.75 |
| 10 kHz | BPSK · BCH | disturbed | 0.15937–0.33163 | 0.37–0.55 | 1.84–4.51 |
| 10 kHz | QPSK · convolutional | quiet | 0.00000 | 84.42–95.10 | 84.53–95.23 |
| 10 kHz | QPSK · convolutional | moderate | 0.11639–0.13574 | 8.08–16.64 | 22.83–34.52 |
| 10 kHz | QPSK · convolutional | disturbed | 0.18290–0.26771 | 0.18–0.55 | 1.19–2.76 |
| 10 kHz | QPSK · BCH | quiet | 0.00000 | 84.40–95.10 | 84.53–95.23 |
| 10 kHz | QPSK · BCH | moderate | 0.10232–0.11737 | 13.63–19.33 | 29.49–40.43 |
| 10 kHz | QPSK · BCH | disturbed | 0.20729–0.28033 | 0.00–0.37 | 1.38–2.66 |
| 10 kHz | 8-PSK · convolutional | quiet | 0.00000 | 84.42–94.07 | 84.53–94.06 |
| 10 kHz | 8-PSK · convolutional | moderate | 0.10813–0.12059 | 4.12–4.44 | 14.19–21.16 |
| 10 kHz | 8-PSK · convolutional | disturbed | 0.23065–0.31345 | 0.00 | 0.64–2.02 |
| 10 kHz | 8-PSK · BCH | quiet | 0.00000–0.00009 | 84.27–93.92 | 84.53–94.06 |
| 10 kHz | 8-PSK · BCH | moderate | 0.07862–0.11287 | 3.65–7.61 | 14.98–24.34 |
| 10 kHz | 8-PSK · BCH | disturbed | 0.23785–0.31684 | 0.00 | 0.92–2.20 |
| 24 kHz | BPSK · convolutional | quiet | 0.00000 | 99.93–100.00 | 99.98–100.00 |
| 24 kHz | BPSK · convolutional | moderate | 0.02032–0.03120 | 62.59–70.10 | 74.70–79.12 |
| 24 kHz | BPSK · convolutional | disturbed | 0.07062–0.11316 | 16.74–23.33 | 35.94–40.46 |
| 24 kHz | BPSK · BCH | quiet | 0.00000 | 99.41–100.00 | 99.46–100.00 |
| 24 kHz | BPSK · BCH | moderate | 0.01421–0.03061 | 64.91–74.75 | 77.53–82.72 |
| 24 kHz | BPSK · BCH | disturbed | 0.09444–0.15326 | 15.85–21.88 | 36.19–43.17 |
| 24 kHz | QPSK · convolutional | quiet | 0.00000 | 99.93–100.00 | 99.98–100.00 |
| 24 kHz | QPSK · convolutional | moderate | 0.02389–0.04089 | 50.50–59.49 | 68.51–74.86 |
| 24 kHz | QPSK · convolutional | disturbed | 0.11620–0.14074 | 8.25–10.37 | 24.73–27.30 |
| 24 kHz | QPSK · BCH | quiet | 0.00000 | 99.93–100.00 | 99.98–100.00 |
| 24 kHz | QPSK · BCH | moderate | 0.02931–0.03933 | 51.20–57.86 | 67.80–75.32 |
| 24 kHz | QPSK · BCH | disturbed | 0.11394–0.13964 | 7.59–11.38 | 24.73–27.96 |
| 24 kHz | 8-PSK · convolutional | quiet | 0.00000–0.00004 | 99.87–99.93 | 99.98–100.00 |
| 24 kHz | 8-PSK · convolutional | moderate | 0.02850–0.03242 | 39.74–43.30 | 59.71–65.18 |
| 24 kHz | 8-PSK · convolutional | disturbed | 0.12194–0.14149 | 1.11–3.34 | 11.73–17.14 |
| 24 kHz | 8-PSK · BCH | quiet | 0.00000–0.00027 | 98.31–99.93 | 98.88–100.00 |
| 24 kHz | 8-PSK · BCH | moderate | 0.02521–0.04626 | 29.59–46.40 | 49.94–68.58 |
| 24 kHz | 8-PSK · BCH | disturbed | 0.12451–0.13369 | 1.12–3.12 | 11.77–15.85 |

## Simulated channel E2 — fresh authenticated useful bit/s

| Band | Coding | Preset | Calibrated baseline | Combined changes |
| --- | --- | --- | --- | --- |
| 10 kHz | BPSK · convolutional | quiet | 46.45–47.31 | [198.32–200.67](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_soft_high_lat_quiet_combined/7446529.json) |
| 10 kHz | BPSK · convolutional | moderate | 4.59–5.01 | [14.83–15.41](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_soft_high_lat_moderate_combined/7446529.json) |
| 10 kHz | BPSK · convolutional | disturbed | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_soft_high_lat_disturbed_combined/7446529.json) |
| 10 kHz | BPSK · BCH | quiet | 279.44–284.45 | [338.37–341.15](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_quiet_combined/7446529.json) |
| 10 kHz | BPSK · BCH | moderate | 15.04–16.88 | [23.89–28.16](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_moderate_combined/7446529.json) |
| 10 kHz | BPSK · BCH | disturbed | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_combined/7446529.json) |
| 10 kHz | QPSK · convolutional | quiet | 425.63–432.24 | [493.49–497.44](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_soft_high_lat_quiet_combined/7446529.json) |
| 10 kHz | QPSK · convolutional | moderate | 14.29–17.97 | [27.92–33.04](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_soft_high_lat_moderate_combined/7446529.json) |
| 10 kHz | QPSK · convolutional | disturbed | 0.00 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_soft_high_lat_disturbed_combined/7446529.json) |
| 10 kHz | QPSK · BCH | quiet | 588.99–597.20 | [682.32–687.23](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_quiet_combined/7446529.json) |
| 10 kHz | QPSK · BCH | moderate | 22.16–25.84 | [42.35–52.13](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_moderate_combined/7446529.json) |
| 10 kHz | QPSK · BCH | disturbed | 0.00 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_combined/7446529.json) |
| 10 kHz | 8-PSK · convolutional | quiet | 635.33–642.69 | [737.81–742.08](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_soft_high_lat_quiet_combined/7446529.json) |
| 10 kHz | 8-PSK · convolutional | moderate | 7.44–8.43 | [21.33–23.55](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_soft_high_lat_moderate_combined/7446529.json) |
| 10 kHz | 8-PSK · convolutional | disturbed | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_soft_high_lat_disturbed_combined/7446529.json) |
| 10 kHz | 8-PSK · BCH | quiet | 879.23–885.95 | [1016.45–1026.16](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_bch_high_lat_quiet_combined/7446529.json) |
| 10 kHz | 8-PSK · BCH | moderate | 10.99–12.27 | [24.80–30.83](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_bch_high_lat_moderate_combined/7446529.json) |
| 10 kHz | 8-PSK · BCH | disturbed | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_8psk_bch_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | BPSK · convolutional | quiet | 504.48–507.04 | [578.00–578.21](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_soft_high_lat_quiet_combined/7446529.json) |
| 24 kHz | BPSK · convolutional | moderate | 177.31–191.57 | [255.65–267.47](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_soft_high_lat_moderate_combined/7446529.json) |
| 24 kHz | BPSK · convolutional | disturbed | 2.16–3.20 | [7.92–15.60](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_soft_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | BPSK · BCH | quiet | 696.03–698.00 | [797.71](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_quiet_combined/7446529.json) |
| 24 kHz | BPSK · BCH | moderate | 260.19–276.85 | [363.12–385.79](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_moderate_combined/7446529.json) |
| 24 kHz | BPSK · BCH | disturbed | 1.52–3.52 | [20.64–25.20](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | QPSK · convolutional | quiet | 1021.49–1022.03 | [1156.16–1156.69](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_soft_high_lat_quiet_combined/7446529.json) |
| 24 kHz | QPSK · convolutional | moderate | 317.44–331.95 | [445.39–475.76](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_soft_high_lat_moderate_combined/7446529.json) |
| 24 kHz | QPSK · convolutional | disturbed | 1.84–4.48 | [28.64–31.68](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_soft_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | QPSK · BCH | quiet | 1408.93–1409.36 | [1593.97–1594.51](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_quiet_combined/7446529.json) |
| 24 kHz | QPSK · BCH | moderate | 441.68–458.72 | [627.55–632.11](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_moderate_combined/7446529.json) |
| 24 kHz | QPSK · BCH | disturbed | 2.24–7.36 | [38.00–46.48](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | 8-PSK · convolutional | quiet | 1518.56–1523.04 | [1717.79–1723.20](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_soft_high_lat_quiet_combined/7446529.json) |
| 24 kHz | 8-PSK · convolutional | moderate | 230.32–245.01 | [487.55–506.61](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_soft_high_lat_moderate_combined/7446529.json) |
| 24 kHz | 8-PSK · convolutional | disturbed | 0.32–1.60 | [14.56–16.64](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_soft_high_lat_disturbed_combined/7446529.json) |
| 24 kHz | 8-PSK · BCH | quiet | 2071.89–2080.96 | [1944.91–1950.45](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_bch_high_lat_quiet_combined/7446529.json) |
| 24 kHz | 8-PSK · BCH | moderate | 300.35–324.16 | [580.83–589.87](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_bch_high_lat_moderate_combined/7446529.json) |
| 24 kHz | 8-PSK · BCH | disturbed | 0.64–1.12 | [17.92–24.72](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_8psk_bch_high_lat_disturbed_combined/7446529.json) |

### Simulated channel E2 — disturbed ablation

`warm` includes varied startup symbols, retained echo support, three warm training passes with cold fallback, a final-64-symbol training score, training length max(128, ceil(1.4 × feedforward span)) and recovery every eight frames. `time` changes uncertainty prediction alone; `compact` changes the message header alone. `combined` enables all three. Baseline retains the longer training and sixteen-frame cadence. The EVM rejection limit stays 0.45.

| Band | Coding | Change | Useful bit/s | Fresh bit/s | Maximum silence, s |
| --- | --- | --- | --- | --- | --- |
| 10 kHz | BPSK · BCH | baseline | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_baseline/7446529.json) | 100.000 |
| 10 kHz | BPSK · BCH | warm | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_warm/7446529.json) | 100.000 |
| 10 kHz | BPSK · BCH | time | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_time/7446529.json) | 100.000 |
| 10 kHz | BPSK · BCH | compact | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_compact/7446529.json) | 100.000 |
| 10 kHz | BPSK · BCH | combined | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_bpsk_bch_high_lat_disturbed_combined/7446529.json) | 100.000 |
| 10 kHz | QPSK · BCH | baseline | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_baseline/7446529.json) | 100.000 |
| 10 kHz | QPSK · BCH | warm | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_warm/7446529.json) | 100.000 |
| 10 kHz | QPSK · BCH | time | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_time/7446529.json) | 100.000 |
| 10 kHz | QPSK · BCH | compact | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_compact/7446529.json) | 100.000 |
| 10 kHz | QPSK · BCH | combined | 0.00–0.32 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_10000_qpsk_bch_high_lat_disturbed_combined/7446529.json) | 69.164–100.000 |
| 24 kHz | BPSK · BCH | baseline | 1.52–3.52 | [1.52–3.52](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_baseline/7446529.json) | 18.655–38.061 |
| 24 kHz | BPSK · BCH | warm | 10.24–15.12 | [9.92–15.12](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_warm/7446529.json) | 9.434–12.586 |
| 24 kHz | BPSK · BCH | time | 0.32–2.80 | [0.32–2.80](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_time/7446529.json) | 18.396–84.085 |
| 24 kHz | BPSK · BCH | compact | 5.12–10.16 | [5.12–10.16](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_compact/7446529.json) | 13.989–22.823 |
| 24 kHz | BPSK · BCH | combined | 20.64–25.20 | [20.64–25.20](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_bpsk_bch_high_lat_disturbed_combined/7446529.json) | 9.123–11.500 |
| 24 kHz | QPSK · BCH | baseline | 2.24–7.36 | [2.24–7.36](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_baseline/7446529.json) | 20.308–31.871 |
| 24 kHz | QPSK · BCH | warm | 19.04–26.40 | [19.04–26.40](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_warm/7446529.json) | 5.354–12.041 |
| 24 kHz | QPSK · BCH | time | 0.96–2.56 | [0.96–2.56](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_time/7446529.json) | 44.125–51.223 |
| 24 kHz | QPSK · BCH | compact | 7.28–8.96 | [7.28–8.96](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_compact/7446529.json) | 16.746–27.446 |
| 24 kHz | QPSK · BCH | combined | 38.00–46.48 | [38.00–46.48](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/E2_disturbed_24000_qpsk_bch_high_lat_disturbed_combined/7446529.json) | 4.483–7.062 |

### Simulated channel E2/A2 — frequency diversity

Each branch occupies 0.4B. Separations are B/2, B/2 + 137 Hz, and 0.55B + 137 Hz. Both copies traverse one physical two-path realization; they are not independent fading channels. Each single-copy control has the full transmit power. All use BPSK+BCH and the compact authenticated path. Off-preset delays test sensitivity to the exact 7 ms echo.

| Band | Spacing | Trace | Lower fresh bit/s | Upper fresh bit/s | Both fresh bit/s | Both maximum silence, s |
| --- | --- | --- | --- | --- | --- | --- |
| 10 kHz | commensurate | moderate | 0.00–0.11 | 0.00 | [0.00–0.11](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_commensurate_both_high_lat_moderate/7446529.json) | 160.475–289.229 |
| 10 kHz | commensurate | disturbed | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | 100.000 |
| 10 kHz | commensurate | 6.75ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_commensurate_both_6.75ms/7446529.json) | 100.000 |
| 10 kHz | commensurate | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_commensurate_both_7.25ms/7446529.json) | 100.000 |
| 10 kHz | offset137 | moderate | 0.00 | 0.00–0.11 | [0.00–0.19](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_offset137_both_high_lat_moderate/7446529.json) | 212.066–236.881 |
| 10 kHz | offset137 | disturbed | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_offset137_both_high_lat_disturbed/7446529.json) | 100.000 |
| 10 kHz | offset137 | 6.75ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_offset137_both_6.75ms/7446529.json) | 100.000 |
| 10 kHz | offset137 | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_offset137_both_7.25ms/7446529.json) | 100.000 |
| 10 kHz | wide137 | moderate | 0.00–0.11 | 0.00 | [0.00–0.11](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_wide137_both_high_lat_moderate/7446529.json) | 141.610–212.066 |
| 10 kHz | wide137 | disturbed | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_10000_diversity_wide137_both_high_lat_disturbed/7446529.json) | 100.000 |
| 10 kHz | wide137 | 6.75ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_wide137_both_6.75ms/7446529.json) | 100.000 |
| 10 kHz | wide137 | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_10000_diversity_wide137_both_7.25ms/7446529.json) | 100.000 |
| 24 kHz | commensurate | moderate | 22.80–27.01 | 23.39–24.19 | [35.20–37.31](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_commensurate_both_high_lat_moderate/7446529.json) | 5.748–8.441 |
| 24 kHz | commensurate | disturbed | 0.00 | 0.00–0.32 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_commensurate_both_high_lat_disturbed/7446529.json) | 41.216–100.000 |
| 24 kHz | commensurate | 6.75ms | 0.00 | 0.00 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_commensurate_both_6.75ms/7446529.json) | 76.529–100.000 |
| 24 kHz | commensurate | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_commensurate_both_7.25ms/7446529.json) | 100.000 |
| 24 kHz | offset137 | moderate | 20.80–24.40 | 22.61–24.51 | [34.99–39.68](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_offset137_both_high_lat_moderate/7446529.json) | 6.317–9.198 |
| 24 kHz | offset137 | disturbed | 0.00 | 0.00 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_offset137_both_high_lat_disturbed/7446529.json) | 98.368–100.000 |
| 24 kHz | offset137 | 6.75ms | 0.00–0.32 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_offset137_both_6.75ms/7446529.json) | 100.000 |
| 24 kHz | offset137 | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_offset137_both_7.25ms/7446529.json) | 100.000 |
| 24 kHz | wide137 | moderate | 20.64–22.29 | 21.01–23.17 | [33.47–36.72](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_wide137_both_high_lat_moderate/7446529.json) | 5.682–7.821 |
| 24 kHz | wide137 | disturbed | 0.00 | 0.00–0.32 | [0.00–0.32](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/E2_disturbed_24000_diversity_wide137_both_high_lat_disturbed/7446529.json) | 53.725–100.000 |
| 24 kHz | wide137 | 6.75ms | 0.00–0.32 | 0.00–0.32 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_wide137_both_6.75ms/7446529.json) | 100.000 |
| 24 kHz | wide137 | 7.25ms | 0.00 | 0.00 | [0.00](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/A2_disturbed_24000_diversity_wide137_both_7.25ms/7446529.json) | 100.000 |

## Simulated channel B5 — serial naamah measurements

2.1 ms applies to added processing and buffering. Total latency and the matched intrinsic transmission/modem reference remain separate. Previous values below are the preceding AEAD campaign for the same twelve named configurations; the additional twelve cases exercise the actual 7 ms equalizer span. Null channel, twelve seconds each; no concurrent validation on naamah.

| Case | Previous added p99.9 ms | Added p99.9 ms | Total p99.9 ms | Intrinsic p99.9 ms | TX / RX per-block p99.9 ms | Result |
| --- | --- | --- | --- | --- | --- | --- |
| [B5_10000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_16qam_null/7446529.host.json) | 1.008624 | 1.001345 | 79.014 | 78.792 | 0.082395 / 0.800084 | pass |
| [B5_10000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_16qam_polar_span_null/7446529.host.json) | 0.969823 | 1.002393 | 84.057 | 83.687 | 0.081735 / 2.024671 | pass |
| [B5_10000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_64qam_null/7446529.host.json) | 1.048407 | 1.005667 | 72.045 | 71.917 | 0.082316 / 0.804552 | pass |
| [B5_10000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_64qam_polar_span_null/7446529.host.json) | 1.078016 | 1.045866 | 77.036 | 76.562 | 0.082286 / 1.997219 | pass |
| [B5_10000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_qpsk_null/7446529.host.json) | 0.968812 | 0.970007 | 116.003 | 115.354 | 0.080602 / 0.758936 | pass |
| [B5_10000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_10000_qpsk_polar_span_null/7446529.host.json) | 0.983144 | 0.990392 | 127.003 | 126.604 | 0.080532 / 2.002599 | pass |
| [B5_24000_16qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_16qam_null/7446529.host.json) | 1.094368 | 1.185843 | 34.008 | 33.083 | 0.325636 / 0.952924 | pass |
| [B5_24000_16qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_16qam_polar_span_null/7446529.host.json) | 1.094295 | 1.143468 | 35.086 | 34.042 | 0.280872 / 2.226333 | pass |
| [B5_24000_64qam_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_64qam_null/7446529.host.json) | 1.117963 | 1.126220 | 26.886 | 26.000 | 0.293816 / 0.960838 | pass |
| [B5_24000_64qam_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_64qam_polar_span_null/7446529.host.json) | 1.115913 | 1.196315 | 32.202 | 31.167 | 0.279589 / 2.186568 | pass |
| [B5_24000_qpsk_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_qpsk_null/7446529.host.json) | 1.028078 | 1.040038 | 48.007 | 47.250 | 0.284378 / 0.957392 | pass |
| [B5_24000_qpsk_polar_span_null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_24000_qpsk_polar_span_null/7446529.host.json) | 1.082405 | 1.083864 | 53.070 | 52.521 | 0.321468 / 2.204522 | pass |
| [B5_disturbed_10000_8psk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_8psk_bch_latency/7446529.host.json) | — | 0.998468 | 117.991 | 117.188 | 0.088678 / 2.669361 | pass |
| [B5_disturbed_10000_8psk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_8psk_soft_latency/7446529.host.json) | — | 1.035731 | 125.030 | 124.917 | 0.087285 / 2.600080 | pass |
| [B5_disturbed_10000_bpsk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_bpsk_bch_latency/7446529.host.json) | — | 0.964090 | 192.003 | 191.625 | 0.102765 / 2.587917 | pass |
| [B5_disturbed_10000_bpsk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_bpsk_soft_latency/7446529.host.json) | — | 0.987923 | 260.006 | 259.437 | 0.104939 / 2.598166 | pass |
| [B5_disturbed_10000_qpsk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_qpsk_bch_latency/7446529.host.json) | — | 0.979242 | 128.005 | 127.479 | 0.087776 / 2.594259 | pass |
| [B5_disturbed_10000_qpsk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_10000_qpsk_soft_latency/7446529.host.json) | — | 0.978018 | 139.010 | 138.687 | 0.087315 / 2.596323 | pass |
| [B5_disturbed_24000_8psk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_8psk_bch_latency/7446529.host.json) | — | 1.152895 | 82.077 | 81.354 | 0.464238 / 6.067871 | pass |
| [B5_disturbed_24000_8psk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_8psk_soft_latency/7446529.host.json) | — | 1.175143 | 90.105 | 89.896 | 0.482753 / 6.217234 | pass |
| [B5_disturbed_24000_bpsk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_bpsk_bch_latency/7446529.host.json) | — | 1.113785 | 142.114 | 141.875 | 0.482182 / 6.149486 | pass |
| [B5_disturbed_24000_bpsk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_bpsk_soft_latency/7446529.host.json) | — | 1.172982 | 174.037 | 173.958 | 0.480669 / 6.239266 | pass |
| [B5_disturbed_24000_qpsk_bch_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_qpsk_bch_latency/7446529.host.json) | — | 1.147627 | 92.001 | 91.146 | 0.467725 / 6.217124 | pass |
| [B5_disturbed_24000_qpsk_soft_latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/B5_disturbed_24000_qpsk_soft_latency/7446529.host.json) | — | 1.160182 | 141.122 | 140.979 | 0.481431 / 6.218126 | pass |

Receiver-call timing is a separate finding: the largest per-block RX p99.9 is 6.239 ms and the largest observed RX call is 14.010 ms. Training runs in bursts. Delivered-message latency passes do not prove a one-millisecond audio-callback deadline. This single-thread fixture creates source messages when its loop runs; scheduling delays before creation are outside its creation-to-delivery metric. Physical audio buffering still requires validation.

## Simulated channel A8 / D6 — authenticated delivery

| SIR dB | Delivered | Authentication failures | Foreign/corrupt delivered | Result |
| --- | --- | --- | --- | --- |
| -10 | 19 | 373 | 0 | pass |
| +0 | 19 | 0 | 0 | pass |
| +10 | 388 | 0 | 0 | pass |

D6 rejects 31 mutations, 8 same-session replays and 8 old-epoch records. Two sender processes produce 16 distinct nonces; no unverified plaintext reaches the sink. In compact format the epoch is implicit authenticated context, so old-epoch records count as authentication failures. Coordinated rotation remains unimplemented.

## Simulated channel E1 — determinism and power

Three repeated message runs have byte-identical canonical JSON. Seeded model/RF determinism also runs in the security selection. Host timings are excluded from byte equality and retained in separate files. Power audit: {'characterized': 16, 'pass': 881}; lower/upper/both audit: {'pass': 72}; diversity/full-band audit: {'pass': 36}. See [POWER.json](POWER.json) for every measured ratio and its complete source parameters. The numerical tolerance is the existing 2%; it is not a new channel acceptance threshold.

## Simulated channel remaining test groups

| Group | Status counts |
| --- | --- |
| A2 | {'characterized': 360} |
| A4 | {'xfail': 1, 'THRESHOLD_TBD': 1} |
| A8 | {'pass': 3} |
| B1 | {'pass': 4, 'xfail': 1} |
| B4 | {'pass': 3} |
| B5 | {'pass': 24} |
| C2 | {'THRESHOLD_TBD': 9, 'xfail': 1, 'pass': 1} |
| C4 | {'pass': 37} |
| D3 | {'xfail': 1} |
| D4 | {'pass': 97} |
| D6 | {'pass': 1, 'xfail': 1} |
| E1 | {'pass': 3} |
| E2 | {'characterized': 360} |

## Simulated channel — Defects found

| Case | Assertion | Reason |
| --- | --- | --- |
| [A4_10000_64qam_drift_10min](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/A4_10000_64qam_drift_10min/7446529.json) | sync_held (xfail) | With warm recovery and elapsed-time prediction, 10 kHz 64-QAM loses lock 1112 times in the ten-minute residual-drift trace; first loss is at 304 s. Carrier correction remains off. |
| [B1_24000_64qam_-20dB_1_100](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/B1_24000_64qam_-20dB_1_100/7446529.json) | sync_held (xfail) | With warm recovery and elapsed-time prediction, 24 kHz 64-QAM loses lock once in the -20 dB / 1 ms attack / 100 ms decay trace. |
| [C2_24000_acquire_0dB](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/C2_24000_acquire_0dB/7446529.json) | acquired (xfail) | At the requested low SNR, the receiver detects the preamble but loses lock without validating a header. |
| [D3_auction_flood](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/D3_auction_flood/7446529.json) | no_starvation (xfail) | Policy conflict: strict bid priority permits starvation during an endless higher-bid flood; Adam rejected increasing priority with age. No cross-key expiry/decay interval is approved. |
| [D6_key_rotation](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/D6_key_rotation/7446529.json) | rotation_supported (xfail) | Both 25-byte and fiber-selected 13-byte authenticated headers retain key IDs, full GCM tags and durable epochs; two-key overlap and coordinated mid-stream retirement remain unimplemented. |

The prior nine-case security ledger is rerun with the new profile. This selection also includes C2 acquisition/noise tests, so its total is not obtained simply by subtracting fixed cases from nine. `validation-meta/CLASSIFICATION.json` records reviewed expected-failure changes; it changes no observations or thresholds. Receiver CPU bursts above are a separate characterization finding, not a newly invented acceptance assertion.

## Simulated channel — Open thresholds

| Threshold | Proposed approach | Reason |
| --- | --- | --- |
| A4.ber_delta: THRESHOLD_TBD | 0 absolute excess BER in the noise-free regression; select a confidence interval for noisy runs | No radio residual-offset budget or BER margin is specified. |
| C2.acquisition_seconds: THRESHOLD_TBD | one complete preamble/training/header plus one audio block | The configured startup lengths give a measurable lower bound; approval needed. |
| C3.recovery_frames: THRESHOLD_TBD | 2 frames after a new valid epoch preamble | The current stream needs an epoch preamble to reacquire; a deadline without one is undefined. |
| C4.pattern_ber_margin: THRESHOLD_TBD | a paired confidence interval, with its significance level selected by Adam | Equal finite-sample BER is not a statistical scrambler test. |
| D1.newest_latency_ms: THRESHOLD_TBD | one frame duration + 2.1 ms, as proposed in the brief | Needs agreement on whether serialization, FEC lookahead and startup are included. |
| D2.freshness_agreement_ms: THRESHOLD_TBD | compare paired freshness distributions; select a quantile margin | Equal survival fractions do not imply equal burst structure. |
| D2.target_survival_margin: THRESHOLD_TBD | select a confidence interval for channel calibration; direct erasures round to the nearest whole frame | A finite SNR grid cannot guarantee exactly 30%, 50%, or 80% channel survival. |
| D3.instrument_delay_ms: THRESHOLD_TBD | one frame duration + 2.1 ms | Strict bid priority and starvation freedom can conflict under sustained overload. |
| D6.rotation_loss_frames: THRESHOLD_TBD | one epoch startup plus the in-flight frame | There is no coordinated rotation protocol to measure yet. |
| E3.memory_growth_bytes: THRESHOLD_TBD | zero steady growth after warmup; choose an allocator/RSS allowance | Host RSS varies and includes harness allocations. |
| E3.queue_depth: THRESHOLD_TBD | configured ring capacity plus one pending auction bid | Must distinguish queue capacity from newest-message freshness. |
| E3.latency_change: THRESHOLD_TBD | a paired percentile tolerance chosen from baseline variability | Exact equality across different fading realizations is not a usable acceptance rule. |

## Simulated channel runtime and limitations

| Selection | Tier | Cases | Seconds | Budget |
| --- | --- | --- | --- | --- |
| [security](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/EXECUTION-full-selection-579c28cf947b.json) | full | 5 | 0.775 | within 1800 s |
| [security](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/security/EXECUTION-quick-selection-1689839064d9.json) | quick | 30 | 37.186 | within 120 s |
| [polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/EXECUTION-full-selection-44e135a0d6fd.json) | full | 252 | 1585.918 | within 1800 s |
| [polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/EXECUTION-full-selection-8ae0ee6545b0.json) | full | 252 | 86.511 | within 1800 s |
| [polar](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/polar/EXECUTION-quick-selection-2433251de72d.json) | quick | 72 | 2.895 | within 120 s |
| [diversity](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/EXECUTION-full-selection-749f54076f0d.json) | full | 108 | 387.915 | within 1800 s |
| [diversity](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity/EXECUTION-full-selection-91b0710b1a1a.json) | full | 108 | 695.652 | within 1800 s |
| [diversity-null](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/diversity-null/EXECUTION-quick.json) | quick | 54 | 6.979 | within 120 s |
| [naamah-latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/EXECUTION-full-selection-e0c3768dd14a.json) | full | 18 | 236.381 | within 1800 s |
| [naamah-latency](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/naamah-latency/EXECUTION-quick-selection-7ea5357da775.json) | quick | 6 | 76.518 | within 120 s |
| [repeat](https://github.com/adamdeprince/goblin-cannon/blob/main/results/disturbed-recovery/repeat/EXECUTION-quick-selection-843865096b62.json) | quick | 3 | 0.179 | within 120 s |

**Runtime finding:** the selected full channel workloads on avx10 total 45.95 minutes, exceeding the 30-minute tier target. Every declared seed, duration and grid point was retained. Individual invocation budget labels above must not be read as a whole-tier pass.

**Runtime finding:** selected quick invocations total 123.757 seconds across both hosts, exceeding the 120-second tier target. A complete quick-tier run under two minutes has not been established.

Sum of selected invocation wall times: {'full': 2993.1508784038015, 'quick': 123.75700955744833}. Selections are not the complete A1–E4 tiers; a per-invocation pass does not establish a whole-tier runtime. No counts or durations were reduced.

These are simulated channels, not measured route availability. The 24 kHz use extends beyond F.1487's validated bandwidth scope. Local usable-time proxies are not STAC audit definitions. No physical audio device/network socket, recorded-band noise, or four-hour soak is included. This change adds no frequency tracker, new code family, or new modulation; it refines existing conventional RLS/training/diversity and OpenSSL GCM. The existing US/international-family patent screen is not a legal clearance opinion.

### Simulated channel — questions for Adam

- All unapproved thresholds above remain open.
- Strict priority still permits lower-bid starvation; no age-based priority boost was added.
- Coordinated overlapping-key rotation remains separate work.
- Recorded-band noise and actual radio/audio-device validation still need inputs/hardware.

Tested source SHA-256: `bc8baf1d34eb61216f9949c8b3a22e6e225b6c4d80a912df3a380a9b4125b6b1`. Base commit `d2ab901f56d69037298eb698385f1a7e474664ec` plus the saved source snapshot identifies the measured worktree.
