#ifndef VECTOR_IO
#define VECTOR_IO
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string_view>
#include <iostream>
#include "stdio.h"
#include "../DynamicArray.h"
#include "../Sequence.h"

template <typename T>
void printSequence(Sequence<T>* seq) {
    auto e = seq->GetEnumerator();
    while (e->next()) {
        std::cout << *(*(*e)) << ' ';
    }
    std::cout << std::endl;
}
template <typename T>
void printSequence(Sequence<T>& seq) {
    auto e = seq.GetEnumerator();
    while (e->next()) {
        std::cout << *(*(*e)) << ' ';
    }
    std::cout << std::endl;
}
template <typename T>
unique_ptr<T> uniqueFromT(T element) {
    return unique_ptr<T>(new T(element));
}
template <typename T>
shared_ptr<T> sharedFromT(T element) {
    return make_shared<T>(element);
}



int checkInput(int *n) {
	int sres = scanf("%d", n);
	while (sres != 1) {
		if (sres == EOF)
			throw std::invalid_argument("End of file");
		if (sres != 1) {
			scanf("%*[^\n]");
			puts("Wrong integer input format\n");
		}
		sres = scanf("%d", n);
	}
	return 0;
}
int checkInput(double *n) {
	double sres = scanf("%lf", n);
	while (sres != 1) {
		if (sres == EOF)
			throw std::invalid_argument("End of file");
		if (sres != 1) {
			scanf("%*[^\n]");
			puts("Wrong double input format\n");
		}
		sres = scanf("%lf", n);
	}
	return 0;
}


template <typename T>
DynamicArray<T> input(size_t len) {
	T arr[len];
    int res;
	for (int i = 0; i < len; ++i) {
        printf("element %d = ", i);
        res = checkInput(&arr[i]);
        if (res == EOF) {
            throw std::invalid_argument("input interrupted");
        }
	}
	return DynamicArray<T>(arr, len);
}
template <typename T>
Sequence<T> *inputSeq() {
	int len;
	std::cout << "Lengh input: ";
	checkInput(&len);
	while (len <= 0) {
		std::cout << "length must be  positive integer" << std::endl;
		checkInput(&len);
	}
	ArraySequence<T> *seq = new ArraySequence<T>(input<T>(len));
	return seq;
}
#endif
