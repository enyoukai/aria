#pragma once

#include <vector>

#include "ast.h"
#include "token.h"

class Parser
{
public:
	Parser(std::vector<Token>);
	std::unique_ptr<AST> GenAST();

private:
	std::vector<Token> tokens;
	int curPointer = 0;

	std::unique_ptr<AST> ParseExpr();
	std::unique_ptr<AST> ParseFactor();
	std::unique_ptr<AST> ParseTerm();
	std::unique_ptr<AST> ParsePrimary();

	Token Peek();
	void Advance();

	bool IsEOF();
};