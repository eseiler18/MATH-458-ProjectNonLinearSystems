//
// Created by eseiler@INTRANET.EPFL.CH on 11.12.21.
//
#include <iostream>
#include <math.h>

extern "C" {

double funa(double x) {
    return exp(x) - 12;
}

double funb(double x) {
    return 5*x + log(sqrt(x*x*x));
}

double func(double x) {
    return cos(x) + x*2;
}
}