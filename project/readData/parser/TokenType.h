//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#ifndef PCSC_PROJECT_TOKENTYPE_H
#define PCSC_PROJECT_TOKENTYPE_H
/**
 * Enum of all the token type parenthesis, operator, number or variable
 */
enum TokenType
{
    OPEN_PAR = 1,   // (
    CLOSE_PAR = 2,  // )
    ADD = 3,        // +
    SUB = 4,        // -
    MUL = 5,        // *
    DIV = 6,        // /
    POW = 7,        // ^
    NUMBER = 8,     // 0-9
    VAR = 9,        // x
    CONTAINER = 10, // container of other token (...)
    FUNCTION = 11   // name of external function or math function
};

static std::string tokenTypeToString(TokenType type) {
    switch (type)
    {
    case OPEN_PAR:
        return "OPEN_PAR";
        break;
    case CLOSE_PAR:
        return "CLOSE_PAR";
        break;
    case MUL:
        return "MUL";
        break;
    case ADD:
        return "ADD";
        break;
    case SUB:
        return "SUB";
        break;
    case DIV:
        return "DIV";
        break;
    case POW:
        return "POW";
        break;
    case NUMBER:
        return "NUMBER";
        break;
    case VAR:
        return "VAR";
        break;
    case CONTAINER:
        return "CONTAINER";
        break;
    case FUNCTION:
        return "FUNCTION";
        break;    
    default:
        return "UNKNOWN";
        break;
    }
}

#endif //PCSC_PROJECT_TOKENTYPE_H
