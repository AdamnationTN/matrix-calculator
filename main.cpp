#include <iostream>


struct Fraction{
    int numerator;
    int denominator;
};

void addnumAndDeno(Fraction& frac){
    std::cout << "Enter the value for the numerator : ";
    std::cin >> frac.numerator;
    std::cout << "Enter the value for the denominator : ";
    std::cin >> frac.denominator;

}

Fraction operator* (Fraction& first, Fraction& second ){
    return {first.numerator * second.numerator, first.denominator * second.denominator};
}

void printres(const Fraction& res){
    std::cout << "Your fractions multiplied together to : " << res.numerator <<'/'<< res.denominator;
}


int main(){
    Fraction frac1{};
    Fraction frac2{};
    Fraction res{};
    addnumAndDeno(frac1);
    addnumAndDeno(frac2);
    res = frac1 * frac2;
    printres(res);
    return 0;



}