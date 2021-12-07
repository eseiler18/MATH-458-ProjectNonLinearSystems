//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "Bisection.h"
#include "FixedPoint.h"
#include "readData/ReaderData.h"
#include "Newton.h"


double ideFun(double x){return x-22;}
double fun(double x){return x*x;}


int main() {

    AbstractNode* fun = Solver::strToFun("x*3 +7");
    AbstractNode* dfun = Solver::strToFun("3");
    Bisection c(fun,0.0001,1000,-10,30);
    //c.SolveEquation();

    Newton n(fun,dfun,-3,0.00001,1000);
    n.SolveEquation();



    /*
    Bisection d(ideFun,0,50);
    d.SolveEquation();

    FixedPoint Fx(ideFun,4);
    Fx.SolveEquation();
    */
    /*
    Data t ;
    t.lowerBound= 4;
    t.upperBound=10 ;
    t.initialValue= 23;
    t.tolerance =0.0001;
    t.maxIter = 1000 ;
    t.fun = Solver::strToFun("x*3 +7"); */
    /*

    FixedPoint fp;
    fp.SetF(ideFun);
    fp.SetInitialValue(-5);
    fp.SetMaxIter(1000);
    fp.SetTol(0.001);
    fp.SolveEquation(); */


    return 0;
}