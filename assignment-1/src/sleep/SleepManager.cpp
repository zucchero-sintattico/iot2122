#include "SleepManager.h"
#include <Arduino.h>
#include <avr/sleep.h>

SleepManager::SleepManager(uint8_t wakeUpPins[4]){
    memcpy(this->wakeUpPins, wakeUpPins, sizeof(this->wakeUpPins));
}

void SleepManager::setup() {
    for(uint8_t i = 0; i < 4; i++) {
        pinMode(this->wakeUpPins[i], INPUT);
    }
}

void emptyFunc(){}

void SleepManager::sleep() {
    for(uint8_t i = 0; i < 4; i++) {
        enableInterrupt(this->wakeUpPins[i], &emptyFunc, RISING);
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    for(uint8_t i = 0; i < 4; i++) {
        disableInterrupt(this->wakeUpPins[i]);
    }
}

