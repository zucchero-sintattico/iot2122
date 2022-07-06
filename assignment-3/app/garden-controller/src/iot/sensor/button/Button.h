#ifndef _BUTTON_H
#define _BUTTON_H

#include "../Sensor.h"
#include <Arduino.h>

class Button : public Sensor {

private:
    uint8_t pin;
    bool isButtonPressed = false;
    bool prevValue = false;

public:
    Button(uint8_t pin);
    bool isPressed();

    void setup();
    void computeRead();

};

#endif