//
// Created by lleguill on 01.12.21.
//

#ifndef BISECTION_H
#define BISECTION_H

#include "AbstractSolver.h"

class Bisection : public  AbstractSolver{
public :
    Bisection();
    ~Bisection() override ;

    //Solve
    void SolveEquation() const override;

};

#endif //BISECTION_H
