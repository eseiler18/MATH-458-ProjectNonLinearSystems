//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"


AbstractSolver::AbstractSolver()
        :tolerance(), maxIter(), f(0) {}


AbstractSolver::AbstractSolver(AbstractNode* fun, double tol, int Maxit) :
    f(fun),tolerance(tol),maxIter(Maxit){}

AbstractSolver::~AbstractSolver() = default;
