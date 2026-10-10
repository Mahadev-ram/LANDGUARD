# Working principle

## Overview

LANDGUARD is designed around a basic concept: measure a few environmental and motion-related indicators and interpret them as possible warning signals for unstable ground conditions. The system is intended to collect sensor data, process it locally, and present a simple status on a display with optional visual or audible alerts.

This description reflects the prototype concept and not a validated field algorithm.

## Sensor roles

### Soil moisture monitoring
Soil moisture is a useful environmental indicator because high saturation can increase the likelihood of slope instability or movement when combined with other conditions. The soil moisture sensor is meant to provide data about relative moisture levels.

This can help indicate whether the ground is unusually wet or approaching susceptibility conditions, but actual threshold selection still requires testing and calibration.

### Rainfall monitoring
The rain sensor contributes to rainfall-related measurement. Rainfall is relevant because prolonged or intense rain can alter the soil condition and increase the risk of slope failure.

The project concept uses rainfall as one of the environmental indicators in the overall risk assessment.

### Vibration monitoring
The vibration sensor is intended to detect sudden movement or vibration events. Such signals can be associated with changes in terrain stability or sudden disturbances near the installation site.

The final integration and interpretation logic for vibration data remain under development.

### Motion and tilt monitoring
The MPU6050 is used for motion-related measurements, including acceleration and orientation. The device can help estimate whether the monitored structure or ground is experiencing tilt, displacement, or sudden acceleration changes.

This is one of the more important sensing components for understanding vibration and destabilization patterns.

## Prototype alert logic

The alert concept is simple:
- read sensors
- compare values to configured thresholds
- display the status
- trigger warnings when conditions appear abnormal

The exact threshold logic is not yet confirmed and should not be treated as final. The firmware remains pending until the hardware is validated as a complete system.

## Display behavior

The OLED display is intended to show:
- current sensor values
- a system status indicator
- warning or alarm states
- basic operational diagnostics

This display acts as a simple user interface for the early prototype stage.

## Audio and visual signals

The buzzer and LEDs are intended to provide:
- visual warning indicator
- audible signal for abnormal conditions
- clear feedback for testing and demonstration

These alerts are part of the early prototype concept and are not validated as formal early-warning outputs.

## Important caution

This project uses a practical, educational prototype approach rather than a certified, field-worthy warning system. Sensor readings and alert logic cannot be treated as proven operational thresholds without calibration, integration testing, and safe field validation.

## Related documents

- [Project overview](project-overview.md)
- [Hardware components](components.md)
- [Wiring and circuit notes](wiring-and-circuit.md)
- [Testing status and results](testing-results.md)
