# LANDGUARD 🌧️⛰️

**A low-cost ESP32-based landslide risk monitoring prototype**

## Overview

LANDGUARD is a prototype designed to monitor selected environmental and ground-movement indicators associated with potential landslide conditions.

The system is being developed using an ESP32 microcontroller and multiple sensors, with a small OLED display intended to present sensor readings and system status.

## Objectives

- Monitor soil moisture and rainfall indicators.
- Measure changes in orientation and acceleration using an MPU6050.
- Detect vibration events.
- Display sensor readings and a prototype risk status.
- Provide visual and audible alerts when configured thresholds are exceeded.

## Hardware

- ESP32 development board
- SH1106 128×64 OLED display
- MPU6050 accelerometer and gyroscope
- Soil moisture sensor
- Rain sensor
- Vibration sensor
- LEDs and buzzer
- Connecting wires and breadboard

## Development Status

**Status: In development**

Individual modules are being tested before integration. The combined hardware, sensor thresholds, display interface, and alert behavior still require validation.

## Repository Structure

- `src/` — integrated firmware
- `tests/` — individual hardware test sketches
- `docs/` — project documentation
- `hardware/` — wiring and circuit diagrams
- `media/` — prototype and test photographs

## Limitations

LANDGUARD is an educational prototype, not a certified landslide early-warning system. Sensor readings and threshold-based alerts require calibration and field validation. It must not be relied upon as the sole basis for safety decisions.

## License

See the `LICENSE` file for the project's license.
