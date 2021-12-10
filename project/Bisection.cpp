//
// Created by lleguill on 01.12.21.
//

#include "Bisection.h"
#include <cassert>

Bisection::Bisection() =default;

Bisection::Bisection(Data *data) {
    if (data->method["Bisection"]) {
        *this = Bisection(data->fun, data->tolerance, data->maxIter,
                          data->lowerBound, data->upperBound);
    } else {
        throw std::invalid_argument("Dont fit with Bisection");
    }
}

Bisection::Bisection(AbstractNode* fun,double tol, int Maxit, double lowerbound, double upperbound) :
    AbstractSolver(fun,tol,Maxit), lowerBound(lowerbound),upperBound(upperbound) {}

Bisection::~Bisection() =default;

void Bisection::SolveEquation() const {
    try {
        double b = upperBound;
        double a = lowerBound;
        std::cout << "Bisection Method :" << std::endl;

        //check 1 : Bound viability
        if (b < a) {
            std::cout << "Higher bound is smaller than lower bound, bounds inverted for the calculation. " << std::endl;
            double aux = a;
            a = b;
            b = aux;
        }

        //check 2 : Solution possible ?
        //assert(GetFValue(a)* GetFValue(b)<0);
        if (GetFValue(a) * GetFValue(b) > 0) {
            throw std::invalid_argument("f(a)*f(b) >0 , can't do the Bisection method");
        }

        //check Direct Solution
        if (GetFValue(a) == 0) {
            std::cout << "A Solution is the lowerBound : x= " << a << std::endl;
            return;
        }
        if (GetFValue(b) == 0) {
            std::cout << "A Solution is the Upperbound : x= " << b << std::endl;
            return;
        }

        //Initialise
        double aux = (a + b) / 2;
        double res = (b - a) / 2;
        int it = 1;

        while (res > tolerance && it < maxIter) {
            if (GetFValue(aux) == 0) {
                std::cout << "Exact solution founded after  " << it << " iterations " << std::endl;
                std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
                return;
            }

            if (GetFValue(a) * GetFValue(aux) < 0) { b = aux; }
            else if (GetFValue(b) * GetFValue(aux) < 0) { a = aux; }
            else {
                std::cout << "Bisection Algorithm not operating correctly" << std::endl;
                return;
            }
            aux = (a + b) / 2;
            res /= 2;
            it += 1;
        }

        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(aux) + " and f(x) = " + std::to_string(GetFValue(aux)));
            throw ExceptionIterate(message);
        } else if (std::abs(GetFValue(aux)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + " x = " + std::to_string(aux) + " and f(x) = " +
                                std::to_string(GetFValue(aux)));
            throw ExceptionIterate(message);
        } else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << aux << " and f(x) = " << GetFValue(aux) << std::endl;
        }

    }
    catch(std::invalid_argument &e){std::cout<<e.what()<<std::endl;}
    catch (ExceptionIterate(&e)){ e.what(); }
}


