//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_ABSTRACTTOKEN_H
#define PCSC_PROJECT_ABSTRACTTOKEN_H

#include <string>
#include <list>
#include "TokenType.h"

/**
 * Token common class representing a syntactic element of the operation
 * A token has a token type in parameter (see TokenType.h list all token type
 */
class AbstractToken{
protected:
    AbstractToken(TokenType t):tokenType(t){}
    TokenType tokenType;

public:
    virtual ~AbstractToken()= default;
    /// getter of the token type
    TokenType getTokenType() const {
        return tokenType;
    }
    /// method to know if token is unary (number or variable)
    bool isUnary() const{
        if (tokenType == TokenType::NUMBER || tokenType == TokenType::VAR){ return true;}
        else{ return false;}
    }
    /// method to know if token is an operator
    bool isOperator() const{
        if (tokenType == TokenType::ADD || tokenType == TokenType::SUB || tokenType == TokenType::MUL ||
        tokenType == TokenType::DIV || tokenType==TokenType::POW) {return true;}
        else{ return false;}
    }
    /// to string method to visualize and help debug
    virtual std::string toString() const = 0;
    /// pure virtual method to get children of TokenContainer
    virtual const std::list<AbstractToken *> &getChildren() {}
};
#endif //PCSC_PROJECT_ABSTRACTTOKEN_H
