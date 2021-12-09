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

    std::vector<Data*> allData = ReaderData::readAllData(("data.csv"));
    int cnt=0;
    for (Data* data: allData){
        cnt++;
        std::cout<<"\nFunction #"<<cnt<<std::endl;
        if (data->method["Newton"]==false && data->method["Bisection"]==false &&
            data->method["Chord"]==false && data->method["FixedPoint"]==false){
            std::cout << "Can't do all methods read warning and verify input in the file" << std::endl;
        }
        if (data->method["Newton"]){
            Newton newt(data);
            newt.SolveEquation();
        }if (data->method["Bisection"]){
            Bisection bisec(data);
            bisec.SolveEquation();
        }if (data->method["Chord"]){
            ClassicChord chrd(data);
            chrd.SolveEquation();
        }if (data->method["FixedPoint"]){
            FixedPoint fxdp(data);
            fxdp.SolveEquation();
        }
        std::cout<<std::endl;
        delete data;
    }




    return 0;
}