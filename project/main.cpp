#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <sstream>
#include "Newton.h"
#include "ClassicChord.h"

double fun(double x){return x*x;}
double dfun(double x){return 2*x;}
double ideFun(double x){return x-22;}
double dIdeFun(double x){return 1;}

void read_csvline() {
    // File pointer
    std::ifstream fin;

    // Open an existing file
    fin.open("/home/eseiler/posixfs/MATH-458-Project_Non_Linear_Systems/project/data.csv", std::ios::in);
    assert(fin.is_open());

    // Get the function number of which the data is required
    int i, count = 0;
    std::cout << "Enter the row number of the file you want to read : ";
    std::cin >> i;

    // Read the Data from the file as String Vector
    std::vector<std::string> row;
    std::string line, word;

    while (!fin.eof()) {
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(fin, line);
        // used for breaking words
        std::stringstream s(line);
        // read every column data of a row and store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data of a row to a vector
            row.push_back(word);
        }
        // Compare the roll number
        if (count == i) {
            // Print the found data
            count = 1;
            std::cout << "Function: " << row[0] << "\n";
            std::cout << "Derivative: " << row[1] << "\n";
            std::cout << "Interval: [" << row[2] << ", " << row[3] << "]" "\n";
            std::cout << "Initial Value: " << row[4] << "\n";
            std::cout << "Tolerance: " << row[5] << "\n";
            std::cout << "Max Iterations: " << row[6] << "\n";
            break;
        }
        count+=1;
    }
}

int main() {
    Newton n;
    n.SetF(ideFun);
    n.SetDf(dIdeFun);
    n.SetInitialValue(-5);
    n.SetMaxIter(100);
    n.SetTol(0.0001);
    n.SolveEquation();

    ClassicChord ch;
    ch.SetF(ideFun);
    ch.SetInitialValue(-5);
    ch.SetMaxIter(100);
    ch.SetTol(0.0001);
    ch.SolveEquation();

    read_csvline();



    return 0;
}
