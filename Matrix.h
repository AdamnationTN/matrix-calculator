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
    // Initializing the Matrix object
    Matrix(int x, int y) : rows(x), cols(y), matrix(rows, std::vector<T>(cols, T{})) {
        assert(this->rows >= 1  && this->rows <= 4 && this->cols >= 1 && this->cols <= 4 && "the matrix sizes of rows and cols must be between 1 to 4!");
    }

    // Destructor
    ~Matrix() {}

    // Getting rows
    int getRow() const { return this->rows; }

    // Getting columns
    int getCols() const { return this->cols; }

    // Matrix getter functions
    std::vector<std::vector<T>> &getMat() { return this->matrix; }
    const std::vector<std::vector<T>> &getMat() const { return this->matrix; }

    // Subscript operator overloads
    const std::vector<T> &operator[](size_t index) const { return matrix[index]; }
    std::vector<T> &operator[](size_t index) { return matrix[index]; }
    // old method printing a matrix
    /*void showMat() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << this->matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }*/
   //overloaded operator<< for printing a matrix
   friend std::ostream& operator<< (std::ostream& out,const Matrix<T>& mat){
        for(int i = 0; i < mat.getRow(); i++){
            for(int j = 0; j < mat.getCols(); j++){
                out << mat.getMat()[i][j] << ' ';
            }
            out << '\n';
        }
        return out;
   };
   friend std::istream& operator>> (std::istream& in, Matrix<T>& mat){
        for (int i = 0;i < mat.getRow() ;i++){
            for (int j = 0; j < mat.getCols(); j++){
                std::cout << "M[" << i+1 << "][" << j+1 << "] = ";
                in >> mat.getMat()[i][j];
            }
        }
        return in;
   }

    void FillMat()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "M[" << i+1 << "][" << j+1 << "] = ";
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
        Matrix<T> temp(this->rows, rightOp.getCols());
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
                temp.getMat()[i][j] = T(); 
                for (int k = 0; k < cols; k++)
                {
                    temp.getMat()[i][j] += this->matrix[i][k] * rightOp.getMat()[k][j];
                }
            }
        }
        return temp;
    }

    // Scalar Multiplication
    Matrix<T> operator*(T scalar) const
    {
        Matrix<T> temp(this->rows, this->cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                temp.getMat()[i][j] = this->getMat()[i][j] * scalar;
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
        if (rows == 1 && cols == 1)
        {
            return matrix[0][0];
        }
        else
        {
            T d = 0;
            int sign = 1;
            for (int i = 0; i < cols; i++)
            {
                d += sign * this->matrix[0][i] * this->Minor(0, i, *this);
                sign *= -1;
            }
            return d;
        }
    }

    T Minor(int i, int j, Matrix<T> &mat)
    {
        assert(mat.getRow() == mat.getCols() && "the matrix must be square");
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

    // The cofactor of the matrix
    Matrix<T> CofactorMat()
    {
        assert(this->getRow() == this->getCols() && "the matrix dimensions must be square!");
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
        T det = this->Determinant();
        assert(det != 0 && "Matrix is not invertible (determinant is 0)!");
        T invdet = static_cast<T>(1.0 / det);
        Matrix<T> temp = this->CofactorMat();
        temp = temp.Transpose();
        temp = temp * invdet;
        return temp;
    }
}; // <--- Correctly closing the class here

#endif
