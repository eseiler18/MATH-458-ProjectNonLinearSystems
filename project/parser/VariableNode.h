//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_VARIABLENODE_H
#define PCSC_PROJECT_VARIABLENODE_H

class VariableNode : public AbstractNode{
public:

    double solve(double x) override{ return x;}

};

#endif //PCSC_PROJECT_VARIABLENODE_H
