#include "blink-task.h"

#include <Arduino.h>
#include "scheduling/strategy/period-based-scheduling-strategy/period-based-scheduling-strategy.h"

void BlinkTask::init() {
    pinMode(LED_BUILTIN, OUTPUT);
    this->state = OFF;
}

void BlinkTask::tick() {
    if (this->state == OFF) {
        Serial.println("BlinkTask: turn on");
        digitalWrite(LED_BUILTIN, HIGH);
        this->state = ON;
    }
    else {
        Serial.println("BlinkTask: turn off");
        digitalWrite(LED_BUILTIN, LOW);
        this->state = OFF;
    }
}