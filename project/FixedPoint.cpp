//
// Created by lleguill on 01.12.21.
//

#include "FixedPoint.h"
#include <cmath>

FixedPoint::FixedPoint() =default;

FixedPoint::FixedPoint(AbstractNode* fun, double intialval, double tol, int Maxit) :
        AbstractSolver(fun,tol,Maxit), initialValue(intialval) {}

FixedPoint::FixedPoint(Data *data) {
    if (data->method["FixedPoint"]) {
        *this =FixedPoint(data->fun,data->initialValue,
                      data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Dont fit with FixedPoint Method");
    }
}

FixedPoint::~FixedPoint() =default;

void FixedPoint::SolveEquation() const {

    //Initialise
    int it = 0;
    double res = tolerance +1;
    double x = initialValue;
    double aux;

    while (res > tolerance && it < maxIter){

        // x(n+1) = f(x) + x(n)
        aux = GetFValue(x) + x;

        //residual is the difference between two succesive iterate
        res = std::abs(aux -x);
        x=aux;
        it +=1;
    }

    std::cout << "Fixed Point Method :" << std::endl;
    if (it >= maxIter){
        std::cout << "Didn't converge after " << maxIter << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "Difference of successive iterates = " << res;
        std::cout << "x = " << x << " and f(x) = " << GetFValue(x) << std::endl;
    }
    else{
        std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "x = " << x << " and f(x) = " << GetFValue(x) << std::endl;
    }


}


