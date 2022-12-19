#include "parser.h"
#include "ast.h"
#include "token.h"

#include <iostream>

Parser::Parser(std::vector<Token> tokensArgs)
{
	tokens = tokensArgs;
}

void Parser::GenAST()
{
	Parser::ParseExpr();
}

ExprAST Parser::ParseExpr()
{
	ExprAST expr = Parser::ParseTerm();

	while (Parser::Peek().type == Token::PLUS || Parser::Peek().type == Token::MINUS)
	{
		Token op = Parser::Peek();

		Parser::Advance();
		ExprAST RHS = Parser::ParseTerm();

		expr = BinaryAST(expr, RHS, op);
	}

	return expr;
}

ExprAST Parser::ParseTerm()
{
}

ExprAST Parser::ParseFactor()
{
}

Token Parser::Peek()
{
}

void Parser::Advance()
{
}