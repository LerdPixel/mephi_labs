#ifndef RANDOM_ARRAY_H
#define RANDOM_ARRAY_H
#include <time.h>
#include "../Sequence.h"
#include "../ArraySequence.h"

Sequence<int>* randomArray(size_t size, int bottom, int top) {
    DynamicArray<int> array(size);
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % (top - bottom) + bottom;
    }
    return new ArraySequence<int>(array);
}
template< class Iter >
void fill_with_random_int_values( Iter start, Iter end, int min, int max)
{
    static std::random_device rd;    // you only need to initialize it once
    static std::mt19937 mte(rd());   // this is a relative big object to create

    std::uniform_int_distribution<int> dist(min, max);

    std::generate(start, end, [&] () { return dist(mte); });
}

#endif