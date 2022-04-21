#ifndef _JSTREAM_H_
#define _JSTREAM_H_

template<class T>
class JStream {
    private:
    T* elements;
    int size;

    JStream(T* elems, int size) {
        this->elements = elems;
        this->size = size;
    }

    public:
    static JStream* of(T* elems, int size) {
        return new JStream<T>(elems, size);
    }

    void foreach(void (*func)(T)) {
        for (int i = 0; i < this->size; i++) {
            func(elements[i]);
        }
    }

    template<class O>
    JStream<O>* map(O(*func)(T)) {
        O* newElements = new O[this->size];
        for (int i = 0; i < this->size; i++) {
            newElements[i] = func(elements[i]);
        }
        return JStream<O>::of(newElements, this->size);
    }

    JStream<T>* filter(bool(*func)(T)) {
        T* newElements = new T[this->size];
        int newElementsIndex = 0;
        for (int i = 0; i < this->size; i++) {
            if (func(elements[i])) {
                newElements[newElementsIndex++] = elements[i];
            }
        }
        return JStream<T>::of(newElements, newElementsIndex);
    }

};

#endif