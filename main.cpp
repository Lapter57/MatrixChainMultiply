#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <chrono>
#include "MatrixDef.h"
using namespace std;

int randomNumber(unsigned int l = 0, unsigned int r = 100) { return (l + (rand() % (r - l + 1))); }
int randomFillMatrix() { return (rand() % 10); }

Matrix<int> matrixChainOrder(const vector<unsigned int>& sizeMat) {
    unsigned int n = sizeMat.size();
    Matrix<int> M(n, n);
    Matrix<int> S(n - 1, n - 1);

    for (register int l = 1; l < n; l++) {
        for (register int i = 1; i < n - l; i++) {
            int j = i + l;
            M(i - 1, j - 1) = numeric_limits<int>::max();
            for (register int k = i; k <= j - 1; k++) {
                int q = M(i - 1, k - 1) + M(k + 1 - 1, j - 1) + sizeMat[i-1] * sizeMat[k] * sizeMat[j];
                if (q < M(i - 1, j - 1)) {
                    M(i - 1, j - 1) = q;
                    S(i - 1, j - 1) = k-1;
                }
            }
        }
    }
    return S;
}

template <class T>
Matrix<T> matrixChainMultiply(const vector<Matrix<T>> matrix, const Matrix<T>& S, int row, int col, ostream& out) {
    if (row == col) {
        out << "A" << row << " ";
        return matrix[row];
    }
    out << "(";
    Matrix<T> A(matrixChainMultiply(matrix, S, row, S(row, col), out));
    Matrix<T> B(matrixChainMultiply(matrix, S, S(row, col) + 1, col, out));
    out << ")";
    return A*B;
}


void task_1() {
    using namespace std::chrono;
    ifstream in;
    ofstream out;
    in.open("input_1.txt");
    out.open("output_1.txt");
    unsigned int l, r, n;
    in >> l >> r >> n;

    vector<unsigned int> numMat(n);
    for (register int i = 0; i < n; i++) {
        in >> numMat[i];
    }



    vector<Matrix<int>> vec_mat;
    for (int i = 0; i < n; i++) {
        vector<unsigned int> sizeMat(numMat[i] + 1);
        for (auto && el : sizeMat) {
            el = randomNumber(l, r);
        }
        int k = 0;
        for (register int j = 0; j < numMat[i]; j++) {
            Matrix<int> matrix(sizeMat[k], sizeMat[k + 1]);
            matrix.randomGenerate(&randomFillMatrix);
            out << matrix << endl;
            vec_mat.push_back(matrix);
            k++;
        }
        auto tStart = high_resolution_clock::now();
        Matrix<int> optimalCost = matrixChainOrder(sizeMat);
        Matrix<int> productMatrixChain = matrixChainMultiply(vec_mat, optimalCost, 0, numMat[i] - 1, out);
        auto tEnd = high_resolution_clock::now();
        duration<double> time1 = duration_cast<duration<double>>(tEnd - tStart);
        out << endl << "Number Of Matrix: " << numMat[i] << endl;
        out << "product Of The Matrix Chain (time: " << time1.count() << " ): "<< endl;
        out << productMatrixChain;

        tStart = high_resolution_clock::now();
        Matrix<int> product = vec_mat[0] * vec_mat[1];
        for (int i = 2; i < vec_mat.size(); i++) {
            product *= vec_mat[i];
        }
        tEnd = high_resolution_clock::now();
        duration<double> time2 = duration_cast<duration<double>>(tEnd - tStart);
        out << endl << "Number Of Matrix: " << numMat[i] << endl;
        out << "product Of The Matrix Chain (time: " << time2.count() << " ): " << endl;
        out << product;
    }


    in.close();
    out.close();


}

int main() {
    srand((unsigned)time(0));
    task_1();
    return 0;
}