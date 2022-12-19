#pragma once

#include <vector>

#include "ast.h"
#include "token.h"

class Parser
{
public:
	Parser(std::vector<Token>);
	void GenAST();

private:
	std::vector<Token> tokens;
	int curPointer = 0;

	ExprAST ParseExpr();
	ExprAST ParseFactor();
	ExprAST ParseTerm();

	Token Peek();
	void Advance();
};