#include "Sugar.h"

Sugar::Sugar(uint8_t pin) : Potentiometer(pin) {}

int Sugar::getPercentage() {
    return map(this->getValue(), 0, 1023, 0, 100);
}