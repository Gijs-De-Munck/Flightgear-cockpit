#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <evario.hpp>
#include <instruments.hpp>
#include <fetchdata.hpp>
#include <math.h>

MCUFRIEND_kbv tft;

static float sink = 0;
static float temperature = 0;
static float MC = 0;
static float altitude = 0;
static float airspeed = 0;
static float heading = 0;
static float pitch = 0;
static float roll = 0;

void setup() {
  Serial.begin(57600);
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
  updateEVario(tft, sink, temperature, MC, altitude, airspeed);
  fetchdata(altitude, heading, pitch, roll, sink, airspeed);
}