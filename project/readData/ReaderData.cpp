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
    while (!csv.eof()) {
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(csv, line);
        // used for breaking words
        std::stringstream s(line);
        // read every column data of a row and store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data of a row to a vector
            row.push_back(word);
        }
        // fill struct data
        Data* data = new Data;
        // function
        if(row[0].empty()){
            throw std::invalid_argument("Invalid cell in csv file: data must have a function"
                                        ", first column can't be empty");
        }
        data->fun = Solver::strToFun(row[0]);
        // derivative
        if(row[1].empty()){
            std::cout << "Warning: derivative is empty can't use Newton method" << std::endl;
        }
        else {
            data->dFun = Solver::strToFun(row[1]);
        }
        // interval
        if(row[2].empty() or row[3].empty()){
            std::cout << "Warning: one bound is empty can't use bisection method" << std::endl;
        }
        if (!ReaderData::isNumber(row[2])){
            throw std::invalid_argument("Invalid cell in csv file: " + row[2] + " should be a number.");
        }
        data->lowerBound = atof(row[2].c_str());
        if (!ReaderData::isNumber(row[3])){
            throw std::invalid_argument("Invalid cell in csv file: " + row[3] + " should be a number.");
        }
        data->upperBound = atof(row[3].c_str());
        if (!ReaderData::isNumber(row[4])){
            throw std::invalid_argument("Invalid cell in csv file: " + row[4] + " should be a number.");
        }
        data->initialValue = atof(row[4].c_str());
        if (!ReaderData::isNumber(row[5])){
            throw std::invalid_argument("Invalid cell in csv file: " + row[5] + " should be a number.");
        }
        data->tolerance = atof(row[5].c_str());
        if (!ReaderData::isNumber(row[6])){
            throw std::invalid_argument("Invalid cell in csv file: " + row[6] + " should be a number.");
        }
        data->maxIter = atoi(row[6].c_str());
        // add data to dataVector output
        dataVector.push_back(data);
    }
    dataVector.pop_back();
    return dataVector;
}


bool ReaderData::isNumber(std::string const& str) {
    int countPoint = 0;
    int countMinus = 0;
    for (char i : str){
        if (isdigit(i) == false) {
            if (i == '.' && countPoint == 0) {
                countPoint = 1;
            } else if (i == '-' && countMinus == 0){
                countMinus = 1;
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


