#pragma once

#include "token.h"
#include <iostream>
#include <string>
#include <memory>
#include "visitor.h"

class Visitor;

class ExprAST
{
public:
	virtual void CodeGen();
	virtual void Accept(Visitor *);
};

class BinaryAST : public ExprAST
{
public:
	BinaryAST(std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS, Token op);
	void Accept(Visitor *) override;

	std::unique_ptr<ExprAST> leftOp, rightOp;
	Token op;

private:
};

class LiteralAST : public ExprAST
{
public:
	LiteralAST(Token value);
	void Accept(Visitor *) override;

	Token value;

private:
};