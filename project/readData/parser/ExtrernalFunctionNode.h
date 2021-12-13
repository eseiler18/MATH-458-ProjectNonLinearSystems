//
// Created by eseiler@INTRANET.EPFL.CH on 11.12.21.
//

#ifndef PCSC_PROJECT_EXTRERNALFUNCTIONNODE_H
#define PCSC_PROJECT_EXTRERNALFUNCTIONNODE_H

#include "AbstractNode.h"
using myP = double(*)(double);
/**
 * External function node use to build an node with function pointer parameter (use when equation is given in code)
 */
class ExternalFunctionNode : public AbstractNode{
public:
    ExternalFunctionNode(myP f):fun(f){}
    /// solve method return simply the value of the function for x
    double solve(int nbParameters, const double parameters[]) override {
        if (nbParameters== 1) {
            return fun(parameters[0]);
        }
        throw new ParserException ("ExternalFunctionNode. several parameters managed not yet implemented");
    }

private:
    myP fun;
};


#endif //PCSC_PROJECT_EXTRERNALFUNCTIONNODE_H
