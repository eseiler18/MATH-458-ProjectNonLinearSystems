//
// Created by eseiler@INTRANET.EPFL.CH on 13.12.21.
//

#ifndef PCSC_PROJECT_PARSEREXCEPTION_H
#define PCSC_PROJECT_PARSEREXCEPTION_H

#include <string>
#include <stdexcept>

/// Exception raised by parser/build phase
class ParserException : public std::logic_error {
public:
    ParserException(const std::string &s):logic_error(s){}

};

#endif //PCSC_PROJECT_PARSEREXCEPTION_H
