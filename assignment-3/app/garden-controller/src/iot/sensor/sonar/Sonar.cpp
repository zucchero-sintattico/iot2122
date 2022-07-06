#include "Sonar.h"

Sonar::Sonar(uint8_t trigPin, uint8_t echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

void Sonar::setup() {
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

void Sonar::computeRead() {
    /* send signal */
    digitalWrite(trigPin, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);

    /* receive echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    this->distance = t * vs;
}

float Sonar::getDistanceInCM() {
    return this->distance * 100;
}