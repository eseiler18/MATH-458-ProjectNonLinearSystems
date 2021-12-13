//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENREADER_H
#define PCSC_PROJECT_TOKENREADER_H

#include <iostream>
class Token;
class AbstractToken;

/**
 * Token reader class managing the syntactic expression and transform a character in an accurate token.
 * The class read the string expression variable and the position variable give the current position in the expression.
 */
class TokenReader {
public:
    /// constructor with string expression, position set to -1
    TokenReader(std::string expression);
    /// read the next character at the position parameter and return the adequate token
    AbstractToken* readNextToken();
private:
    int position;
    std::string expression;
    /// create a token type number after reading a digit, verify case with several digit and decimal number
    Token* createNumberToken();
    /// create a token type function : must start with a-z or A-z
    Token* createFunctionToken();
};
#endif //PCSC_PROJECT_TOKENREADER_H
