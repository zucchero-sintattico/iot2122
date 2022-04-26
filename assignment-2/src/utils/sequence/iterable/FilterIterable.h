#ifndef _FILTER_ITERABLE_H_
#define _FILTER_ITERABLE_H_

#include "./Iterable.h"
#include "utils/functional/predicate/Predicate.h"

template<class T>
class FilterIterable : public Iterable<T> {
    private:
    Iterable<T>* source;
    Predicate<T>* filter;
    T nextElement;
    public:
    FilterIterable(Iterable<T>* source, Predicate<T>* filter) : source(source), filter(filter) {};

    bool hasNext() {
        if (!this->source->hasNext()) {
            return false;
        }
        this->nextElement = this->source->next();
        while (!this->filter->test(this->nextElement)) {
            if (!this->source->hasNext()) return false;
            this->nextElement = this->source->next();
        }
        return true;
    }

    T get() {
        return this->nextElement;
    }
};

#endif