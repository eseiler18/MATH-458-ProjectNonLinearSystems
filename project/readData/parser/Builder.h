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

/**
 * The builder class build the executable binary tree from a token container
 * The root of the tree will be used to get value of the function
 */
class Builder {
public:
    /// constructor with a tokenContainer
    Builder(const TokenContainer& tokenContainer):tokensOfEquation(tokenContainer){}
    /// main method which build the tree and return the root node of it
    AbstractNode * build();
private:
    TokenContainer tokensOfEquation;
    /// build the executable tree from a list of token
    static AbstractNode* buildTokens(std::list <AbstractToken*> tokens);
    /// build an operator node
    static OperatorNode* buildOperator(const std::list <AbstractNode*>& operands, AbstractToken* _operator);
    /// build none operator node and manage token container
    static AbstractNode* buildToken(AbstractToken* token);
    /// build an unitary node (number and variable)
    static AbstractNode* buildUnitary(AbstractToken *unitaryNode);
};


#endif //PCSC_PROJECT_BUILDER_H
