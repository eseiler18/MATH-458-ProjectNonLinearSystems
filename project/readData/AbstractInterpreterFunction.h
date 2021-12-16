//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H
#define PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H

#include <string>
#include <utility>
#include "parser/AbstractNode.h"

class AbstractInterpreterFunction{
protected:
    std::string functionName;
public:
    AbstractInterpreterFunction(std::string &fun):functionName(fun){}
    virtual AbstractNode* createExecutableFunction()=0;
};
#endif //PCSC_PROJECT_ABSTRACTINTERPRETERFUNCTION_H
