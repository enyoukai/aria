#pragma once

#include <vector>

#include "ast.h"
#include "token.h"

class Parser
{
public:
	Parser(std::vector<Token>);
	std::unique_ptr<ExprAST> GenAST();

private:
	std::vector<Token> tokens;
	int curPointer = 0;

	std::unique_ptr<ExprAST> ParseExpr();
	std::unique_ptr<ExprAST> ParseFactor();
	std::unique_ptr<ExprAST> ParseTerm();
	std::unique_ptr<ExprAST> ParsePrimary();

	Token Peek();
	void Advance();

	bool IsEOF();
};