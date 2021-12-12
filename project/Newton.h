//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_NEWTON_H
#define PROJECT_NEWTON_H

#include "AbstractSolver.h"

/**
 * Daughter of AbstractSolver, that solve the Equation with newton Method.
 * Newton need to work with a initial value and the derivative of the function.
 */


class Newton : public AbstractSolver {
public:

    /// Empty constructor
    Newton();
    /// Constructor with a data vector
    Newton(Data* data);
    /// Constructor with variable spared
    Newton(AbstractNode* fun,AbstractNode* dfun,double intialvalue,double tol,int maxIt);
    /// Destructor
    ~Newton() override;

    ///Getter method  for the initial value.
    double GetInitialValue() const { return initialValue; }
    /// Method that return the value of df(x) for a given x
    double GetDfValue(double x) const { return df->solve(x); }

    ///Setter method  for the initial value.
    void SetInitialValue(const double x0) {initialValue = x0; }
    /// Method to set the derivative function
    void SetDf(AbstractNode* dfun) {df = dfun; }


    /// Polymorph solver for newton method
    double SolveEquation() const override;

private:
    double initialValue;
    AbstractNode* df;
};
#endif //PROJECT_NEWTON_H
