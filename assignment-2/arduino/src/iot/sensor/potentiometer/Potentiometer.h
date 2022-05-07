#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#include <Arduino.h>
#include "../Sensor.h"

class Potentiometer : public Sensor {

private:
    uint8_t pin;
    int potentiometerValue;

public:
    Potentiometer(uint8_t pin);
    int getValue();

    void setup();
    void computeRead();

};
#endif