//
// Created by eseiler@INTRANET.EPFL.CH on 13.12.21.
//

#ifndef PCSC_PROJECT_INTERPRETERINPUTFUNCTION_H
#define PCSC_PROJECT_INTERPRETERINPUTFUNCTION_H

#include "parser/Builder.h"
#include "parser/Parser.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "parser/ExtrernalFunctionNode.h"

/**
 * Interpreter of different input for the function.
 * Transform the input function in an Abstract Node use to access value of the function.
 * 2 type of input for the function, string expression or c++ code.
 */
class InterpreterInputFunction {
public:
    /// interpreter from string expression to an executable abstract node
    static AbstractNode* strToFun(std::string& expression);
    /// interpreter from code c++ nameFun in a file (nameFile) to an executable abstract node
    static AbstractNode* functionExternalCFile(const std::string& nameFile, const std::string& nameFun);
};


#endif //PCSC_PROJECT_INTERPRETERINPUTFUNCTION_H
