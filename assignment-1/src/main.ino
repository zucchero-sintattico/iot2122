#define LIBCALL_ENABLEINTERRUPT

#include <Arduino.h>
#include "config.h"

//#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"


uint8_t wakeUpPins[4] = {5, 6, 7, 8};

//FadeManager *fadeManager = new FadeManager(9, 10, 5);
SleepManager *sleepManager = new SleepManager(wakeUpPins);

void setup() {
  Serial.begin(SERIAL_VELOCITY);
  Serial.println("SETUPP");
  sleepManager->setup();
  //fadeManager->setup();
}

void loop() {
  Serial.println("Going to sleep");
  delay(500);
  sleepManager->sleep();
  Serial.println("Waked up");
  delay(500);
}
