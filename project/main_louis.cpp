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
    struct retVals aux;
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
            std::cout << "\nNewton Method with Aitken acceleration :" << std::endl;
            Newton newt(data);
            try {
                aux = newt.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["Bisection"]){
            std::cout << "\nBisection Method :" << std::endl;
            Bisection bisec(data);
            try {
                aux = bisec.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }

        }if (data->method["Chord"]) {
            std::cout << "\nClassic Chord Method with Aikten acceleration:" << std::endl;
            ClassicChord chrd(data);
            try {
            aux = chrd.SolveEquation();
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ e.what(); }
        }if (data->method["FixedPoint"]){
            std::cout << "\nFixed Point Method with Aitken acceleration :" << std::endl;
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