#pragma once

#include <string>

class asmIR
{
private:
	std::string prologue =
		"\tpush rbp\n"
		"\tmov rbp, rsp\n";
	std::string epilogue =
		"\tmov rsp, rbp\n"
		"\tpop rbp\n"
		"ret";
};