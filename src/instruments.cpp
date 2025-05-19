#include <instruments.hpp>
#include <Stepper.h>

void updateInstruments(Stepper &varioStepper, Stepper &altitudeStepper, Stepper &headingStepper, Stepper &rollStepper, Stepper &airspeedStepper, float altitude, float heading, float roll, float sink, float airspeed) {
    stepVarioDial(varioStepper, sink);
    stepAltitudeDial(altitudeStepper, altitude);
    stepHeadingDial(headingStepper, heading);
    stepRollDial(rollStepper, roll);
    stepAirspeedDial(airspeedStepper, airspeed);
}

void stepVarioDial(Stepper &varioStepper, float sink) {
    float sink_m = sink * 0.3048;
    static int vario_stepper_state = 0;
    static int vario_stepper_target = 0;
    if(sink_m > 5) {
        sink_m = 5;
    }
    if(sink_m < -5) {
        sink_m = -5;
    }
    if(sink_m > -3 && sink_m < 3) {
        vario_stepper_target = sink_m * 45 * (2048 / 360);
    }
    if(sink_m < -3 || sink_m > 3) {
        vario_stepper_target = sink_m * 45 * (2048 / 360);
    }
    if(sink_m > 3) {
        vario_stepper_target = 135 + 22.5 * (sink_m - 3) * (2048 / 360);
    }
    if(sink_m < -3) {
        vario_stepper_target = 135 + 22.5 * (sink_m + 3) * (2048 / 360);
    }
    if(vario_stepper_state > vario_stepper_target) {
        vario_stepper_state--;
        varioStepper.step(-1);
    }
    if(vario_stepper_state < vario_stepper_target) {
        vario_stepper_state++;
        varioStepper.step(1);
    }
    
}

void stepAltitudeDial(Stepper &altitudeStepper, float altitude) {
    float altitude_m = altitude * 0.3048;
    static int altitude_stepper_state = 0;
    static int altitude_stepper_target = 0;
    altitude_stepper_target = altitude_m / 1000 * 2048;
    if(altitude_stepper_state > altitude_stepper_target) {
        altitude_stepper_state--;
        altitudeStepper.step(-1);
    }
    if(altitude_stepper_state < altitude_stepper_target) {
        altitude_stepper_state++;
        altitudeStepper.step(1);
    }
}

void stepHeadingDial(Stepper &headingStepper, float heading) {
    static int heading_stepper_target = 0;
    static int heading_stepper_state = 0;
    heading_stepper_target = heading / 360 * 2048;
    if(heading_stepper_state > heading_stepper_target) {
        heading_stepper_state--;
        headingStepper.step(-1);
    }
    if(heading_stepper_state < heading_stepper_target) {
        heading_stepper_state++;
        headingStepper.step(1);
    }
}

void stepRollDial(Stepper &rollStepper, float roll) {

}

void stepAirspeedDial(Stepper &airspeedStepper, float airspeed) {

}