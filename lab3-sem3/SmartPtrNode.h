#ifndef SmartPtrNode_H
#define SmartPtrNode_H
#include "smart_ptrs/shared_ptr.h"

template <typename T>
class SmartPtrNode {
private:
    T value;
    shared_ptr<SmartPrtNode<T>> next;
public:
    Node(T value, shared_ptr<SmartPrtNode<T>> next) : value(value), next(next) {}
    Node(SmartPrtNode<T> &node) : value(node.value), next(node.next) {}
    Node(T value) : value(value), next() {}
    T& GetReference() {
        return value;
    }
    T GetValue() const {
        return value;
    }
    shared_ptr<SmartPrtNode<T>> GetNext() const {
        return next;
    }
    void SetNext(shared_ptr<SmartPrtNode<T>> node) {
        next = node;
    }
    void SetValue(T value) {
        this->value = value;
    }
};

#endif
