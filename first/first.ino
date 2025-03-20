#define LED_PIN 12

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1);
  digitalWrite(LED_PIN, LOW);
  delay(5);
}
