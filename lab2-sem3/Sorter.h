#ifndef SORTER_H
#define SORTER_H
#include "Sequence.h"
#include "smart_ptrs/shared_ptr.h"

template <typename T>
class Sorter {
protected:
    shared_ptr<Sequence<T>> _sequence;
    bool isSorted = false;
    bool (*compare)(T a, T b);
    void swap(int i, int j) { // sequence indexes
        T tmp = _sequence->Get(i);
        (*_sequence)[i] = _sequence->Get(j);
        (*_sequence)[j] = tmp;
    }
    virtual void _sort() = 0;
public:
    Sorter(bool (*cmp)(T, T), shared_ptr<Sequence<T>> sequence) : _sequence(sequence), compare(cmp) {}
    void Sort() {
        if (!isSorted)
            _sort();
        isSorted = true;
    }
    shared_ptr<Sequence<T>> Release() { return _sequence; }
};


#endif