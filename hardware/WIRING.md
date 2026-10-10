# LANDGUARD wiring and calibration

The diagram [LANDGUARD-provisional-wiring.svg](LANDGUARD-provisional-wiring.svg) is a provisional reference, not a verified netlist of the photographed build. Compare it with actual module labels and wiring before powering.

| Component | ESP32 connection in supplied sketch | Notes |
|---|---|---|
| SH1106 OLED | SDA GPIO21, SCL GPIO22 | I2C; constructor uses SCL 22, SDA 21 |
| MPU6050 | SDA GPIO21, SCL GPIO22 | Sketch expects address 0x68 |
| Soil moisture module | AO GPIO34 | Analog output must remain within ADC voltage limits |
| Rain module | AO GPIO35 | Direction/threshold must be calibrated |
| LED | GPIO26 through 220 ohm series resistor | Confirm polarity; do not omit resistor |
| Active buzzer module | Signal GPIO25 | Use transistor/driver if current exceeds GPIO capability |
| Vibration module | Not assigned in integrated sketch | Confirm module and wiring before adding a pin |

All grounds must be common. Power each module according to its specifications. ESP32 GPIOs are not 5 V tolerant; never apply 5 V to GPIO or ADC pins.

## Calibration

SOIL_DRY_RAW, SOIL_WET_RAW, RAIN_WET_RAW, RAIN_RAW_LOWER_WHEN_WET, tilt thresholds, and acceleration-change thresholds are demonstration values. Record repeated dry/wet and orientation readings, then tune these constants. The derived moisture percentage is an estimate, not a calibrated volumetric water-content measurement. The MPU6050 acceleration-change metric is not a calibrated seismic measurement.

## Alarm behaviour

- SAFE: LED off, buzzer off.
- WARNING: LED on, brief buzzer chirp at intervals.
- DANGER: LED on, faster repeated buzzer alarm.

The sketch implements three simplified internal levels (SAFE/WARNING/DANGER), not the report's four-level SAFE/WATCH/WARNING/CRITICAL scheme. Thresholds and alarm response are not field-validated. This is an educational prototype and must not be used for real-world hazard decisions.
