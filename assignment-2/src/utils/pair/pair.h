#ifndef _PAIR_H_
#define _PAIR_H_

template <class L, class R>
class Pair {
public:
    L* left;
    R* right;

    Pair(L* l, R* r) : left(l), right(r) {}
};

#endif