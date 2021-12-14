//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "solverMethods/Bisection.h"
#include "solverMethods/FixedPoint.h"
#include "solverMethods/Newton.h"
#include "solverMethods/ClassicChord.h"
#include "readData/ReaderData.h"


int main(int argc , char* argv[]) {
    if(argc>2){
        std::cout << "Error the main can only take one argument (one csv file) beut there is: " << argc <<
        "arguments" << std::endl;
        return 0;
    }
    std::string pathCSV;
    if(argc==2){
        std::cout << "Lecture of the csv file at path: " << argv[1] << std::endl;
        pathCSV = argv[1];
    }
    if(argc==1){
        std::cout << "Lecture of the default csv file in MATH-458-ProjectNonLinearSystems folder : data.csv"<<std::endl;
        pathCSV = "data.csv";
    }
    ReaderData reader(pathCSV);
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
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl;}
        }if (data->method["Bisection"]){
            std::cout << "\nBisection Method :" << std::endl;
            Bisection bisec(data);
            try {
                aux = bisec.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << bisec.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << bisec.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }

        }if (data->method["Chord"]) {
            std::cout << "\nClassic Chord Method with Aikten acceleration:" << std::endl;
            ClassicChord chrd(data);
            try {
                aux = chrd.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << chrd.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << chrd.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }
        }if (data->method["FixedPoint"]){
            std::cout << "\nFixed Point Method with Aitken acceleration :" << std::endl;
            FixedPoint fxdp(data);
            try {
                aux = fxdp.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << fxdp.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << fxdp.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }
        }
        std::cout<<std::endl;
        delete data;
    }
    return 0;
}