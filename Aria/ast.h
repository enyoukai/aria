#pragma once

#include "token.h"

class ExprAST
{
};

class BinaryAST : public ExprAST
{
public:
	BinaryAST(ExprAST LHS, ExprAST RHS, Token op) : leftOp(LHS), rightOp(RHS), op(op) {}

private:
	ExprAST leftOp;
	ExprAST rightOp;
	Token op;
};