//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#include "Newton.h"

Newton::Newton() = default;

Newton::Newton(Data *data) {
    if (data->method["Newton"]) {
        *this =Newton(data->fun, data->dFun, data->initialValue,
                      data->tolerance,data->maxIter);
    }else{
        throw std::invalid_argument("Argument are not valid for Newton method verify warning and input in the file");
    }
}

Newton::Newton(AbstractNode* fun, AbstractNode* dfun, double intialvalue, double tol, int maxIt)
    : AbstractSolver(fun,tol,maxIt), df(dfun), initialValue(intialvalue){}

Newton::~Newton() = default;


//void Newton::SolveEquation() const {
//    try {
//        std::cout << "Newton Method :" << std::endl;
//        int it = 1;
//        double res = tolerance + 1;
//        double xPrev = initialValue;
//        double xNext;
//        while (res > tolerance && it < maxIter) {
//            xNext = xPrev - GetFValue(xPrev) / GetDfValue(xPrev);
//            res = std::abs(xPrev - xNext);
//            it += 1;
//            xPrev = xNext;
//        }
//
//        if (it >= maxIter) {
//            std::string message("Didn't converge after " + std::to_string(it) + " iterations for a tolerance of "
//                                + std::to_string(tolerance) + ".\nDifference of successive iterates = " +
//                                std::to_string(res) + "x = "
//                                + std::to_string(xNext) + " and f(x) = " + std::to_string(GetFValue(xNext)));
//            throw ExceptionIterate(message);
//        } else if (std::abs(GetFValue(xNext)) > tolerance * 10) {
//            std::string message("Converge to a wrong solution after " + std::to_string(it) +
//                                " iterations for a tolerance of " + std::to_string(tolerance) +
//                                ".\nDifference of successive iterates = "
//                                + std::to_string(res) + " x = " + std::to_string(xNext) + " and f(x) = " +
//                                std::to_string(GetFValue(xNext)));
//            throw ExceptionIterate(message);
//        } else {
//            std::cout << "Converge after " << it << " iterations for a tolerance of " << tolerance << std::endl;
//            std::cout << "x = " << xNext << " and f(x) = " << GetFValue(xNext) << std::endl;
//        }
//    }
//    catch (ExceptionIterate(&e)){ e.what(); }
//    catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
//}

void Newton::SolveEquation() const {
    try {
        std::cout << "Newton Method with Aitken acceleration :" << std::endl;
        int it = 1;
        double res = tolerance + 1;
        double xPrev = initialValue;
        double x;
        double xNext;
        double Ax;
        while (res > tolerance && it < maxIter) {
            x = xPrev - GetFValue(xPrev) / GetDfValue(xPrev);
            xNext = x - GetFValue(x) / GetDfValue(x);
            Ax = xNext - pow(xNext - x,2)/(xNext + xPrev -2*x);
            res = std::abs(Ax - xNext);
            it += 1;
            if (GetDfValue(Ax)==0){
                break;
            }
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
    catch (ExceptionIterate(&e)){ e.what(); }
    catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
}


