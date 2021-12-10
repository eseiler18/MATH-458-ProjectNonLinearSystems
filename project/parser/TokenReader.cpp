//
// Created by eseiler@INTRANET.EPFL.CH on 03.12.21.
//

#include "TokenReader.h"
#include "Token.h"
#include "TokenContainer.h"
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
    while (currentChar == ' ' && position < expression.length()){
        spaceFound = true;
        position++;
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
        case 'X':
            type= TokenType::VAR;
            break;
        default:
            type = TokenType::NUMBER;
            break;
    }
    if(type == TokenType::NUMBER){
        // create number token
        resultToken = createNumberToken();
    }
    else{
        resultToken = new Token(type, currentChar);
    }
    resultToken->setSpaceBefore(spaceFound);
    return resultToken;
}

Token *TokenReader::createNumberToken() {
    char currentChar = expression.at(position);
    if(currentChar<'0' || currentChar >'9'){
        std::string message("Invalid character: ");
        message.push_back(currentChar);
        throw std::invalid_argument(message);
    }
    std::string numberStr;
    numberStr.push_back(currentChar);
    bool dotFound = false;
    while(position < expression.length()-1){
        currentChar = expression.at(position + 1);
        if(currentChar>='0' && currentChar <='9'){
            numberStr.push_back(currentChar);
        }
        else if(currentChar == '.' || currentChar == ',') {
            if(dotFound) {
                std::string message("Invalid character: ");
                message.push_back(currentChar);
                throw std::invalid_argument(message);
            }
            numberStr.push_back('.');
            dotFound = true;
        }
        else{break; }
        position++;
    }
    return new Token(TokenType::NUMBER, numberStr);
}
