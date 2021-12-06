//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_NEWTON_H
#define PROJECT_NEWTON_H

#include "AbstractSolver.h"

class Newton : public AbstractSolver {
public:

    //Generation and destruction methods
    Newton();
    Newton(double (*fun)(double x),double (*dfun)(double x),double intialvalue);
    Newton(double (*fun)(double x),double (*dfun)(double x),double intialvalue,double tol,int Maxit);
    ~Newton() override;

    // Getter
    double GetInitialValue() const { return initialValue; }
    double GetDfValue(double x) const { return df(x); }

    //Setter
    void SetInitialValue(const double x0) {initialValue = x0; }
    void SetDf(double (*fun)(double x)) {df = fun; }


    // Solve method
    void SolveEquation() const override;

private:
    double initialValue;
    double (*df)(double x);

};


#endif //PROJECT_NEWTON_H
