#include <Arduino.h>
#include "config.h"

/*****************************/
#ifndef FADE_PIN
  #define FADE_PIN 9
#endif
#ifndef FADE_INTERVAL
  #define FADE_INTERVAL 2
#endif
/*****************************/

/**
 * Produce fade on FADE_PIN with 
 */
void fade();
