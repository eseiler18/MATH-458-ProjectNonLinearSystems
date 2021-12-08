//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#ifndef PCSC_PROJECT_DATA_H
#define PCSC_PROJECT_DATA_H

#include <string>
#include <map>
#include "../parser/Solver.h"

struct Data{
    // Root node of function and derivative 's trees
    AbstractNode* fun = nullptr;
    AbstractNode* dFun = nullptr;
    // Other variables to apply methods
    double lowerBound = 0;
    double upperBound = 0;
    double initialValue = 0;
    double tolerance = 0;
    int maxIter = 0;
    std::map <std::string, bool> method = {{"Newton",false}, {"Bisection",false},
                                           {"Chord",false},{"FixedPoint",false}};
};

#endif //PCSC_PROJECT_DATA_H
