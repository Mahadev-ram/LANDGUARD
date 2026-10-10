# Hardware test sketches

Upload one sketch at a time in Arduino IDE. Choose the ESP32 board profile matching your board and set Serial Monitor to 115200 baud.

## Recommended order

1. [I2C scanner](05_i2c_scanner/i2c_scanner.ino) — check responding devices on SDA GPIO21 / SCL GPIO22.
2. [MPU6050 standalone test](01_mpu6050_test/mpu6050_test.ino) — check initialization and acceleration readings.
3. [MPU6050 + OLED test](02_mpu6050_oled/mpu6050_oled.ino) — check the sensor/display combination.
4. [Soil/rain raw-read test](03_mpu_soil_rain_oled/mpu_soil_rain_oled.ino) — record analog readings in controlled dry/wet conditions.
5. [LED + buzzer test](04_led_buzzer_test/led_buzzer_test.ino) — exercises SAFE, WATCH, WARNING, and CRITICAL outputs independently of sensors.
6. [Integrated firmware](../src/landguard_full/landguard_full.ino) — try only after checking wiring and individual modules.

## LED and buzzer connections used by the test

| Component | Test pin | Connection note |
|---|---|---|
| LED | GPIO18 (provisional) | GPIO → 220–330 ohm resistor → LED anode; cathode → GND |
| Active buzzer/driver signal | GPIO25 (provisional) | Signal → GPIO25, module GND → common GND; use a driver if needed |

These are software assumptions, not a verified map of the pictured circuit. Confirm the wiring and module pin labels first. The test assumes active-high outputs; a passive piezo may require tone/PWM.

## Libraries

The MPU6050/OLED sketches require Adafruit MPU6050, Adafruit Unified Sensor, Adafruit BusIO, and U8g2. The LED/buzzer test and I2C scanner use built-in Arduino/ESP32 APIs only.

## Recording evidence

For each test, record the physical wiring, observed Serial Monitor/display result, and pass/fail status. A committed sketch is not proof of a passed hardware test. Never mark a test as passed until observed on the physical circuit.

Soil/rain mapping, tilt levels, and acceleration-change thresholds are examples. The acceleration-change value is a rough MPU6050-derived proxy, not a calibrated seismic measurement.
