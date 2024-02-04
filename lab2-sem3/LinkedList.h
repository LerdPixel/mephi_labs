#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Node.h"
#include "ICollection.h"

template <typename T>
class LinkedList : public IEnumerable<T>, public ICollection<T> {
protected:
    Node<T> *header;
private:
    Node<T>* GetNode(size_t index) const;
public:
    class LinkedListEnumerator : public IEnumerator<T> {
        Node<T>* _n;
        LinkedList<T> *_s;
        bool _st;
    public:
        LinkedListEnumerator(LinkedList<T> *s) : _s(s), _n(s->header), _st(true) {}
        bool next() override {
            if (_st) {
                _st = false;
                if (_n == nullptr)
                    return false;
                return true;
            }
            if (_n == nullptr || _n->GetNext() == nullptr)
                return false;
            _n = _n->GetNext();
            return true;
        }
        T& operator * () override { return _n->GetReference(); }
    };
    LinkedList();
    LinkedList(T *items, size_t size);
    LinkedList(const LinkedList<T> &list);
    LinkedList(Node<T>* head);
    LinkedList(const ICollection<T> &collection);
    ~LinkedList();
    std::shared_ptr<IEnumerator<T>> GetEnumerator() override;
    T GetFirst() const;
    T GetLast() const;
    T Get(size_t index) const override;
    T& operator[](size_t index);
    LinkedList<T> *GetSubList(size_t startIndex, size_t endIndex) const;
    size_t GetLength() const override;
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, size_t index);
    void Set(size_t index, T value);
    LinkedList<T>* Concat(LinkedList<T> *list) const;
    inline bool operator==(const LinkedList<T> &rhs) const;
};

template <typename T>
LinkedList<T> :: LinkedList() {
    header = nullptr;
}
template <typename T>
LinkedList<T> :: LinkedList(T *items, size_t size) {
    if (size < 0)
        throw std::length_error("Size can't be negative");
    if (size == 0) {
        header = nullptr;
    }
    else {
        header = new Node<T>(items[0], nullptr);
        Node<T> *nodeRing = header;
        for (size_t i = 1; i < size; ++i) {
            nodeRing->SetNext(new Node<T>(items[i], nullptr));
            nodeRing = nodeRing->GetNext();
        }
    }
}
template <typename T>
LinkedList<T> :: LinkedList(const LinkedList <T> &list) {
    if (list.header == nullptr) {
        header = nullptr;
        return;
    }
    header = new Node<T>(*list.header);
    Node<T> *node = header;
    Node<T> *listNode = list.header->GetNext();
    while(listNode != nullptr) {
        node->SetNext(new Node<T>(*listNode));
        node = node->GetNext();
        listNode = listNode->GetNext();
    }
}
template <typename T>
LinkedList<T> :: LinkedList(Node<T>* head) {
    header = head;
    while (head != nullptr) {
        head = head->GetNext();
    }
}
template <typename T>
LinkedList<T> :: LinkedList(const ICollection<T> &collection) {
    size_t length = collection.GetLength();
    if (length == 0) {
        header = nullptr;
    }
    else {
        header = new Node<T>(collection.Get(0), nullptr);
        Node<T> *nodeRing = header;
        for (size_t i = 1; i < length; ++i) {
            nodeRing->SetNext(new Node<T>(collection.Get(i), nullptr));
            nodeRing = nodeRing->GetNext();
        }
    }
}
template <typename T>
LinkedList<T> :: ~LinkedList() {
    Node<T> *node = header;
    Node<T> *nodeNext;
    while(node != nullptr) {
        nodeNext = node->GetNext();
        delete node;
        node = nodeNext;
    }
}
template <typename T>
std::shared_ptr<IEnumerator<T>> LinkedList<T> :: GetEnumerator() {
    return std::shared_ptr<IEnumerator<T>>(new LinkedList<T>::LinkedListEnumerator(this));
}
template <typename T>
T LinkedList<T> :: GetFirst() const {
    if (header != nullptr) {
        return header->GetValue();
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
T LinkedList<T> :: GetLast() const {
    if (header != nullptr) {
        Node<T>* node = header;
        while (node->GetNext() != nullptr) {
            node = node->GetNext();
        }
        return node->GetValue();
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
T LinkedList<T> :: Get(size_t index) const {
    return GetNode(index)->GetValue();
}
template <typename T>
T& LinkedList<T> :: operator[](size_t index) {
    return GetNode(index)->GetReference();
}
template <typename T>
Node<T>* LinkedList<T> :: GetNode(size_t index) const {
    size_t length = GetLength();
    if (index < length && index >= 0 && header != nullptr) {
        Node<T>* node = header;
        for (size_t i = 0; i < index; i++) {
            node = node->GetNext();
        }
        return node;
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
size_t LinkedList<T> :: GetLength() const {
    Node<T>* node = header;
    size_t i = 0;
    while (node != nullptr) {
        node = node->GetNext();
        ++i;
    }
    return i;
}
template <typename T>
void LinkedList<T> :: Append(T item) {
    if (header == nullptr) {
        header = new Node<T>(item);
        return;
    }
    Node<T>* node = header;
    while (node->GetNext() != nullptr) {
        node = node->GetNext();
    }
    node->SetNext(new Node<T>(item, nullptr));
}
template <typename T>
void LinkedList<T> :: Prepend(T item) {
    Node<T>* node = header;
    header = new Node<T>(item, node);
}
template <typename T>
void LinkedList<T> :: Set(size_t index, T value) {
    size_t length = GetLength();
    if (index < length && index >= 0 && header != nullptr) {
        Node<T>* node = header;
        for (size_t i = 0; i < index; i++) {
            node = node->GetNext();
        }
        node->SetValue(value);
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
LinkedList<T> * LinkedList<T> :: GetSubList(size_t startIndex, size_t endIndex) const {
    size_t length = GetLength();
    if (startIndex <= length && startIndex >= 0 && endIndex <= length && endIndex >= 0/* && header != nullptr*/) {
        if (startIndex > endIndex) {
            size_t t = startIndex;
            startIndex = endIndex;
            endIndex = t;
        }
        else if (startIndex == endIndex)
            return new LinkedList();
        Node<T>* node = GetNode(startIndex);
        Node<T>* newHeader = new Node<T>(*node);
        Node<T>* newNode = newHeader;
        for (size_t i = startIndex + 1; i < endIndex; ++i) {
            node = node->GetNext();
            newNode->SetNext(new Node<T>(*node));
            newNode = newNode->GetNext();
        }
        newNode->SetNext(nullptr);
        return new LinkedList(newHeader);
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
LinkedList<T>* LinkedList<T> :: Concat(LinkedList<T> *list) const {
    LinkedList<T>* newList = new LinkedList(*this);
    size_t listLength = list->GetLength();
    for (size_t i = 0; i < listLength; ++i) {
        newList->Append(list->Get(i));
    }
    return newList;
}
template <typename T>
void LinkedList<T> :: InsertAt(T item, size_t index) {
    size_t length = GetLength();
    if (index > length || index < 0)
        throw std::out_of_range("IndexOutOfRange");
    if (index == 0 || header == nullptr) {
        header = new Node<T>(item, header);
    }
    else {
        Node<T> *stNode = GetNode(index-1);
        Node<T> *newNode = new Node<T>(item, stNode->GetNext());
        stNode->SetNext(newNode);
    }
}
template <typename T>
inline bool LinkedList<T> :: operator==(const LinkedList<T> &rhs) const {
    Node<T> *nodeL = this->header, *nodeR = rhs.header;
//    size_t i = 0;
    while(nodeL != nullptr && nodeR != nullptr) {
//        std::cout << i++ << "   left:" << nodeL->GetValue() << "   right:" << nodeR->GetValue() << '\n';
        if (nodeL->GetValue() != nodeR->GetValue())
            return false;
        nodeL = nodeL->GetNext();
        nodeR = nodeR->GetNext();
    }
    if (nodeL == nullptr && nodeR == nullptr) {
//        std::cout << "/* message */"<< i << '\n';
        return true;
    }
    return false;
}
#endif
