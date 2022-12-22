#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <string>

#include "token.h"

class Scanner
{

public:
	Scanner(std::string file);
	std::vector<Token> Scan();
	void PrintTokens();

private:
	std::ifstream fileBuffer;
	std::string source;
	std::vector<Token> tokens;
	int curPos = -1;

	void NextToken();
	char Peek();
	char NextChar();

	void SkipWhitespace();
	void ProcessInteger();
	void ProcessIdentifier();
	void ProcessString();

	bool AtEOF();

	void AddToken(Token::TokenType type, int intLiteral);
	void AddToken(Token::TokenType type, std::string stringLiteral);
	void AddToken(Token::TokenType type);
};