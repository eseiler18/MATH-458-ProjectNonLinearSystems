//
// Created by eseiler@INTRANET.EPFL.CH on 12.12.21.
//

#ifndef PCSC_PROJECT_TOKENFUNCTION_H
#define PCSC_PROJECT_TOKENFUNCTION_H

#include "TokenContainer.h"
#include "Token.h"
/**
 * Token Function class representing a "function" associatd to a container. The function will be applied for container children
 * A token function must contain one nested container 
 */
class TokenFunction : public Token{
private:
    TokenContainer* nestedContainer;
public:
    /// constructor with type token function
    TokenFunction(const std::string& value): Token(TokenType::FUNCTION, value), nestedContainer(nullptr){}
    /// destructor to prevent memory leak
    ~TokenFunction() override{
        if (nestedContainer) {
            delete nestedContainer;
        }
        nestedContainer=nullptr;

    }
    /// set the  token container on which the function is applied
    void setNestedContainer(TokenContainer* container) {
        nestedContainer=container;
    }

    TokenContainer* getNestedContainer() const {return nestedContainer;}
    /// to string method for visualization and debug
    std::string toString() const override{
        std::string result(getValueStr()+"(");
        if (nestedContainer) {
            result+=nestedContainer->toString();
        }
        result.append(")");
        return result;
    }
};


#endif //PCSC_PROJECT_TOKENFUNCTION_H
