//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#include "ClassicChord.h"

//Constructor
ClassicChord::ClassicChord() = default;
ClassicChord::ClassicChord(AbstractNode* fun, double intialval, double tol, int Maxit) :
    AbstractSolver(fun,tol,Maxit), initialValue(intialval){}

ClassicChord::ClassicChord(Data *data) {
    if (data->method["Chord"]) {
        *this =ClassicChord(data->fun,data->initialValue,
                          data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Dont fit with Classic Chord Method");
    }
}

//Destructor
ClassicChord::~ClassicChord() = default;

//Equation Solver
void ClassicChord::SolveEquation() const {
    try {
        int it = 1;
        double xPrev = initialValue;
        double m = 0.1;
        double x = xPrev - m * GetFValue(xPrev); //first iteration with m=0.1
        double xNext;
        double res = std::abs(x - xPrev);

        while (res > tolerance && it < maxIter) {
            m = (x - xPrev) / (GetFValue(x) - GetFValue(xPrev));
            xNext = x - m * GetFValue(x);
            res = std::abs(xNext - x);
            it += 1;
            xPrev = x;
            x = xNext;
        }
        std::cout << "Classic Chord Method :" << std::endl;
        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(xNext) + " and f(x) = " + std::to_string(GetFValue(xNext)));
            throw ExceptionIterate(message);
        } else if (std::abs(GetFValue(xNext)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + "x = " + std::to_string(xNext) + " and f(x) = " +
                                std::to_string(GetFValue(xNext)));
            throw ExceptionIterate(message);
        } else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
        }
    }
    catch (ExceptionIterate(&e)){ e.what(); }
    catch (std::invalid_argument(&e)){ e.what(); }
}

