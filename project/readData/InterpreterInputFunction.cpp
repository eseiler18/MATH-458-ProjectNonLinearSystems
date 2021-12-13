//
// Created by eseiler@INTRANET.EPFL.CH on 13.12.21.
//

#include "InterpreterInputFunction.h"
#include <chrono>
#include <thread>

AbstractNode *InterpreterInputFunction::strToFun(std::string &expression) {
    Parser parser(expression);
    // create the token container which contain tokens corresponding to characters of the expression
    TokenContainer *tokenExpression = parser.readTokens();
    Builder builder(*tokenExpression);
    // build the executable tree and return the root
    AbstractNode *executableFunction = builder.build();
    return executableFunction;
}

AbstractNode *InterpreterInputFunction::functionExternalCFile(const std::string &nameFile, const std::string &nameFun){
    // path to external file cpp
    std::string cppFile="../../" + nameFile;
    //path to library file
    const char *libFile="../../project/readData/myLib/malib.so";
    //path to logfile
    std::string logfile="../../project/readData/myLib/runtimecode.log";
    // command to compile the cpp file
    std::string cmd = "g++ -Wall -Wextra " + cppFile + " -o " + libFile + " -O2 -shared -fPIC &> " + logfile;
    remove(libFile);
    // compile
    int a = system(cmd.c_str());
    if (a!=0) {
        std::ifstream input_file(logfile);
        std::string message((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        throw std::invalid_argument(message);
    }
    void * lib = nullptr;
    // loop to open the lib because compilation can't take a bit time
    for (int i=0;i<50;i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        lib =dlopen(libFile, RTLD_LAZY);
        if (lib != nullptr){ break;}
    }
    if(lib) {
        // create the pointer on the function in the file
        myP fn = (myP)(dlsym(lib, nameFun.c_str()));
        if(fn) {
            return new ExternalFunctionNode(fn);
        }
        else {
            throw std::invalid_argument("The function " + nameFun + " isn't in the file " + nameFile);
        }
    }
    else{
        std::string libraryFile(libFile);
        throw std::invalid_argument("The library " + libraryFile + " doesn't exist");
    }
}
