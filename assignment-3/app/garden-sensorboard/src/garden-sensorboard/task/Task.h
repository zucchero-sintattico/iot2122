#ifndef _TASK_H_
#define _TASK_H_

#include <Arduino.h>

class Task {

    private:
    unsigned int delay;

    public:
    Task(unsigned int delay) {
        this->delay = delay;
    }

    void run() {
        for (;;) {
            this->loop();
            vTaskDelay(delay);
        }
    }

    virtual void loop() = 0;
};

#endif