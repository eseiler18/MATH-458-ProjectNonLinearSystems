//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#ifndef PROJECT_CLASSICCHORD_H
#define PROJECT_CLASSICCHORD_H
#include "AbstractSolver.h"


/**
 * Daughter of AbstractSolver, that solve the Equation with Classic Chord Method.
 * Classic chord Method need to work with a initial value.
 */

class ClassicChord : public AbstractSolver{
public:
    /// Empty constructor
    ClassicChord();
    /// Constructor with a data vector
    ClassicChord(Data* data);
    /// Constructor with variable spared
    ClassicChord(AbstractNode* fun,double intialvalue,double tol,int Maxit);
    /// Destructor
    ~ClassicChord() override;

    /// Getter method  for the initial value.
    double GetInitialValue() const { return initialValue; }

    /// Setter method  for the initial value.
    void SetInitialValue(const double x0) {initialValue = x0; }

    /// Polymorph solver for classic chord method
    struct retVals SolveEquation() const override;

private:
    double initialValue;
};
#endif //PROJECT_CLASSICCHORD_H
