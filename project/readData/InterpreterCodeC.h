//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#ifndef PCSC_PROJECT_INTERPRETERCODEC_H
#define PCSC_PROJECT_INTERPRETERCODEC_H

#include <sstream>
#include <fstream>
#include <cstdlib>
#include <dlfcn.h>
#include <chrono>
#include <thread>
#include "AbstractInterpreterFunction.h"
#include "parser/ExtrernalFunctionNode.h"

/**
 * Child of AbstractInterpreterFunction for the c++ code of the function as input.
 * The externalFile parameter is the path of the external cpp file where there is the function.
 * The functionName parameter is the name of the function in the external file
 */
class InterpreterCodeC : public AbstractInterpreterFunction{
private:
    std::string externalFile;
public:
    InterpreterCodeC(std::string &file, std::string &nameFun):AbstractInterpreterFunction(nameFun),externalFile(file){}
    /// create the executable function with a pointer on functionName in externalFile by dynamic compilation
    AbstractNode* createExecutableFunction() override;
};


#endif //PCSC_PROJECT_INTERPRETERCODEC_H
