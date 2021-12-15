//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#ifndef PCSC_PROJECT_READERDATA_H
#define PCSC_PROJECT_READERDATA_H

#include <string>
#include <vector>
#include <fstream>

#include "Data.h"

/**
 * ReaderData class which read a cvs file and build the data structure associated (one by row)
 */
class ReaderData {
private:
    std::string folderCsv;
    std::string pathOfCsv;
    int currentLine;
    std::ifstream csv;

public:
    /// constructor with the path of the csv file
    explicit ReaderData(const std::string& pathOfCsv);
    /// main method which read all the csv file and return the data structures
    std::vector<Data*> readAllData();
private:
    /// verify if a string is number
    static bool isNumber(const std::string& str);
    /// verify if file is empty
    static bool isEmptyFile(std::basic_ifstream<char>& file);
    /// read the first cell of the row two know which methods are requested
    void fillChosenMethod(Data* data, const std::string& methods) const;
    /// create the associated data structure for a row of the csv
    Data* createDataRow(std::vector<std::string>& row);
    /// read column upper lower bound for method bisection
    void readIntervalBiSection(std::vector<std::string>& row,Data* data) const;
    /// read column initial value for method Newton, Fixed Point and Chord
    void readInitialValue(std::vector<std::string>& row,Data* data) const;
};


#endif //PCSC_PROJECT_READERDATA_H