#include "Display.h"

void setup()
{
    displayInit();
    displayBoot();

    for(int i=0;i<=100;i+=5)
    {
        displayLoading(i);
        delay(40);
    }

    delay(800);
}

void loop()
{

}