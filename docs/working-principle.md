# Working principle

## Data acquisition

The integrated sketch reads the soil-moisture analog output on GPIO34 and rain analog output on GPIO35. It reads the MPU6050 over I²C using SDA GPIO21 and SCL GPIO22, and reads the digital vibration output on GPIO27. Those non-I²C pin assignments are provisional and must be checked against the actual module wiring.

## Motion and tilt estimates

At startup, the sketch samples the MPU6050 while the device is kept still, to establish a baseline. It calculates roll/pitch changes from accelerometer axes and calculates a smoothed acceleration-change magnitude as a rough motion proxy. These are not calibrated seismic measurements, and all thresholds are provisional.

## Four-state prototype alert logic

The current sketch uses these simplified states:

- **SAFE:** LED and buzzer off.
- **WATCH:** slow LED pulse; buzzer off.
- **WARNING:** steady LED with a brief periodic buzzer chirp.
- **CRITICAL:** faster repeated LED flashes and buzzer pulses.

The implementation combines moisture, rain, tilt, acceleration-change, and digital vibration indications. It is intended to demonstrate multi-sensor threshold logic, not to predict or certify an actual landslide risk level.

## Display and diagnostics

The OLED displays the state, raw soil/rain readings, estimated moisture percentage, digital vibration status, tilt change, and acceleration-change value. The Serial Monitor reports sensor readings and the current state.

## Verification boundary

A firmware sketch or schematic does not prove that the physical device behaves as intended. Confirm the actual pin map, shared I²C operation, analog sensor response, vibration module polarity, and LED/buzzer outputs on the assembled circuit. Record test observations before marking the associated test as passed.

See [hardware tests](../tests/README.md), [wiring and calibration](../hardware/WIRING.md), and [test status](testing-results.md).

LANDGUARD is an educational prototype, not a real-world landslide warning system.
