# Hardware test sketches

Upload **one sketch at a time** using Arduino IDE. Use the ESP32 board profile that matches your board and set Serial Monitor to **115200 baud**.

## Recommended test order

1. [MPU6050 standalone test](01_mpu6050_test/mpu6050_test.ino) — confirms initialization and prints accelerometer readings.
2. [MPU6050 + OLED test](02_mpu6050_oled/mpu6050_oled.ino) — checks the sensor and SH1106 display on I²C.
3. [Soil/rain analog test](03_mpu_soil_rain_oled/mpu_soil_rain_oled.ino) — shows raw AO values for the soil and rain modules.
4. [LED + buzzer test](04_led_buzzer_test/led_buzzer_test.ino) — cycles SAFE (both off), WARNING (LED + short chirps), and DANGER (LED + faster pulses).
5. [I²C scanner](05_i2c_scanner/i2c_scanner.ino) — lists devices responding on SDA GPIO21 / SCL GPIO22.
6. [Integrated sketch](../src/landguard_full/landguard_full.ino) — attempt only after checking individual modules and wiring.

## LED and buzzer connections for the output test

| Component | Pin used by test | Connection note |
|---|---|---|
| LED | GPIO26 | GPIO → series resistor (e.g. 220 Ω) → LED anode; LED cathode → GND |
| Active buzzer | GPIO25 | Signal → GPIO25 and GND → common GND; use a transistor/driver if needed |

These are assumptions used by the sketches, not a verified map for the pictured wiring. Check actual module pin labels and current requirements before connecting power. The output test assumes active-high devices; passive buzzers may need tone/PWM.

## Required libraries

The MPU6050/OLED sketches require **Adafruit MPU6050**, **Adafruit Unified Sensor**, **Adafruit BusIO**, and **U8g2**. The LED/buzzer output test and I²C scanner use built-in Arduino/ESP32 APIs only.

## Recording results

For each test, capture the wiring, observed Serial Monitor output or display, and pass/fail result. Only mark a test passed after observing it on the physical circuit. A source file in the repository is not evidence that it has been successfully uploaded or hardware-tested. The integrated thresholds are demonstration values and require calibration.