//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include "ReaderData.h"

std::vector<Data*> ReaderData::readAllData(const std::string& pathOfCsv) {

    // Open an existing and non-empty file
    std::ifstream csv;
    csv.open(pathOfCsv, std::ios::in);
    if (!csv.is_open()) {
        throw std::invalid_argument("Invalid path: " + pathOfCsv + ". File can't be open doesn't exit.");
    }
    if (ReaderData::isEmptyFile(csv)) {
        throw std::invalid_argument("Invalid file: " + pathOfCsv + ". File exist but it's empty.");
    }

    // Read  data from the file as String Vector and output as Data
    std::vector<std::string> row;
    std::string line, word;
    std::vector<Data*> dataVector;

    getline(csv, line); //skip header line
    int countLine = 1;
    while (!csv.eof()) {
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(csv, line);
        countLine+=1;
        // used for breaking words
        std::stringstream s(line);
        // read every column data of a row and store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data of a row to a vector
            row.push_back(word);
        }
        if(!row.empty()) {
            // fill struct data
            Data *data = new Data;
            // function
            if (row.empty()) {
                throw std::invalid_argument("Invalid cell in csv file: data must have a function"
                                            ", first column can't be empty at line " + to_string(countLine));
            }
            data->fun = Solver::strToFun(row[0]);
            // derivative
            if (row[1].empty()) {
                std::cout << "Warning: derivative is empty at line "  + to_string(countLine)
                    + ". Can't use Newton method" << std::endl;
                data->method["Newton"] = false;
            } else {
                data->dFun = Solver::strToFun(row[1]);
            }
            // interval
            if (row[2].empty()) {

                std::cout << "Warning: lowerBound is empty at line " + to_string(countLine) +
                    ". Can't use bisection method" << std::endl;
                data->method["Bisection"] = false;
            } else {
                if (!ReaderData::isNumber(row[2])) {
                    throw std::invalid_argument("Invalid cell in csv file at line " + to_string(countLine)
                        +": " + row[2] + " should be a number.");
                }
                data->lowerBound = atof(row[2].c_str());
            }
            if (row[3].empty()) {
                std::cout << "Warning: upperBound is empty at line " + to_string(countLine)
                        + ". Can't use bisection method" << std::endl;
                data->method["Bisection"] = false;
            } else {
                if (!ReaderData::isNumber(row[3])) {
                    throw std::invalid_argument("Invalid cell in csv file at line " + to_string(countLine)
                        + ": " + row[3] + " should be a number.");
                }
                data->upperBound = atof(row[3].c_str());
            }
            // initial value
            if (row[4].empty()) {
                std::cout << "Warning: initial value is empty at line: " + to_string(countLine)
                    + ". Can't use newton, chord and fixed point methods" << std::endl;
                data->method["Newton"] = false;
                data->method["FixedPoint"] = false;
                data->method["Chord"] = false;
            } else {
                if (!ReaderData::isNumber(row[4])) {
                    throw std::invalid_argument("Invalid cell in csv file at line " + to_string(countLine)
                        + ": " + row[4] + " should be a number.");
                }
                data->initialValue = atof(row[4].c_str());
            }
            //tolerance
            if (row[5].empty()) {
                data->tolerance = -1;
            } else {
                if (!ReaderData::isNumber(row[5])) {
                    throw std::invalid_argument("Invalid cell in csv file at line " + to_string(countLine)
                        + ": " + row[5] + " should be a number.");
                }
                data->tolerance = atof(row[5].c_str());
            }
            //maxIter
            if (row.size() != 7) {
                data->maxIter = -1;
            } else {
                if (!ReaderData::isNumber(row[6])) {
                    throw std::invalid_argument("Invalid cell in csv file at line " + to_string(countLine)
                        + ": " + row[6] + " should be a number.");
                }
                data->maxIter = atoi(row[6].c_str());
            }

            // add data to dataVector output
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
            if (i == '.' && countPoint == 0) {
                countPoint = 1;
            } else if (i == '-' && countMinus == 0){
                countMinus = 1;
            } else if ((i == 'e' || i == 'E') && countE == 0){
                countE = 1;
            }
            else{
                return false;
            }
        }
    }
    return true;
}

bool ReaderData::isEmptyFile(basic_ifstream<char>& file) {
    long begin, end;
    begin = file.tellg();
    file.seekg (0, ios::end);
    end = file.tellg();
    if(end-begin == 0){
        file.seekg (0, ios::beg);
        return true;
    }
    file.seekg (0, ios::beg);
    return false;
}


