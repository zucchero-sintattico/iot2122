#include <Arduino.h>

#include "config.h"
#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"


FadeManager *fadeManager = new FadeManager(9, 10, 5);
SleepManager *sleepManager = new SleepManager((uint8_t[4]){5, 6, 7, 8});

void setup() {
  Serial.begin(SERIAL_VELOCITY);
  sleepManager->setup();
  fadeManager->setup();
}

void loop() {
  Serial.println("Going to sleep");
  delay(500);
  sleepManager->sleep();
  Serial.println("Waked up");
  delay(500);
}
