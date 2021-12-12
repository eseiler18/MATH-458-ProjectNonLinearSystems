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
    try {
        std::cout << "Newton Method with Aitken acceleration :" << std::endl;
        //Initialisation
        int it = 1;
        double res = tolerance + 1;
        double xPrev = initialValue;
        double x;
        double xNext;
        double Ax;

        // Don't stop until we reach the desired tolerance or the max iteration
        while (res > tolerance && it < maxIter) {
            //Newton update for x(n)
            x = xPrev - GetFValue(xPrev) / GetDfValue(xPrev);
            //Newton update for x(n+1)
            xNext = x - GetFValue(x) / GetDfValue(x);
            //Aitken Update
            Ax = xNext - pow(xNext - x,2)/(xNext + xPrev -2*x);

            //Check if we found exact solution
            if (GetDfValue(Ax)==0){
                break;
            }

            //residual
            res = std::abs(Ax - xNext);

            // Update iteration
            it += 1;
            // Update value
            xPrev = Ax;
        }

        // Trowing error for not converging after the given max iteration
        if (it >= maxIter) {
            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
                                std::to_string(res) + "x = "
                                + std::to_string(Ax) + " and f(x) = " + std::to_string(GetFValue(Ax)));
            throw ExceptionIterate(message);
        }
        // Throwing error for converging to a wrong solution
        else if (std::abs(GetFValue(Ax)) > tolerance * 10) {
            std::string message("Converge to a wrong solution after " + std::to_string(it) +
                                " iterations for a tolerance of " + std::to_string(tolerance) +
                                ".\nDifference of successive iterates = "
                                + std::to_string(res) + " x = " + std::to_string(Ax) + " and f(x) = " +
                                std::to_string(GetFValue(Ax)));
            throw ExceptionIterate(message);
        }
        // else : printing the converged solution
        else {
            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
            std::cout << "x = " << Ax << " and f(x) = " << GetFValue(Ax) << std::endl;
            return Ax;
        }
    }
    // Catch for the throw error
    catch (ExceptionIterate(&e)){ e.what(); }
    catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
    return 0;
}


