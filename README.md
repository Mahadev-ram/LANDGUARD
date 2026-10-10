# LANDGUARD

A low-cost ESP32-based prototype for landslide risk monitoring using motion, soil moisture, rainfall, and vibration sensors.

## Project purpose

LANDGUARD is an educational and prototype-level project intended to monitor environmental and ground-motion conditions that may be associated with landslide risk. The system is designed around an ESP32 microcontroller and a small set of sensors that can provide readings related to moisture, rainfall, vibration, and motion.

This project is not presented as a certified early-warning system or a field-validated landslide monitoring solution. It is intended as a learning-oriented prototype for experimenting with sensor integration, alerting, and data presentation.

## Problem statement

Landslides can be influenced by a combination of factors, including:
- increased soil saturation
- prolonged rainfall
- ground movement or slope instability
- vibration or sudden shifts in terrain conditions

A low-cost monitoring prototype can support research, learning, and testing of basic warning logic by combining several indicator channels into one embedded system.

## Objectives

- Monitor soil moisture conditions
- Detect rainfall-related changes
- Detect vibration and movement-related events
- Measure tilt or acceleration-related motion using an MPU6050
- Display live sensor data on an OLED display
- Trigger visual and audible alerts when configured thresholds are exceeded
- Keep the system simple, low-cost, and suitable for prototyping

## Hardware components

The current project documentation reflects the known hardware in the active prototype setup:

- ESP32 development board
- SH1106 128×64 OLED display
- MPU6050 accelerometer and gyroscope module
- Soil moisture sensor
- Rain sensor
- Vibration sensor
- LEDs
- Buzzer
- Breadboard and connection wires

The OLED and MPU6050 are intended to share the I²C bus in the current test setup:
- SDA: GPIO21
- SCL: GPIO22

The OLED and MPU6050 have each been tested independently. Successful simultaneous operation has not yet been verified.

No final pin assignments are claimed for the remaining sensors in this documentation.

## Proposed operation

The prototype is intended to:
1. Read sensor values from the ESP32
2. Process measurements locally
3. Show status on the OLED display
4. Detect abnormal or threshold-like conditions
5. Trigger LED and buzzer alerts for visual and audible notification

The exact threshold values, risk logic, and final firmware remain pending until hardware integration and calibration are complete.

## Development status

**Status: in progress**

The project is currently in an early hardware and documentation stage. Individual modules are being evaluated before final system integration. Hardware integration and testing are still underway, and the final firmware remains pending.

The repository currently focuses on:
- documentation
- project structure
- hardware context
- testing orientation
- prototype constraints and future improvements

## Repository structure

The following tree reflects files currently present in the repository. The integrated firmware directory and test sketches will be added when the corresponding code is ready to commit.

```text
LANDGUARD/
├── README.md
├── LICENSE
├── .gitignore
├── docs/
│   ├── project-overview.md
│   ├── components.md
│   ├── working-principle.md
│   ├── wiring-and-circuit.md
│   ├── testing-results.md
│   └── limitations-and-future-scope.md
├── tests/
│   └── README.md
├── hardware/
│   └── README.md
└── media/
    └── README.md
```

## Documentation

- [Project overview](docs/project-overview.md)
- [Hardware components](docs/components.md)
- [Working principle](docs/working-principle.md)
- [Wiring and circuit notes](docs/wiring-and-circuit.md)
- [Testing status and results](docs/testing-results.md)
- [Limitations and future scope](docs/limitations-and-future-scope.md)

## Limitations

LANDGUARD is an educational prototype, not a certified landslide early-warning system. It is intended for learning, experimentation, and proof-of-concept evaluation only.

This project does not claim:
- field validation
- certified hazard monitoring accuracy
- proven long-term reliability
- production-ready deployment
- final calibrated thresholds

The system requires careful testing, sensor calibration, and hardware validation before it can be considered for real-world use.

## License

This repository currently uses the MIT License. The license file in the root of the repository should be kept as-is unless project ownership or licensing terms are explicitly changed.

See [LICENSE](LICENSE) for details.

## Notes

This repository is intentionally conservative about claims. Hardware integration, calibration, and firmware implementation are still in progress. No final sensor pin assignments or successful field-ready results are documented here beyond the known current setup details.
