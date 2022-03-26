#include "SleepManager.h"

void SleepManager::setup(uint8_t wakeUpPins[4]) {
    memcpy(SleepManager::wakeUpPins, wakeUpPins, 4);
    for(uint8_t i = 0; i < 4; i++) {
        pinMode(wakeUpPins[i], INPUT);
    }
}

void SleepManager::sleep() {
    for(uint8_t i = 0; i < 4; i++) {
        enableInterrupt(SleepManager::wakeUpPins[i], {}, RISING);
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    for(uint8_t i = 0; i < 4; i++) {
        disableInterrupt(SleepManager::wakeUpPins[i]);
    }
}

void SleepManager::interruptHandler() {
    for(uint8_t i = 0; i < 4; i++) {
        disableInterrupt(SleepManager::wakeUpPins[i]);
    }
}