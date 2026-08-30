#include <iostream>
#include "Matrix2x2.h"



int main(){
    char choice,choice1;
    int rows, cols;

    std::cout << "Please choose the data type of Matrix you want to create :\n";
    std::cout << "A. Int\n";
    std::cout << "B. float\n";
    std::cout << "C. double\n";

    std::cin >> choice;
    std::cout << "Please choose the size of Matrix you want to create :\n";
    std::cout << "A.2x2\n";
    std::cout << "B.3x3\n";
    std::cin >> choice1;
    

    
    std::cout << "Fill your matrix: " << '\n';
    
    mat.FillMat();
    


    return 0;
}