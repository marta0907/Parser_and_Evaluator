#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"


FormulaParser::FormulaParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

TreeNode* FormulaParser::parseFormula() {
    TreeNode* resultToken = parseConjTerm();
    while (tknzr->advanceToken("+"))
    {
        currentToken = tknzr->getToken();
        TreeNode* a = resultToken;
        TreeNode* b = parseConjTerm();
        resultToken = new OperatorNode("+");
        resultToken->updateChildren(a, b);
    }
    return resultToken;
}

TreeNode* FormulaParser::parseConjTerm() {
    TreeNode* resultToken =  parseTerm();
    while (tknzr->advanceToken("*"))
    {
        currentToken = tknzr->getToken();
        TreeNode* a = resultToken;
        TreeNode* b = parseTerm();
        resultToken = new OperatorNode("*");
        resultToken->updateChildren(a, b);
    }
    return resultToken;
}

TreeNode* FormulaParser::parseTerm() {
    TreeNode* resultNode = nullptr;
    if (tknzr->hasToken()) {
        currentToken = tknzr->getToken();
        if (currentToken.type == Variable) {

            resultNode = new VariableNode(currentToken.content);
        }
        else if (currentToken.type == Constant) {
            resultNode = new ConstantNode(currentToken.content);
        }
        else if (currentToken.content == "-") {
            resultNode = new OperatorNode(currentToken.content);
            TreeNode* node = parseTerm();
            resultNode->updateLeftChild(node);
        }
        else if (currentToken.content == "(") {
            if (tknzr->hasToken()) {
                resultNode = parseFormula();
                if (tknzr->hasToken()) {
                    currentToken = tknzr->getToken();
                    if (currentToken.content != ")") {
                        throw std::runtime_error("Error: invalid input");
                    }
                }
                else {
                    throw std::runtime_error("Error: invalid input");
                }
            }
            else {
                throw std::runtime_error("Error: invalid input");
            }
        }
    }
    return resultNode;
}

TreeNode* FormulaParser::getTreeRoot() {
    TreeNode* root = parseFormula();
    if (tknzr->hasToken()) {
        throw std::runtime_error("Error: invalid input");
    }
    return root;
}

FormulaParser::~FormulaParser() {
    delete tknzr;
}

AssignmentParser::AssignmentParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
    std::map<std::string, bool> results;
    parsePair(results);
    while (tknzr->advanceToken(",")) {
        currentToken = tknzr->getToken();
        parsePair(results);
    }
    return results;
}

void AssignmentParser::parsePair(std::map<std::string, bool>& results) {
    if (tknzr->hasToken()) {
        currentToken = tknzr->getToken();
        if (currentToken.type == Variable && tknzr->advanceToken(":")) {
            std::string varName = currentToken.content;
            currentToken = tknzr->getToken();
            parseConstant(results, varName);
        }
        else {
            throw std::runtime_error("Error: invalid input");
        }
    }
}

void AssignmentParser::parseConstant(std::map<std::string, bool>& results, std::string varName) {
    if (tknzr->advanceToken("0") || tknzr->advanceToken("1")) {
        currentToken = tknzr->getToken();
        bool value = currentToken.content == "1";
        if (results.count(varName) && results[varName] != value) {
            throw std::runtime_error("Error: contradicting assignment");
        }
        else {
            results.insert({ varName,value });
        }
    }
    else {
        throw std::runtime_error("Error: invalid input");
    }
}

AssignmentParser::~AssignmentParser() {
    delete tknzr;
}
