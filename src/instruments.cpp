#include <instruments.hpp>
#include <Stepper.h>
#include <InterpolationLib.h>

void updateInstruments(Stepper &varioStepper, Stepper &altitudeStepper, Stepper &headingStepper, Stepper &rollStepper, Stepper &airspeedStepper, float altitude, float heading, float roll, float sink, float airspeed) {
    stepVarioDial(varioStepper, sink);
    stepAltitudeDial(altitudeStepper, altitude);
    stepHeadingDial(headingStepper, heading);
    stepRollDial(rollStepper, roll);
    stepAirspeedDial(airspeedStepper, airspeed);
}

//finished

void stepVarioDial(Stepper &varioStepper, float sink) {
    static int vario_stepper_state = 0;
    static int vario_stepper_target = 0;
    static float vario_stepper_degrees = 0;

    float sink_m = sink * 0.3048; //conversion ft/s to m/s

    if(sink_m > 5) {
        sink_m = 5;
    }   //setting maximum values for dial

    if(sink_m < -5) {
        sink_m = -5;
    }   //setting maximum values for dial

    vario_stepper_degrees = sink_m * 27.1;

    vario_stepper_target = vario_stepper_degrees / 360 * 2048;

    if(vario_stepper_state > vario_stepper_target) {
        vario_stepper_state--;
        varioStepper.step(-1);
    }

    if(vario_stepper_state < vario_stepper_target) {
        vario_stepper_state++;
        varioStepper.step(1);
    }
}

//finished

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

//wraparound not implemented yet

void stepHeadingDial(Stepper &headingStepper, float heading) {
    static int heading_stepper_target = 0;
    static int heading_stepper_state = 0;
    static int previous_heading_stepper_target = 0;

    heading_stepper_target = heading / 360 * 2048;

/*    if(previous_heading_stepper_target > 2040 && heading_stepper_target < 10) {
        heading_stepper_state = heading_stepper_state - 2048;
    }

    if(previous_heading_stepper_target < 10 && heading_stepper_target > 2040) {
        heading_stepper_state = heading_stepper_state + 2048;
    }*/

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
//no roll on new instrument panel, so commenting out
void stepRollDial(Stepper &rollStepper, float roll) {
    static int roll_stepper_target = 0;
    static int roll_stepper_state = 0;

    if(roll > 20) {
        roll = 20;
    }
    if(roll < -20) {
        roll = -20;
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

//new logic for new airspeed dial

void stepAirspeedDial(Stepper &airspeedStepper, float airspeed) {
    static int airspeed_stepper_target;
    static int airspeed_stepper_state;
    float airspeed_degrees;

    float airspeed_km = airspeed * 1.852; //conversion knots to km/h

    if(airspeed_km > 320) {
        airspeed_km = 320;
    }

    // Updated calculation for airspeed_degrees:
    const int numValues = 10;
    double speedValues[10] = {0, 40, 60, 80, 100, 120, 150, 200, 250, 300};
    double degreesValues[10] = {0, 28.7, 75.9, 128.3, 181, 225.5, 290.4, 398.2, 449.6, 503.5};

    airspeed_degrees = Interpolation::ConstrainedSpline(speedValues, degreesValues, numValues, airspeed_km);

    airspeed_stepper_target = airspeed_degrees / 360 * 2048;

    if(airspeed_stepper_state > airspeed_stepper_target) {
        airspeed_stepper_state--;
        airspeedStepper.step(-1);
    }

    if(airspeed_stepper_state < airspeed_stepper_target) {
        airspeed_stepper_state++;
        airspeedStepper.step(1);
    }
}