#ifndef _DEVICE_BUILDER_H_
#define _DEVICE_BUILDER_H_

#include "Device.h"

class DeviceBuilder {
    private:

    PubSubClient* client;

    // Sensors
    Photoresistor* photoresistor;
    Thermometer* thermometer;

    // Actuators
    DigitalLed* digitalLed;

    public:

    DeviceBuilder() {
        this->digitalLed = NULL;
    }

    DeviceBuilder* withDigitalLed(DigitalLed* digitalLed) {
        this->digitalLed = digitalLed;
        return this;
    }

    DeviceBuilder* withPhotoresistor(Photoresistor* photoresistor) {
        this->photoresistor = photoresistor;
        return this;
    }

    DeviceBuilder* withThermometer(Thermometer* thermometer) {
        this->thermometer = thermometer;
        return this;
    }

    DeviceBuilder* withClientMqtt(PubSubClient* client) {
        this->client = client;
        return this;
    }

    Device* build() {
        return new Device(digitalLed, photoresistor, thermometer, client);
    }

};

#endif