# LANDGUARD wiring and calibration

**This is a provisional pin reference, not a verified netlist of the photographed circuit.** Confirm each assignment and module pin label against the assembled build before powering.

## Pin reference used by the integrated sketch

| Component / signal | ESP32 connection | Notes |
|---|---|---|
| SH1106 OLED SDA | GPIO21 | Intended I2C connection |
| SH1106 OLED SCL | GPIO22 | Shared bus with MPU6050 |
| MPU6050 SDA/SCL | GPIO21 / GPIO22 | Sketch expects address 0x68 |
| Soil moisture AO | GPIO34 | Provisional ADC input |
| Soil moisture DO | Not read | Earlier notes associate GPIO26 with this signal; confirm it against actual wiring |
| Rain module AO | GPIO35 | Provisional ADC input |
| Digital vibration output | GPIO27 | Active-low with INPUT_PULLUP by default; change polarity if needed |
| Status LED | GPIO18 through 220–330 ohm series resistor | Provisional assignment |
| Active buzzer / driver signal | GPIO25 | Provisional assignment; use driver if required |

GPIO26 is deliberately not assigned to the LED in the current sketch because earlier project notes associate it with the soil sensor's digital output. All grounds must be common. ESP32 GPIO/ADC pins must not receive signals above 3.3 V.

## Power and output safety

- Follow each module's rated supply voltage.
- Disconnect power before changing wiring.
- Use a 220–330 ohm series resistor for a discrete LED.
- Use a transistor/driver if buzzer current exceeds safe GPIO capability.
- The output test assumes active-high LED and active buzzer; passive piezo buzzers may require tone/PWM.

## Calibration constants

SOIL_DRY_RAW, SOIL_WET_RAW, RAIN_WET_RAW, RAIN_RAW_LOWER_WHEN_WET, moisture thresholds, tilt thresholds, motion thresholds, and vibration polarity are demonstration assumptions. Record repeated readings in known dry/wet conditions and with controlled tilt/motion, then adjust. Calculated moisture percentage is relative, not calibrated volumetric water content.

## Four-state alert behavior

- SAFE: LED and buzzer off.
- WATCH: slow LED pulse; buzzer off.
- WARNING: steady LED with periodic short chirp.
- CRITICAL: faster repeated LED flashes and buzzer pulses.

This is prototype logic, not a validated geotechnical risk model. The supplied photo/video document the bench/model build but do not prove every feature was tested.
