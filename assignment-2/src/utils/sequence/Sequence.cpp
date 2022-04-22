#include "Sequence.h"

template<class T>
Sequence<T>::Sequence(T *elems, int size) {
    this->elements = elems;
    this->size = size;
}

template<class T>
Sequence<T> *Sequence<T>::of(T *elems, int size) {
    return new Sequence<T>(elems, size);
}

template<class T>
void Sequence<T>::foreach(Consumer<T> consumer) {
    for (int i = 0; i < this->size; i++) {
        consumer(elements[i]);
    }
}

template<class T>
template<class O>
Sequence<O> *Sequence<T>::map(Function<T, O> mapper) {
    O *newElements = new O[this->size];
    for (int i = 0; i < this->size; i++) {
        newElements[i] = mapper.apply(elements[i]);
    }
    return Sequence<O>::of(newElements, this->size);
}

template<class T>
Sequence<T> *Sequence<T>::filter(Predicate<T> predicate) {
    T *newElements = new T[this->size];
    int newElementsIndex = 0;
    for (int i = 0; i < this->size; i++) {
        if (predicate.test(elements[i])) {
            newElements[newElementsIndex++] = elements[i];
        }
    }
    return Sequence<T>::of(newElements, newElementsIndex);
}

template<class T>
template<class O>
O *Sequence<T>::reduce(O initialValue, BiFunction<O, T, O> reducer) {
    O result = initialValue;
    for (int i = 0; i < this->size; i++) {
        result = reducer.apply(result, this->elements[i]);
    }
    return result;
}

template<class T>
template<class O>
O *Sequence<T>::reduce(O initialValue, BiFunctionFunction<O, T, O> reducer) {
    return this->reduce(initialValue, new BiFunction<O, T, O>(reducer));
}

