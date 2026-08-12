#pragma once

class Game
{
public:

    virtual void start() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void stop() = 0;

    virtual ~Game() {}
};