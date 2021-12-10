//
// Created by lleguill on 01.12.21.
//

#ifndef BISECTION_H
#define BISECTION_H

#include "AbstractSolver.h"

/**
 * Daughter of AbstractSolver, that solve the Equation with Bisection Method.
 * The Bisection Method need to work with a lower and and a higher bound.
 */

class Bisection : public  AbstractSolver{
public :
    /// Empty Constructor
    Bisection();
    /// Constructor with a data vector
    Bisection(Data* data);
    /// Constructor with variable spared
    Bisection(AbstractNode* fun,double tol,int Maxit,double lowerbound, double upperbund);
    /// Destructor
    ~Bisection() override ;

    /// Method that set the interval
    void SetInterval(const double a, const double b) {lowerBound = a; upperBound = b; }

    ///Getter Method for lower bound
    double GetLowerBound() const { return lowerBound; }
    ///Getter Method for upper bound
    double GetUpperBound() const { return upperBound; }

    //Solve
    /// Polymorph solver for bisection method
    void SolveEquation() const override;

private:
    double upperBound;
    double lowerBound;

};

#endif //BISECTION_H
