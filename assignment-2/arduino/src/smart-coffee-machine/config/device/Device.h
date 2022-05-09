#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "iot/sensor/button/Button.h"
#include "iot/sensor/sonar/Sonar.h"
#include "iot/sensor/thermometer/Thermometer.h"
#include "iot/sensor/pir/Pir.h"
#include "iot/actuator/motor/Motor.h"
#include "smart-coffee-machine/sensors/sugar/Sugar.h"
#include "smart-coffee-machine/actuators/proxy-coffee-display-i2c/ProxyCoffeeDisplayI2C.h"


class Device {

    private:

    // Sensors
    Button* buttonUp;
    Button* buttonDown;
    Button* buttonMake;
    Sugar* sugar;
    Pir* pir;
    Thermometer* thermometer;
    Sonar* sonar;

    // Actuators
    Motor* motor;
    CoffeeDisplayI2C* coffeeDisplayI2C;

    public:
    Device(Button* buttonUp, Button* buttonDown, Button* buttonMake, Sugar* sugar, Pir* pir, Thermometer* thermometer, Sonar* sonar, Motor* motor, CoffeeDisplayI2C* coffeeDisplayI2C) {
        this->buttonUp = buttonUp;
        this->buttonDown = buttonDown;
        this->buttonMake = buttonMake;
        this->sugar = sugar;
        this->pir = pir;
        this->thermometer = thermometer;
        this->sonar = sonar;
        this->motor = motor;
        this->coffeeDisplayI2C = coffeeDisplayI2C;
    }
    Device(uint8_t potentiometerPin, uint8_t thermometerPin, uint8_t buttonMakePin, uint8_t buttonUpPin, uint8_t buttonDownPin, uint8_t sonarEchoPin, uint8_t sonarTrigPin, uint8_t pirPin, uint8_t servoPin) {
        sugar = new Sugar(potentiometerPin);
        thermometer = new Thermometer(thermometerPin);
        buttonMake = new Button(buttonMakePin);
        buttonUp = new Button(buttonUpPin);
        buttonDown = new Button(buttonDownPin);
        sonar = new Sonar(sonarTrigPin, sonarEchoPin);
        pir = new Pir(pirPin);
        motor = new Motor(servoPin);

        coffeeDisplayI2C = ProxyCoffeeDisplayI2C::getInstance();
    }

    Sugar* getSugar() {
        return sugar;
    }

    Thermometer* getThermometer() {
        return thermometer;
    }

    Button* getButtonMake() {
        return buttonMake;
    }

    Button* getButtonUp() {
        return buttonUp;
    }

    Button* getButtonDown() {
        return buttonDown;
    }

    Sonar* getSonar() {
        return sonar;
    }

    Pir* getPir() {
        return pir;
    }

    Motor* getMotor() {
        return motor;
    }

    CoffeeDisplayI2C* getCoffeeDisplayI2C() {
        return coffeeDisplayI2C;
    }

};

#endif