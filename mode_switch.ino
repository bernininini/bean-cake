#define MODE_SWITCH_PIN 12

void setup() {
  Serial.begin(115200);
  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  bool mode = digitalRead(MODE_SWITCH_PIN);
  Serial.println(mode ? "REMOTE MODE" : "BOT MODE");
  delay(500);
}
