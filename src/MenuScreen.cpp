#include "MenuScreen.h"
#include "Input.h"
#include "Display.h"
#include "Config.h"

static int selected = 0;
static int lastSelected = -1;
const char* menuItems[] =
{
    "Play",
    "Messages",
    "Settings",
    "About"
};

void drawItem(int index, bool selectedItem)
{
    int y = 80 + index * 30;

    // czyścimy tylko jedną linię
    displayFillRectangle(
        15,
        y,
        250,
        22,
        COLOR_BLACK
    );

    String text;

    if(selectedItem)
        text = "> ";
    else
        text = "  ";

    text += menuItems[index];

    displayText(
        20,
        y,
        text,
        selectedItem ? COLOR_GREEN : COLOR_WHITE,
        2
    );
}

void MenuScreen::draw()
{
    displayClear(COLOR_BLACK);

    displayText(
        35,
        20,
        "loQra",
        COLOR_GREEN,
        4
    );

    for(int i=0;i<4;i++)
        drawItem(i, i==selected);

    lastSelected = selected;
}

void MenuScreen::update()
{
    InputEvent event = inputUpdate();

    switch(event)
    {
        case InputEvent::UP:

            if(selected>0)
                selected--;

            break;

        case InputEvent::DOWN:

            if(selected<3)
                selected++;

            break;

        default:

            return;
    }

    if(lastSelected!=selected)
    {
        drawItem(lastSelected,false);

        drawItem(selected,true);

        lastSelected=selected;
    }
}