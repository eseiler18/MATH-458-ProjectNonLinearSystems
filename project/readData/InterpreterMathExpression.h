//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#ifndef PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H
#define PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H

#include "AbstractInterpreterFunction.h"
#include "parser/Solver.h"

class InterpreterMathExpression: public AbstractInterpreterFunction{
public:
    InterpreterMathExpression(std::string &expressionFunction):AbstractInterpreterFunction(expressionFunction){}
    AbstractNode* createExecutableFunction() override{
        return Solver::strToFun(functionName);
    }
};

#endif //PCSC_PROJECT_INTERPRETERMATHEXPRESSION_H
