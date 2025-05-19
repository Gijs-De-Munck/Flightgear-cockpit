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
    static int vario_stepper_state = 0;
    static int vario_stepper_target = 0;

    float sink_m = sink * 0.3048; //conversion ft/s to m/s

    if(sink_m > 5) {
        sink_m = 5;
    }   //setting maximum values for dial

    if(sink_m < -5) {
        sink_m = -5;
    }   //setting maximum values for dial

    if(sink_m > -3 && sink_m < 3) {
        vario_stepper_target = sink_m * 45 / 360 * 2048;
    }

    if(sink_m < -3 || sink_m > 3) {
        vario_stepper_target = sink_m * 45 / 360 * 2048;
    }

    if(sink_m > 3) {
        vario_stepper_target = 135 + 22.5 * (sink_m - 3) / 360 * 2048;
    }

    if(sink_m < -3) {
        vario_stepper_target = 135 + 22.5 * (sink_m + 3) / 360 * 2048;
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
    static int altitude_stepper_state = 0;
    static int altitude_stepper_target = 0;
    float altitude_m = altitude * 0.3048; //conversion ft to m

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
    static int previous_heading_stepper_target = 0;

    heading_stepper_target = heading / 360 * 2048;

    if(previous_heading_stepper_target > 270 && heading_stepper_target < 90) {
        heading_stepper_state = heading_stepper_state - 360;
    }

    if(previous_heading_stepper_target < 90 && heading_stepper_target < 270) {
        heading_stepper_state = heading_stepper_state + 360;
    }

    if(heading_stepper_state > heading_stepper_target) {
        heading_stepper_state--;
        headingStepper.step(-1);
    }

    if(heading_stepper_state < heading_stepper_target) {
        heading_stepper_state++;
        headingStepper.step(1);
    }

    previous_heading_stepper_target = heading_stepper_target;
}

void stepRollDial(Stepper &rollStepper, float roll) {
    static int roll_stepper_target = 0;
    static int roll_stepper_state = 0;

    if(roll > 10) {
        roll = 10;
    }
    if(roll < -10) {
        roll = -10;
    }

    roll_stepper_target = roll / 360 * 2048;

    if(roll_stepper_state > roll_stepper_target) {
        roll_stepper_state--;
        rollStepper.step(-1);
    }

    if(roll_stepper_state < roll_stepper_target) {
        roll_stepper_state++;
        rollStepper.step(1);
    }
}

void stepAirspeedDial(Stepper &airspeedStepper, float airspeed) {
    static int airspeed_stepper_target;
    static int airspeed_stepper_state;

    float airspeed_km = airspeed * 1.852; //conversion knots to km/h

    if(airspeed_km > 210) {
        airspeed_km = 210;
    }

    if(airspeed_km < 60) {
        
    }

    if(airspeed_km < 60) {
        
    }
}