#pragma once
#include "shared_ptr.h"

template <typename T>
shared_ptr<T> sharedFromT(T element) {
    return make_shared<T>(element);
}

template <typename T>
T TFromShared(shared_ptr<T> element) {
    return *element;
}