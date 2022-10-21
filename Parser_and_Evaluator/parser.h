#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <iostream>  

#include "tokenizer.h"

class TreeNode;
class Tokenizer;

// Parser for the Boolean Formula
class FormulaParser {
    Tokenizer* tknzr;
    Token currentToken;
    TreeNode* parseFormula(); 
    TreeNode* parseConjTerm(); 
    TreeNode* parseTerm(); 
public:
    FormulaParser(std::string ln);
    TreeNode* getTreeRoot(); 
    ~FormulaParser();
};

// Parser for the Assignment
class AssignmentParser {
    Tokenizer* tknzr;
    Token currentToken;
    void parsePair(std::map<std::string, bool>& map);
    void parseConstant(std::map<std::string, bool>& map, std::string varName);
public:
    AssignmentParser(std::string ln);
    std::map<std::string, bool> parseAssignment();
    ~AssignmentParser();
};

#endif

