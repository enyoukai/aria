#include "asmir.h"

#include <iostream>

std::string asmIR::OutputASM()
{
	std::string outputProgram = "";
	outputProgram += programEntry;
	outputProgram += prologue;
	for (std::string instruction : instructions)
		outputProgram += instruction;
	outputProgram += epilogue;

	return outputProgram;
}

void asmIR::MOV(std::string dest, std::string src)
{
	AddInstruction("mov", dest, src);
}

void asmIR::AddInstruction(std::string instruction, std::string LHS, std::string RHS)
{
	instructions.push_back('\t' + instruction + '\t' + LHS + ", " + RHS + '\n');
}

void asmIR::AddInstruction(std::string instruction, std::string LHS)
{
	instructions.push_back('\t' + instruction + '\t' + LHS + '\n');
}