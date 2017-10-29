#ifndef MULTMATRIX_MATRIXDEF_H
#define MULTMATRIX_MATRIXDEF_H

#include <algorithm>
#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix(unsigned int r, unsigned int c, const T& init) :rows(r), cols(c) {
    M.resize(r);
    for (register int i = 0; i < M.size(); i++) {
        M[i].resize(c, init);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    M = matrix.M;
    rows = matrix.get_rows();
    cols = matrix.get_cols();
}

template<typename T>
Matrix<T>::~Matrix() {
    for(register int i = 0; i < rows; i++)
        M[i].clear();
    M.clear();
    rows = 0;
    cols = 0;
}

template <class T>
template <class Function>
void Matrix<T>::randomGenerate(Function gen) {
    for (register int i = 0; i < rows; i++)
        generate(M[i].begin(), M[i].end(), gen);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
    if (&matrix == this)
        return *this;

    int new_rows = matrix.get_rows();
    int new_cols = matrix.get_cols();

    M.resize(new_rows);
    for (register int i = 0; i < M.size(); i++) {
        M[i].resize(new_cols);
    }

    for (register int i = 0; i<new_rows; i++) {
        for (register int j = 0; j<new_cols; j++) {
            M[i][j] = matrix(i, j);
        }
    }
    rows = new_rows;
    cols = new_cols;

    return *this;
}

template<typename T>
T& Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) {
    return this->M[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const unsigned int &row, const unsigned int &col) const {
    return this->M[row][col];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &matrix) {
    if (cols != matrix.get_rows())
        throw "Incompatible matrix sizes";

    unsigned int mCols = matrix.get_cols();
    Matrix result(rows, mCols);

    for (register int i = 0; i < rows; i++) {
        for (register int j = 0; j < mCols; j++) {
            for (register int k = 0; k < cols; k++) {
                result(i, j) += this->M[i][k] * matrix(k, j);
            }
        }
    }

    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &matrix) {
    Matrix result = (*this) * matrix;
    (*this) = result;
    return *this;
}

#endif //MULTMATRIX_MATRIXDEF_H