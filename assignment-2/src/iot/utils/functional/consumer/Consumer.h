#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "../function/Function.h"

template<class T>
using FunctionalConsumer = FunctionalFunction<T, void>;

template<typename T>
class Consumer {
private:
    FunctionalConsumer<T> functionalConsumer;
public:
    Consumer(FunctionalConsumer<T> functionalConsumer) : functionalConsumer(functionalConsumer) {};

    void accept(T elem) {
        this->functionalConsumer(elem);
    }

    Consumer<T>* AndThen(Consumer<T>* after) {
        return new Consumer<T>([&](T elem) {
            this->accept(elem);
            after->accept(elem);
            });
    }

    Consumer<T>* AndThen(FunctionalConsumer<T>* after) { return AndThen(new Consumer<T>(after)); };

};

#endif