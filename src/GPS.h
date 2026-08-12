#pragma once

#include <Arduino.h>

class GPS
{
public:

    void begin();

    void update();

    bool hasFix() const;

    double latitude() const;
    double longitude() const;

    float speedKmh() const;

    int satellites() const;

private:

    HardwareSerial gpsSerial = HardwareSerial(1);

    bool fix_ = false;

    double latitude_ = 0.0;
    double longitude_ = 0.0;

    float speedKmh_ = 0.0;

    int satellites_ = 0;
};