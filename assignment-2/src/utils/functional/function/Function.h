#ifndef _FUNCTION_H_
#define _FUNCTION_H_

/**
 * Transform an element of type T in an element of type R.
 */
template<class T, class R>
using FunctionalFunction = R(*)(T);

template<class T, class R>
class Function {
    private:
    FunctionalFunction<T, R>* functionalFunction;
    public:
    explicit Function(FunctionalFunction<T, R>* functionalFunction) : functionalFunction(functionalFunction) {};

    R apply(T elem) {
        return this->functionalFunction(elem);
    }

    template<class V>
    Function<T, V> AndThen(Function<R, V>* after) {
        return new Function<T, V>([&](T elem) {
            return after->apply(this->apply(elem));
            });
    }

    template<class V>
    Function<T, V> AndThen(FunctionalFunction<R, V>* after) { return AndThen(new Function<R, V>(after)); }

    template<class V>
    Function<V, R> Compose(Function<V, T>* before) {
        return new Function<V, R>([&](V elem) {
            return this->apply(before->apply(elem));
            });
    }

    template<class V>
    Function<V, R> Compose(FunctionalFunction<V, T>* before) { return Compose(new Function<V, T>(before)); };

};


#endif