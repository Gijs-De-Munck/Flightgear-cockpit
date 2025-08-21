#ifndef __FETCHDATA_HPP
#define __FETCHDATA_HPP

#include <Arduino.h>

void fetchdata(float &altitude, float &heading, float &sink, float &airspeed, float &temperature);
float errorCorrection(float &value, float &previousValue, float maxDeviation);

#endif