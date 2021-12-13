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
    VariableNode(int index=0):index(index) {

    }
    /// Simply for variable x return the value of x
    
    double solve(int nbParameter, const double parameters[]) override{ 
        //return x;
        // index start at 0
        if (nbParameter<(index+1)) {
            std::string msg="Variable x" + index;
            msg+= " index="+index;
            msg+=" can not be found parameters size="+nbParameter;
            throw new ParserException(msg);
        }
        return parameters[index];
    }
};

#endif //PCSC_PROJECT_VARIABLENODE_H
