//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "Bisection.h"
#include "FixedPoint.h"


double ideFun(double x){return x-22;}
double dIdeFun(double x){return 1;}

int main() {
    Bisection b;
    b.SetF(ideFun);
    b.SetMaxIter(100);
    b.SetTol(0.0001);
    b.SolveEquation();

    /*
    FixedPoint fp;
    fp.SetF(ideFun);
    fp.SetInitialValue(-5);
    fp.SetMaxIter(100);
    fp.SetTol(0.0001);
    fp.SolveEquation(); */

    return 0;
}