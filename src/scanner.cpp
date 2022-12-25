#include "scanner.hpp"
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

	return tokens;
}

void Scanner::PrintTokens()
{
	std::string tokenMap[] = {"INT_LITERAl", "STRING_LITERAL", "IDENTIFIER", "PLUS", "MINUS", "STAR", "SLASH", "ASSIGN", "SEMICOLON", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_PAREN", "RIGHT_PAREN", "WHILE", "GREATER", "LESSER", "EQUALS"};
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
	case ':':
		AddToken(Token::ASSIGN);
		NextChar();
		break;
	case ';':
		AddToken(Token::SEMICOLON);
		NextChar();
		break;
	case '{':
		AddToken(Token::LEFT_BRACE);
		NextChar();
		break;
	case '}':
		AddToken(Token::RIGHT_BRACE);
		NextChar();
		break;
	case '(':
		AddToken(Token::LEFT_PAREN);
		NextChar();
		break;
	case ')':
		AddToken(Token::RIGHT_PAREN);
		NextChar();
		break;
	case '>':
		AddToken(Token::GREATER);
		NextChar();
		break;
	case '<':
		AddToken(Token::LESSER);
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

	// TODO: PLEASE MAKE THESE STATIC CONSTS cannot figure out why i can't make these static consts without linker errors
	const std::unordered_map<std::string, Token::TokenType> keywordMap = {
		{"while", Token::WHILE}};

	if (keywordMap.find(processed) != keywordMap.end())
	{
		AddToken(keywordMap.at(processed));
	}
	else
	{
		AddToken(Token::IDENTIFIER, processed);
	}
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