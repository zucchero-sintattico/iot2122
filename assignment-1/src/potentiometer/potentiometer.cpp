#include "potentiometer.h"

int readPotentiometer() {
  return analogRead(POT_PIN);
}

int getDifficult() {
  return map(readPotentiometer(), 0, 1024, 0, DIFFICULTY_LEVELS);
}
