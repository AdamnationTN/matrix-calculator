#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

template <typename T>
class Matrix {
private:
    static int rows;
    static int cols;
    std::vector<std::vector<T>> matrix;

public:
    //initializing the Matrix object
    Matrix2x2(int x, int y) : rows(x),cols(y){
        matrix(rows,std::vector<T>(cols,0));
    } ;
   
    Matrix2x2<T> setMat(){
        
    }

    //getting rows
    int getRow() const{
        return this->rows;
    }
    // getting columns
    int getCols() const{
        return this->cols;
    }
    // matrix getter function
    std::vector<std::vector<T>>& getMat() {
        return this->matrix;
    }

    // Subscript operator overloads for convenient element access (e.g., m[0][1])
    const std::vector<T>& operator[](size_t index) const {
        return matrix[index];
    }
    std::vector<T>& operator[](size_t index) {
        return matrix[index];
    }
    // filling out the matrix
    void FillMat() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << "M[" << i << "][" << j << "] = ";
                std::cin >> matrix[i][j];
            }
        }
    }

    // Matrix Addition
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

    // Matrix Multiplication

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
    // custom rule for Matrix Multiplication by scalar
    Matrix2x2& operator* (T scalar)const {
        Matrix2x2 temp;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                temp.getMat()[i][j] += this->getMat[i][j] * scalar;
            }
        }
        
    }

    // Transpose is by flipping the dimensions

    Matrix2x2 Transpose() const {
        Matrix2x2 res(this->getCols(),this->getRow());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res.matrix[j][i] = this->matrix[i][j];
            }
        }
        return res;
    }
    T Determinant(){
        // calculating a 2x2 determinant
        if(this->getRow() == 2 && this->getCols() == 2){
            return this->getMat()[0][0]*this->getMat()[1][1] - this->getMat()[0][1]* this->getMat()[1][0];
        }
        // calculating a 3x3 determinant
        else if{this->getRow() == 3 && this->getCols() == 3}{
            return this->getMat()[0][0]*(this->getMat()[1][1]*this->getMat()[2][2]-this->getMat()[2][1]*this->getMat()[1][2]) 
            - this->getMat()[0][1]*(this->getMat()[1][0]*this->getMat()[2][2] - this->getMat()[2][0]*this->getMat()[1][2])
            + this->getMat()[0][2]*(this->getMat()[1][0]*this->getMat()[2][1]-this->getMat()[2][0]*this->getMat()[1][1]);
        }
    }  

    // Destructor
    ~Matrix2x2() = default;
};

#endif