# Project overview

## Purpose

LANDGUARD is a low-cost ESP32 prototype for experimenting with soil-moisture, rain, tilt/motion, and alert outputs on a small slope model. Sensor readings are presented on an OLED display, with an LED and buzzer intended to make changes in the prototype's state visible and audible.

It is an educational prototype, not a certified or field-validated landslide early-warning system.

## Current implementation

The repository contains an integrated sketch for the ESP32, SH1106 OLED, MPU6050, soil/rain analog inputs, a digital vibration input, an LED, and an active buzzer. Separate sketches are included for the MPU6050, OLED integration, analog inputs, LED/buzzer outputs, and I²C scanning.

The integrated sketch implements four simplified software states: **SAFE, WATCH, WARNING, and CRITICAL**. These are demonstration rules based on provisional sensor thresholds, not a geotechnically validated risk model. The MPU6050 acceleration-change magnitude is only a rough motion proxy.

## Hardware references

- [Component coverage](components.md)
- [Wiring and calibration notes](../hardware/WIRING.md)
- [Provisional wiring diagram](../hardware/LANDGUARD-provisional-wiring.svg)
- [Test sequence](../tests/README.md)

## Development and validation status

The team previously reported that the OLED and MPU6050 worked in separate standalone tests. The supplied prototype photo and compact demonstration video document the physical bench/model setup. They do not prove that the shared I²C bus, every sensor threshold, or the LED/buzzer behavior has passed full integration testing.

The pin map and thresholds must be checked against the actual circuit. Remaining validation includes compiling/uploading the integrated sketch, checking the shared I²C bus, testing the output signals, and recording repeatable dry/wet and tilt/motion trials.

## Scope and safety

The prototype is suitable for learning about embedded sensing, basic data presentation, and threshold-driven outputs. Do not use it as the basis for evacuation or other safety-critical decisions. Operational landslide-monitoring claims would require validated instruments, appropriate geotechnical modelling, and sustained field testing.
