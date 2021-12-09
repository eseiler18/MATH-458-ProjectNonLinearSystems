//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENCONTAINER_H
#define PCSC_PROJECT_TOKENCONTAINER_H

#include "AbstractToken.h"
#include "Token.h"

class TokenContainer : public AbstractToken{
public:
    TokenContainer(): AbstractToken(TokenType::CONTAINER){}
    ~TokenContainer() override{
        for(AbstractToken* child: children){
            delete child;
        }
        children.clear();
    }

    std::string toString() const override{
        std::string result("(");
        for(AbstractToken* child : children){
            result.append(child->toString());
            result.append(" ");
        }
        result.append(")");
        return result;
    }
    std::list<AbstractToken *> &getChildren()  override {
        return children;
    }
    void addToken(AbstractToken* token) {
        children.push_back(token);
    }
private:
    std::list <AbstractToken*> children;
};


#endif //PCSC_PROJECT_TOKENCONTAINER_H
