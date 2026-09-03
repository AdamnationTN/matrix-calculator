#include <iostream>
#include "Matrix.h"

int main()
{
    Matrix<double> mat(2,2);
    mat.FillMat();
    Matrix<double> cofact(2,2);
    cofact = mat.CofactorMat();
    cofact.showMat();
    return 0;
}