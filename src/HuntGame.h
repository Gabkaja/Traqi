#pragma once

#include <Arduino.h>
#include "Game.h"
#include "GPS.h"

class HuntGame : public Game
{
public:

    explicit HuntGame(GPS* gps);

    void start() override;

    void update() override;

    void draw() override;

    void stop() override;


    void setRadius(uint16_t radiusMeters);

    void setPointCount(uint8_t pointCount);

    void setTimeLimit(uint16_t timeMinutes);


    uint16_t radius() const;

    uint8_t pointCount() const;

    uint16_t timeLimit() const;


    uint8_t currentPoint() const;

    uint8_t capturedPoints() const;

    bool isFinished() const;

private:

    GPS* gps_;


    uint16_t radiusMeters_ = 500;

    uint8_t pointCount_ = 10;

    uint16_t timeLimitMinutes_ = 30;


    uint8_t currentPoint_ = 0;

    uint8_t capturedPoints_ = 0;


    bool running_ = false;

    bool finished_ = false;


    unsigned long startTimeMs_ = 0;


    double startLatitude_ = 0.0;
    double startLongitude_ = 0.0;


    double targetLatitude_ = 0.0;
    double targetLongitude_ = 0.0;


    float targetDistanceMeters_ = 0.0;

    float targetBearing_ = 0.0;


    unsigned long captureStartMs_ = 0;


    void generateTarget();

    void updateNavigation();

    void checkCapture();

    void finishGame();
};