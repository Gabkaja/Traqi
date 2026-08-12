#pragma once

#include "Screen.h"

class HuntSettingsScreen : public Screen
{
public:

    explicit HuntSettingsScreen(Screen* previousScreen);

    void onEnter() override;
    void update() override;
    void draw() override;

private:

    Screen* previousScreen_;

    int selected_ = 0;

    bool editing_ = false;

    int radiusIndex_ = 0;
    int points_ = 10;
    int timeIndex_ = 0;

    const int radiusValues_[3] =
    {
        500,
        1000,
        2000
    };

    const int timeValues_[3] =
    {
        30,
        45,
        60
    };

    void drawRow(int row, bool selected);
    void drawAllRows();
};