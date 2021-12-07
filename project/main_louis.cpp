//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "Bisection.h"
#include "FixedPoint.h"
#include "readData/ReaderData.h"
#include "Newton.h"
#include "ClassicChord.h"





int main() {

    AbstractNode* fun = Solver::strToFun("x*3 +7");
    AbstractNode* dfun = Solver::strToFun("3");
    Bisection c(fun,0.0001,1000,-10,30);
    //c.SolveEquation();

    Newton n(fun,dfun,-3,0.00001,1000);
    //n.SolveEquation();


    std::string frappe("x*3 +7");
    std::string dfrappe("3");

    Data t ;
    t.lowerBound= 4;
    t.upperBound=10 ;
    t.initialValue= 23;
    t.tolerance =-1;
    t.maxIter = 1000 ;
    t.fun = Solver::strToFun(frappe);
    t.dFun = Solver::strToFun(dfrappe);

    Data bisec;
    bisec.lowerBound= -10;
    bisec.upperBound=10 ;
    bisec.initialValue= 23;
    bisec.tolerance =-1;
    bisec.maxIter = 1000 ;
    bisec.fun = Solver::strToFun(frappe);
    bisec.dFun = Solver::strToFun(dfrappe);

    //Newton d(&t);

    Newton BB(&bisec);
    BB.SolveEquation();


    return 0;
}