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