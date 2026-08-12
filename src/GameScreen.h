#pragma once

#include "Screen.h"
#include "Game.h"

class GameScreen : public Screen
{
public:

    explicit GameScreen(Game* game);

    void onEnter() override;

    void onExit() override;

    void update() override;

    void draw() override;

private:

    Game* game_;
};