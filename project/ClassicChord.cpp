//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#include "ClassicChord.h"

ClassicChord::ClassicChord() = default;


ClassicChord::~ClassicChord() = default;

void ClassicChord::SolveEquation() const {
    int it = 1;
    double xPrev = initialValue;
    double m = 0.1;
    double x = xPrev - m * GetFValue(xPrev); //first iteration with m=0.1
    double xNext;
    double res = std::abs(x - xPrev);

    while (res > tolerance && it < maxIter) {
        m = (x - xPrev)/(GetFValue(x) - GetFValue(xPrev));
        xNext = x - m * GetFValue(x);
        res = std::abs(xNext - x);
        it += 1;
        xPrev = x;
        x = xNext;
    }
    std::cout << "Classic Chord Method :" << std::endl;
    if (it >= maxIter) {
        std::cout << "Didn't converge after " << maxIter << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "Difference of successive iterates = " << res;
        std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
    } else {
        std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
    }
}

