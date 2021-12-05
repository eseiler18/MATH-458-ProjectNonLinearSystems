//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_OPERATORNODE_H
#define PCSC_PROJECT_OPERATORNODE_H
#include <utility>

#include "AbstractNode.h"
#include "TokenType.h"

class OperatorNode : public AbstractNode {
public:
    OperatorNode(TokenType t, AbstractNode* op1, AbstractNode* op2): tokenType(t), operand1(op1), operand2(op2){}
    ~OperatorNode(){delete operand1; delete operand2;}
    double solve(double x) override;
private:
    TokenType tokenType;
    AbstractNode *operand1;
    AbstractNode *operand2;
};


#endif //PCSC_PROJECT_OPERATORNODE_H
