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
    void SetUp(std::string sfun,double value);
public:
    double calculated_value;
};

void Fixture_Interpreter::SetUp(std::string sfun, double value) {
    AbstractNode *f = Solver::strToFun(std::move(sfun));
    calculated_value =f->solve(value);
}
#endif //PCSC_PROJECT_FIXTUREINTERPRETER_H
