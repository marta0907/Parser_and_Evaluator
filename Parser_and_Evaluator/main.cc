#include <iostream>
#include "treeNode.h"
#include "parser.h"
#include "tokenizer.h"
#include <map>

std::string removeSpaces(std::string input)
{
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	return input;
}


int main() {
	FormulaParser parser(removeSpaces("------------1"));
	TreeNode* node = parser.getTreeRoot();
	std::map<std::string, bool> map;
	std::cout << node->evaluate(map);
	delete node;
}