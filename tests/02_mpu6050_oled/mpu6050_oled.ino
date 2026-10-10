#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>

Adafruit_MPU6050 mpu;
bool mpuReady = false;
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, 22, 21);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
  Wire.setClock(100000);
  oled.begin();
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0, 20, "MPU6050 Starting...");
  oled.sendBuffer();
  if (mpu.begin(0x68, &Wire)) {
    mpuReady = true;
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("MPU6050 INITIALIZED!");
  } else {
    Serial.println("MPU6050 INITIALIZATION FAILED!");
  }
}
void loop() {
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  if (!mpuReady) {
    oled.drawStr(0, 20, "MPU6050 FAILED!");
    oled.drawStr(0, 38, "Check wiring");
    oled.sendBuffer();
    delay(1000);
    return;
  }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  oled.drawStr(0, 10, "MPU6050 ACCELERATION");
  oled.setCursor(0, 25); oled.print("X: "); oled.print(a.acceleration.x, 2);
  oled.setCursor(0, 38); oled.print("Y: "); oled.print(a.acceleration.y, 2);
  oled.setCursor(0, 51); oled.print("Z: "); oled.print(a.acceleration.z, 2);
  oled.sendBuffer();
  Serial.print("Accel X: "); Serial.print(a.acceleration.x);
  Serial.print(" | Y: "); Serial.print(a.acceleration.y);
  Serial.print(" | Z: "); Serial.println(a.acceleration.z);
  delay(500);
}