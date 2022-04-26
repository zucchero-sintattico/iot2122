#ifndef _SUPPLIER_ITERABLE_H_
#define _SUPPLIER_ITERABLE_H_

#include "./Iterable.h"
#include "utils/functional/supplier/Supplier.h"

template<class T>
class SupplierIterable : public Iterable<T> {
    private:
    Supplier<T>* supplier;
    public:
    explicit SupplierIterable(Supplier<T>* supplier) : supplier(supplier) {};

    bool hasNext() {
        return true;
    }

    T get() {
        return this->supplier->get();
    }
};

#endif