#include "MenuScreen.h"
#include "Input.h"
#include "Display.h"
#include "Config.h"
#include "Colors.h"
#include "Footer.h"

#include "GameSelectScreen.h"
#include "ScreenManager.h"

extern GameSelectScreen gameSelectScreen;

static int selected = 0;
static int previousSelected = 0;

const char* menuItems[] =
{
    "Play",
    "Map",
    "Messages",
    "Settings"
};


void drawMenuItem(int index, bool active)
{
    int startY = 38;
    int spacing = 25;


    uint16_t bg = COLOR_BLACK;
    uint16_t fg = COLOR_WHITE;


    if(active)
    {
        bg = COLOR_GREEN_BG;
        fg = COLOR_GREEN;
    }


    displayFillRectangle(
        10,
        startY + index * spacing,
        170,
        22,
        bg
    );


    String text = String("  ") + menuItems[index];


    if(active)
        text = String("> ") + menuItems[index];


    displayText(
        18,
        startY + 4 + index * spacing,
        text,
        fg,
        2
    );
}



void MenuScreen::draw()
{
    displayClear(COLOR_BLACK);


    // ===== STATUS BAR =====

    displayText(8,7,"Traqi",COLOR_GREEN,2);

    displayText(245,8,"GPS",COLOR_GREEN,1);
    displayText(275,8,"LoRa",COLOR_GREEN,1);

    displayDrawLine(
        0,
        24,
        320,
        24,
        COLOR_DARKGRAY
    );


    // ===== MENU =====

    for(int i=0;i<4;i++)
    {
        drawMenuItem(
            i,
            i == selected
        );
    }
    //footer
    footerDraw();
}



void MenuScreen::update()
{
    InputEvent event = inputUpdate();


    switch(event)
    {

        case InputEvent::UP:

            if(selected > 0)
            {
                previousSelected = selected;
                selected--;

                drawMenuItem(previousSelected,false);
                drawMenuItem(selected,true);
            }

        break;



        case InputEvent::DOWN:

            if(selected < 3)
            {
                previousSelected = selected;
                selected++;

                drawMenuItem(previousSelected,false);
                drawMenuItem(selected,true);
            }

        break;

        case InputEvent::RIGHT:

            if(selected == 0)
            {
                screenManagerSet(&gameSelectScreen);
            }

        break;



        default:
        break;
    }
}

void MenuScreen::onEnter()
{
    gameSelectScreen.setPreviousScreen(this);
    draw();
}