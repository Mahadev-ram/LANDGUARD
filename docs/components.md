# Hardware components

LANDGUARD is a bench/model-scale educational prototype built around an ESP32. This page describes the role of each component and what the current firmware actually reads.

## Hardware included in the project

- ESP32 development board
- SH1106 128×64 OLED
- MPU6050 accelerometer/gyroscope module
- Analog soil-moisture module
- Analog rain sensor module
- Digital vibration sensor module
- Status LED and active buzzer
- Breadboard, jumper wires, and slope-model materials

## Coverage in the current integrated sketch

| Component | Code coverage | Notes |
|---|---|---|
| SH1106 OLED | Yes | Shared I²C setup uses SDA 21 / SCL 22 |
| MPU6050 | Yes | Expected address 0x68; tilt/acceleration-change values are provisional |
| Soil sensor analog output | Yes, GPIO34 | Dry/wet calibration is required |
| Rain sensor analog output | Yes, GPIO35 | Wet polarity and threshold are assumptions |
| Digital vibration output | Yes, GPIO27 | Defaults to active-low with INPUT_PULLUP; verify actual module |
| LED | Yes, GPIO18 | Use a series resistor; pin assignment is provisional |
| Active buzzer | Yes, GPIO25 | Confirm current draw; use a driver where needed |

The older notes associated GPIO26 with the soil sensor's digital output. The integrated sketch therefore does **not** use GPIO26 for the LED. Soil DO is not currently read by the main sketch.

## I²C configuration

The sketches initialize I²C with SDA GPIO21 and SCL GPIO22. The MPU6050 is requested at address 0x68. The team previously reported successful standalone tests for the OLED and MPU6050, but successful simultaneous operation should be reconfirmed with the [I²C scanner](../tests/05_i2c_scanner/i2c_scanner.ino) and the combined OLED/MPU test.

## Electrical cautions

ESP32 GPIO/ADC pins must not receive signals above 3.3 V. Use a common ground, follow each module's rated supply, add an LED series resistor, and use a transistor/driver if the buzzer draws more current than a GPIO can safely supply.

See [wiring and calibration](../hardware/WIRING.md), the [provisional wiring diagram](../hardware/LANDGUARD-provisional-wiring.svg), and [test instructions](../tests/README.md).
