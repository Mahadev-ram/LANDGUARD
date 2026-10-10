#include <Wire.h>
void setup(){Serial.begin(115200);Wire.begin(21,22);Wire.setClock(100000);Serial.println("LANDGUARD I2C SCANNER");}
void loop(){byte found=0;Serial.println("Scanning I2C bus...");for(byte a=1;a<127;a++){Wire.beginTransmission(a);byte e=Wire.endTransmission();if(e==0){Serial.print("I2C device found at 0x");if(a<16)Serial.print('0');Serial.println(a,HEX);found++;}}if(!found)Serial.println("No I2C devices found; check power, GND, SDA/SCL.");Serial.println("Scan complete. Repeat in 3 seconds.\n");delay(3000);}
