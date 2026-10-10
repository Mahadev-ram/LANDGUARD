// LANDGUARD LED + ACTIVE-BUZZER OUTPUT TEST
// Assumptions: LED GPIO18; active buzzer/driver signal GPIO25.
// Use a 220-330 ohm series resistor with a discrete LED.
// Use a driver if buzzer current exceeds safe GPIO capability.
// Passive piezo buzzers may need tone()/PWM instead of steady HIGH.
const int LED_PIN = 18;
const int BUZZER_PIN = 25;
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("LANDGUARD LED + BUZZER TEST");
}
void loop() {
  Serial.println("SAFE: LED OFF, buzzer OFF");
  digitalWrite(LED_PIN, LOW); digitalWrite(BUZZER_PIN, LOW); delay(2000);

  Serial.println("WATCH: slow LED pulse, buzzer OFF");
  digitalWrite(BUZZER_PIN, LOW);
  for (int i = 0; i < 5; ++i) {
    digitalWrite(LED_PIN, HIGH); delay(120);
    digitalWrite(LED_PIN, LOW); delay(1080);
  }

  Serial.println("WARNING: LED ON, periodic chirp");
  digitalWrite(LED_PIN, HIGH);
  for (int i = 0; i < 5; ++i) {
    digitalWrite(BUZZER_PIN, HIGH); delay(120);
    digitalWrite(BUZZER_PIN, LOW); delay(1680);
  }

  Serial.println("CRITICAL: fast LED flashes and buzzer pulses");
  for (int i = 0; i < 12; ++i) {
    digitalWrite(LED_PIN, HIGH); digitalWrite(BUZZER_PIN, HIGH); delay(250);
    digitalWrite(LED_PIN, LOW); digitalWrite(BUZZER_PIN, LOW); delay(250);
  }
}
