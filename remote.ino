// BEAN-CAKE REMOTE: Dual joystick UDP sender + MJPEG viewer
#include <WiFi.h>
#include <WiFiUdp.h>
#include <TFT_eSPI.h>
#include <HTTPClient.h>
#include <JPEGDecoder.h>

const char* ssid = "BEANCAKE";
const char* pwd = "beancake123";
IPAddress ip(192, 168, 4, 1);
WiFiUDP udp;

#define joyL A0
#define joyR A3

TFT_eSPI tft = TFT_eSPI();
uint8_t buf[4];

void stWiFi() {
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) delay(100);
}

void txJoy() {
  int jl = analogRead(joyL);
  int jr = analogRead(joyR);
  buf[0] = jl >> 8; buf[1] = jl & 0xFF;
  buf[2] = jr >> 8; buf[3] = jr & 0xFF;
  udp.beginPacket(ip, 1234);
  udp.write(buf, 4);
  udp.endPacket();
}

void stTFT() {
  tft.init(); tft.setRotation(1); tft.fillScreen(TFT_BLACK);
}

void showImg() {
  HTTPClient http;
  http.begin("http://192.168.4.1/cam");
  int c = http.GET();
  if (c == 200) {
    WiFiClient *s = http.getStreamPtr();
    JpegDec.decodeSdFile(*s);
    JpegDec.renderJPEG(0, 0);
  }
  http.end();
}

void setup() {
  stWiFi();
  stTFT();
  udp.begin(1234);
}

void loop() {
  txJoy();
  showImg();
  delay(100);
}
