#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "iot/actuator/digital-led/DigitalLed.h"
#include "iot/sensor/photoresistor/Photoresistor.h"
#include "iot/sensor/thermometer/Thermometer.h"

class Device {

    private:

    // Sensors
    Photoresistor* photoresistor;
    Thermometer* thermometer;

    // Actuators
    DigitalLed* digitalLed;


    public:
    Device(DigitalLed* digitalLed, Photoresistor* photoresistor, Thermometer* thermometer) {
        this->digitalLed = digitalLed;
        this->photoresistor = photoresistor;
        this->thermometer = thermometer;
    }

    DigitalLed* getDigitalLed() {
        return digitalLed;
    }

    Photoresistor* getPhotoresistor() {
        return photoresistor;
    }

    Thermometer* getThermometer() {
        return thermometer;
    }

    void setup() {
        digitalLed->setup();
        photoresistor->setup();
        thermometer->setup();
    }

    void computeRead() {
        photoresistor->computeRead();
        thermometer->computeRead();
    }
};

#endif