#ifndef _DEVICE_BUILDER_H_
#define _DEVICE_BUILDER_H_

#include "Device.h"

class DeviceBuilder {
    private:

    // Actuators
    Motor* motor;
    DigitalLed* digitalLed1;
    DigitalLed* digitalLed2;
    AnalogLed* analogLed1;
    AnalogLed* analogLed2;

    public:

    DeviceBuilder() {
        this->motor = NULL;
        this->digitalLed1 = NULL;
        this->digitalLed2 = NULL;
        this->analogLed1 = NULL;
        this->analogLed2 = NULL;
    }

    DeviceBuilder* withMotor(Motor* motor) {
        this->motor = motor;
        return this;
    }

    DeviceBuilder* withDigitalLed1(DigitalLed* digitalLed1) {
        this->digitalLed1 = digitalLed1;
        return this;
    }

    DeviceBuilder* withDigitalLed2(DigitalLed* digitalLed2) {
        this->digitalLed2 = digitalLed2;
        return this;
    }

    DeviceBuilder* withAnalogLed1(AnalogLed* analogLed1) {
        this->analogLed1 = analogLed1;
        return this;
    }

    DeviceBuilder* withAnalogLed2(AnalogLed* analogLed2) {
        this->analogLed2 = analogLed2;
        return this;
    }

    Device* build() {
        return new Device(motor, digitalLed1, digitalLed2, analogLed1, analogLed2);
    }

};

#endif