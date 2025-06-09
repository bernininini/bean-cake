#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   9
#define TFT_DC   10
#define TFT_RST  8
#define TFT_MOSI 11
#define TFT_SCK  13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST, TFT_SCK, TFT_MOSI, -1);

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(20, 50);
  tft.println("BEAN-CAKE READY");
}

void loop() {}
