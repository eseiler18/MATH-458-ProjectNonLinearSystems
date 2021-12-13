//
// Created by eseiler@INTRANET.EPFL.CH on 10.12.21.
//

#ifndef PCSC_PROJECT_EXCEPTIONITERATE_H
#define PCSC_PROJECT_EXCEPTIONITERATE_H

#include <string>

class ExceptionIterate{
public:
    ExceptionIterate(std::string &s):message(s){}
    void what() const{
        std::cout << message << std::endl;
    }

private:
    std::string message;

};

#endif //PCSC_PROJECT_EXCEPTIONITERATE_H
