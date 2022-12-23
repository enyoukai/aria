#pragma once

#include <string>
#include <vector>

class Assembly
{
public:
	std::string OutputASM();
	void MOV(std::string, std::string);
	void ADD(std::string, std::string);
	void SUB(std::string, std::string);
	void IMUL(std::string, std::string);
	void IDIV(std::string, std::string);

private:
	std::string programEntry =
		"global main\n"
		"section .text\n"
		"main:\n";
	std::string prologue =
		"\tpush \trbp\n"
		"\tmov \trbp, rsp\n";

	std::string epilogue =
		"\tmov \trsp, rbp\n"
		"\tpop \trbp\n"
		"\tret\n";

	void AddInstruction(std::string, std::string);
	void AddInstruction(std::string, std::string, std::string);

	std::vector<std::string> instructions;
};