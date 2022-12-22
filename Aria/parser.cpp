#include "parser.h"
#include "ast.h"
#include "token.h"

#include <iostream>
#include <memory>

Parser::Parser(std::vector<Token> tokensArgs)
{
	tokens = tokensArgs;
}

std::unique_ptr<AST> Parser::GenAST()
{
	return Parser::ParseExpr();
}

std::unique_ptr<AST> Parser::ParseExpr()
{
	return ParseTerm();
}

std::unique_ptr<AST> Parser::ParseTerm()
{
	std::unique_ptr<AST> expr = ParseFactor();

	// really janky clean later
	while (!IsEOF() && (Peek().type == Token::PLUS || Peek().type == Token::MINUS))
	{
		Token op = Peek();

		Advance();
		std::unique_ptr<AST> RHS = ParseFactor();

		expr = std::make_unique<BinaryAST>(move(expr), move(RHS), op);
	}

	return expr;
}

std::unique_ptr<AST> Parser::ParseFactor()
{
	std::unique_ptr<AST> expr = ParsePrimary();

	while (!IsEOF() && (Peek().type == Token::STAR || Peek().type == Token::SLASH))
	{
		Token op = Peek();

		Advance();
		std::unique_ptr<AST> RHS = ParsePrimary();

		expr = std::make_unique<BinaryAST>(move(expr), move(RHS), op);
	}

	return expr;
}

std::unique_ptr<AST> Parser::ParsePrimary()
{
	std::unique_ptr<AST> expr = std::make_unique<LiteralAST>(Peek());

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