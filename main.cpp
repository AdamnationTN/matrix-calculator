#include <iostream>
#include "Matrix.h"
#include "Vector.h"

int main()
{ 
    Matrix<float> mat(2,2);
    std::cin >> mat;
    std::cout << mat.Inverse() << '\n';
    std::cout << mat.Transpose() << '\n';
    std::cout << mat.isNullMat() << '\n';
    std::cout << mat.Minor(0,0,mat);
    return 0;
}