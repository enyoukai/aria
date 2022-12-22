#pragma once

#include "ast.h"

class ExprAST;
class BinaryAST;
class LiteralAST;

class Visitor
{
public:
	virtual void VisitBinaryAST(BinaryAST *);
	virtual void VisitLiteralAST(LiteralAST *);
};

class PrinterVisitor : public Visitor
{
public:
	PrinterVisitor();

	void VisitBinaryAST(BinaryAST *) override;

	void VisitLiteralAST(LiteralAST *) override;
};

class CodeGenVisitor : public Visitor
{
	CodeGenVisitor();
	void VisitBinaryAST(BinaryAST *) override;
	void VisitLiteralAST(LiteralAST *) override;
};