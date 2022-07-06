#ifndef _LIST_H_
#define _LIST_H_

template<typename T>
class List {
private:
    static const int DEFAULT_START_SIZE = 10;
    T* elements;
    int size = 0;
    int capacity = 0;

    void resize() {
        capacity = capacity * 2;
        T* newElements = new T[capacity];
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

public:

    List() : List(DEFAULT_START_SIZE) {};

    List(int capacity) {
        this->capacity = capacity;
        elements = new T[capacity];
    }

    void remove(T element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                for (int j = i; j < size - 1; j++) {
                    elements[j] = elements[j + 1];
                }
                size--;
                return;
            }
        }
    }

    void add(T element) {
        if (size == capacity) {
            resize();
        }
        elements[size] = element;
        size++;
    }

    bool isElementPresent(T element) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == element) {
                return true;
            }
        }
        return false;
    }

    T get(int index) {
        return elements[index];
    }

    int getSize() {
        return size;
    }


};

#endif