#include "Consumer.h"

template<class T>
void Consumer<T>::accept(T elem) {
    this->functionalConsumer(elem);
}

template<class T>
Consumer<T> Consumer<T>::AndThen(Consumer<T> after) {
    return Consumer<T>([&](T elem) {
        this->accept(elem);
        after.accept(elem);
    });
}
