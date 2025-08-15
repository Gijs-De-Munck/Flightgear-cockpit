#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <evario.hpp>
#include <instruments.hpp>
#include <fetchdata.hpp>
#include <math.h>
#include <Stepper.h>

MCUFRIEND_kbv tft;

Stepper varioStepper(2048, 36, 32, 34, 30);
Stepper altitudeStepper(2048, 52, 48, 50, 46);
Stepper headingStepper(2048, 44, 40, 42, 38); //set correct stepper pins
Stepper rollStepper(2048, 45, 41, 43, 39); //set correct stepper pins
Stepper airspeedStepper(2048, 53, 49, 51, 47); //set correct stepper pins

static float sink = 0;
static float temperature = 0;
static float MC = 0;
static float altitude = 0;
static float airspeed = 0;
static float heading = 0;
static float pitch = 0;
static float roll = 0;

void setup() {
  Serial.begin(115200);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0); // Portrait
  //draw static vario face
  tft.fillScreen(TFT_BLACK);
  tft.drawCircle(160, 160, 140, TFT_WHITE);
  tft.fillRect(160, 0, 180, 320, TFT_BLACK);
  tft.drawLine(160, 20, 240, 20, TFT_WHITE);
  tft.drawLine(160, 300, 240, 300, TFT_WHITE);
	varioStepper.setSpeed(10);
	altitudeStepper.setSpeed(10);
	headingStepper.setSpeed(10);
	rollStepper.setSpeed(10);
	airspeedStepper.setSpeed(20);
}

void loop() {
  updateEVario(tft, sink, temperature, MC, altitude, airspeed, heading);
  fetchdata(altitude, heading, sink, airspeed, temperature);
	updateInstruments(varioStepper, altitudeStepper, headingStepper, rollStepper, airspeedStepper, altitude, heading, roll, sink, airspeed);
}