#include <Arduino.h>
#include <fetchdata.hpp>

void fetchdata(float &altitude, float &sink, float &airspeed) {
    bool gotAltitude = false, gotSink = false, gotAirspeed = false;
    int maxTries = 10; // Maximum tries before moving on

    for (int i = 0; i < maxTries && !gotAltitude; i++) {
        if (Serial.available() > 0) {
            String command, value;
            char lastChar = '\0';

            while (lastChar != '=' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '=') command += lastChar;
            }
            while (lastChar != '\n' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '\n') value += lastChar;
            }

            if (command == "altitude") {
                altitude = value.toFloat();
                gotAltitude = true;
            }
        }
        delay(10); // Small delay to avoid excessive CPU usage
    }

    for (int i = 0; i < maxTries && !gotSink; i++) {
        if (Serial.available() > 0) {
            String command, value;
            char lastChar = '\0';

            while (lastChar != '=' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '=') command += lastChar;
            }
            while (lastChar != '\n' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '\n') value += lastChar;
            }

            if (command == "vertical-speed") {
                sink = value.toFloat();
                gotSink = true;
            }
        }
        delay(10);
    }

    for (int i = 0; i < maxTries && !gotAirspeed; i++) {
        if (Serial.available() > 0) {
            String command, value;
            char lastChar = '\0';

            while (lastChar != '=' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '=') command += lastChar;
            }
            while (lastChar != '\n' && Serial.available() > 0) {
                lastChar = Serial.read();
                if (lastChar != '\n') value += lastChar;
            }

            if (command == "airspeed") {
                airspeed = value.toFloat();
                gotAirspeed = true;
            }
        }
        delay(10);
    }
}
