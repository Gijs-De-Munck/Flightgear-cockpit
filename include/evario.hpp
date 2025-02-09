#ifndef __EVARIO_HPP
#define __EVARIO_HPP

#include <MCUFRIEND_kbv.h>

void updateEVario(MCUFRIEND_kbv &tft, float sink, float temperature, float MC);
void drawVarioArrow(MCUFRIEND_kbv &tft, float sink);
void writeVarioValue(MCUFRIEND_kbv &tft, float sink);
void drawVarioTriangle(MCUFRIEND_kbv &tft, float sink);
void writeTemperature(MCUFRIEND_kbv &tft, float temperature);
void writeMC(MCUFRIEND_kbv &tft, float MC);

#endif