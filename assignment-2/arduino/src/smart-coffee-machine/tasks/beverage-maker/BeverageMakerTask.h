#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/device/Device.h"

// Data
#include "smart-coffee-machine/config/data/AppData.h"

enum class BeverageMakerTaskState {
    IDLE,
    MAKING,
    WAITING
};

#define MAX_DISTANCE_IN_CM 40
#define INCREMENT_PERCENTAGE 1
#define MAX_WAITING_TIME_IN_MS 3000

class BeverageMakerTask : public CommunicablePeriodBasedTaskWithFSM<BeverageMakerTaskState, MessageType> {

    private:
    int _period = 50;

    AppData* appData;

    // Sensors
    Sonar* sonar;

    // Actuators
    CoffeeDisplayI2C* display;
    Motor* motor;

    uint8_t progressPercentage = 0;
    long elapsedWaitingTime = 0;

    public:

    BeverageMakerTask(AppData* appData, Device* device) : CommunicablePeriodBasedTaskWithFSM(BeverageMakerTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;

        this->sonar = device->getSonar();
        this->motor = device->getMotor();
        this->display = device->getCoffeeDisplayI2C();
    }

    void init();
    void computeRead();
    void tick();

    private:
    void onIdleState();
    void onMakingState();
    void onWaitingState();

};

#endif