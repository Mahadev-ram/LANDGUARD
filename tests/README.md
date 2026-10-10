# LANDGUARD hardware tests

Each Arduino sketch is a separate sketch. Select the ESP32 board profile and set Serial Monitor to **115200 baud**.

## Test order

1. [MPU6050 standalone test](01_mpu6050_test/mpu6050_test.ino) — initialization and accelerometer readings.
2. [MPU6050 + OLED test](02_mpu6050_oled/mpu6050_oled.ino) — displays readings on SH1106 OLED using the shared I²C bus.
3. [MPU6050 + OLED + soil/rain raw readings](03_mpu_soil_rain_oled/mpu_soil_rain_oled.ino) — raw ADC values and MPU readings; confirm real wiring matches the provisional pins.
4. [LED + buzzer output test](04_led_buzzer_test/led_buzzer_test.ino) — tests output patterns without depending on the sensors.
5. [I²C scanner](05_i2c_scanner/i2c_scanner.ino) — scans GPIO21/22; confirm OLED and MPU6050 addresses before integrated operation.
6. [Integrated firmware](../src/landguard_full/landguard_full.ino) — use only after individual tests and wiring checks.

## LED and buzzer wiring

| Component | ESP32 | Notes |
|---|---|---|
| LED anode | GPIO26 through a 220 Ω series resistor | LED cathode to GND |
| Active buzzer signal | GPIO25 | Buzzer GND to common GND; use driver if current exceeds GPIO limits |

The output test assumes active-high outputs. A passive piezo buzzer may require a tone/PWM signal rather than a steady HIGH.

## Libraries

MPU6050/OLED sketches require Adafruit MPU6050, Adafruit Unified Sensor, Adafruit BusIO, and U8g2. LED/buzzer and I²C scanner sketches use built-in Arduino/ESP32 APIs only.

## Test evidence

A code file in GitHub is not proof of a passed hardware test. For each test, record the exact wiring, board/library versions, expected behavior, observed output, and result only after observing it. Integrated firmware thresholds are examples only.
