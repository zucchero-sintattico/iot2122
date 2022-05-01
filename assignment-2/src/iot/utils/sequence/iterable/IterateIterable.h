#ifndef _ITERATE_ITERABLE_H_
#define _ITERATE_ITERABLE_H_

#include "./Iterable.h"
#include "utils/functional/unary-operator/UnaryOperator.h"

template<class T>
class IterateIterable : public Iterable<T> {
    private:
    T value;
    UnaryOperator<T>* unaryOperator;
    public:
    IterateIterable(T seed, UnaryOperator<T>* unaryOperator) : value(seed), unaryOperator(unaryOperator) {};

    bool hasNext() {
        return true;
    }

    T get() {
        this->value = this->unaryOperator->apply(this->value);
    }
};

#endif