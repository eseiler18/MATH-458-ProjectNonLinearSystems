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
        std::cout << "Classic Chord Method with Aikten acceleration:" << std::endl;
        int it = 1;
        double xPrev = initialValue;
        double m = 0.1;
        double x = xPrev - m * GetFValue(xPrev); //first iteration with m=0.1
        double xNext;
        double Ax;
        double res = std::abs(x - xPrev);

        while (res > tolerance && it < maxIter) {
            m = (x - xPrev) / (GetFValue(x) - GetFValue(xPrev));
            xNext = x - m * GetFValue(x);
            xPrev = x;
            x = xNext;
            m = (x - xPrev) / (GetFValue(x) - GetFValue(xPrev));
            xNext = x - m * GetFValue(x);
            Ax = xNext - pow(xNext - x, 2) / (xNext + xPrev - 2 * x);
            res = std::abs(Ax - xNext);
            it += 1;
            xPrev = xNext;
            x = Ax;
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
    catch (ExceptionIterate(&e)){ e.what(); }
    catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
}

