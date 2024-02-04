#pragma once
#include "Sequence.h"

template <typename T>
void insertionSort(Sequence<shared_ptr <T>>& arr, bool (*compare)(const T&, const T&)) {
    int j;
    shared_ptr<T> key;
    for (int i = 1; i < arr.GetLength(); ++i) {
        key = arr[i];
        for (j = i - 1; j >= 0 && compare(*key, *arr[j]); --j) {
            arr[j + 1]  = arr[j];
        }
        arr[j + 1] = key;
    }
}

