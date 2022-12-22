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
	virtual std::string Print();
	virtual void CodeGen();
	virtual void Accept(Visitor *);
};

class BinaryAST : public ExprAST
{
public:
	BinaryAST(std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS, Token op);
	std::string Print() override;
	void Accept(Visitor *) override;

private:
	std::unique_ptr<ExprAST> leftOp, rightOp;
	Token op;
};

class LiteralAST : public ExprAST
{
public:
	LiteralAST(Token value);
	std::string Print() override;
	void Accept(Visitor *) override;

private:
	Token value;
};