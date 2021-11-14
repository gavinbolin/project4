#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    END,
    WHITE
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type;
    string desc;
    int lineNumber;

public:
    Token(TokenType type, string description, int line){
        this->type = type;
        desc = description;
        lineNumber = line;
    }

    bool notWhite() {
        if (type == TokenType::WHITE)
            return false;
        else
            return true;
    }
    bool notCom(){
        if (type == TokenType::COMMENT)
            return false;
        else
            return true;
    }
    TokenType getType() {return type;}
    std::string getDesc(){return desc;}

    string toString(){
        string tType;
        ostringstream os;
        switch (type) {
            case TokenType::COLON:      tType = "COLON";       break;
            case TokenType::COLON_DASH: tType = "COLON_DASH";  break;
            case TokenType::COMMA:      tType = "COMMA";       break;
            case TokenType::PERIOD:     tType = "PERIOD";      break;
            case TokenType::Q_MARK:     tType = "Q_MARK";      break;
            case TokenType::LEFT_PAREN: tType = "LEFT_PAREN";  break;
            case TokenType::RIGHT_PAREN:tType = "RIGHT_PAREN"; break;
            case TokenType::MULTIPLY:   tType = "MULTIPLY";    break;
            case TokenType::ADD:        tType = "ADD";         break;
            case TokenType::SCHEMES:    tType = "SCHEMES";     break;
            case TokenType::FACTS:      tType = "FACTS";       break;
            case TokenType::RULES:      tType = "RULES";       break;
            case TokenType::QUERIES:    tType = "QUERIES";     break;
            case TokenType::ID:         tType = "ID";          break;
            case TokenType::STRING:     tType = "STRING";      break;
            case TokenType::COMMENT:    tType = "COMMENT";     break;
            case TokenType::UNDEFINED:  tType = "UNDEFINED";   break;
            case TokenType::END:        tType = "EOF";         break;
            case TokenType::WHITE:      tType = "";            break;
        }
        os << "(" << tType << ",\"" << desc << "\"," << lineNumber << ")";
        return os.str();
    }
    // TODO: add other needed methods
};

#endif // TOKEN_H

/*
#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
     = type;
    desc = description;
    lineNumber = line;
    // TODO: initialize all member variables
}
*/