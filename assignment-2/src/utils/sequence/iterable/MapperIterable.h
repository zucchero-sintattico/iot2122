#ifndef _MAPPER_ITERABLE_H_
#define _MAPPER_ITERABLE_H_

#include "Iterable.h"
#include "utils/functional/function/Function.h"


template<class T, class O>
class MapperIterable : public Iterable<O> {
    private:
    Iterable<T>* source;
    Function<T, O>* mapper;
    public:
    MapperIterable(Iterable<T>* source, Function<T, O>* mapper) : source(source), mapper(mapper) {};

    bool hasNext() {
        return this->source->hasNext();
    }

    O get() {
        return this->mapper->apply(this->source->next());
    }
};

#endif