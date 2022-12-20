#include "parser.h"
#include "ast.h"
#include "token.h"

#include <iostream>
#include <memory>

Parser::Parser(std::vector<Token> tokensArgs)
{
	tokens = tokensArgs;
}

std::unique_ptr<ExprAST> Parser::GenAST()
{
	return Parser::ParseExpr();
}

std::unique_ptr<ExprAST> Parser::ParseExpr()
{
	return ParseTerm();
}

std::unique_ptr<ExprAST> Parser::ParseTerm()
{
	std::unique_ptr<ExprAST> expr = ParseFactor();

	// really janky clean later
	while (!IsEOF() && (Peek().type == Token::PLUS || Peek().type == Token::MINUS))
	{
		Token op = Peek();

		Advance();
		std::unique_ptr<ExprAST> RHS = ParseFactor();

		expr = std::make_unique<BinaryAST>(move(expr), move(RHS), op);
	}

	return expr;
}

std::unique_ptr<ExprAST> Parser::ParseFactor()
{
	std::unique_ptr<ExprAST> expr = ParsePrimary();

	while (!IsEOF() && (Peek().type == Token::STAR || Peek().type == Token::SLASH))
	{
		Token op = Peek();

		Advance();
		std::unique_ptr<ExprAST> RHS = ParsePrimary();

		expr = std::make_unique<BinaryAST>(move(expr), move(RHS), op);
	}

	return expr;
}

std::unique_ptr<ExprAST> Parser::ParsePrimary()
{
	std::unique_ptr<ExprAST> expr = std::make_unique<LiteralAST>(Peek());

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