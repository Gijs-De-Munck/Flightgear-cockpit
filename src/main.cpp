#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <evario.hpp>
#include <instruments.hpp>

MCUFRIEND_kbv tft;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0); // Portrait
  //draw static vario face
  tft.fillScreen(TFT_BLACK);
  tft.drawCircle(160, 160, 140, TFT_WHITE);
  tft.fillRect(160, 0, 180, 320, TFT_BLACK);
  tft.drawLine(160, 20, 240, 20, TFT_WHITE);
  tft.drawLine(160, 300, 240, 300, TFT_WHITE);
}

void loop() {
    float sink = -4;
    float temperature = 25;
    float MC = 2;
    float altitude = 100;
    updateEVario(tft, sink, temperature, MC, altitude);
}