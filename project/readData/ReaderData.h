//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//

#ifndef PCSC_PROJECT_READERDATA_H
#define PCSC_PROJECT_READERDATA_H

#include "Data.h"
#include <string>
#include <vector>

class ReaderData {
public:
    //static Data readOneData(std::string pathOfCsv, int line);
    static std::vector<Data*> readAllData(const std::string& pathOfCsv);
private:
    static bool isNumber(const std::string& str);
    static bool isEmptyFile(basic_ifstream<char>& file);
    static void fillChosenMethod(Data* data, const std::string& methods, int line);
};


#endif //PCSC_PROJECT_READERDATA_H
