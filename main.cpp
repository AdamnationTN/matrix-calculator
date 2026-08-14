#include <iostream>
#include "Matrix2x2.h"




int main(){
    Matrix2x2<int> M1;
    Matrix2x2<int> M2;
    M1.FillMat();
    M2.FillMat();
    
    Matrix2x2<int> res;
    res = M1 + M2;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2 ; j++){
            std::cout << res.getMat()[i][j] << ' ';
        }
        std::cout << '\n';
    }


    return 0;
}