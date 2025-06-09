#define L_JOY_VRX 36
#define L_JOY_VRY 35
#define L_JOY_SW  34
#define R_JOY_VRX 33
#define R_JOY_VRY 32
#define R_JOY_SW  14

void setup() {
  Serial.begin(115200);
  pinMode(L_JOY_SW, INPUT_PULLUP);
  pinMode(R_JOY_SW, INPUT_PULLUP);
}

void loop() {
  int lx = analogRead(L_JOY_VRX);
  int ly = analogRead(L_JOY_VRY);
  int lsw = digitalRead(L_JOY_SW);
  int rx = analogRead(R_JOY_VRX);
  int ry = analogRead(R_JOY_VRY);
  int rsw = digitalRead(R_JOY_SW);
  Serial.printf("L: (%d, %d, %d) | R: (%d, %d, %d)\n", lx, ly, lsw, rx, ry, rsw);
  delay(200);
}
