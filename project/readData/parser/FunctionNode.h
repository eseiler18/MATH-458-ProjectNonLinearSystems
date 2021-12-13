//
// Created by eseiler@INTRANET.EPFL.CH on 11.12.21.
//

#ifndef PCSC_PROJECT_FUNCTIONNODE_H
#define PCSC_PROJECT_FUNCTIONNODE_H

#include<iostream>
#include<string>
#include "AbstractNode.h"
#include <math.h>

/**
 * External function node use to build an node with function pointer parameter (use when equation is given in code)
 */
class FunctionNode : public AbstractNode{
private:
    std::string funtionName;
    AbstractNode* nestedExpression;
public:
    FunctionNode(const std::string& funtionName, AbstractNode* nestedExpression):funtionName(funtionName), nestedExpression(nestedExpression){}

    /// solve method return simply the value of the function for x
    double solve(int nbParameters, const double parameters[]) override { 
        if (funtionName=="sin") {
            return sin(nestedExpression->solve(nbParameters, parameters));
        }
        if (funtionName=="cos") {
            return cos(nestedExpression->solve(nbParameters, parameters));
        }
        if (funtionName=="tan") {
            return tan(nestedExpression->solve(nbParameters, parameters));
        }
        if (funtionName=="atan") {
            return atan(nestedExpression->solve(nbParameters, parameters));
        }
        if (funtionName=="sqrt") {
            if(nestedExpression->solve(nbParameters,parameters) < 0){
                throw std::invalid_argument("error sqrt of negative number");
            }
            return sqrt(nestedExpression->solve(nbParameters, parameters));
        }
        if (funtionName=="exp"){
            return exp(nestedExpression->solve(nbParameters,parameters));
        }
        if (funtionName=="log"){
            if(nestedExpression->solve(nbParameters,parameters) < 0){
                throw std::invalid_argument("error log of negative number");
            }
            return log(nestedExpression->solve(nbParameters,parameters));
        }
        throw ParserException("Function is not yet implemented:" + funtionName);
    }
 


};

#endif //PCSC_PROJECT_FUNCTIONNODE_H

