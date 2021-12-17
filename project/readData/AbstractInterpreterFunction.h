//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H
#define PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H

#include <string>
#include <utility>
#include "parser/AbstractNode.h"

/**
 * Common interface of input function interpreter.
 * Actually to type of input math expression and c++ code
 */
class AbstractInterpreterFunction{
protected:
    std::string functionName;
public:
    AbstractInterpreterFunction(std::string &fun):functionName(fun){}
    /// virtual pure method which create the executable function
    virtual AbstractNode* createExecutableFunction()=0;
};
#endif //PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H
