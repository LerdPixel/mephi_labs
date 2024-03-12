#ifndef SmartPtrNode_H
#define SmartPtrNode_H
#include "smart_ptrs/shared_ptr.h"

template <typename T>
class SmartPtrNode {
private:
    T value;
    shared_ptr<SmartPtrNode<T>> next;
public:
    SmartPtrNode(T value, shared_ptr<SmartPtrNode<T>> next) : value(value), next(next) {}
    SmartPtrNode(SmartPtrNode<T> &node) : value(node.value), next(node.next) {}
    SmartPtrNode(T value) : value(value), next() {}
    T& GetReference() {
        return value;
    }
    T GetValue() const {
        return value;
    }
    shared_ptr<SmartPtrNode<T>> GetNext() const {
        return next;
    }
    void SetNext(shared_ptr<SmartPtrNode<T>> node) {
        next = node;
    }
    void SetValue(T value) {
        this->value = value;
    }
};

#endif
