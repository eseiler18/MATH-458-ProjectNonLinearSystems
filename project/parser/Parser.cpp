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
        // read the next character of the expression and create the token
        currentToken = tokenReader.readNextToken();
        if(currentToken == nullptr){break; } // end of the expression get out of the while  loop
        if (currentToken->getTokenType() == TokenType::CLOSE_PAR){
            if (container == nullptr){
                // try to close container but container doesn't exist (container by default to nullptr)
                throw std::invalid_argument("Illegal close parenthesis ')' reach without any open parenthesis");
            }
            break;
        }
        if  (currentToken->getTokenType() == TokenType::OPEN_PAR){
            // read open parenthesis create container and read tokens until close parenthesis
            TokenContainer* subContainer = new TokenContainer();
            readTokens(subContainer);
            if(subContainer->getChildren().empty()){
                // empty parenthesis
                delete subContainer;
            }
            else{
                // add content of parenthesis in the token list
                tokens.push_back(subContainer);
            }
        }
        else{
            // add token to the token list
            tokens.push_back(currentToken);
        }
    }
    if(!tokens.empty()){
        // manage implicit operator, verify tokens validity and manage priority operations
        tokens = normalizeAndVerifyTokens(tokens);
        if(container == nullptr){
            // create the output container
            container = new TokenContainer;
        }
        else if(currentToken == nullptr || currentToken->getTokenType() != TokenType::CLOSE_PAR){
            // case when container is open with ( but not close
            throw std::invalid_argument( "Illegal open parenthesis without no close parenthesis ')'");
        }
        for(AbstractToken *t : tokens){
            // add tokens in the container
            container->addToken(t);
        }
    }
    return container;
}


std::list<AbstractToken *> Parser::manageImplicitOperator(std::list<AbstractToken *> tokens) {
    if(tokens.empty()){ return tokens; }
    AbstractToken* lastToken = nullptr;
    std::list <AbstractToken*> resultTokens;
    auto it = tokens.begin();
    // iterate on tokens of the expression
    for(int i=0; i<tokens.size(); i++){
        AbstractToken* token = *it;
        // case when expression start with + or - and an implicit 0 like -x -> 0-x
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
        // case when number is followed by variables like 4x -> 4*x
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


void Parser::checkTokenValidity(const std::list <AbstractToken *>& tokens) {
    if(tokens.empty()){ return;}
    AbstractToken* previousToken = nullptr;
    // iterate on all tokens to verify validity
    for (AbstractToken* token : tokens){
        // check if expression start with operator * or / (+ and - manage in implicit operator method)
        if(previousToken == nullptr){
            if(token->isOperator()){
                std::string message("Operator: " + token->toString() + " without first operand.");
                throw std::invalid_argument(message);
            }
        }
        // invalid case when operator is followed by another like +-, *-...
        else if(token->isOperator() && previousToken->isOperator()){
            std::string message("Operator: " + previousToken->toString() +
            " can not be followed by operator: " + token->toString());
            throw std::invalid_argument(message);
        }
        // invalid case when unary token is followed by another like xx, x2 (2x manage in implicit operator method)
        else if (token->isUnary() && previousToken->isUnary()){
            std::string message(previousToken->toString() + " can't be followed by " +
            token->toString() + " without operator.");
            throw std::invalid_argument(message);
        }
        previousToken = token;
    }
    // invalid case when operator finish the expression
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
Parser::managePriorityChildrenOpenLevel(const std::list<AbstractToken *> &tokens, const int level) {
    TokenContainer* currentPriorityContainer = nullptr;
    std::list<AbstractToken*> newTokens;
    // iterate on token in tokens
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
    // manage implicit operator
    newTokens = manageImplicitOperator(tokens);
    // verify validity
    checkTokenValidity(newTokens);
    //manage priority for POW
    newTokens = managePriorityChildrenOpenLevel(newTokens, 2);
    //manage priority for MUL and DIV
    newTokens = managePriorityChildrenOpenLevel(newTokens, 1);
    return newTokens;
}


