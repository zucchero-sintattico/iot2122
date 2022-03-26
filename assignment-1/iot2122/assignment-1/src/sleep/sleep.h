#include <avr/sleep.h>
#include <Arduino.h>
/*****************************/
#ifndef BUTTONS_NUMBER
  #define BUTTONS_NUMBER 4
#endif
#ifndef BASE_BUTTON_PIN
  #define BASE_BUTTON_PIN 2
#endif
#ifndef SECONDS_TO_SLEEP
  #define SECONDS_TO_SLEEP 10
#endif
/*****************************/


/**
 * Go in SLEEP_MODE_PWR_DOWN after SECONDS_TO_SLEEP
 */
void sleep();