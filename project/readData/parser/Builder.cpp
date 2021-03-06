//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#include "Builder.h"
#include "FunctionNode.h"
#include "TokenFunction.h"

OperatorNode * Builder::buildOperator(const std::list<AbstractNode *>& operands, AbstractToken *_operator) {
    // verify that there are two operands
    if(operands.size() !=2 ){
        throw ParserException("Illegal operands combination with " + _operator->toString());
    }
    // build operator node of the token type
    return new OperatorNode(_operator->getTokenType(), operands.front(), operands.back());
}

AbstractNode *Builder::buildUnitary(AbstractToken *unitaryToken){
    // build number node if token type is number
    if(unitaryToken->getTokenType() == TokenType::NUMBER){
        const std::string& numberStr = ((Token*)unitaryToken)->getValueStr();
        double number = std::stod(numberStr);
        return new NumberNode(number);
    }
    // build variable node if token type is variable
    if(unitaryToken->getTokenType() == TokenType::VAR){
        std::string variableName = ((Token*)unitaryToken)->getValueStr();
        if (variableName.length()>1) {
            // get index
            return new VariableNode(std::stoi(variableName.substr(1)));

        }
        return new VariableNode();
    }
    // build the subtree of the content of the token container
    if(unitaryToken->getTokenType() == TokenType::CONTAINER) {
        return buildTokens(unitaryToken->getChildren());
    }
    if(unitaryToken->getTokenType() == TokenType::FUNCTION) {
        // build function  and manage his token container
        TokenFunction* tokenfunction=dynamic_cast<TokenFunction*> (unitaryToken);
        return new FunctionNode(tokenfunction->getValueStr(), buildToken(tokenfunction->getNestedContainer()));
    }
    // invalid case
    else{
        throw ParserException("Builder.buildUnitary - Invalid token type "+ tokenTypeToString(unitaryToken->getTokenType()));
    }
}

AbstractNode *Builder::buildTokens(std::list<AbstractToken *> tokens) {
    if(tokens.empty()){return nullptr; }
    // case when there is only one token
    if(tokens.size() == 1){
        return buildUnitary(tokens.front());
    }
    std::list <AbstractNode*> operands;
    AbstractToken* _operator = nullptr;
    // iterate on token in tokens
    for(AbstractToken* currentToken : tokens){
        // operator case
        if(currentToken->isOperator()) {
            // first operator
            if (_operator == nullptr) {
                _operator = currentToken;
            }
            // when read another operator node
            else {
                // build the previous operator node
                OperatorNode *subExpression = buildOperator(operands, _operator);
                operands.clear();
                // add operand for the next operator
                operands.push_back(subExpression);
                _operator = currentToken;
            }
        }
        // build operands for operators
        else{
            operands.push_back(buildToken(currentToken));
        }
    }
    if(_operator != nullptr){
        return buildOperator(operands, _operator);
    }
    return operands.front();
}

AbstractNode *Builder::buildToken(AbstractToken *token) {
    // manage token container (apply build the tree of children)
    if(token->getTokenType() == TokenType::CONTAINER){
        return buildTokens(token->getChildren());
    }
    else{
        return buildUnitary(token);
    }
}

AbstractNode * Builder::build() {
    // build executable tree of the tokens
    return buildTokens(tokensOfEquation.getChildren());
}
