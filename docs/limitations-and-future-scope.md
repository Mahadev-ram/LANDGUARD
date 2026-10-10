# Limitations and future scope

## Current limitations

LANDGUARD is a single-node bench/model-scale educational prototype. It is not a certified warning system and has not been field-validated.

- The integrated sketch uses four simplified software states (SAFE, WATCH, WARNING, CRITICAL), not a validated geotechnical risk model.
- Soil moisture is shown as a relative estimate derived from raw ADC readings, not calibrated volumetric water content.
- Rain polarity and moisture thresholds must be tuned from measurements.
- MPU6050 acceleration-change is a rough motion proxy, not a calibrated seismic/vibration measurement.
- All GPIO assignments beyond the intended I²C wiring are provisional; confirm them against the assembled circuit.
- Combined sensor operation and LED/buzzer response still require hardware testing.
- The photo/video document the prototype appearance, but are not proof that all test cases passed.
- Breadboard wiring and exposed modules are unsuitable for unattended outdoor deployment.

## Technical and electrical constraints

Sensor readings can vary with supply, installation, soil composition, corrosion, wiring and electrical noise. An active buzzer may require a transistor/driver depending on current draw. Use a common ground, follow each module's supply requirements, include an LED series resistor, and never apply signals above 3.3 V to ESP32 GPIO/ADC pins.

## Future improvements

- Confirm and publish a complete pin-by-pin schematic from the actual assembled circuit.
- Calibrate the sensors with repeated, recorded dry/wet and controlled tilt/motion trials.
- Verify shared I²C operation and every LED/buzzer output pattern.
- Improve power regulation, connectors, enclosure, and corrosion protection.
- Add logging or telemetry only after core sensing behavior is repeatable.
- Conduct appropriate field trials with geotechnical expertise before considering any operational warning use.

## Safety statement

Do not use this prototype as the sole basis for evacuation or other safety-critical decisions. Real-world landslide monitoring requires validated instrumentation, appropriate geotechnical analysis, and sustained field evaluation.

## Related files

- [Main README](../README.md)
- [Hardware components](components.md)
- [Working principle](working-principle.md)
- [Test status](testing-results.md)
- [Wiring and calibration](../hardware/WIRING.md)
- [Provisional wiring diagram](../hardware/LANDGUARD-provisional-wiring.svg)
- [Test guide](../tests/README.md)
