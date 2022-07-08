#ifndef _SENSORMANAGERTASK_H_
#define _SENSORMANAGERTASK_H_

#include <Arduino.h>
#include "../Task.h"
#include "../../device/Device.h"

class SensorManagerTask : public Task {

    private:
    Device* device;

    public:
    SensorManagerTask(unsigned int delay, Device* device) : Task(delay) {
        this->device = device;
    }
    
    void loop();
};

#endif