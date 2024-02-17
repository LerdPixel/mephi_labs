#ifndef SMART_PTRS_LINKED_LIST_H
#define SMART_PTRS_LINKED_LIST_H
#include "SmartPtrNode.h"
#include "ICollection.h"
#include "smart_ptrs/shared_ptr.h"

template <typename T>
class SmartPtrLinkedList : public IEnumerable<T>, public ICollection<T> {
protected:
    shared_ptr<SmartPrtNode<T>> header;
private:
    shared_ptr<SmartPrtNode<T>> GetNode(size_t index) const;
public:
    class SmartPtrLinkedListEnumerator : public IEnumerator<T> {
        shared_ptr<SmartPrtNode<T>> _n;
        SmartPtrLinkedList<T> *_s;
        bool _st;
    public:
        SmartPtrLinkedListEnumerator(SmartPtrLinkedList<T> *s) : _s(s), _n(s->header), _st(true) {}
        bool next() override {
            if (_st) {
                _st = false;
                if (!_n)
                    return false;
                return true;
            }
            if (!_n || !_n->GetNext())
                return false;
            _n = _n->GetNext();
            return true;
        }
        T& operator * () override { return _n->GetReference(); }
    };
    SmartPtrLinkedList();
    SmartPtrLinkedList(T *items, size_t size);
    SmartPtrLinkedList(const SmartPtrLinkedList<T> &list);
    SmartPtrLinkedList(shared_ptr<SmartPrtNode<T>> head);
    SmartPtrLinkedList(const ICollection<T> &collection);
    ~SmartPtrLinkedList();
    shared_ptr<IEnumerator<T>> GetEnumerator() override;
    T GetFirst() const;
    T GetLast() const;
    T Get(size_t index) const override;
    T& operator[](size_t index);
    SmartPtrLinkedList<T> *GetSubList(size_t startIndex, size_t endIndex) const;
    size_t GetLength() const override;
    void Append(T item);
    void Prepend(T item);
    void Remove(size_t index) {
            if (index == 0) {
                header = header->GetNext();
            } else {
                shared_ptr<SmartPrtNode<T>> previous = GetNode(index - 1);
                previous->SetNext((previous->GetNext())->GetNext());
            }
    }
    size_t findByValue(T item) {
        shared_ptr<SmartPrtNode<T>> node = header;
        int index = 0;
        while (node) {
            if (node->GetValue() == item) {
                return index;
            }
            ++index;
            node = node->GetNext();
        }
        return -1; //not found
    }
    void InsertAt(T item, size_t index);
    void Set(size_t index, T value);
    SmartPtrLinkedList<T>* Concat(SmartPtrLinkedList<T> *list) const;
    inline bool operator==(const SmartPtrLinkedList<T> &rhs) const;
};

template <typename T>
SmartPtrLinkedList<T> :: SmartPtrLinkedList() {
}
template <typename T>
SmartPtrLinkedList<T> :: SmartPtrLinkedList(T *items, size_t size) {
    if (size < 0)
        throw std::length_error("Size can't be negative");
    if (size == 0) {
//        header();
    }
    else {
        header = make_shared<SmartPrtNode<T>>(items[0]);
        shared_ptr<SmartPrtNode<T>> nodeRing = header;
        for (size_t i = 1; i < size; ++i) {
            nodeRing->SetNext(make_shared<SmartPrtNode<T>>(items[i]));
            nodeRing = nodeRing->GetNext();
        }
    }
}
template <typename T>
SmartPtrLinkedList<T> :: SmartPtrLinkedList(const SmartPtrLinkedList <T> &list) {
    if (!list.header) {
        //header();
        return;
    }
    header = make_shared<SmartPrtNode<T>>(*list.header);
    shared_ptr<SmartPrtNode<T>> node = header;
    shared_ptr<SmartPrtNode<T>> listNode = list.header->GetNext();
    while(listNode) {
        node->SetNext(make_shared<SmartPrtNode<T>>(*listNode));
        node = node->GetNext();
        listNode = listNode->GetNext();
    }
}
template <typename T>
SmartPtrLinkedList<T> :: SmartPtrLinkedList(shared_ptr<SmartPrtNode<T>> head) {
    header = head;
    while (head) {
        head = head->GetNext();
    }
}
template <typename T>
SmartPtrLinkedList<T> :: SmartPtrLinkedList(const ICollection<T> &collection) {
    size_t length = collection.GetLength();
    if (length == 0) {
   //     header();
    }
    else {
        header = make_shared<SmartPrtNode<T>>(collection.Get(0));
        shared_ptr<SmartPrtNode<T>> nodeRing = header;
        for (size_t i = 1; i < length; ++i) {
            nodeRing->SetNext(make_shared<SmartPrtNode<T>>(collection.Get(i)));
            nodeRing = nodeRing->GetNext();
        }
    }
}
template <typename T>
SmartPtrLinkedList<T> :: ~SmartPtrLinkedList() {
}
template <typename T>
shared_ptr<IEnumerator<T>> SmartPtrLinkedList<T> :: GetEnumerator() {
    return shared_ptr<IEnumerator<T>>(new SmartPtrLinkedList<T>::SmartPtrLinkedListEnumerator(this));
}
template <typename T>
T SmartPtrLinkedList<T> :: GetFirst() const {
    if (header) {
        return header->GetValue();
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
T SmartPtrLinkedList<T> :: GetLast() const {
    if (header) {
        shared_ptr<SmartPrtNode<T>> node = header;
        while (node->GetNext()) {
            node = node->GetNext();
        }
        return node->GetValue();
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
T SmartPtrLinkedList<T> :: Get(size_t index) const {
    return GetNode(index)->GetValue();
}
template <typename T>
T& SmartPtrLinkedList<T> :: operator[](size_t index) {
    return GetNode(index)->GetReference();
}
template <typename T>
shared_ptr<SmartPrtNode<T>> SmartPtrLinkedList<T> :: GetNode(size_t index) const {
    size_t length = GetLength();
    if (index < length && index >= 0 && header) {
        shared_ptr<SmartPrtNode<T>> node = header;
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
size_t SmartPtrLinkedList<T> :: GetLength() const {
    shared_ptr<SmartPrtNode<T>> node = header;
    size_t i = 0;
    while (node) {
        node = node->GetNext();
        ++i;
    }
    return i;
}
template <typename T>
void SmartPtrLinkedList<T> :: Append(T item) {
    if (!header) {
        header = make_shared<SmartPrtNode<T>>(item);
        return;
    }
    shared_ptr<SmartPrtNode<T>> node = header;
    while (node->GetNext()) {
        node = node->GetNext();
    }
    node->SetNext(make_shared<SmartPrtNode<T>>(item));
}
template <typename T>
void SmartPtrLinkedList<T> :: Prepend(T item) {
    shared_ptr<SmartPrtNode<T>> node = header;
    header = make_shared<SmartPrtNode<T>>(item, node);
}
template <typename T>
void SmartPtrLinkedList<T> :: Set(size_t index, T value) {
    size_t length = GetLength();
    if (index < length && index >= 0 && header) {
        shared_ptr<SmartPrtNode<T>> node = header;
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
SmartPtrLinkedList<T>* SmartPtrLinkedList<T> :: GetSubList(size_t startIndex, size_t endIndex) const {
    size_t length = GetLength();
    if (startIndex <= length && startIndex >= 0 && endIndex <= length && endIndex >= 0) {
        if (startIndex > endIndex) {
            size_t t = startIndex;
            startIndex = endIndex;
            endIndex = t;
        }
        else if (startIndex == endIndex)
            return new SmartPtrLinkedList();
        shared_ptr<SmartPrtNode<T>> node = GetNode(startIndex);
        shared_ptr<SmartPrtNode<T>> newHeader = make_shared<SmartPrtNode<T>>(*node);
        shared_ptr<SmartPrtNode<T>> newNode = newHeader;
        for (size_t i = startIndex + 1; i < endIndex; ++i) {
            node = node->GetNext();
            newNode->SetNext(make_shared<SmartPrtNode<T>>(*node));
            newNode = newNode->GetNext();
        }
        newNode->SetNext(shared_ptr<SmartPrtNode<T>>());
        return new SmartPtrLinkedList(newHeader);
    }
    else {
        throw std::out_of_range("IndexOutOfRange");
    }
}
template <typename T>
SmartPtrLinkedList<T>* SmartPtrLinkedList<T> :: Concat(SmartPtrLinkedList<T> *list) const {
    SmartPtrLinkedList<T>* newList = new SmartPtrLinkedList(*this);
    size_t listLength = list->GetLength();
    for (size_t i = 0; i < listLength; ++i) {
        newList->Append(list->Get(i));
    }
    return newList;
}
template <typename T>
void SmartPtrLinkedList<T> :: InsertAt(T item, size_t index) {
    size_t length = GetLength();
    if (index > length || index < 0)
        throw std::out_of_range("IndexOutOfRange");
    if (index == 0 || !header) {
        header = make_shared<SmartPrtNode<T>>(item, header);
    }
    else {
        shared_ptr<SmartPrtNode<T>> stNode = GetNode(index-1);
        shared_ptr<SmartPrtNode<T>> newNode = make_shared<SmartPrtNode<T>>(item, stNode->GetNext());
        stNode->SetNext(newNode);
    }
}
template <typename T>
inline bool SmartPtrLinkedList<T> :: operator==(const SmartPtrLinkedList<T> &rhs) const {
    shared_ptr<SmartPrtNode<T>> nodeL = this->header, nodeR = rhs.header;
    while(nodeL && nodeR) {
        if (nodeL->GetValue() != nodeR->GetValue())
            return false;
        nodeL = nodeL->GetNext();
        nodeR = nodeR->GetNext();
    }
    if (!(nodeL || nodeR)) {
        return true;
    }
    return false;
}
#endif
