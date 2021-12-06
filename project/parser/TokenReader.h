//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENREADER_H
#define PCSC_PROJECT_TOKENREADER_H

#include <iostream>
class Token;
class AbstractToken;

/**
 * Manage the expression token read the expression and transform each character in an accurate token
 */
class TokenReader {
private:
    int position;
    std::string expression;
    Token* createNumberToken();

public:
    TokenReader(std::string expression);
    AbstractToken* readNextToken();
};


#endif //PCSC_PROJECT_TOKENREADER_H
