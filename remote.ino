// NOTE: This sketch reads 2 analog joysticks, sends UDP motor commands to ESP32-CAM, and shows MJPEG stream on TFT.

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <JPEGDecoder.h>
#include <HTTPClient.h>

#define CS 5
#define DC 2
#define RST 4

Adafruit_ILI9341 d(CS, DC, RST);

const char* ssid = "ESP32-CAM";
const char* pass = "12345678";

const char* h = "http://192.168.4.1:81/stream";
const char* ip = "192.168.4.1";
const int pt = 1234;

WiFiUDP u;
int lx = 34;
int rx = 35;

void setup() {
  Serial.begin(115200);
  d.begin();
  d.setRotation(1);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  u.begin(8888);
}

void loop() {
  int l = analogRead(lx);
  int r = analogRead(rx);
  l = map(l, 0, 4095, -255, 255);
  r = map(r, 0, 4095, -255, 255);
  char msg[20];
  sprintf(msg, "%d,%d", l, r);
  u.beginPacket(ip, pt);
  u.write((const uint8_t*)msg, strlen(msg));
  u.endPacket();
  showVid();
}

void showVid() {
  HTTPClient c;
  c.begin(h);
  int r = c.GET();
  if (r == HTTP_CODE_OK) {
    WiFiClient s = c.getStream();
    if (s) {
      JpegDec.decodeSdFile(s);
      d.drawRGBBitmap(0, 0, JpegDec.pImage, JpegDec.width, JpegDec.height);
    }
  }
  c.end();
}
