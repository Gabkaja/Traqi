#include "BootScreen.h"

#include <Arduino.h>

#include "BootLogoBitmap.h"
#include "Colors.h"
#include "Display.h"
#include "ScreenManager.h"

namespace
{
    // Effective landscape screen size. Config.h defines the panel's native
    // TFT_WIDTH=170 / TFT_HEIGHT=320, but Display.cpp calls
    // tft.setRotation(1) in displayInit(), which swaps them into a
    // 320x170 landscape drawing area (see MenuScreen.cpp, which already
    // draws against 320-wide layout).
    constexpr int kScreenWidth = 320;
    constexpr int kScreenHeight = 170;

    constexpr int kLogoX = (kScreenWidth - BOOT_LOGO_WIDTH) / 2;
    constexpr int kLogoY = (kScreenHeight - BOOT_LOGO_HEIGHT) / 2;

    // Total duration of the reveal animation. Purely time-based for now
    // (see BootScreen::getBootProgress) - replace with real init progress
    // later without touching anything else in this file.
    constexpr uint32_t kBootAnimationDurationMs = 1800;
}

BootScreen::BootScreen(Screen* nextScreen)
    : nextScreen_(nextScreen),
      startTimeMs_(0),
      lastRevealedColumn_(0),
      finished_(false)
{
}

void BootScreen::onEnter()
{
    startTimeMs_ = millis();
    lastRevealedColumn_ = 0;
    finished_ = false;
}

float BootScreen::getBootProgress() const
{
    uint32_t elapsedMs = millis() - startTimeMs_;

    if (elapsedMs >= kBootAnimationDurationMs)
        return 1.0f;

    return (float)elapsedMs / (float)kBootAnimationDurationMs;
}

void BootScreen::draw()
{
    displayClear(COLOR_BLACK);

    // Full grey silhouette, painted once. update() paints COLOR_GREEN over
    // it column-by-column as the animation progresses.
    displayBitmapMask(
        kLogoX,
        kLogoY,
        BOOT_LOGO_WIDTH,
        BOOT_LOGO_HEIGHT,
        BOOT_LOGO_BITMAP,
        COLOR_GRAY,
        0,
        BOOT_LOGO_WIDTH
    );
}

void BootScreen::update()
{
    if (finished_)
        return;

    float progress = getBootProgress();
    int revealColumn = (int)(progress * (float)BOOT_LOGO_WIDTH);

    // Only paint the newly-revealed slice, not the whole bitmap, so this
    // stays cheap even though update() runs every loop() iteration.
    if (revealColumn > lastRevealedColumn_)
    {
        displayBitmapMask(
            kLogoX,
            kLogoY,
            BOOT_LOGO_WIDTH,
            BOOT_LOGO_HEIGHT,
            BOOT_LOGO_BITMAP,
            COLOR_GREEN,
            lastRevealedColumn_,
            revealColumn
        );

        lastRevealedColumn_ = revealColumn;
    }

    if (progress >= 1.0f)
    {
        finished_ = true;
        screenManagerSet(nextScreen_);
    }
}