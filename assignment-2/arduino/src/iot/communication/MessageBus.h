#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_
#include <Arduino.h>


template<typename M>
class MessageBus {
private:
    M messages[100];
    int size = 0;
public:

    void print() {
        Serial.print("Messages: ");
        for (int i = 0; i < size; i++) {
            Serial.print(messages[i]);
            Serial.print(", ");
        }
        Serial.println();
    }

    void push(M message) {
        messages[size] = message;
        size++;
    }

    bool isMessagePresent(M message) {
        for (int i = 0; i < size; i++) {
            if (messages[i] == message) {
                return true;
            }
        }
        return false;
    }

    void removeMessage(M message) {
        for (int i = 0; i < size; i++) {
            if (messages[i] == message) {
                for (int j = i; j < size - 1; j++) {
                    messages[j] = messages[j + 1];
                }
                size--;
                return;
            }
        }
    }

    int getSize() {
        return this->size;
    }
};

#endif