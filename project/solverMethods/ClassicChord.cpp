//
// Created by eseiler@INTRANET.EPFL.CH on 28.11.21.
//

#include "ClassicChord.h"

// Default empty constructor
ClassicChord::ClassicChord() = default;

// The constructor with data call the constructor with all separated input.
// It also verify the comptability with the classic chord method
ClassicChord::ClassicChord(Data *data) {
    if (data->method["Chord"]) {
        *this =ClassicChord(data->fun,data->initialValue,
                            data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Dont fit with Classic Chord Method");
    }
}
// Classic constructor
ClassicChord::ClassicChord(AbstractNode* fun, double intialval, double tol, int Maxit) :
    AbstractSolver(fun,tol,Maxit), initialValue(intialval){}

// Default destructor
ClassicChord::~ClassicChord() = default;


// Solving method
double ClassicChord::SolveEquation() const {
    std::cout << "\nClassic Chord Method with Aikten acceleration:" << std::endl;
    //Initialise
    int it = 1;
    double xPrev = initialValue;
    double m = 0.1;
    double x = xPrev - m * GetFValue(xPrev); //first iteration with m=0.1
    double xNext;
    double Ax;
    double res = std::abs(x - xPrev);
    double result;

    // Don't stop until we reach the desired tolerance or the max iteration
    while (res > tolerance && it < maxIter) {
        // Check divide by 0
        if (GetFValue(x) == 0 && GetFValue(xPrev)==0){
            result = x;
            break;
        }
        // m update for iteration n
        m = (x - xPrev) / (GetFValue(x) - GetFValue(xPrev));
        // chord update for x(n)
        xNext = x - m * GetFValue(x);

        // Update value for the n+1 iteration ( for Aitken )
        xPrev = x;
        x = xNext;

        // Check divide by 0
        if (GetFValue(x) == 0 && GetFValue(xPrev)==0){
            result = x;
            break;
        }
        // m update for iteration n+1
        m = (x - xPrev) / (GetFValue(x) - GetFValue(xPrev));
        // chord update for x(n+1)
        xNext = x - m * GetFValue(x);
        if ((xNext ==0 && x==0 && xPrev==0) || std::isinf(xNext) || std::isinf(xPrev) || std::isinf(x)) {
            result = xNext;
            break;
        }
        // Aitken update
        Ax = xNext - pow(xNext - x, 2) / (xNext + xPrev - 2 * x);

        // update residual : the difference between two successive iterate
        res = std::abs(Ax - xNext);

        // Update value & iterator
        it += 1;
        xPrev = xNext;
        x = Ax;
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

