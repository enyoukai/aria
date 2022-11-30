#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "scanner.h"

using namespace std;

void scan_tokens(string);

int main()
{
	Scanner scanner("!test.aria");
	scanner.Scan();
}