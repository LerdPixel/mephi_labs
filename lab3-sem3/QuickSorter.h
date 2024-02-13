#ifndef QUICK_SORTER_H
#define QUICK_SORTER_H
#include "Sorter.h"

template <typename T>
class  QuickSorter : public Sorter<T> {
protected:
    int partition(int start, int end) {
        T pivot = this->_sequence->Get(start);
        int count = 0;
        for (int i = start + 1; i <= end; ++i) {
            if (this->compare(this->_sequence->Get(i), pivot))
                ++count;
        }
        // Giving pivot element its correct position
        int pivotIndex = start + count;
        this->swap(pivotIndex, start);

        int i = start, j = end;
    
        while (i < pivotIndex && j > pivotIndex) {
    
            while (this->compare(this->_sequence->Get(i), pivot)) {
                ++i;
            }
    
            while (this->compare(pivot, this->_sequence->Get(j))) {
                --j;
            }
    
            if (i < pivotIndex && j > pivotIndex) {
                this->swap(i++, j--);
            }
        }
    
        return pivotIndex;
    }
    void quicksort(int start, int end) {
        if (start >= end)
            return;
        int p = partition(start, end);
        quicksort(start, p - 1);
        quicksort(p + 1, end);
    }
    void _sort() override {
        quicksort(0, this->_sequence->GetLength()-1);
    }
public:
    QuickSorter(bool (*cmp)(T, T), shared_ptr<Sequence<T>> sequence) : Sorter<T>(cmp, sequence) {}

};


#endif