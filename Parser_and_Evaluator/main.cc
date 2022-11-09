#include <vector>
#include <exception>
#include "treeNode.h"
#include "parser.h"


int contains_symbol(const std::string& line, char symbol);
void parse_line(const std::string& line, std::string& formulaStr, std::string& assignmentStr);
void split_str(std::string const& str, const char delim, std::vector <std::string>& out);

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
	std::string line;
	std::string formulaStr;
	std::string assignmentStr;
	
	while (getline(std::cin, line)) {
		try {
			TreeNode* root;
			//remove_spaces(line);
			parse_line(line, formulaStr, assignmentStr);
			AssignmentParser ap(assignmentStr);
			FormulaParser fp(formulaStr);
			root = fp.getTreeRoot();
			std::map<std::string, bool> map = ap.parseAssignment();
			bool res = root->evaluate(map);
			std::cout << res << std::endl;
			delete root;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
	
}


void parse_line(const std::string& line, std::string& formulaStr, std::string& assignmentStr) {
	char delimiter = ';';
	if (contains_symbol(line, delimiter) != 1) {
		throw std::runtime_error("Error: invalid input");
	}
	else {
		std::vector<std::string> vector;
		split_str(line, delimiter, vector);
		if (vector[0].length() == 0)
			throw std::runtime_error("Error: invalid input");
		formulaStr = vector[0];
		assignmentStr = vector.size() == 1 ? "" : vector[1];
	}
}

int contains_symbol(const std::string& line, char symbol) {
	int count = 0;
	for (int i = 0; i < line.length(); i++) {
		if (symbol == line[i])
			count++;
	}
	return count;
}

void split_str(std::string const& str, const char delim, std::vector <std::string>& out) {
	std::stringstream s(str);
	std::string s2;
	while (std::getline(s, s2, delim))
	{
		out.push_back(s2);
	}
}
