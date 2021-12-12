//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#ifndef PCSC_PROJECT_READERDATA_H
#define PCSC_PROJECT_READERDATA_H

#include "Data.h"
#include <string>
#include <vector>

/**
 * ReaderData class which read a cvs file and build the data structure associated (one by row)
 */
class ReaderData {
public:
    /// main method which read all the csv file and return the data structures
    static std::vector<Data*> readAllData(const std::string& pathOfCsv);
private:
    /// verify if a string is number
    static bool isNumber(const std::string& str);
    /// verify if file is empty
    static bool isEmptyFile(std::basic_ifstream<char>& file);
    /// read the first cell of the row two know which methods are requested
    static void fillChosenMethod(Data* data, const std::string& methods, int line);
    static AbstractNode* readFunctionExternalFile(const std::string& nameFile, const std::string& nameFun);
};


#endif //PCSC_PROJECT_READERDATA_H
