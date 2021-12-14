//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include <math.h>
#include <iostream>
#include "OperatorNode.h"

double OperatorNode::solve(int nbParameters, const double parameters[]) {
    // addition case
    if (tokenType == TokenType::ADD){
        return operand1->solve(nbParameters, parameters) + operand2->solve(nbParameters, parameters);
    }
    //subtraction case
    if (tokenType == TokenType::SUB){
        return operand1->solve(nbParameters, parameters) - operand2->solve(nbParameters, parameters);
    }
    // multiplication case
    if (tokenType == TokenType::MUL){
        return operand1->solve(nbParameters, parameters) * operand2->solve(nbParameters, parameters);
    }
    // division case
    if (tokenType == TokenType::DIV){
        // verify division by 0
        if (operand2->solve(nbParameters, parameters) == 0){
            throw std::invalid_argument("Error divide by zero");
        }
        return operand1->solve(nbParameters, parameters) / operand2->solve(nbParameters, parameters);
    }
    // power case
    if (tokenType == TokenType::POW){
        return pow(operand1->solve(nbParameters, parameters), operand2->solve(nbParameters, parameters));
    }
    throw ParserException("OperatorNode Invalid operation type :" + tokenType);
}
