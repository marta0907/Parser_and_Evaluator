#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

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

// a tokenizer breaks a stream of string into tokens
class Tokenizer
{
    std::string expression;
    int index;
    // your code starts here
public:
    Tokenizer(std::string ln);
    bool advanceToken(std::string ln); // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken(); // returns the token being processed
};

#endif

