#ifndef _BIFUNCTION_H_
#define _BIFUNCTION_H_

#include "../function/Function.h"
/**
 * Transform an element of type T in an element of type R.
 */
template<class I1, class I2, class O>
using FunctionalBiFunction = O(*)(I1, I2);

template<class I1, class I2, class O>
class BiFunction {
private:
    FunctionalBiFunction<I1, I2, O> functionalBiFunction;
public:
    explicit BiFunction(FunctionalBiFunction<I1, I2, O> functionalBiFunction) : functionalBiFunction(
            functionalBiFunction) {};

    O apply(I1 i1, I2 i2);

    template<class X>
    BiFunction<I1, I2, X> AndThen(Function<O, X> after);

    template<class X>
    BiFunction<I1, I2, X> AndThen(FunctionalFunction<O, X> after) { return AndThen(new Function<O, X>(after)); };

};


#endif