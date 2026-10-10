# Tests

This folder is intended for hardware and software testing notes related to the LANDGUARD prototype.

## Purpose

The project is currently in the hardware integration stage. Individual tests should be kept simple, documented, and isolated from final system assumptions.

## Current testing focus

Planned or in-progress validation areas include:
- OLED display operation
- MPU6050 communication and motion readings
- soil moisture sensor behavior
- rain sensor behavior
- vibration sensor behavior
- LED and buzzer response
- I²C bus integrity
- basic power stability

## Important status note

Hardware integration and testing are still in progress. No final test results or calibrated values are included in this repository.

## Recommended test discipline

- test one module at a time
- record observations clearly
- keep sensor notes separate from final design claims
- avoid using tentative results as final project evidence
- do not assign final pin mappings until hardware validation is complete

## Related documentation

- [Project overview](../docs/project-overview.md)
- [Hardware components](../docs/components.md)
- [Wiring and circuit notes](../docs/wiring-and-circuit.md)
- [Testing status and results](../docs/testing-results.md)
