#pragma once

#include <vector>
#include <string>

#include "token.h"

class Scanner
{

public:
	void ScanTokens(std::string source);

private:
	std::vector<Token> tokens;

	void ScanToken();
};