#include <fetchdata.hpp>
#include <Arduino.h>

void fetchdata(float &altitude, float &heading, float & sink, float &airspeed, float &temperature) {
    if (Serial.available() > 10) { // Wait until there are enough bytes available
        String command;
        String value;
        char lastChar = '\0';

    // Read characters until '=' is found, storing the command name
        while (lastChar != '=' && Serial.available() > 0) {
            lastChar = Serial.read();
            if (lastChar != '=')
                command += lastChar;
        }

    // Read the remaining characters until newline '\n', storing the value
        while (lastChar != '\n' && Serial.available() > 0) {
            lastChar = Serial.read();
            if (lastChar != '\n')
                value += lastChar;
        }
        // Process different commands
        if (command == "alt") {
            altitude = value.toFloat();
        } 
        if (command == "hdg") {
            heading = value.toFloat();
        }
        if (command == "sink") {
            sink = value.toFloat();
        }
        if (command == "ias") {
            airspeed = value.toFloat();
        }
        if (command == "temp") {
            temperature = value.toFloat();
        }
    }
}