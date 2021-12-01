//
// Created by eseiler@INTRANET.EPFL.CH on 27.11.21.
//

#ifndef PROJECT_ABSTRACTSOLVER_H
#define PROJECT_ABSTRACTSOLVER_H
#include <iostream>

class AbstractSolver {
public:
    // Constructor and destructor
    AbstractSolver();
    virtual ~AbstractSolver();

    // Setter
    void SetInterval(const double a, const double b) {lowerBound = a; upperBound = b; }
    void SetInitialValue(const double x0) {initialValue = x0; }
    void SetTol(const double tol) {tolerance = tol; }
    void SetMaxIter(const int nMax) {maxIter = nMax; }
    void SetF(double (*fun)(double x)) {f = fun; }
    void SetDf(double (*fun)(double x)) {df = fun; }

    // Getter
    double GetLowerBound() const { return lowerBound; }
    double GetUpperBound() const { return upperBound; }
    double GetInitialValue() const { return initialValue; }
    double GetTol() const { return tolerance; }
    int GetMaxIter() const { return maxIter; }

    //Get functions value methods
    double GetFValue(double x) const { return f(x); }
    double GetDfValue(double x) const { return df(x); }

    // Solver methods (Pure Virtual)
    virtual void SolveEquation() const = 0;

protected:
    double lowerBound;
    double upperBound;
    double initialValue;
    double tolerance;
    int maxIter;
    double (*f)(double x);
    double (*df)(double x);
};

#endif //PROJECT_ABSTRACTSOLVER_H
