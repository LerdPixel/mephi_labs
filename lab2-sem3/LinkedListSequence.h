#ifndef LINKED_LIST_SEQUENCE_H
#define LINKED_LIST_SEQUENCE_H
#include <memory>
#include "LinkedList.h"
#include "Sequence.h"


template <typename T>
class LinkedListSequence : public Sequence<T> {
protected:
    LinkedList<T> *elements;
public:
    LinkedListSequence() {
        this->elements = new LinkedList<T>();
    }
    LinkedListSequence(T* items, size_t count) {
        this->elements = new LinkedList<T>(items, count);
    }
    LinkedListSequence(const Sequence<T> *sequence) {
        size_t length = sequence->GetLength();
        this->elements = new LinkedList<T>();
        for (size_t i = 0; i < length; ++i) {
            elements->Append(sequence->Get(i));
        }
    }
    LinkedListSequence(const Sequence<T> &sequence) {
        size_t length = sequence.GetLength();
        this->elements = new LinkedList<T>();
        for (size_t i = 0; i < length; ++i) {
            elements->Append(sequence.Get(i));
        }
    }
    LinkedListSequence(const LinkedList<T> &list) {
        this->elements = new LinkedList<T>(list);
    }
    LinkedListSequence(const ICollection<T> &collection) {
        this->elements = new LinkedList<T>(collection);
    }
    ~LinkedListSequence() {
        if (elements)
            delete elements;
    }
    T GetFirst() const override {
        return elements->GetFirst();
    }
    T GetLast() const override {
        return elements->GetLast();
    }
    T Get(size_t index) const override {
        return elements->Get(index);
    }
    std::shared_ptr<IEnumerator<T>> GetEnumerator() override {
        return elements->GetEnumerator();
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
        LinkedList<T> *list = elements->GetSubList(startIndex, endIndex);
        LinkedListSequence<T> *res = new LinkedListSequence<T>(*list);
        delete list;
        return res;
    }
    size_t GetLength() const override {
        return this->elements->GetLength();
    }
    void Append(T item) override {
        elements->Append(item);
    }
    void Prepend(T item) override {
        elements->Prepend(item);
    }
    T& operator[] (const size_t index) override {
        return (*elements)[index];
    }
    void InsertAt(T item, size_t index) override {
        elements->InsertAt(item, index);
    }
};

#endif
