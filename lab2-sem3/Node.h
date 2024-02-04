#ifndef NODE_H
#define NODE_H


template <typename T>
class Node {
private:
    T value;
    Node<T> *next;
public:
    Node(T value, Node<T> *next) : value(value), next(next) {}
    Node(Node<T> &node) : value(node.value), next(node.next) {}
    Node(T value) : value(value), next(nullptr) {}
//    ~Node() {delete next;}
    T& GetReference() {
        return value;
    }
    T GetValue() const {
        return value;
    }
    Node<T> *GetNext() const {
        return next;
    }
    void SetNext(Node<T> *node) {
        next = node;
    }
    void SetValue(T value) {
        this->value = value;
    }
};

#endif
