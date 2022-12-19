#include "parser.h"
#include "ast.h"
#include "token.h"

#include <iostream>

Parser::Parser(std::vector<Token> tokensArgs)
{
	tokens = tokensArgs;
}

ExprAST Parser::GenAST()
{
	return Parser::ParseExpr();
}

ExprAST Parser::ParseExpr()
{
	return ParseTerm();
}

ExprAST Parser::ParseTerm()
{
	ExprAST expr = ParseFactor();

	// really janky clean later
	while (!IsEOF() && (Peek().type == Token::PLUS || Peek().type == Token::MINUS))
	{
		Token op = Peek();

		Advance();
		ExprAST RHS = ParseFactor();

		expr = BinaryAST(expr, RHS, op);
	}

	return expr;
}

ExprAST Parser::ParseFactor()
{
	ExprAST expr = ParsePrimary();

	while (!IsEOF() && (Peek().type == Token::STAR || Peek().type == Token::SLASH))
	{
		Token op = Peek();

		Advance();
		ExprAST RHS = ParsePrimary();

		expr = BinaryAST(expr, RHS, op);
	}

	return expr;
}

ExprAST Parser::ParsePrimary()
{
	ExprAST expr = PrimaryAST(Peek());
	Advance();

	return expr;
}

Token Parser::Peek()
{
	return tokens[curPointer];
}

void Parser::Advance()
{
	curPointer++;
}

bool Parser::IsEOF()
{
	return curPointer >= tokens.size();
}