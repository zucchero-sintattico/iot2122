#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "utils/functional/consumer/Consumer.h"
#include "utils/functional/function/Function.h"
#include "utils/functional/bifunction/BiFunction.h"
#include "utils/functional/predicate/Predicate.h"
#include "utils/functional/supplier/Supplier.h"
#include "utils/functional/unary-operator/UnaryOperator.h"
#include "utils/sequence/iterable/Iterable.h"

#include "utils/sequence/iterable/IterableArray.h"
#include "utils/sequence/iterable/FilterIterable.h"
#include "utils/sequence/iterable/IterateIterable.h"
#include "utils/sequence/iterable/MapperIterable.h"
#include "utils/sequence/iterable/SupplierIterable.h"

template<class T>
class Sequence {
    private:
    Iterable<T>* source;


    public:

    Sequence(Iterable<T>* source) : source(source) {};

    static Sequence<T>* of(Iterable<T>* source) { return new Sequence<T>(source); }

    static Sequence<T>* of(T* elems, int size) { return Sequence<T>::of(new IterableArray<T>(elems, size)); }


    static Sequence<T>* generate(Supplier<T>* supplier) {
        return new Sequence<T>(new SupplierIterable<T>(supplier));
    }

    static Sequence<T>* iterate(T seed, UnaryOperator<T>* unaryOperator) {
        return new Sequence<T>(new IterateIterable<T>(seed, unaryOperator));
    }


    void foreach(Consumer<T>* consumer) {
        while (this->source->hasNext()) consumer->accept(this->source->next());
    }

    template<class O>
    Sequence<O>* map(Function<T, O>* mapper) {
        return new Sequence<O>(new MapperIterable<T, O>(this->source, mapper));
    }

    Sequence<T>* filter(Predicate<T>* predicate) {
        return new Sequence<T>(new FilterIterable<T>(this->source, predicate));
    }

    template<class O>
    O* reduce(O initialValue, BiFunction<O, T, O>* reducer) {
        O result = initialValue;
        while (this->source->hasNext()) {
            result = reducer->apply(result, this->source->next());
        }
        return result;
    }


    /*
     * CONVERSIONS
     */

    void foreach(FunctionalConsumer<T> functionalConsumer) { this->foreach(new Consumer<T>(functionalConsumer)); }

    template<class O>
    Sequence<O>* map(FunctionalFunction<T, O> mapper) { return this->map(new Function<T, O>(mapper)); };

    Sequence<T>* filter(FunctionalPredicate<T> predicate) { return this->filter(new Predicate<T>(predicate)); };

    template<class O>
    O* reduce(O initialValue, FunctionalBiFunction<O, T, O> reducer) {
        return this->reduce(initialValue,
            new BiFunction<O, T, O>(
                reducer));
    }


    static Sequence<T>* generate(FunctionalSupplier<T> supplier) { return generate(new Supplier<T>(supplier)); };

    static Sequence<T>* iterate(T seed, FunctionalUnaryOperator<T> unaryOperator) {
        return iterate(seed,
            new UnaryOperator<T>(
                unaryOperator));
    };
};

#endif