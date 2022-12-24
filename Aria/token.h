#pragma once

#include <string>
#include <unordered_map>

struct Token
{
	enum TokenType
	{
		INT_LITERAL,
		STRING_LITERAL,
		IDENTIFIER,
		PLUS,
		MINUS,
		STAR,
		SLASH,
		ASSIGN,
		SEMICOLON,
		LEFT_BRACE,
		RIGHT_BRACE,
		LEFT_PAREN,
		RIGHT_PAREN,
		WHILE,
		GREATER,
		LESSER,
		EQUALS
	};

	TokenType type;
	int intLiteral;
	std::string stringLiteral;
};