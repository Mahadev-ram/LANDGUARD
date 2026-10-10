# Limitations and future scope

## Current limitations

LANDGUARD is an early-stage prototype and has several important limitations:

- It is not a certified early-warning system.
- It is not validated for real-world field deployment.
- Sensor thresholds are not yet confirmed.
- Hardware integration is still in progress.
- Final firmware is pending.
- The system has no proven calibration or long-term stability.
- The project should be considered educational and experimental.

## Technical constraints

The project is intentionally low-cost, which makes it accessible, but that also introduces practical trade-offs:
- sensor accuracy may vary
- environmental noise can affect measurements
- wiring and breadboard arrangements can be fragile
- power supply conditions may affect stability
- local calibration will be necessary for useful interpretation

## Operational caution

A prototype such as this should not be used as the sole basis for safety-critical decisions. It is best viewed as a learning platform and a demonstrator for embedded sensing and basic warning logic.

## Future improvements

Potential future improvements include:

- more robust enclosure design
- better power regulation and filtering
- more reliable PCB-based layout
- sensor calibration routines
- improved threshold logic
- data logging to local storage or remote dashboards
- wireless communication for remote alerts
- environmental packaging for outdoor conditions
- stronger display and interface design
- remote monitoring or notification support
- integration with additional sensors for better situational context

## Research and learning value

Despite current limits, the project has educational value:
- it demonstrates sensor integration with an ESP32
- it introduces motion and environmental sensing concepts
- it supports learning about low-cost monitoring systems
- it provides a foundation for future prototype iterations

## Summary

LANDGUARD is a starting point for a low-cost landslide monitoring concept. With proper engineering work, calibration, and field testing, it could evolve into a more capable monitoring system. At the current stage, however, it remains a prototype under development and must be treated as such.

## Related documents

- [Project overview](project-overview.md)
- [Hardware components](components.md)
- [Working principle](working-principle.md)
- [Testing status and results](testing-results.md)
