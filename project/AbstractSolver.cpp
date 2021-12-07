//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"


AbstractSolver::AbstractSolver()
        :tolerance(), maxIter(), f(0) {}

AbstractSolver::AbstractSolver(double (*fun)(double))  {
    f =fun ;
    tolerance=0.00001;
    maxIter= 10000 ;
}

AbstractSolver::AbstractSolver(double (*fun)(double), double tol, int Maxit) :
    f(fun),tolerance(tol),maxIter(Maxit) {}

AbstractSolver::~AbstractSolver() = default;
