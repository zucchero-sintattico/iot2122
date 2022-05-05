#ifndef _SONAR_MANAGER_H_
#define _SONAR_MANAGER_H_

#include "iot/sensor/SensorManager.h"

class SonarManager : public SensorManager {

    private:
    const float vs = 331.45 + 0.62*20;
    int trigPin;
    int echoPin;
    float distance;

    public:
    SonarManager(int trigPin, int echoPin);
    float getDistanceInCM();

    void setup();
    void computeRead();

};

#endif