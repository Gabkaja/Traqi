#pragma once

enum class InputEvent
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    CLICK
};

void inputInit();

InputEvent inputUpdate();