#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <evario.hpp>
#include <instruments.hpp>

MCUFRIEND_kbv tft;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0); // Portrait

  tft.fillScreen(TFT_BLACK);
  tft.drawCircle(160, 160, 140, TFT_WHITE);
  tft.fillRect(160, 0, 180, 320, TFT_BLACK);
}

void loop() {
    float sink = 0;
    float temperature = 0;
    float MC = 0;
    updateEVario(tft, sink, temperature, MC);
}