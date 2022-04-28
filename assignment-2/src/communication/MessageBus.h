#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

template<class M>
class MessageBus {
private:
    struct Node {
        M message;
        Message* next;
    };
    Node* first;
    Node* last;
    int size;
public:
    void push(M message);
    M* getMessages();
    bool isMessagePresent(M message);
    void removeMessage(M message);
    int getSize();
};

#endif