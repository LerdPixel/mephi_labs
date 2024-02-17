#include <iostream>
#include "smart_ptrs/unique_ptr.h"
#include "smart_ptrs/shared_ptr.h"
#include "ArraySequence.h"
#include "forUI/arrayIO.h"
#include "forUI/randomArray.h"
#include "quicksort.h"
#include "insertionSort.h"
#include <chrono>
#include "Sorter.h"
#include "QuickSorter.h"
#include "InsertionSorter.h"

bool intComparator(int a, int b) {
    return a < b;
}


bool compareAscending(const int& a, const int &b) {
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
class cases {
    shared_ptr<Sequence<int>> _seq;
public:
    cases(shared_ptr<Sequence<int>> seq) {
        _seq = seq;
    }
    void bestCase() {
        for (int i = 0; i < _seq->GetLength(); ++i) {
            (*_seq)[i] = i;
        }
    }
    void worstCase() {
        int length = _seq->GetLength();
        for (int i = 0; i < length; ++i) {
            (*_seq)[i] = length - i;
        }
    }
    void random(shared_ptr<int> rndArray, int length) {
        if (length != _seq->GetLength())
            throw std::out_of_range("DifferentLength");
        for (int i = 0; i < _seq->GetLength(); ++i) {
            (*_seq)[i] = *(rndArray.get()+i);
        }
    }
};

template <typename T>
long long counter(shared_ptr<Sorter<T>> sorter) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter->Sort();
    auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
}

void randomInput() {
    int top, bottom, count,optionType, times, exitCode = 0;
    std::cout << "input borders:" << std::endl;
    checkInput(&bottom);
    checkInput(&top);
    std::cout << "input number of measurement:" << std::endl;   
    checkInput(&times);
    while (true) {
        std::cout << "sort: 0 - exit; 1 - insertion sort; 2 - quick sort" << '\n';
        checkInput(&optionType);
        if (optionType == exitCode) 
            break;
        std::cout << "input array length:" << std::endl;
        checkInput(&count);
        shared_ptr<Sequence<int>> Iarray = randomSequence(count, bottom, top);
        shared_ptr<Sorter<int>> sorter;
        switch (optionType) {
            case 2:
                sorter = shared_ptr<Sorter<int>>(new  QuickSorter<int>(intComparator, Iarray));
            break;
            case 1:
                sorter  = shared_ptr<Sorter<int>>(new InsertionSorter<int>(intComparator, Iarray));
            break;
        }
        cases resetArray(Iarray);
        long long duration = 0;
        for (int i = 0; i < times; ++i) {
            duration += counter<int>(sorter);
            resetArray.random(randomArray(count, bottom, top), count);
        }
        std::cout << "Mean duration: " << duration / times << " microseconds" << "\n\n" << " Something else? \n";
    }
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
    int exitCode = 0, optionType, dataType = 0;
    while(exitCode != 1) {
        std::cout << "test type: 0 - random data; 1 - keybord input; 2 - exit" << '\n';
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
            case 3:
                //comparisonV();
            break;
            case 2:
                exitCode = 1;
            break;
        }
    }
    return 0;
}