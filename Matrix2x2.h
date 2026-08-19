#ifndef MATRIX2x2_H
#define MATRIX2x2_H

#include <array>
#include <iostream>

template <typename T>
class Matrix2x2 {
private:
    static constexpr int rows = 2;
    static constexpr int cols = 2;
    std::array<std::array<T, 2>, 2> matrix{};

public:
    
    Matrix2x2() = default;

    // Const and Non-Const Accessors
    const std::array<std::array<T, 2>, 2>& getMat() const {
        return this->matrix;
    }

    std::array<std::array<T, 2>, 2>& getMat() {
        return this->matrix;
    }

    // Subscript operator overloads for convenient element access (e.g., m[0][1])
    const std::array<T, 2>& operator[](size_t index) const {
        return matrix[index];
    }

    std::array<T, 2>& operator[](size_t index) {
        return matrix[index];
    }

    void FillMat() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "M[" << i << "][" << j << "] = ";
                std::cin >> matrix[i][j];
            }
        }
    }

    // Addition
    Matrix2x2 operator+(const Matrix2x2& rightOp) const {
        Matrix2x2 temp;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.matrix[i][j] = this->matrix[i][j] + rightOp.matrix[i][j];
            }
        }
        return temp;
    }        

    // Subtraction
    Matrix2x2 operator-(const Matrix2x2& rightOp) const {
        Matrix2x2 temp;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.matrix[i][j] = this->matrix[i][j] - rightOp.matrix[i][j];
            }
        }
        return temp;
    }        

    // Multiplication
    Matrix2x2 operator*(const Matrix2x2& rightOp) const {
        Matrix2x2 temp;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.matrix[i][j] = T(); // Ensure zero-initialization before accumulating
                for (int k = 0; k < cols; k++) {
                    temp.matrix[i][j] += this->matrix[i][k] * rightOp.matrix[k][j];
                }
            }
        }
        return temp;
    }

    // Transpose
    Matrix2x2 Transpose() const {
        Matrix2x2 res;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.matrix[i][j] = this->matrix[j][i];
            }
        }
        return res;
    }

    // Destructor
    ~Matrix2x2() = default;
};

#endif