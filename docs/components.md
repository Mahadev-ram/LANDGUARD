# Hardware components

This page lists the known components used in the current LANDGUARD prototype and describes their intended role. The hardware setup is still evolving, and final pin assignments for all sensors remain pending.

## Core controller

### ESP32
The ESP32 is the main microcontroller for the prototype. It is intended to:
- collect sensor data
- process readings
- manage display output
- control alert behavior
- support future data logging or communication features

The ESP32 is the central processing unit for the project.

## Display

### SH1106 128×64 OLED
The SH1106 display is a compact graphical OLED module used to show:
- sensor readings
- system status
- warnings or alert states
- basic operational information

The OLED has been tested independently. The MPU6050 has also been tested independently. Successful simultaneous operation on the shared I²C bus has not yet been verified; combined-bus debugging is in progress.

Known current I²C configuration for the test setup:
- SDA: GPIO21
- SCL: GPIO22

## Motion sensing

### MPU6050
The MPU6050 is used for motion-related measurements, including:
- acceleration
- orientation changes
- tilt-related movement
- changes in motion that may be useful to prototype vibration detection

The intended shared I²C connections are:
- SDA: GPIO21
- SCL: GPIO22

The standalone MPU6050 test has produced readings, but detection in the combined OLED + MPU6050 sketch is still being debugged. Do not interpret the combined bus as verified yet.

## Environmental sensing

### Soil moisture sensor
A soil moisture sensor is used to estimate relative soil moisture. Increased moisture can be a relevant environmental indicator, but the final thresholds and calibration remain unverified.

### Rain sensor
The rain sensor is intended to detect rainfall-related wetness. Its final interface and calibration details are not yet finalized.

### Vibration sensor
The vibration sensor is intended to detect physical movement or vibration events. Its final integration and electrical interface remain pending.

## Alert hardware

### LEDs
LEDs are intended as visual indicators for prototype status or threshold-triggered warnings. The final arrangement and control logic are still under development.

### Buzzer
The buzzer is intended to provide an audible alert when a configured condition is detected. Its final alert logic remains under development.

## Notes on wiring and final assignments

This repository intentionally avoids inventing final pin assignments for all sensors.

- Intended shared I²C pins for OLED and MPU6050: SDA GPIO21, SCL GPIO22
- Independent OLED and MPU6050 tests have been performed
- Successful simultaneous OLED + MPU6050 operation is not yet verified
- Remaining sensor pin assignments are not finalized
- Full circuit integration is still pending

## Summary

The hardware is intentionally simple and low-cost, with the ESP32 acting as the center of the design. The current implementation is a prototype-level experiment rather than a fully integrated system.

For the full project context, see:
- [Project overview](project-overview.md)
- [Working principle](working-principle.md)
- [Wiring and circuit notes](wiring-and-circuit.md)
- [Testing status](testing-results.md)
