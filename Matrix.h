#ifndef MATRIX_H
#define MATRIX_H

#include <type_traits>
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <concepts>
template <typename T>

requires std::is_arithmetic_v<T>

class Matrix
{
    private:
    int rows;
    int cols;
    std::vector<std::vector<T>> matrix;
    
    public:
    // Initializing the Matrix object
    Matrix(int x, int y) : rows(x), cols(y) {
        assert(rows > 0 && cols > 0 && "The matrix dimenstions must not to be negative or null");
        matrix.resize(rows, std::vector<T>(cols, T{}));
    }
    
    
    // Getting rows
    int getRow() const { return this->rows; }

    // Getting columns
    int getCols() const { return this->cols; }
    
    // Matrix getter functions
    std::vector<std::vector<T>> &at() { return this->matrix; }
    const std::vector<std::vector<T>> &at() const { return this->matrix; }
    
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
               out << mat.at()[i][j] << ' ';
            }
            out << '\n';
        }
        return out;
   };
   friend std::istream& operator>> (std::istream& in, Matrix<T>& mat){
       for (int i = 0;i < mat.getRow() ;i++){
           for (int j = 0; j < mat.getCols(); j++){
               std::cout << "M[" << i+1 << "][" << j+1 << "] = ";
               in >> mat.at()[i][j];
            }
        }
        return in;
    }
    
    /*void FillMat()
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
    */
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
                temp.at()[i][j] = this->matrix[i][j] - rightOp.matrix[i][j];
            }
        }
        return temp;
    }
    
    // Matrix Multiplication
    Matrix<T> operator*(const Matrix &rightOp) const
    {
        //int l = 0,r = 0;
        T sum{};
        assert(this->cols == rightOp.getRow() && "the cols of left hand must be equal to the right hand rows!");
        Matrix<T> temp(this->getRow(), rightOp.getCols());
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < rightOp.getCols(); j++)
            { sum = 0;
                for (int k = 0; k < this->cols; k++)
                {
                    sum += this->matrix[i][k] * rightOp.at()[k][j];
                }
                temp.at()[i][j] = sum;
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
                temp.at()[i][j] = this->at()[i][j] * scalar;
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
    
    T Determinant() const requires std::floating_point<T>
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

    T Minor(int i, int j, const Matrix<T> &mat) const
    {
        assert(mat.getRow() == mat.getCols() && i < mat.getRow() && j < mat.getCols() && "the matrix must be square and its indexs not to be outside boundiaries and must be in rows and cols range");
        Matrix<T> minormat(mat.getRow() - 1, mat.getCols() - 1);
        int k = 0;
        int g = 0;
        for (int x = 0; x < mat.getRow(); x++)
        {
            for (int y = 0; y < mat.getCols(); y++)
            {
                if (!(x == i || y == j))
                {
                    minormat.at()[k][g] = mat.at()[x][y];
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
    Matrix<T> CofactorMat() const
    {
        assert(this->getRow() == this->getCols() && "the matrix dimensions must be square!");
        Matrix<T> cofactor(this->rows, this->cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                cofactor.at()[i][j] = static_cast<T>(std::pow(-1, i + j)) * Minor(i, j, *this);
            }
        }
        return cofactor;
    }
    
    Matrix<T> Adjoint() const
    {
        assert(this->rows == this->cols && "the matrix must be square!");
        Matrix<T> temp(this->rows, this->cols);
        temp = *this;
        temp = temp.CofactorMat();
        temp = temp.Transpose();
        return temp;
    }
    
    Matrix<T> Inverse() const requires std::floating_point<T>
    {

        T det = this->Determinant();
        assert(det != 0 && "Matrix is not invertible (determinant is 0)!");
        T invdet = static_cast<T>(1.0 / det);
        Matrix<T> temp = this->CofactorMat();
        temp = temp.Transpose();
        temp = temp * invdet;
        return temp;
    }
    
    
    Matrix<T> Identity(int order) const{
        Matrix<T> temp (order,order);
        for (int i = 0; i < order; i++){
            temp.at()[i][i]=T{1};
        }
        return temp;
    }
    
    bool isEigenValue(T eigenval) const {
        assert(this->rows == this->cols && "the matrix must be square to be eigenvalue!");
        Matrix<T> temp(this->rows,this->rows);
        temp = temp + (*this - (Identity(rows) * eigenval));
        if (temp.Determinant() == 0){
            return true;
        }
        else{
            return false;
        }
        
    }
    bool isNullMat() const{
        bool test=true;
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->cols; j++){
                if (this->at()[i][j] != T{0}){
                    test=false;
                    break;
                }
            }
        }
        return test;
        
    }

    bool isEigenVec(const Matrix<T>& vectoreigen ,T eigenval) const{
        assert(vectoreigen.getCols() == 1 && isEigenValue(eigenval) && this->getRow() == vectoreigen.getRow() && "it must be vector and true eigenvalue to be eigenvector!");
        Matrix<T> temp (this->getRow(),this->cols);
        temp = temp + ((*this - (Identity(rows) * eigenval)) * vectoreigen);
        if (temp.isNullMat() == true){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool isIdentity() const{
        assert(this->rows == this->cols && "the matrix must be square to be identity!");
        Matrix<T> temp(this->rows,this->cols);
        temp = temp + (*this - Identity(this->rows));
        if (temp.isNullMat() == true){
            return true;
        }
        else{
            return false;
        }

    }
    
    bool isInverse(const Matrix<T>& Inv) const{
        assert(this->rows == this->cols && Inv.getRow()==Inv.getCols() && "the matrix must be square and the inverse must be square too!");
        Matrix<T> temp(this->rows,this->cols);
        temp = temp + (*this * Inv);
        Matrix<T> temp2 (this->rows,this->cols);
        temp2 = temp2 + (Inv*(*this));
        
        if (temp.isIdentity() == true && temp2.isIdentity() == true){
            return true;
        }
        else{
            return false;
        }
    }
    inline T Trace() const{
        assert(this->rows == this->cols && "the matrix must be square to find the Trace");
        T Trace = T{0};
        for (int i = 0; i < this->rows;i++){
            Trace += this->matrix[i][i];
        }
        return Trace;
    }
    
}; // <--- Correctly closing the class here
#endif