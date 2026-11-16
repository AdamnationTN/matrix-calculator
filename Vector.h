#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <cmath>
#include <concepts>
template<typename T>
requires std::is_arithmetic_v<T>
struct Vector3D{
    T x, y, z;
    inline Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z){};
    inline friend std::ostream& operator<< (std::ostream& out, const Vector3D<T>& vec){
        out << '{' << vec.x << ", " << vec.y << ", " << vec.z << '}';
        return out;
    }
    inline friend std::istream& operator>> (std::istream& in, Vector3D<T>& vec){
        std::cout << "x = ";
        in >> vec.x;
        std::cout << "y = ";
        in >> vec.y;
        std::cout << "z = ";
        in >> vec.z;
        return in;
    }
    T DotProduct(const Vector3D<T>& a, const Vector3D<T>& b){
        return (a.x * b.x + a.y * b.y+ a.z * b.z);
    }
    inline T Magnitude(){
        return std::sqrt(x*x+y*y+z*z);
    }
};


template<typename T>
requires std::is_arithmetic_v<T>
Vector3D<T> CrossProduct (const Vector3D<T>& a, const Vector3D<T>& b){
    T x = a.y * b.z - a.z * b.y;
    T y = a.z * b.x - a.x * b.z;
    T z = a.x * b.y - a.y * b.x;
    return {x, y, z};
}

template<typename T>

requires std::is_arithmetic_v<T>

struct Vector2D{
    T x, y;
    inline Vector2D(T _x, T _y) : x(_x), y(_y){};
    inline friend std::ostream& operator<< (std::ostream& out, const Vector2D<T>& vec){
       out << '{' << vec.x << ", " << vec.y << '}';
       return out;
    }
    inline friend std::istream& operator>> (std::istream& in, Vector2D<T>& vec){
        std::cout << "x = ";
        in >> vec.x;
        std::cout << "y = ";
        in >> vec.y;
        return in;
    }
    inline T Magnitude(){
        return std::sqrt(x*x+y*y);
    }
    int AngleBetween2Vectors(Vector2D<T>& a,Vector2D<T>& b){
        return acos((DotProduct(a,b))/((a.Magnitude()) * (b.Magnitude())));          
    }
    friend inline T DotProduct(const Vector2D<T>& a, const Vector2D<T>& b){};
};
template <typename T>
inline T DotProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
            return (a.x * b.x + a.y * b.y);
}
#endif