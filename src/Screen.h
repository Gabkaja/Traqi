#pragma once

class Screen
{
public:

    virtual void onEnter() {}

    virtual void onExit() {}

    virtual void update() {}

    virtual void draw() = 0;

    virtual ~Screen() {}
};