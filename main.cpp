#include <iostream>
#include "Matrix.h"

int main()
{ 
    Vector2D<int> vec2d(1,2);
    std::cout << vec2d.Magnitude() << std::endl;
    return 0;
}