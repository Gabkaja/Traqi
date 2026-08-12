#include "GameScreen.h"

#include "Display.h"
#include "Colors.h"


GameScreen::GameScreen(Game* game)
{
    game_ = game;
}


void GameScreen::onEnter()
{
    if(game_ != nullptr)
        game_->start();

    draw();
}


void GameScreen::onExit()
{
    if(game_ != nullptr)
        game_->stop();
}


void GameScreen::update()
{
    if(game_ != nullptr)
        game_->update();
}


void GameScreen::draw()
{
    displayClear(COLOR_BLACK);

    if(game_ != nullptr)
        game_->draw();
}