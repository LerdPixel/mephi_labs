#include <iostream>
#include "ArraySequence.h"
#include "smart_ptrs/unique_ptr.h"
#include "smart_ptrs/shared_ptr.h"
#include "swap.h"
#include <vector>
#include <memory>
#include "quicksort.h"
#include "insertionSort.h"

bool compareAscending(const int& a, const int& b) {
    return a < b;
}
template <typename T>
unique_ptr<T> uniqueFromT(T element) {
    return unique_ptr<T>(new T(element));
}
template <typename T>
shared_ptr<T> sharedFromT(T element) {
    return make_shared<T>(element);
}
template <typename T>
void printSequence(Sequence<T>* seq) {
    auto e = seq->GetEnumerator();
    while (e->next()) {
        std::cout << *(*(*e)) << ' ';
    }
    std::cout << std::endl;
}
int main() {
    int a[] =  {12, 4, 5, 6, 7, 3, 1, 15};
    shared_ptr<int> b[] = {make_shared<int>(12), make_shared<int>(3), make_shared<int>(7), make_shared<int>(1)};
    int size = 8;
    auto Iarray = new ArraySequence<int>(a, 8);
    Sequence<shared_ptr<int>> *array2 = Iarray->Map<ArraySequence<shared_ptr<int>>,  shared_ptr<int>>(sharedFromT<int>);
    ArraySequence<shared_ptr<int>> array(b, 4);
    std::cout << "Original array: ";
    auto e = array.GetEnumerator();
    while (e->next()) {
        std::cout << *(*(*e)) << ' ';
    }
    std::cout << std::endl;

    quicksort(array, 0, array.GetLength() - 1, compareAscending);

    std::cout << "Sorted array in ascending order: ";
    e = array.GetEnumerator();
    while (e->next()) {
        std::cout << *(*(*e)) << ' ';
    }
    std::cout << std::endl;
    insertionSort(*array2, compareAscending);
    printSequence(array2);
    delete array2;
    delete Iarray;
    return 0;
}
