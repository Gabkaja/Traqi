#include "HuntGame.h"

#include "Display.h"
#include "Colors.h"


HuntGame::HuntGame(GPS* gps)
{
    gps_ = gps;
}


void HuntGame::start()
{
    running_ = true;
    finished_ = false;

    currentPoint_ = 0;
    capturedPoints_ = 0;

    startTimeMs_ = millis();

    if(gps_ != nullptr && gps_->hasFix())
    {
        startLatitude_ = gps_->latitude();
        startLongitude_ = gps_->longitude();
    }
}


void HuntGame::update()
{
    if(!running_)
        return;


    if(gps_ != nullptr)
        gps_->update();


    unsigned long elapsed =
        millis() - startTimeMs_;

    unsigned long limit =
        (unsigned long)timeLimitMinutes_ * 60000UL;


    if(elapsed >= limit)
    {
        finishGame();
    }
}


void HuntGame::draw()
{
    displayClear(COLOR_BLACK);


    displayText(
        8,
        7,
        "HUNT",
        COLOR_GREEN,
        2
    );


    displayDrawLine(
        0,
        24,
        320,
        24,
        COLOR_DARKGRAY
    );


    displayText(
        20,
        50,
        "CEL",
        COLOR_WHITE,
        2
    );


    displayText(
        20,
        80,
        "1 / 10",
        COLOR_GREEN,
        2
    );


    displayText(
        20,
        120,
        "GPS OK",
        COLOR_WHITE,
        1
    );
}


void HuntGame::stop()
{
    running_ = false;
}


void HuntGame::setRadius(uint16_t radiusMeters)
{
    radiusMeters_ = radiusMeters;
}


void HuntGame::setPointCount(uint8_t pointCount)
{
    if(pointCount < 3)
        pointCount = 3;

    if(pointCount > 15)
        pointCount = 15;

    pointCount_ = pointCount;
}


void HuntGame::setTimeLimit(uint16_t timeMinutes)
{
    timeLimitMinutes_ = timeMinutes;
}


uint16_t HuntGame::radius() const
{
    return radiusMeters_;
}


uint8_t HuntGame::pointCount() const
{
    return pointCount_;
}


uint16_t HuntGame::timeLimit() const
{
    return timeLimitMinutes_;
}


uint8_t HuntGame::currentPoint() const
{
    return currentPoint_;
}


uint8_t HuntGame::capturedPoints() const
{
    return capturedPoints_;
}


bool HuntGame::isFinished() const
{
    return finished_;
}


void HuntGame::generateTarget()
{
}


void HuntGame::updateNavigation()
{
}


void HuntGame::checkCapture()
{
}


void HuntGame::finishGame()
{
    running_ = false;
    finished_ = true;
}