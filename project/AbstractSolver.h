//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_ABSTRACTSOLVER_H
#define PROJECT_ABSTRACTSOLVER_H
#include <iostream>
#include "parser/AbstractNode.h"
#include "readData/Data.h"

class AbstractSolver {
public:
    // Constructor and destructor
    AbstractSolver();
    AbstractSolver(AbstractNode* fun);
    AbstractSolver(AbstractNode* fun ,double tol,int Maxit);

    virtual ~AbstractSolver();



    // Setter
    void SetTol(const double tol) {tolerance = tol; }
    void SetMaxIter(const int nMax) {maxIter = nMax; }
    void SetF(AbstractNode* fun) {f = fun; }


    // Getter
    double GetTol() const { return tolerance; }
    int GetMaxIter() const { return maxIter; }

    //Get functions value methods
    double GetFValue(double x) const { return f->solve(x); }


    // Solver methods (Pure Virtual)
    virtual void SolveEquation() const = 0;

protected:
    double tolerance =0.0001;
    int maxIter =10000;
    AbstractNode* f ;
};

#endif //PROJECT_ABSTRACTSOLVER_H
