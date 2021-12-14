#include <utility>

//
// Created by lleguill on 14.12.21.
//

#ifndef PCSC_PROJECT_FIXTUREINTERPRETER_H
#define PCSC_PROJECT_FIXTUREINTERPRETER_H

/**
 * Fixture class for interpreter Test
 */
class Fixture_Interpreter : public testing::Test{
protected :
    void SetUp(std::string sfun,double value,bool expectedError=false);
public:
    double calculated_value;
    int error_valid =0;
};

void Fixture_Interpreter::SetUp(std::string sfun, double value,bool expectedError) {
    try {
        AbstractNode *f = Solver::strToFun(std::move(sfun));
        calculated_value = f->solve(value);
    }catch(ParserException(&e)){
        if (expectedError){
            error_valid=1;
        }
    }
}
#endif //PCSC_PROJECT_FIXTUREINTERPRETER_H
