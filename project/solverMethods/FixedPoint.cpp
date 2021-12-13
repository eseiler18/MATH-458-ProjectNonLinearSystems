//
// Created by lleguill on 01.12.21.
//

#include "FixedPoint.h"
#include <cmath>

// Default empty constructor
FixedPoint::FixedPoint() =default;

// The constructor with data call the constructor with all separated input.
// It also verify the comptability with the fixed point method
FixedPoint::FixedPoint(Data *data) {
    if (data->method["FixedPoint"]) {
        *this =FixedPoint(data->fun,data->initialValue,
                          data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Dont fit with FixedPoint Method");
    }
}
// Classic constructor
FixedPoint::FixedPoint(AbstractNode* fun, double intialval, double tol, int Maxit) :
        AbstractSolver(fun,tol,Maxit), initialValue(intialval) {}

// Default destructor
FixedPoint::~FixedPoint() =default;


// Solving method
double FixedPoint::SolveEquation() const {
    std::cout << "\nFixed Point Method with Aitken acceleration :" << std::endl;
    //Initialise
    int it = 0;
    double res = tolerance + 1;
    double xPrev = initialValue;
    double x;
    double xNext;
    double Ax;
    double result;
    // Don't stop until we reach the desired tolerance or the max iteration
    while (res > tolerance && it < maxIter) {
        // x(n) = f(x(n-1)) + x(n(n-1)
        x = GetFValue(xPrev) + xPrev;
        if (std::abs(xPrev-x) < tolerance){
            result = x;
            break;
        }
        // x(n+1) = f(x(n)) + x(n)
        xNext = GetFValue(x) + x;
        if (std::abs(xNext-x) < tolerance){
            result = xNext;
            break;
        }
        // Check divide by 0 & if x value are infinite
        if ((xNext ==0 && x==0 && xPrev==0) || std::isinf(xNext) || std::isinf(xPrev) || std::isinf(x)) {
            result = xNext;
            break;
        }
        // Aitken update
        Ax = xNext - pow(xNext - x, 2) / (xNext + xPrev - 2 * x);

        //residual is the difference between two successive iterate
        res = std::abs(Ax - xNext);

        // Update iteration
        it += 1;
        // Update value
        xPrev = Ax;
        result = Ax;
    }

    // Trowing error for not converging after the given max iteration
    if (it >= maxIter) {
        std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                            + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                            std::to_string(res) + "x = "
                            + std::to_string(result) + " and f(x) = " + std::to_string(GetFValue(result)));
        throw ExceptionIterate(message);
    }
        // Throwing error for converging to a wrong solution
    else if (std::abs(GetFValue(result)) > tolerance * 10) {
        std::string message("Converge to a wrong solution after " + std::to_string(it) +
                            " iterations for a tolerance of " + std::to_string(tolerance) +
                            ".\nDifference of successive iterates = "
                            + std::to_string(res) + " x = " + std::to_string(result) + " and f(x) = " +
                            std::to_string(GetFValue(result)));
        throw ExceptionIterate(message);
    }
        // else : printing the converged solution
    else {
        std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
        std::cout << "x = " << result << " and f(x) = " << GetFValue(result) << std::endl;
        return result;
    }
}

