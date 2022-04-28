#ifndef _FSM_H_
#define _FSM_H_

#include <Arduino.h>

template<class S>
class FiniteStateMachine {

private:
    S state;

public:
    FiniteStateMachine(S initialState) : state(initialState) {}

    void setState(S newState) {
        state = newState;
    }

    S getState() {
        return state;
    }

};

#endif