#include <evario.hpp>
#include <math.h>

void updateEVario(MCUFRIEND_kbv &tft, float sink, float temperature, float MC, float altitude, float airspeed) {
    writeVarioValue(tft, sink);
    drawVarioArrow(tft, sink);
    drawVarioTriangle(tft, sink);
    writeMC(tft, MC);
    writeTemperature(tft, temperature);
    writeAltitude(tft, altitude);
    writeAirspeed(tft, airspeed);
}

void writeVarioValue(MCUFRIEND_kbv &tft, float sink) {
    static float previous_sink = NAN;

    tft.setTextSize(4);
    if(sink != previous_sink) { // Only erase if old value is different than new value should become
        tft.setCursor(120, 145);
        tft.setTextColor(TFT_BLACK);
        tft.print(abs(previous_sink), 1);
    }
    if(sink != previous_sink) { // Only draw new value if anything has changed
        tft.setCursor(120, 145);
        tft.setTextColor(TFT_WHITE);
        tft.print(abs(sink), 1);
        previous_sink = sink;
    }
}

void drawVarioArrow(MCUFRIEND_kbv &tft, float sink) {
    const int angle_degrees = sink * 18 -90;
    const int cx = 160;       // Center of the clock
    const int cy = 160;
    const int length = 50;    // Length of the hand
    const int width = 5; 
    const int start_offset = 85; // Distance from the center to start the line

    static int old_start_x_1, old_start_y_1, old_start_x_2, old_start_y_2, old_end_x, old_end_y; // To track previous hand position

    float angle_radians = angle_degrees * PI / 180.0;
    float cos_angle = cos(angle_radians);
    float sin_angle = sin(angle_radians);

    int start_x_1 = cx + start_offset * sin_angle - width * cos_angle;
    int start_y_1 = cy - start_offset * cos_angle - width * sin_angle;
    int start_x_2 = cx + start_offset * sin_angle + width * cos_angle;
    int start_y_2 = cy - start_offset * cos_angle + width * sin_angle;
    int end_x = cx + (start_offset + length) * sin_angle;
    int end_y = cy - (start_offset + length) * cos_angle;

    if (old_start_x_1 != start_x_1 && old_start_y_1 != start_y_1 && old_start_x_2 != start_x_2 && old_start_y_2 != start_y_2 && old_end_x != end_x && old_end_y != end_y) { // Only erase if old hand is different than new hand should become
        tft.fillTriangle(old_start_x_1, old_start_y_1, old_start_x_2, old_start_y_2, old_end_x, old_end_y, TFT_BLACK);
    }
    
    if (old_start_x_1 != start_x_1 && old_start_y_1 != start_y_1 && old_start_x_2 != start_x_2 && old_start_y_2 != start_y_2 && old_end_x != end_x && old_end_y != end_y) { // only draw new hand if anything has changed
        tft.fillTriangle(start_x_1, start_y_1, start_x_2, start_y_2, end_x, end_y, TFT_RED);
    }
    old_start_x_1 = start_x_1;
    old_start_y_1 = start_y_1;
    old_start_x_2 = start_x_2;
    old_start_y_2 = start_y_2;
    old_end_x = end_x;
    old_end_y = end_y;
}

void drawVarioTriangle(MCUFRIEND_kbv &tft, float sink) {
    static int previous_triangle = 0;

    if(sink < 0  && previous_triangle != -1) {
        previous_triangle = -1;
        tft.fillTriangle(120, 175, 185, 175, 152.5, 200, TFT_WHITE);
        tft.fillTriangle(120, 142, 185, 142, 152.5, 117, TFT_BLACK);
    }
    if(sink > 0 && previous_triangle != 1) {
        previous_triangle = 1;
        tft.fillTriangle(120, 175, 185, 175, 152.5, 200, TFT_BLACK);
        tft.fillTriangle(120, 142, 185, 142, 152.5, 117, TFT_WHITE);
    }
    if(sink == 0 && previous_triangle == 1) {
        tft.fillTriangle(120, 142, 185, 142, 152.5, 117, TFT_BLACK);
        previous_triangle = 0;
    }
    if(sink == 0 && previous_triangle == -1) {
        tft.fillTriangle(120, 175, 185, 175, 152.5, 200, TFT_BLACK);
        previous_triangle = 0;
    }
}

void writeTemperature(MCUFRIEND_kbv &tft, float temperature) {
    static float previous_temperature = NAN;
    if(temperature != previous_temperature) {
        tft.setCursor(10, 10);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK);
        tft.print(previous_temperature, 1);
        tft.write('C');
        tft.setCursor(10, 10);
        tft.setTextColor(TFT_WHITE);
        tft.print(temperature, 1);
        tft.write('C');
        previous_temperature = temperature;
    }
}

void writeMC(MCUFRIEND_kbv &tft, float MC) {
    static float previous_MC = NAN;
    tft.setCursor(10, 300);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.write('M');
    tft.write('C');
    tft.setCursor(31, 300);
    tft.write(':');

    if(MC != previous_MC) {
        tft.setCursor(10, 300);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK);
        tft.print(previous_MC, 1);
        tft.setCursor(40, 300);
        tft.setTextColor(TFT_WHITE);
        tft.print(MC, 1);
        previous_MC = MC;
    }
}

void writeAltitude(MCUFRIEND_kbv & tft, float altitude) {
    static float previous_altitude = NAN;
    if(altitude != previous_altitude) {
        tft.setCursor(120, 210); //erase old altitude
        tft.setTextColor(TFT_BLACK);
        tft.setTextSize(2);
        tft.print(previous_altitude, 0);
        tft.write('m');
        
        tft.setCursor(120, 210); //draw new altitude
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.print(altitude, 0);
        tft.write('m');
        previous_altitude = altitude;
    }
}

void writeAirspeed(MCUFRIEND_kbv & tft, float airspeed) {
    static float previous_airspeed = NAN;
    if(airspeed != previous_airspeed) {
        tft.setCursor(120, 100); //erase old airspeed
        tft.setTextColor(TFT_BLACK);   
        tft.setTextSize(2);
        tft.print(previous_airspeed, 0);
        tft.write('k');
        tft.write('m');
        tft.write('/');
        tft.write('h');

        tft.setCursor(120, 100); //draw new airspeed
        tft.setTextColor(TFT_WHITE);    
        tft.setTextSize(2);
        tft.print(airspeed, 0);
        tft.write('k');
        tft.write('m');
        tft.write('/');
        tft.write('h');
        previous_airspeed = airspeed;
    }
}