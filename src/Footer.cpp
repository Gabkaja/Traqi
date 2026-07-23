#include "Footer.h"
#include "Display.h"
#include "Colors.h"


void footerDraw()
{
    displayDrawLine(
        0,
        150,
        320,
        150,
        COLOR_DARKGRAY
    );


    displayText(
        10,
        156,
        "UP DOWN Move",
        COLOR_GRAY,
        1
    );


    displayText(
        115,
        156,
        "RIGHT OK",
        COLOR_GRAY,
        1
    );


    displayText(
        220,
        156,
        "LEFT Back",
        COLOR_GRAY,
        1
    );
}