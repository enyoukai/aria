#include "assembly.h"

#include <iostream>

std::string Assembly::OutputASM()
{
	std::string outputProgram = "";
	outputProgram += programEntry;
	outputProgram += prologue;
	for (std::string instruction : instructions)
		outputProgram += instruction;
	outputProgram += epilogue;

	return outputProgram;
}

void Assembly::MOV(std::string dest, std::string src)
{
	AddInstruction("mov", dest, src);
}

void Assembly::ADD(std::string dest, std::string src)
{
	AddInstruction("add", dest, src);
}

void Assembly::SUB(std::string dest, std::string src)
{
	AddInstruction("sub", dest, src);
}

void Assembly::IMUL(std::string dest, std::string src)
{
	AddInstruction("imul", dest, src);
}

void Assembly::IDIV(std::string dest, std::string src)
{
	AddInstruction("idiv", dest, src);
}

void Assembly::AddInstruction(std::string instruction, std::string LHS, std::string RHS)
{
#ifdef DEBUG
	std::cerr << ('\t' + instruction + '\t' + LHS + ", " + RHS) << std::endl;
#endif
	instructions.push_back('\t' + instruction + '\t' + LHS + ", " + RHS + '\n');
}

void Assembly::AddInstruction(std::string instruction, std::string LHS)
{
#ifdef DEBUG
	std::cerr << ('\t' + instruction + '\t' + LHS) << std::endl;
#endif
	instructions.push_back('\t' + instruction + '\t' + LHS + '\n');
}