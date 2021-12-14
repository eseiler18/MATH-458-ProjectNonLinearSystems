//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "solverMethods/Bisection.h"
#include "solverMethods/FixedPoint.h"
#include "solverMethods/Newton.h"
#include "solverMethods/ClassicChord.h"
#include "readData/ReaderData.h"


int main() {
    ReaderData reader("data.csv");
    std::vector<Data*> allData = reader.readAllData();
    retVals aux;
    int cnt=0;
    for (Data* data: allData){
        cnt++;
        std::cout<<"------------------------------";
        std::cout<<"\nFunction #"<<cnt<<std::endl;
        if (!data->method["Newton"] && !data->method["Bisection"] &&
            !data->method["Chord"] && !data->method["FixedPoint"]){
            std::cout << "Can't do methods read warning and verify input in the file" << std::endl;
        }
        if (data->method["Newton"]){
            std::cout << "\nNewton Method with Aitken acceleration :" << std::endl;
            Newton newt(data);
            try {
                aux = newt.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << newt.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << newt.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["Bisection"]){
            std::cout << "\nBisection Method :" << std::endl;
            Bisection bisec(data);
            try {
                aux = bisec.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << bisec.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << bisec.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }

        }if (data->method["Chord"]) {
            std::cout << "\nClassic Chord Method with Aikten acceleration:" << std::endl;
            ClassicChord chrd(data);
            try {
                aux = chrd.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << chrd.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << chrd.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["FixedPoint"]){
            std::cout << "\nFixed Point Method with Aitken acceleration :" << std::endl;
            FixedPoint fxdp(data);
            try {
                aux = fxdp.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << fxdp.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << fxdp.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }
        std::cout<<std::endl;
        delete data;
    }
    return 0;
}