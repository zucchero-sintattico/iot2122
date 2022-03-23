#include "potentiometer.h"
#include "fade.h"

unsigned long time0 = 0;
bool stopped = false;

void setup() {
  Serial.begin(9600);
  fadeSetup();
}

void loop() {
  fade();
}
