#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <PubSubClient.h>

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
    const char* ssid = "Home&Life SuperWiFi-5D91";
    const char* password = "7RR7UY3DG7XT8KMQ";
    const char* mqtt_server = "192.168.1.49";
    WiFiClient wifi;
    PubSubClient mqtt;

    Device(DigitalLed* digitalLed, Photoresistor* photoresistor, Thermometer* thermometer, PubSubClient* client) {
        this->digitalLed = digitalLed;
        this->photoresistor = photoresistor;
        this->thermometer = thermometer;
        this->mqtt = PubSubClient(this->wifi);
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