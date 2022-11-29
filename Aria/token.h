#pragma once

struct Token
{
	enum TokenType
	{
		INT_LITERAL,
		STRING_LITERAL,
		STRING,
		PLUS,
		MINUS,
		STAR,
		SLASH
	};

	TokenType type;
	int intLiteral;
	int stringLiteral;
};