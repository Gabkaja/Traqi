#include "ScreenManager.h"
#include "MenuScreen.h"
#include "Display.h"
#include "Joystick.h"
#include "Input.h"
#include "BootScreen.h"
#include "Globals.h"


MenuScreen menu;
BootScreen boot(&menu);



void setup()
{
    Serial.begin(115200);

    displayInit();

    joystickInit();

    inputInit();

    gps.begin();

    screenManagerInit(&boot);
}

void loop()
{
    gps.update();

    screenManagerUpdate();
}