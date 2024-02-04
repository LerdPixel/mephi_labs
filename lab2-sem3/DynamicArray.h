#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <iostream>
#include <memory>
#include "IEnumerable.h"
#include "IEnumerator.h"
#include "ICollection.h"
//using namespace std;

template <typename T>
class DynamicArray : public IEnumerable<T>, public ICollection<T> {
protected:
    T *array;
    size_t length;
    size_t realSize;
public:
    class ArrayEnumerator : public IEnumerator<T> {
        size_t _i;
        DynamicArray<T> *_s;
    public:
        ArrayEnumerator(DynamicArray<T> *s) : _s(s), _i(-1) {}
        bool next() override {
            _i++;
            return _i < _s->length && _i >= 0;
        }
        T& operator * () override { return (*_s)[_i]; }
    };
    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(T *items, size_t size);
    DynamicArray(const DynamicArray<T> &dynamicArray);
    DynamicArray(const ICollection<T> &collection);
    ~DynamicArray();
    std::shared_ptr<IEnumerator<T>> GetEnumerator() override;
    T Get(size_t index) const override;
    T& operator[](size_t index);
    size_t GetLength() const override;
    void Set(int index, T value);
    void Resize(size_t newSize);
    void Resize(size_t newSize, size_t realSize);
    void ExpandingResize(size_t newSize);
    void AddSize(size_t adding);
};

template <typename T>
DynamicArray<T> :: DynamicArray() {
    length = 0;
    realSize = 0;
    array = nullptr;
}
template <typename T>
DynamicArray<T> :: DynamicArray(size_t size) {
    if (size < 0)
        throw std::length_error("Size can't be negative");
    length = size;
    realSize = size;
    array = new T [size];
}
template <typename T>
DynamicArray<T> :: DynamicArray(T *items, size_t size) {
    if (size < 0)
        throw std::length_error("Size can't be negative");
    length = size;
    realSize = size;
    array = new T [size];
    for (size_t i = 0; i < size; ++i) {
        array[i] = items[i];
    }
}
template <typename T>
DynamicArray<T> :: DynamicArray(const DynamicArray<T> &dynamicArray) {
    size_t length = dynamicArray.GetLength();
    array = new T [length];
    for (size_t i = 0; i < length; ++i) {
        array[i] = dynamicArray.Get(i);
    }
    realSize = length;
    this->length = length;
}
template <typename T>
DynamicArray<T> :: DynamicArray(const ICollection<T> &collection) {
    size_t length = collection.GetLength();
    array = new T [length];
    for (size_t i = 0; i < length; ++i) {
        array[i] = collection.Get(i);
    }
    realSize = length;
    this->length = length;
}


template <typename T>
DynamicArray<T> :: ~ DynamicArray() {
    if (array)
        delete [] array;
}
template <typename T>
std::shared_ptr<IEnumerator<T>> DynamicArray<T> :: GetEnumerator() {
    return std::shared_ptr<IEnumerator<T>>(new DynamicArray<T>::ArrayEnumerator(this));
}


template <typename T>
T DynamicArray<T> :: Get(size_t index) const {
    if (index < 0 || index >= this->length) {
        throw std::out_of_range("IndexOutOfRange");
    }
    return array[index];
}
template <typename T>
T& DynamicArray<T> :: operator[](size_t index) {
    if (index < 0 || index >= this->length) {
        throw std::out_of_range("IndexOutOfRange");
    }
    return array[index];
}

template <typename T>
void DynamicArray<T> :: Set(int index, T value) {
    if (index < 0 || index >= this->length) {
        throw std::out_of_range("IndexOutOfRange");
    }
    this->array[index] = value;
}

template <typename T>
size_t DynamicArray<T> :: GetLength() const {
    return this->length;
}

template <typename T>
void DynamicArray<T> :: Resize(size_t newSize) {
    if (newSize < 0)
        throw std::length_error("Size can't be negative");
    T *array = new T [newSize];
    size_t i;
    for (i = 0; i < (newSize < this->length ? newSize : this->length); ++i) {
        array[i] = this->array[i];
    }
    for ( ; i < newSize; ++i) {
        array[i] = 0;
    }
    delete [] this->array;
    this->realSize = newSize;
    this->array = array;
    this->length = newSize;
}
template <typename T>
void DynamicArray<T> :: Resize(size_t newSize, size_t realSize) {
    if (newSize < 0 || realSize < 0 || newSize > realSize)
        throw std::length_error("Size can't be negative");
    T *array = new T [realSize];
    size_t i;
    for (i = 0; i < (newSize < this->length ? newSize : this->length); ++i) {
        array[i] = this->array[i];
    }
    /*for ( ; i < newSize; ++i) {
        array[i] = 0;
    }*/
    delete [] this->array;
    this->realSize = realSize;
    this->array = array;
    this->length = newSize;
}


template <typename T>
void DynamicArray<T> :: ExpandingResize(size_t newSize) {
    if (newSize < 0)
        throw std::length_error("Size can't be negative");
    if (newSize <= realSize) {
        length = newSize;
    }
    else {
        AddSize(newSize-length);
    }
}

template <typename T>
void DynamicArray<T> :: AddSize(size_t adding) {
    if (adding < 0)
        throw std::length_error("Size can't be negative");
    size_t newLength = adding + length;
    if (newLength <= realSize) {
        length = newLength;
    }
    else {
        size_t newRealSize = realSize > 0 ? realSize : 1;
        while (newLength > newRealSize) {
            newRealSize *= 2;
        }
        Resize(newLength, newRealSize);
    }
}


#endif
