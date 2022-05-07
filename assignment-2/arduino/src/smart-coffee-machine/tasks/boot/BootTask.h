#ifndef _BOOT_TASK_H_
#define _BOOT_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/actuators/coffee-display-i2c/CoffeeDisplayI2C.h"
#include "smart-coffee-machine/actuators/fake-coffee-display-i2c/FakeCoffeeDisplayI2C.h"

#include <Arduino.h>

enum class BootTaskState : uint8_t {
    BOOT,
    IDLE
};

class BootTask : public CommunicablePeriodBasedTaskWithFSM<BootTaskState, MessageType> {

private:
    int _period = 100;

    CoffeeDisplayI2C* coffeeDisplay;
    long duration = 3000;
    long elapsed = 0;

public:
    BootTask() : CommunicablePeriodBasedTaskWithFSM(BootTaskState::BOOT) {
        PeriodBasedTask::setPeriod(this->_period);
        this->coffeeDisplay = FakeCoffeeDisplayI2C::getInstance();
    }

    void init();
    void computeRead();
    void tick();

private:
    void onBootState();
    void onIdleState();
};

#endif