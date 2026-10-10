# Project overview

## Purpose

LANDGUARD is a low-cost ESP32 prototype for experimenting with soil-moisture, rain, tilt/motion, and alert outputs on a small slope model. It combines sensor readings with a local OLED status display and a buzzer/LED output.

It is an educational prototype, not a certified early-warning system or a field-validated landslide prediction solution.

## Current implementation

The repository contains an integrated sketch for the ESP32, SH1106 OLED, MPU6050, soil/rain analog inputs, LED, and active buzzer. It also contains standalone sensor/output tests and an I²C scanner.

The current code implements three simplified internal states: SAFE, WARNING, and DANGER. It uses a change-in-acceleration value from the MPU6050 as a rough motion/vibration proxy. The separate digital vibration sensor mentioned in the project concept is not yet integrated into the main sketch. The report's four-state SAFE/WATCH/WARNING/CRITICAL design is therefore not implemented exactly.

## Hardware references

- [Component coverage](components.md)
- [Wiring and calibration notes](../hardware/WIRING.md)
- [Provisional wiring diagram](../hardware/LANDGUARD-provisional-wiring.svg)
- [Test sequence](../tests/README.md)

## Development and validation status

The team previously reported standalone OLED and MPU6050 tests as working. The supplied prototype image and demo video document the physical bench/model setup. They do not establish that the integrated sketch, complete I²C bus, thresholds, or alert outputs have been fully validated.

Remaining validation includes checking the real pin map, compiling and uploading the integrated sketch, testing each output, measuring raw soil/rain readings under controlled conditions, and documenting repeatable calibration results.

## Scope and safety

The prototype is suitable for learning about embedded sensing, basic data presentation, and threshold-driven outputs. It must not be used for real-world evacuation or other safety decisions. Field validation with appropriate geotechnical expertise would be required before any operational hazard-monitoring claims could be made.