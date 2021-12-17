//
// Created by lleguill on 01.12.21.
//

#include <iostream>
#include "solverMethods/Bisection.h"
#include "solverMethods/FixedPoint.h"
#include "solverMethods/Newton.h"
#include "solverMethods/ClassicChord.h"
#include "readData/ReaderData.h"

// read the csv file and solve for each lignes
int main(int argc , char* argv[]) {
    if(argc>2){
        std::cout << "Error the main can only take one argument (one csv file) beut there is: " << argc <<
        "arguments" << std::endl;
        return 0;
    }
    // Get the csv file in argument
    std::string pathCSV;
    if(argc==2){
        std::cout << "Lecture of the csv file at path: " << argv[1] << std::endl;
        pathCSV = argv[1];
    }
    // if no argument, take the "data.csv by default"
    if(argc==1){
        std::cout << "Lecture of the default csv file in MATH-458-ProjectNonLinearSystems folder : data.csv"<<std::endl;
        pathCSV = "data.csv";
    }
    //Create a class reader with the correspondant csv
    ReaderData reader(pathCSV);
    //Data struct that stores all the features
    std::vector<Data*> allData = reader.readAllData();
    //auxiliaire value that store answer
    retVals aux;
    // counter of lignes
    int cnt=0;
    
    for (Data* data: allData){
        cnt++;
        std::cout<<"------------------------------";
        std::cout<<"\nFunction #"<<cnt<<std::endl;
        
        // If can't make any method for a given function, warn the user.
        if (!data->method["Newton"] && !data->method["Bisection"] &&
            !data->method["Chord"] && !data->method["FixedPoint"]){
            std::cout << "Can't do methods read warning and verify input in the file" << std::endl;
        }
        
        // If can do a method, create the correspondant solver. Catch specific error when solving.
        
        //Newton
        if (data->method["Newton"]){
            std::cout << "\nNewton Method with Aitken acceleration :" << std::endl;
            try {
                //Create solver
                Newton newt(data);
                //solve
                aux = newt.SolveEquation();
                //print solution (it anything was throw)
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << newt.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << newt.GetFValue(aux.result) << std::endl;
            }
            //Catch specific error
            catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl;}
    
        //Bisection   
        }if (data->method["Bisection"]){
            std::cout << "\nBisection Method :" << std::endl;
            try {
                Bisection bisec(data);
                aux = bisec.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << bisec.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << bisec.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }
        
        //Chord
        }if (data->method["Chord"]) {
            std::cout << "\nClassic Chord Method with Aikten acceleration:" << std::endl;
            try {
                ClassicChord chrd(data);
                aux = chrd.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << chrd.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << chrd.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }
        
        // Fixed Point
        }if (data->method["FixedPoint"]){
            std::cout << "\nFixed Point Method with Aitken acceleration :" << std::endl;
            try {
                FixedPoint fxdp(data);
                aux = fxdp.SolveEquation();
                std::cout << "Converge after " << aux.it << " iterations for a tolerance of " << fxdp.GetTol() << std::endl;
                std::cout << "x = " << aux.result << " and f(x) = " << fxdp.GetFValue(aux.result) << std::endl;
            }catch (std::invalid_argument(&e)) { std::cout << e.what() << std::endl; }
            catch (ExceptionIterate(&e)){ std::cout << e.what() << std::endl; }
        }
        std::cout<<std::endl;
        
        //Delete the structure
        delete data;
    }
    return 0;
}
