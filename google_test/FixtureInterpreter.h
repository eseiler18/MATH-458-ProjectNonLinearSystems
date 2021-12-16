//
// Created by lleguill on 14.12.21.
//

#ifndef PCSC_PROJECT_FIXTUREINTERPRETER_H
#define PCSC_PROJECT_FIXTUREINTERPRETER_H

#include <utility>

/**
 * Fixture class for interpreter Test
 */
class Fixture_Interpreter : public testing::Test{
protected :
    /// One Variable Case
    void SetUp(std::string sfun,double value,bool expectedError=false);
    /// Multi Variable Case
    void SetUp(std::string sfun,double x[] ,int nbVariables,bool expectedError=false);
public:
    double calculated_value;
    int error_valid =0;
};

// The one variable Case call the Multi Variable case by setting nbVariable =1
void Fixture_Interpreter::SetUp(std::string sfun, double value,bool expectedError) {
    SetUp(std::move(sfun),&value,1,expectedError);
}

void Fixture_Interpreter::SetUp(std::string sfun, double x[], int nbVariables, bool expectedError) {
    error_valid = 0; // Setup for the case we make multiple SetUp in the Same Test
    try {
        AbstractNode *f = Solver::strToFun(std::move(sfun));
        calculated_value = f->solve(nbVariables, x);
    } catch (ParserException(&e)) {
        // If we expected error and we catch the error, The error_valid parameter is set to 1
        if (expectedError) {
            error_valid = 1;
        }
        //In the Other Case, he error_valid parameter stay 0, and the Google Test will fail.
    }
}

#endif //PCSC_PROJECT_FIXTUREINTERPRETER_H
