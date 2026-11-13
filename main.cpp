#include <iostream>
#include "Matrix.h"

int main()
{ 
    Vector2D<int> vec1(3,4);
    Vector2D<int> vec2(1,2);
    std::cout << vec1 << '\n';
    std::cout << vec2 << '\n';
    std::cout << DotProduct(vec1,vec2) << '\n';
    std::cout << vec1.AngleBetween2Vectors(vec1,vec2);    
    return 0;
}