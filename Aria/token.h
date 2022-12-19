#pragma once

#include <string>

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
		EQUALS
	};

	TokenType type;
	int intLiteral;
	std::string stringLiteral;
};

