#ifndef MULTMATRIX_MATRIX_H
#define MULTMATRIX_MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Matrix {
private:
    vector<vector<T> > M;
    unsigned int rows;
    unsigned int cols;
public:
    Matrix(unsigned int r, unsigned int c, const T& init = 0);
    Matrix(const Matrix<T>& matrix);
    virtual ~Matrix();

    unsigned int get_rows()const { return rows; }
    unsigned int get_cols()const { return cols; }

    template <class Function>
    void randomGenerate(Function gen);

    Matrix<T>& operator=(const Matrix<T>& matrix);
    T& operator()(const unsigned int& row, const unsigned int& col);
    const T& operator()(const unsigned int &row, const unsigned int &col) const;
    Matrix<T> operator*(const Matrix<T>& matrix);
    Matrix<T>&operator*=(const Matrix<T>& matrix);

    friend istream& operator>> (istream &in, Matrix<T>& matrix) {
        for (register int x = 0; x < matrix.get_rows(); x++) {
            for (register int y = 0; y < matrix.get_cols(); y++) {
                in >> matrix(x, y);
            }
        }
        return in;
    }

    friend ostream& operator<< (ostream &out, Matrix<T>& matrix) {
        out << "Matrix[ " << matrix.get_rows() << " , " << matrix.get_cols() << " ] :" << endl;
        for (unsigned int i = 0; i < matrix.get_rows(); i++) {
            for (unsigned int j = 0; j < matrix.get_cols(); j++) {
                out << matrix(i, j) << " ";
            }
            out << endl;
        }
        return out;
    }
};


#endif //MULTMATRIX_MATRIX_H
