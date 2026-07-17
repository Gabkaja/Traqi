#include "ScreenManager.h"

Screen* currentScreen = nullptr;

void screenManagerInit(Screen* firstScreen)
{
    currentScreen = firstScreen;

    currentScreen->onEnter();

    currentScreen->draw();
}

void screenManagerUpdate()
{
    if(currentScreen != nullptr)
        currentScreen->update();
}

void screenManagerSet(Screen* screen)
{
    if(currentScreen != nullptr)
        currentScreen->onExit();

    currentScreen = screen;

    currentScreen->onEnter();

    currentScreen->draw();
}