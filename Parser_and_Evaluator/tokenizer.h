#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <iostream>  

enum TokenType {
    Constant,
    Variable,
    Operator,
    Symbol
};

struct Token
{
    std::string content;
    TokenType type;
};

class Tokenizer
{
    std::string expression;
    int index;
public:
    Tokenizer(std::string ln);
    bool advanceToken(std::string ln);
    bool hasToken() const;
    Token getToken();
    void validateStr(std::string str);
};

#endif

