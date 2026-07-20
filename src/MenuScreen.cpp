#include "MenuScreen.h"
#include "Input.h"
#include "Display.h"
#include "Config.h"
#include "Colors.h"
#include "Dog.h"

static int selected = 0;
const char* menuItems[] =
{
    "Play",
    "Map",
    "Messages",
    "Settings"
};

void MenuScreen::draw()
{
    displayClear(COLOR_BLACK);

    // ===== STATUS BAR =====

    displayFillRectangle(0,0,320,24,COLOR_BLACK);

    displayText(8,7,"Traqi",COLOR_GREEN,2);

    displayText(245,8,"GPS",COLOR_GREEN,1);
    displayText(275,8,"LoRa",COLOR_GREEN,1);

    displayDrawLine(0,24,320,24,COLOR_DARKGRAY);

    // ===== DOG PLACEHOLDER =====
    dog.setMood(DogMood::Happy);
    dog.draw(220,40);

    // ===== MENU =====

    int startY = 40;

    for(int i=0;i<4;i++)
    {
        uint16_t bg=COLOR_BLACK;
        uint16_t fg=COLOR_WHITE;

        if(i==selected)
        {
            bg=COLOR_GREEN_BG;
            fg=COLOR_GREEN;
        }

        displayFillRectangle(
            10,
            startY+i*30,
            170,
            26,
            bg
        );

        String text = String("  ") + menuItems[i];

        if(i==selected)
            text = String("> ") + menuItems[i];

        displayText(
            18,
            startY+6+i*30,
            text,
            fg,
            2
        );
    }

}

void MenuScreen::update()
{
    InputEvent event = inputUpdate();

    switch(event)
    {
        case InputEvent::UP:

            if(selected>0)
            {
                selected--;
                draw();
            }

            break;

        case InputEvent::DOWN:

            if(selected<3)
            {
                selected++;
                draw();
            }

            break;

        default:
            break;
    }
}