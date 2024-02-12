#ifndef INSERTION_SORTER_H
#define INSERTION_SORTER_H
#include "Sorter.h"

template <typename T>
class InsertionSorter : public Sorter<T> {
protected:
    void _sort() override {
        int j;
        T key;
        for (int i = 1; i < this->_sequence->GetLength(); ++i) {
            key = this->_sequence->Get(i);
            for (j = i - 1; j >= 0 && this->compare(key, this->_sequence->Get(j)); --j) {
                (*this->_sequence)[j + 1] = this->_sequence->Get(j);
            }
            (*this->_sequence)[j + 1] = key;
        }
    }
public:
    InsertionSorter(bool (*cmp)(T, T), shared_ptr<Sequence<T>> sequence) : Sorter<T>(cmp, sequence) {}
};

#endif
