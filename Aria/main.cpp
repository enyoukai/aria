#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "scanner.h"

using namespace std;

void scan_tokens(string);

int main()
{
	Scanner scanner("!.aria");
	scanner.Scan();
}