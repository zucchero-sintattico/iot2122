#include "fade.h"

int brightness = 0;
int fadeAmount = 5;
unsigned long prevOperationTimestamp = 0;

void fadeSetup() {
  pinMode(FADE_PIN, OUTPUT);
}

void fade() {
  unsigned long newOperationTimestamp = millis();
  if (newOperationTimestamp - prevOperationTimestamp > FADE_INTERVAL) {
    prevOperationTimestamp = newOperationTimestamp;
    analogWrite(FADE_PIN, brightness);
    brightness += fadeAmount;
    if (brightness >= 255 || brightness <= 0) {
      fadeAmount = -fadeAmount;
    }
  }
}

void stopFade() {
  brightness = 0;
  fadeAmount = 5;
  analogWrite(FADE_PIN, LOW);
}
