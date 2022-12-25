#include "parser.hpp"
#include "ast.hpp"
#include "token.hpp"

#include <iostream>
#include <memory>

Parser::Parser(std::vector<Token> tokensArgs)
{
	tokens = tokensArgs;
}

std::vector<std::unique_ptr<AST>> Parser::GenAST()
{
	std::vector<std::unique_ptr<AST>> ProgramAST;

	while (!IsEOF())
	{
		ProgramAST.push_back(std::move(Parser::ParseLine()));
	}

	return ProgramAST;
}

std::unique_ptr<AST> Parser::ParseLine()
{
	if (Peek().type == Token::IDENTIFIER)
	{
		return ParseAssignment();
	}

	if (Peek().type == Token::WHILE)
	{
		return ParseWhileLoop();
	}

	std::cout << "something happened";
	return nullptr;
}

std::unique_ptr<AST> Parser::ParseWhileLoop()
{
	Advance(); // skip while
	Advance(); // skip left paren (TODO: WHAT IS THIS please add some proper syntax validation)
	std::unique_ptr<AST> comparison = ParseComparison();
	Advance(); // skip right paren

	std::vector<std::unique_ptr<AST>> block;

	// parse block
	Advance(); // skip left brace (TODO: i need to stop this)
	while (Peek().type != Token::RIGHT_BRACE)
	{
		block.push_back(std::move(ParseLine()));
	}
	Advance();

	return std::make_unique<WhileAST>(std::move(comparison), std::move(block));
}

std::unique_ptr<AST> Parser::ParseAssignment()
{
	std::unique_ptr<VariableAST> variable = std::make_unique<VariableAST>(Peek());
	Advance();
	Advance(); // skipping assignment operator kinda goofy
	std::unique_ptr<AST> expression = ParseExpr();

	std::unique_ptr<AssignmentAST> assignment = std::make_unique<AssignmentAST>(std::move(variable), std::move(expression));

	Advance(); // skip semicolon
	return assignment;
}

std::unique_ptr<AST> Parser::ParseExpr()
{
	return ParseComparison();
}

std::unique_ptr<AST> Parser::ParseComparison()
{
	std::unique_ptr<AST> expr = ParseTerm();

	if (!IsEOF() && (Peek().type == Token::GREATER || Peek().type == Token::LESSER || Peek().type == Token::EQUALS))
	{
		Token comparison = Peek();
		Advance();
		std::unique_ptr<AST> RHS = ParseTerm();

		expr = std::make_unique<ComparisonAST>(move(expr), move(RHS), comparison);
	}

	return expr;
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