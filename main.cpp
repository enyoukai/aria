#include <iostream>
#include <fstream>

using namespace std;

void scan_tokens(char *);

int main()
{
	scan_tokens("test.aria");
}

void scan_tokens(char *filename)
{
	fstream fin(filename, fstream::in);
	char c = fin.get();

	while (fin.good())
	{
		cout << c;
		c = fin.get();
	}
}