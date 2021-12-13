//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTNODE_H
#define PCSC_PROJECT_ABSTRACTNODE_H
/**
 * This class is an abstract node of the binary tree which represent function
 */
class AbstractNode{
public:
    virtual ~AbstractNode()= default;
    /// This methods return the value of a node f(x) associated to an input x
    virtual double solve(double x)=0;
};

#endif //PCSC_PROJECT_ABSTRACTNODE_H
