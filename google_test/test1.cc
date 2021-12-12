#include <cmath>
#include <exception>
#include <gtest/gtest.h>

#include "../project/Newton.h"
#include "../project/Bisection.h"
#include "../project/ClassicChord.h"
#include "../project/FixedPoint.h"
#include "../project/parser/Solver.h"

#include "../project/readData/ReaderData.h"
#include "../project/ExceptionIterate.h"




// MACRO function "TEST" from Google Test
// defines a test and a context
///---------------- Constructor string to function --------------------------------------
TEST(ConstructorStrToFuncTest1,invalid_input){
    ASSERT_THROW(Solver::strToFun("x+ cinq"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("x +*2"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("x 44"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("(x+3"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("2* x)"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("x +"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("/x"),std::invalid_argument);
    ASSERT_THROW(Solver::strToFun("Prog is fun"),std::invalid_argument);
}

///---------------- Interpreter string to function of method Solve-----------------------
TEST(StrToFunTest1,Valid_input){
    AbstractNode* f = Solver::strToFun("x^3 +(2*x -8)/x^2");
    ASSERT_NEAR(f->solve(2),7,0.0001);
    ASSERT_NEAR(f->solve(-4),-65,0.0001);
    ASSERT_NEAR(f->solve(0.05),-3159.999875,0.0001);
}
TEST(StrToFunTest1,divide_by_0){
    AbstractNode* f = Solver::strToFun("1/x");
    ASSERT_THROW(f->solve(0),std::invalid_argument);
}




TEST(MyNewtonTest1, valid_input) {
    AbstractNode* f = Solver::strToFun("x^3 +2*x -8");
    AbstractNode* df = Solver::strToFun("3*x^2 + 2");
     struct Data dat= {.fun= f,.dFun = df,.initialValue=10,.tolerance=0.0001,
                .maxIter=1000,.method ={{"Newton",true}} };
     Newton n(&dat);
    ASSERT_NEAR(0, n.GetFValue(n.SolveEquation()),0.001);
}
TEST(MyNewtonTest1, no_solution) {
    AbstractNode* f = Solver::strToFun("x^2 +2");
    AbstractNode *df = Solver::strToFun("2*x");
    struct Data dat = {.fun= f, .dFun = df, .initialValue=10, .tolerance=0.0001,
            .maxIter=1000, .method ={{"Newton", true}}};
    Newton b(&dat);
    ASSERT_THROW(b.SolveEquation(), ExceptionIterate);
}

///---------------- Bisection Test -------------------------------
// Valid Test
TEST(MyBisectionTest1, valid_input) {
    AbstractNode* f = Solver::strToFun("x^3 +2*x -8");
    struct Data dat= {.fun= f,.lowerBound =-1000,.upperBound=1000,
            .tolerance=0.0001, .maxIter=1000,.method ={{"Bisection",true}} };
    Bisection b(&dat);
    ASSERT_NEAR(0, b.GetFValue(b.SolveEquation()),0.001);
}
TEST(MyBisectionTest2, invalid_input) {
    AbstractNode* f = Solver::strToFun("x^2 +2");
    struct Data dat= {.fun= f,.lowerBound =-1,.upperBound=1,
            .tolerance=0.0001, .maxIter=1000,.method ={{"Bisection",true}} };
    Bisection b(&dat);
    ASSERT_THROW(b.SolveEquation(),std::invalid_argument);
}

///---------------- Classic Chord Test -------------------------------
TEST(MyChordTest1, valid_input) {
    AbstractNode* f = Solver::strToFun("x^3 +2*x -8");
    struct Data dat= {.fun= f,.initialValue=1,
            .tolerance=0.0001, .maxIter=1000,.method ={{"Chord",true}} };
    ClassicChord c(&dat);
    ASSERT_NEAR(0, c.GetFValue(c.SolveEquation()),0.001);
}

///---------------- Fixed Point Test -------------------------------
TEST(MyFPTest1, valid_input) {
    AbstractNode* f = Solver::strToFun("x^3 +2*x -8");
    struct Data dat= {.fun= f,.initialValue=1,
            .tolerance=0.0001, .maxIter=1000,.method ={{"FixedPoint",true}} };
    FixedPoint fp(&dat);
    ASSERT_NEAR(0, fp.GetFValue(fp.SolveEquation()),0.001);
}

