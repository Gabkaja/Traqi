#pragma once
#include <stdint.h>
#include "Screen.h"

/*
 * BootScreen
 *
 * Splash screen shown right after power-on. draw() paints the logo greyed
 * out once; update() then colorizes it left-to-right as boot progress
 * advances, and hands control to nextScreen once the reveal reaches 100%.
 */
class BootScreen : public Screen
{
public:

    // nextScreen is the screen to switch to once the boot animation
    // finishes (e.g. &menu).
    explicit BootScreen(Screen* nextScreen);

    void onEnter() override;

    void draw() override;

    void update() override;

private:

    // Time-based progress source for the reveal animation (0.0..1.0).
    // Isolated in its own method so it can be swapped later for real
    // initialization progress instead of elapsed time.
    float getBootProgress() const;

    Screen* nextScreen_;

    uint32_t startTimeMs_;
    int lastRevealedColumn_;
    bool finished_;
};