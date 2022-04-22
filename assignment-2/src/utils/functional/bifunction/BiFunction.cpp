#include "BiFunction.h"

template<class I1, class I2, class O>
O BiFunction<I1, I2, O>::apply(I1 i1, I2 i2) {
    return this->functionalBiFunction(i1, i2);
}

template<class I1, class I2, class O>
template<class X>
BiFunction<I1, I2, X> BiFunction<I1, I2, O>::AndThen(Function<O, X> after) {
    return new BiFunction<I1, I2, X>([&](I1 i1, I2 i2) {
        return after.apply(this->apply(i1, i2));
    });
}
