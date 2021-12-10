//
// Created by lleguill on 01.12.21.
//

#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include "AbstractSolver.h"

/**
 * Daughter of AbstractSolver, that solve the Equation with Fixed point Method.
 * Fixed point Method need to work with a initial value.
 */

class FixedPoint :public AbstractSolver{
public:

    //Generation & Destructor
    /// Empty constructor
    FixedPoint();
    /// Constructor with a data vector
    FixedPoint(Data* data);
    /// Constructor with variable spared
    FixedPoint(AbstractNode* fun,double intialvalue,double tol,int Maxit);
    /// Destructor
    ~FixedPoint() override;

    ///Getter method  for the initial value.
    double GetInitialValue() const { return initialValue; }

    ///Setter method  for the initial value.
    void SetInitialValue(const double x0) {initialValue = x0; }

    //Solve Method
    /// Polymorph solver for fixed point  method
    void SolveEquation() const override;

private:
    double initialValue;
};

#endif //FIXEDPOINT_H
