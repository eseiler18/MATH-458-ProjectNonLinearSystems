//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENTYPE_H
#define PCSC_PROJECT_TOKENTYPE_H
enum TokenType{
    OPEN_PAR = 1, // (
    CLOSE_PAR = 2, // )
    ADD = 3, // +
    SUB = 4, // -
    MUL = 5, // *
    DIV = 6, // /
    POW = 7, // ^
    NUMBER = 8, // 0-9
    VAR = 9, // x
    CONTAINER = 10, // 0-9
};
#endif //PCSC_PROJECT_TOKENTYPE_H
