#include "scanner.h"
#include <iostream>
#include <sstream>
#include <fstream>

Scanner::Scanner(std::string fileName)
{
	std::ifstream fileStream(fileName);
	std::stringstream buffer;
	buffer << fileStream.rdbuf();

	source = buffer.str();
}

void Scanner::Scan(std::string source)
{
	Token curToken = NextToken();

	while (curToken.type != Token::END_OF_FILE)
	{
		tokens.push_back(curToken);
	}
}

Token Scanner::NextToken()
{
	Token tok;

	switch (source.getChar(curPos))
	{
	case '+':
		tok.type = Token::PLUS;
		return tok;
	case '-':
		tok.type = Token::MINUS;
		return tok;
	case '*':
		tok.type = Token::STAR;
		return tok;
	case '/':
		tok.type = Token::SLASH;
		return tok;
	default:
		if (isdigit())
	}
}