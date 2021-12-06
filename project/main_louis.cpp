//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "Bisection.h"
#include "FixedPoint.h"


double ideFun(double x){return x-22;}
double fun(double x){return x*x;}


int main() {


    Bisection c(ideFun,0.0001,1000,10,30);
    c.SolveEquation();


    Bisection d(ideFun,0,50);
    d.SolveEquation();

    FixedPoint(ideFun,4);

    /*

    FixedPoint fp;
    fp.SetF(ideFun);
    fp.SetInitialValue(-5);
    fp.SetMaxIter(1000);
    fp.SetTol(0.001);
    fp.SolveEquation(); */


    return 0;
}