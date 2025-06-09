#define AIN1 15
#define AIN2 16
#define PWMA 14
#define BIN1 12
#define BIN2 13
#define PWMB 4
#define STBY 10

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);  // Enable motors
}

void loop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 200);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 200);

  delay(2000);

  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  delay(1000);
}
