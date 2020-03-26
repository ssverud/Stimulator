#include <Arduino.h>
#include "AsyncUDP.h"

class Joystick
{
public:
    int joystickPinX;
    int joystickPinY;
    int joystickValueX;
    int joystickValueY;
    int previousJoystickValueX = 0;
    int previousJoystickValueY = 0;
    int joystickButtonPin = 13;
    int tolerance = 400;
    AsyncUDP Judp;

    //joystick constructor
    Joystick(int joystickPinX, int joystickPinY)
    {
        this->joystickPinX = joystickPinX;
        this->joystickPinY = joystickPinY;
        pinMode(joystickPinX, INPUT);
        pinMode(joystickPinY, INPUT);
        pinMode(joystickButtonPin, INPUT_PULLUP);
    }

    // Joystick loop
    void loop()
    {
        joystickValueX = analogRead(joystickPinX);
        joystickValueY = analogRead(joystickPinY);

        //only update if bigger than tolerance
        if (abs(joystickValueX - previousJoystickValueX) > tolerance ||
            abs(joystickValueY - previousJoystickValueY) > tolerance)
        {

            //Serial.print(map(analogRead(pinX), 0, 4095, -100, 100));
            Serial.print(previousJoystickValueX);
            Serial.print(" : ");
            Serial.println(previousJoystickValueY);
            //Serial.println(map(analogRead(pinY), 0, 4095, 100, -100));
            previousJoystickValueX = analogRead(joystickPinX);
            previousJoystickValueY = analogRead(joystickPinY);
        }

        //if clicked on joystick initiate pixel
        if (digitalRead(joystickButtonPin) == LOW)
        
        {
            Serial.println("CLICKED ON");
            Judp.writeTo((const uint8_t *)"init 10 10", 10, IPAddress(192, 168, 43, 255), 7000);
        }

        //pixel moveup
        if (previousJoystickValueY > 2000)
        {
            Judp.writeTo((const uint8_t *)"moveup", 6, IPAddress(192, 168, 43, 255), 7000);
        }
        //pixel movedown
        if (previousJoystickValueY < 1000)
        {
            Judp.writeTo((const uint8_t *)"movedown", 8, IPAddress(192, 168, 43, 255), 7000);
        }
        //pixel move right
        if (previousJoystickValueX < 1000)
        {
            Judp.writeTo((const uint8_t *)"moveright", 9, IPAddress(192, 168, 43, 255), 7000);
        }
        //pixel move left
        if (previousJoystickValueX > 2000)
        {
            Judp.writeTo((const uint8_t *)"moveleft", 8, IPAddress(192, 168, 43, 255), 7000);
        }
    }
};