#include "scanner.h"
#include <iostream>
#include <sstream>
#include <fstream>

Scanner::Scanner(std::string fileName)
{
	fileBuffer = std::ifstream(fileName);
}

void Scanner::Scan()
{
	while (!AtEOF())
		NextToken();

#define DEBUG
#ifdef DEBUG
	for (Token t : tokens)
	{
		std::cout << t.type << '\n';
	}
#endif
}

void Scanner::NextToken()
{
	char curChar = ConsumeChar();

	switch (curChar)
	{
	case ' ':
	case '\t':
	case '\r':
		SkipWhitespace();
		break;

	case EOF:
		AddToken(Token::END_OF_FILE);
		break;
	case '+':
		AddToken(Token::PLUS);
		break;
	case '-':
		AddToken(Token::MINUS);
		break;
	case '*':
		AddToken(Token::STAR);
		break;
	case '/':
		AddToken(Token::SLASH);
		break;
	default:
		if (isdigit(curChar))
		{
			break;
		}
	}
}

char Scanner::ConsumeChar()
{
	return fileBuffer.get();
}

char Scanner::Peek()
{
	return fileBuffer.peek();
}

void Scanner::AddToken(Token::TokenType type)
{
	Token tok = {type};
	tokens.push_back(tok);
}

bool Scanner::AtEOF()
{
	return fileBuffer.peek() == EOF;
}

void Scanner::SkipWhitespace()
{
	while (Peek() == ' ' || Peek() == '\r' || Peek() == '\t')
	{
		ConsumeChar();
	}
}