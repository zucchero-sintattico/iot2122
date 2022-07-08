#ifndef _STATUSMANAGERTASK_H_
#define _STATUSMANAGERTASK_H_

#include <Arduino.h>
#include "../Task.h"
#include "../../device/Device.h"

class StatusManagerTask : public Task {

    private:
    Device* device;

    public:
    StatusManagerTask(unsigned int delay, Device* device) : Task(delay) {
        this->device = device;
    }
    
    void loop();
};

#endif