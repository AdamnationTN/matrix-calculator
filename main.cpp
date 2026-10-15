#include <iostream>
#include "Matrix.h"

int main()
{ 
    Matrix<double> mat(4,4);
    std::cout << "fill you matrix: \n";
    mat.FillMat();
    std::cout << mat;
    std::cout << '\n' << mat.Determinant() << '\n';
    Matrix<double> invmat (2,2);
    invmat = mat.Inverse();
    std::cout << invmat;
    return 0;
}