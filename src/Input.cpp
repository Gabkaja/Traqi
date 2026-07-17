#include <Arduino.h>

#include "Input.h"
#include "Joystick.h"

static bool released = true;

InputEvent inputUpdate()
{
    int x = joystickX();
    int y = joystickY();

    if (released)
    {
        if (y < 1200)
        {
            released = false;
            return InputEvent::UP;
        }

        if (y > 3000)
        {
            released = false;
            return InputEvent::DOWN;
        }

        if (x < 1200)
        {
            released = false;
            return InputEvent::LEFT;
        }

        if (x > 3000)
        {
            released = false;
            return InputEvent::RIGHT;
        }

        if (joystickPressed())
        {
            released = false;
            return InputEvent::CLICK;
        }
    }

    if (x > 1700 &&
        x < 2400 &&
        y > 1700 &&
        y < 2400 &&
        !joystickPressed())
    {
        released = true;
    }

    return InputEvent::NONE;
}

void inputInit()
{

}