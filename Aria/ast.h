#pragma once

#include "token.h"
#include <iostream>
#include <string>

class ExprAST
{
	// TODO: visitor later
public:
	virtual std::string Print() { return "what"; };
};

class BinaryAST : public ExprAST
{
public:
	BinaryAST(ExprAST LHS, ExprAST RHS, Token op) : leftOp(LHS), rightOp(RHS), op(op) {}
	std::string Print() override
	{
		return "(" + leftOp.Print() + "," + rightOp.Print() + "," + std::to_string(op.type) + ")";
	}

private:
	ExprAST leftOp;
	ExprAST rightOp;
	Token op;
};

class PrimaryAST : public ExprAST
{
public:
	PrimaryAST(Token value) : value(value) {}
	std::string Print() override
	{
		return "(" + std::to_string(value.intLiteral) + ")";
	}

private:
	Token value;
};