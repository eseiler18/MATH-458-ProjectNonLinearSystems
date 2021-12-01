//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "Newton.h"

Newton::Newton() = default;

Newton::~Newton() = default;

void Newton::SolveEquation() const {
    int it = 1;
    double res = tolerance + 1;
    double xPrev = initialValue;
    double xNext;
    while (res > tolerance && it < maxIter){
        xNext = xPrev - GetFValue(xPrev) / GetDfValue(xPrev);
        res=std::abs(xPrev-xNext);
        it+=1;
        xPrev = xNext;
    }
    std::cout << "Newton Method :" << std::endl;
    if (it > maxIter){
        std::cout << "Didn't converge after " << maxIter << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "Difference of successive iterates = " << res;
        std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
    }
    else{
        std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
    }
}


