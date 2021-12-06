//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"


AbstractSolver::AbstractSolver()
        :  tolerance(), maxIter(), f(0) {}

AbstractSolver::AbstractSolver(double (*fun)(double)) {
    f=fun;
    std::cout<< "Abstract Solver constructor tolerence = 0.0001 ,  "
                "Max itération = 1000"<< std::endl;
}

AbstractSolver::~AbstractSolver() {}

AbstractSolver::AbstractSolver(double (*fun)(double),double tol, int Maxit) {
    f = fun ;
    tolerance = tol;
    maxIter = Maxit;
}
