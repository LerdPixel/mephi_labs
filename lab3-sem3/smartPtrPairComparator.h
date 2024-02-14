#pragma once
#include "Pair.h"
#include "smart_ptrs/shared_ptr.h"

template <typename T>
bool smartPtrPairComparator(T a, T b) {
    return a->GetKey() < b->GetKey();
}

template <typename T>
bool smartPtrPairEqual(T a, T b) {
    return a->GetKey() == b->GetKey();
}