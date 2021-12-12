//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "Bisection.h"
#include "FixedPoint.h"
#include "readData/ReaderData.h"
#include "Newton.h"
#include "ClassicChord.h"






int main() {
    /*
    AbstractNode* fun = Solver::strToFun("(x*3 +7)/0");
    fun->solve(8);


    AbstractNode* fun = Solver::strToFun("x*3 +7");
    AbstractNode* dfun = Solver::strToFun("3");
    Bisection c(fun,0.0001,1000,-10,30);
    //c.SolveEquation();
    Newton n(fun,dfun,-3,0.00001,1000);
    //n.SolveEquation();
    std::string frappe("x*3 +7");
    std::string dfrappe("3");


    Data bisec;
    bisec.lowerBound= -10;
    bisec.upperBound=10 ;
    bisec.initialValue= 23;
    bisec.tolerance =-1;
    bisec.maxIter = 1000 ;
    bisec.fun = Solver::strToFun(frappe);
    bisec.dFun = Solver::strToFun(dfrappe);

    //Newton d(&t);

    Newton BB(&bisec);
    BB.SolveEquation();
    */
    AbstractNode* f = Solver::strToFun("x^2 -1");
    AbstractNode* df = Solver::strToFun("2*x");
    Newton n(f,df,5,0.0001,10000);
    n.SolveEquation();

    double aux;
    std::vector<Data*> allData = ReaderData::readAllData(("data.csv"));
    int cnt=0;
    for (Data* data: allData){
        cnt++;
        std::cout<<"------------------------------";
        std::cout<<"\nFunction #"<<cnt<<std::endl;
        if (!data->method["Newton"] && !data->method["Bisection"] &&
            !data->method["Chord"] && !data->method["FixedPoint"]){
            std::cout << "Can't do all methods read warning and verify input in the file" << std::endl;
        }
        if (data->method["Newton"]){
            Newton newt(data);
            try {
                aux = newt.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["Bisection"]){
            Bisection bisec(data);
            try {
                aux = bisec.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }

        }if (data->method["Chord"]) {
            ClassicChord chrd(data);
            try {
            aux = chrd.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["FixedPoint"]){
            FixedPoint fxdp(data);
            try {
                aux = fxdp.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }
        std::cout<<std::endl;
        delete data;
    }




    return 0;
}