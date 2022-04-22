#include "Sequence.h"

template<class T, class O>
class MapperIterable : public Iterable<O> {
private:
    Iterable<T> *source;
    Function<T, O> *mapper;
public:
    MapperIterable(Iterable<T> *source, Function<T, O> *mapper) : source(source), mapper(mapper) {};

    bool hasNext() {
        return this->source->hasNext();
    }

    O get() {
        return this->mapper->apply(this->source->next());
    }
};

template<class T>
class FilterIterable : public Iterable<T> {
private:
    Iterable<T> *source;
    Predicate<T> *filter;
    T nextElement;
public:
    FilterIterable(Iterable<T> *source, Predicate<T> *filter) : source(source), filter(filter) {};

    bool hasNext() {
        if (!this->source->hasNext()) {
            return false;
        }
        this->nextElement = this->source->next();
        while (!this->filter->test(this->nextElement)) {
            if (!this->source->hasNext()) return false;
            this->nextElement = this->source->next();
        }
        return true;
    }

    T get() {
        return this->nextElement;
    }
};

template<class T>
class SupplierIterable : public Iterable<T> {
private:
    Supplier<T> *supplier;
public:
    explicit SupplierIterable(Supplier<T> *supplier) : supplier(supplier) {};

    bool hasNext() {
        return true;
    }

    T get() {
        return this->supplier->get();
    }
};

template<class T>
class IterateIterable : public Iterable<T> {
private:
    T value;
    UnaryOperator<T> *unaryOperator;
public:
    IterateIterable(T seed, UnaryOperator<T> *unaryOperator) : value(seed), unaryOperator(unaryOperator) {};

    bool hasNext() {
        return true;
    }

    T get() {
        this->value = this->unaryOperator->apply(this->value);
    }
};

template<class T>
void Sequence<T>::foreach(Consumer<T> *consumer) {
    while (this->source->hasNext()) consumer->accept(this->source->next());
}

template<class T>
template<class O>
Sequence<O> *Sequence<T>::map(Function<T, O> *mapper) {
    return new Sequence<O>(new MapperIterable<T, O>(this->source, mapper));
}

template<class T>
Sequence<T> *Sequence<T>::filter(Predicate<T> *predicate) {
    return new Sequence<T>(new FilterIterable<T>(this->source, predicate));
}

template<class T>
template<class O>
O *Sequence<T>::reduce(O initialValue, BiFunction<O, T, O> *reducer) {
    O result = initialValue;
    while (this->source->hasNext()) {
        result = reducer->apply(result, this->source->next());
    }
    return result;
}

/*
 * STATIC METHODS
 */


template<class T>
Sequence<T> *Sequence<T>::of(Iterable<T> *source) { return new Sequence<T>(source); }

template<class T>
Sequence<T> *Sequence<T>::of(T *elems, int size) { return of(new IterableArray<T>(elems, size)); }

template<class T>
Sequence<T> *Sequence<T>::generate(Supplier<T> *supplier) {
    return new Sequence<T>(new SupplierIterable<T>(supplier));
}

template<class T>
Sequence<T> *Sequence<T>::iterate(T seed, UnaryOperator<T> *unaryOperator) {
    return new Sequence<T>(new IterateIterable<T>(seed, unaryOperator));
}




