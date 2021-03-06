#include <cmath>
#include<iostream>
#include <exception>
#include <utility>
#include <gtest/gtest.h>
#include "../project/readData/parser/ParserException.h"

#include "../project/solverMethods/Newton.h"
#include "../project/solverMethods/Bisection.h"
#include "../project/solverMethods/ClassicChord.h"
#include "../project/solverMethods/FixedPoint.h"
#include "../project/readData/parser/Solver.h"
#include "../project/readData/ReaderData.h"
#include "../project/solverMethods/ExceptionIterate.h"

#include "FixtureMethod.h"
#include "FixtureInterpreter.h"
#include "../project/readData/InterpreterCodeC.h"





//---------------- Priority operator test--------------------------
TEST_F(Fixture_Interpreter,priorityTest){
    // Test Some valid input, compare the result given by the reconstructed function with the reel one.
    std::cout << "\nTesting Priority operator ... " << std::endl;

    Fixture_Interpreter::SetUp("3*x  + 5 *x *x* 4 - 5",4);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value,3*4+5*4*4*4-5,0.0001)<< "Problem for : 3*x  + 5 *x *x* 4 - 5";

    Fixture_Interpreter::SetUp("(x + 3)*x * 4 + 5",3);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value,(3+3)*3*4+5,0.0001)<< "Problem for : (x + 3)*x * 4 + 5";

    Fixture_Interpreter::SetUp("18+ x / 3*x^3 - 5*x",4);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value,18+4.0/3*4*4*4-5*4,0.0001)<< "Problem for : 18+ x / 3*x^3 - 5*x";

    Fixture_Interpreter::SetUp(" x / x^3*3 +18- 5*x",4);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value,4.0/(4*4*4)*3+18-5*4,0.0001)<< "Problem for :  x / x^3*3 +18- 5*x";
}
//---------------- Expected Error Parser Exception--------------------------
TEST_F(Fixture_Interpreter,error_parser_expected){
    //Test error with wrong input. If a error is in fact detected, the error_valid variavle is set to 1
    
    std::cout << "Testing expected error parseur exception ... " << std::endl;
    // begin with *
    Fixture_Interpreter::SetUp("*3*x  + 5 *x *x 4 - 5",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for 3*x  + 5 *x *x 4 - 5  -> error expected";
    // double "/"
    Fixture_Interpreter::SetUp(" 3// 5",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for 3// 5  -> error expected";
    // no operator
    Fixture_Interpreter::SetUp(" x 3",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for 2 3  -> error expected";
    // ) dont open
    Fixture_Interpreter::SetUp("(5*2) + 5)",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for 3*x  + 5 *x *x 4 /- 5  -> error expected";
    // 5 in lettre
    Fixture_Interpreter::SetUp("x + cinq",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for x + cinq  -> error expected";
    // divide nothing
    Fixture_Interpreter::SetUp("/ x",4, true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for / x  -> error expected";
}
///---------------- operator test-------------------------
TEST_F(Fixture_Interpreter,testoperator) {
    // Test Some operator. Compare the result given by the reconstructed function with the reel one.
    
    std::cout << "Testing operator ... " << std::endl;

    Fixture_Interpreter::SetUp("x*x", 5);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, 25, 0.0001)<< "Problem for : x*x";

    Fixture_Interpreter::SetUp("x^x", 5);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, 5*5*5*5*5, 0.0001)<< "Problem for : x^x";

    Fixture_Interpreter::SetUp("(x + 3)*x * 4.4 + 5", 3);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, (3+3)*3*4.4+5, 0.0001)<< "Problem for : (x + 3)*x * 4.4 + 5";
}

///---------------- External function Test ------------------------
TEST_F(Fixture_Interpreter,testexternalfunction) {
    // Test Some valid input with specific function, compare the result given by the reconstructed function with the reel one.
    
    std::cout << "Testing external function ... " << std::endl;

    Fixture_Interpreter::SetUp("sin(12*x)", 5);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, sin(12*5), 0.0001) << "Problem for : sin(12*x)";

    Fixture_Interpreter::SetUp("exp(x * cos(x^2))", 2.3);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, exp(2.3 * cos(2.3*2.3)), 0.0001)
                                    << "Problem for : exp(x * cos(x^2))";

    Fixture_Interpreter::SetUp("sqrt(3*x + x)", 5);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, sqrt(3*5 +5), 0.0001) << "Problem for : sqrt(3*x/4)";
}


///---------------- Multi Variable TEST------------------------
TEST_F(Fixture_Interpreter,multiVariables) {
    // Test multi-variable function. Compare the result given by the reconstructed function with the reel one.
    std::cout << "Testing multiVariable Parser  .. " << std::endl;

    double variables[2]{2.0,5.0};
    Fixture_Interpreter::SetUp("sin(12x0) + cos(12x1)",variables,2);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, sin(12*2) + cos(12*5), 0.0001)
    << "<-- Problem for : sin(12x0) + cos(12x1))";

    double variables2[4]{2.0,5.0,8.0,1.5};
    Fixture_Interpreter::SetUp("x2 * x1 + x3^2 /x0 +x2",variables2,4);
    ASSERT_NEAR(Fixture_Interpreter::calculated_value, 8 *5 + 1.5*1.5/2 +8, 0.0001)
    << "<-- Problem for : x2 * x1 + x3^2 /x0 +x2";
}

TEST_F(Fixture_Interpreter,multiVariables_Exception) {
    //Test error with wrong input. If a error is in fact detected, the error_valid variavle is set to 1
    
    std::cout << "Testing Expected multiVariable Exception .. " << std::endl;
    double variable[2];

    // x0 and x2 but no x1 ( x must follow and begin by x0 )
    Fixture_Interpreter::SetUp("x0+ x2",variable,2,true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for x1 + x3 -> error expected";
    
    // use of y ( parser only understand x0 x1 etc ... )
    Fixture_Interpreter::SetUp("x+ y",variable,2,true);
    ASSERT_EQ(Fixture_Interpreter::error_valid,1)<< "Problem for x+ y -> error expected";
}

///---------------- Extern File TEST------------------------
TEST(ReadingOutputFile,fun_Test){
    //Test the function in the extern functionTest.cpp file given. Assert the reader can return the pointer to the desired function
    
    std::cout << "Testing Read function from extern file .." << std::endl;

    std::string path="../../google_test/functionTest.cpp";
    std::string functionName="funa";
    InterpreterCodeC interpreter1(path, functionName);
    AbstractNode* f = interpreter1.createExecutableFunction();
    ASSERT_NEAR(f->solve(4), exp(4)-12, 0.0001)<<"<-- Problem Reading the extern file : exp(x) - 12 ";
    
    functionName="funb";
    InterpreterCodeC interpreter2(path, functionName);
    AbstractNode* g = interpreter2.createExecutableFunction();
    ASSERT_NEAR(g->solve(4),5*4 +log(sqrt(4*4*4)), 0.0001)<<"<-- Problem Reading the extern file: 5*x + log(sqrt(x*x*x))";

    functionName="func";
    InterpreterCodeC interpreter3(path, functionName);
    AbstractNode* h = interpreter3.createExecutableFunction();
    ASSERT_NEAR(h->solve(4), cos(4) + 4*2 ,0.0001)<<"<-- Problem Reading the extern file : cos(x) + x*2; ";
}

TEST(ReadingOutputFile2,Exeption_Test) {
    // Test if given a wrong function name throw the desired error
    
    std::cout << "Testing Read function from extern file Exception error" << std::endl;
    
    std::string path="../../google_test/functionTest.cpp";
    std::string functionName="wrong";
    InterpreterCodeC interpreter1(path, functionName);
    ASSERT_THROW(interpreter1.createExecutableFunction()
                 ,std::invalid_argument);
}

/// ----------------Divide by 0 exception -------------------------
TEST(StrToFunTest1,divide_by_0){
    // Testing if the dividing by 0 throw an error
    
    std::cout << "Testing divide by 0 exception... " << std::endl;
    AbstractNode* f = Solver::strToFun("1/x");
    ASSERT_THROW(f->solve(0),std::invalid_argument)<< "Problem when dividing by 0 : invalid argument expected ..";
}


/// ----------------Classic Chord TEST --------------------------------
TEST_F(Fixture_Solve,Test_Chord){
    // Test working case valid result
    
    std::cout<<"Testing Chord resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("x","0",10,0.0001,1000,-100,1000,
                         "Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,0000.1)<< "<--Classic Chord resolution Problem";

    Fixture_Solve::SetUp("x^3 +2*x -8","3*x^2 + 2",10,0.0001,1000,-100,
                         1000,"Chord");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,0000.1)<< "<--Classic Chord resolution Problem";
}

TEST_F(Fixture_Solve,Test_Chord_Exception) {
    // Test exception when the method doen't reach a good solution
    
    std::cout << "Testing Chord exception ... " << std::endl;
    try {
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "Chord");
        FAIL()<<"should throw an exception ";
    } catch (ExceptionIterate(&e)) {} // Test Passed
    //If Catch Any other exception --> Test failed
    catch (...){
        FAIL() <<"<--Wrong exception throw" ;
    }
}

/// ------------Bisection TEST --------------------------------
TEST_F(Fixture_Solve,Test_Bisection){
    // Test working case valid result
    
    std::cout<<"Testing Bisection Resolution ... "<<std::endl;
    Fixture_Solve::SetUp("2*x/(x^2+1)","0",7,0.0001,1000,-100,6000,
                         "Bisection");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,00.1)<< "<--Bisection resolution Problem";

    Fixture_Solve::SetUp("x^7-x^2-7", "0", 7, 0.0001, 1000, -100,
                         6000,"Bisection");
    ASSERT_NEAR(Fixture_Solve::getResult(), 0, 00.1)<< "<--Bisection resolution Problem";
}
TEST_F(Fixture_Solve,Test_Bisection_Exception) {
    std::cout << "Testing Bisection exception ... " << std::endl;
    
    // Test error when f(a) * f(b) >0
    try { 
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.01, 1000, -100,
                             1000, "Bisection");
        FAIL()<<"should throw an exception ";
    }catch (std::invalid_argument(&e)) {} // Test Passed
    catch (...){ //If Catch Any other exception --> Test failed
        FAIL() <<"<--Wrong exception throw" ;
    }
    
    // Test exception when the method doen't reach a good solution
    try { 
        Fixture_Solve::SetUp("x^3", "0", 0, 0.0001, 10, -10000,
                             1, "Bisection");
        FAIL()<<"should throw an exception ";
    }catch (ExceptionIterate(&e)) {} // Test Passed
    catch (...){ //If Catch Any other exception --> Test failed
        FAIL() <<"<--Wrong exception throw" ;
    }
}

/// ----------------NEWTON TEST ----------------------------------
TEST_F(Fixture_Solve,Test_Newton){
    // Test working case valid result
    
    std::cout<<"Testing  Newton resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("3*x^2 + 2*x","6*x +2",10,0.0001,1000,-100,
                         1000,"Newton");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1)<< "<--Newton resolution Problem..";

    Fixture_Solve::SetUp("6*x","6",10,0.0001,1000,-100,
                         1000,"Newton");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1)<< "<--Newton resolution Problem..";
}
TEST_F(Fixture_Solve,Test_Newton_Exception){
    // Test exception when the method doen't reach a good solution
    
    std::cout<<"Testing Newton exception ... "<<std::endl;
    try { // Test exception when the method doen't reach a good solution
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "Newton");
        FAIL()<<"should throw an exception ";
    }catch (ExceptionIterate(&e)) {} // Test Passed
    catch (...){ //If Catch Any other exception --> Test failed
        FAIL() <<"<--Wrong exception throw" ;
    }
}


/// ----------------Fixed Point  TEST --------------------------------
TEST_F(Fixture_Solve,Test_Fixed_point){
    // Test working case valid result
    
    std::cout<<"Testing fixed point resolution  ... "<<std::endl;
    Fixture_Solve::SetUp("3*x^2 + 2*x","6*x +2",10,0.0001,1000,-100,
                         1000,"FixedPoint");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1)<< "<--Fixed Point resolution Problem";

    Fixture_Solve::SetUp("6*x","6",10,0.0001,1000,-100,
                         1000,"FixedPoint");
    ASSERT_NEAR(Fixture_Solve::getResult(),0,000.1)<< "<--Fixed Point resolution Problem";
}


TEST_F(Fixture_Solve,Test_FP_Exception) {
    // Test exception when the method doen't reach a good solution
    
    std::cout << "Testing Fixed_point  exception ... " << std::endl;

    try { // Test exception when the method doen't reach a good solution
        Fixture_Solve::SetUp("x^2+2", "2*x", 10, 0.0001, 1000, 0,
                             0, "FixedPoint");
        FAIL()<<"<--should throw an exception ";
    }
    catch (ExceptionIterate(&e)) {} // Test Passed
    catch (...){ //If Catch Any other exception --> Test failed
        FAIL() <<"<--Wrong exception throw" ;
    }
}







