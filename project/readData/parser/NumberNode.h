//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_NUMBERNODE_H
#define PCSC_PROJECT_NUMBERNODE_H

#include "AbstractNode.h"
/**
 * This class is a number node in the binary tree which represent function
 * A number has a value so there is one parameter value
 */
class NumberNode : public AbstractNode{
public:
    NumberNode(double v):value(v){}
    /// Simply for a number return the value of the number
    double solve(int nbParameters, const double parameters[]) {
        return value;
    }
private:
    double value;
};

#endif //PCSC_PROJECT_NUMBERNODE_H
