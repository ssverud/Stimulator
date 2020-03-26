#include <Arduino.h>
#include "AsyncUDP.h"

class Potentiometer
{
public:
    int potentiometerPin;
    int potentiometerValue;
    int previousPotentiometerValue;
    int tolerance = 150;
    AsyncUDP Pudp;

    //potentiometer constructor
    Potentiometer(int potentiometerPin)
    {
        this->potentiometerPin = potentiometerPin;
        pinMode(potentiometerPin, INPUT);
    }

    // Potentiometer loop
    void loop()
    {
        potentiometerValue = analogRead(potentiometerPin);
        if (abs(potentiometerValue - previousPotentiometerValue) > tolerance)
        {
            Serial.println(potentiometerValue);
            previousPotentiometerValue = potentiometerValue;
        }

        //pxlserver pixel color change
        if (previousPotentiometerValue < 400)
        {
            Pudp.writeTo((const uint8_t *)"color 80 20 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 400 && previousPotentiometerValue < 800)
        {
            Pudp.writeTo((const uint8_t *)"color 200 200 200", 17, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 800 && previousPotentiometerValue < 1200)
        {
            Pudp.writeTo((const uint8_t *)"color 50 50 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 1600 && previousPotentiometerValue < 2000)
        {
            Pudp.writeTo((const uint8_t *)"color 100 50 200", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 2000 && previousPotentiometerValue < 2400)
        {
            Pudp.writeTo((const uint8_t *)"color 50 200 200", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 2400 && previousPotentiometerValue < 2800)
        {
            Pudp.writeTo((const uint8_t *)"color 50 200 100", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 3200 && previousPotentiometerValue < 3600)
        {
            Pudp.writeTo((const uint8_t *)"color 20 50 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (previousPotentiometerValue > 3600 && previousPotentiometerValue < 4000)
        {
            Pudp.writeTo((const uint8_t *)"color 90 100 80", 15, IPAddress(192, 168, 43, 255), 7000);
        }
    }
};