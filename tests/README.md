# Tests

This folder is for isolated hardware test sketches and test notes for the LANDGUARD prototype.

## Standalone tests

The following modules have been tested independently:
- **SH1106 OLED:** standalone display output was observed.
- **MPU6050:** standalone initialization and sensor readings were observed.

The corresponding sketches still need to be committed to this repository so others can reproduce the tests. Until the sketches are added, this README documents the test status but does not itself provide executable tests.

## Current testing focus

- resolve the combined OLED + MPU6050 I²C issue
- add the standalone OLED and MPU6050 sketches
- validate soil moisture, rain, and vibration sensor behavior independently
- verify LED and buzzer response
- check I²C bus integrity and power stability
- integrate and test the complete system incrementally

## Test reporting

For each test, record:
- hardware and wiring used
- sketch and library versions where relevant
- expected behavior
- observed output
- pass/fail status and any issues
- calibration method, if applicable

Do not record a test as passed unless the behavior was actually observed. Raw readings alone do not establish calibrated sensor performance.

## Status

Hardware integration and testing are still in progress. The final firmware, calibrated thresholds, and complete system behavior remain unverified.

## Related documentation

- [Project overview](../docs/project-overview.md)
- [Hardware components](../docs/components.md)
- [Wiring and circuit notes](../docs/wiring-and-circuit.md)
- [Testing status and results](../docs/testing-results.md)
