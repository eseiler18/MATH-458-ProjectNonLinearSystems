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

class InterpreterCodeC : public AbstractInterpreterFunction{
private:
    std::string externalFile;
public:
    InterpreterCodeC(std::string &file, std::string &nameFun):AbstractInterpreterFunction(nameFun),externalFile(file){}

    AbstractNode* createExecutableFunction() override;
};


#endif //PCSC_PROJECT_INTERPRETERCODEC_H
