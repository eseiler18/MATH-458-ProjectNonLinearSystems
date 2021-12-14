//
// Created by eseiler@INTRANET.EPFL.CH on 14.12.21.
//

#include <iostream>
#include "NewtonSystem.h"
#include "ExceptionIterate.h"

Eigen::VectorXd NewtonSystem::getFValue(double x[]) {
    Eigen::VectorXd result(nbVariable);
    int count=0;
    for(AbstractNode* f : F){
        double res = f->solve(nbVariable, x);
        result(count)=res;
        count++;
    }
    return result;
}

Eigen::MatrixXd NewtonSystem::getJValue(double x[]) {
    Eigen::MatrixXd result(nbVariable,nbVariable);
    for (int i=0; i<nbVariable; i++){
        for (int j=0; j<nbVariable; j++){
            double res = J(i,j)->solve(nbVariable, x);
            result(i,j) = res;
        }
    }
    return result;
}

double *NewtonSystem::solveSystem() {
    int it=1;
    double res = tolerance+1;
    double* x = initialValue;
    double* xNext;
    double* result;
    while(res > tolerance && it < maxIter){
        Eigen::VectorXd FValue = getFValue(x);
        Eigen::MatrixXd JValue = getJValue(x);
        if(JValue.determinant() == 0){
            result = x;
            break;
        }
        auto facto = JValue.fullPivLu();
        Eigen::VectorXd delta = facto.solve(-FValue);
        res=0;
        for(int i=0; i<nbVariable; i++) {
            // compute next x
            xNext[i] = x[i] + delta(i);
            // compute the norm of the difference between two iteration
            res += pow(x[i] - xNext[i], 2);
            //  update x
            x[i] = xNext[i];
        }
        res = sqrt(res);
        result=x;
        it++;
    }
    std::string resultStr;
    std::string FResultStr;
    for (int i=0 ; i<nbVariable;i++){
        resultStr.append(std::to_string(result[i]));
        FResultStr.append(std::to_string(getFValue(result)(i)));
        resultStr.append(",");
        FResultStr.append(",");
    }
    if (it >= maxIter) {
        std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                            + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                            std::to_string(res) + "\nx = "
                            + resultStr + " and F(x) = " + FResultStr);
        throw ExceptionIterate(message);
    }
        // Throwing error for converging to a wrong solution
    else if (getFValue(result).norm() > tolerance*100) {
        std::string message("Converge to a wrong solution after " + std::to_string(it) +
                            " iterations for a tolerance of " + std::to_string(tolerance) +
                            ".\nDifference of successive iterates = "
                            + std::to_string(res) + "\nx = " + resultStr + " and f(x) = " + FResultStr);
        throw ExceptionIterate(message);
    }
    maxIter =it;
    return result;
}


