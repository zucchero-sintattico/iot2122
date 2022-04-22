#include "Supplier.h"

template<class T>
T Supplier<T>::get() {
    return this->functionalSupplier();
}