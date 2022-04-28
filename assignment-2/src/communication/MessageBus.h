#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

template<class M>
class MessageBus {
private:
    struct Node {
        M message;
        Node* next;
    };
    Node* first = nullptr;
    Node* last = nullptr;
    int size = 0;
public:

    void push(M message) {
        Node* node = new Node();
        node->message = message;
        node->next = nullptr;
        if (first == nullptr) {
            first = node;
            last = node;
        }
        else {
            last->next = node;
            last = node;
        }
        this->size++;
    }

    bool isMessagePresent(M message) {
        Node* current = this->first;
        while (current != nullptr) {
            if (current->message == message) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void removeMessage(M message) {
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

    int getSize() {
        return this->size;
    }
};

#endif