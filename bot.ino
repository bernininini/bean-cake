#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "ESP32-CAM";
const char* pass = "12345678";

WiFiUDP u;
int p = 1234;

#define A1 14
#define A2 15
#define PWMA 12
#define B1 13
#define B2 2
#define PWMB 4

void m(int p1, int d1, int d2, int p) {
  digitalWrite(d1, p1 > 0);
  digitalWrite(d2, p1 < 0);
  analogWrite(p, abs(p1));
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, pass);
  u.begin(p);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  int pLen = u.parsePacket();
  if (pLen) {
    char b[20];
    u.read(b, sizeof(b));
    int l = 0, r = 0;
    sscanf(b, "%d,%d", &l, &r);
    m(l, A1, A2, PWMA);
    m(r, B1, B2, PWMB);
  }
}
