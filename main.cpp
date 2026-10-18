#include <iostream>
#include "Matrix.h"

int main()
{ 
    Matrix<double> mat(2,3);
    Matrix<double> mat2(3,2);
    std::cout << "fill you matrix: \n";
    std::cin >> mat;
    std::cin >> mat2;
    std::cout << mat * mat2;
    return 0;
}