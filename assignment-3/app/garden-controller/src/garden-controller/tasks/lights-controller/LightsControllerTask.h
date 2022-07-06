#ifndef _LIGHTS_CONTROLLER_TASK_H_
#define _LIGHTS_CONTROLLER_TASK_H_

#include "garden-controller/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "garden-controller/config/device/Device.h"

// Data
#include "garden-controller/config/data/AppData.h"

enum class LightsControllerTaskState {
    WORKING,
    IDLE
};

class LightsControllerTask : public CommunicablePeriodBasedTaskWithFSM<LightsControllerTaskState, MessageType> {

    private:
    int _period = 50;

    AppData* appData;

    // Actuators
    DigitalLed* digitalLed1;
    DigitalLed* digitalLed2;
    AnalogLed* analogLed1;
    AnalogLed* analogLed2;


    public:

    LightsControllerTask(AppData* appData, Device* device) : CommunicablePeriodBasedTaskWithFSM(LightsControllerTaskState::WORKING) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
        this->digitalLed1 = device->getDigitalLed1();
        this->digitalLed2 = device->getDigitalLed2();
        this->analogLed1 = device->getAnalogLed1();
        this->analogLed2 = device->getAnalogLed2();
    }

    void init();
    void computeRead();
    void tick();

    private:
    void onIdleState();
    void onWorkingState();

};

#endif