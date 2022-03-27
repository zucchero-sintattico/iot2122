#include <Arduino.h>

#include "FadeManager.h"

FadeManager::FadeManager(uint8_t fadePin, uint8_t fadeIntervalMilliSeconds = 10, uint8_t fadeAmount = 5) {
  this->fadePin = fadePin;
  this->fadeIntervalMilliSeconds = fadeIntervalMilliSeconds;
  this->fadeAmount = fadeAmount;
}

void FadeManager::setup() {
  pinMode(this->fadePin, OUTPUT);
}

void FadeManager::start() {
  this->prevOperationTimestamp = 0;
  this->brightness = 5;
}

bool FadeManager::hasTimeElapsedSinceLastFadeOperation() {
  return millis() - this->prevOperationTimestamp > this->fadeIntervalMilliSeconds;
}

void FadeManager::fade() {
  if (this->hasTimeElapsedSinceLastFadeOperation()) {
    this->prevOperationTimestamp = millis();
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