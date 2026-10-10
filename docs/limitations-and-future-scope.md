# Limitations and future scope

## Current prototype limitations

LANDGUARD is a single-node bench/model-scale educational prototype. It is not a certified early-warning system, and it has not been field-validated.

- The integrated sketch uses provisional soil, rain, tilt, and acceleration-change thresholds.
- Moisture percentage is an estimate derived from raw ADC values, not a calibrated volumetric water-content measurement.
- The current motion/vibration feature is an MPU6050 acceleration-change proxy; the separate digital vibration module is not read by the integrated sketch.
- The firmware uses three simplified states (SAFE, WARNING, DANGER), while the report's proposed design describes four states (SAFE, WATCH, WARNING, CRITICAL).
- The integrated sketch and actual GPIO mapping must be checked against the real wiring and compiled/uploaded on the physical assembly.
- An assembled prototype photo/video does not prove all sensor combinations, output behavior, or calibration.
- Breadboard wiring and non-weatherproof sensors are unsuitable for unattended outdoor deployment.

## Engineering constraints

Sensor outputs can vary with supply, mounting, soil composition, corrosion, wiring, and electrical noise. Alert thresholds must be derived from repeated controlled observations. An active buzzer may require a transistor/driver depending on its current draw.

ESP32 GPIO/ADC pins must not receive signals above 3.3 V. Follow each module's supply and wiring requirements, use a common ground, and use a series resistor with discrete LEDs.

## Future improvements

- Verify and publish a complete, pin-by-pin schematic from the assembled circuit.
- Calibrate and document the sensor response using repeatable dry/wet and tilt tests.
- Integrate the dedicated digital vibration sensor with its confirmed module pinout.
- Align firmware's state machine with the four-state report proposal, if that remains a requirement.
- Improve power regulation, connectors, enclosure, and corrosion protection.
- Add long-term logging, multi-node monitoring, and wireless telemetry only after the core sensor behavior is validated.
- Conduct field trials with geotechnical expertise before considering any operational warning use.

## Safety statement

Do not use this prototype as the sole basis for evacuation or other safety-critical decisions. Real-world landslide monitoring requires validated instrumentation, an appropriate geotechnical model, and sustained field evaluation.

## Related files

- [Main README](../README.md)
- [Hardware components](components.md)
- [Working principle](working-principle.md)
- [Test status](testing-results.md)
- [Wiring and calibration](../hardware/WIRING.md)
- [Provisional wiring diagram](../hardware/LANDGUARD-provisional-wiring.svg)
- [Test guide](../tests/README.md)
