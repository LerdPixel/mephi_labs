#pragma once

template <typename T>
bool baseComparator(T a, T b) {
    return a < b;
}

template <typename T>
bool baseEqual(T a, T b) {
    return a == b;
}