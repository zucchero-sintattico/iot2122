#include <Arduino.h>

#include "FadeManager.h"

FadeManager::FadeManager(uint8_t fadePin, uint8_t fadeIntervalMilliSeconds, uint8_t fadeAmount){
    this->fadePin = fadePin;
    this->fadeIntervalMilliSeconds = fadeIntervalMilliSeconds;
    this->fadeAmount = fadeAmount;
    this->prevOperationTimestamp = 0;
}

void FadeManager::setup(){
    pinMode(this->fadePin, OUTPUT);
}


void FadeManager::fade() {
  unsigned long newOperationTimestamp = millis();
  if (newOperationTimestamp - this->prevOperationTimestamp > this->fadeIntervalMilliSeconds) {
    this->prevOperationTimestamp = newOperationTimestamp;

    analogWrite(this->fadePin, this->brightness);
    this->brightness += this->fadeAmount;
    if (this->brightness >= 255 || this->brightness <= 0) {
      this->fadeAmount = -this->fadeAmount;
    }
  }
}

void FadeManager::stopFade() {
  this->brightness = 0;
  analogWrite(this->fadePin, LOW);
}