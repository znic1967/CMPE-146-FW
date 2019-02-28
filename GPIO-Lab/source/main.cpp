#include "../../library/L0_LowLevel/LPC40xx.h"
#include "utility/log.hpp"
#include "utility/time.hpp"
#include "LabGPIO.h"

void toggleLED(LabGPIO button, LabGPIO led);

int main(void)
{
    int lastButton=-1;

    LabGPIO button0(1, 19);
    LabGPIO led0(2, 3);
    LabGPIO button1(1, 15);
    LabGPIO led1(1, 26);
    LabGPIO button2(0, 30);
    LabGPIO led2(1, 24);
    LabGPIO button3(0, 29);
    LabGPIO led3(1, 18);

    // Initialize button and led here
    button0.SetAsInput();
    led0.SetAsOutput();
    button1.SetAsInput();
    led1.SetAsOutput();
    button2.SetAsInput();
    led2.SetAsOutput();
    button3.SetAsInput();
    led3.SetAsOutput();
    LOG_INFO("Initialization Done.");

    while(true)
    {
        if (button0.ReadBool())
        {
            toggleLED(button0, led0);
            lastButton=0;
        }
        if (button1.ReadBool())
        {
            toggleLED(button1, led1);
            if (lastButton == 0)
            {
                lastButton = 1;
            }
        }
        if (button2.ReadBool())
        {
            toggleLED(button2, led2);
            if (lastButton == 1)
            {
                lastButton = 2;
            }
        }
        if (button3.ReadBool()) 
        {
            
            if (lastButton == 2)
            {
                led0.SetLow();
                led1.SetLow();
                led2.SetLow();
                led3.SetLow();
                lastButton = -1;
                Delay(1000);
            }
            else
            {
                toggleLED(button3, led3);
            }
        }
    }
    return 0;
}

void toggleLED(LabGPIO button, LabGPIO led)
{
    bool finished=0;
    while(!finished)
    {
        if (!(button.ReadBool())) //Button is released
        { 
            bool ledStatus = led.ReadBool();
            if (ledStatus)
            {
                led.SetLow();
            }
            else
            {
                led.SetHigh();
            }
            finished=1;
        }
    }
}
