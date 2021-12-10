//
// Created by lleguill on 01.12.21.
//

#include "Bisection.h"
#include <cassert>

// Default empty constructor
Bisection::Bisection() =default;

// The constructor with data call call the constructor with all separated input
Bisection::Bisection(Data *data) {
    if (data->method["Bisection"]) {
        *this = Bisection(data->fun, data->tolerance, data->maxIter,
                          data->lowerBound, data->upperBound);
    } else {
        throw std::invalid_argument("Dont fit with Bisection");
    }
}

// Classic constructor
Bisection::Bisection(AbstractNode* fun,double tol, int Maxit, double lowerbound, double upperbound) :
    AbstractSolver(fun,tol,Maxit), lowerBound(lowerbound),upperBound(upperbound) {}

// Default destructor
Bisection::~Bisection() =default;

void Bisection::SolveEquation() const {
    try {
        double b = upperBound;
        double a = lowerBound;
        std::cout << "Bisection Method :" << std::endl;

        // Check 1 : Bound viability:  a must be smaller  than b. If it isn't, the method automatically change
        // the two variable, and print a warning for the user.
        if (b < a) {
            std::cout << "Higher bound is smaller than lower bound, bounds inverted for the calculation. " << std::endl;
            double aux = a;
            a = b;
            b = aux;
        }

        // Check 2 : Solution possible : For Bisection method, f(a) and f(b) must have different sign
        // In the other case, the method trow a error invalid argument.
        if (GetFValue(a) * GetFValue(b) > 0) {
            throw std::invalid_argument("f(a)*f(b) >0 , can't do the Bisection method");
        }

        //Check Direct Solution for lower bound
        if (GetFValue(a) == 0) {
            std::cout << "A Solution is the lowerBound : x= " << a << std::endl;
            return;
        }
        //Check Direct Solution for upper bound
        if (GetFValue(b) == 0) {
            std::cout << "A Solution is the Upperbound : x= " << b << std::endl;
            return;
        }

        //Initialize
        double aux = (a + b) / 2;
        double res = (b - a) / 2;
        int it = 1;

        // It take the medium of the interval each time until they reach the desired tolerance
        // By
        while (res > tolerance && it < maxIter) {

            // Check if we found a exact solution
            if (GetFValue(aux) == 0) {
                std::cout << "Exact solution founded after  " << it << " iterations " << std::endl;
                std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
                return;
            }

            // Compare the medium of the interval with the bound to update the new interval
            if (GetFValue(a) * GetFValue(aux) < 0) { b = aux; }
            else if (GetFValue(b) * GetFValue(aux) < 0) { a = aux; }
            else {
                std::cout << "Bisection Algorithm not operating correctly" << std::endl;
                return;
            }

            //Take the new medium of the interval
            aux = (a + b) / 2;
            //Update the residu
            res /= 2;
            //Update the iteration
            it += 1;
        }

        // Trowing error for not converging after the given max iteration
        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(aux) + " and f(x) = " + std::to_string(GetFValue(aux)));
            throw ExceptionIterate(message);
        }
        // Throwing error for converging to a wrong solution
        else if (std::abs(GetFValue(aux)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + " x = " + std::to_string(aux) + " and f(x) = " +
                                std::to_string(GetFValue(aux)));
            throw ExceptionIterate(message);
        }
        // else : printing the converged solution
        else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
        }

    }
    // Catch for the throw error
    catch(std::invalid_argument &e){std::cout<<e.what()<<std::endl;}
    catch (ExceptionIterate(&e)){ e.what(); }
}


