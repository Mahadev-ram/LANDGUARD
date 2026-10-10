// LANDGUARD LED + active-buzzer output test
// Use a series resistor for the LED. If buzzer current exceeds GPIO limits,
// use a transistor/driver module. Assumes active-high outputs.
const int LED_PIN = 26;
const int BUZZER_PIN = 25;
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); digitalWrite(BUZZER_PIN, LOW);
  Serial.println("LANDGUARD LED + BUZZER TEST");
}
void loop() {
  Serial.println("SAFE: both OFF");
  digitalWrite(LED_PIN, LOW); digitalWrite(BUZZER_PIN, LOW); delay(2000);
  Serial.println("WARNING: LED ON, short buzzer chirps");
  digitalWrite(LED_PIN, HIGH);
  for (int i=0; i<3; ++i) { digitalWrite(BUZZER_PIN, HIGH); delay(120); digitalWrite(BUZZER_PIN, LOW); delay(650); }
  Serial.println("DANGER: LED ON, faster repeated alarm");
  digitalWrite(LED_PIN, HIGH);
  for (int i=0; i<8; ++i) { digitalWrite(BUZZER_PIN, HIGH); delay(200); digitalWrite(BUZZER_PIN, LOW); delay(200); }
}
