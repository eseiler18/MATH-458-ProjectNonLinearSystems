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

//Test
class Fixture_Solve : public testing::Test{
protected:
    Fixture_Solve();

    void SetUp(std::string sfun, std::string sdfun, double initialVal, double tol, int Maxit,
               double lowerbound, double upperbound,std::string met);

    virtual void TearDown();
    ~Fixture_Solve();

public:
    double getResult() const;

private:
    AbstractNode* f ;
    AbstractNode* df ;
    double tolerance ;
    int maxIter ;
    double upperBound;
    double lowerBound;
    double initialValue;
    std::string method;
    double result ;
};

Fixture_Solve::Fixture_Solve() {}

void Fixture_Solve::SetUp(std::string sfun, std::string sdfun, double initialVal, double tol, int Maxit,
                          double lowerbound, double upperbound,std::string met) {
    f=Solver::strToFun(std::move(sfun));
    df=Solver::strToFun(sdfun);
    initialValue =initialVal;
    tolerance=tol ;
    maxIter=Maxit ;
    upperBound = upperbound ;
    lowerBound =lowerbound ;
    method=met ;

    if ("Newton"==met){
        Newton aux(f,df,initialValue,tolerance,maxIter);
        result=aux.GetFValue(aux.SolveEquation());
    }else if ("FixedPoint" == met){
        ClassicChord aux(f,initialValue,tolerance,maxIter);
        result=aux.GetFValue(aux.SolveEquation());
    }else if ("Chord" == met ){
        ClassicChord aux(f,initialValue,tolerance,maxIter);
        result=aux.GetFValue(aux.SolveEquation());
    }else if ("Bisection" == met){
        Bisection aux(f,tolerance,maxIter,lowerBound,upperBound);
        result=aux.GetFValue(aux.SolveEquation());
    }
}
void Fixture_Solve::TearDown() {};
Fixture_Solve::~Fixture_Solve() {}

double Fixture_Solve::getResult() const {
    return result;
};



TEST_F(Fixture_Solve,Test_1){
    Fixture_Solve::SetUp("x","0",10,0.001,1000,-100,1000,
                         "Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,0.1);
}

TEST_F(Fixture_Solve,Test_2){
    Fixture_Solve::SetUp("x^3 +2*x -8","3*x^2 + 2",10,0.0001,1000,-100,
                         1000,"Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,0.1);
}

TEST_F(Fixture_Solve,Test_3){
    Fixture_Solve::SetUp("2*x/(x^2+1)","0",7,0.0001,1000,-100,6000,
                         "Bisection");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,00.1);
}





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


/// -----------------------Test Newton -------------------------------------------------------------

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