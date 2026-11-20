#include <iostream>
#include "Matrix.h"
#include <string>
#include "Vector.h"
int main()
{   
    Vector3D<int> vec1(1,0,0);
    Vector3D<int> vec2(0,1,0);
    std::cout << vec1.AngleBetween2Vectors(vec1,vec2);
    return 0;
}