#ifndef _SENSOR_MANAGER_H_
#define _SENSOR_MANAGER_H_

class SensorManager {

public:
    virtual void computeRead() = 0;
};

#endif