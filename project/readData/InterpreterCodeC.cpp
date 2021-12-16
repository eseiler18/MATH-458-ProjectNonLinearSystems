//
// Created by eseiler@INTRANET.EPFL.CH on 16.12.21.
//

#include "InterpreterCodeC.h"

AbstractNode *InterpreterCodeC::createExecutableFunction() {
    // path to external file cpp
    std::string cppFile=externalFile;
    //path to library file
    const char *libFile="/tmp/malib.so";
    //path to logfile
    std::string logfile="/tmp/runtimecode.log";
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
        myP fn = (myP)(dlsym(lib, functionName.c_str()));
        if(fn) {
            return new ExternalFunctionNode(fn);
        }
        else {
            throw std::invalid_argument("The function " + functionName + " isn't in the file " + externalFile);
        }
    }
    else{
        std::string libraryFile(libFile);
        throw std::invalid_argument("The library " + libraryFile + " doesn't exist");
    }

}
