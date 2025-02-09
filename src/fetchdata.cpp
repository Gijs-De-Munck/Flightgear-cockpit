#include <Arduino.h>

void fetchdata(float &altitude, float &heading, float &pitch, float &roll, float & sink, float &airspeed) {
    if (Serial.available() > 14) { // Wait until there are enough bytes available
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
        if (command == "altitude") {
            altitude = value.toFloat();
        } 
        if (command == "heading") {
            heading = value.toFloat();
        } 
        if (command == "pitch") {
            pitch = value.toFloat();
        } 
        if (command == "roll") {
            roll = value.toFloat();
        }
        if (command == "vertical-speed") {
            sink = value.toFloat();
        }
        if (command == "airspeed") {
            airspeed = value.toFloat();
        }
    }
}
