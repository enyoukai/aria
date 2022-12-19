#pragma once

#include "token.h"
#include <iostream>
#include <string>
#include <memory>

class ExprAST
{
	// TODO: visitor later
public:
	virtual std::string Print() { return "what"; };
};

class BinaryAST : public ExprAST
{
public:
	BinaryAST(std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS, Token op) : leftOp(std::move(LHS)), rightOp(std::move(RHS)), op(op) {}
	std::string Print() override
	{
		std::string TOKEN_MAP[] = {"INT_LITERAl", "STRING_LITERAL", "IDENTIFIER", "PLUS", "MINUS", "STAR", "SLASH", "EQUALS"};
		return "(" + leftOp->Print() + "," + rightOp->Print() + "," + TOKEN_MAP[op.type] + ")";
	}

private:
	std::unique_ptr<ExprAST> leftOp, rightOp;
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