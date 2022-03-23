#include "sleep.h"
#include "fade.h"

unsigned long prevWakeUpTime = 0;
bool resetTimer = false;

void sleep() {

    if (resetTimer) {
        prevWakeUpTime = millis();
        resetTimer = false;
    }

    if (millis() - prevWakeUpTime > SECONDS_TO_SLEEP * 1000) {
        stopFade();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        sleep_disable();
        resetTimer = true;
    }
}