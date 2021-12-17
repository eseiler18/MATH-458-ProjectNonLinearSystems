//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#ifndef PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H
#define PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H

#include "AbstractInterpreterFunction.h"
#include "parser/Solver.h"

/**
 * Child of AbstractInterpreterFunction for the mathematics expression of the function as input.
 * Here the functionName parameter is the expression of the function
 */
class InterpreterMathExpression: public AbstractInterpreterFunction{
public:
    InterpreterMathExpression(std::string &expressionFunction):AbstractInterpreterFunction(expressionFunction){}
    /// create the executable tree and return the root
    AbstractNode* createExecutableFunction() override{
        return Solver::strToFun(functionName);
    }
};

#endif //PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H
