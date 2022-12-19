#include "scanner.h"
#include <iostream>
#include <sstream>
#include <fstream>

Scanner::Scanner(std::string fileName)
{
	fileBuffer = std::ifstream(fileName);
}

std::vector<Token> Scanner::Scan()
{
	while (!AtEOF())
		NextToken();

// #define DEBUG
#ifdef DEBUG
	std::string tokenMap[] = {"INT_LITERAl", "STRING_LITERAL", "IDENTIFIER", "PLUS", "MINUS", "STAR", "SLASH", "EQUALS"};
	for (Token t : tokens)
	{
		std::cout << tokenMap[t.type];
		if (t.type == Token::INT_LITERAL)
		{
			std::cout << ' ' << t.intLiteral;
		}
		else if (t.type == Token::IDENTIFIER)
		{
			std::cout << ' ' << t.stringLiteral;
		}
		else if (t.type == Token::STRING_LITERAL)
		{
			std::cout << ' ' << t.stringLiteral;
		}
		std::cout << '\n';
	}
#endif
	return tokens;
}

void Scanner::NextToken()
{
	char curChar = Peek();

	switch (curChar)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		SkipWhitespace();
		break;

	case '+':
		AddToken(Token::PLUS);
		NextChar();
		break;
	case '-':
		AddToken(Token::MINUS);
		NextChar();
		break;
	case '*':
		AddToken(Token::STAR);
		NextChar();
		break;
	case '/':
		AddToken(Token::SLASH);
		NextChar();
		break;
	case '=':
		AddToken(Token::EQUALS);
		NextChar();
		break;
	case '\"':
		ProcessString();
		break;
	default:
		if (isdigit(curChar))
		{
			ProcessInteger();
		}
		else if (isalpha(curChar))
		{
			ProcessIdentifier();
		}
		else
		{
			std::cout << curChar << '\n';
			return;
		}
	}
}

char Scanner::NextChar()
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

void Scanner::AddToken(Token::TokenType type, int intLiteral)
{
	Token tok;
	tok.type = type;
	tok.intLiteral = intLiteral;
	tokens.push_back(tok);
}

void Scanner::AddToken(Token::TokenType type, std::string stringLiteral)
{
	Token tok;
	tok.type = type;
	tok.stringLiteral = stringLiteral;
	tokens.push_back(tok);
}

bool Scanner::AtEOF()
{
	return fileBuffer.peek() == EOF;
}

void Scanner::SkipWhitespace()
{
	while (Peek() == ' ' || Peek() == '\r' || Peek() == '\t' || Peek() == '\n')
	{
		NextChar();
	}
}

// TODO: CHECK FOR BAD INPUT
void Scanner::ProcessInteger()
{
	std::string processed = "";

	while (isdigit(Peek()))
	{
		processed += NextChar();
	}

	if (isalpha(Peek()))
	{
		std::cout << "Identifier cannot start with integer\n";
		return;
	}

	AddToken(Token::INT_LITERAL, std::stoi(processed));
}

void Scanner::ProcessIdentifier()
{
	std::string processed = "";

	while (isalnum(Peek()))
	{
		processed += NextChar();
	}

	AddToken(Token::IDENTIFIER, processed);
}

void Scanner::ProcessString()
{
	std::string processed = "";

	NextChar();

	while (Peek() != '\"')
	{
		if (AtEOF())
		{
			std::cout << "UNFINISHED STRING" << '\n';
			return;
		}
		processed += NextChar();
	}

	NextChar();

	AddToken(Token::STRING_LITERAL, processed);
}