#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_
#include <Arduino.h>
#include "iot/utils/list/List.h"

template<typename M>
class MessageBus {
    private:
    List<M>* messages = new List<M>();
    public:

    void push(M message) {
        messages->add(message);
    }

    bool isMessagePresent(M message) {
        return messages->isElementPresent(message);
    }

    void removeMessage(M message) {
        messages->remove(message);
    }

    int getSize() {
        return messages->getSize();
    }
};

#endif