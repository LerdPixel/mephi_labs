#ifndef LINKED_LIST_SEQUENCE_H
#define LINKED_LIST_SEQUENCE_H
#include "smart_ptrs/shared_ptr.h"
#include "SmartPtrLinkedList.h"
#include "Sequence.h"


template <typename T>
class SmartPtrLinkedListSequence : public Sequence<T> {
protected:
    shared_ptr<SmartPtrLinkedList<T>> elements;
public:
    SmartPtrLinkedListSequence() {
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>());
    }
    SmartPtrLinkedListSequence(T* items, size_t count) {
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>(items, count));
    }
    SmartPtrLinkedListSequence(const Sequence<T> *sequence) {
        size_t length = sequence->GetLength();
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>());
        for (size_t i = 0; i < length; ++i) {
            elements->Append(sequence->Get(i));
        }
    }
    SmartPtrLinkedListSequence(const Sequence<T> &sequence) {
        size_t length = sequence.GetLength();
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>());
        for (size_t i = 0; i < length; ++i) {
            elements->Append(sequence.Get(i));
        }
    }
    SmartPtrLinkedListSequence(const SmartPtrLinkedList<T> &list) {
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>(list));
    }
    SmartPtrLinkedListSequence(const ICollection<T> &collection) {
        this->elements = shared_ptr<SmartPtrLinkedList<T>>(new SmartPtrLinkedList<T>(collection));
    }
    ~SmartPtrLinkedListSequence() {
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
    shared_ptr<IEnumerator<T>> GetEnumerator() override {
        return elements->GetEnumerator();
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override {
        SmartPtrLinkedList<T> *list = elements->GetSubList(startIndex, endIndex);
        SmartPtrLinkedListSequence<T> *res = new SmartPtrLinkedListSequence<T>(*list);
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
    void Remove(size_t index) override {
        
    }
};

#endif
