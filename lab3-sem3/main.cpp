#include <iostream>
#include "ArraySequence.h"
#include "SortedSequence.h"

int main(int argc, char const *argv[])
{
    std::string a("dabc"), b("cba");
    std::cout << (a > b) << std::endl;
    return 0;
}
