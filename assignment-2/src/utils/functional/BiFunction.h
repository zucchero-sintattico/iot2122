#ifndef _BIFUNCTION_H_
#define _BIFUNCTION_H_

/**
 * Transform two element of type I1 and I2 into an element of type O.
 */
template<class I1, class I2, class O>
using BiFunctionFunction = O(*)(I1, I2);

template<class I1, class I2, class O>
class BiFunction {

private:
    BiFunctionFunction<I1, I2, O> biFunction;
public:

    explicit BiFunction(BiFunctionFunction<I1, I2, O> biFunction) {
        this->biFunction = biFunction;
    }

    O apply(I1 i1, I2 i2) {
        return this->biFunction(i1, i2);
    }
};

#endif
