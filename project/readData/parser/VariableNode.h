//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_VARIABLENODE_H
#define PCSC_PROJECT_VARIABLENODE_H
#include <vector>
#include <string>
/**
 * This class is a variable node of the binary tree which represent function
 */
class VariableNode : public AbstractNode{
private:
    int index;
public:
    /// constructor with zero by default when there is one variable
    VariableNode(int index=0):index(index) {}
    /// Simply for variable x return the value of x
    double solve(int nbParameter, const double parameters[]) override{
        // index start at 0
        if (nbParameter<(index+1)) {
            std::string msg="Variable x" + std::to_string(index);
            msg+= " index="+std::to_string(index);
            msg+=" can not be found parameters size="+std::to_string(nbParameter);
            throw ParserException(msg);
        }
        return parameters[index];
    }
};

#endif //PCSC_PROJECT_VARIABLENODE_H
