#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_

#include <Arduino.h>
#include "../Sensor.h"

class Potentiometer : public Sensor {

private:
    int pin;
    int potentiometerValue;

public:
    Potentiometer(int pin);
    int getValue();

    void setup();
    void computeRead();

};
#endif