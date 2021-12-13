//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include "TokenReader.h"
#include "Token.h"
#include "TokenContainer.h"
#include "TokenFunction.h"
#include <utility>

TokenReader::TokenReader(std::string expression) : expression(std::move(expression)), position(-1) {}

AbstractToken *TokenReader::readNextToken() {
    position++;
    if (position >= expression.length()){
        // reach end of expression
        return nullptr;
    }
    char currentChar = expression.at(position);
    // Skip space
    bool spaceFound = false;
    while (currentChar == ' '){
        spaceFound = true;
        position++;
        if (position >= expression.length()) {
            // we reach the end of expression => no more token
            return nullptr;
        }
        currentChar = expression.at(position);
    } 
    // create the new token associated with the new character
    TokenType type;
    Token* resultToken = nullptr;
    switch(currentChar){
        case '(':
            type = TokenType::OPEN_PAR;
            break;
        case ')':
            type = TokenType::CLOSE_PAR;
            break;
        case '+':
            type = TokenType::ADD;
            break;
        case '-':
            type = TokenType::SUB;
            break;
        case '*':
            type = TokenType::MUL;
            break;
        case '/':
            type = TokenType::DIV;
            break;
        case '^':
            type = TokenType::POW;
            break;
        case 'x':
        case 'X':{
                // now we can have several variable x1, x2, x3.... check if there is some digit
                std::string variableName;
                variableName.push_back(currentChar);
                while (position+1 < expression.length() && std::isdigit(expression[position+1])){
                    variableName.push_back(expression[position+1]);
                    position++;
                }
                resultToken = new Token(TokenType::VAR, variableName);
            }
            break;
        default:
            // create number token
            // change here where manage functioname
            if (std::isdigit(currentChar)) {
                resultToken = createNumberToken();
            } else {
                resultToken = createFunctionToken();
            }
            break;
    }
    if (resultToken==nullptr) {
        resultToken = new Token(type, currentChar);
    }
    resultToken->setSpaceBefore(spaceFound);
    return resultToken;
}

Token *TokenReader::createNumberToken() {
    char currentChar = expression.at(position);
    // check if character is a digit
    if(!std::isdigit(currentChar)){
        std::string message("Invalid character: ");
        message.push_back(currentChar);
        throw ParserException(message);
    }
    std::string numberStr;
    numberStr.push_back(currentChar);
    bool dotFound = false;
    while(position < expression.length()-1){
        currentChar = expression.at(position + 1);
        // case when number is several digit
        if(std::isdigit(currentChar)){
            numberStr.push_back(currentChar);
        }
        // case when the number is decimal
        else if(currentChar == '.' || currentChar == ',') {
            if(dotFound) {
                std::string message("Invalid character: ");
                message.push_back(currentChar);
                throw ParserException(message);
            }
            numberStr.push_back('.');
            dotFound = true;
        }
        // break is the number is finish
        else{break; }
        position++;
    }
    // build the token number
    return new Token(TokenType::NUMBER, numberStr);
}


Token *TokenReader::createFunctionToken() {
    char currentChar = expression.at(position);
    // check if character is an alphanumeric character
    if(!std::isalnum(currentChar)){
        std::string message("Invalid character reach: ");
        message.push_back(currentChar);
        throw ParserException(message);
    }
    std::string functionName;
    functionName.push_back(currentChar);
    bool dotFound = false;
    while(position < expression.length()-1){
        currentChar = expression.at(position + 1);
        // case when number is several digit
        if(std::isalnum(currentChar)){
            functionName.push_back(currentChar);
        } else if (currentChar !=' ' and currentChar != '(') {
            // it's not a function name :not following by space or ( 
            std::string message();
            throw ParserException("Invalid token reach: " + functionName);
        } else {
            // break is the number is finish
            break;
        }
        position++;
    }
    // build the token number
    return new TokenFunction(functionName);
}
