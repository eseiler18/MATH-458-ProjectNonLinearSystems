//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>      // dynamic library loading, dlopen() etc
#include "ReaderData.h"
//#include "../parser/ExtrernalFunctionNode.h"
#include "InterpreterInputFunction.h"
#include "parser/ParserException.h"

ReaderData::ReaderData(const std::string& pathOfCsv):pathOfCsv(pathOfCsv) {
    // Open an existing and non-empty file
    csv.open(pathOfCsv, std::ios::in);
    // verify existence
    if (!csv.is_open()) {
        throw std::invalid_argument("Invalid path: " + pathOfCsv + ". File can't be open doesn't exit.");
    }
    // verify if file is empty
    if (ReaderData::isEmptyFile(csv)) {
        throw std::invalid_argument("Invalid file: " + pathOfCsv + ". File exist but it's empty.");
    }
}


void ReaderData::readIntervalBiSection(std::vector<std::string>& row, Data* data) const {
    if (!data->method["Bisection"]) {
        // only available for BISECTION
        return;
    }
    // interval
    if (row[3].empty() || row[4].empty()) {
        // verify emptiness
        std::cout << "Warning line " + std::to_string(currentLine) + ": lowerBound and upperBound must be filled" +
                     ". Can't use bisection method" << std::endl;
        data->method["Bisection"] = false;
    } else if(isNumber(row[3]) && isNumber(row[4])){
        data->lowerBound = atof(row[3].c_str());
        data->upperBound = atof(row[4].c_str());
    }
    else{
        // exception if the cell is not a number
        throw std::invalid_argument("Invalid cell in csv file at line " + std::to_string(currentLine)
                                        + ": " + row[3] +" and "+ row[4] +" must be numbers.");
    }

}

void ReaderData::readInitialValue(std::vector<std::string>& row, Data* data) const {
    // only available for newton, fixed point and chord methods
    if (data->method["Newton"] || data->method["FixedPoint"] || data->method["Chord"]) {
        // verify emptiness
        if (row[5].empty()) {
            std::string methodCantDo;
            if (data->method["Newton"]) {
                data->method["Newton"] = false;
                methodCantDo = "Newton";
            }
            if (data->method["FixedPoint"]) {
                data->method["FixedPoint"] = false;
                if (methodCantDo.empty()) {
                    methodCantDo += "fixed point";
                } else {
                    methodCantDo += ", fixed point";
                }
            }
            if (data->method["Chord"]) {
                data->method["Chord"] = false;
                if (methodCantDo.empty()) {
                    methodCantDo += "Chord";
                } else {
                    methodCantDo += ", chord";
                }
            }
            std::cout << "Warning line " + std::to_string(currentLine) + ": initial value is empty" +
                         ". Can't use " + methodCantDo + " methods" << std::endl;
        }
        else if(isNumber(row[5])){
                data->initialValue = atof(row[5].c_str());
        }
        else{
            // exception if the cell is not a number
            throw std::invalid_argument("Invalid cell in csv file at line " + std::to_string(currentLine)
                                            + ": " + row[5] + " should be a number.");
        }
    }
}


Data* ReaderData::createDataRow(std::vector<std::string>& row) {
    try {
        Data *data = new Data;
        // methods
        if (row[0].empty()) {
            data->method["Newton"] = true;
            data->method["Chord"] = true;
            data->method["FixedPoint"] = true;
            data->method["Bisection"] = true;
        } else {
            fillChosenMethod(data, row[0]);
        }

        // function
        if (row[1].empty()) {
            throw std::invalid_argument("Invalid cell in csv file: data must have a function"
                                        ", first column can't be empty at line " + std::to_string(currentLine));
        }
        const char* externalFunctionCppFile=nullptr;
        if (row.size()!=9){
            // case when the function is given with string expression (no external file)
            data->fun = InterpreterInputFunction::strToFun(row[1]);
        }
        else{
            // case when the function is given with c++ code in an external file
            data->fun = InterpreterInputFunction::functionExternalCFile(row[8], row[1]);
        }
        // derivative
        if (data->method["Newton"]) {
            if (row[2].empty()) {
                std::cout << "Warning line " + std::to_string(currentLine) + ": derivative is empty"
                             + ". Can't use Newton method" << std::endl;
                data->method["Newton"] = false;
            } else {
                if (row.size()!=9){
                    // case when the function is given with string expression (no external file)
                    data->dFun = InterpreterInputFunction::strToFun(row[2]);
                }
                else{
                    // case when the function is given with c++ code in an external file
                    data->dFun = InterpreterInputFunction::functionExternalCFile(row[8], row[2]);
                }
            }
        }

        // Interval
        readIntervalBiSection(row, data);

        // initial value
        readInitialValue(row, data);

        //tolerance
        if (row[6].empty()) {
            data->tolerance = 0.000001;
            std::cout << "Warning line " + std::to_string(currentLine) + ": tolerance is empty"
                         + ". Set value by default at " + std::to_string(data->tolerance) << std::endl;
        } else if (isNumber(row[6])) {
            data->initialValue = atof(row[6].c_str());
        } else{
            throw std::invalid_argument("Invalid cell in csv file at line " + std::to_string(currentLine)
                                            + ": " + row[6] + " should be a number.");
        }

        //maxIter
        if (row.size() < 8 || row[7].empty()) {
            data->maxIter = 10000;
            std::cout << "Warning line " + std::to_string(currentLine) + ": number of max iterations is empty"
                         + ". Set value by default at " + std::to_string(data->maxIter) << std::endl;
        } else if (isNumber(row[7])){
            data->initialValue = atof(row[7].c_str());
        } else{
            throw std::invalid_argument("Invalid cell in csv file at line " + std::to_string(currentLine)
                                            + ": " + row[7] + " should be a number.");
        }
        return data;
    }//if catch an exception return a data with all methods false because there is an error in the csv file at that line
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
        Data *data = new Data;
        return data;
    }
    catch (ParserException &e){
        std::cout << e.what() << std::endl;
        Data *data = new Data;
        return data;
    }
}

std::vector<Data*> ReaderData::readAllData() {

    // Read  data from the file as String Vector and output as Data
    std::vector<std::string> row;
    std::string line, word;
    std::vector<Data*> dataVector;

    getline(csv, line); //skip header line
    currentLine = 1;
    while (!csv.eof()) {
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(csv, line);
        currentLine++;
        // used for breaking words
        std::stringstream s(line);
        // read every column data of a row and store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data of a row to a vector
            row.push_back(word);
        }
        if (!row.empty()) {
            // fill struct data
            Data *data =createDataRow(row);

            //add data to dataVector output
            dataVector.push_back(data);
        }
    }
    return dataVector;
}

bool ReaderData::isNumber(std::string const& str) {
    int countPoint = 0;
    int countMinus = 0;
    int countE = 0;
    for (char i : str){
        if (isdigit(i) == false) {
            // verify decimal number
            if (i == '.' && countPoint == 0) {
                countPoint = 1;
            }
                // verify negative number
            else if (i == '-' && countMinus == 0){
                countMinus = 1;
            }
                // verify writing like 1e-6
            else if ((i == 'e' || i == 'E') && countE == 0){
                countE = 1;
            }
            else{
                return false;
            }
        }
    }
    return true;
}


bool ReaderData::isEmptyFile(std::basic_ifstream<char>& file) {
    long begin, end;
    begin = file.tellg();
    file.seekg (0, std::ios::end);
    end = file.tellg();
    if(end-begin == 0){
        file.seekg (0, std::ios::beg);
        return true;
    }
    file.seekg (0, std::ios::beg);
    return false;
}


void ReaderData::fillChosenMethod(Data *data, const std::string& methods) const {
    std::stringstream s(methods);
    std::string word;
    std::vector<std::string> methodsVector;
    while (getline( s, word, ';')) {
        methodsVector.push_back(word);
    }
    for(std::string method : methodsVector){
        char m = method.back();
        switch(m){
            case 'f':
            case 'F':
                data->method["FixedPoint"] = true;
                break;
            case 'b':
            case 'B':
                data->method["Bisection"] = true;
                break;
            case 'n':
            case 'N':
                data->method["Newton"] = true;
                break;
            case 'c':
            case 'C':
                data->method["Chord"] = true;
                break;
            default:
                throw std::invalid_argument("Invalid argument:" + method + " at line " + std::to_string(currentLine)+
                                            ". Methods must be f, b, n, or c delimited by ;. Respectively fixed point, "
                                            "bisection, newton and chord methods");
        }
    }
}



