//
// Created by lleguill on 14.12.21.
//

#ifndef PCSC_PROJECT_FIXTURETEST_H
#define PCSC_PROJECT_FIXTURETEST_H

/**
 * Fixture class to do the Test.
 * It use Set Up to initialise the calculation and make the test.ccp more clear
 */
class Fixture_Solve : public testing::Test{
protected:
    /// Setup :choose the method and return the result
    void SetUp(std::string sfun, std::string sdfun, double initialVal, double tol, int Maxit,
               double lowerbound, double upperbound,const std::string& met);

    ///Tear down (empty for the moment)


public:
    ///Get the result for the assertion Test
    double getResult() const;
    ///Get the throw for Assert exception
    const retVals &getRetMethod() const;

private:
    AbstractNode* f ;
    AbstractNode* df ;
    // Retuned by the method
    struct retVals ret_method;
    //What we want for the Google Test
    double result ;
};



void Fixture_Solve::SetUp(std::string sfun, std::string sdfun, double initialVal, double tol, int maxit,
                          double lowerbound, double upperbound,const std::string& met) {
    f=Solver::strToFun(std::move(sfun));
    df=Solver::strToFun(std::move(sdfun));

    if ("Newton"==met){
        Newton aux(f,df,initialVal,tol,maxit);
        ret_method=aux.SolveEquation();
        result = aux.GetFValue(ret_method.result);
    }else if ("FixedPoint" == met){
        ClassicChord aux(f,initialVal,tol,maxit);
        ret_method=aux.SolveEquation();
        result = aux.GetFValue(ret_method.result);
    }else if ("Chord" == met ){
        ClassicChord aux(f,initialVal,tol,maxit);
        ret_method=aux.SolveEquation();
        result = aux.GetFValue(ret_method.result);
    }else if ("Bisection" == met){
        Bisection aux(f,tol,maxit,lowerbound,upperbound);
        ret_method=aux.SolveEquation();
        result = aux.GetFValue(ret_method.result);
    }

}

double Fixture_Solve::getResult() const {
    return result;
}

const retVals &Fixture_Solve::getRetMethod() const {
    return ret_method;
};


#endif //PCSC_PROJECT_FIXTURETEST_H
