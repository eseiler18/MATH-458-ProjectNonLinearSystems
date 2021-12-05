//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTNODE_H
#define PCSC_PROJECT_ABSTRACTNODE_H

class AbstractNode{
public:
    virtual ~AbstractNode(){}
    virtual double solve(double x)=0;
};

#endif //PCSC_PROJECT_ABSTRACTNODE_H
