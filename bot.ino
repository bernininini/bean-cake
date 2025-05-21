// BEAN-CAKE BOT: ESP32-S3 CAM with motor control and camera stream
#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "BEANCAKE";
const char* pwd = "beancake123";
WiFiUDP udp;

#define IN1 12
#define IN2 13
#define IN3 14
#define IN4 15
#define ENA 2
#define ENB 4

int spdL = 0;
int spdR = 0;

void stM(int l, int r) {
  analogWrite(ENA, abs(l));
  digitalWrite(IN1, l > 0);
  digitalWrite(IN2, l < 0);
  analogWrite(ENB, abs(r));
  digitalWrite(IN3, r > 0);
  digitalWrite(IN4, r < 0);
}

void hndUDP() {
  int p = udp.parsePacket();
  if (p) {
    char d[8];
    udp.read(d, 8);
    spdL = (d[0] << 8) | d[1];
    spdR = (d[2] << 8) | d[3];
    stM(spdL, spdR);
  }
}

void stWiFi() {
  WiFi.softAP(ssid, pwd);
  udp.begin(1234);
}

void stPWM() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  ledcAttachPin(ENA, 0); ledcSetup(0, 1000, 8);
  ledcAttachPin(ENB, 1); ledcSetup(1, 1000, 8);
}

void stCam() {
  camera_config_t cfg;
  cfg.ledc_channel = LEDC_CHANNEL_0;
  cfg.ledc_timer = LEDC_TIMER_0;
  cfg.pin_d0 = 5; cfg.pin_d1 = 18; cfg.pin_d2 = 19; cfg.pin_d3 = 21;
  cfg.pin_d4 = 36; cfg.pin_d5 = 39; cfg.pin_d6 = 34; cfg.pin_d7 = 35;
  cfg.pin_xclk = 0; cfg.pin_pclk = 22; cfg.pin_vsync = 25; cfg.pin_href = 23;
  cfg.pin_sscb_sda = 26; cfg.pin_sscb_scl = 27; cfg.pin_pwdn = 32;
  cfg.pin_reset = -1; cfg.pin_xclk = 0;
  cfg.xclk_freq_hz = 20000000;
  cfg.pixel_format = PIXFORMAT_JPEG;
  cfg.frame_size = FRAMESIZE_QVGA;
  cfg.jpeg_quality = 10;
  cfg.fb_count = 1;
  esp_camera_init(&cfg);
  server.on("/cam", HTTP_GET, [](AsyncWebServerRequest *r){
    camera_fb_t *f = esp_camera_fb_get();
    r->send_P(200, "image/jpeg", f->buf, f->len);
    esp_camera_fb_return(f);
  });
  server.begin();
}

void setup() {
  stPWM();
  stWiFi();
  stCam();
}

void loop() {
  hndUDP();
}
