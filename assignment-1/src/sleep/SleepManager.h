#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

class SleepManager {
        
    private:
        unsigned long prevWakeUpTime = 0;
        bool resetTimer = false;
        
    public:
        SleepManager();
        void setup();
        void sleep();
};

#endif