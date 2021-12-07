//
// Created by lleguill on 01.12.21.
//

#ifndef BISECTION_H
#define BISECTION_H

#include "AbstractSolver.h"

class Bisection : public  AbstractSolver{
public :
    // Constructor
    Bisection();
    Bisection(Data* data);
    Bisection(AbstractNode* fun,double tol,int Maxit,double lowerbound, double upperbund);
    ~Bisection() override ;

    //Set Method
    void SetInterval(const double a, const double b) {lowerBound = a; upperBound = b; }

    // Get Method
    double GetLowerBound() const { return lowerBound; }
    double GetUpperBound() const { return upperBound; }

    //Solve
    void SolveEquation() const override;

private:
    double upperBound{};
    double lowerBound{};

};

#endif //BISECTION_H
