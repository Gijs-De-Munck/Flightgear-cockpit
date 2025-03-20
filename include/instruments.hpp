#ifndef __INSTRUMENTS_HPP
#define __INSTRUMENTS_HPP

void updateInstruments(float heading, float pitch, float roll, float sink, float airspeed);

void stepVarioDial(float sink);
void stepAltitudeDial(float altitude);
void stepHeadingDial(float heading);
void stepRollDial(float roll);
void stepAltitudeDial(float altitude);

#endif