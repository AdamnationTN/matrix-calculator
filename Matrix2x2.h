#ifndef MATRIX2x2_H
#define MATRIX2x2_H
#include <vector>
#include <iostream>
template <typename T>

class Matrix2x2{
    int rows = 2;
    int cols = 2;
    std::vector<std::vector<T>> matrix;
    public:
    Matrix2x2 () : matrix(rows,std::vector<T>(cols)){};
        std::vector<std::vector<T>> getMat(){
            return this->matrix;
        }
        
        void FillMat(){
            for (int i = 0; i < rows ; i++){
                for(int j = 0; j < cols ; j++){
                    std::cout << "M[" << i << "][" << j << "] = ";
                    std::cin >> matrix[i][j];
                }
            }
        }
        Matrix2x2 operator+ (const Matrix2x2& leftop) const{
            Matrix2x2 temp;
            for (int i = 0; i < rows ; i++){
                for(int j = 0; j < cols ; j++){
                    temp.matrix[i][j] += this->matrix[i][j] + leftop.matrix[i][j];
                }
            }
            return temp;
        };        
        Matrix2x2 operator- (const Matrix2x2& leftop) const{
            
            Matrix2x2 temp;
            for (int i = 0; i < rows ; i++){
                for(int j = 0; j < cols ; j++){
                    temp.matrix[i][j] += this->matrix[i][j] - leftop.matrix[i][j];
                }
            }
            return temp;
        };        
        Matrix2x2 operator* (Matrix2x2& leftop) const{
            std::vector<std::vector<T>> temp (rows,std::vector<T>(cols));
            for (int i = 0; i < rows ; i++){
                for(int j = 0; j < cols ; j++){
                    for(int k = 0; k < cols;k++){
                    temp[i][j] += this->matrix[i][k] * leftop.matrix[k][j];
                }
            }
            return temp;
        }
        };
        ~Matrix2x2(){}

};




#endif