//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_NUMBERNODE_H
#define PCSC_PROJECT_NUMBERNODE_H

#include "AbstractNode.h"

class NumberNode : public AbstractNode{
public:
    NumberNode(double v):value(v){}

    double solve(double x) override{
        return value;
    }
private:
    double value;
};

#endif //PCSC_PROJECT_NUMBERNODE_H
