//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#ifndef PROJECT_CLASSICCHORD_H
#define PROJECT_CLASSICCHORD_H
#include "AbstractSolver.h"

class ClassicChord : public AbstractSolver{
    public:

    // Generator and Destructor
    ClassicChord();
    ClassicChord(AbstractNode* fun,double intialval);
    ClassicChord(AbstractNode* fun,double intialvalue,double tol,int Maxit);
    ~ClassicChord() override;

    // Getter
    double GetInitialValue() const { return initialValue; }

    //Setter
    void SetInitialValue(const double x0) {initialValue = x0; }

    //Solve method
    void SolveEquation() const override;

private:
    double initialValue;
};

#endif //PROJECT_CLASSICCHORD_H
