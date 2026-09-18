#ifndef MATRIX_H
#define MATRIX_H
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include <cctype>
template <typename T>
class Matrix
{
private:
    int rows;
    int cols;
    std::vector<std::vector<T>> matrix;

public:
    // initializing the Matrix object
    Matrix(int x, int y) : rows(x), cols(y), matrix(rows, std::vector<T>(cols, T{})) {};

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
    std::vector<std::vector<T>> &getMat()
    {
        return this->matrix;
    }
    const std::vector<std::vector<T>> &getMat() const
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

    void showMat() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
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
        Matrix<T> temp(rows, cols);
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
        assert(rightOp.getCols() == this->getCols() && rightOp.getRow() == this->getRow() && "the row and cols must be equal to both matrices!");
        // NxN substraction
        Matrix<T> temp(this->rows, rightOp.getCols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.getMat()[i][j] = this->matrix[i][j] - rightOp.matrix[i][j];
            }
        }
        return temp;
    }

    // Matrix Multiplication
    Matrix<T> operator*(Matrix &rightOp) const
    {

        assert(this->cols == rightOp.getRow());
        Matrix<T> temp(this->getRow(), rightOp.getCols());
        for (int i = 0; i < temp.getRow(); i++)
        {
            for (int j = 0; j < temp.getCols(); j++)
            {
                temp.getMat()[i][j] = T(); // Ensure zero-initialization before accumulating (setting matrix to 0)
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
        Matrix<T> temp(this->rows, this->cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.getMat()[i][j] += this->getMat()[i][j] * scalar;
            }
        }
        return temp;
    }

    // Transpose
    Matrix<T> Transpose() const
    {
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
        assert(this->rows == this->cols && "the matrix sizes must be n x n");
        // 1x1 determinant
        if (rows == 1 && cols == 1)
        {
            return matrix[0][0];
        }
        // calculating a NxN determinant
        else
        {
            T deter = 0;
            int sign = 1;
            for (int i = 0; i < cols; i++)
            {
                deter += sign * this->matrix[0][i] * static_cast<T>(this->Minor(0, i, *this));
                sign *= -1;
            }
            return deter;
        }
        return T{};
    }

    T Minor(int i, int j, Matrix<T> &mat)
    {
        assert(mat.getRow() == mat.getCols()) && "the matrix must be square";

        // NxN matrix condition

        Matrix<T> minormat(mat.getRow() - 1, mat.getCols() - 1);
        int k = 0;
        int g = 0;
        for (int x = 0; x < mat.getRow(); x++)
        {
            for (int y = 0; y < mat.getCols(); y++)
            {
                if (!(x == i || y == j))
                {
                    minormat.getMat()[k][g] = mat.getMat()[x][y];
                    g++;
                    if (g == minormat.getCols())
                    {
                        g = 0;
                        k++;
                    }
                }
            }
        }
            return minormat.Determinant();
        }
        return T{};
    }

// the cofactor of the matrix
    Matrix<T> CofactorMat()
    {
    assert(this->getRow() == this->getCols() && "the matrix dimenstions must be square in order to make a cofactor matrix");
        {
        Matrix<T> cofactor(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cofactor.getMat()[i][j] = static_cast<T>(std::pow(-1, i + j)) * Minor(i, j, *this);
            }
            }
            return cofactor;
        }
        return Matrix<T>(0, 0);
    }

    Matrix<T> Adjoint()
    {
    if (this->rows == this->cols)
    {
        Matrix<T> temp(this->rows, this->cols);
        temp = *this;
        temp = temp.CofactorMat();
        temp = temp.Transpose();
        return temp;
    }

        return Matrix<T>(0, 0);
    }

    Matrix<T> Inverse()
    {
    assert(this->Determinant() != 0 && "determinant of matrix must be different than 0 + columns and rows are equal in order to be matrix inversible!");
    T invdet = static_cast<T>(1.0 / this->Determinant());
    Matrix<T> temp(2, 2);
    temp = *this;
    temp = temp.CofactorMat();
    temp = temp.Transpose();
    temp = temp * invdet;
    return temp;
    }

// Destructor
    ~Matrix(){};

};

#endif
