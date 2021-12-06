//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#ifndef PCSC_PROJECT_SOLVER_H
#define PCSC_PROJECT_SOLVER_H

#include "Builder.h"
#include "Parser.h"

class Solver{
public:
    static AbstractNode* strToFun(std::string expression){
        Parser parser(expression);
        TokenContainer *tokenExpression = parser.readTokens();
        Builder builder(*tokenExpression);
        AbstractNode* executableFunction = builder.build();
        return  executableFunction;
    }
    static std::string interpreterVision(std::string expression){
        Parser parser(expression);
        TokenContainer *tokenExpression = parser.readTokens();
        return tokenExpression->toString();
    }
private:
};

#endif //PCSC_PROJECT_SOLVER_H
