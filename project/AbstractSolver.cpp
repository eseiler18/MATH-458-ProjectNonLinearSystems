//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"


AbstractSolver::AbstractSolver()
        : lowerBound(), upperBound(), initialValue(),
        tolerance(), maxIter(), f(0), df(0) {}

AbstractSolver::~AbstractSolver() = default;
