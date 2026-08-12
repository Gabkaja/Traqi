#pragma once

#include "Screen.h"

class GameSelectScreen : public Screen
{
public:

    void setPreviousScreen(Screen* screen);

    void onEnter() override;

    void draw() override;

    void update() override;

private:

    Screen* previousScreen_ = nullptr;

    int selected_ = 0;
};