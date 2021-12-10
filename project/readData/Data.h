//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#ifndef PCSC_PROJECT_DATA_H
#define PCSC_PROJECT_DATA_H

#include <string>
#include <map>
#include "../parser/Solver.h"

/**
 * Structure which contain parameters associated numerical methods.
 * Corresponding to one row of the csv file.
 * Parameters have default value because cells of the csv file can be empty.
 */
struct Data{
    // function of the equation mandatory (build with Solver.h)
    AbstractNode* fun = nullptr;
    // derivative optional depends on the methods requested
    AbstractNode* dFun = nullptr;
    // Other variables optional depends on the methods requested
    double lowerBound = 0;
    double upperBound = 0;
    double initialValue = 0;
    double tolerance = 0;
    int maxIter = 0;
    // map to know which are the methods requested
    std::map <std::string, bool> method = {{"Newton",false}, {"Bisection",false},
                                           {"Chord",false},{"FixedPoint",false}};
};

#endif //PCSC_PROJECT_DATA_H
