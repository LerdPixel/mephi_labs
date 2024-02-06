#include <iostream>
#include "smart_ptrs/unique_ptr.h"
#include "smart_ptrs/shared_ptr.h"
#include "ArraySequence.h"
#include "forUI/arrayIO.h"
#include "forUI/randomArray.h"
#include "quicksort.h"
#include "insertionSort.h"
#include <chrono>


bool compareAscending(const int& a, const int& b) {
    return a < b;
}
bool compareAscending(const double& a, const double& b) {
    return a < b;
}
template <typename T>
void keybordInput() {
    int optionType;
    Sequence<int> *Iarray = inputSeq<int>();
    shared_ptr<Sequence<shared_ptr<int>>> array2(Iarray->Map<ArraySequence<shared_ptr<int>>,  shared_ptr<int>>(sharedFromT<int>));
    std::cout << "sort: 0 - quick sort; 1 - insertion sort" << '\n';
    checkInput(&optionType);
    switch (optionType) {
        case 0:
            quicksort(*array2, 0, array2->GetLength() - 1, compareAscending);
        break;
        case 1:
            insertionSort(*array2, compareAscending);
        break;
    }
    printSequence(*array2);
    delete Iarray;
}

void randomInput() {
    int top, bottom, count,optionType;
    std::cout << "input borders:" << std::endl;
    checkInput(&bottom);
    checkInput(&top);
    std::cout << "input length:" << std::endl;
    checkInput(&count);
    Sequence<int>* Iarray = randomArray(count, bottom, top);
    shared_ptr<Sequence<shared_ptr<int>>> array2(Iarray->Map<ArraySequence<shared_ptr<int>>,  shared_ptr<int>>(sharedFromT<int>));
    std::cout << "sort: 0 - quick sort; 1 - insertion sort" << '\n';
    checkInput(&optionType);
    auto start = std::chrono::high_resolution_clock::now();
    switch (optionType) {
        case 0:
            quicksort(*array2, 0, array2->GetLength() - 1, compareAscending);
        break;
        case 1:
            insertionSort(*array2, compareAscending);
        break;
    }  
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "duration: " << duration.count() << std::endl;
}
/* void comparisonV() {
    for (int i = 10; i < 100000; i *= 2) {
        int top = 100000, bottom = 0, count = i;
        Sequence<int>* Iarray = randomArray(count, bottom, top);
        shared_ptr<Sequence<shared_ptr<int>>> array2(Iarray->Map<ArraySequence<shared_ptr<int>>,  shared_ptr<int>>(sharedFromT<int>));
        shared_ptr<Sequence<shared_ptr<int>>> array3(Iarray->Map<ArraySequence<shared_ptr<int>>,  shared_ptr<int>>(sharedFromT<int>));
        auto start = std::chrono::high_resolution_clock::now();
        quicksort(*array2, 0, array2->GetLength() - 1, compareAscending);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
        start = std::chrono::high_resolution_clock::now();
        insertionSort(*array3, compareAscending);
        stop = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::array<int, count> a;
        fill_with_random_int_values(a.begin(), a.end(), bottom, top);
    }
} */
int main() {
    while(exitCode != 1) {
        std::cout << "test type: 0 - random data; 1 - keybord input; 2 - comparison with std::sort ; 3 - exit" << '\n';
        checkInput(&optionType);
        switch (optionType) {
            case 0:
            randomInput();
            break;
            case 1:
                switch (dataType) {
                case 0:
                    keybordInput<int>();
                    break;
                case 1:
                    keybordInput<double>();
                    break;
                }
            break;
            case 2:

            break;
            case 3:
                exitCode = 1;
            break;
        }
    }
    return 0;
}