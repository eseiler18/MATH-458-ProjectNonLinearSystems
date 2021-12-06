//
// Created by lleguill on 01.12.21.
//

#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#include "AbstractSolver.h"

class FixedPoint :public AbstractSolver{
public:

    //Generation & Destructor
    FixedPoint();
    FixedPoint(double (*fun)(double x),double intialval);
    FixedPoint(double (*fun)(double x),double intialvalue,double tol,int Maxit);
    ~FixedPoint() override;

    // Getter
    double GetInitialValue() const { return initialValue; }

    //Setter
    void SetInitialValue(const double x0) {initialValue = x0; }

    //Solve Method
    void SolveEquation() const override;
private:
    double initialValue;

};


#endif //FIXEDPOINT_H
