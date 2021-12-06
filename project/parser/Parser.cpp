//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#include <list>
#include "Parser.h"
#include "Token.h"
#include "TokenContainer.h"

Parser::Parser(std::string expression): tokenReader(expression) {}

TokenContainer *Parser::readTokens(TokenContainer *container) {
    std::list <AbstractToken*> tokens;
    AbstractToken* currentToken;
    while (true){
        currentToken = tokenReader.readNextToken();
        if(currentToken == nullptr){break; }
        if (currentToken->getTokenType() == TokenType::CLOSE_PAR){
            if (container == nullptr){
                throw std::invalid_argument("Illegal close parenthesis ')' reach without any open parenthesis");
            }
            break;
        }
        if  (currentToken->getTokenType() == TokenType::OPEN_PAR){
            TokenContainer* subContainer = new TokenContainer();
            readTokens(subContainer);
            if(subContainer->getChildren().empty()){
                delete subContainer;
            }
            else{
                tokens.push_back(subContainer);
            }
        }
        else{
            tokens.push_back(currentToken);
        }
    }
    if(!tokens.empty()){
        tokens = normalizeAndVerifyTokens(tokens);
        if(container == nullptr){
            container = new TokenContainer;
        }
        else if(currentToken == nullptr || currentToken->getTokenType() != TokenType::CLOSE_PAR){
            throw std::invalid_argument( "Illegal open parenthesis without no close parenthesis ')'");
        }
        for(AbstractToken *t : tokens){
            container->addToken(t);
        }
    }
    return container;
}


void Parser::checkTokenValidity(const std::list <AbstractToken *>& tokens) {
    if(tokens.empty()){ return;}
    AbstractToken* previousToken = nullptr;
    for (AbstractToken* token : tokens){
        if(previousToken == nullptr){
            if(token->isOperator()){
                std::string message("Operator: " + token->toString() + " without first operand.");
                throw std::invalid_argument(message);
            }
        }
        else if(token->isOperator() && previousToken->isOperator()){
            std::string message("Operator: " + previousToken->toString() +
            " can not be followed by operator: " + token->toString());
            throw std::invalid_argument(message);
        }
        else if (token->isUnary() && previousToken->isUnary()){
            std::string message(previousToken->toString() + " can't be followed by " +
            token->toString() + " without operator.");
            throw std::invalid_argument(message);
        }
        previousToken = token;
    }
    if(previousToken->isOperator()){
        std::string message("Operator " + previousToken->toString() + " can't end the expression.");
        throw std::invalid_argument(message);
    }
}


int Parser::getPriority(AbstractToken *token) {
    if (token->getTokenType() == TokenType::ADD || token->getTokenType() == TokenType::SUB) { return 0; }
    if (token->getTokenType() == TokenType::MUL || token->getTokenType() == TokenType::DIV) { return 1; }
    if (token->getTokenType() == TokenType::POW){ return 2; }
    else { return -1; }
}

std::list<AbstractToken *>
Parser::managePriorityChildrenOpenLevel(const list<AbstractToken *> &tokens, const int level) {
    TokenContainer* currentPriorityContainer = nullptr;
    std::list<AbstractToken*> newTokens;
    for(AbstractToken* token : tokens){
        if(getPriority(token) >= level){
            if(currentPriorityContainer == nullptr){
                currentPriorityContainer = new TokenContainer;
                AbstractToken* tokenAppend = newTokens.back();
                newTokens.pop_back();
                currentPriorityContainer->addToken(tokenAppend);
                newTokens.push_back(currentPriorityContainer);
            }
        }
        else if(getPriority(token) < level && getPriority(token) > -1){
            currentPriorityContainer = nullptr;
        }
        if(currentPriorityContainer != nullptr){
            currentPriorityContainer->addToken(token);
        }
        else{
            newTokens.push_back(token);
        }
    }
    return newTokens;
}


std::list <AbstractToken*> Parser::normalizeAndVerifyTokens(const std::list <AbstractToken*>& tokens){
    std::list <AbstractToken*> newTokens;
    newTokens = manageImplicitOperator(tokens);
    checkTokenValidity(newTokens);
    //create container for POW
    newTokens = managePriorityChildrenOpenLevel(newTokens, 2);
    //create container for MUL and DIV
    newTokens = managePriorityChildrenOpenLevel(newTokens, 1);
    return newTokens;
}

std::list<AbstractToken *> Parser::manageImplicitOperator(std::list<AbstractToken *> tokens) {
    if(tokens.empty()){ return tokens; }
    AbstractToken* lastToken = nullptr;
    std::list <AbstractToken*> resultTokens;
    auto it = tokens.begin();
    for(int i=0; i<tokens.size(); i++){
        AbstractToken* token = *it;
        if(lastToken == nullptr){
            if((token->getTokenType() == TokenType::ADD || token->getTokenType() == TokenType::SUB) && i < tokens.size()-1 ){
                it++;
                AbstractToken* nextToken = *it;
                it--;
                if(not((Token*)nextToken)->isSpaceBefore() && nextToken->getTokenType() == TokenType::NUMBER ||
                        nextToken->getTokenType() == TokenType::VAR){
                    resultTokens.push_back(new Token(TokenType::NUMBER, '0'));
                }
            }
        }
        else if(token->isUnary() && lastToken->isUnary()){
            if(not((Token*)lastToken)->isSpaceBefore() && (lastToken->getTokenType() == TokenType::NUMBER ||
                                                           token->getTokenType() == TokenType::VAR)){
                resultTokens.push_back(new Token(TokenType::MUL, '*'));
            }
        }
        lastToken = token;
        resultTokens.push_back(lastToken);
        it++;
    }
    return resultTokens;
}

