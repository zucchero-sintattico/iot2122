#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "utils/functional/consumer/Consumer.h"
#include "utils/functional/function/Function.h"
#include "utils/functional/bifunction/BiFunction.h"
#include "utils/functional/predicate/Predicate.h"
#include "utils/functional/supplier/Supplier.h"
#include "utils/functional/unary-operator/UnaryOperator.h"

template<class T>
class Iterable {
    virtual bool hasNext() = 0;

    virtual T next() = 0;
};

template<class T>
class IterableArray : public Iterable<T> {

private:
    T *elements;
    int size;
    int index = 0;
public:
    IterableArray(T *elems, int size) : elements(elems), size(size) {};

    bool hasNext() {
        return this->index < this->size;
    }

    T get() {
        return this->elements[this->index++];
    }
};

template<class T>
class Sequence {
private:
    Iterable<T> *source;

    explicit Sequence(Iterable<T> *source) : source(source) {};
public:

    static Sequence<T> *of(Iterable<T> *source);

    static Sequence<T> *of(T *elems, int size);

    static Sequence<T> *generate(Supplier<T> *supplier);

    static Sequegnce <T> *iterate(T seed, UnaryOperator<T> *unaryOperator);


    void foreach(Consumer<T> *consumer);

    template<class O>
    Sequence<O> *map(Function<T, O> *mapper);

    Sequence<T> *filter(Predicate<T> *predicate);

    template<class O>
    O *reduce(O initialValue, BiFunction<O, T, O> *reducer);


    /*
     * CONVERSIONS
     */

    void foreach(FunctionalConsumer<T> functionalConsumer) { this->foreach(new Consumer<T>(functionalConsumer)); }

    template<class O>
    Sequence<O> *map(FunctionalFunction<T, O> mapper) { return this->map(new Function<T, O>(mapper)); };

    Sequence<T> *filter(FunctionalPredicate<T> predicate) { return this->filter(new Predicate<T>(predicate)); };

    template<class O>
    O *reduce(O initialValue, FunctionalBiFunction<O, T, O> reducer) {
        return this->reduce(initialValue,
                            new BiFunction<O, T, O>(
                                    reducer));
    }


    static Sequence<T> *generate(FunctionalSupplier<T> supplier) { return generate(new Supplier<T>(supplier)); };

    static Sequence<T> *iterate(T seed, FunctionalUnaryOperator<T> unaryOperator) {
        return iterate(seed,
                       new UnaryOperator<T>(
                               unaryOperator));
    };
};

#endif