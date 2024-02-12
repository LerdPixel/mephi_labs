#include <iostream>
#include "ArraySequence.h"
#include "Sequence.h"

int main(int argc, char const *argv[])
{
    int a[] = {1, 2, 3, 4, 5};
    Sequence<int>* seqA = new ArraySequence<int>(a, 5);
    ArraySequence<int>* p3 = dynamic_cast<ArraySequence<int>*>(seqA);
    std::cout << p3->GetLength() << std::endl;
    return 0;
}
