#ifndef _CONSUMER_H_
#define _CONSUMER_H_

template<class T>
using FunctionalConsumer = void (*)(T);

template<class T>
class Consumer {
private:
    FunctionalConsumer<T> functionalConsumer;
public:
    explicit Consumer(FunctionalConsumer<T> functionalConsumer) : functionalConsumer(functionalConsumer) {};

    void accept(T elem);

    Consumer<T> AndThen(Consumer<T> after);

    Consumer<T> AndThen(FunctionalConsumer<T> after) { return AndThen(new Consumer<T>(after)); };
    
};


#endif