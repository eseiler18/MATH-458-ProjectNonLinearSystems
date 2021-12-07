//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include <math.h>
#include <iostream>
#include "OperatorNode.h"

double OperatorNode::solve(double x) {
    if (tokenType == TokenType::ADD){
        return operand1->solve(x) + operand2->solve(x);
    }
    if (tokenType == TokenType::SUB){
        return operand1->solve(x) - operand2->solve(x);
    }
    if (tokenType == TokenType::MUL){
        return operand1->solve(x) * operand2->solve(x);
    }
    if (tokenType == TokenType::DIV){
        if (operand2->solve(x) == 0){
            throw std::invalid_argument("Error divide by zero");
        }
        return operand1->solve(x) / operand2->solve(x);
    }
    if (tokenType == TokenType::POW){
        return pow(operand1->solve(x), operand2->solve(x));
    }
}
