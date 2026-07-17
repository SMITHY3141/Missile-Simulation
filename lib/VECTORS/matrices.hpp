

#ifndef MATRICES_HPP
#define MATRICES_HPP
#include "vectors.hpp"

#include <cstddef>
#include <iostream>
#include <cmath>


// DECLERATIONS

template <int N, int M>
struct Matrix {
    float data[N][M]; // rows, columns
    // so data[2][3] = {{?, ?, ?}, {?, ?, ?}}
    // an array of 2, arrays of 3

    Matrix<N, M> inverse() const;

    float* operator[](size_t index);
    const float* operator[](size_t index) const;

};


template <int N, int M>
std::ostream& operator<<(std::ostream& os, const Matrix<N, M> &m);

template <int N, int M>
Vector<N> operator*(const Matrix<N, M> &m, const Vector<M> &v);

template <int N, int M, int K>
Matrix<N, K> operator*(const Matrix<N, M> &m1, const Matrix<M, K> &m2);

template <int N, int M>
Matrix<N, M> get_identity();
  
template <int N, int M>
void swap_rows(Matrix<N, M> &m, int a, int b);

Matrix<3, 3> matrix_from_euler(float yaw, float pitch, float roll);




// DEFINITIONS
template <int N, int M>
std::ostream& operator<<(std::ostream& os, const Matrix<N, M> &m) {
    os << '[' << '\n';
    for (int i = 0; i < N; i++) {
        os << '[';
        for (int j = 0; j < M; j++) {
            os << m[i][j];
            if (j == M - 1) {
                break;
            }
            os << ", ";
        }
        os << "]\n";

    }
    os << "]";
    return os;
}

template <int N, int M>
float* Matrix<N, M>::operator[](size_t index) {
    return data[index]; //returns row, must be later indexed by column
}

template <int N, int M>
const float* Matrix<N, M>::operator[](size_t index) const {
    return data[index];
}



// Assumes it's invertible, runs gaussian elimination
template <int N, int M>
Matrix<N, M> Matrix<N, M>::inverse() const {
    Matrix<N, M> working = *this;
    Matrix<N, M> result = get_identity<N, M>();

    // for each column
    for (int k = 0; k < N; k++) {
        // find a value to eliminate other rows (along this column)
        float base;
        for (int i = k; i < N; i++) {
            if (!working[i][k]) {
                continue;
            }

            base = working[i][k]; 
            if (i == k) {
                continue;
            }

            swap_rows(working, i, k);
            swap_rows(result, i, k);
            break;
        }


        // eliminate other rows
        for (int i = 0; i < N; i++) { // subtract other rows by base row
            if (i == k) { // don't subtract own row by itself
                continue;
            }

            float scale = working[i][k] / base;
            for (int j = 0; j < M; j++) { // reference column should become 0 anyways
                result[i][j] -= scale * result[k][j];
                if (j <= k) {
                    continue;
                }
                working[i][j] -= scale * working[k][j];

            }
        }
    }
    
    // should be diagonal now, just scale each element
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] /= working[i][i];
        }
    }

    return result;
}


template <int N, int M>
Matrix<N, M> get_identity() {
    Matrix<N, M> result{};
    for (int i = 0; i < std::min(N, M); i++) {
        result[i][i] = 1;
    }
    return result;
}

template <int N, int M>
void swap_rows(Matrix<N, M> &m, int a, int b) {
    for (int i = 0; i < M; i++) {
        float val = m[a][i];
        m[a][i] = m[b][i];
        m[b][i] = val;
    }
}

template <int N, int M>
Vector<N> operator*(const Matrix<N, M> &m, const Vector<M> &v) {
    Vector<N> result;
    for (int i = 0; i < N; i++) {
        float sum = 0.f;
        for (int j = 0; j < N; j++) {
            sum += m[i][j] * v[j];

        }
        result[i] = sum;
    }
    return result;
}

template <int N, int M, int K>
Matrix<N, K> operator*(const Matrix<N, M> &m1, const Matrix<M, K> &m2) {
    Matrix<N, K> result;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < K; k++) {
            float sum = 0;
            for (int j = 0; j < M; j++) {
                sum += m1[i][j] * m2[j][k]; // FIXME cache misses maybe?
            }
            result[i][k] = sum;
        }
    }

    return result;
}

// yaw * pitch * roll (x is right, y is forward, z is up)
inline Matrix<3, 3> matrix_from_euler(float yaw, float pitch, float roll) {
    Matrix<3, 3> Z = {{
        {std::cos(yaw), -std::sin(yaw), 0},
        {std::sin(yaw), std::cos(yaw), 0},
        {0, 0, 1}
    }};
    Matrix<3, 3> X = {{
        {1, 0, 0},
        {0, std::cos(pitch), -std::sin(pitch)},
        {0, std::sin(pitch), std::cos(pitch)}
    }};
    Matrix<3, 3> Y = {{
        {std::cos(roll), 0, -std::sin(roll)},
        {0, 1, 0},
        {std::sin(roll), 0, std::cos(roll)}
    }};

    return Z * X * Y;
}

#endif // MATRICES_HPP
