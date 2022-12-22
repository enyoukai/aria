#pragma once

#include "ast.h"

class ExprAST;
class BinaryAST;
class LiteralAST;

class Visitor
{
	virtual void VisitExprAST(ExprAST *);
	virtual void VisitBinaryAST(BinaryAST *);
	virtual void VisitLiteralAST(LiteralAST *);
};

class PrinterVisitor : public Visitor
{
	void VisitExprAST(ExprAST *) override;

	void VisitBinaryAST(BinaryAST *) override;

	void VisitLiteralAST(LiteralAST *) override;
};