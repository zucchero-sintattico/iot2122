#ifndef _PIR_MANAGER_H_
#define _PIR_MANAGER_H_

#include "iot/sensor/SensorManager.h"

class PirManager : public SensorManager {

    private:
    int pin;
    bool detection;
    int calibrationTimeMS = 10000;

    public:
    PirManager(int pin);
    bool isSomeoneDetected();

    void setup();
    void computeRead();

};

#endif