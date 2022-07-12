#ifndef _APP_DATA_H_
#define _APP_DATA_H_

#include <Arduino.h>

enum Status : uint8_t {
    AUTO,
    MANUAL,
    ALARM
};

class AppData {

private:
    Status status = Status::AUTO;

    bool _isDigitalLed1Active = false;
    bool _isDigitalLed2Active = false;

    uint8_t analogLed1Value = 0; // 0 - 4 to be mapped to 0 - 255
    uint8_t analogLed2Value = 0; // 0 - 4 to be mapped to 0 - 255

    bool _isIrrigatorOpen = false;
    uint8_t irrigationSpeed = 1; // 1 - 5

public:

    AppData() {

    }
    AppData(Status initialStatus) {
        this->status = initialStatus;
    }

    Status getStatus() {
        return status;
    }

    void setStatus(Status status) {
        this->status = status;
    }

    bool isDigitalLed1Active() {
        return _isDigitalLed1Active;
    }

    void setDigitalLed1Active(bool isActive) {
        this->_isDigitalLed1Active = isActive;
    }

    bool isDigitalLed2Active() {
        return _isDigitalLed2Active;
    }

    void setDigitalLed2Active(bool isActive) {
        this->_isDigitalLed2Active = isActive;
    }

    uint8_t getAnalogLed1Value() {
        return analogLed1Value;
    }

    void setAnalogLed1Value(uint8_t value) {
        this->analogLed1Value = value;
    }

    uint8_t getAnalogLed2Value() {
        return analogLed2Value;
    }

    void setAnalogLed2Value(uint8_t value) {
        this->analogLed2Value = value;
    }

    uint8_t getIrrigationSpeed() {
        return irrigationSpeed;
    }

    void setIrrigationSpeed(uint8_t speed) {
        this->irrigationSpeed = speed;
    }

    bool isIrrigatorOpen() {
        return _isIrrigatorOpen;
    }

    void setIrrigatorOpen(bool isOpen) {
        this->_isIrrigatorOpen = isOpen;
    }

    void update(bool isDigitalLed1Active, bool isDigitalLed2Active, uint8_t analogLed1Value, uint8_t analogLed2Value, uint8_t irrigationSpeed) {
        this->setDigitalLed1Active(isDigitalLed1Active);
        this->setDigitalLed2Active(isDigitalLed2Active);
        this->setAnalogLed1Value(analogLed1Value);
        this->setAnalogLed2Value(analogLed2Value);
        this->setIrrigationSpeed(irrigationSpeed);
    }
};

#endif