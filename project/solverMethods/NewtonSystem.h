//
// Created by eseiler@INTRANET.EPFL.CH on 14.12.21.
//

#ifndef PCSC_PROJECT_NEWTONSYSTEM_H
#define PCSC_PROJECT_NEWTONSYSTEM_H

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <utility>
#include "../readData/parser/AbstractNode.h"

class NewtonSystem {
public:
    NewtonSystem(int nbVar,Eigen::VectorX<AbstractNode*> f,  Eigen::MatrixX<AbstractNode*> j, double tol,  int nMax, double* x0)
    : nbVariable(nbVar), F(std::move(f)), J(std::move(j)), tolerance(tol),maxIter(nMax),initialValue(x0){}
    Eigen::VectorXd getFValue(double x[]);
    Eigen::MatrixXd getJValue(double x[]);
    double getTolerance() const {
        return tolerance;
    }
    int getMaxIter() const {
        return maxIter;
    }

    double* solveSystem();

private:
    int nbVariable;
    Eigen::VectorX<AbstractNode*> F;
    Eigen::MatrixX<AbstractNode*> J;
    double tolerance;
    int maxIter;
    double* initialValue;
};


#endif //PCSC_PROJECT_NEWTONSYSTEM_H
