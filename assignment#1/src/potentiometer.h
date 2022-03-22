#include <Arduino.h>
#include "config.h"

/*****************************/
#ifndef POT_PIN
  #define POT_PIN A0
#endif

#ifndef DIFFICULTY_LEVELS
  #define DIFFICULTY_LEVELS 8
#endif
/*****************************/

/**
 * Read from POT_PIN
 */
int readPotentiometer();

/**
 * Map 0 - 1023 to 0 - (DIFFICULTY_LEVELS - 1)
 */
int getDifficult();
