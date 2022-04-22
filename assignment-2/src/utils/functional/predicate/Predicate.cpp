#include "Predicate.h"

template<class T>
bool Predicate<T>::test(T elem) {
    return this->predicateFunction(elem);
}

template<class T>
Predicate<T> Predicate<T>::And(Predicate<T> otherPredicate) {
    return new Predicate<T>([&](T elem) {
        return this->predicateFunction(elem) && otherPredicate.test(elem);
    });
};

template<class T>
Predicate<T> Predicate<T>::Or(Predicate<T> otherPredicate) {
    return new Predicate<T>([&](T elem) {
        return this->predicateFunction(elem) || otherPredicate.test(elem);
    });
}

template<class T>
Predicate<T> Predicate<T>::negate() {
    return new Predicate<T>([&](T elem) {
        return !this->test(elem);
    });
};
