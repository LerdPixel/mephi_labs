#pragma once
#include "Pair.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "smart_ptrs/shared_ptr.h"
#include "ISortedSequence.h"
#include "Sorter.h"
#include "QuickSorter.h"
#include "InsertionSorter.h"
#include "smart_ptrs/sharedFromT.h"
#include "smartPtrPairComparator.h"
#define NOT_SORTED_GAP 10


template <typename T>
class SortedPointerSequence : public ISortedSequence<T> {
protected:
    shared_ptr<Sorter<shared_ptr<T>>> fastSort;
    shared_ptr<Sorter<shared_ptr<T>>> stableSort;
    shared_ptr<Sequence<shared_ptr<T>>> data;
    bool (*_cmp)(shared_ptr<T>, shared_ptr<T>);
    bool (*_isEqual)(shared_ptr<T>, shared_ptr<T>);
    bool isSorted;
    size_t notSortedCount = 0;
    void setSorts() {
        fastSort = std::move(shared_ptr<Sorter<shared_ptr<T>>>(new QuickSorter<shared_ptr<T>>(_cmp, data)));
        stableSort = std::move(shared_ptr<Sorter<shared_ptr<T>>>(new InsertionSorter<shared_ptr<T>>(_cmp, data)));
    }
    void Sort() {
        if (isSorted)
            return;
        if (notSortedCount > NOT_SORTED_GAP) {
            fastSort->Sort();
        }
        else {
            stableSort->Sort();
        }
        isSorted = true;
    }
public:
    SortedPointerSequence(bool (*cmp)(shared_ptr<T>, shared_ptr<T>) = smartPtrPairComparator, bool (*isEqual)(shared_ptr<T>, shared_ptr<T>) = smartPtrPairEqual) : isSorted(true), notSortedCount(0), _cmp(cmp), _isEqual(isEqual)  {
        data = shared_ptr<Sequence<shared_ptr<T>>>(new ArraySequence<shared_ptr<T>>());
        setSorts();
    }
    SortedPointerSequence(const ICollection<T> &collection,  bool (*cmp)(shared_ptr<T>, shared_ptr<T>) = smartPtrPairComparator, bool(*isEqual)(shared_ptr<T>, shared_ptr<T>) = smartPtrPairEqual) : _cmp(cmp), _isEqual(isEqual) {
        setSorts();
        shared_ptr<Sequence<T>> array(new ArraySequence<T>(collection));
        data = shared_ptr<Sequence<shared_ptr<T>>>(array->Map<ArraySequence<shared_ptr<T>>,  shared_ptr<T>>(sharedFromT<T>));
        notSortedCount = collection.GetLength();
        if (notSortedCount > 1) {
            isSorted = false;
        } else {
            isSorted = true;
        }
    }
    SortedPointerSequence(const Sequence<T> *sequence, bool (*cmp)(T, T) = smartPtrPairComparator, bool(*isEqual)(T, T) = smartPtrPairEqual) : data(sequence->Map<ArraySequence<shared_ptr<T>>,  shared_ptr<T>>(sharedFromT<T>)), _cmp(cmp), _isEqual(isEqual) {
        setSorts();
        notSortedCount = sequence->GetLength();
        if (notSortedCount > 1) {
            isSorted = false;
        } else {
            isSorted = true;
        }
    }
    void Add(T item) override {
        isSorted = false;
        ++notSortedCount;
        data->Append(make_shared<T>(item));
    }
    void AddMany(shared_ptr<Sequence<T>> sequence) {
        isSorted = false;
        notSortedCount += sequence->GetLength();
        data->Concat(sequence->Map<ArraySequence<shared_ptr<T>>,  shared_ptr<T>>(sharedFromT<T>));
    }
    int IndexOf(T element) override {
        this->Sort();
        shared_ptr<T> elementPointer(make_shared<T>(element));
        int start = 0, end = data->GetLength() - 1, mid; 
        while(start <= end) {
            mid = (start + end) / 2;
            if (_isEqual(data->Get(mid), elementPointer))
                return mid;
            if (_cmp(data->Get(mid), elementPointer)) {
                start = mid + 1;
            }
            else {
                end = mid - 1;
            }
        }
        return -1;
    }
    shared_ptr<T>
    shared_ptr<Sequence<shared_ptr<T>>> GetValues() override {
        Sort();
        return data;
    }
    int GetLength() const override {
        return data->GetLength();
    }
    bool GetIsEmpty() const override {
        return data->GetLength() > 0;
    }
    T GetFirst() override {
        Sort();
        return *data->GetFirst();
    }
    T GetLast() override {
        Sort();
        return *data->GetLast();
    }
    ~SortedPointerSequence() {}
};