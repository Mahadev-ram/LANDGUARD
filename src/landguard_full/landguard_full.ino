#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>
#include <math.h>

// LANDGUARD educational prototype. Thresholds are demonstration values only.
Adafruit_MPU6050 mpu;
bool mpuReady = false;
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE, 22, 21);
const int SOIL_PIN=34, RAIN_PIN=35, LED_PIN=26, BUZZER_PIN=25;
const int SOIL_DRY_RAW=3000, SOIL_WET_RAW=1300, RAIN_WET_RAW=1800;
const bool RAIN_RAW_LOWER_WHEN_WET=true;
const int SOIL_WARNING=60, SOIL_DANGER=80, WET_SOIL_RAIN_DANGER=70;
const float TILT_WARNING_DEG=10.0, TILT_DANGER_DEG=20.0;
const float VIBRATION_WARNING=2.0, VIBRATION_DANGER=4.0;
const unsigned long VIBRATION_HOLD_MS=1500;
int soilRaw=0, rainRaw=0, soilPercent=0; bool rainDetected=false;
float ax=0, ay=0, az=0, rollDeg=0, pitchDeg=0, tiltDeg=0, vibration=0;
float baselineRoll=0, baselinePitch=0, gravityX=0, gravityY=0, gravityZ=0;
unsigned long lastWarningVibration=0, lastDangerVibration=0, lastSensorRead=0;
unsigned long lastDisplayUpdate=0, lastSerialUpdate=0, lastBuzzerChange=0;
int riskLevel=0; // 0 SAFE, 1 WARNING, 2 DANGER; simplified prototype states
bool buzzerOn=false;
const unsigned long SENSOR_INTERVAL=50, DISPLAY_INTERVAL=250, SERIAL_INTERVAL=500;

void calculateAngles(float x,float y,float z,float &roll,float &pitch) {
  roll=atan2(y,z)*180.0/PI;
  pitch=atan2(-x,sqrt(y*y+z*z))*180.0/PI;
}
float angleDifference(float current,float baseline) {
  float d=current-baseline;
  while(d>180.0)d-=360.0; while(d< -180.0)d+=360.0; return d;
}
void calibrateMPU() {
  if(!mpuReady)return;
  oled.clearBuffer(); oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0,20,"Calibrating MPU..."); oled.drawStr(0,36,"Keep device still"); oled.sendBuffer();
  const int samples=40; float rollSum=0,pitchSum=0,xSum=0,ySum=0,zSum=0;
  for(int i=0;i<samples;i++) {
    sensors_event_t a,g,temp; mpu.getEvent(&a,&g,&temp); float r,p;
    calculateAngles(a.acceleration.x,a.acceleration.y,a.acceleration.z,r,p);
    rollSum+=r; pitchSum+=p; xSum+=a.acceleration.x; ySum+=a.acceleration.y; zSum+=a.acceleration.z; delay(50);
  }
  baselineRoll=rollSum/samples; baselinePitch=pitchSum/samples;
  gravityX=xSum/samples; gravityY=ySum/samples; gravityZ=zSum/samples;
}
void readSensors() {
  soilRaw=analogRead(SOIL_PIN); rainRaw=analogRead(RAIN_PIN);
  if(SOIL_DRY_RAW!=SOIL_WET_RAW) { soilPercent=map(soilRaw,SOIL_DRY_RAW,SOIL_WET_RAW,0,100); soilPercent=constrain(soilPercent,0,100); }
  rainDetected=RAIN_RAW_LOWER_WHEN_WET?(rainRaw<=RAIN_WET_RAW):(rainRaw>=RAIN_WET_RAW);
  if(!mpuReady) { tiltDeg=NAN; vibration=NAN; return; }
  sensors_event_t a,g,temp; mpu.getEvent(&a,&g,&temp);
  ax=a.acceleration.x; ay=a.acceleration.y; az=a.acceleration.z;
  calculateAngles(ax,ay,az,rollDeg,pitchDeg);
  tiltDeg=fmaxf(fabsf(angleDifference(rollDeg,baselineRoll)),fabsf(angleDifference(pitchDeg,baselinePitch)));
  float dx=ax-gravityX,dy=ay-gravityY,dz=az-gravityZ; vibration=sqrtf(dx*dx+dy*dy+dz*dz);
  const float alpha=0.08; gravityX+=alpha*(ax-gravityX); gravityY+=alpha*(ay-gravityY); gravityZ+=alpha*(az-gravityZ);
  unsigned long now=millis(); if(vibration>=VIBRATION_WARNING)lastWarningVibration=now; if(vibration>=VIBRATION_DANGER)lastDangerVibration=now;
}
void evaluateRisk() {
  unsigned long now=millis();
  bool soilWarning=soilPercent>=SOIL_WARNING,soilDanger=soilPercent>=SOIL_DANGER;
  bool tiltWarning=mpuReady&&tiltDeg>=TILT_WARNING_DEG,tiltDanger=mpuReady&&tiltDeg>=TILT_DANGER_DEG;
  bool vibrationWarning=mpuReady&&(now-lastWarningVibration<=VIBRATION_HOLD_MS);
  bool vibrationDanger=mpuReady&&(now-lastDangerVibration<=VIBRATION_HOLD_MS);
  bool danger=soilDanger||tiltDanger||vibrationDanger||(rainDetected&&soilPercent>=WET_SOIL_RAIN_DANGER);
  bool warning=soilWarning||rainDetected||tiltWarning||vibrationWarning||!mpuReady;
  riskLevel=danger?2:(warning?1:0);
}
void updateAlarm() {
  unsigned long now=millis(); digitalWrite(LED_PIN,riskLevel==0?LOW:HIGH);
  if(riskLevel==0) { digitalWrite(BUZZER_PIN,LOW); buzzerOn=false; lastBuzzerChange=0; return; }
  // WARNING: short chirp at intervals; DANGER: faster repeated alarm.
  unsigned long onTime=(riskLevel==2)?250:100,offTime=(riskLevel==2)?250:1500;
  if(!buzzerOn) { if(lastBuzzerChange==0||now-lastBuzzerChange>=offTime) { digitalWrite(BUZZER_PIN,HIGH); buzzerOn=true; lastBuzzerChange=now; } }
  else if(now-lastBuzzerChange>=onTime) { digitalWrite(BUZZER_PIN,LOW); buzzerOn=false; lastBuzzerChange=now; }
}
void updateDisplay() {
  oled.clearBuffer(); oled.setFont(u8g2_font_6x10_tf); oled.drawStr(0,9,"LANDGUARD MONITOR");
  oled.setCursor(0,20); oled.print("Status: ");
  if(!mpuReady)oled.print("CHECK MPU"); else if(riskLevel==2)oled.print("DANGER!"); else if(riskLevel==1)oled.print("WARNING"); else oled.print("SAFE");
  oled.setCursor(0,31); oled.print("Soil:"); oled.print(soilPercent); oled.print("% Raw:"); oled.print(soilRaw);
  oled.setCursor(0,41); oled.print("Rain:"); oled.print(rainDetected?"YES":"NO"); oled.print(" Raw:"); oled.print(rainRaw);
  oled.setCursor(0,51); oled.print("Tilt:"); if(mpuReady)oled.print(tiltDeg,1);else oled.print("N/A");
  oled.print(" Vib:"); if(mpuReady)oled.print(vibration,1);else oled.print("N/A");
  oled.setCursor(0,62); if(!mpuReady)oled.print("Check MPU wiring");else if(riskLevel==2)oled.print("DANGER - PROTOTYPE");else if(riskLevel==1)oled.print("Warning - Check");else oled.print("Monitoring active");
  oled.sendBuffer();
}
void printSerialData() {
  Serial.println("-----------------------------");
  Serial.print("Soil raw: ");Serial.print(soilRaw);Serial.print(" | Moisture estimate: ");Serial.print(soilPercent);Serial.println("%");
  Serial.print("Rain raw: ");Serial.print(rainRaw);Serial.print(" | Rain detected: ");Serial.println(rainDetected?"YES":"NO");
  if(mpuReady) {
    Serial.print("Accel X: ");Serial.print(ax,2);Serial.print(" | Y: ");Serial.print(ay,2);Serial.print(" | Z: ");Serial.println(az,2);
    Serial.print("Tilt change: ");Serial.print(tiltDeg,2);Serial.println(" deg");
    Serial.print("Acceleration-change magnitude: ");Serial.print(vibration,2);Serial.println(" m/s^2");
  } else Serial.println("MPU6050: N/A");
  Serial.print("Risk: "); if(!mpuReady)Serial.println("WARNING - CHECK MPU");else if(riskLevel==2)Serial.println("DANGER");else if(riskLevel==1)Serial.println("WARNING");else Serial.println("SAFE");
}
void setup() {
  Serial.begin(115200); delay(1000); pinMode(LED_PIN,OUTPUT); pinMode(BUZZER_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW); digitalWrite(BUZZER_PIN,LOW); analogReadResolution(12);
  Wire.begin(21,22); Wire.setClock(100000); oled.begin(); oled.clearBuffer(); oled.setFont(u8g2_font_6x10_tf);
  oled.drawStr(0,20,"LANDGUARD MONITOR");oled.drawStr(0,36,"Starting...");oled.sendBuffer();
  if(mpu.begin(0x68,&Wire)) {
    mpuReady=true; Serial.println("MPU6050 INITIALIZED!");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);mpu.setGyroRange(MPU6050_RANGE_500_DEG);mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);calibrateMPU();
  } else { mpuReady=false; Serial.println("MPU6050 INITIALIZATION FAILED!"); }
  pinMode(SOIL_PIN,INPUT);pinMode(RAIN_PIN,INPUT);Serial.println("LANDGUARD prototype started.");
  readSensors();evaluateRisk();updateDisplay();
}
void loop() {
  unsigned long now=millis();
  if(now-lastSensorRead>=SENSOR_INTERVAL){lastSensorRead=now;readSensors();evaluateRisk();}
  updateAlarm();
  if(now-lastDisplayUpdate>=DISPLAY_INTERVAL){lastDisplayUpdate=now;updateDisplay();}
  if(now-lastSerialUpdate>=SERIAL_INTERVAL){lastSerialUpdate=now;printSerialData();}
}
