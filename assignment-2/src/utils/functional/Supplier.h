#ifndef _SUPPLIER_H_
#define _SUPPLIER_H_

/**
 * Supply an element of type T.
 */
template<class T>
using SupplierFunction = T(*)();

template<class T>
class Supplier {

private:
    SupplierFunction<T> supplier;
public:
    Supplier(SupplierFunction<T> supplier) {
        this->supplier = supplier;
    };

    T get() {
        return this->supplier();
    };
};

#endif