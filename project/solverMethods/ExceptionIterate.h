//
// Created by eseiler@INTRANET.EPFL.CH on 10.12.21.
//

#ifndef PCSC_PROJECT_EXCEPTIONITERATE_H
#define PCSC_PROJECT_EXCEPTIONITERATE_H

#include <string>
#include <stdexcept>


class ExceptionIterate : public std::logic_error{
public:
    ExceptionIterate(const std::string &s):logic_error(s){}
};



#endif //PCSC_PROJECT_EXCEPTIONITERATE_H
