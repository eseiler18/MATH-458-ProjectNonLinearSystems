//
// Created by eseiler@INTRANET.EPFL.CH on 04.12.21.
//

#ifndef PCSC_PROJECT_SOLVER_H
#define PCSC_PROJECT_SOLVER_H

#include "Builder.h"
#include "Parser.h"

/**
 * Solver class which process from a string expression the construction of the executable binary tree.
 * First read all characters of the expression and create adequate tokens.
 * Then build the executable tree.
 */
class Solver{
public:
    /// main methods which return the root of the tree
    /// access value of the function with the solve method of Abstract node for every value of x
    static AbstractNode* strToFun(std::string expression){
        Parser parser(expression);
        // create the token container which contain tokens corresponding to characters of the expression
        TokenContainer *tokenExpression = parser.readTokens();
        Builder builder(*tokenExpression);
        // build the executable tree and return the root
        AbstractNode* executableFunction = builder.build();
        return  executableFunction;
    }
    /// to string methods for visualization and debug
    static std::string interpreterVision(std::string expression){
        Parser parser(expression);
        TokenContainer *tokenExpression = parser.readTokens();
        std::string value=tokenExpression->toString();
        delete tokenExpression;
        return value;
    }
private:
};

#endif //PCSC_PROJECT_SOLVER_H
