#include "Display.h"
#include "Config.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

void displayInit()
{
    SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

    tft.init(TFT_WIDTH, TFT_HEIGHT);
    tft.setRotation(1);
}

void displayClear(uint16_t color)
{
    tft.fillScreen(color);
}

void displayText(
    int x,
    int y,
    const String &text,
    uint16_t color,
    uint8_t size)
{
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextSize(size);
    tft.print(text);
}

void displayRectangle(
    int x,
    int y,
    int w,
    int h,
    uint16_t color)
{
    tft.drawRect(x, y, w, h, color);
}

void displayFillRectangle(
    int x,
    int y,
    int w,
    int h,
    uint16_t color)
{
    tft.fillRect(x, y, w, h, color);
}

void displayBoot()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(4);

    tft.setCursor(35, 35);
    tft.println("loQra");

    tft.setTextSize(2);
    tft.setCursor(55, 85);
    tft.println("booting...");
}

void displayLoading(int percent)
{
    int x = 25;
    int y = 140;
    int w = 270;
    int h = 20;

    tft.drawRect(x, y, w, h, ST77XX_WHITE);

    int fill = (w - 2) * percent / 100;

    tft.fillRect(x + 1, y + 1, fill, h - 2, ST77XX_GREEN);
}