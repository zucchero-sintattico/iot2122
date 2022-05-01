#ifndef _TIMER_H_
#define _TIMER_

class Timer {

    public:
    Timer();
    void setupFreq(int freq);
    /* period in ms */
    void setupPeriod(int period);
    void waitForNextTick();

};


#endif