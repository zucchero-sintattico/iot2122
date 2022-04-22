#include "Function.h"

template<class T, class R>
R Function<T, R>::apply(T elem) {
    return this->functionalFunction(elem);
}

template<class T, class R>
template<class V>
Function<T, V> Function<T, R>::AndThen(Function<R, V> *after) {
    return new Function<T, V>([&](T elem) {
        return after->apply(this->apply(elem));
    });
}

template<class T, class R>
template<class V>
Function<V, R> Function<T, R>::Compose(Function<V, T> *before) {
    return new Function<V, R>([&](V elem) {
        return this->apply(before->apply(elem));
    });
}

