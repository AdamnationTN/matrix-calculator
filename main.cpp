#include <iostream>
#include "Matrix.h"

int main()
{
    Matrix<double> mat(2,2);
    std::cout << "fill you matrix: \n";
    mat.FillMat();
    mat.showMat();
    std::cout << '\n' << mat.Determinant() << '\n';
    Matrix<double> invmat (2,2);
    invmat = mat.Inverse();
    invmat.showMat();
    return 0;
}