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
            static float previousAltitude = 0; // Static variable to hold the previous altitude value
            altitude = value.toFloat();
            errorCorrection(altitude, previousAltitude, 100);
            previousAltitude = altitude;
        } 
        if (command == "hdg") {
            static float previousHeading = 0; // Static variable to hold the previous heading value
            heading = value.toFloat();
            errorCorrection(heading, previousHeading, 10);
            previousHeading = heading;
        }
        if (command == "sink") {
            static float previousSink = 0; // Static variable to hold the previous sink value
            sink = value.toFloat();
            errorCorrection(sink, previousSink, 0.5);
            previousSink = sink;
        }
        if (command == "ias") {
            static float previousAirspeed = 0; // Static variable to hold the previous airspeed value
            airspeed = value.toFloat();
            errorCorrection(airspeed, previousAirspeed, 5);
            previousAirspeed = airspeed;
        }
        if (command == "temp") {
            static float previousTemperature = 0; // Static variable to hold the previous temperature value
            temperature = value.toFloat();
            errorCorrection(temperature, previousTemperature, 2);
            previousTemperature = temperature;
        }
    }
}

float errorCorrection(float &value, float &previousValue, float maxDeviation) {
    if(abs(value - previousValue) > maxDeviation) {
        value = previousValue;
        // previousValue remains unchanged
    }
    return value;
}