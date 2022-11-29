#pragma once

#include <vector>
#include <string>

#include "token.h"

class Scanner
{

public:
	std::vector<Token> ScanTokens(std::string);

private:
	std::vector<Token> tokens;

	void ScanToken();
};