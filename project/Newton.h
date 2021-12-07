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
    Newton(AbstractNode* fun,AbstractNode* dfun,double intialvalue);
    Newton(AbstractNode* fun,AbstractNode* dfun,double intialvalue,double tol,int Maxit);
    ~Newton() override;

    // Getter
    double GetInitialValue() const { return initialValue; }
    double GetDfValue(double x) const { return df->solve(x); }

    //Setter
    void SetInitialValue(const double x0) {initialValue = x0; }
    void SetDf(AbstractNode* dfun) {df = dfun; }


    // Solve method
    void SolveEquation() const override;

private:
    double initialValue;
    AbstractNode* df;

};


#endif //PROJECT_NEWTON_H
