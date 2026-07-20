#include "Dog.h"

#include "Display.h"
#include "Colors.h"

Dog dog;

void Dog::setMood(DogMood mood)
{
    currentMood = mood;
}

void Dog::draw(int x,int y)
{
    // głowa

    displayFillCircle(x+25,y+25,20,COLOR_BROWN);

    // uszy

    displayFillCircle(x+10,y+10,8,COLOR_BROWN);
    displayFillCircle(x+40,y+10,8,COLOR_BROWN);

    // pysk

    displayFillCircle(x+25,y+32,10,COLOR_TAN);

    // oczy

    displayFillCircle(x+18,y+22,2,COLOR_BLACK);
    displayFillCircle(x+32,y+22,2,COLOR_BLACK);

    switch(currentMood)
    {
        case DogMood::Happy:

            displayText(
                x+52,
                y+5,
                "!",
                COLOR_GREEN,
                2
            );

            break;

        case DogMood::Searching:

            displayCircle(
                x+60,
                y+18,
                7,
                COLOR_GREEN
            );

            break;

        case DogMood::Sleeping:

            displayText(
                x+52,
                y+5,
                "Z",
                COLOR_WHITE,
                2
            );

            break;

        case DogMood::Confused:

            displayText(
                x+52,
                y+5,
                "?",
                COLOR_ORANGE,
                2
            );

            break;

        default:
            break;
    }
}