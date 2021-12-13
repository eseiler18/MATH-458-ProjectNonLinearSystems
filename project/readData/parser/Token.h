//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKEN_H
#define PCSC_PROJECT_TOKEN_H

#include "AbstractToken.h"
#include <iostream>
#include <utility>
/**
 * Token class which represent a syntactic element (character) of the mathematics equation
 * Child of Abstract token
 */
class Token : public AbstractToken{
public:
    /// Constructor with string
    Token(TokenType t,const std::string& value): AbstractToken(t), valueStr(value){}
    /// Constructor with char
    Token(TokenType t,const char value): AbstractToken(t){
        valueStr.push_back(value);
    }
    /// getter of spaceBefore
    bool isSpaceBefore() const {
        return spaceBefore;
    }
    /// setter of space before
    void setSpaceBefore(bool space) {
        Token::spaceBefore = space;
    }
    /// getter of valueStr
    const std::string &getValueStr() const {
        return valueStr;
    }
    /// to string method for visualization and debugging
    std::string toString() const override {
        return valueStr;
    }
private:
    std::string valueStr;
    bool spaceBefore;
};
#endif //PCSC_PROJECT_TOKEN_H
