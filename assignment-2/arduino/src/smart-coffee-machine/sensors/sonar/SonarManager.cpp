#include "SonarManager.h"
#include <Arduino.h>

SonarManager::SonarManager(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

void SonarManager::setup() {
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);  
}

void SonarManager::computeRead() {
    /* send signal */
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);
    
    /* receive echo */
    float tUS = pulseIn(echoPin, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    this->distance = t*vs;
}

float SonarManager::getDistanceInCM() {
    return this->distance;
}