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
    ~FixedPoint() override;

    //Solve Method
    void SolveEquation() const override;

};


#endif //FIXEDPOINT_H
