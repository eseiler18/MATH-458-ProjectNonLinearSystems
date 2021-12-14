//
// Created by eseiler@INTRANET.EPFL.CH on 14.12.21.
//

#ifndef PCSC_PROJECT_NEWTONSYSTEM_H
#define PCSC_PROJECT_NEWTONSYSTEM_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <utility>
#include "../readData/parser/AbstractNode.h"

/**
 * Newton System class use to apply the newton method at a system
 * the parameter F is a vector with all equation of the system
 * the parameter J is the Jacobian matrix of the system
 */
class NewtonSystem {
public:
    /// Constructor of NewtonSystem with all parameters
    NewtonSystem(int nbVar,Eigen::VectorX<AbstractNode*> f,  Eigen::MatrixX<AbstractNode*> j, double tol,  int nMax, double* x0)
    : nbVariable(nbVar), F(std::move(f)), J(std::move(j)), tolerance(tol),maxIter(nMax),initialValue(x0){}
    /// get the value of F for value of x0, x1...
    Eigen::VectorXd getFValue(double x[]);
    /// get the value of J for value of x0, x1...
    Eigen::MatrixXd getJValue(double x[]);
    /// getter for the tolerance
    double getTolerance() const {
        return tolerance;
    }
    /// getter for the maxIter
    int getMaxIter() const {
        return maxIter;
    }
    /// solve the system for parameter initial value with the Newton Method
    double* solveSystem();

private:
    /// number of variable in the system
    int nbVariable;
    Eigen::VectorX<AbstractNode*> F;
    Eigen::MatrixX<AbstractNode*> J;
    double tolerance;
    int maxIter;
    double* initialValue;
};


#endif //PCSC_PROJECT_NEWTONSYSTEM_H
