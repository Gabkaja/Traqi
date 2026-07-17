#include "ScreenManager.h"
#include "MenuScreen.h"
#include "Display.h"
#include "Joystick.h"
#include "Input.h"

MenuScreen menu;

void setup()
{
    displayInit();

    joystickInit();

    inputInit();

    screenManagerInit(&menu);
}

void loop()
{
    screenManagerUpdate();
}