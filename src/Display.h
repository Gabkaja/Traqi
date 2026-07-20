#pragma once

#include <Arduino.h>
#include <stdint.h>

void displayInit();

void displayClear(uint16_t color);

void displayText(
    int x,
    int y,
    const String &text,
    uint16_t color,
    uint8_t size
);

void displayRectangle(
    int x,
    int y,
    int w,
    int h,
    uint16_t color
);

void displayFillRectangle(
    int x,
    int y,
    int w,
    int h,
    uint16_t color
);

void displayDrawLine(
    int x0,
    int y0,
    int x1,
    int y1,
    uint16_t color
);

void displayCircle(
    int x,
    int y,
    int r,
    uint16_t color
);

void displayFillCircle(
    int x,
    int y,
    int r,
    uint16_t color
);
void displayBitmapMask(
    int x,
    int y,
    int w,
    int h,
    const uint8_t* mask,
    uint16_t color,
    int colStart,
    int colEnd
);