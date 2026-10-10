#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>
#include <math.h>

// LANDGUARD educational bench/model prototype.
// Thresholds and non-I2C pin assignments are provisional; calibrate and verify.
Adafruit_MPU6050 mpu;
bool mpuReady = false;
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, 22, 21);

// Provisional pin map: compare with the real wiring before powering.
const int SOIL_PIN = 34;       // soil sensor AO
const int RAIN_PIN = 35;       // rain module AO
const int VIBRATION_PIN = 27;  // digital vibration module, active-low assumption
const int LED_PIN = 18;        // discrete LED through series resistor
const int BUZZER_PIN = 25;     // active buzzer or driver-module signal
const bool VIBRATION_ACTIVE_HIGH = false;

// Example reference readings; replace with repeated measured dry/wet values.
const int SOIL_DRY_RAW = 3000;
const int SOIL_WET_RAW = 1300;
const int RAIN_WET_RAW = 1800;
const bool RAIN_RAW_LOWER_WHEN_WET = true;

const int SOIL_WATCH = 40;
const int SOIL_WARNING = 60;
const int SOIL_CRITICAL = 80;
const int WET_SOIL_CRITICAL = 70;
const float TILT_WATCH_DEG = 5.0;
const float TILT_WARNING_DEG = 10.0;
const float TILT_CRITICAL_DEG = 20.0;
const float ACCEL_CHANGE_WARNING = 2.0;  // rough proxy, not seismic measurement
const float ACCEL_CHANGE_CRITICAL = 4.0;
const unsigned long MOTION_HOLD_MS = 1500;

enum RiskState { SAFE = 0, WATCH = 1, WARNING = 2, CRITICAL = 3 };
RiskState riskState = WATCH;

int soilRaw = 0, rainRaw = 0, soilPercent = 0;
bool rainDetected = false, vibrationDetected = false;
float ax = 0, ay = 0, az = 0;
float tiltChangeDeg = 0, accelChange = 0;
float baselineRoll = 0, baselinePitch = 0;
float gravityX = 0, gravityY = 0, gravityZ = 0;
bool gravityInitialized = false;
unsigned long lastWarningMotion = 0, lastCriticalMotion = 0;
unsigned long lastSensorRead = 0, lastDisplayUpdate = 0, lastSerialUpdate = 0;
const unsigned long SENSOR_INTERVAL_MS = 50;
const unsigned long DISPLAY_INTERVAL_MS = 250;
const unsigned long SERIAL_INTERVAL_MS = 1000;

void calculateAngles(float x, float y, float z, float &roll, float &pitch) {
  roll = atan2(y, z) * 180.0 / PI;
  pitch = atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;
}
float angleDifference(float current, float baseline) {
  float difference = current - baseline;
  while (difference > 180.0) difference -= 360.0;
  while (difference < -180.0) difference += 360.0;
  return difference;
}
void calibrateMPU() {
  if (!mpuReady) return;
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0, 20, "Calibrating MPU...");
  oled.drawStr(0, 36, "Keep device still");
  oled.sendBuffer();

  const int samples = 40;
  float rollSum = 0, pitchSum = 0, xSum = 0, ySum = 0, zSum = 0;
  for (int i = 0; i < samples; ++i) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    float roll = 0, pitch = 0;
    calculateAngles(a.acceleration.x, a.acceleration.y, a.acceleration.z, roll, pitch);
    rollSum += roll; pitchSum += pitch;
    xSum += a.acceleration.x; ySum += a.acceleration.y; zSum += a.acceleration.z;
    delay(50);
  }
  baselineRoll = rollSum / samples;
  baselinePitch = pitchSum / samples;
  gravityX = xSum / samples; gravityY = ySum / samples; gravityZ = zSum / samples;
  gravityInitialized = true;
}
void readSensors() {
  soilRaw = analogRead(SOIL_PIN);
  rainRaw = analogRead(RAIN_PIN);
  vibrationDetected = digitalRead(VIBRATION_PIN) ==
      (VIBRATION_ACTIVE_HIGH ? HIGH : LOW);

  if (SOIL_DRY_RAW != SOIL_WET_RAW) {
    soilPercent = map(soilRaw, SOIL_DRY_RAW, SOIL_WET_RAW, 0, 100);
    soilPercent = constrain(soilPercent, 0, 100);
  }
  rainDetected = RAIN_RAW_LOWER_WHEN_WET
      ? (rainRaw <= RAIN_WET_RAW)
      : (rainRaw >= RAIN_WET_RAW);

  if (!mpuReady) return;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x; ay = a.acceleration.y; az = a.acceleration.z;

  float roll = 0, pitch = 0;
  calculateAngles(ax, ay, az, roll, pitch);
  tiltChangeDeg = fmaxf(fabsf(angleDifference(roll, baselineRoll)),
                        fabsf(angleDifference(pitch, baselinePitch)));
  if (!gravityInitialized) {
    gravityX = ax; gravityY = ay; gravityZ = az;
    gravityInitialized = true;
  }
  float dx = ax - gravityX, dy = ay - gravityY, dz = az - gravityZ;
  accelChange = sqrtf(dx * dx + dy * dy + dz * dz);
  const float alpha = 0.08;
  gravityX += alpha * (ax - gravityX);
  gravityY += alpha * (ay - gravityY);
  gravityZ += alpha * (az - gravityZ);

  const unsigned long now = millis();
  if (vibrationDetected || accelChange >= ACCEL_CHANGE_WARNING) lastWarningMotion = now;
  if (accelChange >= ACCEL_CHANGE_CRITICAL) lastCriticalMotion = now;
}
void evaluateRisk() {
  const unsigned long now = millis();
  const bool soilWatch = soilPercent >= SOIL_WATCH;
  const bool soilWarning = soilPercent >= SOIL_WARNING;
  const bool soilCritical = soilPercent >= SOIL_CRITICAL;
  const bool tiltWatch = mpuReady && tiltChangeDeg >= TILT_WATCH_DEG;
  const bool tiltWarning = mpuReady && tiltChangeDeg >= TILT_WARNING_DEG;
  const bool tiltCritical = mpuReady && tiltChangeDeg >= TILT_CRITICAL_DEG;
  const bool motionWarning = vibrationDetected ||
      (lastWarningMotion != 0 && now - lastWarningMotion <= MOTION_HOLD_MS);
  const bool motionCritical = mpuReady && lastCriticalMotion != 0 &&
      now - lastCriticalMotion <= MOTION_HOLD_MS;

  const bool critical = soilCritical || tiltCritical || motionCritical ||
      (rainDetected && soilPercent >= WET_SOIL_CRITICAL);
  const bool warning = soilWarning || tiltWarning ||
      (soilWatch && rainDetected) ||
      (motionWarning && (rainDetected || soilWatch || tiltWatch));
  const bool watch = soilWatch || rainDetected || tiltWatch || motionWarning;

  if (critical) riskState = CRITICAL;
  else if (warning) riskState = WARNING;
  else if (watch || !mpuReady) riskState = WATCH;
  else riskState = SAFE;
}
const char *riskName() {
  switch (riskState) {
    case SAFE: return "SAFE";
    case WATCH: return "WATCH";
    case WARNING: return "WARNING";
    case CRITICAL: return "CRITICAL";
    default: return "UNKNOWN";
  }
}
void updateAlerts() {
  const unsigned long now = millis();
  switch (riskState) {
    case SAFE:
      digitalWrite(LED_PIN, LOW);
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case WATCH:
      digitalWrite(LED_PIN, (now % 1200UL) < 120UL ? HIGH : LOW);
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case WARNING:
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, (now % 1800UL) < 120UL ? HIGH : LOW);
      break;
    case CRITICAL:
      digitalWrite(LED_PIN, (now % 500UL) < 150UL ? HIGH : LOW);
      digitalWrite(BUZZER_PIN, (now % 500UL) < 250UL ? HIGH : LOW);
      break;
  }
}
void updateDisplay() {
  oled.clearBuffer();
  oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0, 9, "LANDGUARD MONITOR");
  oled.setCursor(0, 20); oled.print("Status: "); oled.print(riskName());
  oled.setCursor(0, 31); oled.print("Soil:"); oled.print(soilPercent); oled.print("% Raw:"); oled.print(soilRaw);
  oled.setCursor(0, 41); oled.print("Rain:"); oled.print(rainDetected ? "YES" : "NO");
  oled.print(" Vib:"); oled.print(vibrationDetected ? "YES" : "NO");
  oled.setCursor(0, 51); oled.print("Tilt:");
  if (mpuReady) oled.print(tiltChangeDeg, 1); else oled.print("N/A");
  oled.print(" AccD:");
  if (mpuReady) oled.print(accelChange, 1); else oled.print("N/A");
  oled.setCursor(0, 62);
  if (!mpuReady) oled.print("MPU CHECK / PROTO");
  else if (riskState == CRITICAL) oled.print("CRITICAL - PROTO");
  else if (riskState == WARNING) oled.print("WARNING - CHECK");
  else if (riskState == WATCH) oled.print("WATCH CONDITIONS");
  else oled.print("Monitoring active");
  oled.sendBuffer();
}
void printSerialData() {
  Serial.println("---- LANDGUARD READINGS ----");
  Serial.print("Soil raw: "); Serial.print(soilRaw);
  Serial.print(" | Estimated moisture: "); Serial.print(soilPercent); Serial.println("%");
  Serial.print("Rain raw: "); Serial.print(rainRaw);
  Serial.print(" | Rain detected: "); Serial.println(rainDetected ? "YES" : "NO");
  Serial.print("Digital vibration: "); Serial.println(vibrationDetected ? "YES" : "NO");
  if (mpuReady) {
    Serial.print("Accel X/Y/Z (m/s^2): "); Serial.print(ax, 2); Serial.print(", ");
    Serial.print(ay, 2); Serial.print(", "); Serial.println(az, 2);
    Serial.print("Tilt change (deg): "); Serial.println(tiltChangeDeg, 2);
    Serial.print("Acceleration-change proxy (m/s^2): "); Serial.println(accelChange, 2);
  } else Serial.println("MPU6050 unavailable; motion values are not valid.");
  Serial.print("Risk state: "); Serial.println(riskName());
}
void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIBRATION_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  analogReadResolution(12);

  Wire.begin(21, 22);
  Wire.setClock(100000);
  oled.begin();
  oled.setFont(u8g2_font_6x10_tf);
  oled.clearBuffer();
  oled.drawStr(0, 20, "LANDGUARD MONITOR");
  oled.drawStr(0, 36, "Starting...");
  oled.sendBuffer();

  if (mpu.begin(0x68, &Wire)) {
    mpuReady = true;
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    Serial.println("MPU6050 initialized.");
    calibrateMPU();
  } else {
    mpuReady = false;
    Serial.println("MPU6050 initialization failed; check bus and address.");
  }
  pinMode(SOIL_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  readSensors();
  evaluateRisk();
  updateDisplay();
}
void loop() {
  const unsigned long now = millis();
  if (now - lastSensorRead >= SENSOR_INTERVAL_MS) {
    lastSensorRead = now;
    readSensors();
    evaluateRisk();
  }
  updateAlerts();
  if (now - lastDisplayUpdate >= DISPLAY_INTERVAL_MS) {
    lastDisplayUpdate = now;
    updateDisplay();
  }
  if (now - lastSerialUpdate >= SERIAL_INTERVAL_MS) {
    lastSerialUpdate = now;
    printSerialData();
  }
}
