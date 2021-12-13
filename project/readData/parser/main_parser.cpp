//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include <iostream>
#include <math.h>
#include "Solver.h"

void testFunctionMultiVariables(const char* functionDefinition, int nbVariable, double x[], double expectedResult, bool expectedError=false){
    static int compteur = 1;
    try {
        std::cout<<compteur<<"- Test strFun: '" << functionDefinition<<"'";
        if (nbVariable>1) {
            for (int i=0;i<nbVariable;i++) {
                 std::cout<<" x"<<i<<"="<<x[i];
                
            }
        } else {
            std::cout<<" x="<<x;
        }
            std::cout<<std::endl;
        AbstractNode *node = Solver::strToFun(functionDefinition);
        double result = node->solve(nbVariable, x);
        if (abs(expectedResult - result)<0.00001) {
            std::cout<<"\tResult="<<result<<" -- PASSED\n";
        } else {
            std::cerr<<"\t"<<Solver::interpreterVision(functionDefinition)<<std::endl;
            std::cerr<<"\tExpected result="<<expectedResult<<" - result="<<result<<" -- ERROR!!!!!\n";
            std::cerr<<"\tABORT ERROR\n";
            exit(9);
        }
        delete node;
    } catch (const std::exception& ex) {
        if (expectedError) {
            std::cout<<"\tExpected error ="<<ex.what()<<" -- PASSED\n";
        } else {
            std::cerr<<"\tError ="<<ex.what()<<" -- ERROR!!!\n";
            std::cerr<<"\t"<<Solver::interpreterVision(functionDefinition)<<std::endl;
            std::cerr<<"\tABORT ERROR\n";
            exit(9);
        }
    }
    compteur++;
}

void testFunction(const char* functionDefinition, double x, double expectedResult, bool expectedError=false){
    // &x => array of one element...
    testFunctionMultiVariables(functionDefinition, 1, &x, expectedResult, expectedError);
}


void testOperatorsBug() {
    testFunction("-3*x^3 ", 4, 0 - 3*4*4*4);
    testFunction("2 - 3*x^3 ", 4, 2 - 3*4*4*4);

}

void testPriority() {
    testFunction("3*x  + 5 *x *x* 4 - 5", 4, 3*4+5*4*4*4-5);
    testFunction("(x + 3)*x * 4 + 5", 3, (3+3)*3*4+5);
    testFunction("3*x  + 5 *x *x 4 - 5", 4, 0,true);
    testFunction("18+ x / 3*x^3 - 5*x", 4, 18+4.0/3*4*4*4-5*4);
    testFunction(" x / x^3*3 +18- 5*x", 4, 4.0/(4*4*4)*3+18-5*4);
}

void testOperators() {
    testFunction("x*x", 5, 25);
    testFunction("x^2", 5, 25);
    testFunction("3 *x + 2", 5, 3*5+2);
    testFunction("3*x*8 - 5", 5, 3*5*8-5);
    testFunction("(x + 3)*x * 4.4 + 5", 3, (3+3)*3*4.4+5);
    testFunction("x + 3*x *4 + 5", 2,  2+3*2*4+5);
    testFunction("x + (3*x *4) + 5", 2,  2+3*2*4+5);
}

void testExternalFunction() {
    testFunction("sin(12x)", 5, sin(12*5));
    testFunction("x*sqrt(2)+3", 5, 5*sqrt(2)+3);
    testFunction("sin(12x) + x*sqrt(2)+3", 5, sin(12*5)+5*sqrt(2)+3);
}


void testSeveralVariables() {
    double variables[2]{2.0,5.0};
    testFunctionMultiVariables("sin(12x0) + cos(12x1)", 2, variables, sin(12*2) + cos(12*5));
}

int main(){
    testSeveralVariables();
    testExternalFunction();
    testOperators();
    testOperatorsBug();
    testPriority();
    Solver s;
    std::cout << s.interpreterVision("4x") << std::endl << s.interpreterVision("x^2+1")<< std::endl;
    auto function = s.strToFun("-4x");
    std::cout << function->solve(2.5) << std::endl;
};

