//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKEN_H
#define PCSC_PROJECT_TOKEN_H

#include "AbstractToken.h"
#include <iostream>
#include <utility>
class Token : public AbstractToken{
public:
    // Constructor
    Token(TokenType t,const std::string value): AbstractToken(t), valueStr(std::move(value)){}
    Token(TokenType t,const char value): AbstractToken(t){
        valueStr.push_back(value);
    }
    // Methods
    std::string toString() const override {return valueStr;}

    bool isSpaceBefore() const {
        return spaceBefore;
    }

    const std::string &getValueStr() const {
        return valueStr;
    }

    void setSpaceBefore(bool spaceBefore) {
        Token::spaceBefore = spaceBefore;
    }
private:
    std::string valueStr;
    bool spaceBefore;

};
#endif //PCSC_PROJECT_TOKEN_H
