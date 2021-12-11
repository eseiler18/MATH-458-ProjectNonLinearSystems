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
            aux = newt.SolveEquation();
            std::cout<<"Return test for Google, x = "<<aux<<std::endl<<std::endl;
        }if (data->method["Bisection"]){
            Bisection bisec(data);
            aux =bisec.SolveEquation();
            std::cout<<"Return test for Google, x = "<<aux<<std::endl<<std::endl;
        }if (data->method["Chord"]){
            ClassicChord chrd(data);
            aux =chrd.SolveEquation();
            std::cout<<"Return test for Google, x = "<<aux<<std::endl<<std::endl;
        }if (data->method["FixedPoint"]){
            FixedPoint fxdp(data);
            aux = fxdp.SolveEquation();
            std::cout<<"Return test for Google, x = "<<aux<<std::endl<<std::endl;
        }
        std::cout<<std::endl;
        delete data;
    }




    return 0;
}