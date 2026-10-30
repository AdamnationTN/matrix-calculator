#include <iostream>
#include "Matrix.h"

int main()
{ 
    Matrix<double> mat(2,2);
    std::cout << "fill you matrix: \n";
    std::cin >> mat;
    if (mat.isEigenvalue(2)){
        std::cout << "this matrix has eigenvalue meaning we can find eigenvector";
    }
    else{}
    return 0;
}