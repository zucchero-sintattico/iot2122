#include "fade.h"

int value = 0;
bool inc = true;
unsigned long prevOperationTimestamp = 0;

void fade() {
  unsigned long newOperationTimestamp = millis();
  if (newOperationTimestamp - prevOperationTimestamp > FADE_INTERVAL) {
    prevOperationTimestamp = newOperationTimestamp;
    analogWrite(FADE_PIN, value);
    value += inc ? 1 : -1;
    if (value >= 255 || value <= 0) {
      inc = !inc;
    }
  }
}
