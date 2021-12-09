//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_VARIABLENODE_H
#define PCSC_PROJECT_VARIABLENODE_H
/**
 * This class is a variable node of the binary tree which represent function
 */
class VariableNode : public AbstractNode{
public:
    /// Simply for variable x return the value of x
    double solve(double x) override{ return x;}
};

#endif //PCSC_PROJECT_VARIABLENODE_H
