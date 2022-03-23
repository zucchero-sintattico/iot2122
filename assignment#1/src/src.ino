#include "potentiometer.h"
#include "fade.h"



void setup() {
  Serial.begin(9600);
  pinMode(FADE_PIN, OUTPUT); // TODO: meglio metterlo come fadeSetup()?
}

void loop() {
  Serial.println("ciao");
  delay(1000);
}
