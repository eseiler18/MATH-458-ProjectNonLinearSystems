//
// Created by eseiler@INTRANET.EPFL.CH on 06.12.21.
//
# include <iostream>
#include "ReaderData.h"

int main(int argc, char* argv[]){
        std::vector<Data*> allData = ReaderData::readAllData(("../data.csv"));
    return 0;
};

