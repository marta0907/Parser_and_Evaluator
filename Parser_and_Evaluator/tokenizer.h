#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <iostream> 
#include <cctype> 

enum TokenType {
    Constant,
    Variable,
    Operator,
    Symbol,
    None
};

struct Token
{
    std::string content;
    TokenType type = None;
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

