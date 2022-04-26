#ifndef _PREDICATE_H_
#define _PREDICATE_H_

#include "utils/functional/function/Function.h"

template<class X>
using FunctionalPredicate = FunctionalFunction<X, bool>;

template<class T>
class Predicate {
    private:
    FunctionalPredicate<T> functionalPredicate;
    public:
    explicit Predicate(FunctionalPredicate<T> predicateFunction) : functionalPredicate(predicateFunction) {};

    bool test(T elem) {
        return this->functionalPredicate(elem);
    }

    Predicate<T> And(Predicate<T> otherPredicate) {
        return new Predicate<T>([&](T elem) {
            return this->test(elem) && otherPredicate.test(elem);
            });
    };

    Predicate<T> And(FunctionalPredicate<T> otherPredicate) { return And(new Predicate<T>(otherPredicate)); };

    Predicate<T> Or(Predicate<T> otherPredicate) {
        return new Predicate<T>([&](T elem) {
            return this->test(elem) || otherPredicate.test(elem);
            });
    }

    Predicate<T> Or(FunctionalPredicate<T> otherPredicate) { return Or(new Predicate<T>(otherPredicate)); };

    Predicate<T> negate() {
        return new Predicate<T>([&](T elem) {
            return !this->test(elem);
            });
    };
};


#endif
