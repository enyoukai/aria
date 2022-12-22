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
	return Parser::ParseLine();
}

std::unique_ptr<AST> Parser::ParseLine()
{
	if (Peek().type == Token::IDENTIFIER)
	{
		return ParseAssignment();
	}

	std::cout << "something happened";
	return nullptr;
}

std::unique_ptr<AST> Parser::ParseAssignment()
{
	std::unique_ptr<VariableAST> variable = std::make_unique<VariableAST>(Peek());
	Advance();
	Advance(); // skipping assignment operator kinda goofy
	std::unique_ptr<AST> expression = ParseExpr();

	std::unique_ptr<AssignmentAST> assignment = std::make_unique<AssignmentAST>(std::move(variable), std::move(expression));
	return assignment;
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
	Token primary = Peek();
	Advance();

	if (primary.type == Token::INT_LITERAL || primary.type == Token::STRING_LITERAL)
	{
		return std::make_unique<LiteralAST>(primary);
	}

	else if (primary.type == Token::IDENTIFIER)
	{
		return std::make_unique<VariableAST>(primary);
	}

	return nullptr;
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