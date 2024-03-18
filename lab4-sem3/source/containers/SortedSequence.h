#pragma once
#include "Sequence.h"
#include "ArraySequence.h"
#include "smart_ptrs/shared_ptr.h"
#include "ISortedSequence.h"
#include "Sorter.h"
#include "QuickSorter.h"
#include "InsertionSorter.h"
#include "baseComparator.h"

template <typename T>
class SortedSequence : public ISortedSequence<T> {
protected:
    shared_ptr<Sorter<T>> fastSort;
    shared_ptr<Sorter<T>> stableSort;
    shared_ptr<Sequence<T>> data;
    bool (*_cmp)(const T&, const T&);
    bool (*_isEqual)(const T&, const T&);
    bool isSorted;
    size_t notSortedCount = 0;
    static const size_t NOT_SORTED_GAP = 10;
    void setSorts() {
        fastSort = std::move(shared_ptr<Sorter<T>>(new QuickSorter<T>(_cmp, data)));
        stableSort = std::move(shared_ptr<Sorter<T>>(new InsertionSorter<T>(_cmp, data)));
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
    SortedSequence(bool (*cmp)(const T&, const T&) = baseComparator, bool(*isEqual)(const T&, const T&) = baseEqual) : isSorted(true), notSortedCount(0), _cmp(cmp), _isEqual(isEqual)  {
        data = shared_ptr<Sequence<T>>(new ArraySequence<T>());
        setSorts();
    }
    SortedSequence(const ICollection<T> &collection,  bool (*cmp)(const T&, const T&) = baseComparator, bool(*isEqual)(const T&, const T&) = baseEqual) : data(new ArraySequence<T>(collection) ), _cmp(cmp), _isEqual(isEqual) {
        setSorts();
        notSortedCount = collection.GetLength();
        if (notSortedCount > 1) {
            isSorted = false;
        } else {
            isSorted = true;
        }
    }
    SortedSequence(const Sequence<T> *sequence, bool (*cmp)(const T&, const T&) = baseComparator, bool(*isEqual)(const T&, const T&) = baseEqual) : data(new ArraySequence<T>(sequence)), _cmp(cmp), _isEqual(isEqual) {
        setSorts();
        notSortedCount = sequence->GetLength();
        if (notSortedCount > 1) {
            isSorted = false;
        } else {
            isSorted = true;
        }
    }
    SortedSequence(shared_ptr<Sequence<T>> sequence, bool (*cmp)(const T&, const T&) = baseComparator, bool(*isEqual)(const T&, const T&) = baseEqual) : data(new ArraySequence<T>(sequence.get())), _cmp(cmp), _isEqual(isEqual) {
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
        data->Append(item);
    }
    void AddMany(shared_ptr<Sequence<T>> sequence) {
        isSorted = false;
        notSortedCount += sequence->GetLength();
        data->Concat(sequence.get());
    }
    int IndexOf(T element) override {
        this->Sort();
        int start = 0, end = data->GetLength() - 1, mid; 
        while(start <= end) {
            mid = (start + end) / 2;
            if (_isEqual(data->Get(mid), element))
                return mid;
            if (_cmp(data->Get(mid), element)) {
                start = mid + 1;
            }
            else {
                end = mid - 1;
            }
        }
        return -1;
    }
    std::optional<T> Get(T element) override {
        auto index = IndexOf(element);
        if (index == -1)
            return {};
        return data->Get(IndexOf(element));
    }
    shared_ptr<Sequence<T>> GetValues() override {
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
        return data->GetFirst();
    }
    T GetLast() override {
        Sort();
        return data->GetLast();
    }
    void Remove(T element) override {
        data->Remove(IndexOf(element));
    }
    ~SortedSequence() {}
};