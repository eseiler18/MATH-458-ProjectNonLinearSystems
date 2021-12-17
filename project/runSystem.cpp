#include <iostream>
#include "solverMethods/NewtonSystem.h"
#include "readData/parser/Solver.h"
#include "solverMethods/ExceptionIterate.h"

int main(int argc , char* argv[]) {
    try {
        // Two variable sytem
        int nbVariable = 2;
        double x[2] = {2.0, 3.0};
        
        // Construc the Abstract node from the matematical expression
        AbstractNode *f1 = Solver::strToFun("x0^2+x0*x1-10");
        AbstractNode *f2 = Solver::strToFun("x1+3*x0*x1^2-57");
        
        Eigen::VectorX<AbstractNode *> F(nbVariable);
        F(0) = f1;
        F(1) = f2;
        
        // Construct the correspondnat Jacobian
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
        
        // construct the Solver
        NewtonSystem sys(nbVariable, F, J, 0.00000001, 10000, x0);
        //Solve the System
        double *xRes = sys.solveSystem();
        
        //Get the result for each variables
        std::string resultStr;
        std::string FResultStr;
        for (int i=0 ; i<nbVariable;i++){
            resultStr.append(std::to_string(xRes[i]));
            FResultStr.append(std::to_string(sys.getFValue(xRes)(i)));
            resultStr.append(",");
            FResultStr.append(",");
        }
        // Print result
        std::cout << "Converge after " << sys.getMaxIter() << " iterations for a tolerance of " <<
        sys.getTolerance() << std::endl;
        std::cout << "x = " << resultStr << " and f(x) = " << FResultStr << std::endl;
    }
    
    // Catch wrong answer exeption
    catch(ExceptionIterate &e) {std::cout << e.what() << std::endl;}
    //Catch error in the construction of the function
    catch (ParserException &e) {std::cout << e.what() << std::endl;}
    // Catch wrong argument
    catch (std::invalid_argument &e) {std::cout << e.what() << std::endl;}
}
