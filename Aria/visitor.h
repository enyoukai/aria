#pragma once

#include "ast.h"
#include <unordered_map>
#include "asmir.h"

class AST;
class BinaryAST;
class LiteralAST;
class VariableAST;
class AssignmentAST;

class Visitor
{
public:
	virtual void VisitBinaryAST(BinaryAST *);
	virtual void VisitLiteralAST(LiteralAST *);
	virtual void VisitVariableAST(VariableAST *);
	virtual void VisitAssignmentAST(AssignmentAST *);
};

class PrinterVisitor : public Visitor
{
public:
	PrinterVisitor();

	void VisitBinaryAST(BinaryAST *) override;
	void VisitLiteralAST(LiteralAST *) override;
	void VisitVariableAST(VariableAST *) override;
	void VisitAssignmentAST(AssignmentAST *) override;
};

class CodeGenVisitor : public Visitor
{
public:
	CodeGenVisitor();
	void VisitBinaryAST(BinaryAST *) override;
	void VisitLiteralAST(LiteralAST *) override;
	void VisitVariableAST(VariableAST *) override;
	void VisitAssignmentAST(AssignmentAST *) override;

	void OutputASM();

private:
	int stackPointer = 0;
	std::unordered_map<std::string, int> variableMap;
	std::string asmOutput;
	asmIR asmIR;
};