//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTNODE_H
#define PCSC_PROJECT_ABSTRACTNODE_H
#include "ParserException.h"
/**
 * This class is an abstract node of the binary tree which represent function
 */
class AbstractNode{
public:
    virtual ~AbstractNode()= default;
    /// This methods return the value of a node f(x) associated to an input array of parameters
    virtual double solve(int nbParameters, const double parameters[])=0;

    /// This methods return the value of a node f(x) associated to an input x
    double solve(double x) {
        // ascend compatibility create a list with only one parameter
        return solve(1, &x);
    };
};
#endif //PCSC_PROJECT_ABSTRACTNODE_H
