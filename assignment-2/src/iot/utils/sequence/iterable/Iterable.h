#ifndef _ITERABLE_H_
#define _ITERABLE_H_

template<class T>
class Iterable {

    public:

    virtual bool hasNext() = 0;

    virtual T next() = 0;
};

#endif