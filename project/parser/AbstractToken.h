//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTTOKEN_H
#define PCSC_PROJECT_ABSTRACTTOKEN_H

#include <iostream>
#include <list>
#include "TokenType.h"

/**
 * Token common class representing a syntacic element of the operation
 */
class AbstractToken{
protected:
    AbstractToken(TokenType t):tokenType(t){}
    TokenType tokenType;

public:
    virtual ~AbstractToken()= default;
    // Methods
    bool isUnary() const{
        if (tokenType == TokenType::NUMBER || tokenType == TokenType::VAR){ return true;}
        else{ return false;}
    }

    TokenType getTokenType() const {
        return tokenType;
    }

    bool isOperator() const{
        if (tokenType == TokenType::ADD || tokenType == TokenType::SUB || tokenType == TokenType::MUL ||
        tokenType == TokenType::DIV || tokenType==TokenType::POW) {return true;}
        else{ return false;}
    }

    virtual std::string toString() const = 0;
    virtual const std::list<AbstractToken *> &getChildren() const{}


};
#endif //PCSC_PROJECT_ABSTRACTTOKEN_H
