//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENCONTAINER_H
#define PCSC_PROJECT_TOKENCONTAINER_H

#include <list>
#include "AbstractToken.h"
#include "Token.h"
using namespace std;

class TokenContainer : public AbstractToken{
public:
    TokenContainer(): AbstractToken(TokenType::CONTAINER){}
    ~TokenContainer() override{
        for(AbstractToken* child: children ){
            delete child;
        }
        children.clear();
    }

    string toString() const override{
        string result("(");
        for(AbstractToken* child : children){
            result.append(child->toString());
            result.append(" ");
        }
        result.append(")");
        return result;
    }

    const list<AbstractToken *> &getChildren() const override {
        return children;
    }

    void addToken(AbstractToken* token) {
        children.push_back(token);
    }

private:
    list <AbstractToken*> children;
};


#endif //PCSC_PROJECT_TOKENCONTAINER_H
