#ifndef _POTENTIOMETER_MANAGER_H_
#define _POTENTIOMETER_MANAGER_H_

#include <Arduino.h>
#include "iot/sensor/SensorManager.h"

class PotentiometerManager : public SensorManager {

    private:
    int pin;
    int potentiometerValue;

    public:
    PotentiometerManager(int pin);
    int getValue();

    void setup();
    void computeRead();

};
#endif