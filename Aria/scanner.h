#pragma once

#include <vector>
#include <string>

#include "token.h"

class Scanner
{

public:
	Scanner(std::string file);
	void Scan(std::string source);

private:
	std::string source;
	std::vector<Token> tokens;
	int curPos = 0;

	Token NextToken();
	void Advance();
	char Peek();
};