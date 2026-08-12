#include "HuntSettingsScreen.h"

#include "Display.h"
#include "Input.h"
#include "Colors.h"
#include "Footer.h"
#include "ScreenManager.h"
#include "Globals.h"

String radiusText(int meters)
{
    if(meters >= 1000)
    {
        return String(meters / 1000) + " km";
    }

    return String(meters) + " m";
}

HuntSettingsScreen::HuntSettingsScreen(Screen* previousScreen)
{
    previousScreen_ = previousScreen;
}


void HuntSettingsScreen::onEnter()
{
    selected_ = 0;

    draw();
}


void HuntSettingsScreen::drawRow(int row, bool selected)
{
    const int startY = 40;
    const int rowHeight = 25;

    uint16_t bg = selected
        ? COLOR_GREEN_BG
        : COLOR_BLACK;

    uint16_t fg = selected
        ? COLOR_GREEN
        : COLOR_WHITE;


    displayFillRectangle(
        10,
        startY + row * rowHeight,
        300,
        22,
        bg
    );


    String text;


    // ==========================================
    // RADIUS
    // ==========================================

    if(row == 0)
    {
        text = "Radius       ";

        if(selected && editing_)
        {
            text += "< ";

            text += radiusText(radiusValues_[radiusIndex_]);

            text += " >";
        }
        else
        {
            if(radiusValues_[radiusIndex_] >= 1000)
            {
                text += radiusValues_[radiusIndex_] / 1000;
                text += " km";
            }
            else
            {
                text += radiusValues_[radiusIndex_];
                text += " m";
            }
        }
    }


    // ==========================================
    // POINTS
    // ==========================================

    else if(row == 1)
    {
        text = "Points       ";

        if(selected && editing_)
        {
            text += "< ";
            text += points_;
            text += " >";
        }
        else
        {
            text += points_;
        }
    }


    // ==========================================
    // TIME
    // ==========================================

    else if(row == 2)
    {
        text = "Time         ";

        if(selected && editing_)
        {
            text += "< ";
            text += timeValues_[timeIndex_];
            text += " min >";
        }
        else
        {
            text += timeValues_[timeIndex_];
            text += " min";
        }
    }


    // ==========================================
    // START
    // ==========================================

    else if(row == 3)
    {
        text = "START";
    }


    displayText(
        16,
        startY + row * rowHeight + 4,
        text,
        fg,
        1
    );
}


void HuntSettingsScreen::drawAllRows()
{
    for(int i = 0; i < 4; i++)
    {
        drawRow(
            i,
            i == selected_
        );
    }

    footerDraw();
}


void HuntSettingsScreen::draw()
{
    displayClear(COLOR_BLACK);


    displayText(
        8,
        7,
        "Hunt",
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


    drawAllRows();
}


void HuntSettingsScreen::update()
{
    InputEvent event = inputUpdate();


    // ==========================================
    // NORMAL MODE
    // ==========================================

    if(!editing_)
    {
        switch(event)
        {
            // --------------------------
            // wybór poprzedniej pozycji
            // --------------------------

            case InputEvent::UP:

                if(selected_ > 0)
                {
                    int previous = selected_;

                    selected_--;

                    drawRow(previous, false);
                    drawRow(selected_, true);
                }

                break;


            // --------------------------
            // wybór następnej pozycji
            // --------------------------

            case InputEvent::DOWN:

                if(selected_ < 3)
                {
                    int previous = selected_;

                    selected_++;

                    drawRow(previous, false);
                    drawRow(selected_, true);
                }

                break;


            // --------------------------
            // wejście w edycję
            // --------------------------

            case InputEvent::RIGHT:

                if(selected_ == 0 ||
                   selected_ == 1 ||
                   selected_ == 2)
                {
                    editing_ = true;

                    drawRow(selected_, true);
                }

                else if(selected_ == 3)
                {
                    // START

                    huntGame.setRadius(
                        radiusValues_[radiusIndex_]
                    );

                    huntGame.setPointCount(
                        points_
                    );

                    huntGame.setTimeLimit(
                        timeValues_[timeIndex_]
                    );

                    screenManagerSet(&huntScreen);
                }

                break;


            // --------------------------
            // powrót z ekranu
            // --------------------------

            case InputEvent::LEFT:

                if(previousScreen_ != nullptr)
                {
                    screenManagerSet(previousScreen_);
                }

                break;


            default:
                break;
        }

        return;
    }


    // ==========================================
    // EDIT MODE
    // ==========================================

    switch(event)
    {
        // --------------------------------------
        // zmiana wartości w górę
        // --------------------------------------

        case InputEvent::UP:

            if(selected_ == 0)
            {
                if(radiusIndex_ < 2)
                {
                    radiusIndex_++;

                    drawRow(0, true);
                }
            }

            else if(selected_ == 1)
            {
                if(points_ < 15)
                {
                    points_++;

                    drawRow(1, true);
                }
            }

            else if(selected_ == 2)
            {
                if(timeIndex_ < 2)
                {
                    timeIndex_++;

                    drawRow(2, true);
                }
            }

            break;


        // --------------------------------------
        // zmiana wartości w dół
        // --------------------------------------

        case InputEvent::DOWN:

            if(selected_ == 0)
            {
                if(radiusIndex_ > 0)
                {
                    radiusIndex_--;

                    drawRow(0, true);
                }
            }

            else if(selected_ == 1)
            {
                if(points_ > 3)
                {
                    points_--;

                    drawRow(1, true);
                }
            }

            else if(selected_ == 2)
            {
                if(timeIndex_ > 0)
                {
                    timeIndex_--;

                    drawRow(2, true);
                }
            }

            break;


        // --------------------------------------
        // zatwierdzenie wartości
        // --------------------------------------

        case InputEvent::RIGHT:

            editing_ = false;

            drawRow(selected_, true);

            break;


        // --------------------------------------
        // wyjście z edycji bez opuszczania ekranu
        // --------------------------------------

        case InputEvent::LEFT:

            editing_ = false;

            drawRow(selected_, true);

            break;


        default:
            break;
    }
}