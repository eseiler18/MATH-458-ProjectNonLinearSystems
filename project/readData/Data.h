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
    AbstractNode* fun;
    AbstractNode* dFun;
    // Other variables to apply methods
    double lowerBound;
    double upperBound;
    double initialValue;
    double tolerance;
    int maxIter;
    std::map <std::string, bool> method = {{"Newton",true}, {"Bisection",true},
                                           {"Chord",true},{"FixedPoint",true}};
};

#endif //PCSC_PROJECT_DATA_H
