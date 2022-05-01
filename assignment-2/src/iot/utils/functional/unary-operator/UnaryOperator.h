#ifndef _UNARY_OPERATOR_H_
#define _UNARY_OPERATOR_H_

#include "../function/Function.h"

template<class T>
using FunctionalUnaryOperator = FunctionalFunction<T, T>;

template<class T>
class UnaryOperator : public Function<T, T> {
public:
    UnaryOperator(FunctionalUnaryOperator<T> functionalUnaryOperator) : Function<T, T>(functionalUnaryOperator) {};
};


#endif