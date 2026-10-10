# Hardware components

LANDGUARD is a bench/model-scale educational prototype built around an ESP32. This page distinguishes the intended hardware role from what the current sketch actually implements.

## Hardware

- ESP32 development board
- SH1106 128×64 OLED
- MPU6050 accelerometer/gyroscope module
- Analog soil-moisture module
- Analog rain sensor module
- LED and active buzzer
- A separate digital vibration module appears in the project concept/prototype, but it is not currently read by the integrated sketch.
- Breadboard, jumper wires, and slope-model materials

## Current code coverage

| Component | Current sketch coverage | Important limitation |
|---|---|---|
| SH1106 OLED | Yes | Combined I²C operation still needs physical confirmation |
| MPU6050 | Yes | Tilt and acceleration-change thresholds are illustrative |
| Soil analog output | Yes, GPIO34 | Dry/wet mapping must be calibrated |
| Rain analog output | Yes, GPIO35 | Active direction and wet threshold must be calibrated |
| LED | Yes, GPIO26 | Confirm pin and use series resistor |
| Active buzzer | Yes, GPIO25 | Confirm polarity/current; a driver may be needed |
| Dedicated digital vibration module | No | Pin and output polarity have not been confirmed |

## I²C

The sketches initialize I²C with SDA GPIO21 and SCL GPIO22. The MPU6050 is requested at address 0x68. The OLED and MPU6050 have each been reported as working individually; simultaneous operation should be checked with the [I²C scanner](../tests/05_i2c_scanner/i2c_scanner.ino) and combined test before treating the bus as verified.

## Electrical caution

ESP32 GPIO/ADC pins must not receive signals above 3.3 V. Use a common ground, match module voltage requirements, add an LED series resistor, and use a transistor/driver if the buzzer current is too high for a GPIO.

See [wiring and calibration](../hardware/WIRING.md), the [provisional diagram](../hardware/LANDGUARD-provisional-wiring.svg), and [test instructions](../tests/README.md).