#include "MessageBus.h"

template<class M>
void MessageBus<M>::push(M message) {
    this->last->next = new Node(message, nullptr);
    this->last = this->last->next;
    this->size++;
}

template<class M>
M* MessageBus<M>::getMessages() {
    M* messages = new M[this->size];
    Node* current = this->first;
    for (int i = 0; i < this->size; i++) {
        messages[i] = current->message;
        current = current->next;
    }
    return messages;
}

template<class M>
bool MessageBus<M>::isMessagePresent(M message) {
    Node* current = this->first;
    while (current != nullptr) {
        if (current->message == message) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<class M>
int MessageBus<M>::getSize() {
    return this->size;
}

template<class M>
void MessageBus<M>::removeMessage(M message) {
    Node* current = this->first;
    Node* previous = nullptr;
    while (current != nullptr) {
        if (current->message == message) {
            if (previous == nullptr) {
                this->first = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            this->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}