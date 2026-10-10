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

This display is currently part of the active prototype setup and is communicating over the I²C bus along with the MPU6050.

Known current I²C configuration:
- SDA: GPIO21
- SCL: GPIO22

## Motion sensing

### MPU6050
The MPU6050 is used for motion-related sensing, including:
- acceleration
- orientation changes
- tilt-related movement
- vibration or abrupt motion detection

The module is currently connected to the same I²C bus as the OLED:
- SDA: GPIO21
- SCL: GPIO22

The MPU6050 is a key component for ground-motion awareness in the prototype concept.

## Environmental sensing

### Soil moisture sensor
A soil moisture sensor is used to estimate the water content of the soil. In a landslide-associated context, increased moisture can be a relevant environmental signal.

This sensor provides a low-cost way to observe moisture trends, though the final thresholds and calibration remain unverified.

### Rain sensor
The rain sensor is intended to detect rainfall levels or rainfall-related wetness. It contributes to the system's environmental sensing layer.

The exact final interface and calibration details are not yet finalized.

### Vibration sensor
The vibration sensor is intended to detect physical movement or vibration events that may relate to instability or shifting ground conditions.

The final design and exact electrical interface for this sensor remain pending.

## Alert hardware

### LEDs
LEDs are included as visual indicators. They may be used to signal:
- normal state
- warning level
- alarm state
- system fault or startup status

The final arrangement and control logic are still under development.

### Buzzer
The buzzer is intended to provide an audible alert when a configured condition is detected. It complements the LED warnings and can help draw attention to threshold-triggered states.

## Notes on wiring and final assignments

This repository intentionally avoids inventing final pin assignments for all sensors. Some wiring details are known for the current setup, but the broader prototype circuit is still in progress.

Important:
- OLED and MPU6050 share I²C: SDA GPIO21, SCL GPIO22
- remaining sensor pin assignments are not finalized
- final circuit integration is still pending

## Summary

The hardware is intentionally simple and low-cost, with the ESP32 acting as the center of the design. The current implementation is a prototype-level experiment rather than a fully integrated system.

For the full project context, see:
- [Project overview](project-overview.md)
- [Working principle](working-principle.md)
- [Wiring and circuit notes](wiring-and-circuit.md)
- [Testing status](testing-results.md)
