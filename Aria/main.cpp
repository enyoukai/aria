#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

#include "scanner.h"
#include "parser.h"
#include "ast.h"
#include "visitor.h"

using namespace std;

void scan_tokens(string);

int main()
{
	Scanner scanner("!.aria");
	std::vector<Token> tokens = scanner.Scan();
	scanner.PrintTokens();

	Parser parser(tokens);
	std::vector<std::unique_ptr<AST>> programAST = parser.GenAST();

	PrinterVisitor ASTPrinter;
	programAST[1]->Accept(&ASTPrinter);

	CodeGenVisitor ToASM;
	programAST[0]->Accept(&ToASM);
	programAST[1]->Accept(&ToASM);
	ToASM.OutputASM();
}