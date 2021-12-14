#include <cmath>
#include<iostream>
#include<string>
#include <exception>
#include <utility>
#include <gtest/gtest.h>

#include "../project/solverMethods/Newton.h"
#include "../project/solverMethods/Bisection.h"
#include "../project/solverMethods/ClassicChord.h"
#include "../project/solverMethods/FixedPoint.h"
#include "../project/readData/parser/Solver.h"

#include "../project/readData/ReaderData.h"
#include "../project/solverMethods/ExceptionIterate.h"

#include "FixtureTest.h"


///---------------- Constructor string to function --------------------------------------
TEST(ConstructorStrToFuncTest1,invalid_input){
    std::cout << "Testing reader ... " << std::endl;
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
    std::cout << "Testing Solver return method... " << std::endl;
    AbstractNode* f = Solver::strToFun("x^3 +(2*x -8)/x^2");
    ASSERT_NEAR(f->solve(2),7,0.0001);
    ASSERT_NEAR(f->solve(-4),-65,0.0001);
    ASSERT_NEAR(f->solve(0.05),-3159.999875,0.0001);
}
TEST(StrToFunTest1,divide_by_0){
    std::cout << "Testing divide by 0 exception... " << std::endl;
    AbstractNode* f = Solver::strToFun("1/x");
    ASSERT_THROW(f->solve(0),std::invalid_argument);
}

TEST_F(Fixture_Solve,Test_Chord){
    std::cout<<"Testing Chord resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("x","0",10,0.0001,1000,-100,1000,
                         "Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,00.1);

    Fixture_Solve::SetUp("x^3 +2*x -8","3*x^2 + 2",10,0.0001,1000,-100,
                         1000,"Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1);
}


TEST_F(Fixture_Solve,Test_Bisection){
    std::cout<<"Testing Bisection Resolution ... "<<std::endl;
    Fixture_Solve::SetUp("2*x/(x^2+1)","0",7,0.0001,1000,-100,6000,
                         "Bisection");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,00.1);

    Fixture_Solve::SetUp("x^7-x^2-7", "0", 7, 0.0001, 1000, -100,
                         6000,"Bisection");
    ASSERT_NEAR(Fixture_Solve::getResult(), 0, 00.1);

}

TEST_F(Fixture_Solve,Test_Newton){
    std::cout<<"Testing  Newton resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("3*x^2 + 2*x","6*x +2",10,0.0001,1000,-100,
                         1000,"Newton");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1);

    Fixture_Solve::SetUp("6*x","6",10,0.0001,1000,-100,
                         1000,"Newton");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1);
}

TEST_F(Fixture_Solve,Test_Fixed_point){
    std::cout<<"Testing fixed point resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("3*x^2 + 2*x","6*x +2",10,0.0001,1000,-100,
                         1000,"FixedPoint");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1);

    Fixture_Solve::SetUp("6*x","6",10,0.0001,1000,-100,
                         1000,"FixedPoint");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1);
}


TEST_F(Fixture_Solve,Test_Newton_Exception){
    std::cout<<"Testing Newton exception ... "<<std::endl;
    try {
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "Newton");
        std::cout<<"Error test Newton Exception... "<<std::endl;
        ASSERT_EQ(1,0);
    }catch (ExceptionIterate(&e)){ ASSERT_EQ(1,1) ;}
}
TEST_F(Fixture_Solve,Test_FP_Exception) {
    std::cout << "Testing Fixed_point  exception ... " << std::endl;
    try {
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "FixedPoint");
        std::cout << "Error test Fixed point Exception... " << std::endl;
        ASSERT_EQ(1, 0);
    } catch (ExceptionIterate(&e)) { ASSERT_EQ(1, 1); }
}

TEST_F(Fixture_Solve,Test_Bisection_Exception) {
    std::cout << "Testing Bisection exception ... " << std::endl;
    try {
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.01, 1000, -100,
                             1000, "Bisection");
        std::cout << "Error test Bisection Exception... " << std::endl;
        ASSERT_EQ(1, 0);
    } catch (std::invalid_argument(&e)) { ASSERT_EQ(1, 1); }
}

TEST_F(Fixture_Solve,Test_Chord_Exception) {
    std::cout << "Testing Chord exception ... " << std::endl;
    try {
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "Chord");
        std::cout << "Error test Chord Exception... " << std::endl;
        ASSERT_EQ(1, 0);
    } catch (ExceptionIterate(&e)) { ASSERT_EQ(1, 1); }
}






/// -----------------------Test Newton -------------------------------------------------------------
/*
TEST(MyNewtonTest1, valid_input) {
    AbstractNode* f = Solver::strToFun("x^3 +2*x -8");
    AbstractNode* df = Solver::strToFun("3*x^2 + 2");
     struct Data dat= {.fun= f,.dFun = df,.initialValue=10,.tolerance=0.0001,
                .maxIter=1000,.method ={{"Newton",true}} };
     Newton n(&dat);
    ASSERT_NEAR(0, n.GetFValue(n.SolveEquation()),0.001);
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
*/


/*file(GLOB SOURCES  ${PROJECT_SOURCE_DIR}/*.cpp)
foreach(f ${SOURCES})
    get_filename_component(basename ${f} NAME_WE)
    get_filename_component(dir ${f} DIRECTORY)
    add_executable(${basename} ${f})
endforeach() */

/*Fixture_Solve::Fixture_Solve(std::string sfun, std::string sdfun, double initialVal, double tol, int Maxit,
                             double lowerbound, double upperbound,int met) : f(Solver::strToFun(sfun)),
                             df(Solver::strToFun(sdfun)),initialValue(initialVal), tolerance(tol),
                             maxIter(Maxit), method(met), upperBound(upperbound),lowerBound(lowerbound){}; */