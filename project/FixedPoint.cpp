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
    try {
        std::cout << "Fixed Point Method :" << std::endl;
        //Initialise
        int it = 0;
        double res = tolerance + 1;
        double x = initialValue;
        double aux;

        while (res > tolerance && it < maxIter) {

            // x(n+1) = f(x) + x(n)
            aux = GetFValue(x) + x;

            //residual is the difference between two succesive iterate
            res = std::abs(aux - x);
            x = aux;
            it += 1;
        }

        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(x) + " and f(x) = " + std::to_string(GetFValue(x)));
            throw ExceptionIterate(message);
        } else if (std::abs(GetFValue(x)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + "x = " + std::to_string(x) + " and f(x) = " +
                                std::to_string(GetFValue(x)));
            throw ExceptionIterate(message);
        } else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << x << " and f(x) = " << GetFValue(x) << std::endl;
        }

    }
    catch(std::invalid_argument &e){std::cout<<e.what()<<std::endl;}
    catch (ExceptionIterate(&e)){ e.what(); }


}


