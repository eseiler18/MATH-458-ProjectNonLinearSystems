//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"

// Default empty constructor
AbstractSolver::AbstractSolver()
        :tolerance(), maxIter(), f(0) {}

// Classic Constructor that affect the given value to the variables
AbstractSolver::AbstractSolver(AbstractNode* fun, double tol, int Maxit) :
    f(fun),tolerance(tol),maxIter(Maxit){}

// Default destructor
AbstractSolver::~AbstractSolver() = default;
