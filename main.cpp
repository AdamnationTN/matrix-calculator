#include <iostream>
#include "Matrix.h"

int main()
{ 
    Matrix<double> mat(2,2);
    std::cout << "fill you matrix: \n";
    std::cin >> mat;
    std::cout << mat;
    std::cout << '\n' << mat.Determinant() << '\n';
    return 0;
}