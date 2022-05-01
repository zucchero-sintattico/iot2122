#ifndef _COMMUNICABLE_H_
#define _COMMUNICABLE_H_

#include "./MessageBus.h"

template<class M>
class Communicable {
    private:
    MessageBus<M>* messageBus;
    public:
    void attachMessageBus(MessageBus<M>* messageBus) {
        this->messageBus = messageBus;
    }
    MessageBus<M>* getMessageBus() {
        return this->messageBus;
    }
};

#endif