# LANDGUARD

**Low-cost ESP32 landslide-monitoring educational prototype** using environmental readings, an MPU6050 motion sensor, an OLED display, an LED, and a buzzer.

![LANDGUARD prototype on a model slope](media/prototype-overview.jpg)

[View the supplied demo video](media/LANDGUARD-demo.mp4)

> **Safety and scope:** LANDGUARD is a bench/model-scale educational prototype, not a certified or field-validated landslide early-warning system. Thresholds are illustrative until calibrated. Never use this prototype as the basis for evacuation or other safety-critical decisions.

## What is included

- ESP32 firmware with SH1106 OLED, MPU6050, soil/rain analog inputs, LED and active-buzzer patterns.
- Separate sketches for MPU6050, OLED integration, analog input checks, LED/buzzer outputs, and I²C scanning.
- A provisional wiring diagram and calibration/safety notes.
- Project documentation and supplied prototype media.

## Source code

| File | Purpose |
|---|---|
| [Integrated sketch](src/landguard_full/landguard_full.ino) | OLED + MPU6050 + soil/rain AO + LED + active buzzer |
| [MPU6050 test](tests/01_mpu6050_test/mpu6050_test.ino) | Check MPU initialization and accelerometer readings |
| [MPU6050 + OLED test](tests/02_mpu6050_oled/mpu6050_oled.ino) | Test readings on the SH1106 display |
| [Soil/rain raw-read test](tests/03_mpu_soil_rain_oled/mpu_soil_rain_oled.ino) | Inspect analog readings with OLED/MPU present |
| [LED + buzzer test](tests/04_led_buzzer_test/led_buzzer_test.ino) | Exercise SAFE, WARNING, and DANGER output patterns |
| [I²C scanner](tests/05_i2c_scanner/i2c_scanner.ino) | Find connected I²C device addresses |
| [Wiring diagram (SVG)](hardware/LANDGUARD-provisional-wiring.svg) | Provisional connection overview |
| [Wiring and calibration notes](hardware/WIRING.md) | Assumptions, power limits, and calibration guidance |

Each `.ino` file is a separate Arduino sketch. Start with the individual tests in the [test instructions](tests/README.md) before attempting the integrated sketch.

## Hardware and provisional pin map

| Function | GPIO / interface in the current integrated sketch |
|---|---|
| SH1106 OLED and MPU6050 | I²C SDA 21, SCL 22; MPU address expected at 0x68 |
| Soil moisture analog output | GPIO34 |
| Rain sensor analog output | GPIO35 |
| Status LED | GPIO26 through a series resistor (e.g. 220 Ω) |
| Active buzzer signal | GPIO25 |
| Dedicated digital vibration module | Not currently integrated in the main sketch |

**Verify the table against your actual wiring before powering or uploading.** GPIO34/35 and GPIO26/25 are assumed by the firmware but have not been confirmed from a verified netlist. All grounds must be common; ESP32 GPIO/ADC inputs must not receive signals above 3.3 V. Use a driver if the buzzer current exceeds safe GPIO output limits.

## Setup

1. Install the ESP32 board support package for Arduino IDE.
2. Install **Adafruit MPU6050**, **Adafruit Unified Sensor**, **Adafruit BusIO**, and **U8g2** from Library Manager.
3. Select the ESP32 board profile matching your hardware and open one sketch folder at a time.
4. Set Serial Monitor to **115200 baud**.
5. Follow the sequence in [tests/README.md](tests/README.md).

The output test assumes an active-high LED and active buzzer. A passive piezo buzzer may need a tone/PWM signal instead of a steady HIGH.

## Current alert logic

The integrated sketch has three simplified states:

- **SAFE:** LED and buzzer off.
- **WARNING:** LED on with short periodic buzzer chirps.
- **DANGER:** LED on with faster repeated buzzer pulses.

The project report describes a four-state concept (SAFE/WATCH/WARNING/CRITICAL). The current code does **not** implement that exact four-state scheme. The acceleration-change value is an MPU6050-based proxy; the separate digital vibration sensor is not wired into the integrated sketch yet.

## Project documentation

- [Project overview](docs/project-overview.md)
- [Hardware components](docs/components.md)
- [Working principle](docs/working-principle.md)
- [Testing status and results](docs/testing-results.md)
- [Limitations and future scope](docs/limitations-and-future-scope.md)
- [Wiring and calibration](hardware/WIRING.md)

## Validation status

The team previously reported that the OLED and MPU6050 worked in separate standalone tests. The supplied photo and video show the physical bench/model prototype. These do not prove that the combined I²C system, all sensor thresholds, or the newly added LED/buzzer behavior have been fully tested.

The integrated firmware and pin map remain **unverified on the complete physical circuit**. Record real test observations and calibration data before marking any pending test as passed.

## Repository layout

```text
LANDGUARD/
├── README.md
├── LICENSE
├── docs/
│   ├── project-overview.md
│   ├── components.md
│   ├── working-principle.md
│   ├── testing-results.md
│   └── limitations-and-future-scope.md
├── hardware/
│   ├── LANDGUARD-provisional-wiring.svg
│   └── WIRING.md
├── media/
│   ├── prototype-overview.jpg
│   └── LANDGUARD-demo.mp4
├── src/landguard_full/landguard_full.ino
└── tests/
    ├── 01_mpu6050_test/
    ├── 02_mpu6050_oled/
    ├── 03_mpu_soil_rain_oled/
    ├── 04_led_buzzer_test/
    ├── 05_i2c_scanner/
    └── README.md
```

## License

Source code: MIT license. See [LICENSE](LICENSE).