#ifndef _SONAR_H_
#define _SONAR_H_

#include "../Sensor.h"

class Sonar : public Sensor {

private:
    const float vs = 331.45 + 0.62 * 20;
    int trigPin;
    int echoPin;
    float distance;

public:
    Sonar(int trigPin, int echoPin);
    float getDistanceInCM();

    void setup();
    void computeRead();

};

#endif