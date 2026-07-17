#include <Arduino.h>

#include "Joystick.h"
#include "Config.h"

void joystickInit()
{
    pinMode(JOY_SW, INPUT_PULLUP);
}

int joystickX()
{
    return analogRead(JOY_X);
}

int joystickY()
{
    return analogRead(JOY_Y);
}

bool joystickPressed()
{
    return digitalRead(JOY_SW) == LOW;
}