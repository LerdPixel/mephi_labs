#pragma once
#include <vector>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<T>(cols));
    }

    // Getter
    T Get(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[row][col];
    }
    T& GetReference(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[row][col];
    }
    // Setter
    void Set(size_t row, size_t col, T value) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        data[row][col] = value;
    }
};
