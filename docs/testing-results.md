# Test status and results

## Evidence available

- A standalone OLED test and a standalone MPU6050 test were previously reported as working independently by the project team.
- The supplied prototype photo and video show an assembled bench/model prototype with a display and sensors.
- The repository includes repeatable MPU6050/OLED/raw ADC test sketches and an output test for LED/buzzer.

## Tests still requiring direct confirmation

| Test | Status in repository | What remains to verify |
|---|---|---|
| Standalone MPU6050 | Reported independently working | Keep serial output / upload result as evidence |
| Standalone OLED | Reported independently working | Keep photo/output evidence as evidence |
| OLED + MPU6050 together | Not confirmed by previously recorded test status | Run I²C scanner and combined sketch |
| Soil moisture / rain ADC | Test sketch provided | Confirm wiring, raw values, and wet/dry response |
| Vibration module | Not integrated into current main firmware | Confirm module's digital pin and test it independently |
| LED + buzzer outputs | Test sketch provided | Upload output test and observe physical behavior |
| Full integrated sketch | Not hardware-verified here | Compile/upload and check every feature on assembled prototype |
| Calibration / threshold tests | Pending | Record repeated dry/wet and tilt trials; choose thresholds from data |

Do not interpret repository code, an animated diagram, or a prototype photo as proof of a passed test. No field validation or reliable landslide prediction is claimed.
