#pragma once

#include "ast.hpp"
#include <unordered_map>
#include "assembly.hpp"

class AST;
class BinaryAST;
class LiteralAST;
class VariableAST;
class AssignmentAST;
class ComparisonAST;
class WhileAST;
class BlockAST;

class Visitor
{
public:
	virtual void VisitBinaryAST(BinaryAST *);
	virtual void VisitLiteralAST(LiteralAST *);
	virtual void VisitVariableAST(VariableAST *);
	virtual void VisitAssignmentAST(AssignmentAST *);
	virtual void VisitComparisonAST(ComparisonAST *);
	virtual void VisitWhileAST(WhileAST *);
	virtual void VisitBlockAST(BlockAST *);
};

class PrinterVisitor : public Visitor
{
public:
	PrinterVisitor();

	void VisitBinaryAST(BinaryAST *) override;
	void VisitLiteralAST(LiteralAST *) override;
	void VisitVariableAST(VariableAST *) override;
	void VisitAssignmentAST(AssignmentAST *) override;
	void VisitComparisonAST(ComparisonAST *) override;
	void VisitWhileAST(WhileAST *) override;
};

class CodeGenVisitor : public Visitor
{
public:
	CodeGenVisitor();
	void VisitBinaryAST(BinaryAST *) override;
	void VisitLiteralAST(LiteralAST *) override;
	void VisitVariableAST(VariableAST *) override;
	void VisitAssignmentAST(AssignmentAST *) override;
	void VisitComparisonAST(ComparisonAST *) override;
	void VisitWhileAST(WhileAST *) override;

	void OutputASM();

private:
	int stackPointer = 0;
	int loopCounter = 0;
	std::unordered_map<std::string, int> variableStackMap;
	Assembly asmIR;

	std::string result;

	int VariableToPointer(std::string);

	std::string CurrentRegisterAlloc();
	std::string PushRegisterAlloc();
	std::string PopRegisterAlloc();

	const std::vector<std::string> storageRegisters = {"rax", "rbx", "rcx", "rdx"};

	int currentRegisterAlloc = -1;
};