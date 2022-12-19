#pragma once

#include <vector>

#include "ast.h"
#include "token.h"

class Parser
{
public:
	Parser(std::vector<Token>);
	ExprAST GenAST();

private:
	std::vector<Token> tokens;
	int curPointer = 0;

	ExprAST ParseExpr();
	ExprAST ParseFactor();
	ExprAST ParseTerm();
	ExprAST ParsePrimary();

	Token Peek();
	void Advance();

	bool IsEOF();
};