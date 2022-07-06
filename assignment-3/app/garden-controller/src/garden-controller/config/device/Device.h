#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "iot/actuator/motor/Motor.h"
#include "iot/actuator/digital-led/DigitalLed.h"
#include "iot/actuator/analog-led/AnalogLed.h"


class Device {

    private:

    // Actuators
    Motor* motor;
    DigitalLed* digitalLed1;
    DigitalLed* digitalLed2;
    AnalogLed* analogLed1;
    AnalogLed* analogLed2;


    public:
    Device(Motor* motor, DigitalLed* digitalLed1, DigitalLed* digitalLed2, AnalogLed* analogLed1, AnalogLed* analogLed2) {
        this->motor = motor;
        this->digitalLed1 = digitalLed1;
        this->digitalLed2 = digitalLed2;
        this->analogLed1 = analogLed1;
        this->analogLed2 = analogLed2;
    }

    Motor* getMotor() {
        return motor;
    }

    DigitalLed* getDigitalLed1() {
        return digitalLed1;
    }

    DigitalLed* getDigitalLed2() {
        return digitalLed2;
    }

    AnalogLed* getAnalogLed1() {
        return analogLed1;
    }

    AnalogLed* getAnalogLed2() {
        return analogLed2;
    }


};

#endif