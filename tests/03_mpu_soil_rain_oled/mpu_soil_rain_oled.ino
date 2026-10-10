#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>

Adafruit_MPU6050 mpu;
bool mpuReady = false;
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, 22, 21);
const int SOIL_PIN = 34;
const int RAIN_PIN = 35;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
  Wire.setClock(100000);
  analogReadResolution(12);
  oled.begin();
  if (mpu.begin(0x68, &Wire)) {
    mpuReady = true;
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("MPU6050 INITIALIZED!");
  } else Serial.println("MPU6050 INITIALIZATION FAILED!");
}
void loop() {
  int soilRaw = analogRead(SOIL_PIN);
  int rainRaw = analogRead(RAIN_PIN);
  Serial.print("Soil raw: "); Serial.print(soilRaw);
  Serial.print(" | Rain raw: "); Serial.println(rainRaw);
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0, 9, "LANDSLIDE SENSORS");
  oled.setCursor(0, 20); oled.print("Soil raw: "); oled.print(soilRaw);
  oled.setCursor(0, 30); oled.print("Rain raw: "); oled.print(rainRaw);
  if (mpuReady) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    oled.setCursor(0, 41); oled.print("Accel X: "); oled.print(a.acceleration.x, 1);
    oled.setCursor(0, 51); oled.print("Accel Y: "); oled.print(a.acceleration.y, 1);
    oled.setCursor(0, 61); oled.print("Accel Z: "); oled.print(a.acceleration.z, 1);
  } else {
    oled.drawStr(0, 43, "MPU6050 NOT FOUND");
    oled.drawStr(0, 56, "Check I2C wiring");
  }
  oled.sendBuffer();
  delay(500);
}