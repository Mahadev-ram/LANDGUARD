# Working principle

## Data acquisition

The integrated sketch reads analog values from the soil-moisture input (GPIO34) and rain input (GPIO35). It requests MPU6050 acceleration data over I²C, using SDA GPIO21 and SCL GPIO22. These pin assignments are the sketch's current assumptions and must be checked against actual wiring.

## Tilt and motion estimate

The sketch calculates roll and pitch from accelerometer axes and stores a baseline during startup. It also calculates a smoothed acceleration-change magnitude as a rough motion/vibration proxy. This is not a calibrated vibration or seismic measurement, and motion/tilt thresholds are provisional.

A separate digital vibration sensor is included in the project concept but is not currently read by the integrated sketch.

## Current risk and alert behavior

The integrated code uses three simplified levels:

- **SAFE:** LED off and buzzer off.
- **WARNING:** LED on and intermittent short active-buzzer chirps.
- **DANGER:** LED on and faster repeated buzzer pulses.

Risk classification uses provisional moisture, rain, tilt and acceleration-change thresholds. Those thresholds must be determined from actual repeated tests. The code does not implement the report's four states (SAFE/WATCH/WARNING/CRITICAL) exactly.

## Display and diagnostics

The OLED displays status, raw analog readings, estimated moisture percentage, tilt change, and the acceleration-change metric. The Serial Monitor reports readings and the simplified risk state for inspection.

## Verification boundary

A written algorithm does not prove that the physical device behaves as intended. Confirm the OLED and MPU6050 on the shared bus, check analog response, test LED/buzzer outputs independently, and compare the pin map to the assembled circuit before trying integrated operation.

See [hardware tests](../tests/README.md), [wiring and calibration](../hardware/WIRING.md), and [test status](testing-results.md).

LANDGUARD is an educational prototype and must not be used as a real-world landslide warning system.