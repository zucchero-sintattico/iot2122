#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "utils/functional/consumer/Consumer.h"
#include "utils/functional/function/Function.h"
#include "utils/functional/BiFunction.h"
#include "utils/functional/predicate/Predicate.h"

template<class T>
class Sequence {
private:
    T *elements;
    int size{};

    Sequence(T *elems, int size);

public:
    static Sequence<T> *of(T *elems, int size);

    void foreach(Consumer<T> consumer);

    template<class O>
    Sequence<O> *map(Function<T, O> mapper);

    Sequence<T> *filter(Predicate<T> predicate);

    template<class O>
    O *reduce(O initialValue, Function<O, T, O> reducer);

    template<class O>
    O *reduce(O initialValue, BiFunctionFunction <O, T, O> reducer);

    /*
     * CONVERSIONS
     */

    void foreach(FunctionalConsumer<T> functionalConsumer) { this->foreach(new Consumer<T>(functionalConsumer)); }

    template<class O>
    Sequence<O> *map(FunctionalFunction<T, O> mapper) { return this->map(new Function<T, O>(mapper)); };

    Sequence<T> *filter(FunctionalPredicate<T> predicate) { return this->filter(new Predicate<T>(predicate)); };


};

#endif