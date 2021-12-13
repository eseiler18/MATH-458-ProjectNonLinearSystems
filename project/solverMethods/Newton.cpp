//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "Newton.h"

// Default empty constructor
Newton::Newton() = default;

// The constructor with data call the constructor with all separated input.
// It also verifies the compatibility of arguments with the newton method
Newton::Newton(Data *data) {
    if (data->method["Newton"]) {
        *this =Newton(data->fun, data->dFun, data->initialValue,
                      data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Argument are not valid for Newton method verify warning and input in the file");
    }
}
// Classic constructor
Newton::Newton(AbstractNode* fun, AbstractNode* dfun, double intialvalue, double tol, int maxIt)
    : AbstractSolver(fun,tol,maxIt), df(dfun), initialValue(intialvalue){}

// Default destructor
Newton::~Newton() = default;


// Solving method
double Newton::SolveEquation() const {
    std::cout << "\nNewton Method with Aitken acceleration :" << std::endl;
    //Initialisation
    int it = 1;
    double res = tolerance + 1;
    double xPrev = initialValue;
    double x;
    double xNext;
    double Ax;
    double result;

    // Don't stop until we reach the desired tolerance or the max iteration
    while (res > tolerance && it < maxIter) {
        //Newton update for x(n)
        if (GetDfValue(xPrev)==0){
            result = xPrev;
            break;
        }
        x = xPrev - GetFValue(xPrev) / GetDfValue(xPrev);
        //Newton update for x(n+1)
        if (GetDfValue(x)==0){
            result = x;
            break;
        }
        xNext = x - GetFValue(x) / GetDfValue(x);
        //Aitken Update
        if ((xNext ==0 && x==0 && xPrev==0) || std::isinf(xNext) || std::isinf(xPrev) || std::isinf(x)) {
            result = xNext;
            break;
        }
        Ax = xNext - pow(xNext - x,2)/(xNext + xPrev -2*x);

        //residual
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

