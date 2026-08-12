#include "GameSelectScreen.h"

#include "Display.h"
#include "Input.h"
#include "Colors.h"
#include "Footer.h"
#include "ScreenManager.h"
#include "HuntSettingsScreen.h"


GameSelectScreen gameSelectScreen;


void GameSelectScreen::setPreviousScreen(Screen* screen)
{
    previousScreen_ = screen;
}
void GameSelectScreen::onEnter()
{
    draw();
}

static HuntSettingsScreen huntSettingsScreen(&gameSelectScreen);


const char* gameItems[] =
{
    "Hunt"
};


const int gameCount = 1;


void GameSelectScreen::draw()
{
    displayClear(COLOR_BLACK);

    // ===== HEADER =====

    displayText(
        8,
        7,
        "Games",
        COLOR_GREEN,
        2
    );

    displayDrawLine(
        0,
        24,
        320,
        24,
        COLOR_DARKGRAY
    );


    // ===== GAMES =====

    const int startY = 40;

    for(int i = 0; i < gameCount; i++)
    {
        uint16_t bg = COLOR_BLACK;
        uint16_t fg = COLOR_WHITE;

        if(i == selected_)
        {
            bg = COLOR_GREEN_BG;
            fg = COLOR_GREEN;
        }

        displayFillRectangle(
            10,
            startY + i * 30,
            170,
            26,
            bg
        );

        String text = "  ";
        text += gameItems[i];

        if(i == selected_)
            text = "> " + String(gameItems[i]);

        displayText(
            18,
            startY + 6 + i * 30,
            text,
            fg,
            2
        );
    }

    footerDraw();
}


void GameSelectScreen::update()
{
    InputEvent event = inputUpdate();

    switch(event)
    {
        case InputEvent::UP:

            if(selected_ > 0)
            {
                selected_--;
                draw();
            }

            break;


        case InputEvent::DOWN:

            if(selected_ < gameCount - 1)
            {
                selected_++;
                draw();
            }

            break;


        case InputEvent::RIGHT:

            if(selected_ == 0)
            {
                screenManagerSet(&huntSettingsScreen);
            }

            break;


        case InputEvent::LEFT:

            if(previousScreen_ != nullptr)
            {
                screenManagerSet(previousScreen_);
            }

            break;

        default:
            break;
    }
}