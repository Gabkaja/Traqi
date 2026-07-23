#include "Display.h"
#include "Config.h"
#include "Colors.h"

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

void displayDrawLine(
    int x0,
    int y0,
    int x1,
    int y1,
    uint16_t color
)
{
    tft.drawLine(x0, y0, x1, y1, color);
}

void displayCircle(
    int x,
    int y,
    int r,
    uint16_t color)
{
    tft.drawCircle(x,y,r,color);
}

void displayFillCircle(
    int x,
    int y,
    int r,
    uint16_t color)
{
    tft.fillCircle(x,y,r,color);
}

void displayBitmapMask(
    int x,
    int y,
    int w,
    int h,
    const uint8_t* mask,
    uint16_t color,
    int colStart,
    int colEnd)
{
    if (colStart < 0) colStart = 0;
    if (colEnd > w) colEnd = w;
    if (colStart >= colEnd) return;
 
    int bytesPerRow = (w + 7) / 8;
 
    tft.startWrite();
 
    for (int row = 0; row < h; row++)
    {
        const uint8_t* rowPtr = mask + (row * bytesPerRow);
 
        for (int col = colStart; col < colEnd; col++)
        {
            uint8_t byteVal = pgm_read_byte(rowPtr + (col >> 3));
            uint8_t bitMask = 0x80 >> (col & 0x07);
 
            if (byteVal & bitMask)
            {
                tft.writePixel(x + col, y + row, color);
            }
        }
    }
 
    tft.endWrite();
}
 
// Rysuje maskę bitową 1bpp (z PROGMEM) w zadanym kolorze, ale tylko dla
// kolumn z przedziału [colStart, colEnd). Pozwala to odsłaniać bitmapę
// stopniowo (np. animacja boot) bez przerysowywania całości co klatkę.
// Format masek: MSB-first, każdy wiersz wyrównany do pełnego bajtu.