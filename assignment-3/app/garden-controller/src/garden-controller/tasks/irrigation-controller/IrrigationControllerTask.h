#ifndef _IRRIGATION_CONTROLLER_TASK_H_
#define _IRRIGATION_CONTROLLER_TASK_H_

#include "garden-controller/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "garden-controller/config/device/Device.h"
#include "garden-controller/config/data/AppData.h"
#include <Arduino.h>

enum class IrrigationControllerTaskState : uint8_t {
    READY,
    OPEN,
    CLOSED
};

class IrrigationControllerTask : public CommunicablePeriodBasedTaskWithFSM<IrrigationControllerTaskState, MessageType> {

private:
    int _period = 50;

    AppData* appData;
    // Actuators
    Motor* motor;

    int angle = 0;
    int direction = 1;

    // Constants
    const long OPEN_TIME_MILLISECONDS = 5000;
    const long CLOSED_TIME_MILLISECONDS = 5000;
    long openTimestamp = 0;
    long closeTimestamp = 0;

public:
    IrrigationControllerTask(AppData* appData, Device* device) : CommunicablePeriodBasedTaskWithFSM(IrrigationControllerTaskState::READY) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
        this->motor = device->getMotor();
        this->openTimestamp = millis();
        this->appData->setIrrigatorStatus(IrrigatorStatus::READY);
    }

    void init();
    void computeRead();
    void tick();

private:
    void onReadyState();
    void onOpenState();
    void onClosedState();

    void rotate();
    void changeStateToOpen();
    void changeStateToClosed();
};

#endif