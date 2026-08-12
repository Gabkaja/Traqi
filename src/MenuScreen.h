#pragma once

#include "Screen.h"

class MenuScreen : public Screen
{
public:

    void draw() override;

    void update() override;
    
    void onEnter() override;
};