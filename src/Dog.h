#pragma once

enum class DogMood
{
    Idle,
    Happy,
    Searching,
    Sleeping,
    Confused
};

class Dog
{
public:

    void setMood(DogMood mood);

    void draw(int x,int y);

private:

    DogMood currentMood = DogMood::Idle;
};

extern Dog dog;