//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include <iostream>
#include "Solver.h"

int main(){
    Solver s;
    std::cout << s.interpreterVision("4x") << std::endl << s.interpreterVision("x^2+1")<< std::endl;
    auto function = s.strToFun("-4x");
    std::cout << function->solve(2.5) << std::endl;
};

