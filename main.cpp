#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "scanner.h"

using namespace std;

void scan_tokens(string);

int main()
{
	ifstream t("test.aria");
	stringstream buffer;
	buffer << t.rdbuf();

	string source = buffer.str();

	Scanner scanner;
	scanner.ScanTokens(source);
}

// void scan_tokens(string filename)
// {
// 	vector<Token> tokens;

// 	fstream fin(filename, fstream::in);

// 	while (fin.good())
// 	{
// 		struct Token tok;

// 		char c = fin.get();
// 		while (c == ' ')
// 			c = fin.get();

// 		switch (c)
// 		{
// 		case EOF:
// 			break;
// 		case '+':
// 			tok.type = Token::PLUS;
// 			break;
// 		case '-':
// 			tok.type = Token::MINUS;
// 			break;
// 		case '*':
// 			tok.type = Token::STAR;
// 			break;
// 		case '/':
// 			tok.type = Token::SLASH;
// 			break;
// 		default:
// 			tok.type = Token::STRING_LITERAL;
// 			tok.stringLiteral = c;
// 		}
// 		tokens.push_back(tok);
// 	}

// 	string DEBUG[] = {"INT", "PLUS", "MINUS", "STAR", "SLASH"};

// 	for (Token t : tokens)
// 	{
// 		cout << DEBUG[t.type] << " : ";
// 		if (t.type == Token::INT_LITERAL)
// 		{
// 			cout << t.stringLiteral;
// 		}
// 		cout << '\n';
// 	}
// }