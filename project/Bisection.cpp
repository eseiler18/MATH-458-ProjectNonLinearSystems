//
// Created by lleguill on 01.12.21.
//

#include "Bisection.h"
#include <cassert>

Bisection::Bisection() =default;

Bisection::~Bisection() =default;

void Bisection::SolveEquation() const {
    double a=upperBound;
    double b=lowerBound;
    std::cout<<"Bisection Method :"<<std::endl;

    //Tcheck 1 : Bound viability
    assert(b>a);

    //Tcheck 2 : Solution possible ?
    assert(GetFValue(a)* GetFValue(b)<0);

    //Tcheck Direct Solution
    if (GetFValue(a)==0){
        std::cout<<"A Solution is the lowerBound : x= "<<a<<std::endl;
        return;
    }
    if (GetFValue(b)==0){
        std::cout<<"A Solution is the Upperbound : x= "<<b<<std::endl;
        return;
    }

    //Initialise
    double aux = (a+b)/2;
    double res = (b-a)/2;
    int it = 1;

    while (res > tolerance && it < maxIter) {
        if (GetFValue(aux)==0){
            std::cout << "Exact solution founded after  " << it << " iterations "<< std::endl;
            std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
            return;
        }

        if (GetFValue(a)* GetFValue(aux)<0){b=aux;}
        else if (GetFValue(b)* GetFValue(aux)<0){a=aux;}
        else {
            std::cout<<"Bisection Algorithm not operating correctly"<<std::endl;
            return;
        }
        aux= (a+b)/2;
        res /= 2;
        it +=1;
    }

    if (it > maxIter){
        std::cout << "Didn't converge after " << maxIter << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "Difference of successive iterates = " << res;
        std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
    }
    else{
        std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
    }



}
