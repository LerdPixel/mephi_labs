#pragma once
#include "Sequence.h"
#include "Sorter.h"

template <typename T>
class ISortedSequence {
public:
    virtual int GetLength() const = 0;
    virtual bool GetIsEmpty() const = 0;
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual void Add(T ) = 0;
    virtual int IndexOf(T ) = 0;
    virtual std::optional<T> Get(T ) = 0;
    virtual shared_ptr<Sequence<T>> GetValues() = 0;
    virtual void Remove(T element) = 0;
    virtual ~ISortedSequence() {}
};