#ifndef SORTER_H
#define SORTER_H
#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"

template <typename T>
class Sorter {
protected:
    shared_ptr<Sequence<T>> _sequence;
    bool (*compare)(T a, T b);
    void swap(int i, int j) { // sequence indexes
        T tmp = _sequence->Get(i);
        (*_sequence)[i] = _sequence->Get(j);
        (*_sequence)[j] = tmp;
    }
    bool isSorted = false;
public:
    Sorter(bool (*cmp)(T, T), shared_ptr<Sequence<T>> sequence) : _sequence(sequence), compare(cmp) {}
    virtual void Sort() = 0;
    shared_ptr<Sequence<T>> Release() { return _sequence; }
};


#endif