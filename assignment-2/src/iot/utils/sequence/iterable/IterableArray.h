#ifndef _ITERABLE_ARRAY_H_
#define _ITERABLE_ARRAY_H_

#include "Iterable.h"

template<class T>
class IterableArray : public Iterable<T> {

    private:
    T* elements;
    int size;
    int index = 0;
    public:
    IterableArray(T* elems, int size) : elements(elems), size(size) {};

    bool hasNext() {
        return this->index < this->size;
    }

    T next() {
        return this->elements[this->index++];
    }
};

#endif