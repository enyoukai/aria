#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "scanner.h"
#include "parser.h"

using namespace std;

void scan_tokens(string);

int main()
{
	Scanner scanner("!.aria");
	std::vector<Token> tokens = scanner.Scan();

	Parser parser(tokens);
	ExprAST ast = parser.GenAST();

	std::cout << ast.Print() << '\n';

	BinaryAST bin = BinaryAST(ast, ast, Token());
	std::cout << bin.Print() << '\n';
}