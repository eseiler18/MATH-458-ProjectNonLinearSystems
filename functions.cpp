//
// Created by eseiler@INTRANET.EPFL.CH on 11.12.21.
//
#include <iostream>
#include <math.h>

extern "C" {
double fun(double x) {
    double res = 0;
    for (int i = 0; i < 13; ++i)
        res += x * x * exp(x);
    return res;
}
double funb(double x) {
    return exp(x) - 12;
}

double dfunb(double x) {
    return exp(x);
}
}