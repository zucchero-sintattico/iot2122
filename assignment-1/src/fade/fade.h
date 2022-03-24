#include <Arduino.h>

/*****************************/
#ifndef FADE_PIN
  #define FADE_PIN 9
#endif
#ifndef FADE_INTERVAL
  #define FADE_INTERVAL 10
#endif
/*****************************/

/**
 * setup the pin FADE_PIN as output for fading
 */
void fadeSetup();

/**
 * Produce fade on FADE_PIN with FADE_INTERVAL ms interval
 */
void fade();

/**
 * Stop fade on FADE_PIN
 */
void stopFade();
