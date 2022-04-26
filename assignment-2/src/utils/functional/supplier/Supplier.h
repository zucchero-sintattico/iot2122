#ifndef _SUPPLIER_H_
#define _SUPPLIER_H_

#include "../function/Function.h"

template<class T>
using FunctionalSupplier = T(*)();

template<class T>
class Supplier {
    private:
    FunctionalSupplier<T> functionalSupplier;
    public:
    explicit Supplier(FunctionalSupplier<T> functionalSupplier) : functionalSupplier(functionalSupplier) {};

    T get() {
        return this->functionalSupplier();
    }
};


#endif