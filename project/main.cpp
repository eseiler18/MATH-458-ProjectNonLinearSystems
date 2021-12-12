#include <cstdlib>      // EXIT_FAILURE, etc
#include <string>
#include <iostream>
#include <fstream>
#include <dlfcn.h>      // dynamic library loading, dlopen() etc
#include <memory>
#include <unistd.h>
#include <chrono>
#include <thread>



using myP = double(*)(double);
int main(int argc , char* argv[]) {
    std::string cppfile="../../functions.cpp";
    const char *libfile="../../malib.so";
    // le résultat de la compile est dans log file ca revient à faire:
    // g++ - Wall -Wextra monfichier.cpp -o malib.so
    std::string logfile="../../runtimecode.log";
    std::string cmd = "g++ -Wall -Wextra " + cppfile + " -o " + libfile + " -O2 -shared -fPIC &> " + logfile;
    remove(libfile);
    system(cmd.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(400) );
    void * lib = nullptr;
    while (lib == nullptr){
        lib =dlopen(libfile, RTLD_LAZY);
    }
    if(lib) {
        myP  fn = (myP)(dlsym(lib, "fun"));
        if(fn) {
            std::cout << fn(1) << std::endl;

        }
        dlclose(lib);
    }
    else{
        throw std::invalid_argument("lib null");
    }

}