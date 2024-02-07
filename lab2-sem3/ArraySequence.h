#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H
#include "DynamicArray.h"
#include "Sequence.h"


template <typename T>
class ArraySequence : public Sequence<T> {
protected:
    DynamicArray<T> *elements;
public:
    ArraySequence() {
        this->elements = new DynamicArray<T>();
    }
    ArraySequence(T* items, size_t count) {
        this->elements = new DynamicArray<T>(items, count);
    }
    ArraySequence(const Sequence<T> *sequence) {
        size_t length = sequence->GetLength();
        T array[length];
        for (size_t i = 0; i < length; i++) {
            array[i] = sequence->Get(i);
        }
        this->elements = new DynamicArray<T>(array, length);
    }
    ArraySequence(const Sequence<T> &sequence) {
        size_t length = sequence.GetLength();
        T array[length];
        for (size_t i = 0; i < length; i++) {
            array[i] = sequence.Get(i);
        }
        this->elements = new DynamicArray<T>(array, length);
    }
    ArraySequence(const DynamicArray<T> &dynamicArray) {
        this->elements = new DynamicArray<T>(dynamicArray);
    }
    ArraySequence(const ICollection<T> &collection) {
        this->elements = new DynamicArray<T>(collection);
    }
    ArraySequence(const ArraySequence<T> &) = delete;
    ~ArraySequence() {
        if (elements)
            delete elements;
    }
    std::shared_ptr<IEnumerator<T>> GetEnumerator() override {
        return elements->GetEnumerator();
    }
    T GetFirst() const override {
        return elements->Get(0);
    }
    T GetLast() const override {
        return elements->Get(elements->GetLength() - 1);
    }
    T Get(size_t index) const override {
        return elements->Get(index);
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
        if (startIndex < 0 || startIndex > this->GetLength() || endIndex < 0 || endIndex > this->GetLength())
            throw std::out_of_range("IndexOutOfRange");
        if (startIndex > endIndex) {
            size_t t = startIndex;
            startIndex = endIndex;
            endIndex = t;
        }
        DynamicArray<T> dynamicArray = DynamicArray<T>(endIndex - startIndex);
        for (size_t i = startIndex; i < endIndex; ++i) {
            dynamicArray.Set(i - startIndex, this->elements->Get(i));
        }
        return new ArraySequence<T>(dynamicArray);
    }
    size_t GetLength() const override {
        return this->elements->GetLength();
    }
    void Append(T item) override {
        size_t currentLength = this->elements->GetLength();
        this->elements->ExpandResize(currentLength + 1);
        this->elements->Set(currentLength, item);
    }
    void Prepend(T item) override {
        size_t currentLength = this->elements->GetLength();
        this->elements->ExpandResize(currentLength + 1);
        for (int i = currentLength - 1; i >= 0; --i) {
            this->elements->Set(i + 1, this->elements->Get(i));
        }
        this->elements->Set(0, item);
    }
    T& operator[] (const size_t index) override {
        return (*elements)[index];
    }
    void InsertAt(T item, size_t index) override {
        if (index < 0 || index > this->elements->GetLength())
            throw std::out_of_range("IndexOutOfRange");
        size_t length = this->elements->GetLength();
        this->elements->ExpandResize(length + 1);
        for (int i = length; i > index; --i) {
            this->elements->Set(i, this->elements->Get(i-1));
        }
        this->elements->Set(index, item);
    }
};

#endif
