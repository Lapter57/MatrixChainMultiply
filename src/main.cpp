#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <chrono>
#include "MatrixDef.h"
#include <iomanip>
using namespace std;

int randomNumber(unsigned int l = 1, unsigned int r = 100) { return (l + (rand() % (r - l + 1))); }
int randomFillMatrix() { return (rand() % 2); }

Matrix<unsigned long long>* matrixChainOrder(const vector<unsigned int>& sizeMat) {
    unsigned int n = sizeMat.size();
    Matrix<unsigned long long> M(n-1, n-1);
    Matrix<unsigned long long> *S;
    S = new Matrix<unsigned long long>(n - 1, n - 1);

    for (register int l = 1; l < n; l++) {
        for (register int i = 1; i < n - l; i++) {
            int j = i + l;
            M(i - 1, j - 1) = numeric_limits<unsigned long long>::max();
            for (register int k = i; k <= j - 1; k++) {
                int q = M(i - 1, k - 1) + M(k, j - 1) + sizeMat[i-1] * sizeMat[k] * sizeMat[j];
                if (q < M(i - 1, j - 1)) {
                    M(i - 1, j - 1) = q;
                    (*S)(i - 1, j - 1) = k-1;
                }
            }
        }
    }
    return S;
}

template <class T>
Matrix<T> matrixChainMultiply(const vector<Matrix<T>*>& matrix, const Matrix<T> &S, int row, int col, ostream& out) {
    if (row == col) {
        out << "A" << row << " ";
        return *matrix[row];
    }
    out << "( ";
    Matrix<T> A(matrixChainMultiply(matrix, S, row, S(row, col), out));
    Matrix<T> B(matrixChainMultiply(matrix, S, S(row, col) + 1, col, out));
    out << ")";
    return A*B;
}


void task() {
    using namespace std::chrono;
    ifstream in;
    ofstream out;
    ofstream outData;
    ofstream outData2;
    in.open("input_1.txt");
    out.open("output_1.txt");
    outData.open("data_M10.txt");
    outData2.open("data_N.txt");
    unsigned int l, r, n;
    in >> l >> r >> n;
    vector<vector<double>> outputN(8);

    vector<unsigned int> numMat(n);
    for (register int i = 0; i < n; i++) {
        in >> numMat[i];
    }

    for (register int r = 5; r <= 40; r += 5) {
        //outData << "M = " << r << endl << endl;
        outData << left << setw(4) << r;
        vector<Matrix<unsigned long long>*> vec_mat;
        vector<unsigned int> sizeMat;
        for (register int i = 0; i < n; i++) {
            double valueTimeOpt = 0.0;
            double valueTimeNotOpt = 0.0;
            for (register int p = 0; p < 10000; p++) {
                sizeMat.resize(numMat[i] + 1);

                for (auto && el : sizeMat) {
                    el = randomNumber(l, r);
                }
                int k = 0;
                Matrix<unsigned long long> *matrix;
                for (register int j = 0; j < numMat[i]; j++) {
                    matrix = new Matrix<unsigned long long>(sizeMat[k], sizeMat[k + 1]);
                    matrix->randomGenerate(&randomFillMatrix);
                    //out << *matrix << endl;
                    vec_mat.push_back(matrix);
                    k++;
                }
                out << endl;

                auto tStart = high_resolution_clock::now();
                Matrix<unsigned long long> *optimalCost = matrixChainOrder(sizeMat);
                Matrix<unsigned long long> productMatrixChain = matrixChainMultiply(vec_mat, *optimalCost, 0, numMat[i] - 1, out);
                auto tEnd = high_resolution_clock::now();
                auto time1 = duration_cast<duration<double, milli>>(tEnd - tStart);
                valueTimeOpt += time1.count();
                /*out << endl << "Number Of Matrix: " << numMat[i] << endl;
                out << "product Of The Matrix Chain (time: " << time1.count() << " ): " << endl;*/
                //out << productMatrixChain;

                tStart = high_resolution_clock::now();
                Matrix<unsigned long long> product = *vec_mat[0] * *vec_mat[1];
                for (int i = 2; i < vec_mat.size(); i++) {
                    product *= *vec_mat[i];
                }
                tEnd = high_resolution_clock::now();
                auto time2 = duration_cast<duration<double, milli>>(tEnd - tStart);
                valueTimeNotOpt += time2.count();
                /*out << endl << "Number Of Matrix: " << numMat[i] << endl;
                out << "product Of The Matrix Chain (time: " << time2.count() << " ): " << endl;*/
                //out << product;

                //outData << left << setw(10) << setprecision(4) << time1.count() << setw(10) << setprecision(4) << time2.count();

                delete optimalCost;
                optimalCost = nullptr;
                sizeMat.clear();
                for (auto && el : vec_mat) {
                    delete el;
                    el = nullptr;
                }
                vec_mat.clear();
            }
            valueTimeOpt /= 10000.0;
            valueTimeNotOpt /= 10000.0;
            outData << left << setw(10) << setprecision(4) << valueTimeOpt << setw(10) << setprecision(4) << valueTimeNotOpt;
            outputN[(numMat[i] / 5) - 1].push_back(valueTimeOpt);
            outputN[(numMat[i] / 5) - 1].push_back(valueTimeNotOpt);
        }
        outData << endl;
    }

    for (register int i = 0; i < 8; i++) {
        outData2 << left << setw(4) << i*5+5;
        for (register int j = 0; j < outputN[i].size(); j++) {
            outData2 << left << setw(10) << setprecision(4) << outputN[i][j];
        }
        outData2 << endl;
    }
    in.close();
    out.close();
    outData.close();
    outData2.close();


}


unsigned long long matrixChainOrderMin(const vector<unsigned int>& sizeMat) {
    unsigned int n = sizeMat.size();
    Matrix<unsigned long long> M(n-1, n-1);
    for (register int l = 1; l < n; l++) {
        for (register int i = 1; i < n - l; i++) {
            int j = i + l;
            M(i - 1, j - 1) = numeric_limits<unsigned long long>::max();
            for (register int k = i; k <= j - 1; k++) {
                int q = M(i - 1, k - 1) + M(k, j - 1) + sizeMat[i - 1] * sizeMat[k] * sizeMat[j];
                if (q < M(i - 1, j - 1)) {
                    M(i - 1, j - 1) = q;
                }
            }
        }
    }
    return M(0,n-2);
}

void task_2() {
    ifstream in;
    ofstream out;
    ofstream outData;
    ofstream outData2;
    in.open("input_1.txt");
    out.open("output_1.txt");
    outData.open("data_M12.txt");
    outData2.open("data_N12.txt");
    unsigned int l, r, n;
    in >> l >> r >> n;
    vector<vector<unsigned long long>> outputN(8);

    vector<unsigned int> numMat(n);
    for (register int i = 0; i < n; i++) {
        in >> numMat[i];
    }

    for (register int r = 5; r <= 40; r += 5) {
        //outData << "M = " << r << endl << endl;
        outData << left << setw(4) << r;
        vector<Matrix<unsigned long long>*> vec_mat;
        vector<unsigned int> sizeMat;
        for (register int i = 0; i < n; i++) {
            unsigned long long optimalCost = 0;
            unsigned long long notOptimalCost = 0;
            for (register int p = 0; p < 10000; p++) {
                sizeMat.resize(numMat[i] + 1);
                for (auto && el : sizeMat) {
                    el = randomNumber(l, r);
                }
                optimalCost += matrixChainOrderMin(sizeMat);
                for (register int k = 1; k < numMat[i]; k++) {
                    notOptimalCost += sizeMat[0] * sizeMat[k] * sizeMat[k + 1];
                }

            }
            optimalCost /= 10000;
            notOptimalCost /= 10000;
            outData << left << setw(10) << optimalCost << setw(10) << setprecision(4) << notOptimalCost;
            outputN[(numMat[i] / 5) - 1].push_back(optimalCost);
            outputN[(numMat[i] / 5) - 1].push_back(notOptimalCost);
        }
        outData << endl;
    }

    for (register int i = 0; i < 8; i++) {
        outData2 << left << setw(4) << i * 5 + 5;
        for (register int j = 0; j < outputN[i].size(); j++) {
            outData2 << left << setw(10)  << outputN[i][j];
        }
        outData2 << endl;
    }
    in.close();
    out.close();
    outData.close();
    outData2.close();
}

int main() {
    srand((unsigned)time(0));
    task();
    task_2();
    return 0;
}