#ifndef _DEVICE_BUILDER_H_
#define _DEVICE_BUILDER_H_

#include "Device.h"

class DeviceBuilder {
    private:

    // Sensors
    Button* buttonUp;
    Button* buttonDown;
    Button* buttonMake;
    Potentiometer* potentiometer;
    Pir* pir;
    Thermometer* thermometer;
    Sonar* sonar;

    // Actuators
    Motor* motor;
    CoffeeDisplayI2C* coffeeDisplayI2C;

    public:

    DeviceBuilder* withButtonUp(Button* buttonUp) {
        this->buttonUp = buttonUp;
        return this;
    }

    DeviceBuilder* withButtonDown(Button* buttonDown) {
        this->buttonDown = buttonDown;
        return this;
    }

    DeviceBuilder* withButtonMake(Button* buttonMake) {
        this->buttonMake = buttonMake;
        return this;
    }

    DeviceBuilder* withPotentiometer(Potentiometer* potentiometer) {
        this->potentiometer = potentiometer;
        return this;
    }

    DeviceBuilder* withPir(Pir* pir) {
        this->pir = pir;
        return this;
    }

    DeviceBuilder* withThermometer(Thermometer* thermometer) {
        this->thermometer = thermometer;
        return this;
    }

    DeviceBuilder* withSonar(Sonar* sonar) {
        this->sonar = sonar;
        return this;
    }

    DeviceBuilder* withMotor(Motor* motor) {
        this->motor = motor;
        return this;
    }

    DeviceBuilder* withCoffeeDisplayI2C(CoffeeDisplayI2C* coffeeDisplayI2C) {
        this->coffeeDisplayI2C = coffeeDisplayI2C;
        return this;
    }

    Device* build() {
        return new Device(buttonUp, buttonDown, buttonMake, potentiometer, pir, thermometer, sonar, motor, coffeeDisplayI2C);
    }
};

#endif