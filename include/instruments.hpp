#ifndef __INSTRUMENTS_HPP
#define __INSTRUMENTS_HPP

#include <Stepper.h>

void updateInstruments(Stepper &varioStepper, Stepper &altitudeStepper, Stepper &headingStepper, Stepper &rollStepper, Stepper &airspeedStepper, float altitude, float heading, float roll, float sink, float airspeed);

void stepVarioDial(Stepper &varioStepper, float sink);
void stepAltitudeDial(Stepper &altitudeStepper, float altitude);
void stepHeadingDial(Stepper &headingStepper, float heading);
void stepRollDial(Stepper &rollStepper, float roll);
void stepAirspeedDial(Stepper &airspeedStepper, float airspeed);

#endif