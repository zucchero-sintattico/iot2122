#ifndef _SONAR_H_
#define _SONAR_H_

#include "../Sensor.h"
#include <Arduino.h>

class Sonar : public Sensor {

private:
    const float vs = 331.45 + 0.62 * 20;
    uint8_t trigPin;
    uint8_t echoPin;
    float distance;

public:
    Sonar(uint8_t trigPin, uint8_t echoPin);
    float getDistanceInCM();

    void setup();
    void computeRead();

};

#endif