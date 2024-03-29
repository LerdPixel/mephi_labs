#pragma once
#include "swap.h"
#include "Sequence.h"

template <typename T>
int partition(Sequence<shared_ptr <T>>& arr, int start, int end, bool (*compare)(const T&, const T&))
{
    T pivot = *arr[start];
    int count = 0;
    for (int i = start + 1; i <= end; ++i) {
        if (compare(*arr[i], pivot))
            ++count;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (compare(*arr[i], pivot)) {
            ++i;
        }
 
        while (compare(pivot, *arr[j])) {
            --j;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}

template <typename T>
void quicksort(Sequence<shared_ptr<T>>& arr, int start, int end, bool (*compare)(const T&, const T&))
{
    if (start >= end)
        return;
    int p = partition(arr, start, end, compare);
    quicksort(arr, start, p - 1, compare);
    quicksort(arr, p + 1, end, compare);
}
template <typename T>
void quickSort(Sequence<shared_ptr<T>>& arr, bool (*compare)(const T&, const T&)) {
    quicksort(arr, 0, arr.GetLength()-1, compare);
}