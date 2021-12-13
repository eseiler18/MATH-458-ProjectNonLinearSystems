//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENCONTAINER_H
#define PCSC_PROJECT_TOKENCONTAINER_H

#include "AbstractToken.h"
#include "Token.h"
/**
 * Token container class representing a "group" of tokens use to manage parenthesis and priority cases
 * A token container contain tokens stored in the children parameter
 */
class TokenContainer : public AbstractToken{
public:
    /// constructor with type token container
    TokenContainer(): AbstractToken(TokenType::CONTAINER){}
    /// destructor to prevent memory leak
    ~TokenContainer() override{
        for(AbstractToken* child: children){
            delete child;
        }
        children.clear();
    }
    /// add a token to the container
    void addToken(AbstractToken* token) {
        children.push_back(token);
    }
    /// to string method for visualization and debug
    std::string toString() const override{
        std::string result("(");
        for(AbstractToken* child : children){
            result.append(child->toString());
            result.append(" ");
        }
        result.append(")");
        return result;
    }
};


#endif //PCSC_PROJECT_TOKENCONTAINER_H
