//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_OPERATORNODE_H
#define PCSC_PROJECT_OPERATORNODE_H
#include <utility>

#include "AbstractNode.h"
#include "TokenType.h"
/**
 * This class is a binary operator node of the binary tree which represent function.
 * The operator must have a type (+,-,*..) and two operands
 */
class OperatorNode : public AbstractNode {
public:
    OperatorNode(TokenType t, AbstractNode* op1, AbstractNode* op2): tokenType(t), operand1(op1), operand2(op2){}
    ~OperatorNode() override{delete operand1; delete operand2;}
    /// return the value of operand1 'operator type' operand2
    double solve(double x) override;
private:
    TokenType tokenType;
    AbstractNode *operand1;
    AbstractNode *operand2;
};


#endif //PCSC_PROJECT_OPERATORNODE_H
