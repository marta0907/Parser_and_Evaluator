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
    TreeNode* resultToken = parseTerm();
    while (tknzr->advanceToken("*"))
    {
        currentToken = tknzr->getToken();
        TreeNode* a = resultToken;
        TreeNode* b = parseConjTerm();
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
            return resultNode;
        }
        else if (currentToken.type == Constant) {
            resultNode = new ConstantNode(currentToken.content);
            return resultNode;
        }
        else if (currentToken.content == "-") {
            resultNode = new OperatorNode(currentToken.content);
            TreeNode* node = parseTerm();
            resultNode->updateLeftChild(node);
            return resultNode;
        }
        else if (currentToken.content == "(") {
            if (tknzr->hasToken()) {
                resultNode = parseFormula();
                if (tknzr->hasToken()) {
                    currentToken = tknzr->getToken();
                    if (currentToken.content == ")") {
                        return resultNode;
                    }
                    else {
                        //return error incorrect formula
                    }
                }
                else {
                    //return error incorrect formula
                }
            }
            else {
                //return error incorrect formula
            }
        }
    }
    return nullptr;
}


TreeNode* FormulaParser::getTreeRoot() {
    return parseFormula();
}

FormulaParser::~FormulaParser() {
    delete tknzr;
}

AssignmentParser::AssignmentParser(std::string ln) : tknzr{ new Tokenizer{ln} } {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
    std::map<std::string, bool> results;
    return results;
}

AssignmentParser::~AssignmentParser() {
    delete tknzr;
}
