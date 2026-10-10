# Wiring and circuit notes

## Purpose

This document records the current known wiring context for the LANDGUARD prototype and explains what is known versus what remains pending. It is intentionally conservative and does not claim a final schematic or completed hardware design.

## Current known configuration

The following hardware relationship is confirmed for the present test setup:

- SH1106 OLED and MPU6050 share the same I²C bus
- SDA: GPIO21
- SCL: GPIO22

This means the OLED and MPU6050 are currently treated as coexisting I²C peripherals in the test configuration.

## What is not yet finalized

The following details remain unconfirmed in the current project documentation:
- final pin assignments for the soil moisture sensor
- final pin assignments for the rain sensor
- final pin assignments for the vibration sensor
- final pin assignments for the LEDs
- final pin assignments for the buzzer
- final power distribution scheme
- final ground and signal routing layout
- final circuit diagram for a complete integrated prototype

Because of this, no final circuit diagram is provided here.

## Recommended working approach

For the present stage:
- keep the I²C bus wiring for OLED and MPU6050 clearly documented
- validate each sensor individually before final integration
- test power stability before full assembly
- avoid assuming final wiring until hardware verification is complete
- maintain a hardware test notebook for each module

## Safety and caution

This is a prototype project, not a field-deployed industrial system. Breadboard wiring, power wiring, and prototype sensor hookups should be checked carefully before powering the system. Electrical protection, proper grounding, and test-environment safety remain important considerations.

## Documentation status

This document is intentionally a placeholder for the integration phase rather than a final hardware blueprint. The complete circuit board design and final pin map are still pending.

## Related documents

- [Project overview](project-overview.md)
- [Hardware components](components.md)
- [Working principle](working-principle.md)
- [Testing status and results](testing-results.md)
