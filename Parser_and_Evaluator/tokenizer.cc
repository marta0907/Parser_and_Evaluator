#include "tokenizer.h"


Tokenizer::Tokenizer(std::string ln) {
    // complete the constructor
    this->expression = ln;
    this->index = 0;
}

bool Tokenizer::advanceToken(std::string ln) {
    for (int i = 0; i < ln.length(); i++) {
        if (ln[i] != expression[index + i]) return false;
    }
    return true;
}

bool Tokenizer::hasToken() const {
    return index < expression.length();
} // not sure about that method

// only can be called when hasToken() is true  (something useful???)
Token Tokenizer::getToken() {
    Token resultToken;
    std::string str;
    while (index < expression.length()) {
        char c = expression[index];
        switch (c)
        {
        case(' '): {
            index++;
            break;
        }
        case('('):
        case(')'):
        case('+'):
        case('*'): 
        case('-'):
        case(','):
        case(':'): {
            if (str.size() > 0) {
                resultToken.content = str;
                resultToken.type = Variable;
                return resultToken;
            };
            resultToken.content = c;
            resultToken.type = (c == '+' || c == '*' || c == '-') ? Operator : Symbol;
            index++;
            return resultToken;
        }
        case('0'):
        case('1'): {
            if (str.size() > 0)
            {
                index++;
                str.push_back(c);
                break;
            }
            else {
                resultToken.content = c;
                resultToken.type = Constant;
                index++;
                return resultToken;
            }
        }
        default:
            str.push_back(c);
            index++;
            break;
        }
    }
    if (str.size() > 0) {
        resultToken.content = str.data();
        resultToken.type = Variable;
    }
    return resultToken;
}
