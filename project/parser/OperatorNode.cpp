//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include <math.h>
#include <iostream>
#include "OperatorNode.h"

double OperatorNode::solve(double x) {
    // addition case
    if (tokenType == TokenType::ADD){
        return operand1->solve(x) + operand2->solve(x);
    }
    //subtraction case
    if (tokenType == TokenType::SUB){
        return operand1->solve(x) - operand2->solve(x);
    }
    // multiplication case
    if (tokenType == TokenType::MUL){
        return operand1->solve(x) * operand2->solve(x);
    }
    // division case
    if (tokenType == TokenType::DIV){
        // verify division by 0
        if (operand2->solve(x) == 0){
            throw std::invalid_argument("Error divide by zero");
        }
        return operand1->solve(x) / operand2->solve(x);
    }
    // power case
    if (tokenType == TokenType::POW){
        return pow(operand1->solve(x), operand2->solve(x));
    }
}
