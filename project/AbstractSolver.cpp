//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "AbstractSolver.h"


AbstractSolver::AbstractSolver()
        :tolerance(), maxIter(), f(0) {}


AbstractSolver::AbstractSolver(AbstractNode* fun, double tol, int Maxit) {
    f=fun ;
    if (tol != -1){
        tolerance =tol ;
    }else{
        std::cout<<"Tolerance not specified, set to defaut value 0.0001"<<std::endl;
    }
    if (Maxit != -1){
        maxIter= Maxit;
    }else{
        std::cout<<"Max itération not specified, set to defaut value 10000"<<std::endl;
    }
}

AbstractSolver::~AbstractSolver() = default;
