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
        std::cout << "Fixed Point Method with Aitken acceleration :" << std::endl;
        //Initialise
        int it = 0;
        double res = tolerance + 1;
        double xPrev = initialValue;
        double x;
        double xNext;
        double Ax;
        while (res > tolerance && it < maxIter) {
            // x(n+1) = f(x) + x(n)
            x = GetFValue(xPrev) + xPrev;
            xNext = GetFValue(x) + x;
            Ax = xNext - pow(xNext - x, 2) / (xNext + xPrev - 2 * x);
            //residual is the difference between two successive iterate
            res = std::abs(Ax - xNext);
            it += 1;
            xPrev = Ax;
        }
        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(Ax) + " and f(x) = " + std::to_string(GetFValue(Ax)));
            throw ExceptionIterate(message);
        } else if (std::abs(GetFValue(Ax)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + " x = " + std::to_string(Ax) + " and f(x) = " +
                                std::to_string(GetFValue(Ax)));
            throw ExceptionIterate(message);
        } else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << Ax << " and f(x) = " << GetFValue(Ax) << std::endl;
        }

    }
    catch (std::invalid_argument &e) { std::cout << e.what() << std::endl; }
    catch (ExceptionIterate(&e)) { e.what(); }
}


