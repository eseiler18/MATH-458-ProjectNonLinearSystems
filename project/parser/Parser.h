//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#ifndef PCSC_PROJECT_PARSER_H
#define PCSC_PROJECT_PARSER_H

#include <iostream>
#include <list>
#include "TokenReader.h"

class TokenContainer;

class Parser {
public:
    Parser(std::string expression);
    TokenContainer* readTokens(TokenContainer* container=nullptr);


private:
    TokenReader tokenReader;
    static void checkTokenValidity(const std::list <AbstractToken*>& tokens);
    static int getPriority(AbstractToken* token);
    static std::list <AbstractToken*> managePriorityChildrenOpenLevel(const std::list <AbstractToken*>& tokens, int const level);
    static std::list <AbstractToken*> normalizeAndVerifyTokens(const std::list <AbstractToken*>& tokens);
    static  std::list <AbstractToken*> manageImplicitOperator(std::list <AbstractToken*> tokens);
};


#endif //PCSC_PROJECT_PARSER_H
