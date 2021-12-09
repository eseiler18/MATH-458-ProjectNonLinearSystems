//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#ifndef PCSC_PROJECT_BUILDER_H
#define PCSC_PROJECT_BUILDER_H

#include <list>
#include "TokenContainer.h"
#include "NumberNode.h"
#include "VariableNode.h"
#include "OperatorNode.h"
#include "TokenType.h"

class Builder {
public:
    Builder(const TokenContainer& tokenContainer):tokensOfEquation(tokenContainer){}
    AbstractNode * build();


private:
    TokenContainer tokensOfEquation;
    static OperatorNode* buildOperator(const std::list <AbstractNode*>& operands, AbstractToken* _operator);
    static AbstractNode* buildUnitary(AbstractToken *unitaryNode);
    static AbstractNode* buildTokens(std::list <AbstractToken*> tokens);
    static AbstractNode* buildToken(AbstractToken* token);
};


#endif //PCSC_PROJECT_BUILDER_H
