#ifndef VECTOR_IO
#define VECTOR_IO
#include <iostream>
#include "stdio.h"
#include "../DynamicArray.h"
#include "../Complex.h"
#include "../Matrix.h"
#include "../MathVector.h"
#include "../Polynomial.h"

std::ostream &operator<<(std::ostream &os, Complex const &m) {
    return os << "(" << m.Re() << " + " << m.Im() << " i)";
}
template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> const &m) {
	os << "{";
	for (size_t i = 0; i < m.GetHight(); i++) {
		for (size_t j = 0; j < m.GetLength(); j++) {
			os << m.Get(j, i) << " ";
		}
		os << ";";
	}

    return os << "}";
}
template <typename T>
std::ostream &operator<<(std::ostream &os, MathVector<T> const &v) {
	os << "{";
	for (size_t i = 0; i < v.GetDimension(); i++) {
		os << v.Get(i) << " ";
	}
    return os << "}";
}
template <typename T>
std::ostream &operator<<(std::ostream &os, Polynomial<T> const &p) {
	if (p.GetLength() > 0) {
		os << p.Get(0) << " + ";
	}
	for (size_t i = 1; i < p.GetLength(); i++) {
		os << p.Get(i) << "*x^" << i << " + ";
	}
    return os;
}

/*
class arrayIO {
	public
}
*/

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
int checkInput(Complex *n) {
	double r, im;
	checkInput(&r);
	checkInput(&im);
	*n = Complex(r, im);
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
template <typename T> Matrix<T> inputM(size_t a, size_t b) {
	if (a < 0 || b < 0)
		throw std::length_error("lengths can't be negative");
	return Matrix<T>(input<T>(a*b), a, b);
}
template <typename T> Polynomial<T> inputP(size_t deg) {
	if (deg <= 0)
		throw std::length_error("Degree can't be negative");
	return Polynomial<T>(input<T>(deg));
}


#endif
