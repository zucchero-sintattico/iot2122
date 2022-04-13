#ifndef _TASK_H_
#define _TASK_H_

class Task {

public:

    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif