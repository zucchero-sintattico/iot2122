#ifndef _POTENTIOMETER_MANAGER_H_
#define _POTENTIOMETER_MANAGER_H_

#include <Arduino.h>
#include "../SensorManager.h"

class PotentiometerManager : public SensorManager {

private:
    int pin;
    uint8_t potentiometerValue;

public:
    PotentiometerManager(int pin);
    uint8_t getValue();

    void setup();
    void computeRead();

};
#endif