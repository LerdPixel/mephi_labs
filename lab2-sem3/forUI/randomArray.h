#ifndef RANDOM_ARRAY_H
#define RANDOM_ARRAY_H
#include <time.h>
#include "../Sequence.h"
#include "../smart_ptrs/shared_ptr.h"
#include "../ArraySequence.h"



shared_ptr<int> randomArray(size_t size, int bottom, int top) {
    shared_ptr<int> array(new int[size]);
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        *(array.get()+i) = rand() % (top - bottom) + bottom;
    }
    return array;
}
shared_ptr<Sequence<int>> randomSequence(size_t size, int bottom, int top) {
    return shared_ptr<Sequence<int>>(new ArraySequence<int>(randomArray(size, bottom, top).get(), size));
}
#endif