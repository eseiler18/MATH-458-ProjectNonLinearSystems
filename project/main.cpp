#include <iostream>
#include "solverMethods/NewtonSystem.h"
#include "readData/InterpreterInputFunction.h"
#include "readData/parser/Solver.h"
#include "solverMethods/ExceptionIterate.h"

int main(int argc , char* argv[]) {
    try {
        int nbVariable = 2;
        double x[2] = {2.0, 3.0};
        AbstractNode *f1 = Solver::strToFun("x0^2+x0*x1-10");
        AbstractNode *f2 = Solver::strToFun("x1+3*x0*x1^2-57");
        Eigen::VectorX<AbstractNode *> F(nbVariable);
        F(0) = f1;
        F(1) = f2;
        AbstractNode *f1dx = Solver::strToFun("2x0+x1");
        AbstractNode *f2dx = Solver::strToFun("3*x1^2");
        AbstractNode *f1dy = Solver::strToFun("x0");
        AbstractNode *f2dy = Solver::strToFun("1+3*x0*x1");
        Eigen::MatrixX<AbstractNode *> J(nbVariable, nbVariable);
        J(0, 0) = f1dx;
        J(0, 1) = f1dy;
        J(1, 0) = f2dx;
        J(1, 1) = f2dy;
        double x0[2] = {10, 5};
        NewtonSystem sys(nbVariable, F, J, 0.00000001, 10000, x0);
        double *xRes = sys.solveSystem();
        std::string resultStr;
        std::string FResultStr;
        for (int i=0 ; i<nbVariable;i++){
            resultStr.append(std::to_string(xRes[i]));
            FResultStr.append(std::to_string(sys.getFValue(xRes)(i)));
            resultStr.append(",");
            FResultStr.append(",");
        }
        std::cout << "Converge after " << sys.getMaxIter() << " iterations for a tolerance of " <<
        sys.getTolerance() << std::endl;
        std::cout << "x = " << resultStr << " and f(x) = " << FResultStr << std::endl;
    }
    catch(ExceptionIterate &e) {e.what();}
    catch (ParserException &e) {std::cout << e.what() << std::endl;}
    catch (std::invalid_argument &e) {std::cout << e.what() << std::endl;}
}