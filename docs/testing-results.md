# Test status and results

## Evidence available

- The project team previously reported a standalone OLED test and a standalone MPU6050 test as working independently.
- The supplied prototype photo and compact demonstration video show the bench/model prototype.
- Repeatable test sketches are included for MPU6050, OLED integration, soil/rain raw ADC values, LED/buzzer outputs, and I²C scanning.

## Current verification status

| Test | Repository status | Still required |
|---|---|---|
| Standalone MPU6050 | Previously reported working independently | Retain upload/serial evidence for the final submission |
| Standalone OLED | Previously reported working independently | Retain display evidence for the final submission |
| OLED + MPU6050 together | Not confirmed by earlier recorded tests | Run I²C scanner and combined sketch on the real circuit |
| Soil moisture / rain analog readings | Test sketch provided | Confirm raw values and dry/wet direction on actual modules |
| Digital vibration module | Added to current integrated sketch on provisional GPIO27 | Confirm module pinout, signal polarity, and physical triggering |
| LED + buzzer | Standalone output test and integrated output logic are provided | Upload output test and observe each output pattern physically |
| Integrated firmware | Present in repository; not compiled or hardware-tested here | Compile/upload and check every sensor/output on the assembled prototype |
| Calibration / threshold behavior | Pending | Record repeated dry/wet and controlled tilt/motion trials |

The media files document the physical build, but code, a wiring illustration, or a photo does not prove that an associated test passed. No field validation or reliable landslide prediction is claimed.
