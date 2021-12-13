//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#ifndef PCSC_PROJECT_PARSER_H
#define PCSC_PROJECT_PARSER_H

#include <iostream>
#include <list>
#include "TokenReader.h"

class TokenContainer;
/**
 * Parser class managing the syntactic expression.
 * First read all the characters of the expression with the tokenReader class.
 * Then  manages implicit operator and verify tokens validity.
 * Finally manages operational priorities.
 */
class Parser {
public:
    /// constructor with the string expression of the equation
    Parser(std::string expression);
    /// main method transforming the string expression into valid tokens and add them in a token container
    TokenContainer* readTokens(TokenContainer* container=nullptr);
private:
    TokenReader tokenReader;
    /// manage implicits operations (4x=4*x, -x=0-x)
    static  std::list <AbstractToken*> manageImplicitOperator(const std::list <AbstractToken*>& tokens);
    /// verify that tokens are usable (no two operator in a row, variable follow by number..)
    static void checkTokenValidity(const std::list <AbstractToken*>& tokens);
    /// get priority of an operator token ( ^=2, */=1, -+=0)
    static int getPriority(const AbstractToken* token);
    /// manage operational priorities of a given level
    static std::list <AbstractToken*> managePriorityChildrenOpenLevel(const std::list <AbstractToken*>& tokens, int level);
    /// call all the verify and manage operator methods on tokens
    static std::list <AbstractToken*> normalizeAndVerifyTokens(const std::list <AbstractToken*>& tokens);
    // check if there is one TokenFunction follow by a Container. In this case associate them
    static std::list<AbstractToken *> manageTokenFunction(const std::list<AbstractToken *>& tokens);
 
};


#endif //PCSC_PROJECT_PARSER_H
