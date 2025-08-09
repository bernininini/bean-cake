//arduino UNO w 2 joysticks sending over serial

void setup() {
  Serial.begin(115200);
}

void loop() {
  int joy1X = analogRead(A0);
  int joy1Y = analogRead(A1);
  int joy2X = analogRead(A2);
  int joy2Y = analogRead(A3);

  Serial.print(joy1X);
  Serial.print(",");
  Serial.print(joy1Y);
  Serial.print(",");
  Serial.print(joy2X);
  Serial.print(",");
  Serial.println(joy2Y);

  delay(50);
}
