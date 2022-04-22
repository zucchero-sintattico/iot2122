#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

template<class T>
class Sequence {
private:
    T *elements;
    int size;

    Sequence(T *elems, int size) {
        this->elements = elems;
        this->size = size;
    }

public:
    static Sequence *of(T *elems, int size) {
        return new JStream<T>(elems, size);
    }

    void foreach(void (*func)(T)) {
        for (int i = 0; i < this->size; i++) {
            func(elements[i]);
        }
    }

    template<class O>
    Sequence<O> *map(O(*func)(T)) {
        O *newElements = new O[this->size];
        for (int i = 0; i < this->size; i++) {
            newElements[i] = func(elements[i]);
        }
        return Sequence<O>::of(newElements, this->size);
    }

    Sequence<T> *filter(bool(*func)(T)) {
        T *newElements = new T[this->size];
        int newElementsIndex = 0;
        for (int i = 0; i < this->size; i++) {
            if (func(elements[i])) {
                newElements[newElementsIndex++] = elements[i];
            }
        }
        return Sequence<T>::of(newElements, newElementsIndex);
    }

};

#endif