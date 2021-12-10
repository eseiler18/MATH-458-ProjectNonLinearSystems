//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_ABSTRACTSOLVER_H
#define PROJECT_ABSTRACTSOLVER_H
#include <iostream>
#include "parser/AbstractNode.h"
#include "readData/Data.h"
#include "ExceptionIterate.h"
#include <math.h>

/**
 * AbstractSolver Class is the mother class of all the numerical method. It contains the variables
 * common to all method :
 * - The function
 * - The max iteration
 * - The tolerance
 */

class AbstractSolver {
public:
    // Constructor and destructor
    AbstractSolver();
    /// Constructor with the three variable common to all method
    AbstractSolver(AbstractNode* fun ,double tol,int Maxit);

    virtual ~AbstractSolver();

    /// Method to set the tolerance
    void SetTol(const double tol) {tolerance = tol; }
    /// Method to set the max iteration
    void SetMaxIter(const int nMax) {maxIter = nMax; }
    /// Method to set the function
    void SetF(AbstractNode* fun) {f = fun; }


    // Getter
    /// Method to get the tolerance
    double GetTol() const { return tolerance; }
    /// Method to get the max iteration
    int GetMaxIter() const { return maxIter; }

    //Get functions value methods
    /// Method that return the value of f(x) for a given x
    double GetFValue(double x) const { return f->solve(x); }


    /// Pure virtual method that solve f(x)
    virtual void SolveEquation() const = 0;

protected:
    // function pointer
    AbstractNode* f ;
    // Other variables
    double tolerance ;
    int maxIter ;

};

#endif //PROJECT_ABSTRACTSOLVER_H
