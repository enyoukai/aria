#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

enum TokenType
{
	INT,
	PLUS,
	MINUS,
	STAR,
	SLASH
};

struct Token
{
	int type;
	string val;
};

void scan_tokens(string);

int main()
{
	ifstream t("file.txt");
	stringstream buffer;
	buffer << t.rdbuf();

	string source = buffer.str();

	cout << source;
}

void scan_tokens(string filename)
{
	vector<Token> tokens;

	fstream fin(filename, fstream::in);

	while (fin.good())
	{
		struct Token tok;

		char c = fin.get();
		while (c == ' ')
			c = fin.get();

		switch (c)
		{
		case EOF:
			break;
		case '+':
			tok.type = PLUS;
			break;
		case '-':
			tok.type = MINUS;
			break;
		case '*':
			tok.type = STAR;
			break;
		case '/':
			tok.type = SLASH;
			break;
		default:
			tok.type = INT;
			tok.val = c;
		}
		tokens.push_back(tok);
	}

	string DEBUG[] = {"INT", "PLUS", "MINUS", "STAR", "SLASH"};

	for (Token t : tokens)
	{
		cout << DEBUG[t.type] << " : ";
		if (t.type == INT)
		{
			cout << t.val;
		}
		cout << '\n';
	}
}