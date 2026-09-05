#ifndef MATRIX_H
#define MATRIX_H
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>

template <typename T>
class Matrix
{
private:
    int rows;
    int cols;
    std::vector<std::vector<T>> matrix;

public:
    // initializing the Matrix object
    Matrix(int x, int y) : rows(x), cols(y), matrix(rows, std::vector<T>(cols, T{})){};
    // getting rows
    int getRow() const
    {
        return this->rows;
    }
    // getting columns
    int getCols() const
    {
        return this->cols;
    }
    // matrix getter function
    std::vector<std::vector<T>>& getMat()
    {
        return this->matrix;
    }
    const std::vector<std::vector<T>>& getMat() const
    {
        return this->matrix;
    }

    // Subscript operator overloads for convenient element access (e.g., m[0][1])
    const std::vector<T> &operator[](size_t index) const
    {
        return matrix[index];
    }
    std::vector<T> &operator[](size_t index)
    {
        return matrix[index];
    }
    void showMat() const{
        for (int i = 0 ; i < rows; i++){
            for(int j = 0; j < cols ; j++){
                std::cout << this->matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
    // filling out the matrix
    void FillMat()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "M[" << i << "][" << j << "] = ";
                std::cin >> matrix[i][j];
            }
        }
    }

    // Matrix Addition
    Matrix<T> operator+(const Matrix &rightOp) const
    {
        assert(rightOp.getCols() == this->getCols() && rightOp.getRow() == this->getRow());
        Matrix<T> temp(rows,cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.matrix[i][j] = this->matrix[i][j] + rightOp.matrix[i][j];
            }
        }
        return temp;
    }

    // Subtraction
    Matrix<T> operator-(const Matrix &rightOp) const
    {
        assert(rightOp.getCols() == this->getCols() && rightOp.getRow() == this->getRow());
    if((this->getRow() == 2 && rightOp.getRow()==2 ) && (this->getCols() == 2 && rightOp.getCols()==2 )){    
        Matrix<T> temp (2,2);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.getMat()[i][j] = this->matrix[i][j] - rightOp.matrix[i][j];
            }
        }
        return temp;
    }}

    // Matrix Multiplication

    Matrix<T> operator*(const Matrix &rightOp) const
    {
        assert(this->cols == rightOp.getRow());
        Matrix<T> temp(this->getRow(), rightOp.getCols());
        for (int i = 0; i < temp.getRow(); i++)
        {
            for (int j = 0; j < temp.getCols(); j++)
            {
                temp.getMat()[i][j] = T(); // Ensure zero-initialization before accumulating
                for (int k = 0; k < cols; k++)
                {
                    temp.getMat()[i][j] += this->matrix[i][k] * rightOp.getMat()[k][j];
                }
            }
        }
        return temp;
    }
    // custom rule for Matrix Multiplication by scalar
    Matrix<T> operator*(T scalar) const
    {
        
        Matrix<T> temp(this->getRow(),this->getCols());
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.getMat()[i][j] += this->getMat()[i][j] * scalar;
            }
        }
    }
    // Transpose

    Matrix<T> Transpose() const{
    
        Matrix<T> res(this->getCols(), this->getRow());
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                res.matrix[j][i] = this->matrix[i][j];
            }
        }
        return res;
    }
    T Determinant()
    {
        // calculating a 2x2 determinant
        if (rows == 2 && cols == 2)
        {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        // calculating a 3x3 determinant
        else if (rows == 3 && cols == 3)
        {
            return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) 
            - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]) 
            + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
        }
    }

    T Minor(int i, int j, Matrix<T>& mat)
    {
    if (mat.getRow() == 2 && mat.getCols() == 2)
    {
        for (int x = 0; x < 2; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                if (!(x == i || y == j))
                {
                    return mat.getMat()[x][y];
                }
            }
        }
    }

    else if (mat.getRow() == 3 && mat.getCols() == 3)
    {
        Matrix<T> minormat(2, 2);

        int k = 0;
        int g = 0;

        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (!(x == i || y == j))
                {
                    minormat.getMat()[k][g] = mat.getMat()[x][y];

                    g++;

                    if (g == 2)
                    {
                        g = 0;
                        k++;
                    }
                }
            }
        }

        return minormat.Determinant();
    }

        // the cofactor of the matrix
    Matrix<T> CofactorMat()
        {
            if (this->getRow() == 2 && this->getCols() == 2)
            {
                Matrix<T> cofactor(2, 2);
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        cofactor.getMat()[i][j] = static_cast<T>(std::pow(-1, i + j)) * Minor(i, j, *this);
                    }
                }
                return cofactor;
            }
            else if (rows == 3 && cols == 3)
            {
                Matrix<T> cofactor(3, 3);
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        cofactor.getMat()[i][j] = static_cast<T>(std::pow(-1, i + j)) * Minor(i, j, *this);
                    }
                }
                return cofactor;
            }
        }
        Matrix<T> Adjoint(){
            if (this->rows == 2 && this->cols == 2){
                Matrix<T> temp(2,2);
                temp = *this;
                temp = temp.CofactorMat();
                temp = temp.Transpose();            
                return temp;
            }
            else if (this->rows == 3 && this->cols == 3){
                Matrix<T> temp (3,3);
                temp = *this;
                temp = temp.CofactorMat();
                temp = temp.Transpose();            
                return temp;
            }

        }
        Matrix<T> Inverse(){
            assert(this->Determinant() != 0 && "determinant of matrix must be different than 0 in order to be matrix inversible!");
            if (this->rows == 2 && this->cols == 2){
                const T invdet = static_cast<T>(1/this->Determinant());
                Matrix<T> temp(2,2);
                temp = *this;
                temp = temp.CofactorMat();
                temp = temp.Transpose();
                temp = invdet * temp;
                return temp;
                
            }
            else if (this->rows == 3 && this->cols == 3){
                const T invdet = static_cast<T>(1/this->Determinant());
                Matrix<T> temp(3,3);
                temp = *this;
                temp = temp.CofactorMat();
                temp = temp.Transpose();
                temp = invdet * temp;
                return temp;
            }
        }

        // Destructor
        ~Matrix(){};
    }
};

#endif