#ifndef _SENSOR_MANAGER_H_
#define _SENSOR_MANAGER_H_

#include "./Setuppable.h"

class SensorManager : public Setuppable {

public:
    virtual void computeRead() = 0;
};

#endif