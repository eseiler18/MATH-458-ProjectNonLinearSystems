//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#include "Builder.h"

OperatorNode * Builder::buildOperator(const std::list<AbstractNode *>& operands, AbstractToken *_operator) {
    if(operands.size() !=2 ){
        throw std::invalid_argument("Illegal operands combination with " + _operator->toString());
    }
    return new OperatorNode(_operator->getTokenType(), operands.front(), operands.back());
}

AbstractNode *Builder::buildUnitary(AbstractToken *unitaryToken){
    if(unitaryToken->getTokenType() == TokenType::NUMBER){
        const std::string& numberStr = ((Token*)unitaryToken)->getValueStr();
        double number = std::stod(numberStr);
        return new NumberNode(number);
    }
    if(unitaryToken->getTokenType() == TokenType::VAR){
        return new VariableNode();
    }
    if(unitaryToken->getTokenType() == TokenType::CONTAINER) {
        return buildTokens(unitaryToken->getChildren());
    }
    else{
        throw std::invalid_argument("Invalid token type for buildUnitary");
    }
}

AbstractNode *Builder::buildTokens(std::list<AbstractToken *> tokens) {
    if(tokens.empty()){return nullptr; }
    if(tokens.size() == 1){
        return buildUnitary(tokens.front());
    }
    std::list <AbstractNode*> operands;
    AbstractToken* _operator = nullptr;
    for(AbstractToken* currentToken : tokens){
        if(currentToken->isOperator()) {
            if (_operator == nullptr) {
                _operator = currentToken;
            } else {
                OperatorNode *subExpression = buildOperator(operands, _operator);
                operands.clear();
                operands.push_back(subExpression);
                _operator = currentToken;
            }
        }
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
    if(token->getTokenType() == TokenType::CONTAINER){
        return buildTokens(token->getChildren());
    }
    else{
        return buildUnitary(token);
    }
}

AbstractNode * Builder::build() {
    return buildTokens(tokensOfEquation.getChildren());
}
