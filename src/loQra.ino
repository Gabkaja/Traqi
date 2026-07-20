#include "ScreenManager.h"
#include "MenuScreen.h"
#include "Display.h"
#include "Joystick.h"
#include "Input.h"
#include "BootScreen.h"

MenuScreen menu;
BootScreen boot(&menu);

void setup()
{
    displayInit();

    joystickInit();

    inputInit();

    screenManagerInit(&boot);
}

void loop()
{
    screenManagerUpdate();
}